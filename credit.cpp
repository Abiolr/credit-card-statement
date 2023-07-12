// Name: Abiola Raji

// Source File:  a1.cpp

// Purpose: to print a customer's montlhy credit card statement
// Details: checks to see if account number is valid, provides
// the amount of interest due, provide total purchases and payments made,
// provides new balance and minimum payment.

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

void print_statement (int account_number, double credit_limit,
                      double open_balance, double total_purchases,
                      double total_payments, double interest_due,
                      double close_balance, double minimum_payment);

bool is_valid_length (int account_number);

int extract_digit (int number, int position);

bool has_valid_check_digit (int account_number);

bool is_valid_account (int account_number);

void read_and_process (int account_number,
                       double &total_purchases,
                       double &total_payments,
                       bool &valid_account,
                       bool &valid_transaction);

void update_account (double open_balance,
                    double total_payments,
                    double total_purchases,
                    double credit_limit,
                    double &interest_due,
                    double &close_balance,
                    double &minimum_payment);

//------------------------------------------------------------
// Function Name:  main
// Purpose: to call the functions to print an accurate statement
//
// Details: takes the account number, starting balance, and the 
// credit limit and calls three functions.
//
// Inputs: account_number - the customer's account number
//         open_balance - the customer's starting balance
//         credit_limit - the customer's credit limit
//    
//------------------------------------------------------------

int main ()
{
    int account_number;
    double open_balance;
    double credit_limit;
    double total_purchases;
    double total_payments;
    bool valid_account;
    bool valid_transaction;
    double interest_due;
    double close_balance;
    double minimum_payment;

    cin >> account_number >> open_balance >> credit_limit;

    read_and_process(account_number,
		     total_purchases,
		     total_payments,
		     valid_account,
		     valid_transaction);

    update_account(open_balance,
		   total_payments,
		   total_purchases,
		   credit_limit,
		   interest_due,
		   close_balance,
		   minimum_payment);

    if (valid_transaction == true)
    {
     	print_statement(account_number, credit_limit,
			open_balance, total_purchases,
			total_payments, interest_due,
			close_balance, minimum_payment);
    }

    return 0;


}

//------------------------------------------------------------
// Function Name:  print_statement
// Purpose: to print a month-end credit card statement
//
// Details:  
//    All quantities are printed as dollar amounts with 
//    exactly 2 digits after the decimal point.
//
//    The bill consists of 8 lines of output. Each line starts with a
//    title, whose field width is 20 characters. Titles are left justified.
//    The item on the first line following the title is the customer's
//    account number. It is left justified and follows the title field
//    immediately.
//    On the remaining 7 lines the item following the title is a dollar
//    value. All dollar values are right justified and in a field of
//    width 8.
//
// Inputs: credit_limit - the customer's credit limit
//         open_balance - amount owing at beginning of month
//         total_purchases - sum of purchase transactions for the month
//         total_payments - sum of payment transactions for the month
//         interest_due - interest on overdue balance
//         close_balance - amount owing at end of month
//         minimum_payment - minimum amount to be paid by customer
//    
//------------------------------------------------------------

void print_statement (int account_number, 
                      double credit_limit, 
                      double open_balance, 
                      double total_purchases, 
                      double total_payments,
                      double interest_due, 
                      double close_balance,
                      double minimum_payment)
{
  const int TITLE_FIELD_WIDTH = 20;
  const int VALUE_FIELD_WIDTH = 8;
  const int DECIMAL_PLACES = 2;
  
  cout << endl;
  cout.setf(ios::fixed);
  cout.setf(ios::showpoint);
  cout.precision(DECIMAL_PLACES);

  cout << endl;
  cout << left << setw(TITLE_FIELD_WIDTH) << "Account Number:"
       << account_number << endl;
  cout << left << setw(TITLE_FIELD_WIDTH) << "Credit Limit:"
       << right << setw(VALUE_FIELD_WIDTH) <<  credit_limit << endl;
  cout << left << setw(TITLE_FIELD_WIDTH) << "Starting Balance:"
       << right << setw(VALUE_FIELD_WIDTH) <<  open_balance << endl;
  cout << left << setw(TITLE_FIELD_WIDTH) << "Total Purchases:"
       << right << setw(VALUE_FIELD_WIDTH) <<  total_purchases << endl;
  cout << left << setw(TITLE_FIELD_WIDTH) << "Total Payments:"
       << right << setw(VALUE_FIELD_WIDTH) <<  total_payments << endl;
  cout << left << setw(TITLE_FIELD_WIDTH) << "Interest:"
       << right << setw(VALUE_FIELD_WIDTH) <<  interest_due << endl;
  cout << left << setw(TITLE_FIELD_WIDTH) << "Month End Balance:"
       << right << setw(VALUE_FIELD_WIDTH) <<  close_balance << endl;
  cout << left << setw(TITLE_FIELD_WIDTH) << "Minimum Payment:"
       << right << setw(VALUE_FIELD_WIDTH) <<  minimum_payment << endl;

  cout.unsetf(ios::left);
  cout.unsetf(ios::right);
  return;
}

