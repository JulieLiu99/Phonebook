#include<iostream>
#include<fstream>
#include<cmath>
#include<istream>
#include<string>
#include <iterator> 
#include <sstream> //for delete function
#include "functions.h"

using namespace std;


int main(int count, char * args[]){

	ifstream fin;
	bool initiated = false;
	string line;
	string inputFile;
	HashMap cityHashMap;
	HashMap nameHashMap;

    //take as parameters names of the input textfile
    for (int i = 1; i < count; i++) {
        if ((string(args[i]) == "-f") && i + 1 < count)
            inputFile = args[i + 1];
    }
    //remind user of the way to invocate the application
    if (inputFile == "" ) {
       cout << "mymachine-prompt >> ./fonbook -f <filename>" << endl;
        return -1;
    }
    //print out names of the input textfile
    cout << "Input file is " << inputFile << endl;

	
	while(true) {
	    
	    string line;
	    cout << "Enter your command: " << endl;
	    getline(cin, line);
	    string command = line.substr(0, line.find(" "));
	    string key = line.substr(line.find(" ")+1, line.length());
	    
	    if(command=="init") 
	    { 
	    	if(!initiated) 
	    	{
				cityHashMap=HashMap(18000);
				nameHashMap=HashMap(18000);
	    		cout<<"Initiated."<<endl;
	    		initiated=true;
			} else 
			{
				cout<<"Already initiated."<<endl;
			}
			
		    	
		    fin.open(inputFile);
	    	
			if(!fin)
			{
				cout<<"Cannot open the file."<<endl;
			} else 
			{
                while(!fin.eof())
                {
                    string lastName, firstName, address1, address2, city, country, number;
                    getline(fin,lastName,' ');
                    getline(fin,firstName,' ');
                    getline(fin,address1,' ');
                    getline(fin,address2,' ');
                    getline(fin,city,' ');
                    getline(fin,country,' ');
                    getline(fin,number);

                    string key1 = city;
                    string value1 = lastName + " " + firstName + " " + address1 + " " + address2 + " " + country + " " + number;
                    string key2 = lastName + " " + firstName;
                    string value2 = address1 + " " + address2 + " " + city + " " + country + " " + number;
            
                    cout << key1 << " : " << value1 <<endl;
                    cout << key2 << " : " << value2 <<endl;
                    cityHashMap.insert(key1,value1);
                    nameHashMap.insert(key2,value2);
                }
	        }
		fin.close();
		}
	    
	    
	    else if(command=="load") 
	    {
	    	if(initiated) 
	    	{
		    	fin.open(key);
		    	
                if(!fin)
                {
				    cout<<"Cannot open the file."<<endl;
                } 
                else 
                {
                    while(!fin.eof())
                    {
                    string lastName, firstName, address1, address2, city, country, number;
                    getline(fin,lastName,' ');
                    getline(fin,firstName,' ');
                    getline(fin,address1,' ');
                    getline(fin,address2,' ');
                    getline(fin,city,' ');
                    getline(fin,country,' ');
                    getline(fin,number);

                    string key1 = city;
                    string value1 = lastName + " " + firstName + " " + address1 + " " + address2 + " " + country + " " + number;
                    string key2 = lastName + " " + firstName;
                    string value2 = address1 + " " + address2 + " " + city + " " + country + " " + number;
            
                    cout << key1 << " : " << value1 <<endl;
                    cout << key2 << " : " << value2 <<endl;
                    cityHashMap.insert(key1,value1);
                    nameHashMap.insert(key2,value2);
                    }
                }
                
                fin.close();
		    
            } else 
            {
                cout<<"Please initiate the program first."<<endl;
            }
	    } 
	
	
	    else if (command == "allinCity") 
	    {
	        if(initiated) 
	    	{
                cout << "Customers residing in " << key << " are: " << endl;
                cout << cityHashMap.search(key) << endl;
            }else 
            {
                cout<<"Please initiate the program first."<<endl;
            }
		}

		else if (command == "add") 
		{
		    if(initiated) 
	    	{
                nameHashMap.insertByInput(key,true);
                cityHashMap.insertByInput(key,false);
                cout<< "Added." <<endl;
			}else 
            {
                cout<<"Please initiate the program first."<<endl;
            }
		}
		
		else if (command == "find")
		{
		    if(initiated) 
	    	{
                cout << "Customer with a name of " << key << " is: " << endl;
                cout << "Entry for " << key << " has been successfully added!"<<endl;
            }else 
            {
                cout<<"Please initiate the program first."<<endl;
            }
		}
		
		else if (command == "dump") 
		{
		    if(initiated) 
	    	{
			nameHashMap.dump(key);
			}else 
            {
                cout<<"Please initiate the program first."<<endl;
            }
		}

		else if (command == "delete") 
		{
		    if(initiated) 
	    	{
                string cityKey = nameHashMap.MemberKeyToCityKey(key);
                if(cityHashMap.deleteMember(cityKey)) 
                {
                    if(nameHashMap.deleteMember(key)) 
                    {
                     cout << "Entry for " << key << " has been successfully deleted!"<<endl;
                    } else 
                    {
                    cout << "Record not found to be deleted."<<endl;
                    }
                } 
            }else 
            {
                cout<<"Please initiate the program first."<<endl;
            }
		}
		
		else if (command == "quit")
		{
		    break;
		}
	
	}
	exit(0);
}
