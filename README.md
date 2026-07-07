# CodeAlpha Banking System (Version 1.0)

## Overview
A command-line interface (CLI) banking application written in C++. This system models real-world banking operations, allowing users to register, log in, create accounts, and perform essential financial transactions. It utilizes a modular, object-oriented architecture to securely manage user authentication, account balances, and transaction histories.

## Features
* **User Authentication:** Secure registration and login system. User credentials are obfuscated using standard string hashing and saved locally to persist across sessions.
* **Account Management:** Users can create an account with an initial deposit. Each account is assigned a randomly generated, unique 10-digit account number.
* **Core Banking Operations:**
  * **Deposit:** Add funds to the active account.
  * **Withdraw:** Remove funds, featuring automatic validation to prevent overdrafts (Insufficient Funds check).
  * **Transfer:** Send funds securely to another user's account number using a double-entry transaction record (debit active account, credit target account).
* **Transaction History:** Automatically records the date, uniquely generated transaction ID (e.g., `TXN-4829`), and amount for every successful operation. 
* **State Recovery:** Rebuilds user profiles and account data into active memory upon logging back into the system.

## Project Architecture
The codebase follows a modular design, split into distinct headers and implementation files:

* `main.cpp`: The entry point of the application. Handles the main menu loop, program routing, and core class function definitions (like `withdraw` and `login_user`).
* `main.h`: Contains the definitions for the core Data Models (`Transaction`, `Account`, `Customer`) and the `AuthManager` class.
* `functions.h`: Declares the helper functions and program flow controllers (menus, screen clearing, input validation).
* `function.cpp`: Implements the UI menus, input validation logic, and the primary application flows (`account_creation`, `user_logging`, and `dashboard_loop`).
* `customer_data.txt`: The local database file generated automatically to store registered usernames and password hashes.

## Prerequisites
To compile and run this project, you will need a standard C++ compiler (like GCC or Clang) that supports at least C++11.

## Compilation and Execution
To run the application, compile the `.cpp` files together and execute the resulting binary.

**Using G++ (Linux/macOS/Windows Git Bash):**
```bash
# Compile the code
g++ main.cpp function.cpp -o bank_system

# Run the executable
./bank_system
```
## Usage Flow
1. **Launch the app:** You will be geeted with the Main Menu. 
2. **Create an Account (Option 1):** Register a username (no spaces, >2 chars) and a password (>5 chars). Follow the prompt to make an initial deposit.
3. **Login (Option 2):** If you already have an account, log in using your credentials to access the Account Dashboard.
4. **Dashboard:** From here, you can deposit, withdraw, transfer, or view your transaction history.
5. **Logout:** Safely closes your active session and returns to the main menu.

## Author
Developed by: **Adzoyi Stephen Edem**      *June, 2026*
