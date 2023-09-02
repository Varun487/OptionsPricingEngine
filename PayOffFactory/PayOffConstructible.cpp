//
//  PayOffConstructible.cpp
//  ch10_factory_pattern
//
//  Created by cheerzzh on 24/6/14.
//  Copyright (c) 2014年 Jared Zhou. All rights reserved.
//

#include "PayOffConstructible.h"

namespace {
    // Register all required payoffs
    PayOffHelper<PayOffBNCall> RegisterBNCall("BNCall");
    PayOffHelper<PayOffBNPut> RegisterBNPut("BNPut");
    PayOffHelper<PayOffRTCallH> RegisterRTCallH("RTCallH");
    PayOffHelper<PayOffRTCallL> RegisterRTCallL("RTCallL");
    PayOffHelper<PayOffRTPutH> RegisterRTPutH("RTPutH");
    PayOffHelper<PayOffRTPutL> RegisterRTPutL("RTPutL");
}
