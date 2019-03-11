/*
	Kompozycja - A posiada Obiekt B
			B jest niszczone przy niszczeniu A

	Agregacja - A posiada wskaznik do Obiektu B
			B NIE jest niszczone przy niszczeniu A
*/

#pragma once
#include <string>
#include <list>
#include <memory>

#include "Rent.h"
#include "ClientType.h"
#include "Exeptions.h"

class ClientType;
class Address;
class Rent;

typedef std::shared_ptr<Rent> RentPtr;

class Client
{
public:
	bool operator == (const Client &c)
	{
		return this->PersonalID == c.PersonalID;
	}

	Client(std::string FirstName, std::string LastName, std::string PersonalID);
	~Client();

	std::string ClientInfo(bool PrintRent = true);

	void GiveFName(std::string);
	void GiveLName(std::string);
	void GiveAddress(Address*);
	void GiveRegAddress(Address*);
	void GiveRent(Rent*);
	void EraseRent(Rent*);

    std::string GetPersonalID();
	std::list<RentPtr> GetRents();

	//ClientType
	void ChangeClientType(ClientType*);
	int GetMaxVeh();
	double GetDiscount();
private:
	std::string FirstName;
	std::string LastName;
	std::string PersonalID;
	
	// Agregacje:
	Address* RegisteredAddress;
	Address* Adress;

	std::list<RentPtr> Rents;

	ClientType* CType; // delegacja

};