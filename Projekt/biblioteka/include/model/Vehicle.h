#pragma once
#include <string>

#include "Exeptions.h"

using namespace std;

enum segment { A = 10, B = 11, C = 12, D = 13, E = 14, F = 15};

class Vehicle
{
public:

    bool operator == (const Vehicle &V)
    {
        return this->Id == V.Id;
    }

    Vehicle(string Id, int BaseRentPrice);
    virtual ~Vehicle();

    virtual string VehicleInfo();
    bool IsVehicleAvailable();
    void ChangeAvailiablity();

    int GetBaseRentPrice();
    string GetId();
    int GetAccualPrice();

    void  GiveAccualPrice(int);

private:
    string Id;
    int BaseRentPrice;
    int AccualRentalPrice;
    bool Available;
};

class MotorVehicle: public Vehicle // dziedziczenie z Vehicle
{
public:
    MotorVehicle(string Id, int BaseRentPrice, int EngineDisplayment);
    virtual ~MotorVehicle();

    int GetEngineDisplayment();
    double GetChangeRatio();

private:
    int EngineDisplayment;
};

class Bicycle: public Vehicle
{
public:
    Bicycle(string Id, int BaseRentPrice);
    virtual ~Bicycle();

    string VehicleInfo();
};

class Car: public MotorVehicle
{
public:
    Car(string Id, int BaseRentPrice, int EngineDisplayment, segment Seg);
    virtual ~Car();

    string VehicleInfo();

private:
    segment Seg;
};

class Mobe: public  MotorVehicle
{
public:
    Mobe(string Id, int BaseRentPrice, int EngineDisplayment);
    virtual ~Mobe();

    string VehicleInfo();
};