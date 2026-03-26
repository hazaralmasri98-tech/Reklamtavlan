#pragma once
#include "models.h"

void initCustomers();
const Customer* pickNextCustomer();
const Message* pickMessage(const Customer* c);