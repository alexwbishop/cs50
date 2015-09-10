/**
 * de-caesar-nokey.c
 * 
 * Alex W. Bishop
 * alex.w.bishop@gmail.com
 * 
 * Decrypts text encoded with a Caesar cipher into all 25 possible keys to find its key.
 */
 
#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // returns error if 1 arg not provided (program only)
    if (argc != 1)
    {
        printf("Usage: ./de-caesar-nokey\nIf you already know the key, use ./de-caesar [#key]\n");
        return 1;
    }
    // prompt user for message text
    printf("Enter encrypted text:\n");
    char* p = GetString();
    printf("All possible decryptions:\n");
    // by starting from 25, displays keys in ascending order after flipping (1-25)
    int key = 25;
    // iterates a decryption for each possible key
    for (int i = 1; i < 26; i++, key--)
    {
        // flips the encryption key to its inverse for decryption
        printf("Key = %i: ", 26 - (key % 26));
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
    }
    // successful run of program
    return 0;
}