//------------------------------------------------------------
// Function Name: is_valid_length
// Purpose: to check if the account number is the correct length
//
// Details: the function takes the account number checks to see
// if it 7 digits, which are the numbers 1000000-9999999. the
// function returns true if it is the valid length and false if
// it is not.
//
// Inputs: account_number - the customer's account number
//    
//------------------------------------------------------------

bool is_valid_length (int account_number)
{
    if (1000000 <= account_number && account_number <= 9999999) {
        return true;
    } else {
        return false;
    }
}

//------------------------------------------------------------
// Function Name: extract_digit
// Purpose: to find the digit of a number at its given position
//
// Details: the function takes an integer and its position and
// returns the digit at that position.
//
// Inputs: number - an integer 
//         position - the position the number
//    
//------------------------------------------------------------

int extract_digit (int number, int position)
{
	int digit_at_p;
	digit_at_p = number / pow(10, position);
	digit_at_p %= 10;
	
	return digit_at_p;
}

//------------------------------------------------------------
// Function Name:  has_valid_check_digit
// Purpose: to check if the check digit equals the units digit
//
// Details: gets the sum of the units digit and check to see if
// it is equal to the check digit, which is the last number (position
// zero) of the account number. Returns true if equal and false if not.
//
// Inputs: account_number - the customer's account number
//    
//------------------------------------------------------------

bool has_valid_check_digit (int account_number)
{
	int check_digit = extract_digit(account_number, 1);
	int units_digit;
	units_digit = extract_digit(account_number, 6) * 6 + 
	extract_digit(account_number, 5) * 5 + 
	extract_digit(account_number, 4) * 4 + 
	extract_digit(account_number, 3) * 3 + 
	extract_digit(account_number, 2) * 2 + 
	extract_digit(account_number, 1);
	units_digit %= 10;
	if (check_digit == units_digit){
		return true;
	}
	else {
		return false;
	}
}

//------------------------------------------------------------
// Function Name:  is_valid_account
// Purpose: to determine if account number is valid
//
// Details: the function takes the account number and returns 
// true if the account number is valid and false if it is not.
//
// Inputs: account_number - the customer's account number
//    
//------------------------------------------------------------

bool is_valid_account (int account_number)
{
	bool test1;
	bool test2;
    test1 = is_valid_length(account_number);
	test2 = has_valid_check_digit(account_number);

	if (test1 == true and test2 == true) {
        return true;
    } else {
        cout << "Invalid account number" << endl;
        return false;
    }
}

//------------------------------------------------------------
// Function Name:  read_and_process
// Purpose: to read and process monthly transactions
//
// Details: takes the account number and the monthly transactions
// and returns the total_purchases and total payments. prints error
// message if error code is 'B'.
//
// Inputs: account_number - the customer's account number
//         total_purchases - the customer's total purchases
//         total_payments - the customer's total payments
//         error_code - the error code for the account (G/B)
//    
//------------------------------------------------------------

void read_and_process (int account_number,
		       double &total_purchases,
		       double &total_payments,
		       bool &valid_account,
		       bool &valid_transaction)
{
    valid_account = is_valid_account(account_number);
    char error_code;
    cin >> total_purchases >> total_payments >> error_code;

    if (error_code == 'B')
    {
	cout << "Bad monthly transaction record" << endl;
	cout << "*** Account " << account_number << " - statement not printed due to errors ***" << endl;
	valid_transaction = false;
    }
    else {
	valid_transaction = true;
    }
}

//------------------------------------------------------------
// Function Name:  update_account
// Purpose: to update the the information for the customer's monthly
// statement
//
// Details: takes the starting balance, payments, purchases, and credit
// limit and returns the interest owing, the new balance, and the minimum
// payment. 
//
// Inputs: open_balance - the customer's starting balance
//         total_purchases - the customer's total purchases
//         total_payments - the customer's total payments
//         credit_limit - the customer's credit limit
//    
//------------------------------------------------------------

void update_account (double open_balance,
		    double total_payments,
		    double total_purchases,
		    double credit_limit,
		    double &interest_due,
		    double &close_balance,
		    double &minimum_payment)
{
    const double INTEREST = 0.015;
    double difference = open_balance - total_payments;
    if (difference > 0)
    {
        interest_due = difference * INTEREST;
    }
    else {
        interest_due = 0;
    }

    close_balance = open_balance - total_payments + total_purchases + interest_due;

    if (close_balance < 10)
    {
        minimum_payment = 0;
    }
    else {
        if (close_balance < credit_limit)
        {
            if (close_balance * 0.1 > 10)
            {
                minimum_payment = close_balance * 0.1;
            }
            else {
                minimum_payment = 10;
            }
        }
        else { 
            if (close_balance * 0.1 > 10)
            {
                minimum_payment = close_balance * 0.1;
            }
            else {
                minimum_payment = 10;
            }
            minimum_payment += close_balance - credit_limit;
        }
    }

}