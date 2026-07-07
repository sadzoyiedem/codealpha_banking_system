#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <vector>
#include "main.h"

using namespace std;

// Helper functions
void welcome_menu();
void divider();
void clear_screen();
bool input_validation(int min, int max, int &user_opt);
bool validate_trans_amount(float amount);
void account_menu();

// Program Functionalities
string account_creation(vector<Customer> &database, AuthManager &auth);
string user_logging(vector<Customer> &database, AuthManager &auth);
void dashboard_loop(Customer &active_customer, vector<Customer> &database);

#endif