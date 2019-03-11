//
// Created by pobi on 02.12.18.
//
#pragma once

#include "Repositories.h"
#include "Vehicle.h"
#include "Client.h"


using namespace std;

template < class T >
class TRepo;

typedef TRepo<ClientPtr> TClientRepo;
typedef TRepo<VehiclePtr> TVehicleRepo;
typedef TRepo<RentPtr> TRentRepo;

class RentsManager
{
public:
    RentsManager();
    virtual ~RentsManager();

    void CreateRent(ClientPtr C, VehiclePtr V, local_date_time ldt);
    void RemoveRent(RentPtr);

    ClientPtr GetClientForRentedVehicle(VehiclePtr);
    string RentReport(char NameRepo); // Current or Archive
    void ReturnVehicle(VehiclePtr);
    list<RentPtr> GetAllClientRents(ClientPtr);
    double CheckClientRentBallance(ClientPtr);
    void ChangeClientType(ClientPtr);

    TRentRepo GetRepo(char Repo);

private:
    TRentRepo CurrentRepo;
    TRentRepo ArchiveRepo;

};
///------------------------------------

class Vehicle;

class VehiclesManager
{
public:
    VehiclesManager();
    virtual ~VehiclesManager();
    //void CreateVehicle(VehiclePtr);
    void CreateVehicle(string, int);
    void CreateVehicle(string, int, int);
    void CreateVehicle(string, int, int, segment);
    void RemoveVehicle(VehiclePtr);
    string VehicleReport();

    bool IsSameId(string);

    TVehicleRepo GetRepo(){ return VehicleRepo; };

private:
    TVehicleRepo VehicleRepo;
};
///------------------------------------

class ClientsManager
{
public:
    ClientsManager();
    virtual ~ClientsManager();

    void CreateClient(string FirstName, string LastName, string PersonalID); // string bo przesylamy wyjatek
    void RemoveClient(ClientPtr);
    string ClientReport(bool PrintRents = true);
    void GiveClientAddres(char N, ClientPtr Client, std::string Street, std::string Number);

    TClientRepo GetRepo(){ return ClientRepo; };
    private:
    TClientRepo ClientRepo;
};

