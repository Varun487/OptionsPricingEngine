#include <iostream>
#include "OptionPricingReportWriter.hpp"
#include "TreeObservable.hpp"
#include "PayOff3.h"
#include "TreeAmerican.h"
#include "Parameters.h"

using namespace QuantLib;

int main(int argc, const char * argv[]) {

    // Setup parameters
    double Expiry = 1;
    double Strike = 50;
    double Spot = 50;
    double Vol = 0.3;
    double r = 0.05;
    double d = 0.08;
    double b = 3;
    unsigned long Steps = 3;

    // Create a PayOff objects for Call and Put Options
    PayOffCall thePayOffCall(Strike);
	PayOffPut thePayOffPut(Strike);

    // Create a risk free rate ParametersConstant
    ParametersConstant rParam(r);

    // Create a dividend ParametersConstant
    ParametersConstant dParam(d);

    // Create a TreeAmerican object
	TreeAmerican TreeAmerCall(Expiry, thePayOffCall);
	TreeAmerican TreeAmerPut(Expiry, thePayOffPut);

    // Create multiple observables
    pTreeObservable BNCallPricer(new SimpleBinomialTree(Spot, rParam, dParam, Vol, Steps, Expiry));
    pTreeObservable BNPutPricer(new SimpleBinomialTree(Spot, rParam, dParam, Vol, Steps, Expiry));
    pTreeObservable RTCallHPricer(new RandomHighTree(Spot, rParam, dParam, Vol, Steps, Expiry, b));
    pTreeObservable RTPutHPricer(new RandomHighTree(Spot, rParam, dParam, Vol, Steps, Expiry, b));
    pTreeObservable RTCallLPricer(new RandomLowTree(Spot, rParam, dParam, Vol, Steps, Expiry, b));
    pTreeObservable RTPutLPricer(new RandomLowTree(Spot, rParam, dParam, Vol, Steps, Expiry, b));

    // Register observables with observer and call the GetThePrice method to log answers to console
    OptionPricingReportWriter OPRW(BNCallPricer, "BNCall");
    BNCallPricer->GetThePrice(TreeAmerCall);

    OPRW.registerPricer(BNPutPricer, "BNPut");
    BNPutPricer->GetThePrice(TreeAmerPut);

    OPRW.registerPricer(RTCallHPricer, "RTCallH");
    RTCallHPricer->GetThePrice(TreeAmerCall);

    OPRW.registerPricer(RTPutHPricer, "RTPutH");
    RTPutHPricer->GetThePrice(TreeAmerPut);

    OPRW.registerPricer(RTCallLPricer, "RTCallL");
    RTCallLPricer->GetThePrice(TreeAmerCall);

    OPRW.registerPricer(RTPutLPricer, "RTPutL");
    RTPutLPricer->GetThePrice(TreeAmerPut);

    return 0;
}
