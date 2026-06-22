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
      account_creation(bank_database);
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
      running = false;
      break;
    }

  } while (running);

  return 0;
}
