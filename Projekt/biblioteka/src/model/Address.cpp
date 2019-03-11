#include "model/Address.h"

Address::Address(std::string Street, std::string Number)
        :Street(Street), Number(Number)
        { }
Address::~Address(){ }

std::string Address::GetNumber() { return this->Number; }
std::string Address::GetStreet(){ return this->Street; }
void Address::GiveNumber(std::string Number) { this->Number = Number; }
void Address::GiveStreet(std::string Street){ this->Street = Street; }

