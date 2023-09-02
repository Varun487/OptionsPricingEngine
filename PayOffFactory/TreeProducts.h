//
//  TreeProduct.hpp
//  ch8_trees
//
//  Created by Steve Yang on 10/12/21.
//

#ifndef TreeProduct_hpp
#define TreeProduct_hpp

class TreeProducts
{
public:

    TreeProducts(double FinalTime_);
    virtual double FinalPayOff(double Spot) const=0;
    virtual double PreFinalValue(double Spot,
                                 double Time,
                                 double DiscountedFutureValue) const=0;
    virtual ~TreeProducts(){}
    virtual TreeProducts* clone() const=0;
    double GetFinalTime() const;

private:
    double FinalTime;

};

#endif /* TreeProduct_hpp */
