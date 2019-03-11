#pragma once

#include <string>
#include "Rent.h"

class Seeker {
public:
    bool operator() ();
};

class SeekClientById//: public Seeker
{
public:
    SeekClientById(std::string Id);
    bool operator() (ClientPtr &C){ return C->GetPersonalID() ==  Id; };

private:
    std::string Id;
};
