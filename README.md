# Options Pricing Engine

## Aim

To build an option pricer using the Binomial tree and Random tree pricing methods while utilizing the observer-observable and Factory object oriented programming design patterns.

## Build the project

1. Initialize the project

```bash
git clone git@github.com:Varun487/OptionsPricingEngine.git
cd OptionsPricingEngine
```

2. Install the Quantlib C++ library.

3. To compile and run the Options pricer using factory pattern

```bash
g++ main.cpp ArgList.cpp Arrays.cpp BinomialTree.cpp Parameters.cpp PayOff3.cpp PayOffBridge.cpp PayOffConstructible.cpp PayOffFactory.cpp Random.cpp RandomHighTree.cpp RandomLowTree.cpp TreeAmerican.cpp TreeProducts.cpp -o run
./run
```

4. To compile and run the Options pricer using observer-observable pattern
```bash
g++ -I'PATH_TO_BOOST_INSTALLATION' $(quantlib-config --cflags --libs) main.cpp OptionPricingReportWriter.cpp TreeObservable.cpp Arrays.cpp Parameters.cpp PayOff3.cpp PayOffBridge.cpp TreeAmerican.cpp TreeProducts.cpp Random.cpp -o run
./run
```

Replace `PATH_TO_BOOST_INSTALLATION` with the path to the directory of your boost installation.
