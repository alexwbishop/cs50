/**
 * caesar.c
 * 
 * Alex W. Bishop
 * alex.w.bishop@gmail.com
 * 
 * Encrypts input text using Caesar's cipher.
 * Formula: Ci = (Pi + K) % 26
 */
 
#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // returns error if other than 2 args given
    if (argc != 2)
    {
        printf("Usage: ./caesar [#key]\n");
        return 1;
    }
    
    // returns error if any key char is not a digit
    int l = strlen(argv[1]);
    for (int i = 0; i < l; i++)
    {
        if (isdigit(argv[1][i]) == false)
        {
            printf("Positive ints only.\n");
            return 1;
        }
    }
    // converts input key to int
    int key = atoi(argv[1]);
    
    // prompt user for message text
    char* p = GetString();
    
    // scan through input message, char by char
    for (int i = 0, l = strlen(p); i < l; i++)
    {
        // only shift if char is an alpha
        if (isalpha(p[i]))
        {
            // for upper case chars
            if (isupper(p[i]))
            {
                // convert from ASCII to alpha
                int upper = p[i] - 65;
                // shift char through UC alphabet by key
                int c = (upper + key) % 26;
                // print shifted char
                printf("%c", c + 65);
            }
            // for lower case chars
            else if (islower(p[i]))
            {
                // convert from ASCII to alpha
                int lower = p[i] - 97;
                // shift char through LC alphabet by key
                int c = (lower + key) % 26;
                // print shifted char
                printf("%c", c + 97);
            }
        }
        // pass char through if non-alpha
        else
        {
            printf("%c", p[i]);
        }
    }
    printf("\n");
    
    // successful run of program
    return 0;
}

