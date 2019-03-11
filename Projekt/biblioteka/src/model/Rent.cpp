#include <model/Rent.h>
#include <boost/date_time/local_time/local_date_time.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>

Rent::Rent(ClientPtr Client, VehiclePtr Vehicle, local_date_time Start)
	: Client(Client), StartDate(Start), EndDate(Start), Vehicle(Vehicle)
	{
		boost::uuids::random_generator gen;
		ID = gen();
    	RentCost = 0.0;
    	
    	if(Vehicle->IsVehicleAvailable())
	    	Vehicle->ChangeAvailiablity();
		else
			throw RentExeption("0 - Niedostepny pojazd!\n");

		if(Client->GetMaxVeh()+1 > Client->GetRents().size()+1)
			Client->GiveRent(this);
		else
			throw RentExeption("1 - Klient osiagnal maksymalna liczbe pojazdow do wypozyczenia!\n");

	}

Rent::~Rent() { }

int Rent::RentDuration()
{
	local_time_period period = local_time_period(StartDate, EndDate);
	int s = period.length().total_seconds();
	int d = (s + 60 * 60 * 24 - 1) / 60 / 60 / 24;

	return d;
}

void Rent::ReturnVehicle()
{
	time_zone_ptr zone(new posix_time_zone("GMT"));
	local_date_time ldt = local_sec_clock::local_time(zone);

	this->EndDate = ldt;

	RentCost = RentDuration() * Vehicle->GetAccualPrice() * Client->GetDiscount();
	//this->Client->GiveRent(nullptr);
	this->Client->EraseRent(this);
	this->Vehicle->ChangeAvailiablity();
}

std::string Rent::RentInfo(bool FromClient)
{
    string Info;
	Info.append("UUID: ").append(boost::lexical_cast<std::string>(ID))
		.append("\nStart: ").append(boost::lexical_cast<std::string>(StartDate))
		.append("\nCost: ").append(std::to_string(RentCost)).append(" gelda")
		.append("\nEnd: ").append(boost::lexical_cast<std::string>(EndDate));

	if(!FromClient)
		Info.append("\n- Client: \n").append(Client->ClientInfo(false));

    if(FromClient)
        Info.append("\n");
	Info.append("- Vehicle: \n").append(Vehicle->VehicleInfo());

	return Info;
}

VehiclePtr Rent::GetVehicle() { return Vehicle; }
ClientPtr Rent::GetClient() {	return Client; }

double Rent::GetRentCost() { return RentCost; }
//boost::uuids::uuid Rent::GetID() { return ID; }


