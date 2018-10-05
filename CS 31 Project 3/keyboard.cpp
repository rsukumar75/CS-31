#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
using namespace std;

//Function to check for validity of song string syntax. Returns boolean value.
bool hasCorrectSyntax(string song)
{
    if(song.size()==0) //An empty string has valid syntax
        return true;
    bool hasCharacter=false;
    bool hasSpace=false;
    for(int i=0;i<song.size();i++)
    {
        if(song[i]!=' ') //Check if the song string is empty (only spaces)
        {
            hasCharacter=true;
        }
        if(song[i]==' ')
        {
            hasSpace=true;
        }
        if(isalpha(song[i]) && (song[i]!='b') && ((song[i]<'A') || ((song[i]>'G')))) //Check to see if notes are only A,B,C,D,E,F,G
        {
            return false;
        }
        if(isdigit(song[i]) && ((song[i]-'0') < 0 || (song[i]-'0') > 9)) //Check to see if octave is within range
        {
            return false;
        }
        if(((song[i]== '#' || song[i]=='b' || isdigit(song[i])) && (i==0)) || ((song[i]== '#' || song[i]=='b') && isdigit(song[i-1])))
        {// Accidental sign cannot be the first character and cannot follow a digit. Digit cannot be the first character either
            return false;
        }
        if(islower(song[i]) && song[i] != 'b') //Check for lower case notes
        {
            return false;
        }
        if(! isalpha(song[i]) && (! isdigit(song[i])) && song[i] != '/' && song[i] != '#' && song[i]!= ' ') //Check for special characters apart from '/' and '#'
        {
            return false;
        }
        if(i!=song.size()-1) // to prevent undefined behaviour
        {
            if(isdigit(song[i]) && isdigit(song[i+1])) //Check for repeating numbers
            {
                return false;
                
            }
            if((song[i]=='#' || song[i]=='b') && (song[i+1]=='#' || song[i+1]=='b')) //Check for repeating accidental signs
            {
                return false;
                
            }
        }
        
    }
    if(hasCharacter)
    {
        if(hasSpace) // If the song string has spaces within it, it has invalid syntax
            return false;
    }
    if(! hasCharacter) //Empty song string is valid
        return true;
    if(song[song.size()-1]!='/') //The last character must denote a beat
        return false;
    return true;
}

//*************************************
//  encodeNote
//*************************************

// Given an octave number, a note letter, and an accidental sign, return
// the character that the indicated note is encoded as if it is playable.
// Return a space character if it is not playable.
//
// First parameter:   the octave number (the integer 4 is the number of the
//                    octave that starts with middle C, for example).
// Second parameter:  an upper case note letter, 'A' through 'G'
// Third parameter:   '#', 'b', or ' ' (meaning no accidental sign)
//
// Examples:  encodeNote(4, 'A', ' ') returns 'Q'
//            encodeNote(4, 'A', '#') returns '%'
//            encodeNote(4, 'H', ' ') returns ' '


char encodeNote(int octave, char noteLetter, char accidentalSign)
{
    // This check is here solely to report a common CS 31 student error.
    if (octave > 9)
    {
        cerr << "********** encodeNote was called with first argument = " << octave << endl;
    }
    
    // Convert Cb, C, C#/Db, D, D#/Eb, ..., B, B#
    //      to -1, 0,   1,   2,   3, ...,  11, 12
    
    int note;
    switch (noteLetter)
    {
        case 'C':
            note =  0;
            break;
        case 'D':
            note =  2;
            break;
        case 'E':
            note =  4;
            break;
        case 'F':
            note =  5;
            break;
        case 'G':
            note =  7;
            break;
        case 'A':
            note =  9;
            break;
        case 'B':
            note = 11;
            break;
        default:
            return ' ';
    }
    switch (accidentalSign)
    {
        case '#':
            note++;
            break;
        case 'b':
            note--;
            break;
        case ' ':
            break;
        default:
            return ' ';
    }
    
    // Convert ..., A#1, B1, C2, C#2, D2, ... to
    //         ..., -2,  -1, 0,   1,  2, ...
    
    int sequenceNumber = 12 * (octave - 2) + note;
    
    string keymap = "Z1X2CV3B4N5M,6.7/A8S9D0FG!H@JK#L$Q%WE^R&TY*U(I)OP";
    if (sequenceNumber < 0  ||  sequenceNumber >= keymap.size())
        return ' ';
    return keymap[sequenceNumber];
}

