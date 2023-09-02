#include "RandomLowTree.h"
#include "Random.h"
#include "Arrays.h"
#include <cmath>
#include <iostream>

// the basic math functions should be in namespace std but aren't in VCPP6
#if !defined(_MSC_VER)
using namespace std;
#endif

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

    // Return high estimate of option
    return TheTree[0][0].second;
}
