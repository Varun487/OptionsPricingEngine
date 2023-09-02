//
//  TreeAmerican.cpp
//  ch8_trees
//
//  Created by Steve Yang on 10/12/21.
//

#include "TreeAmerican.h"
#include <algorithm>

TreeAmerican::TreeAmerican(double FinalTime,
                           const PayOffBridge& ThePayOff_)
                 : TreeProducts(FinalTime),
                   ThePayOff(ThePayOff_)
{
}

TreeProducts* TreeAmerican::clone() const
{
     return new TreeAmerican(*this);
}

double TreeAmerican::FinalPayOff(double Spot) const
{
    return ThePayOff(Spot);
}

double TreeAmerican::PreFinalValue(double Spot,
                                 double , // Borland compiler doesnt like unused named variables
                                 double DiscountedFutureValue) const
{
    return std::max(ThePayOff(Spot), DiscountedFutureValue);
}

