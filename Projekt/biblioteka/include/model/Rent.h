#pragma once

#include <string>
#include <list>
#include <memory>
#include "model/Address.h"
#include "model/Client.h"
#include "model/Vehicle.h"

#include <boost/date_time/local_time/local_time.hpp>
#include <boost/uuid/random_generator.hpp>

using namespace boost::local_time;

class Client;
class Vehicle;

typedef std::shared_ptr<Client> ClientPtr;
typedef std::shared_ptr<Vehicle> VehiclePtr;

class Rent
{
public:
	bool operator == (const Rent &R)
	{
		return this->ID == R.ID;
	}

	Rent(ClientPtr Client, VehiclePtr Vehicle, local_date_time Start);
	~Rent();

	int RentDuration();
	void ReturnVehicle();
	std::string RentInfo(bool FromClient);

	double GetRentCost();
	VehiclePtr GetVehicle();
	ClientPtr GetClient();
	//boost::uuids::uuid GetID();
private:
	//Agregacje:
	ClientPtr Client;
	VehiclePtr Vehicle;

	double RentCost;
	boost::uuids::uuid ID;
	local_date_time StartDate;
	local_date_time EndDate;
};