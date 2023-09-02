//
//  PayOff3.h
//  ch10_factory_pattern
//
//  Created by cheerzzh on 24/6/14.
//  Copyright (c) 2014年 Jared Zhou. All rights reserved.
//
#include "ArgList.h"
// #include "BinomialTree.h"
// #include "TreeAmerican.h"

#ifndef __ch10_factory_pattern__PayOff3__
#define __ch10_factory_pattern__PayOff3__
class PayOff
{
public:
    
    PayOff(){};
    
    virtual double operator()(double Spot) const=0;
    virtual ~PayOff(){}
    virtual PayOff* clone() const=0;
    
private:
};

class PayOffCall : public PayOff
{
public:
    
    PayOffCall(ArgumentList& args);
    
    virtual double operator()(double Spot) const;
    virtual ~PayOffCall(){}
    virtual PayOff* clone() const;
    
private:
    
    double Strike;
    
};


class PayOffPut : public PayOff
{
public:
    
    PayOffPut(ArgumentList& args);
    
    virtual double operator()(double Spot) const;
    virtual ~PayOffPut(){}
    virtual PayOff* clone() const;
    
private:
    
    double Strike;
    
};

class PayOffBNCall : public PayOff
{
public:
    
    PayOffBNCall(ArgumentList& args);
    
    virtual double operator()(double Spot) const;
    virtual ~PayOffBNCall(){}
    virtual PayOff* clone() const;
    
private:
    
    double BNCallPrice;
};

class PayOffBNPut : public PayOff
{
public:
    
    PayOffBNPut(ArgumentList& args);
    
    virtual double operator()(double Spot) const;
    virtual ~PayOffBNPut(){}
    virtual PayOff* clone() const;
    
private:
    
    double BNPutPrice;
};

class PayOffRTCallH : public PayOff
{
public:
    
    PayOffRTCallH(ArgumentList& args);
    
    virtual double operator()(double Spot) const;
    virtual ~PayOffRTCallH(){}
    virtual PayOff* clone() const;
    
private:
    
    double RTCallHPrice;
};

class PayOffRTCallL : public PayOff
{
public:
    
    PayOffRTCallL(ArgumentList& args);
    
    virtual double operator()(double Spot) const;
    virtual ~PayOffRTCallL(){}
    virtual PayOff* clone() const;
    
private:
    
    double RTCallLPrice;
};

class PayOffRTPutH : public PayOff
{
public:
    
    PayOffRTPutH(ArgumentList& args);
    
    virtual double operator()(double Spot) const;
    virtual ~PayOffRTPutH(){}
    virtual PayOff* clone() const;
    
private:
    
    double RTPutHPrice;
};

class PayOffRTPutL : public PayOff
{
public:
    
    PayOffRTPutL(ArgumentList& args);
    
    virtual double operator()(double Spot) const;
    virtual ~PayOffRTPutL(){}
    virtual PayOff* clone() const;
    
private:
    
    double RTPutLPrice;
};

#endif /* defined(__ch10_factory_pattern__PayOff3__) */
