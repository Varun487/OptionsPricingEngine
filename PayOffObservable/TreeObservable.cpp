#include "TreeObservable.hpp"

SimpleBinomialTree::SimpleBinomialTree(double Spot_,
                                       const Parameters& r_,
                                       const Parameters& d_,
                                       double Volatility_,
                                       unsigned long Steps_,
                                       double Time_)
                                       : Spot(Spot_),
                                         r(r_),
                                         d(d_),
                                         Volatility(Volatility_),
                                         Steps(Steps_),
                                         Time(Time_),
                                         Discounts(Steps)
{
    TreeBuilt=false;
}

void SimpleBinomialTree::BuildTree()
{
    TreeBuilt = true;
    TheTree.resize(Steps+1);
    
    double InitialLogSpot = log(Spot);

    for (unsigned long i=0; i <=Steps; i++)
    {

        TheTree[i].resize(i+1);

        double thisTime = (i*Time)/Steps;

        double movedLogSpot =
                            InitialLogSpot+ r.Integral(0.0, thisTime)
                                          - d.Integral(0.0, thisTime);
    
        movedLogSpot -= 0.5*Volatility*Volatility*thisTime;

        double sd = Volatility*sqrt(Time/Steps);

        for (long j = -static_cast<long>(i), k=0; j <= static_cast<long>(i); j=j+2,k++)
              TheTree[i][k].first = exp(movedLogSpot+ j*sd);
    }
   
    for (unsigned long l=0; l <Steps; l++)
    {
        Discounts[l] = exp(- r.Integral(l*Time/Steps,(l+1)*Time/Steps));
    }
}

double SimpleBinomialTree::GetThePrice(const TreeProducts& TheProduct)
{
    if (!TreeBuilt)
        BuildTree();

    if (TheProduct.GetFinalTime() != Time)
        throw("mismatched product in SimpleBinomialTree");

    for (long j = -static_cast<long>(Steps), k=0; j <=static_cast<long>( Steps); j=j+2,k++)
        TheTree[Steps][k].second = TheProduct.FinalPayOff(TheTree[Steps][k].first);

    for (unsigned long i=1; i <= Steps; i++)
    {
        unsigned long index = Steps-i;
        double ThisTime = index*Time/Steps;
   
        for (long j = -static_cast<long>(index), k=0; j <= static_cast<long>(index); j=j+2,k++)
        {
            double Spot = TheTree[index][k].first;
            double futureDiscountedValue =
                            0.5*Discounts[index]*(TheTree[index+1][k].second+TheTree[index+1][k+1].second);
            TheTree[index][k].second = TheProduct.PreFinalValue(Spot,ThisTime,futureDiscountedValue);
        }
        
    }

    // Set option value
    optionValue = TheTree[0][0].second;

    // Notify observers
    notifyObservers();

    return TheTree[0][0].second;
}

////////////////////////////////////////////////////////////////////////////////////////////

RandomHighTree::RandomHighTree(double Spot_,
                                       const Parameters& r_,
                                       const Parameters& d_,
                                       double Volatility_,
                                       unsigned long Steps_,
                                       double Time_,
                                       double b_)
                                       : Spot(Spot_),
                                         r(r_),
                                         d(d_),
                                         Volatility(Volatility_),
                                         Steps(Steps_),
                                         Time(Time_),
                                         Discounts(Steps),
                                         b(b_)

{
    TreeBuilt=false;
}

void RandomHighTree::BuildTree()
{
    // Setup tree
    TreeBuilt = true;
    TheTree.resize(Steps+1);

    // Setup variables for simulation
    double delta_time;
    double step_length;

    // Simulate price paths for random tree    
    for (unsigned long i=0; i <=Steps; i++)
    {
        // Determine number of prices per step
        step_length = pow(b, i);

        // Allocate memory
        TheTree[i].resize(step_length);

        // Set Spot price at 0th step of tree
        if (i == 0)
        {
            TheTree[0][0].first = Spot;
        } 
        // Get next price in GBM for all other steps
        else 
        {
            delta_time = Time/Steps;

            // Set prices for all paths
            for (long j = 0; j < step_length; j++) 
            {
                TheTree[i][j].first = GetGBMNextPrice(TheTree[i-1][floor(j/b)].first, r.Integral(0.0,i*delta_time), d.Integral(0.0,i*delta_time), Volatility, delta_time);
            }
        }
    }

    // Set discounts
    for (unsigned long l=0; l <Steps; l++)
    {
        Discounts[l] = exp(- r.Integral(l*Time/Steps,(l+1)*Time/Steps));
    }
}