//Function goes through song string entered as a parameter and returns the beat of unplayable note
//If the song string is playable, the function returns -1
int isPlayable(string song)
{
    if(! hasCorrectSyntax(song)) //A syntactically wrong song string is not playable
        return 0;
    char note=' ';
    char accidentalSign=' ';
    int octave=-1;
    bool ongoingNote=false;
    int beat=1;
    for(int i=0;i<song.size();i++)
    {
        if(song[i]=='/' && i!=song.size()-1) //Keeps track of the beat being checked
            beat++;
        if(isalpha(song[i]) && (song[i]!='b') && (! ongoingNote)) //store the note
        {
            note=song[i];
            ongoingNote=true;
        }
        else if((isalpha(song[i]) && (ongoingNote) && (song[i]!='b')) || song[i]=='/') //end of a note
        {
            ongoingNote=false;
            if(octave==-1) //if no octave digit was entered
                octave=4;
            if(octave<2 || octave>5) //if the octave is beyond what ButtonBass can play
            {
                if(note=='C' && accidentalSign=='b' && octave==6)// Cb6 is a playable note
                {
                    if(isalpha(song[i])) //stores next note
                    {
                        note=song[i];
                        ongoingNote=true;
                    }
                    else
                        note=' '; //reinitialising note, octave and accidentalSign
                    octave=-1;
                    accidentalSign=' ';
                    continue;
                }
                else if(note=='B' && accidentalSign=='#' && octave==1) //B#1 is a playable note
                {
                    if(isalpha(song[i])) //stores next note
                    {
                        note=song[i];
                        ongoingNote=true;
                    }
                    else
                        note=' '; //reinitialising note, octave and accidentalSign
                    octave=-1;
                    accidentalSign=' ';
                    continue;
                }
                else if(note=='C' && accidentalSign==' ' && octave==6) // C6 is a playable note
                {
                    if(isalpha(song[i])) //stores next note
                    {
                        note=song[i];
                        ongoingNote=true;
                    }
                    else
                        note=' '; //reinitialising note, octave and accidentalSign
                    octave=-1;
                    accidentalSign=' ';
                    continue;
                }
                else
                {
                    if(i!=song.size()-1 && song[i]=='/')
                        beat--;
                    return beat;
                }
            }
            else
            {
                if(note=='C' && accidentalSign=='b' && octave==2) //Cb2 is not a playable note
                {
                    if(i!=song.size()-1 && song[i]=='/')
                        beat--;
                    return beat;
                }
            }
            if(isalpha(song[i])) //stores next note
            {
                note=song[i];
                ongoingNote=true;
            }
            else
                note=' '; //reinitialising note, octave and accidentalSign
            octave=-1;
            accidentalSign=' ';
        }
        else if(isdigit(song[i])) //store octave of note
            octave=song[i] - '0';
        else if(song[i]=='#' || song[i]=='b') // store accidental sign
            accidentalSign=song[i];
        else
            continue;
    }
    return -1;
}

//Function runs through the song string passed as argument and encodes the characters if it is playable
//If the song string has invalid syntax it returns 1
/* If the song string has valid syntax but is unplayable it returns 2 and stores the beat with the unplayable note in badBeat */
/* If the song string is playable, it returns 0 and encodes the string and stores the encoded string in instructions */
int encodeSong(string song, string& instructions, int& badBeat)
{
    if(! hasCorrectSyntax(song)) //Not a valid song string
        return 1;
    else if(hasCorrectSyntax(song) && isPlayable(song)!=-1) // valid song string but is not playable
    {
        badBeat=isPlayable(song);
        return 2;
    }
    else
    {
        instructions="";
        char note=' ';
        char accidentalSign=' ';
        int octave=-1;
        bool ongoingNote=false;
        int numberOfNotes=0;
        int pos=0;
        int k=0;
        bool hasCharacter=false;
        for(int i=0;i<song.size();i++)
        {
            if(song[i]!=' ') //Check if the song string is empty (only spaces)
            {
                hasCharacter=true;
            }
        }
        if(! hasCharacter) //If it is empty
            return 0;
        while(pos<song.size())
        {
            while(song[pos]!='/')
            {
                if(isalpha(song[pos]) && song[pos]!='b') //counting number of notes in each beat
                   numberOfNotes++;
                pos++;
            }
            if(numberOfNotes==0) //An empty beat is encoded as a space
                instructions+=" ";
            else if(numberOfNotes>1) //If there are multiple notes in a beat, they are encoded within square brackets
                instructions+="[";
            for(;k<=pos;k++)
            {
                if(isalpha(song[k]) && (song[k]!='b') && (! ongoingNote)) //store the note
                {
                    note=song[k];
                    ongoingNote=true;
                }
                else if((isalpha(song[k]) && (ongoingNote) && (song[k]!='b')) || (song[k]=='/' && note!= ' ')) //end of a note
                {
                    if(octave==-1)
                        octave=4;
                    instructions+=encodeNote(octave, note, accidentalSign); //encoding the note
                    ongoingNote=false;
                    if(isalpha(song[k]))
                    {
                        note=song[k];
                        ongoingNote=true;
                    }
                    else
                        note=' ';
                    octave=-1;
                    accidentalSign=' ';
                }
                else if(isdigit(song[k])) //store octave of note
                    octave=song[k] - '0';
                else if(song[k]=='#' || song[k]=='b') // store accidental sign
                    accidentalSign=song[k];
            }
            if(numberOfNotes>1)
                instructions+="]";
            numberOfNotes=0;
            pos++;
            
        }
    }
    return 0;
}

