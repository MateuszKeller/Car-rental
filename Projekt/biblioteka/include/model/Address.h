#pragma once
#include <string>

class Address // adres klienta
{
public:
    Address(std::string Street, std::string Number);
    Address();
    virtual ~Address();

    std::string GetStreet();
    std::string GetNumber();
    void GiveStreet(std::string);
    void GiveNumber(std::string);
private:

    std::string Street;
    std::string Number;
};