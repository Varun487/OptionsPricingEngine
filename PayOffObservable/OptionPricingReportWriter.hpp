#ifndef OptionPricingReportWriter_hpp
#define OptionPricingReportWriter_hpp

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <ql/patterns/observable.hpp>
#include "TreeObservable.hpp"

using namespace QuantLib;

// Shared pointer ot tree observable
typedef boost::shared_ptr<TreeObservable> pTreeObservable;

class OptionPricingReportWriter : public Observer {
  private:
    pTreeObservable TreeObservable;
    std::string name;
  public:
    OptionPricingReportWriter(pTreeObservable TreeObs, std::string name_) : TreeObservable(TreeObs), name(name_)
    {
        this->registerWith(TreeObservable);
    }
    void registerPricer(pTreeObservable TreeObs, std::string name_)
    {
      TreeObservable = TreeObs;
      name = name_;
      this->registerWith(TreeObservable);
    }
    void update() 
    {
        std::cout << "OptionPricingReportWriter: " << name  << " value = " << TreeObservable->GetOptionValue() << std::endl;
    }
};

#endif /* OptionPricingReportWriter_hpp */
