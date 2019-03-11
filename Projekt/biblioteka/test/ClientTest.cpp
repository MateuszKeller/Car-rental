#include <iostream>
#include <boost/test/unit_test.hpp>
#include "boost/date_time/gregorian/gregorian.hpp"

#include "model/Managers.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(CMSuiteCorrect)

    BOOST_AUTO_TEST_CASE(BasicsCMTestCase) {

        ClientsManager MC;
        BOOST_REQUIRE_EQUAL(MC.GetRepo().GetAll().size(), 0);
        BOOST_REQUIRE_EQUAL(MC.ClientReport(), "Clients:\n"); //- Manager tworzony z pustym Repo ?

        MC.CreateClient("Jan","Niezbedny","00000000001");
        BOOST_REQUIRE_EQUAL(MC.GetRepo().GetAll().size(), 1);// dziala dodawanie ?

        MC.CreateClient("Janina","Niezbedna","00000000002");
        MC.CreateClient("Janina","Niezbedna","00000000003");
        BOOST_REQUIRE_EQUAL(MC.GetRepo().GetAll().size(), 3);// dziala dodawanie takich samych imion i nazwisk ?

        ClientPtr Seeker = make_shared<Client>("Janina","Niezbedna","00000000003");
        MC.RemoveClient(Seeker);
        BOOST_REQUIRE_EQUAL(MC.GetRepo().GetAll().size(), 2);// dziala usuwanie ?

        BOOST_REQUIRE_EQUAL(MC.ClientReport(), "Clients:\n1.  Jan Niezbedny 00000000001\n2.  Janina Niezbedna 00000000002\n");// poprawne dane ?
        //cout << "Basics:\n" << MC.ClientReport();
    }

    BOOST_AUTO_TEST_CASE(AdvancedCMTestCase) {

        ClientsManager MC;

        Address Addres ("Sezamkowa", "12");
        BOOST_REQUIRE_EQUAL(Addres.GetStreet(), "Sezamkowa");
        BOOST_REQUIRE_EQUAL(Addres.GetNumber(), "12"); // - dziala tworzenie adresu ?

        Address *RA= new Address("Sezamkowa", "12");
        RA->GiveStreet("Ciasteczkowa");
        RA->GiveNumber("18");
        BOOST_REQUIRE_EQUAL(RA->GetStreet(), "Ciasteczkowa");
        BOOST_REQUIRE_EQUAL(RA->GetNumber(), "18"); // - dziala zmiana adresu ?

        MC.CreateClient("Jan","Niezbedny","00000000001");
        ClientPtr Seeker = make_shared<Client>("Jan","Niezbedny","00000000001");
        MC.GetRepo().Find(Seeker)->GiveFName("Janusz");
        MC.GetRepo().Find(Seeker)->GiveLName("Zbedny");
        //MC.GetRepo().Find(Seeker)->GiveAddress(A);
        MC.GiveClientAddres('A', Seeker, "Sezamkowa", "12");
        MC.GetRepo().Find(Seeker)->GiveRegAddress(RA);
        BOOST_REQUIRE_EQUAL(MC.ClientReport(), "Clients:\n1.  Janusz Zbedny 00000000001\nReg addr: Ciasteczkowa 18\nAddr: Sezamkowa 12\n");// dziala zmiana/dodawanie danych ?

        BOOST_REQUIRE_EQUAL(MC.GetRepo().Find(Seeker)->GetMaxVeh(), 2);
        BOOST_REQUIRE_CLOSE(MC.GetRepo().Find(Seeker)->GetDiscount(), 1, 0.00001);
        MC.GetRepo().Find(Seeker)->ChangeClientType(new BusinessClient());
        BOOST_REQUIRE_EQUAL(MC.GetRepo().Find(Seeker)->GetMaxVeh(), 10);
        BOOST_REQUIRE_CLOSE(MC.GetRepo().Find(Seeker)->GetDiscount(), 0.7, 0.00001);//- dziala zmiana typu klienta
        //cout << "Advanced:\n" << MC.ClientReport() << endl;
        delete RA, A;
    }

    BOOST_AUTO_TEST_CASE(ExeptionsCMTestCase) {// Czy dzialaja wyjatki

        ClientsManager MC;
        MC.CreateClient("Jan","Niezbedny","00000000001");
        //cout << "Wyjatki:\n";
        try
        {
            MC.CreateClient("Jan","Niezbedny","00000000001");
            BOOST_REQUIRE_THROW(MC.CreateClient("Jan","Niezbedny","00000000001"), ClientExeption);
        }
        catch (ClientExeption& CE )
        {
            //cout << CE.what();
            BOOST_REQUIRE_EQUAL(CE.what(), "0 - Nieprawidlowy pesel!\n");
        }
        catch (logic_error)
        { /*cout << "logic error";*/ }
        try
        {
            MC.CreateClient("x","XX","00000000009");
            BOOST_REQUIRE_THROW(MC.CreateClient("x","XX","00000000009"), ClientExeption);
        }
        catch (ClientExeption& CE )
        {
            //cout << CE.what();
            BOOST_REQUIRE_EQUAL(CE.what(), "1 - Zakrotkie imie lub nazwisko!\n");
        }
        try
        {
            MC.CreateClient("Jan","Niezbedny","0000000000+");
            BOOST_REQUIRE_THROW(MC.CreateClient("Jan","Niezbedny","0000000000+"), ClientExeption);
        }
        catch (ClientExeption& CE )
        {
            //cout << CE.what();
            BOOST_REQUIRE_EQUAL(CE.what(), "2 - Zly format peselu!\n");
        }
    }

BOOST_AUTO_TEST_SUITE_END()

//        SeekClientById seek("00000000002");