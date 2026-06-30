#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>

using namespace std;

// Helper functions
void welcome_menu();
void divider();
void clear_screen();
bool input_validation(int min, int max, int &user_opt);
bool validate_trans_amount(float amount);

// Program Functionalities
void account_creation(vector<Customer> &database);

#endif