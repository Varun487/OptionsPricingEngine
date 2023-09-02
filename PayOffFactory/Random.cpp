//
//  Random2.cpp
//  ch6_random_number_class
//
//  Created by cheerzzh on 19/6/14.
//  Copyright (c) 2014年 Jared Zhou. All rights reserved.
//
#include <math.h>
#include "Random.h"

// the basic math functions should be in namespace std but aren't in VCPP6
#if !defined(_MSC_VER)
using namespace std;
#endif

double GetOneGaussianByBoxMuller()
{
	double result;
	double x, y;
	double sizeSquared;

	do
	{
		x = 2.0 * rand() / static_cast<double>(RAND_MAX) - 1;
		y = 2.0 * rand() / static_cast<double>(RAND_MAX) - 1;
		sizeSquared = x * x + y * y;
	} while (sizeSquared >= 1.0);
	result = x * sqrt(-2 * log(sizeSquared) / sizeSquared);

	return result;
}

// Generate next price
double GetGBMNextPrice(
                       // Initial price
                       const double S_0,
                       // Risk free interest rate (constant)
                       const double& r,
                       // Dividend rate (constant)
                       const double& d,               // Volatility of underlying (constant)
                       const double& v,
                       // Time step size
                       const double& dT
                       )
{
    double drift = exp(dT * (r - d - 0.5 * v * v));
    double vol = sqrt(v * v * dT);
    double gauss_bm = GetOneGaussianByBoxMuller();
    double S = S_0 *  drift * exp(vol * gauss_bm);
    return S;
}

// Generate a path
void GetGBMSpotPricePath(std::vector<double>& spotPrices,
						// Vector of spot prices to be filled in
						const double& r,
						// Risk free interest rate (constant)
						const double& v,
						// Volatility of underlying (constant)
						const double& T
						// Expiry
						)
{
	double dT = T / static_cast<double>(spotPrices.size() - 1); // T / Num of Intervals
	double drift = exp(dT * (r - 0.5 * v * v));
	double vol = sqrt(v * v * dT);

	for (int i = 1; i < spotPrices.size(); i++) // spotPrices[0] = S_0
	{
		double gauss_bm = GetOneGaussianByBoxMuller();
		spotPrices[i] = spotPrices[i - 1] * drift * exp(vol * gauss_bm);
	}
}
