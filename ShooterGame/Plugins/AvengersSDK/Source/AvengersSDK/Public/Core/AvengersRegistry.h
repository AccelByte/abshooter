// Copyright (c) 2019 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "AvengersSettings.h"

namespace AccelByte
{

class AVENGERSSDK_API FAvengersRegistry
{
public:
    static AvengersSettings Settings;

    //Static class doesn't have constructors or destructor
    FAvengersRegistry() = delete;
    FAvengersRegistry(const FAvengersRegistry& other) = delete;
    FAvengersRegistry& operator=(const FAvengersRegistry& other) = delete;
    FAvengersRegistry(FAvengersRegistry&& other) = delete;
    FAvengersRegistry& operator=(FAvengersRegistry&& other) = delete;
    ~FAvengersRegistry() = delete;
};
}