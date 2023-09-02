#pragma warning( disable : 4786 )

#include "TreeProducts.h"
#include "Parameters.h"
#include "Arrays.h"
#include <vector>

class RandomHighTree
{

public:
    RandomHighTree(double Spot_,
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
    unsigned long Steps;
    double Time;
    double b;
    bool TreeBuilt;

    std::vector<std::vector<std::pair<double, double> > > TheTree;
    MJArray Discounts;
};
