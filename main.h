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
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<int> dist(1000, 9999);
    return "TXN-" + std::to_string(dist(engine));
  }

public:
  Transaction(string d, float amt) : transaction_id(generate_trans_id()), date(d), amount(amt) {}

  // getters
  string get_trans_id() { return transaction_id; }
  float get_amount() { return amount; }
  string get_date() { return date; }
};

class Account
{
private:
  string account_number;
  float balance;
  vector<Transaction> transactions;

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
    Transaction t("2026-07-06", amount);
    add_transaction(t);
    cout << "Amount deposit successful." << endl;
  }

  void withdraw(float amount);
  void add_transaction(Transaction &new_trans) { transactions.push_back(new_trans); }
  void display_transactions();
};

class Customer
{
private:
  string username;
  string password_hash;
  vector<Account> accounts;

public:
  Customer(string u_name, string p_hash) : username(u_name), password_hash(p_hash) {}

  // Getters
  string get_username() { return username; }
  vector<Account> &get_accounts() { return accounts; }

  void add_account(Account &new_account)
  {
    accounts.push_back(new_account);
  }

  void display_account_details()
  {
    cout << "Account summary for " << username << ": " << endl;

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

  bool is_valid_password(string password)
  {
    if (password.length() < 6)
    {
      cout << "Password must be at least 6 characters long.\n";
      return false;
    }
    return true;
  }

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

  bool register_user(string username, string password);
  bool login_user(string username, string password);

  string hash_password(string password)
  {
    hash<string> hasher;
    size_t hashValue = hasher(password);
    return to_string(hashValue);
  }
};

#endif