#include <iostream>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <signal.h>
#include <sys/wait.h>
/*
Lukas Taylor
CS470
Lab 02
1/30/18

*/

using namespace std;

void forkIt(vector<char> ch)
{
	//char array of 26 upper and lower case letters to compare each index of char vector
	char upperCaseAlpha[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	char lowerCaseAlpha[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	
	cout << "~~~~~~~~~~~~~~~~~~~~Before fork~~~~~~~~~~~~~~~~~~~~" << endl;

	for(int s = 0; s <= 25; s++)
	{
		if(fork() == 0) //fork returns zero and returns child process
		{
				int counter = 0; //outer loop for 26 letters in alphabet
				
				for(int i = 0; i < ch.size(); i++ ) //loops til end of vector
				{
					
					if(ch[i] == upperCaseAlpha[s] || ch[i] == lowerCaseAlpha[s]) //vector index checked with char array indexes
					{
						counter++;	
					}
				}
			cout << getpid() << " " << upperCaseAlpha[s] << " or " << lowerCaseAlpha[s] << ": " << counter << endl;

			exit(0); //exit out of child process each time
		}
		else
		{
			wait(NULL);
		}	
	}
	cout << "~~~~~~~~~~~~~~~~~~~~After fork~~~~~~~~~~~~~~~~~~~~" << endl;
}
void readFromfile(int argCounter, char *argv[])
{

	vector<char> letterV;	//vector for characters in file

	if(argCounter !=2) //if command line arg is not two
	{
		cout << "ERROR: Incorrect number of arguments" << endl; //error message
		cout << "Enter another command." << endl;
		exit(0);

	}
	else
	{
		FILE *filePointer;	//file pointer
		char ch; //used for characters in file
		string commandLineInput; //string for commandline arguments(filename)
		commandLineInput = argv[1];	//reads second argument from command line
		filePointer = fopen(commandLineInput.c_str(), "r"); //open user specified file
		
		if(filePointer == NULL) //file doesn't exit
		{
			cout << "ERROR: Invalid file name." << endl;
			exit(0);
		}	
		while(1)
		{
			
			ch = fgetc(filePointer); //puts file into char
			if(ch == EOF)
			{
				break;
			}
			
			letterV.push_back(ch); //puts each char into a vector starting at last index
		}

		forkIt(letterV);

		fclose(filePointer);
	}
}
int main (int argc, char *argv[])
{
	readFromfile(argc, argv);

	exit(0);
}