double RandomHighTree::GetThePrice(const TreeProducts& TheProduct)
{
    if (!TreeBuilt)
        BuildTree();

    if (TheProduct.GetFinalTime() != Time)
        throw("Mismatched product in RandomHighTree");

    // Set number of prices in a step
    double step_length = pow(b, Steps);
    double next_step_avg_payoff;
    
    // Caluclate payoff at terminal nodes
    for (long j = 0; j < step_length; j++)
    {
        TheTree[Steps][j].second = TheProduct.FinalPayOff(TheTree[Steps][j].first);
    }

    // Calculate price at each node for all previous steps by backtracking
    for (int i = Steps-1; i >= 0; i--)
    {
        step_length = pow(b, i);
        next_step_avg_payoff = 0;

        for (int j = 0; j < step_length; j++)
        {
            // Caluculate the average high estimates from the next step
            for (int k = 0; k < b; k++)
            {
                next_step_avg_payoff += TheTree[i+1][(j*b) + k].second;
            }
            next_step_avg_payoff = next_step_avg_payoff/b;

            // Set high estimate value
            if (next_step_avg_payoff <= TheProduct.FinalPayOff(TheTree[i][j].first))
            {
                TheTree[i][j].second = TheProduct.FinalPayOff(TheTree[i][j].first);
            }
            else
            {
                TheTree[i][j].second = next_step_avg_payoff;
            }
        }
    }

    // Set tree built as false to rebuild tree for next simulation
    TreeBuilt = false;

    // Set option value
    optionValue = TheTree[0][0].second;

    // Notify observers
    notifyObservers();

    // Return high estimate of option
    return TheTree[0][0].second;
}

////////////////////////////////////////////////////////////////////////////////////////////

RandomLowTree::RandomLowTree(double Spot_,
                                       const Parameters& r_,
                                       const Parameters& d_,
                                       double Volatility_,
                                       unsigned long Steps_,
                                       double Time_,
                                       double b_)
                                       : Spot(Spot_),
                                         r(r_),
                                         d(d_),
                                         Volatility(Volatility_),
                                         Steps(Steps_),
                                         Time(Time_),
                                         Discounts(Steps),
                                         b(b_)

{
    TreeBuilt=false;
}

void RandomLowTree::BuildTree()
{
    // Setup tree
    TreeBuilt = true;
    TheTree.resize(Steps+1);

    // Setup variables for simulation
    double delta_time;
    double step_length;

    for (unsigned long i=0; i <=Steps; i++)
    {
        
        // Determine number of prices per step
        step_length = pow(b, i);

        // Allocate memory
        TheTree[i].resize(step_length);

        // Set Spot price at 0th step of tree
        if (i == 0)
        {
            TheTree[0][0].first = Spot;
        } 
        // Get next price in GBM for all other steps
        else 
        {
            delta_time = Time/Steps; 

            // Set prices for all paths
            for (long j = 0; j < step_length; j++) 
            {
                TheTree[i][j].first = GetGBMNextPrice(TheTree[i-1][floor(j/b)].first, r.Integral(0.0,i*delta_time), d.Integral(0.0,i*delta_time), Volatility, delta_time);
            }
        }
    }
    
    // Set discounts
    for (unsigned long l=0; l <Steps; l++)
    {
        Discounts[l] = exp(- r.Integral(l*Time/Steps,(l+1)*Time/Steps));
    }
}

double RandomLowTree::GetThePrice(const TreeProducts& TheProduct)
{
    if (!TreeBuilt)
        BuildTree();

    if (TheProduct.GetFinalTime() != Time)
        throw("mismatched product in SimpleBinomialTree");

    // Setup
    double step_length = pow(b, Steps);
    double next_step_avg_payoff;
    double v_ik[int(b)];
    double v_ik_avg;

    // Caluclate payoff at terminal nodes
    for (long j = 0; j < step_length; j++)
    {
        TheTree[Steps][j].second = TheProduct.FinalPayOff(TheTree[Steps][j].first);
    }

    // Calculate price at each node for all previous steps by backtracking
    for (int i = Steps-1; i >= 0; i--)
    {
        step_length = pow(b, i);

        for (int j = 0; j < step_length; j++)
        {
            v_ik_avg = 0;

            // Caluclate v_ik
            for (int k = 0; k < b; k++){
                next_step_avg_payoff = 0;
                v_ik[k] = 0;

                // Calculate next step's avg payoff
                for (int l = 0; l < b; l++){
                    if (l != k)
                    {
                        next_step_avg_payoff += TheTree[i+1][j*b +l].second;
                    }
                }
                next_step_avg_payoff = next_step_avg_payoff/(b-1);

                // Set v_ik value  
                if (next_step_avg_payoff <= TheProduct.FinalPayOff(TheTree[i][j].first)){
                    v_ik[k] = TheProduct.FinalPayOff(TheTree[i][j].first);
                }
                else {
                    v_ik[k] = TheTree[i+1][j*b + k].second;
                }
            }
            
            // Calculate average of v_ik
            for (int k = 0; k < b; k++) {
                v_ik_avg += v_ik[k];
            }
            v_ik_avg = v_ik_avg/b;

            // Set low estimate
            TheTree[i][j].second = v_ik_avg;
        }
    }

    // Set tree built as false to rebuild tree for next simulation
    TreeBuilt = false;

    // Set option value
    optionValue = TheTree[0][0].second;

    // Notify observers
    notifyObservers();

    // Return high estimate of option
    return TheTree[0][0].second;
}
