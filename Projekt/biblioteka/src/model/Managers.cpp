//
// Created by pobi on 02.12.18.
//

#include <model/Managers.h>

class ClientType;

////////////RENTS///////////
RentsManager::RentsManager() { }
RentsManager::~RentsManager() { }

void RentsManager::CreateRent(ClientPtr C, VehiclePtr V, local_date_time ldt)
{
    CurrentRepo.Create(make_shared<Rent>(C,V,ldt));
}
void RentsManager::RemoveRent(RentPtr Rent)
{
    Rent->ReturnVehicle();
    CurrentRepo.Remove(CurrentRepo.Find(Rent));
}
ClientPtr RentsManager::GetClientForRentedVehicle(VehiclePtr Vehicle)
{
    for(auto Rent:CurrentRepo.GetAll())
        if(Rent->GetVehicle() == Vehicle)
            return Rent->GetClient();//->ClientInfo(true);
}

string RentsManager::RentReport(char NameRepo)
{
    string Ret = ""; int i = 1;

    switch (NameRepo) {
        case 'C':
            Ret = "Current Rents:\n";
            for (auto rent:CurrentRepo.GetAll()) {
                Ret.append(to_string(i)).append(". ").append(rent->RentInfo(false)).append(" --- \n");
                i++;
            }
            break;
        case 'A':
            Ret = "Archive Rents:\n";
            for (auto rent:ArchiveRepo.GetAll()) {
                Ret.append(to_string(i)).append(" ").append(rent->RentInfo(false)).append(" --- \n");
                i++;
            }
            break;
        default:
            Ret.append("Wybrano nieprawidlowe repozytorium->\n");
            break;
    }

    return Ret;
}
void RentsManager::ReturnVehicle(VehiclePtr V)
{
    ClientPtr C = GetClientForRentedVehicle(V);
    for(auto rent:CurrentRepo.GetAll())
    {
        if(*rent->GetVehicle()== *V)
        {
            rent->ReturnVehicle();

            ArchiveRepo.Create(rent);
            CurrentRepo.Remove(CurrentRepo.Find(rent));
        }

    }
    ChangeClientType(C);
    return;
}
list<RentPtr> RentsManager::GetAllClientRents(ClientPtr C)
{
    list<RentPtr> Ret;
    for(auto rent:ArchiveRepo.GetAll())
    {
        if(C==rent->GetClient())
            Ret.push_back(rent);
    }
    return Ret;
}

double RentsManager::CheckClientRentBallance(ClientPtr C)
{
    double Ret = 0;
    for(auto rent:GetAllClientRents(C))
        Ret += rent->GetRentCost();

    return Ret;
}
void RentsManager::ChangeClientType(ClientPtr C)
{
    if(CheckClientRentBallance(C) > 30000)
        C->ChangeClientType(new BusinessClient());
    else if(CheckClientRentBallance(C) > 7000)
        C->ChangeClientType(new LoyalClient());
    else if(CheckClientRentBallance(C) > 1000)
        C->ChangeClientType(new NewbieClient());

    return;
}

TRentRepo RentsManager::GetRepo(char Repo)
{
    switch (Repo)
    {
        case 'C':
            return CurrentRepo;
            break;
        case 'A':
            return ArchiveRepo;
            break;
    }
}

/// ------------------------------------------------------ ///
///////////VEHICLE///////////
/// ------------------------------------------------------ ///
VehiclesManager::VehiclesManager(){ }
VehiclesManager::~VehiclesManager() { }

void VehiclesManager::CreateVehicle(string Id, int BaseRentPrice)
{
    if(!IsSameId(Id))
        VehicleRepo.Create(make_shared<Bicycle>(Id, BaseRentPrice));
    return;
}
void VehiclesManager::CreateVehicle(string Id, int BaseRentPrice, int EngineDisplayment)
{
    if(!IsSameId(Id))
        VehicleRepo.Create(make_shared<Mobe>(Id, BaseRentPrice, EngineDisplayment));
    return;
}
void VehiclesManager::CreateVehicle(string Id, int BaseRentPrice, int EngineDisplayment, segment Seg)
{
    if(!IsSameId(Id))
        VehicleRepo.Create(make_shared<Car>(Id, BaseRentPrice, EngineDisplayment, Seg));
    return;
}
void VehiclesManager::RemoveVehicle(VehiclePtr Vehicle)
{
    VehicleRepo.Remove(VehicleRepo.Find(Vehicle));
}
string VehiclesManager::VehicleReport()
{
    std::string Ret = "Vehicles:\n"; int i = 1;
    for(auto Vehicle:VehicleRepo.GetAll())
    {
        Ret.append(to_string(i)).append(". ").append(Vehicle->VehicleInfo());
        i++;
    }
    return Ret;
}

bool VehiclesManager::IsSameId(string ID)
{
    for(auto vehicle:VehicleRepo.GetAll())
        if(ID==vehicle->GetId())
            throw VehicleExeption("0 - Nieprawidlowy id!\n");

    return false;
}


/// ------------------------------------------------------ ///
///////////CLIENT////////////
/// ------------------------------------------------------ ///

ClientsManager::ClientsManager() { }
ClientsManager::~ClientsManager() { }

void ClientsManager::CreateClient(string FirstName, string LastName, string PersonalID)
{
    for(auto client:ClientRepo.GetAll())
          if(PersonalID==client->GetPersonalID())
            throw ClientExeption("0 - Nieprawidlowy pesel!\n");

    ClientRepo.Create(make_shared<Client>(FirstName, LastName, PersonalID));
    return;
}
void ClientsManager::RemoveClient(ClientPtr Client)
{
    ClientRepo.Remove(ClientRepo.Find(Client));
}
string ClientsManager::ClientReport(bool PrintRents){
    std::string Ret = "Clients:\n"; int i = 1;
    for(auto Client:ClientRepo.GetAll())
    {
        Ret.append(to_string(i)).append(". ").append(Client->ClientInfo(PrintRents));
        i++;
    }
    return Ret;
}

void ClientsManager::GiveClientAddres(char N, ClientPtr Client, std::string Street, std::string Number)
{
    switch (N)
    {
        case 'R':
            ClientRepo.Find(Client)->GiveRegAddress(new Address(Street, Number));
        break;
        case 'A':
            ClientRepo.Find(Client)->GiveAddress(new Address(Street, Number));
        break;
    }

}