#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include "main.h"

using namespace std;

// Helper functions
bool validate_trans_amount(float amount);
void account_menu();

// Program Functionalities
string account_creation(vector<Customer> &database, AuthManager &auth);
string user_logging(vector<Customer> &database, AuthManager &auth);
void dashboard_loop(Customer &active_customer, vector<Customer> &database);

#endif