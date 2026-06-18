#include <iomanip>
#include "main.h"
#include "functions.h"

// Helper functions

void welcome_menu()
{
  cout << "What do you want to do?\n\t"
       << "1. Create an account\n\t"
       << "2. Access an Existing Account (Login)\n\t"
       << "3. Exit Program" << endl;
}

void divider()
{
  cout << "--------------------------------------------------------------------------" << endl;
}

void clear_screen()
{
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

bool input_validation(int min, int max, int &user_opt)
{
  int option{};
  cin >> option;

  if (cin.fail() || option < min || option > max)
  {
    cin.clear();
    cin.ignore(1000, '\n');

    cout << "Invalid option entered!\nRe-enter option: ";

    return true;
  }

  user_opt = option;

  return false;
}

// Program functionalities

void account_creation()
{
  clear_screen();
  divider();
  cout << setw(45) << "ACCOUNT CREATION" << endl;
  divider();

  string user_first_name;
  string user_last_name;
  string user_email;

  cout << "Enter you first name: ";
  cin >> user_first_name;
  cout << "Enter you last name: ";
  cin >> user_last_name;
  cout << "Enter you email: ";
  cin >> user_email;

  // Instantiating customer object
  Customer n_customer(user_first_name, user_last_name, user_email);

#if DEBUG
  n_customer.display_details();
#endif
}