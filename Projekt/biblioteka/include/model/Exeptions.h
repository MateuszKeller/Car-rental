#pragma once

#include <stdexcept>
#include <string>

class ClientExeption: public std::logic_error
{
public:
    ClientExeption(const std::string &arg): logic_error(arg) {};
    virtual ~ClientExeption();

private:

};

class VehicleExeption: public std::logic_error
{
public:
    VehicleExeption(const std::string &arg): logic_error(arg) {};
    virtual ~VehicleExeption();

private:
};

class RentExeption: public std::logic_error
{
public:
    RentExeption(const std::string &arg): logic_error(arg) {};
    virtual ~RentExeption();

private:
};
