//
//  PayOffConstructible.h
//  ch10_factory_pattern
//
//  Created by cheerzzh on 24/6/14.
//  Copyright (c) 2014年 Jared Zhou. All rights reserved.
//

#ifndef __ch10_factory_pattern__PayOffConstructible__
#define __ch10_factory_pattern__PayOffConstructible__

#if defined(_MSC_VER)
#pragma warning( disable : 4786)
#endif

#include <iostream>
#include "ArgList.h"
#include "PayOff3.h"
#include "PayOffFactory.h"
#include "BinomialTree.h"
#include <string>
#include <vector>

template <class T>
class PayOffHelper
{
public:
    PayOffHelper(std::string);
    static PayOff* Create(ArgumentList& args);
};

template <class T>
PayOff* PayOffHelper<T>::Create(ArgumentList& args)
{
    return new T(args);
}

template <class T>
PayOffHelper<T>::PayOffHelper(std::string id)
{
    PayOffFactory& thePayOffFactory = PayOffFactory::Instance();
    thePayOffFactory.RegisterPayOff(id,PayOffHelper<T>::Create);
}


#endif /* defined(__ch10_factory_pattern__PayOffConstructible__) */
