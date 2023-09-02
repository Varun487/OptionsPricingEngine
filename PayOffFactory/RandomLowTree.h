#pragma warning( disable : 4786 )

#include "TreeProducts.h"
#include "Parameters.h"
#include "Arrays.h"
#include <vector>

class RandomLowTree
{

public:
    RandomLowTree(double Spot_,
                       const Parameters& r_,
                       const Parameters& d_,
                       double Volatility_,
                       unsigned long Steps,
                       double Time,
                       double b);

    double GetThePrice(const TreeProducts& TheProduct);

protected:

    void BuildTree();

private:
  
    double Spot;
    Parameters r;
    Parameters d;
    double Volatility;
    double b;
    unsigned long Steps;
    double Time;
    bool TreeBuilt;

    std::vector<std::vector<std::pair<double, double> > > TheTree;
    MJArray Discounts;
};
