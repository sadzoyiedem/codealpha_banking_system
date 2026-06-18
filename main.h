#ifndef MAIN_H
#define MAIN_H
#include <iostream>

#define DEBUG 1

using namespace std;

class Customer
{
private:
  string first_name;
  string last_name;
  string email;

public:
  Customer(string f_n, string l_n, string em) : first_name(f_n), last_name(l_n), email(em) {}
#if DEBUG
  void display_details()
  {
    cout << "FN: " << first_name
         << "\tLN: " << last_name
         << "\tEM: " << email << endl;
  }
#endif
};

class Account
{
private:
  int account_number;
  int balance;

public:
  Account() : account_number(0), balance(0) {}
};

class Transaction
{
};

// Helper functions
void divider();
void welcome_menu();
bool input_validation(int min, int max);

#endif
