//
//  PayOff3.cpp
//  ch10_factory_pattern
//
//  Created by cheerzzh on 24/6/14.
//  Copyright (c) 2014年 Jared Zhou. All rights reserved.
//

#include "PayOff3.h"
#include <algorithm>
#include "BinomialTree.h"
#include "TreeAmerican.h"
#include "RandomHighTree.h"
#include "RandomLowTree.h"

PayOffCall::PayOffCall(ArgumentList& args)
{
    Strike = args.GetDoubleArgumentValue("Strike");
}

double PayOffCall::operator() (double Spot) const
{
    return std::max(Spot - Strike, 0.0);
}

PayOff* PayOffCall::clone() const
{
    return new PayOffCall(*this); // return a copy of current payoff class
}

///////////////////////////////////////////////////////////////////////////////

PayOffPut::PayOffPut(ArgumentList& args)
{
    Strike = args.GetDoubleArgumentValue("Strike");
}

double PayOffPut::operator()(double Spot) const
{
    return std::max(Strike - Spot, 0.0);
}

PayOff* PayOffPut::clone() const
{
    return new PayOffPut(* this);
}

///////////////////////////////////////////////////////////////////////////////

PayOffBNCall::PayOffBNCall(ArgumentList& args)
{
    PayOffCall thePayOffCall(args);
    TreeAmerican TreeAmerCall(args.GetDoubleArgumentValue("Expiry"), thePayOffCall);
    ParametersConstant rParam(args.GetDoubleArgumentValue("r"));
    ParametersConstant dParam(args.GetDoubleArgumentValue("d"));
    SimpleBinomialTree BinomTree(args.GetDoubleArgumentValue("Spot"),
                                 rParam,
                                 dParam,
                                 args.GetDoubleArgumentValue("Vol"),
                                 args.GetDoubleArgumentValue("Steps"),
                                 args.GetDoubleArgumentValue("Expiry"));
    BNCallPrice = BinomTree.GetThePrice(TreeAmerCall);
}

double PayOffBNCall::operator()(double Spot) const
{
    return BNCallPrice;
}

PayOff* PayOffBNCall::clone() const
{
    return new PayOffBNCall(* this);
}

///////////////////////////////////////////////////////////////////////////////

PayOffBNPut::PayOffBNPut(ArgumentList& args)
{
    PayOffPut thePayOffPut(args);
    TreeAmerican TreeAmerPut(args.GetDoubleArgumentValue("Expiry"), thePayOffPut);
    ParametersConstant rParam(args.GetDoubleArgumentValue("r"));
    ParametersConstant dParam(args.GetDoubleArgumentValue("d"));
    SimpleBinomialTree BinomTree(args.GetDoubleArgumentValue("Spot"),
                                 rParam,
                                 dParam,
                                 args.GetDoubleArgumentValue("Vol"),
                                 args.GetDoubleArgumentValue("Steps"),
                                 args.GetDoubleArgumentValue("Expiry"));
    BNPutPrice = BinomTree.GetThePrice(TreeAmerPut);
}

double PayOffBNPut::operator()(double Spot) const
{
    return BNPutPrice;
}

PayOff* PayOffBNPut::clone() const
{
    return new PayOffBNPut(* this);
}

///////////////////////////////////////////////////////////////////////////////

PayOffRTCallH::PayOffRTCallH(ArgumentList& args)
{
    PayOffCall thePayOffCall(args);
    TreeAmerican TreeAmerCall(args.GetDoubleArgumentValue("Expiry"), thePayOffCall);
    ParametersConstant rParam(args.GetDoubleArgumentValue("r"));
    ParametersConstant dParam(args.GetDoubleArgumentValue("d"));
    RandomHighTree RHighTree(args.GetDoubleArgumentValue("Spot"),
                                 rParam,
                                 dParam,
                                 args.GetDoubleArgumentValue("Vol"),
                                 args.GetDoubleArgumentValue("Steps"),
                                 args.GetDoubleArgumentValue("Expiry"),
                                 args.GetDoubleArgumentValue("b"));
    RTCallHPrice = 0;
    for (int i = 0; i < args.GetDoubleArgumentValue("n"); i++){
        RTCallHPrice += RHighTree.GetThePrice(TreeAmerCall);
    }
    RTCallHPrice = RTCallHPrice/args.GetDoubleArgumentValue("n");
}