//Test if the functions work for various song strings
int main()
{
    string song="";
    string instructions="123";
    int badBeat=232;
    assert(encodeSong("",instructions,badBeat)==0);
    cout << instructions << endl;
    cout << badBeat << endl;
    assert(encodeSong("///",instructions,badBeat)==0);
    cout << instructions << endl;
    cout << badBeat << endl;
    assert(encodeSong("????",instructions,badBeat)==1);
    cout << instructions << endl;
    cout << badBeat << endl;
    assert(encodeSong("  ",instructions,badBeat)==0);
    cout << instructions << endl;
    cout << badBeat << endl;
    assert(encodeSong("A  B/",instructions,badBeat)==1);
    cout << instructions << endl;
    cout << badBeat << endl;
    assert(encodeSong("A3B/C",instructions,badBeat)==1);
    cout << instructions << endl;
    cout << badBeat << endl;
    assert(encodeSong("3/",instructions,badBeat)==1);
    cout << instructions << endl;
    cout << badBeat << endl;
    assert(encodeSong("#/",instructions,badBeat)==1);
    cout << instructions << endl;
    cout << badBeat << endl;
    assert(encodeSong("b/",instructions,badBeat)==1);
    cout << instructions << endl;
    cout << badBeat << endl;
    assert(encodeSong("A5/B3c4/",instructions,badBeat)==1);
    cout << instructions << endl;
    cout << badBeat << endl;
    assert(encodeSong("A4/B33D2/",instructions,badBeat)==1);
    cout << instructions << endl;
    cout << badBeat << endl;
    assert(encodeSong("B3/C#b4D/",instructions,badBeat)==1);
    cout << instructions << endl;
    cout << badBeat << endl;
    assert(encodeSong("B3/C##4D/",instructions,badBeat)==1);
    cout << instructions << endl;
    cout << badBeat << endl;
    assert(encodeSong("B3/Cbb4D/",instructions,badBeat)==1);
    cout << instructions << endl;
    cout << badBeat << endl;
    assert(encodeSong("A3B#4/D5Cb2/F5G3/",instructions,badBeat)==2);
    cout << instructions << endl;
    cout << badBeat << endl;
    assert(encodeSong("A4B5/D7G6/C3/",instructions,badBeat)==2);
    cout << instructions << endl;
    cout << badBeat << endl;
    assert(encodeSong("A1B5/G3///",instructions,badBeat)==2);
    cout << instructions << endl;
    cout << badBeat << endl;
    assert(encodeSong("G/",instructions,badBeat)==0);
    cout << instructions << endl;
    cout << badBeat << endl;
    assert(encodeSong("D3/F#3/A3/D4//D3F#3A3D4/",instructions,badBeat)==0);
    cout << instructions << endl;
    cout << badBeat << endl;
    assert(encodeSong("B5C3//D/",instructions,badBeat)==0);
    cout << instructions << endl;
    cout << badBeat << endl;
    assert(encodeSong("A3Bb5/D4Cb6/G/",instructions,badBeat)==0);
    cout << instructions << endl;
    cout << badBeat << endl;
    assert(encodeSong("F3G#5/B#1A3/",instructions,badBeat)==0);
    cout << instructions << endl;
    cout << badBeat << endl;
    assert(encodeSong("G5A3/C6D2/",instructions,badBeat)==0);
    cout << instructions << endl;
    cout << badBeat << endl;
    }
