#ifndef TreeObservable_hpp
#define TreeObservable_hpp

#include <stdio.h>
#include <ql/patterns/observable.hpp>
#include "Arrays.h"
#include "Parameters.h"
#include "TreeProducts.h"
#include "Random.h"

using namespace QuantLib;

class TreeObservable : public Observable 
{
  protected:
    double optionValue;
  public:
    virtual double GetThePrice(const TreeProducts& TheProduct) = 0;
    double GetOptionValue()
    {
      return optionValue;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////

class SimpleBinomialTree : public TreeObservable
{

public:
    SimpleBinomialTree(double Spot_,
                       const Parameters& r_,
                       const Parameters& d_,
                       double Volatility_,
                       unsigned long Steps,
                       double Time);

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
    bool TreeBuilt;

    std::vector<std::vector<std::pair<double, double> > > TheTree;
    MJArray Discounts;
};

////////////////////////////////////////////////////////////////////////////////////////////

class RandomHighTree : public TreeObservable
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

////////////////////////////////////////////////////////////////////////////////////////////

class RandomLowTree : public TreeObservable
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

#endif /* TreeObservable_hpp */
