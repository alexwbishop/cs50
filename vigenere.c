/**
 * vigenere.c
 * 
 * Alex W. Bishop
 * alex.w.bishop@gmail.com
 * 
 * Encrypts input text using Vigenere's cipher.
 * Formula: Ci = (Pi + Kj) % 26
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
        printf("Usage: ./vigenere [keyword]\n");
        return 1;
    }
    
    // set key and length of key
    char* key = argv[1];
    int length = strlen(key);
    
    // returns error if string contains non-alpha
    for (int i = 0; i < length; i++)
    {
        if (isalpha(key[i]) == false)
        {
            printf("Alpha chars only.\n");
            return 1;
        }
    }
    
    // create an array for shift values of size length
    int *k = malloc(sizeof(int) * length);
    
    // assign values to the shift array
    for (int i = 0; i < length; i++)
    {
        // set shift value for UC char in key (ASCII to alpha)
        if (isupper(key[i]))
        {
        k[i] = key[i] - 65;
        }
        // set shift value for LC char in key (ASCII to alpha)
        else if (islower(key[i]))
        {
        k[i] = key[i] - 97;
        }
    }
    
    // prompt user for message text
    char* p = GetString();
    
    // scan through input message, char by char
    for (int i = 0, j = 0, l = strlen(p); i < l; i++)
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
                int c = (upper + k[j % length]) % 26;
                // print shifted char
                printf("%c", c + 65);
            }
            // for lower case chars
            else if (islower(p[i]))
            {
                // convert from ASCII to alpha
                int lower = p[i] - 97;
                // shift char through LC alphabet by key
                int c = (lower + k[j % length]) % 26;
                // print shifted char
                printf("%c", c + 97);
            }
            // cycle j to the next shift in the key after a shift was performed
            j++;
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

