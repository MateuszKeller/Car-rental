#include <boost/test/unit_test.hpp>
#include "boost/date_time/gregorian/gregorian.hpp"
#include "model/Managers.h"

#include <iostream>
using namespace std;

BOOST_AUTO_TEST_SUITE(RentSuiteCorrect)

    BOOST_AUTO_TEST_CASE(BasicsRMTestCase) {
        RentsManager MR;
        BOOST_REQUIRE_EQUAL(MR.GetRepo('C').GetAll().size(), 0);
        BOOST_REQUIRE_EQUAL(MR.GetRepo('A').GetAll().size(), 0);
        BOOST_REQUIRE_EQUAL(MR.RentReport('C'), "Current Rents:\n");
        BOOST_REQUIRE_EQUAL(MR.RentReport('A'), "Archive Rents:\n"); //- Manager tworzony z pustym Repo ?

        time_zone_ptr Zone(new posix_time_zone("GMT"));
        local_date_time Ldt = local_sec_clock::local_time(Zone) - boost::gregorian::days(10);
        ClientPtr C(new Client("Jan","Niezbedny","00000000001"));
        Address *AA= new Address("Sezamkowa", "12"); C->GiveRegAddress(AA);
        Address *RA= new Address("Ciasteczkowa", "18"); C->GiveAddress(RA);
        VehiclePtr V1(new Car("Bum-bum 46", 100, 1200, A));
        VehiclePtr V2(new Bicycle("Rowor 1", 20));

        MR.CreateRent(C, V1, Ldt);
        BOOST_REQUIRE_EQUAL(MR.GetRepo('C').GetAll().size(), 1);// dziala dodawanie ?


        MR.CreateRent(C, V2, Ldt);
        BOOST_REQUIRE_EQUAL(MR.GetRepo('C').GetAll().size(), 2);
        RentPtr Seeker = *next(MR.GetRepo('C').GetAll().begin(), 1);
        MR.RemoveRent(Seeker);
        BOOST_REQUIRE_EQUAL(MR.GetRepo('C').GetAll().size(), 1); // - dziala usuwanie ?

        //cout << C->ClientInfo(true);
        //cout << MR.RentReport('C');
        delete RA, AA;
    }

    BOOST_AUTO_TEST_CASE(AdvancedRMTestCase) {
        RentsManager MR;
        time_zone_ptr Zone(new posix_time_zone("GMT"));
        local_date_time Ldt = local_sec_clock::local_time(Zone) - boost::gregorian::days(10);
        ClientPtr C(new Client("Jan","Niezbedny","00000000001"));
        Address *AA= new Address("Sezamkowa", "12"); C->GiveRegAddress(AA);
        Address *RA= new Address("Ciasteczkowa", "18"); C->GiveAddress(RA);
        VehiclePtr V1(new Car("Bum-bum 46", 100, 1200, A));
        MR.CreateRent(C, V1, Ldt);

        BOOST_REQUIRE_EQUAL(C->GetRents().size(), 1); // czy klient widzi swoje wypozyczenia ?
        BOOST_REQUIRE_EQUAL(V1->IsVehicleAvailable(), false); // czy pojazd staje sie niedostepny ?
        BOOST_REQUIRE_EQUAL(MR.GetClientForRentedVehicle(V1),C); // dziala wyciaganie klienta po pojezdzie ?
        MR.ReturnVehicle(V1);
        //cout << MR.RentReport('A');
                                                               //po oddaniu pojazdu
        BOOST_REQUIRE_EQUAL(C->GetRents().size(), 0); // czy wypozyczenie jest usuniete od klienta ?
        BOOST_REQUIRE_EQUAL(V1->IsVehicleAvailable(), true); // czy pojazd staje sie dostepny ?
        BOOST_REQUIRE_EQUAL(MR.GetRepo('C').GetAll().size(), 0);// czy wypozyczenie jest usuwane z wypozyczen obecnych ?
        BOOST_REQUIRE_EQUAL(MR.GetRepo('A').GetAll().size(), 1);// czy wypozyczenie jest dodawane do wypozyczen archiwalnych ?

        BOOST_REQUIRE_CLOSE(MR.CheckClientRentBallance(C), 14000, 0.000001);// czy bilans sie zgadza ?
        BOOST_REQUIRE_CLOSE(C->GetDiscount(), 0.87, 0.00001);// czy typ klienta sie zmienia ?
        delete RA, AA;
    }

    BOOST_AUTO_TEST_CASE(ExeptionsRMTestCase) {// Czy dzialaja wyjatki
        RentsManager MR;
        time_zone_ptr Zone(new posix_time_zone("GMT"));
        local_date_time Ldt = local_sec_clock::local_time(Zone) - boost::gregorian::days(10);
        ClientPtr C(new Client("Jan","Niezbedny","00000000001"));
        Address *AA= new Address("Sezamkowa", "12"); C->GiveRegAddress(AA);
        Address *RA= new Address("Ciasteczkowa", "18"); C->GiveAddress(RA);
        VehiclePtr V1(new Car("Bum-bum 46", 100, 1200, A));
        VehiclePtr V2(new Mobe("Sku...ter", 100, 1200));
        VehiclePtr V3(new Bicycle("Rowor 1", 20));
        MR.CreateRent(C, V1, Ldt);
        MR.CreateRent(C, V2, Ldt);

        //cout << "Wyjatki:\n";
        try
        {
            MR.CreateRent(C, V2, Ldt);
            BOOST_REQUIRE_THROW(MR.CreateRent(C, V2, Ldt), ClientExeption);
        }
        catch (RentExeption& RE )
        {
            //cout << RE.what();
            BOOST_REQUIRE_EQUAL(RE.what(), "0 - Niedostepny pojazd!\n");
        }
        try
        {
            MR.CreateRent(C, V3, Ldt);
            BOOST_REQUIRE_THROW(MR.CreateRent(C, V3, Ldt), ClientExeption);
        }
        catch (RentExeption& RE )
        {
            //cout << RE.what();
            BOOST_REQUIRE_EQUAL(RE.what(), "1 - Klient osiagnal maksymalna liczbe pojazdow do wypozyczenia!\n");
        }
        delete RA, AA;
    }
BOOST_AUTO_TEST_SUITE_END()