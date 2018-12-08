#include "functions.h"
#include<iostream>
#include<fstream>
#include<cmath>
#include<istream>
#include<string>
#include <iterator> 
#include <sstream> 
#include <iterator> 
#include <map> 

using namespace std;



HashNode::HashNode(string key, string value) //Contstructor for HashNode class
{
        this->key = key; //Setting local variables from constructor arguments
        this->value = value; //Setting local variables from constructor arguments
}

string HashNode::getKey() //Get key function to return key of node
{
		return this->key; //returning key
}
		
string HashNode::getValue() //Get key function to return value of node
{
		return this->value; //returning value
}
		
HashMap::HashMap() //Empty Constructor
{
}

HashMap::HashMap(int capacity) //Hashmap Constructor with capacity argument
{
    nodeArray = new HashNode*[capacity]; //initializing array of HashNodes
    this->capacity = capacity; //Setting the capacity local variable to capacity argument
    this->size = 0;
}

int HashMap::hashCode(const string key) //Function that converts key string to hashcode
{
    long sum=0; //sum equals zero
    for(int i=0; i<key.length(); i++)
        sum+=pow(2,i)*int(key[i]);
    return sum%(this->capacity);
}

void HashMap::insert(const string key, const string value)
{
    HashNode *tempNode= new HashNode(key,value);
    int index = hashCode(key);
    while(nodeArray[index]!=NULL) //A while loop to iterate through the hashmap
    {
        index = (index+1) % this->capacity;
    }

    nodeArray[index] = tempNode;
    this->size++; //Increment the counter by one for this function
}

void HashMap::insertByInput(const string input, bool isNameMap) //Function for user to add their own users to our data structure
{
    string line = input;
    int numInputs=7;
    string arr[numInputs];
        int i = 0;
        stringstream ssin(line);//Take the line string as an input
            while (ssin.good() && i < numInputs) //Go through the string
            {
                ssin >> arr[i]; //Insert into array after every space
                ++i; //Increment the i value
            }
    if(isNameMap) //If argument isNameMap is true
    {
        string fullName = arr[0] + " " + arr[1]; //Array concatenation for full name
        string values = arr[2] + " " + arr[3] + " " + arr[4] + " " + arr[5] + " " + arr[6]; //Array concatenation for value
        this->insert(fullName,values);
    } else //If argument isNameMap is false
    {
        string city = arr[4]; //Array concatenation for city
        string values = arr[0] + " " + arr[1] + " " + arr[2] + " " + arr[3] + " " + arr[5] + " " + arr[6]; //Array concatenation for value
        this->insert(city,values);
    }
}

string HashMap::search(const string key)
{

    int index = hashCode(key);
    int counter = 0;
    string restring;

    while(nodeArray[index] != NULL && counter < this->capacity) //A while loop to iterate through the hashmap
    {
        if (nodeArray[index]->getKey() == key)
        {			
            restring = restring + string(nodeArray[index]->getValue()) + "\n";
        }
        
        index = (index+1) % this->capacity;
        counter ++; //Increment the counter by one for this function
        
    }

    if(restring != "")
    {
        string comparison =  "(comparisons = " + to_string(counter) + ")";
        restring = restring + comparison;		
        return restring;	
    }else
    {
        return "Record Not Found"; //Error message for the user
    }
}

bool HashMap::deleteMember(const string key2) 
{
    int index2 = this->hashCode(key2);
    int counter2 = 0;
    string restring;
    bool deleted=false; //Deleted bool to keep track of key deletion

    while(this->nodeArray[index2] != NULL && counter2 < this->capacity) //A while loop to iterate through the hashmap
    {
        if (this->nodeArray[index2]->getKey() == key2) //If current node key is the same as the key provided by user(arg)
        {	
            this->nodeArray[index2]=NULL; //Set the node to null, effectively deleting it
            deleted=true; //Set deleted boolean to true
            break;
        }
        //cout<<"REACHED" <<endl;
        index2 = (index2+1) % this->capacity;
        counter2 ++; //Increment the counter by one for this function
        
    }
    return deleted; // Returning the result of this function which is a bool
}

string HashMap::MemberKeyToCityKey(const string key3) 
{
    int index2 = hashCode(key3);
    int counter2 =0;
    string restring;
    string result="";
    while(this->nodeArray[index2] != NULL && counter2 < this->capacity) //A while loop to iterate through the hashmap
    {
        if (this->nodeArray[index2]->getKey() == key3) //If the key is the same as the node array key
        {			
            string line = this->nodeArray[index2]->getValue();
            string arr[5];
            int i = 0;
            stringstream ssin(line); //Use the string as a line input stream
                while (ssin.good() && i < 5) 
                {
                    ssin >> arr[i]; //Seperate and insert into array by space
                    ++i; //Incrementing the counter i by one
                }
                result = arr[2]; //Returning the city key from the name key
                break; //Break to save time complexity
        }
        index2 = (index2+1) % this->capacity;
        counter2 ++; //Increment the counter by one for this function
    }
    return result; // Returning the result of this function which is a string
}

void HashMap::dump(const string filename){
		    
		    
		    map<string, string> orderedMap; 
		    int index = 0;
		    cout << this->size << endl;
			while(index < this->capacity) //A while loop to iterate through the hashmap
			{ 
			    if(this->nodeArray[index]!= NULL) //If the current node is not NULL/empty
			    {
				    cout << this->nodeArray[index]->getKey() <<  " " << this->nodeArray[index]->getValue() << endl;
				    orderedMap.insert(pair<string, string>(this->nodeArray[index]->getKey(), this->nodeArray[index]->getValue()));           
                }
                
				index ++; //Increment the counter by one for this function
			}	
			
		    ofstream myfile(filename, std::ios::trunc);
		    map<string, string>::iterator itr; 
	        for (itr = orderedMap.begin(); itr != orderedMap.end(); ++itr) { 
                //cout <<  itr->first << " " << itr->second << endl; 
                myfile << itr->first + " " + itr->second << endl;
            } 
			
			myfile.close(); 

		}


int HashMap::getSize() //Function for HashMap class to return size
{
    return this->size;
}

HashMap::~HashMap()
{
    delete[] this->nodeArray;
}
