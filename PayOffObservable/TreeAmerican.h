//
//  TreeAmerican.hpp
//  ch8_trees
//
//  Created by Steve Yang on 10/12/21.
//

#ifndef TreeAmerican_hpp
#define TreeAmerican_hpp

#include "TreeProducts.h"
#include "PayOffBridge.h"

class TreeAmerican : public TreeProducts
{

public:

    TreeAmerican(double FinalTime,
                 const PayOffBridge& ThePayOff_);

    virtual TreeProducts* clone() const;
    virtual double FinalPayOff(double Spot) const;
    virtual double PreFinalValue(double Spot,
                                 double Time,
                                 double DiscountedFutureValue) const;
    virtual ~TreeAmerican(){}

private:

    PayOffBridge ThePayOff;

};


#endif /* TreeAmerican_hpp */
