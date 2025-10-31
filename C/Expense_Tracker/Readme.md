Expense Tracker (C Program)

A simple and lightweight command-line Expense Tracker written in C.
It allows you to record, view, and summarize expenses by category — all stored in a CSV file for easy access.

Features

Automatically records the current date
Add new expenses with amount and category
Stores data in a expenses.csv file
View all recorded expenses in a tabular format

Summary of expenses grouped by category

Persistent data across sessions (CSV-based)

File Structure
.
├─ expense_tracker.c    # Source code
└─ readme.md

How to Compile & Run

Make sure you have a C compiler installed (like GCC).

Compile:
gcc expense_tracker.c -o expense_tracker

Run:
./expense_tracker

CSV Format

The program automatically generates expenses.csv (if not present) with the following header:

Date,Amount,Category
2025-10-30,199.99,Groceries
2025-10-31,550.00,Travel
...


This means you can open it directly in Excel, Google Sheets, or any data analytics tool.

Menu Options

When you run the program, you'll see:

1. Add Expense
2. View All Expenses
3. View Summary by Category
4. Exit

Add Expense

Enter amount

Enter category

Date auto-fills to today

Example:

Enter amount: $250
Enter category: Utilities
Expense added successfully!
View All Expenses

Displays all recorded entries:

Date         Amount       Category
2025-10-30   $250.00      Utilities


Additionally shows:

Total expense count

Overall amount spent

Summary by Category

Groups expenses by category:

Category             Total        Count
Groceries            $500.00      3
Travel               $550.00      1

Persistent Storage

All expenses are permanently saved inside expenses.csv, so nothing is lost when the program closes.

Concepts Used

File handling (fopen, fprintf, fgets)

String tokenization (strtok)

Structs for data modeling

Looping, conditions, and input validation

Basic memory-safe input cleanup
Input Validation

The program prevents:

Negative/zero amounts
Empty categories
Invalid main menu input

Future Enhancements (Ideas)

Delete/Update expenses

Filter by date range

Export monthly/annual summaries

Category-wise budgeting

Graphical visualization using Python integration

Author

Developed as a simple terminal-based expense management utility written in C.
