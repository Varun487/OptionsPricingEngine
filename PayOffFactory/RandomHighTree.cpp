#include "RandomHighTree.h"
#include "Random.h"
#include "Arrays.h"
#include <cmath>

// the basic math functions should be in namespace std but aren't in VCPP6
#if !defined(_MSC_VER)
using namespace std;
#endif

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

    // Return high estimate of option
    return TheTree[0][0].second;
}
