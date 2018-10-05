#include "utilities.h"
#include <iostream>
#include <cstring>
#include <string>
#include <cctype>
using namespace std;

const char WORDFILENAME[] = "/Users/rishabsukumar/Documents/Rishab/UCLA/CS 31/stars/P5words.txt"; // Word file from which valid words used by the game are obtained
int runOneRound(const char words[][7], int nWords, int wordnum);
int main()
{
    char w[9000][7]; /* Create an array with the capacity to hold 9000 C Strings of a max length of 7 characters */
    int nWords = getWords(w, 9000, WORDFILENAME); /* stores the words in a text file in the array of C strings and stores the number of interesting words in the variable nWords */
    if (nWords < 1) //If there were no words in the text file
        cout << "No words were loaded, so I can't play the game." << endl;
    else
    {
        cout << "How many rounds do you want to play? ";
        int rounds;
        cin >> rounds; // stores number of rounds to be played
        cin.ignore(10000,'\n'); // ignores all characters until a newline character is reached
        double average=0;
        int total=0;
        int min=0;
        int max=0;
        if(rounds<=0) //If the user wants 0 or less rounds to be played
            cout << "The number of rounds must be positive." << endl;
        else
        {
            for(int i=1;i<=rounds;i++) /* run loop as many times as the number of rounds user enters */
            {
                cout << endl; // Empty line printed
                cout << "Round " << i << endl; // Display ongoing round
                int wordnum=randInt(0, nWords-1); /* Generate a random int to randomize secret word for the round */
                int wordLen=strlen(w[wordnum]); //stores length of secret word
                cout << "The secret word is " << wordLen << " letters long." << endl;
                int tries=runOneRound(w,nWords,wordnum); // calls function to run the round
                if(i==1) /* If it is the first round, initialize min and max to the number of tries */
                {
                    min=tries;
                    max=tries;
                }
                else if(tries>max) /* changes value of max number of tries if tries is greater than previous max */
                    max=tries;
                else if(tries<min) /* changes value of min number of tries if tries is smaller than previous min */
                    min=tries;
                total+=tries; // stores total for average calculation
                average=static_cast<double>(total)/i; /* type casts total to double and finds thee average for i number of rounds */
                if(tries==-1)
                    cerr << "There was an error in the text file." << endl;
                else if(tries>1) // for formatting
                    cout << "You got it in " << tries << " tries." << endl;
                else // for formatting
                    cout << "You got it in " << tries << " try." << endl;
                cout.setf(ios::fixed);
                cout.precision(2); /* precision of the double average is set to 2 decimal places */
                cout << "Average: " << average << ", minimum: " << min << ", maximum: " << max << endl; // display statistics of each round
            }
        }
    }
}

/* runOneRound is a function that runs through one round of the game an returns the number of tries the user takes to find the right word */
int runOneRound(const char words[][7], int nWords,int wordnum)
{
    if(nWords<=0 || wordnum<0 || wordnum>=nWords) /* if number of words are less than or equal to 0 and position of secret word is outside of the interesting elements in the array */
        return -1;
    bool validPrompt=true; // bool variable to check if prompt is valid
    int tries=0; // stores number of tries
    
    for(;;)
    {
        char prompt[100]; // C string to hold user's prompt
        int s=0; // stores number of stars
        int p=0; // stores number of planets
        validPrompt=true;
        cout << "Probe word: " ;
        cin.getline(prompt,100); // accepts user's input and stores it in C string prompt
        if(strlen(prompt)<4 || strlen(prompt)>6) //prompt must be between 4 and 6 characters
        {
            cout << "Your probe word must be of 4 to 6 lower case letters." << endl;
            continue;
            
        }
        for(int i=0;i<strlen(prompt);i++)
        {
            if(! isalpha(prompt[i]) || ! islower(prompt[i])) /* Prompt must only contain lower case alphabets */
            {
                cout << "Your probe word must be of 4 to 6 lower case letters." << endl;
                validPrompt=false; // change bool variable to false
                break;
            }
        }
        if(! validPrompt)
            continue;
        
        bool validWord=false; // bool variable to check if word exists in array of C strings
        for(int i=0;i<nWords;i++) // loop to check if word exists in array of C strings
        {
            if(! strcmp(prompt,words[i])) // to check equality
            {
                validWord=true;
                break;
            }
        }
        if(! validWord)
        {
            cout << "I don't know that word." << endl;
            continue;
        }
        tries++; // increment number of tries
        int size=strlen(words[wordnum]); //stores size of secret word
        int index[7]; /* creates an array to store index of characters already found to be a star or a planet */
        for(int i=0;i<size;i++) // initializes all positions of index array
        {
            index[i]=-1;
        }
        bool check=false; /* bool variable to check if character has already been found to be a planet or a star */
        bool p_maybe_s=false; /* bool variable to check if character found to be a planet may also be a star in a different position, i.e. if the character is repeated in a position where it is a star */
        int k=0;
        for(int i=0;i<strlen(prompt);i++) // runs loop to parse through characters in prompt
        {
            for(int j=0;j<size;j++) // runs loop to parse through characters in secret word
            {
                check = false; // initialize bool variable to false
                p_maybe_s=false; // initialize bool variable to false
                for(int l=0;l<size;l++) /* runs loop to check if character in position j has already been found to be a planet or a star */
                {
                    if(index[l]==j)
                    {
                        check=true;
                    }
                }
                if(! check && prompt[i]==words[wordnum][j] && i==j) /* if character in prompt is the same as character in secret word and in the same position, it is a star */
                {
                    s++; // increment stars
                    index[k++]=j; // store index of star in array of indexes
                    break;
                }
                else if(! check && prompt[i]==words[wordnum][j] && i!=j) /* if character in prompt is the same as character in secret word but not in the same position, it is a planet */
                {
                    if(i>j) /* if character in prompt is at a later position than the character in the secret word */
                    {
                        for(int m=j+1;m<size;m++) /* parses through remaining characters in secret word to check if the planet may actually be a star */
                        {
                            if(prompt[i]==words[wordnum][m] && i==m) /* if current char is a star */
                            {
                                p_maybe_s=true;
                                index[k++]=m; // store index of star in array of indexes
                                break;
                            }
                        }
                    }
                    else /* if character in prompt is at an earlier position than the character in the secret word */
                    {
                        for(int o=i+1;o<strlen(prompt);o++) /* parses through remaining character in prompt to see if any other character might be a star */
                        {
                            if(prompt[i]==prompt[o] && prompt[o]==words[wordnum][j] && o==j)
                            {  // if character is a star in another position in prompt
                                index[k++]=j; // store index of star in array of indexes
                                p_maybe_s=true;
                                break;
                            }
                        }
                    }
                    if(p_maybe_s) // if planet is a star in another position
                    {
                        s++; // increment stars
                        break;
                    }
                    else
                    {
                        p++; // increment planets
                        index[k++]=j; // store index of star in array of indexes
                        break;
                    }
                }
            }
        }
        if(strcmp(prompt,words[wordnum])) // display number of stars and planets
            cout << "Stars: " << s << ", Planets: " << p << endl;
        else if(! strcmp(prompt,words[wordnum])) /* if prompt is the secret word return number of tries */
        {
            return tries;
        }
    }
    
}


