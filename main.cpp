/*

  * Command Line Banking System

    * This banking system models real-word customer and account creation alongside transactions performed by customers.

    * Creates classes for Customer, Account and Transaction.

    * Uses modular function to handle account creation and managing of customers and accounts.

    * Implements features for deposit, withdrawals, and fund transfers.

    * Stores transaction history and allow users to view recent transactions.

    * Displays the neccesary account informations.





  * Developed by: Adzoyi Stephen Edem



  * June, 2026

*/

#include <iomanip>
#include "main.h"
#include "functions.h"

int main()
{
  // Welcome message

  divider();

  cout << setw(65)
       << "Welcome to Version 1 of the Edem's Banking System Application" << endl;

  divider();

  // Data structure holding list of customers
  vector<Customer> bank_database;

  // Instantiate AuthManager and tell it the file_name
  AuthManager auth_system("customer_data.txt");

  bool running = false;

  do
  {
    int user_option{};
    welcome_menu();
    cout << "Enter option: ";
    while (input_validation(1, 3, user_option))
      ;

    switch (user_option)
    {
    case 1:
      account_creation(bank_database, auth_system);
#if DEBUG
      bank_database[0].display_details(); // This will now show "Accounts Owned: 1"
#endif
      break;
    case 2:
      break;
    default:

      divider();
      cout << "Thank you for using this program. \n\nExiting program..." << endl;
      divider();

      running = true;
      break;
    }

  } while (running);

  return 0;
}

// Functions definitions from main.h

void Account::withdraw(float amount)
{
  if (amount > balance)
  {
    cout << "Insufficient account balance to perform transaction!\nTop up acccount balance." << endl;
    return;
  }

  balance -= amount;

  cout << "Withdrawal successful." << endl;
}

void Account::display_transactions()
{
  cout << "Transactions summary for " << account_number << endl;

  if (transactions.empty())
  {
    cout << "No transactions recorded yet." << endl;
    return;
  }

  for (int i = 0; i < transactions.size(); i++)
  {
    cout << "Transaction " << i + 1
         << "Transaction id: " << transactions[i].get_trans_id()
         << "Amount: " << transactions[i].get_amount() << endl;
  }

  divider();
}

bool AuthManager::register_user(string username, string password)
{
  if (!is_valid_username(username))
    return false;
  if (!is_valid_password(password))
    return false;

  if (username_exists(username))
  {
    cout << "Registration failed: username '" << username << "' is already taken.\n";
    return false;
  }

  string hashed_password = hash_password(password);

  ofstream file(data_file, ios::app);

  if (!file)
  {
    cout << "Registration failed: could not open the data file.\n";
    return false;
  }

  file << username << " " << hashed_password << endl;

  return true;
}

void AuthManager::login_user(string username, string password)
{
  ifstream file(data_file);

  if (!file)
  {
    cout << "Login failed: no users have registered yet.\n";
    return;
  }

  string file_username, file_hash;

  string entered_hash = hash_password(password);

  while (file >> file_username >> file_hash)
  {
    if (file_username == username)
    {
      if (file_hash == entered_hash)
        cout << "Login successful! Welcome back, " << username << ".\n";
      else
        cout << "Login failed: incorrect password.\n";
      return;
    }
  }

  cout << "Login failed: username '" << username << "' not found.\n";
}