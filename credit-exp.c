/**
 * credit-exp.c
 * 
 * Alex W. Bishop
 * alex.w.bishop@gmail.com
 * 
 * Determines if credit card number is a valid Visa, MC, Amex, or invalid using Luhn's algorithm.
 * Also verifies if expiration date is valid.
 * First, the input is a long long. Then it's copied to a string,
 * so its length can be measured. Then it's copied to an int array, so individual digits can be
 * used in mathematical operations for the checksum.
 */
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <time.h>

// define error responses
void invalid(void)
{
    printf("CARD # IS INVALID, OR TYPE IS UNKNOWN\n");
}
void expired(void)
{
    printf("CARD IS EXPIRED\n");
}
void lengtherror(void)
{
    printf("LENGTH IS INVALID\n");
}
void montherror(void)
{
    printf("MONTH IS INVALID\n");
}
void yearerror(void)
{
    printf("YEAR IS INVALID\n");
}

int main(void)
{
    // welcome message
    printf("Welcome to the credit card verification system! (VISA, MASTERCARD, AMEX only)\n");
    
    // define current time variables
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int currYear = tm.tm_year + 1900;
    int currMonth = tm.tm_mon + 1;
    
    // prompts user for credit card number
    printf("Enter credit card number: ");
    long long CCNumber = GetLongLong();

    // create an empty char array of max card length
    char s[16];
    // prints each digit to the char array
    sprintf(s, "%lld", CCNumber);
    // creates an int of the card# length
    int len = strlen(s);

    // prompt for expiration month if length is valid (13, 15, 16 digits)
    if (len == 13 || len == 15 || len == 16)
    {
        printf("Expiration month (MM): ");
        string inputMonth = GetString();
        // check if expiration month is valid (01:12)
        if (!strcmp("01", inputMonth) || !strcmp("02", inputMonth) || !strcmp("03", inputMonth) || !strcmp("04", inputMonth) || !strcmp("05", inputMonth) || !strcmp("06", inputMonth) || !strcmp("07", inputMonth) || !strcmp("08", inputMonth) || !strcmp("09", inputMonth) || !strcmp("10", inputMonth) || !strcmp("11", inputMonth) || !strcmp("12", inputMonth))
        {
            // convert input month to an int
            int expMonth = atoi(inputMonth);
            // prompt for expiration year
            printf("Expiration year (YY): ");
            int expYear = GetInt();
            expYear = expYear + 2000;
            // check if expiration year is valid
            if (expYear < currYear + 100 && expYear >= currYear)
            {
            // display entered expiration date in MM/YYYY format
            printf("Expiration date: %.2i/%i\n", expMonth, expYear);
            }
            // return error if expiration year is invalid
            else
            {
                yearerror();
                return 0;
            }
            // return error if card already expired
            if (expYear < currYear || (expYear == currYear && expMonth < currMonth))
            {
                expired();
                return 0;
            }
        }
        // return error if expiration month is invalid
        else
        {
            montherror();
            return 0;
        }
    }
    // return error if card # length is invalid
    else
    {
        lengtherror();
        return 0;
    }
    
    // create an int array with length of number
    int number[len];
    // print digits into ASCII-converted array of ints
    for (int i = 0; i < len; i++)
    {
        number[i] = s[i] - '0';
    }
    // set up checksum starting points
    int sum = 0, j = 1;
    // move from last digit towards beginning
    for (int i = len - 1; i >= 0; i--)
    {
        // perform on every other digit (first run will be false)
        if (j % 2 == 0)
        {
            // multiply by 2, add resulting digit to sum
            sum += number[i] * 2 % 10;
            // add 1 for the ten's place digit if applicable
            if (number[i] * 2 >= 10)
                sum = sum + 1;
        }
        // add an un-multiplied number to sum
        else
            sum = sum + number[i];
        
        j++;
    }
    
    // determine card type if checksum AND expiration is valid
    if (sum % 10 == 0)
    {
        // AMEX starts with 34 or 37
        if (number[0] == 3 && (number[1] == 4 || number[1] == 7))
            printf("VALID CARD. TYPE: AMEX\n");
        // MC starts with 51 thru 55
        else if (number[0] == 5 && number[1] > 0 && number[1] < 6)
            printf("VALID CARD. TYPE: MASTERCARD\n");
        // VISA starts with 4
        else if (number[0] == 4)
            printf("VALID CARD. TYPE: VISA\n");
        // return error otherwise
        else
            invalid();
    }
    else
        invalid();
    return 0;
}