double PayOffRTCallH::operator()(double Spot) const
{
    return RTCallHPrice;
}

PayOff* PayOffRTCallH::clone() const
{
    return new PayOffRTCallH(* this);
}

///////////////////////////////////////////////////////////////////////////////

PayOffRTCallL::PayOffRTCallL(ArgumentList& args)
{
    PayOffCall thePayOffCall(args);
    TreeAmerican TreeAmerCall(args.GetDoubleArgumentValue("Expiry"), thePayOffCall);
    ParametersConstant rParam(args.GetDoubleArgumentValue("r"));
    ParametersConstant dParam(args.GetDoubleArgumentValue("d"));
    RandomLowTree RLowTree(args.GetDoubleArgumentValue("Spot"),
                                 rParam,
                                 dParam,
                                 args.GetDoubleArgumentValue("Vol"),
                                 args.GetDoubleArgumentValue("Steps"),
                                 args.GetDoubleArgumentValue("Expiry"),
                                 args.GetDoubleArgumentValue("b"));
    RTCallLPrice = 0;
    for (int i = 0; i < args.GetDoubleArgumentValue("n"); i++){
        RTCallLPrice += RLowTree.GetThePrice(TreeAmerCall);
    }
    RTCallLPrice = RTCallLPrice/args.GetDoubleArgumentValue("n");
}

double PayOffRTCallL::operator()(double Spot) const
{
    return RTCallLPrice;
}

PayOff* PayOffRTCallL::clone() const
{
    return new PayOffRTCallL(* this);
}

///////////////////////////////////////////////////////////////////////////////

PayOffRTPutH::PayOffRTPutH(ArgumentList& args)
{
    PayOffPut thePayOffPut(args);
    TreeAmerican TreeAmerPut(args.GetDoubleArgumentValue("Expiry"), thePayOffPut);
    ParametersConstant rParam(args.GetDoubleArgumentValue("r"));
    ParametersConstant dParam(args.GetDoubleArgumentValue("d"));
    RandomHighTree RHighTree(args.GetDoubleArgumentValue("Spot"),
                                 rParam,
                                 dParam,
                                 args.GetDoubleArgumentValue("Vol"),
                                 args.GetDoubleArgumentValue("Steps"),
                                 args.GetDoubleArgumentValue("Expiry"),
                                 args.GetDoubleArgumentValue("b"));
    RTPutHPrice = 0;
    for (int i = 0; i < args.GetDoubleArgumentValue("n"); i++){
        RTPutHPrice += RHighTree.GetThePrice(TreeAmerPut);
    }
    RTPutHPrice = RTPutHPrice/args.GetDoubleArgumentValue("n");
}

double PayOffRTPutH::operator()(double Spot) const
{
    return RTPutHPrice;
}

PayOff* PayOffRTPutH::clone() const
{
    return new PayOffRTPutH(* this);
}

///////////////////////////////////////////////////////////////////////////////

PayOffRTPutL::PayOffRTPutL(ArgumentList& args)
{
    PayOffPut thePayOffPut(args);
    TreeAmerican TreeAmerPut(args.GetDoubleArgumentValue("Expiry"), thePayOffPut);
    ParametersConstant rParam(args.GetDoubleArgumentValue("r"));
    ParametersConstant dParam(args.GetDoubleArgumentValue("d"));
    RandomLowTree RLowTree(args.GetDoubleArgumentValue("Spot"),
                                 rParam,
                                 dParam,
                                 args.GetDoubleArgumentValue("Vol"),
                                 args.GetDoubleArgumentValue("Steps"),
                                 args.GetDoubleArgumentValue("Expiry"),
                                 args.GetDoubleArgumentValue("b"));
    RTPutLPrice = 0;
    for (int i = 0; i < args.GetDoubleArgumentValue("n"); i++){
        RTPutLPrice += RLowTree.GetThePrice(TreeAmerPut);
    }
    RTPutLPrice = RTPutLPrice/args.GetDoubleArgumentValue("n");
}

double PayOffRTPutL::operator()(double Spot) const
{
    return RTPutLPrice;
}

PayOff* PayOffRTPutL::clone() const
{
    return new PayOffRTPutL(* this);
}
