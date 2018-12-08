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



HashNode::HashNode(string key, string value)
{
        this->key = key;
        this->value = value;
}

string HashNode::getKey()
{
		return this->key;
}
		
string HashNode::getValue()
{
		return this->value;
}
		
		



//------------------------ SEPARATION ------------------------//



		
HashMap::HashMap() 
{
}

HashMap::HashMap(long capacity)
{
    nodeArray = new HashNode*[capacity];
    this->capacity = capacity;
    this->size = 0;
}

long HashMap::hashCode(const string key)
{
    long sum=0;
    for(long i=0; i<key.length(); i++)
        sum+=pow(2,i)*long(key[i]);
    return sum%(this->capacity);
}

void HashMap::insert(const string key, const string value)
{
    HashNode *tempNode= new HashNode(key,value);
    long index = hashCode(key);
    while(nodeArray[index]!=NULL)
    {
        index = (index+1) % this->capacity;
    }

    nodeArray[index] = tempNode;
    this->size++;
}

void HashMap::insertByInput(const string input, bool isNameMap) 
{
    string line = input;
    long numInputs=7;
    string arr[numInputs];
        long i = 0;
        stringstream ssin(line);
            while (ssin.good() && i < numInputs) 
            {
                ssin >> arr[i];
                ++i;
            }
    if(isNameMap) 
    {
        string fullName = arr[0] + " " + arr[1];
        string values = arr[2] + " " + arr[3] + " " + arr[4] + " " + arr[5] + " " + arr[6];
        this->insert(fullName,values);
    } else 
    {
        string city = arr[4];
        string values = arr[0] + " " + arr[1] + " " + arr[2] + " " + arr[3] + " " + arr[5] + " " + arr[6];
        this->insert(city,values);
    }
}

string HashMap::search(const string key)
{

    long index = hashCode(key);
    long counter = 0;
    string restring;

    while(nodeArray[index] != NULL && counter < this->capacity)
    {
        if (nodeArray[index]->getKey() == key)
        {			
            restring = restring + string(nodeArray[index]->getValue()) + "\n";
        }
        
        index = (index+1) % this->capacity;
        counter ++;
        
    }

    if(restring != "")
    {
        string comparison =  "(comparisons = " + to_string(counter) + ")";
        restring = restring + comparison;		
        return restring;	
    }else
    {
        return "Customer in the city are not found";
    }
}

bool HashMap::deleteMember(const string key2) 
{
    long index2 = this->hashCode(key2);
    long counter2 = 0;
    string restring;
    bool deleted=false;

    while(this->nodeArray[index2] != NULL && counter2 < this->capacity)
    {
        if (this->nodeArray[index2]->getKey() == key2)
        {	
            this->nodeArray[index2]=NULL;
            deleted=true;
            break;
        }
        cout<<"REACHED" <<endl;
        index2 = (index2+1) % this->capacity;
        counter2 ++;
        
    }
    return deleted;
}

string HashMap::MemberKeyToCityKey(const string key3) 
{
    long index2 = hashCode(key3);
    long counter2 =0;
    string restring;
    string result="";
    while(this->nodeArray[index2] != NULL && counter2 < this->capacity)
    {
        if (this->nodeArray[index2]->getKey() == key3) 
        {			
            string line = this->nodeArray[index2]->getValue();
            string arr[5];
            long i = 0;
            stringstream ssin(line);
                while (ssin.good() && i < 5) 
                {
                    ssin >> arr[i];
                    ++i;
                }
                result = arr[2];
                break;
        }
        index2 = (index2+1) % this->capacity;
        counter2 ++;
    }
    return result;
}

map<string, string>  HashMap::dump(const string filename)
{//need to be in sorted order
        map<string, string> orderedMap; 
        
        long index = 0;
        while(index < this->capacity){
        
            if(this->nodeArray[index] != NULL){
                //cout << this->nodeArray[index]->getKey() <<  " " << this->nodeArray[index]->getValue() << endl;
                orderedMap.insert(pair<string, string>(this->nodeArray[index]->getKey(), this->nodeArray[index]->getValue())); 
            }
            
            index ++;	
        }	
		return orderedMap;
}

long HashMap::getSize()
{
    return this->size;
}

HashMap::~HashMap()
{
    delete[] this->nodeArray;
}
