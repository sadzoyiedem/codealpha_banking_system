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

bool validate_trans_amount(float amount)
{
  if (cin.fail() || amount < 0)
  {
    cin.clear();
    cin.ignore(1000, '\n');
    cout << "Invalid amount entered!\nRe-enter amount: ";
    return true;
  }

  return false;
}

// Program functionalities
void account_creation(vector<Customer> &database, AuthManager &auth)
{
  clear_screen();
  divider();
  cout << setw(45) << "ACCOUNT CREATION" << endl;
  divider();

  string username, password;

  cout << "Enter your username: ";
  cin >> username;
  cout << "Enter your password: ";
  cin >> password;

  // Auth_system running its checks.
  bool success = auth.register_user(username, password);

  if (!success)
  {
    cout << "Please try creating an account again." << endl;
    return; // Bouncer pattern! Stop here if registration failed.
  }

  string secure_password_hash = auth.hash_password(password);

  // Instantiating customer object
  Customer n_customer(username, secure_password_hash);

  // Prompting for initial deposit
  float ini_depo{};
  cout << "Enter startup amount: ";
  cin >> ini_depo;
  while (validate_trans_amount(ini_depo))
  {
    cin >> ini_depo;
  }

  // Instantiating linked account-customer object
  Account n_account(ini_depo);
  n_customer.add_account(n_account); // linking objects

  database.push_back(n_customer);

#if DEBUG
  n_customer.display_details(); // This will now show "Accounts Owned: 1"
#endif

  // Displaying success message
  divider();
  cout << "Account created successfully." << endl;
  n_customer.display_account_details();
  divider();
}