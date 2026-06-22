#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <vector>

#define DEBUG 0

using namespace std;

// Helper functions
void welcome_menu();
void divider();
void clear_screen();
bool input_validation(int min, int max, int &user_opt);
string generate_account_number();

class Account
{

private:
  string account_number;
  float balance;

public:
  Account(float bal) : account_number(generate_account_number()), balance(bal) {}

  float get_balance()
  {
    return balance;
  }
  string get_acc_num() { return account_number; }
};

// 2. Update Customer class to "own" Accounts
class Customer
{
private:
  string first_name;
  string last_name;
  string email;
  vector<Account> accounts; // <-- The Link! A customer "has" accounts.

public:
  Customer(string f_n, string l_n, string em) : first_name(f_n), last_name(l_n), email(em) {}

  // Function to attach an account to this customer
  void add_account(Account &new_account)
  {
    accounts.push_back(new_account);
  }

#if DEBUG
  void display_details()
  {
    cout << "FN: " << first_name
         << "\tLN: " << last_name
         << "\tEM: " << email
         << "\tAccounts Owned: " << accounts.size() << endl;
  }
#endif

  void display_accounts()
  {
    cout << "Account summary for " << first_name << " " << last_name << ": " << endl;

    if (accounts.empty())
    {
      cout << "No accounts found." << endl;
      return;
    }

    for (int i = 0; i < accounts.size(); i++)
    {
      cout << "Account " << i + 1
           << "\nAccount number: " << accounts[i].get_acc_num()
           << "\nBalance: GHC " << accounts[i].get_balance() << endl;
    }
  }
};

class Transaction
{
};

#endif
