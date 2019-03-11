#include <iostream>
#include <boost/test/unit_test.hpp>
#include "boost/date_time/gregorian/gregorian.hpp"

#include "model/Managers.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(VMSuiteCorrect)

    BOOST_AUTO_TEST_CASE(BasicsVMTestCase)
    {
        VehiclesManager MV;
        BOOST_REQUIRE_EQUAL(MV.GetRepo().GetAll().size(), 0);
        BOOST_REQUIRE_EQUAL(MV.VehicleReport(), "Vehicles:\n"); //- Manager tworzony z pustym Repo ?

        MV.CreateVehicle("Rower 1", 10);
        BOOST_REQUIRE_EQUAL(MV.GetRepo().GetAll().size(), 1);// dziala dodawanie ?

        MV.CreateVehicle("Skuter 1", 20, 700);
        MV.CreateVehicle("Skuter 2", 25, 1258);
        MV.CreateVehicle("Samochod 1", 100, 1900, A);

        VehiclePtr Seeker = make_shared<Mobe>("Skuter 2", 25, 1258);
        MV.RemoveVehicle(Seeker);
        BOOST_REQUIRE_EQUAL(MV.GetRepo().GetAll().size(), 3);// dziala usuwanie ?

        BOOST_REQUIRE_EQUAL(MV.VehicleReport(), "Vehicles:\n1. Rower: Rower 1 cost 10\n2. Skuter: Skuter 1 cost 20\n3. Samochod: Samochod 1 cost 2800\n");// poprawne dane ?
        //cout << MV.VehicleReport() << endl;
    }

    BOOST_AUTO_TEST_CASE(AdvancedVMTestCase)
    {
        VehiclesManager MV;
        MV.CreateVehicle("Samochod 1", 100, 1900, A);
        VehiclePtr Seeker = make_shared<Car>("Samochod 1", 100, 1900, A);
        BOOST_REQUIRE_EQUAL(MV.GetRepo().Find(Seeker)->GetBaseRentPrice(), 100);
        BOOST_REQUIRE_EQUAL(MV.GetRepo().Find(Seeker)->GetId(), "Samochod 1"); // pobieranie danych ?

        BOOST_REQUIRE_EQUAL(MV.GetRepo().Find(Seeker)->GetAccualPrice(), 2800);
        MV.GetRepo().Find(Seeker)->GiveAccualPrice(1500);
        BOOST_REQUIRE_EQUAL(MV.GetRepo().Find(Seeker)->GetAccualPrice(), 1500); // zmiana ceny?

        BOOST_REQUIRE_EQUAL(MV.GetRepo().Find(Seeker)->IsVehicleAvailable(), true);
        MV.GetRepo().Find(Seeker)->ChangeAvailiablity();
        BOOST_REQUIRE_EQUAL(MV.GetRepo().Find(Seeker)->IsVehicleAvailable(), false); // zmiana dostepnosci ?

        //cout << MV.VehicleReport() << endl;
    }

    BOOST_AUTO_TEST_CASE(ExeptionsVMTestCase)
    {
        VehiclesManager MV;
        MV.CreateVehicle("Samochod 1", 100, 1900, A);
        try
        {
            MV.CreateVehicle("Samochod 1", 100, 1900, A);
            BOOST_REQUIRE_THROW(MV.CreateVehicle("Samochod 1", 100, 1900, A), VehicleExeption);
        }
        catch (VehicleExeption& VE )
        {
            //cout << VE.what();
            BOOST_REQUIRE_EQUAL(VE.what(), "0 - Nieprawidlowy id!\n");
        }
        try
        {
            MV.CreateVehicle("Samochod 2", -100, 1900, D);
            BOOST_REQUIRE_THROW(MV.CreateVehicle("Samochod 1", -100, 1900, A), VehicleExeption);
        }
        catch (VehicleExeption& VE )
        {
            //cout << VE.what();
            BOOST_REQUIRE_EQUAL(VE.what(), "1 - Nieprawidlowa cena!\n");
        }
    }

BOOST_AUTO_TEST_SUITE_END()
