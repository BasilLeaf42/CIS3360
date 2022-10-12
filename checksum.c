
/*=============================================================================
| Assignment: pa02 - Calculating an 8, 16, or 32 bit checksum
|				   for a simple ASCII file containing only ASCII
| 				   characters. This file is terminated by a NEWLINE
|				   character which has a hexadecimal value of ’0a’.
|
| Author: Christopher Cao
| Language: C
|
| To Compile: gcc -o pa02 pa02.c
|
| To Execute: ./pa02
|			 where inputFilename.txt is the ASCII text file
|			 and 8 is the checksum size in bits
|			 (Valid options are 8, 16, & 32)
|
| Note: All input files are simple 8 bit ASCII input
|
| Class: CIS3360 - Security in Computing - Summer 2021
| Instructor: McAlpin
| Due Date: 7/26/2021
|
+=============================================================================*/

// pre-processor directives
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

// start of main function
int main(int argc, char *argv[])
{
	// variable declaration
	FILE *inputFile = fopen(argv[1], "r");
	int checksumSize = atoi(argv[2]);
	int i = 0;
	int flag = 1;
	int inputLength = 0;
	long long unsigned int result = 0;
	char inputText = getc(inputFile);
	char outputText[atoi(argv[2])];
	char char1 = 'X';
	char char2 = 'X';
	char char3 = 'X';
	char char4 = 'X';
	
	// statement to detect invalid values for checksumSize
	if ((checksumSize != 8) && (checksumSize != 16) && (checksumSize != 32))
	{
		printf("Valid checksum sizes are 8, 16, or 32\n");
		
		return -1;
	}
	
	// loop to format and print inputText
	while (flag)
	{
		// statement to format and print inputText
		if ((int)inputText != EOF && i < 1024)
		{
			// output if newline is necessary
			if (i % 80 == 0)
			{
				printf("\n%c", inputText);
				inputText = getc(inputFile);
				i++;
			}
			
			// output if newline is unnecessary
			else
			{
				printf("%c", inputText);
				inputText = getc(inputFile);
				i++;
			}
		}
		
		// statement to terminate loop when end of file is reached
		else
		{
			flag = 0;
		}
	}
	
	// update variables
	flag = 1;
	inputLength = i;
	i = 0;
	rewind(inputFile);
	
	// statement to detect 8 bit checksum
	if (checksumSize == 8)
	{
		char1 = getc(inputFile);
		
		// loop to calculate 8 bit checksum
		while (flag)
		{
			// statement to calculate 8 bit checksum
			if (char1 != EOF)
			{
				result = result + ((int)char1);
				char1 = getc(inputFile);
			}
			
			// statement to terminate loop when char1 reaches end of file
			else
			{
				result &= ~(1023 << checksumSize);
				flag = 0;
			}
		}
	}
	
	// statement to detect 16 bit checksum
	else if (checksumSize == 16)
	{
		char1 = getc(inputFile);
		char2 = getc(inputFile);
		
		// statement to calculate final result and pad out if char2 reaches end of file
		if (char2 == EOF)
		{
			printf("X");
			result = result + ((int)char1 << 8) + 88;
			result &= ~(1023 << checksumSize);
			inputLength = inputLength + 1;
			flag = 0;
		}
		
		// loop to calculate 16 bit checksum
		while (flag)
		{
			result = result + ((int)char2) + (((int)char1) << 8);
			char1 = getc(inputFile);
			char2 = getc(inputFile);
			
			// statement to detect if char1 reaches end of file
			if (char1 != EOF)
			{
				// statement to calculate final result and pad out if char2 reaches end of file
				if (char2 == EOF)
				{
					printf("X");
					result = result + ((int)char1 << 8) + 88;
					result &= ~(1023 << checksumSize);
					inputLength = inputLength + 1;
					flag = 0;
				}
			}
			
			// statement to terminate loop when char1 reaches end of file
			else
			{
				result &= ~(1023 << checksumSize);
				flag = 0;
			}
		}
	}
	
	// statement to detect 32 bit checksum
	else if (checksumSize == 32)
	{
		// loop to calculate 32 bit checksum
		while (flag)
		{
			char1 = getc(inputFile);
			char2 = getc(inputFile);
			char3 = getc(inputFile);
			char4 = getc(inputFile);
			
			// statement to calculate final result and pad out if char2 reaches end of file
			if (char2 == EOF)
			{
				printf("XXX");
				result = result + ((int)char1 << 24) + 5789784;
				result &= ~(4294967295 << checksumSize);
				inputLength = inputLength + 3;
				flag = 0;
			}
			
			// statement to calculate final result and pad out if char3 reaches end of file
			else if (char3 == EOF)
			{
				printf("XX");
				result = result + ((int)char1 << 24) + ((int)char2 << 16) + 22616;
				result &= ~(4294967295 << checksumSize);
				inputLength = inputLength + 2;
				flag = 0;
			}
			
			// statement to calculate final result and pad out if char4 reaches end of file
			else if (char4 == EOF)
			{
				printf("X");
				result = result + ((int)char1 << 24) + ((int)char2 << 16) + ((int)char3 << 8) + 88;
				result &= ~(4294967295 << checksumSize);
				inputLength = inputLength + 1;
				flag = 0;
			}
			
			// statement to continue calculating result
			else
			{
				result = result + ((int)char1 << 24) + ((int)char2 << 16) + ((int)char3 << 8) + ((int)char4);
			}
		}
	}
	
	// convert result to hexadecimal
	sprintf(outputText, "%llx", result);
	
	// final output
	printf("\n%2d bit checksum is %8s for all %4d chars\n", checksumSize, outputText, inputLength);
	
	return 0;
}

/*=============================================================================
| I Christopher Cao (ch282858) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/
