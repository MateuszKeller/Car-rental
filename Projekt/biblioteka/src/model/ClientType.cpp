//
// Created by pobi on 02.12.18.
//

#include <model/ClientType.h>

#include "model/ClientType.h"

ClientType::~ClientType() {}
/// ////////// NEWBIE ////////// ///
int DefaultClient::GiveMaxVehicles() { return 2; }
double DefaultClient::GiveDiscount() { return 1.0; }

/// ////////// NEWBIE ////////// ///
int NewbieClient::GiveMaxVehicles() { return 3; }
double NewbieClient::GiveDiscount() { return 0.95; }

/// ////////// LOYAL ////////// ///
int LoyalClient::GiveMaxVehicles() { return 5; }
double LoyalClient::GiveDiscount() { return 0.87; }

/// ////////// BUSINESS ////////// ///
int BusinessClient::GiveMaxVehicles() { return 10; }
double BusinessClient::GiveDiscount() { return 0.7; }



