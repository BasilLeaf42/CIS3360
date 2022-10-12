
/*=============================================================================
| Assignment: pa01 - Encrypting a plaintext file using the Vigenere cipher
|
| Author: Christopher Cao
| Language: C
|
| To Compile: gcc -o pa01 pa01.c
|
| To Execute: ./pa01 kX.txt pX.txt
|
| where kX.txt is the keytext file
| and pX.txt is plaintext file
|
| Note: All input files are simple 8 bit ASCII input
|
| Class: CIS3360 - Security in Computing - Summer 2021
| Instructor: McAlpin
| Due Date: 6/27/2021
|
+=============================================================================*/

// pre-processor directives
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// start of main function
int main(int argc, char *argv[])
{
	FILE *keyFile = fopen(argv[1], "r"), *plainTextFile = fopen(argv[2], "r");
	int i = 0;
	int flag = 1;
	int keySize;
	char keyText[512];
	char plainText[512];
	char cipherText[512];
	char storedCharacter = 'x';

	// format and print key
	printf("\n\nVigenere Key:\n");
  
	while (flag)
	{
		// statement to sort through string
		if (fscanf(keyFile, "%c", &storedCharacter) != EOF && i < 512)
		{
			// statement to sort through alphabetic characters
			if ((storedCharacter >= 'A' && storedCharacter <= 'Z') || (storedCharacter >= 'a' && storedCharacter <= 'z'))
			{
				// statement to convert uppercase letters to lowercase
				if (storedCharacter >= 'A' && storedCharacter <= 'Z')
				{
					storedCharacter = tolower(storedCharacter);
				}
				
				// output if newline is necessary
				if (i % 80 == 0)
				{
					printf("\n%c", storedCharacter);
					keyText[i] = storedCharacter;
					i++;
				}
				
				// output if newline is not necessary
				else
				{
					printf("%c", storedCharacter);
					keyText[i] = storedCharacter;
					i++;
				}
			}
		}
		
		// terminate while loop
		else
		{
			flag = 0;
		}
	}
	
	// update variables
	flag = 1;
	keySize = i;
	i = 0;

	// format and print plaintext
	printf("\n\n\nPlaintext:\n");
	
	while(flag)
	{
		// statement to sort through string
		if(fscanf(plainTextFile, "%c", &storedCharacter) != EOF && i < 512)
		{
			// statement to sort through alphabetic characters
			if((storedCharacter >= 'A' && storedCharacter <= 'Z') || (storedCharacter >= 'a' && storedCharacter <= 'z'))
			{
				// statement to convert uppercase letters to lowercase
				if(storedCharacter >= 'A' && storedCharacter <= 'Z')
				{
					storedCharacter = tolower(storedCharacter);
				}
				
				// output if newline is necessary
				if (i % 80 == 0)
				{
					printf("\n%c", storedCharacter);
					plainText[i] = storedCharacter;
					i++;
				}
				
				// output if newline is not necessary
				else
				{
					printf("%c", storedCharacter);
					plainText[i] = storedCharacter;
					i++;
				}
			}
		}
		
		// terminate while loop
		else
		{
			flag = 0;
		}
	}

	// fill plaintext with "x" as necessary
	for (i; i < 512; i++)
	{
		// output if newline is necessary
		if (i % 80 == 0)
		{
			printf("\nx");
			plainText[i] = 'x';
		}
		
		// output if newline is not necessary
		else
		{
			printf("x");
			plainText[i] = 'x';
		}
	}
	
	// update variables
	flag = 1;
	i = 0;
	
	// encrypt and print ciphertext
	printf("\n\n\nCiphertext:\n");
	
	// statement to sort through string
	for (i = 0; i < 512; i++)
	{
		// encrypt current character
		cipherText[i] = (((plainText[i] - 'a') + (keyText[i % keySize] - 'a')) % 26) + 'a';
		
		// output if newline is necessary
		if (i % 80 == 0)
		{
			printf("\n%c", cipherText[i]);
		}
		
		// output if newline is not necessary
		else
		{
			printf("%c", cipherText[i]);
		}
	}
	
	// final output
	printf("\n");
}

/*=============================================================================
| I Christopher Cao (ch282858) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/
