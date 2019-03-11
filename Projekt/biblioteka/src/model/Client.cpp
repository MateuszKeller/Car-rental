#include <iostream>
#include <regex>

#include "model/Address.h"
#include <model/Client.h>
#include <model/Rent.h>
#include <model/Repositories.h>

using namespace std;

Client::Client(string FirstName, string LastName, string PersonalID)
        :FirstName(FirstName), LastName(LastName), PersonalID(PersonalID) // lista inicjalizacyjna
        {
            if(FirstName.length() < 2 || LastName.length() < 3)
                throw ClientExeption("1 - Zakrotkie imie lub nazwisko!\n");

            regex pattern("\\d{11}");
            if(!regex_match(PersonalID, pattern))
                throw ClientExeption("2 - Zly format peselu!\n");

            this->Adress = nullptr;
            this->RegisteredAddress = nullptr;
	        CType = new DefaultClient();
        }

Client::~Client() { delete  CType; }

string Client::ClientInfo(bool printRent)
{
    string Info = " ";
    Info.append(FirstName).append(" ")
        .append(LastName).append(" ")
        .append(PersonalID).append("\n");
    
    if (RegisteredAddress != nullptr)
    {
        Info.append("Reg addr: ").append(RegisteredAddress->GetStreet())
            .append(" ").append(RegisteredAddress->GetNumber()).append("\n");
    }

    if (Adress != nullptr)
    {
        Info.append("Addr: ").append( Adress->GetStreet())
            .append(" ").append(Adress->GetNumber()).append("\n");
    }

    if(!Rents.empty() && printRent)
    {

        int i = 1;  Info.append(" Rents:\n");
        for(auto rent:Rents)
        {
            Info.append(to_string(i)).append(". ")
                .append(rent->RentInfo(true)).append(" --- \n");
            i++;
        }
    }

    return Info;
}

void Client::GiveFName(string FirstName) { this->FirstName = FirstName; }
void Client::GiveLName(string LastName) { this->LastName = LastName; }
void Client::GiveAddress(Address* Adress) { this->Adress = Adress; }
void Client::GiveRegAddress(Address* Adress) { this->RegisteredAddress = Adress; }
void Client::GiveRent(Rent* R) { this->Rents.push_back(make_shared<Rent>(*R)); }
void Client::EraseRent(Rent* R)
{
    list<RentPtr>::iterator it = Rents.begin();
    for(auto E:Rents)
    {
        if (*R == *E)
        {
            E.reset();
            break;
        }
        advance (it,1);
    }
    this->Rents.erase(it);

}
list<RentPtr> Client::GetRents() { return Rents; }
string Client::GetPersonalID() { return PersonalID; }

// CType
void Client::ChangeClientType(ClientType* Type) { CType = Type; }
int Client::GetMaxVeh() { return CType->GiveMaxVehicles(); }
double Client::GetDiscount() { return CType->GiveDiscount(); }


