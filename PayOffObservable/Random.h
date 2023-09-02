//
//  Random2.h
//  ch6_random_number_class
//
//  Created by cheerzzh on 19/6/14.
//  Copyright (c) 2014年 Jared Zhou. All rights reserved.
//
#ifndef __Option_Class__Random__
#define __Option_Class__Random__

#include <vector>

double GetOneGaussianByBoxMuller();

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
                       );

void GetGBMSpotPricePath(std::vector<double>& spotPrices,
						// Vector of spot prices to be filled in
						const double& r,
						// Risk free interest rate (constant)
						const double& v,
						// Volatility of underlying (constant)
						const double& T
						// Expiry
						);

#endif /* defined(__Option_Class__Random__) */
