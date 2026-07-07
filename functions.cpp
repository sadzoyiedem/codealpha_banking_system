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

void account_menu()
{
  clear_screen();
  divider();
  cout << setw(45) << "ACCOUNT MENU" << endl;
  divider();

  cout << "\t1. Deposit funds\n"
       << "\t2. Withdraw funds\n"
       << "\t3. Transfer funds\n"
       << "\t4. View Transaction History\n"
       << "\t5. View account details\n"
       << "\t6. Logout" << endl;

  divider();
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
string account_creation(vector<Customer> &database, AuthManager &auth)
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

  bool success = auth.register_user(username, password);

  if (!success)
  {
    cout << "Please try creating an account again." << endl;
    return "";
  }

  string secure_password_hash = auth.hash_password(password);
  Customer n_customer(username, secure_password_hash);

  float ini_depo{};
  cout << "Enter startup amount: ";
  cin >> ini_depo;
  while (validate_trans_amount(ini_depo))
  {
    cin >> ini_depo;
  }

  Account n_account(ini_depo);

  // Record initial deposit as a transaction if > 0
  if (ini_depo > 0)
  {
    Transaction initial_txn("2026-07-06", ini_depo);
    n_account.add_transaction(initial_txn);
  }

  n_customer.add_account(n_account);
  database.push_back(n_customer);

  divider();
  cout << "Account created successfully. Account Number: " << n_account.get_acc_num() << endl;
  divider();

  return username;
}

string user_logging(vector<Customer> &database, AuthManager &auth)
{
  clear_screen();
  divider();
  cout << setw(45) << "LOGIN" << endl;
  divider();

  string username, password;

  cout << "Enter your username: ";
  cin >> username;
  cout << "Enter your password: ";
  cin >> password;

  bool success = auth.login_user(username, password);

  if (!success)
  {
    cout << "Please try logging into account again." << endl;
    return "";
  }

  return username;
}

void dashboard_loop(Customer &active_customer, vector<Customer> &database)
{
  bool logged_in = true;

  // Accessing the primary active account (assumes 1 account per user for now)
  if (active_customer.get_accounts().empty())
    return;
  Account &active_account = active_customer.get_accounts()[0];

  while (logged_in)
  {
    account_menu();
    int user_option{};
    cout << "Enter option: ";
    while (input_validation(1, 6, user_option))
      ;

    float amount{};
    string target_acc;
    bool found = false;

    switch (user_option)
    {
    case 1:
      cout << "Enter amount to deposit: ";
      cin >> amount;
      while (validate_trans_amount(amount))
        cin >> amount;
      active_account.deposit(amount);
      break;

    case 2:
      cout << "Enter amount to withdraw: ";
      cin >> amount;
      while (validate_trans_amount(amount))
        cin >> amount;
      active_account.withdraw(amount);
      break;

    case 3:
      cout << "Enter target account number: ";
      cin >> target_acc;
      cout << "Enter amount to transfer: ";
      cin >> amount;
      while (validate_trans_amount(amount))
        cin >> amount;

      for (auto &cust : database)
      {
        for (auto &acc : cust.get_accounts())
        {
          if (acc.get_acc_num() == target_acc)
          {
            found = true;
            if (active_account.get_balance() >= amount)
            {
              active_account.withdraw(amount); // Deducts and records
              acc.deposit(amount);             // Adds and records
              cout << "Transfer successful." << endl;
            }
            else
            {
              cout << "Insufficient funds for transfer." << endl;
            }
            break;
          }
        }
        if (found)
          break;
      }
      if (!found)
        cout << "Target account not found." << endl;
      break;

    case 4:
      active_account.display_transactions();
      break;

    case 5:
      active_customer.display_account_details();
      break;

    case 6:
      cout << "Logging out..." << endl;
      logged_in = false;
      break;
    }

    if (logged_in)
    {
      cout << "\nPress Enter to return to menu...";
      cin.ignore();
      cin.get();
    }
  }
}