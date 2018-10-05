#include <iostream>
#include <string>
#include <cassert>
#include <cctype>
using namespace std;

int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);
int positionOfMax(const string a[],int n);
int rotateLeft(string a[], int n, int pos);
int countRuns(const string a[], int n);
int flip(string a[], int n);
int differ(const string a1[],int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int split(string a[], int n, string splitter);
void display(string a[], int len);

int main()
{
    string people[5]={"clark","peter","diana","tony","selina"};
    assert(appendToAll(people,5,"!!!")==5);
    assert(appendToAll(people,3,"???")==3);
    assert(appendToAll(people,0,"...")==0);
    assert(appendToAll(people,-3,"///")==-1);
    display(people,5);
    string names[6]={"Noah","Rishab","Athu","Pali","Rishab","Rishab"};
    assert(lookup(names,-3,"Ammar")==-1);
    assert(lookup(names,0,"Ammar")==-1);
    assert(lookup(names,3,"Pali")==-1);
    assert(lookup(names,6,"Athu")==2);
    assert(lookup(names,6,"AThU")==-1);
    assert(positionOfMax(names,6)==1);
    assert(positionOfMax(names,0)==-1);
    assert(positionOfMax(names,-3)==-1);
    assert(rotateLeft(names,6,3)==3);
    display(names,6);
    assert(rotateLeft(names,4,2)==2);
    display(names,6);
    assert(rotateLeft(names,3,4)==-1);
    assert(rotateLeft(names,0,0)==-1);
    assert(rotateLeft(names,-3,0)==-1);
    string names2[7]={"Rohan","Rohan","Rohan","Rishan","Zaid","Akshay","Akshay"};
    assert(countRuns(names2,4)==2);
    assert(countRuns(names2, 7)==4);
    assert(countRuns(names2,0)==0);
    assert(countRuns(names2,-3)==-1);
    assert(flip(names2,7)==7);
    display(names2,7);
    assert(flip(names2,3)==3);
    display(names2,7);
    assert(flip(names2,0)==0);
    display(names2,7);
    assert(flip(names2,-3)==-1);
    string folks[6]={"bruce", "steve", "", "tony", "sue", "clark"};
    string group[5]={"bruce", "steve", "clark", "", "tony"};
    assert(differ(folks,6,group,5)==2);
    assert(differ(folks,4,group,2)==2);
    assert(differ(folks,-3,group,2)==-1);
    assert(differ(folks,0,group,2)==0);
    string names3[10]={"logan","reed","sue","selina","bruce","peter"};
    string names4[10]={"reed","sue","selina"};
    assert(subsequence(names3, 6, names4, 3)==1);
    string names5[10]={"logan","selina"};
    assert(subsequence(names3, 6, names5, 2)==-1);
    string names6[0];
    assert(subsequence(names3,6,names6,0)==0);
    assert(subsequence(names3,6,names4,0)==0);
    string names7[3]={"bruce","peter","sue"};
    assert(subsequence(names3,6,names7,3)==-1);
    assert(lookupAny(names3, 6, names7, 3)==2);
    assert(lookupAny(names3,6,names6,0)==-1);
    assert(lookupAny(names3, 6, names, 4)==-1);
    assert(lookupAny(names5, 2, names7, 3)==-1);
    assert(split(names3,4,"quirky")==1);
    display(names3,6);
    assert(split(names3,6,"quirky")==3);
    display(names3,6);
    assert(split(names3,6,"zeal")==6);
    display(names3,6);
    assert(split(names3,-3,"zeal")==-1);
    assert(split(names3,0,"zeal")==0);
    string names8[6]={"rock","paper","scissors"," ", "rock","rock"};
    assert(split(names8,6,"rock")==2);
    display(names8,6);
}

//Appends value to the end of each of the n elements of the array and returns n
int appendToAll(string a[], int n, string value)
{
    if(n<0) //bad argument passed
        return -1;
    for(int i=0;i<n;i++)
    {
        a[i]+=value;
    }
    return n;
}

//Returns the position of a string in the array that is equal to target
int lookup(const string a[], int n, string target)
{
    if(n<0) //bad argument passed
        return -1;
    for(int i=0;i<n;i++)
    {
        if(a[i]==target)
            return i;
    }
        return -1; //string equal to target not found
}

//Returns the position of a string in the array such that that string is >= every string in the array
int positionOfMax(const string a[],int n)
{
    string max="";
    int pos = 0;
    if(n<=0) //Bad argument or has no elements
        return -1;
    max=a[0]; //variable that stores largest string (in terms of character encoding)
    for(int i=0;i<n;i++)
    {
        if(a[i]>max) //stores max only if string is greater than current max
        {
            max=a[i];
            pos=i; //stores position of max string
        }
    }
    return pos;
}

/* Eliminates the item at position pos by copying all elements after it one place to the left. The item that was thus eliminated is put into the last position of the array. Return the original position of the item that was moved to the end. */
int rotateLeft(string a[], int n, int pos)
{
    string temp=""; //temporary variable to faciliate swapping of values
    if(n<=0) //Bad argument or has no elements
        return -1;
    if(pos>=n) //if pos is beyond the range of interesting elements in the array
        return -1;
    for(int i=pos;i<n-1;i++) /* pos is moved to the end of the n interesting elements in the array and all other elements are moved one index to the left. */
    {
        temp=a[i];
        a[i]=a[i+1];
        a[i+1]=temp;
    }
    return pos;
}

//Returns the number of sequences of one or more consecutive identical items in a
int countRuns(const string a[], int n)
{
    string current=""; //stores current string sequence
    int cnt=0; //counts number of sequences
    if(n<0) //bad argument passed
        return -1;
    for(int i=0;i<n;i++)
    {
        if(current!=a[i]) //if it is a new string sequence
        {
            current=a[i]; //stores new string sequence
            cnt++;
        }
    }
    return cnt;
}

//Reverse the order of the elements of the array and return n
int flip(string a[], int n)
{
    string temp=""; //temporary variable to facilitate the swapping of values
    if(n<0) //bad argument passed
        return -1;
    for(int i=0,j=n-1;i<n/2;i++,j--) //swaps the values from each end of the array
    {  //i starts from the beginning of the array and j from the end of the array
            temp=a[i];
            a[i]=a[j];
            a[j]=temp;
    }
    return n; //returns the number of interesting elements
}

/* Returns the position of the first corresponding elements of a1 and a2 that are not equal. If the arrays are equal up to the point where one or both runs out, return whichever value of n1 and n2 is less than or equal to the other */
int differ (const string a1[], int n1, const string a2[], int n2)
{
    int smaller=n1; //stores the smaller of the numbers
    if(n1<0 || n2<0) //bad arguments passed
        return -1;
    if(n2<n1)
        smaller=n2;
    for(int i=0;i<smaller;i++)
    {
        if(a1[i]!=a2[i]) //Finds first position of inequality
            return i;
    }
    return smaller; //We treat an array with 0 interesting elements as an array that has run out
}

/* If all n2 elements of a2 appear in a1, consecutively and in the same order, then return the position in a1 where that subsequence begins */
int subsequence(const string a1[], int n1, const string a2[], int n2)
{
    int k,j;
    if(n1<0 || n2<0) //bad arguments passed
        return -1;
    //a sequence of 0 elements is a subsequence of any sequence, even one with no elements.
    if(n2==0)
        return 0;
    if(n2>n1) //Sequence cannot be a subsequence of another sequence if it is bigger than it
        return -1;
    for(int i=0;i<n1;i++)
    {
        bool subsequenceMatch=true;
        for(j=i, k=0;k<n2 && j<n1;k++,j++) //check for subsequence from i position
        {
            if(a2[k]!=a1[j])
            {
                subsequenceMatch=false;
                break;
            }
        }
        if(k!=n2) //if the complete subsequence wasn't checked
            continue;
        else if(subsequenceMatch)
            return i;
    }
    return -1; //if a1 doesn't contain a2 as a subsequence
}

/* Return the smallest position in a1 of an element that is equal to any of the elements in a2 */
int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
    if(n1<0 || n2<0) //bad arguments passed
        return -1;
    for(int i=0;i<n1;i++)
    {
        for(int j=0;j<n2;j++)
        {
            if(a2[j]==a1[i])//checks for equality of all character in a2 with each character in a1
                return i;
        }
    }
    return -1;
}

/* Rearrange the elements of the array so that all the elements whose value is < splitter come before all the other elements and all the elements whose value is > splitter come after all the other elements. Return the position of the first element that, after the rearrangement, is not < splitter, or n if there are no such elements */
int split(string a[], int n, string splitter)
{ //We treat an array with 0 interesting elements as an array with no elements >= splitter
    if(n<0)
        return -1; //bad arguments passed
    bool flag=true;
    string temp=""; //temporary variable to facilitate swapping
    while(flag) //sorting of elements
    {
        flag=false;
        for(int i=0;i<n-1;i++)
        {
            if(a[i]>a[i+1])
            {
                temp=a[i];
                a[i]=a[i+1];
                a[i+1]=temp;
                flag=true;
            }
        }
    }
    for(int i=0;i<n;i++) //check for the first element that is not < splitter after rearrangement
    {
        if(a[i]>=splitter)
            return i; //returns position of that element
    }
    return n; // return number of interesting elements if no such element is found
}

void display(string a[], int len)
{
    for(int i=0;i<len;i++)
    {
        cerr << a[i] << " " ;
    }
    cerr << endl;
}


