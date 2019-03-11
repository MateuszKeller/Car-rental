//
// Created by pobi on 02.12.18.
//

#pragma once

class ClientType
{
public:
    virtual int GiveMaxVehicles() = 0;
    virtual double GiveDiscount() = 0;
    virtual ~ClientType();
};
/// ----------------------------------------

class DefaultClient: public ClientType
{
public:
    int GiveMaxVehicles() final;
    double GiveDiscount() final;
};
/// ----------------------------------------

class NewbieClient: public ClientType
{
public:
    int GiveMaxVehicles() final;
    double GiveDiscount() final;
};

/// ----------------------------------------

class LoyalClient: public ClientType
{
public:
    int GiveMaxVehicles() final;
    double GiveDiscount() final;
};
/// ----------------------------------------

class BusinessClient: public ClientType
{
public:
    int GiveMaxVehicles() final;
    double GiveDiscount() final;
};

