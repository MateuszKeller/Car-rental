#include <model/Vehicle.h>

#include "model/Vehicle.h"
#include <iostream>

Vehicle::Vehicle(string Id, int BaseRentPrice)
        :Id(Id), BaseRentPrice(BaseRentPrice), Available(true)
        {
            if(BaseRentPrice<=0)
                throw VehicleExeption("1 - Nieprawidlowa cena!\n");
        }
Vehicle::~Vehicle() { }

string Vehicle::VehicleInfo()
{
    return Id.append(" cost ").append(to_string(BaseRentPrice)).append("\n");
}

int Vehicle::GetBaseRentPrice() { return BaseRentPrice; }
string Vehicle::GetId() { return Id; }
bool Vehicle::IsVehicleAvailable() { return Available; }
void Vehicle::ChangeAvailiablity()
{
    if(Available)
        Available= false;
    else
        Available= true;
}
int Vehicle::GetAccualPrice() { return AccualRentalPrice; }
void Vehicle::GiveAccualPrice(int Price) { AccualRentalPrice = Price; }

/// ////////// MOTORVEHICLE ////////// ///
MotorVehicle::MotorVehicle(string Id, int BaseRentPrice, int EngineDisplayment)
        :EngineDisplayment(EngineDisplayment), Vehicle(Id, BaseRentPrice) { }
MotorVehicle::~MotorVehicle() { }

int MotorVehicle::GetEngineDisplayment() { return EngineDisplayment; }
double MotorVehicle::GetChangeRatio()
{
    int x = GetEngineDisplayment();
    if(x<1000)
        return 1.0;
    else if(x<2000)
	{
        double w = x-1000;
        w /= 500;
        w += 1;
        return w;
    } else
        return 1.5;
}

/// ////////// BICYCLE ////////// ///
Bicycle::Bicycle(string Id, int BaseRentPrice)
        : Vehicle(Id, BaseRentPrice)
        {
            GiveAccualPrice(BaseRentPrice);
        }
Bicycle::~Bicycle() { }

string Bicycle::VehicleInfo()
{
    string Info = "Rower: ";
    return Info.append(GetId()).append(" cost ").append(to_string(GetAccualPrice())).append("\n");
}

/// ////////// CAR ////////// ///
Car::Car(string Id, int BaseRentPrice, int EngineDisplayment, segment Seg)
        : Seg(Seg), MotorVehicle(Id, BaseRentPrice, EngineDisplayment)
        {
            GiveAccualPrice(BaseRentPrice* GetChangeRatio()* Seg);
            //cout <<"cena: "<< AccualRentalPrice<<endl;
        }
Car::~Car() { }

string Car::VehicleInfo()
{
    //cout << "Vehicle Info\n";
    string Info = "Samochod: ";
    Info.append(GetId()).append(" cost ").append(to_string(GetAccualPrice())).append("\n");
    return Info;
}

/// ////////// MOBE ////////// ///
Mobe::Mobe(string Id, int BaseRentPrice, int EngineDisplayment)
        : MotorVehicle(Id, BaseRentPrice, EngineDisplayment)
        {
            GiveAccualPrice(BaseRentPrice* GetChangeRatio());
        }
Mobe::~Mobe() { }

//int Mobe::GetAccualRentialPrice() { return AccualRentalPrice; }
string Mobe::VehicleInfo()
{
    string Info = "Skuter: ";
    return Info.append(GetId()).append(" cost ").append(to_string(GetAccualPrice())).append("\n");
}
