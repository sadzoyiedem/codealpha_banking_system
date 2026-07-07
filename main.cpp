#include <iomanip>
#include "main.h"
#include "functions.h"

int main()
{
  divider();

  cout << setw(65)
       << "Welcome to Version 1 of the Edem's Banking System Application" << endl;

  divider();

  vector<Customer> bank_database;
  AuthManager auth_system("customer_data.txt");

  bool running = true;

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
    {
      string active_user = account_creation(bank_database, auth_system);
      if (!active_user.empty())
      {
        for (auto &cust : bank_database)
        {
          if (cust.get_username() == active_user)
          {
            dashboard_loop(cust, bank_database); // Go to Account Dashboard Loop
            break;
          }
        }
      }
      break;
    }
    case 2:
    {
      string active_user = user_logging(bank_database, auth_system);

      if (!active_user.empty())
      {
        bool found_in_memory = false;

        // Try to find them in active memory (works if they created the account in this same session)
        for (auto &cust : bank_database)
        {
          if (cust.get_username() == active_user)
          {
            found_in_memory = true;
            dashboard_loop(cust, bank_database);
            break;
          }
        }

        //  Reconstruct the user if they restarted the app
        if (!found_in_memory)
        {
          cout << "\n[System] Reloading user profile into active memory..." << endl;

          // Recreate the customer object
          Customer reloaded_cust(active_user, "loaded_from_file");

          // The dashboard assumes the user has at least one account,
          // so we must generate an empty one to prevent a crash.
          Account empty_account(0.0f);
          reloaded_cust.add_account(empty_account);

          // Add them to the active session database
          bank_database.push_back(reloaded_cust);

          // Launch the dashboard using the newly added customer (the last one in the vector)
          dashboard_loop(bank_database.back(), bank_database);
        }
      }
      break;
    }
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

// Functions definitions from main.h
void Account::withdraw(float amount)
{
  if (amount > balance)
  {
    cout << "Insufficient account balance to perform transaction!\nTop up account balance." << endl;
    return;
  }

  balance -= amount;

  // Creates transaction record for withdrawal
  Transaction t("2026-07-06", -amount);
  add_transaction(t);

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
         << " | Date: " << transactions[i].get_date()
         << " | ID: " << transactions[i].get_trans_id()
         << " | Amount: GHC " << transactions[i].get_amount() << endl;
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

bool AuthManager::login_user(string username, string password)
{
  ifstream file(data_file);

  if (!file)
  {
    cout << "Login failed: no users have registered yet.\n";
    return false;
  }

  string file_username, file_hash;
  string entered_hash = hash_password(password);

  while (file >> file_username >> file_hash)
  {
    if (file_username == username)
    {
      if (file_hash == entered_hash)
      {
        cout << "Login successful! Welcome back, " << username << ".\n";
        return true;
      }
      else
      {
        cout << "Login failed: incorrect password.\n";
        return false;
      }
    }
  }

  cout << "Login failed: username '" << username << "' not found.\n";
  return false;
}