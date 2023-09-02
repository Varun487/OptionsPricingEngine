//
//  TreeProduct.cpp
//  ch8_trees
//
//  Created by Steve Yang on 10/12/21.
//

#include "TreeProducts.h"

TreeProducts::TreeProducts(double FinalTime_)
: FinalTime(FinalTime_)
{
}

double TreeProducts::GetFinalTime() const
{
    return FinalTime;
}
