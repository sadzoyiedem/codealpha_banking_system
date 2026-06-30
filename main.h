#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <vector>
#include <fstream>
#include <random>

#define DEBUG 0

using namespace std;

// Helper functions
void welcome_menu();
void divider();
void clear_screen();
bool input_validation(int min, int max, int &user_opt);

class Transaction
{
private:
  string transaction_id;
  string date;
  float amount;

  static string generate_trans_id()
  {
    // 1. The Seed: Pulls true random data from hardware
    std::random_device rd;

    // 2. The Engine: Does the heavy math to pick a number
    std::mt19937 engine(rd());

    // 3. The Distribution: Forces the number to be between 1000 and 9999
    std::uniform_int_distribution<int> dist(1000, 9999);

    // Generate the number, turn it into a string, and add "TXN-"
    return "TXN-" + std::to_string(dist(engine));
  }

public:
  Transaction(string d, float amt) : transaction_id(generate_trans_id()), date(d), amount(amt) {}

  // getters
  string get_trans_id() { return transaction_id; }
  float get_amount() { return amount; }
};
class Account
{

private:
  string account_number;
  float balance;
  vector<Transaction> transactions; // store transactions data

  static string generate_account_number()
  {
    random_device rd;

    mt19937_64 engine(rd());

    uniform_int_distribution<long long> rules(1000000000LL, 9999999999LL);

    long long raw_number = rules(engine);

    return to_string(raw_number);
  }

public:
  Account(float bal) : account_number(generate_account_number()), balance(bal) {}

  // Getters
  float get_balance() { return balance; }
  string get_acc_num() { return account_number; }

  void deposit(float amount)
  {
    balance += amount;
    cout << "Amount deposit successful." << endl;
  }

  void withdraw(float amount); // defined in main.cpp

  // recording transactions of acccount
  void add_transaction(Transaction &new_trans) { transactions.push_back(new_trans); }

  void display_transactions(); // defined in main.cpp
};

// 2. Update Customer class to "own" Accounts
class Customer
{
private:
  string username;
  string password_harsh;
  string first_name;
  string last_name;
  string email;
  vector<Account> accounts; // The Link! A customer "has" accounts.

public:
  Customer(string f_n, string l_n, string em, string u_name, string p_harsh) : first_name(f_n), last_name(l_n), email(em), username(u_name), password_harsh(p_harsh) {}

  // Getters
  string get_username() { return username; }

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

class AuthManager
{
private:
  string data_file;

  string hash_password(string password)
  {
    hash<string> hasher;
    size_t hashValue = hasher(password);
    return to_string(hashValue);
  }

  // Basic validation: username must be at least 3 characters and have no spaces.
  bool is_valid_username(string username)
  {
    if (username.length() < 3)
    {
      cout << "Username must be at least 3 characters long.\n";
      return false;
    }
    for (char c : username)
    {
      if (c == ' ')
      {
        cout << "Username cannot contain spaces.\n";
        return false;
      }
    }
    return true;
  }

  // Basic validation: password must be at least 6 characters.
  bool is_valid_password(string password)
  {
    if (password.length() < 6)
    {
      cout << "Password must be at least 6 characters long.\n";
      return false;
    }
    return true;
  }

  // Reads through the data file to see if a username already exists.
  bool username_exists(string username)
  {
    ifstream file(data_file);
    string file_username, file_hash;

    while (file >> file_username >> file_hash)
    {
      if (file_username == username)
      {
        return true;
      }
    }
    return false;
  }

public:
  AuthManager(string f_name) : data_file(f_name) {}

  void register_user(string username, string password); // defined in main.cpp

  void login_user(string username, string password); //defined in main.cpp

};

#endif
