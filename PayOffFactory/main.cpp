#include "ArgList.h"
#include "PayOff3.h"
#include "PayOffConstructible.h"
#include "PayOffBridge.h"
#include "PayOffFactory.h"
#include <string>
#include <iostream>
using namespace std;

int main()
{
    // Constants given in question
    double Expiry = 1;
    double Strike = 50;
    double Spot = 50;
    double Vol = 0.3;
    double r = 0.05;
    double d = 0.08;
    double b = 3;
    double Steps = 3;
    double n = 100;
    std::string name;

    // Setup argument list        
    ArgumentList args("myArgs");
    args.add("Strike", Strike);
    args.add("Expiry", Expiry);
    args.add("Spot", Spot);
    args.add("Vol", Vol);
    args.add("r", r);
    args.add("d", d);
    args.add("b", b);
    args.add("Steps", Steps);
    args.add("n", n);
    
    // Take user input on payoff
    cout << "\nEnter class name: ";
    cin >> name;

    // Generate payoff pointer    
    PayOff* PayOffPtr = PayOffFactory::Instance().CreatePayOff(name,args);
    
    // Calculate price of payoff if payoff exists
    if (PayOffPtr != NULL)
    {
        cout << "\n" << "Price of " << name << ": " << PayOffPtr->operator ()(Spot) << "\n";
        delete PayOffPtr;
    }
    
    return 0;
}
