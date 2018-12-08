#include<iostream>
#include<fstream>
#include<cmath>
#include<istream>
#include<string>
#include <iterator> 
#include <sstream> 
#include <iterator> 
#include <map> 
#include "functions.h"


using namespace std;


int main(int count, char * args[]) // main function 
{
    cout << "mymachine-prompt >> ./fonbook -f <filename>" << endl;
    cout << "1. Add Customer (add e)\n2. Find Customer (find k)\n3. Delete Customer ( delete k)\n4. Find All Customers in a City ( allinCity)\n5. Load Customer Database (load f)\n6. Save Customer Database to a File (dump f)\n7. Quit (quit)"<<endl;
	ifstream fin;
	bool initiated = false;
	string line;
	string inputFile;
	HashMap cityHashMap;
	HashMap nameHashMap;
    bool fileLoaded=false;
    
    //take as parameter name of the input textfile
    if(count>2) 
    {
        for (int i = 1; i < count; i++) 
        {
            if ((string(args[i]) == "-f") && ((i + 1) < count)){
                inputFile = args[i + 1];
                fileLoaded=true;
            }

        }
    }

    if(fileLoaded) 
    {
    //print out names of the input textfile
        cout << "Input file is " << inputFile << endl;
    } 
	
	while(true) 
	{
	    string line;
	    cout << "Enter your command: " << endl; // keep asking the user input
	    getline(cin, line);
	    string command = line.substr(0, line.find(" "));
	    string key = line.substr(line.find(" ")+1, line.length());
	    
	    if(command=="init") 
	    { 
	    	if((!initiated)) // to initiate the whole program
	    	{
				cityHashMap=HashMap(1000000); //hashing map with city as the key
				nameHashMap=HashMap(1000000); //hashing map with last and first name as the key
	    		cout<<"Initiated."<<endl;
	    		initiated=true;
	    		
                if(fileLoaded)
                {
                    fin.open(inputFile);
                    if(!fin)
                    {
                        fileLoaded=false;
                        cout << "Cannot open the file. Please use load function to load your file." << endl;
                    } else 
                    {
                        cout <<"---------"<<endl;
                        while(!fin.eof()) // read from the file and insert into the hashing map
                        {
                            string lastName, firstName, address1, address2, city, country, number;
                            getline(fin,lastName,' '); //last name
                            getline(fin,firstName,' '); //first name
                            getline(fin,address1,' '); // first part of address
                            getline(fin,address2,' '); //second part of address
                            getline(fin,city,' '); // city
                            getline(fin,country,' '); // country
                            getline(fin,number); // phone number

                            string key1 = lastName + " " + firstName;
                            string value1 = address1 + " " + address2 + " " + city + " " + country + " " + number;
                            string key2 = city;
                            string value2 = lastName + " " + firstName + " " + address1 + " " + address2 + " " + country + " " + number;
                        
                            if(firstName.size()>0) 
                            {
                                cout << key1 << " : " << value1 <<endl;
                                cout << key2 << " : " << value2 <<endl;
                                cout <<"---------"<<endl;
                                nameHashMap.insert(key1,value1); // insert the entry to the name hashing map
                                cityHashMap.insert(key2,value2); // insert the entry to the city hashing map
                            }
                        }
                        cout<<"File loaded successfully."<<endl;
                fin.close();
            }
                }

			} else 
			{
				cout<<"Already initiated."<<endl;
			}
			

	    }
	    
	    else if(command=="load") // to load the entries from file to hashing map
	    {
	    	if(initiated) 
	    	{
                    fin.open(key);
                    if(!fin)
                    {
                        fileLoaded=false;
                        cout<<"Cannot open the file. Please recheck the file you are loading."<<endl;
                    } 
                    else 
                    {
                        fileLoaded=true;
                        cout <<"---------"<<endl;

                        while(!fin.eof()) // to split the line in file into different variables
                        {
                            string lastName, firstName, address1, address2, city, country, number;
                            getline(fin,lastName,' '); //last name
                            getline(fin,firstName,' '); //first name
                            getline(fin,address1,' '); // first part of address
                            getline(fin,address2,' '); //second part of address
                            getline(fin,city,' '); // city
                            getline(fin,country,' '); // country
                            getline(fin,number); // phone number

                            string key1 = lastName + " " + firstName; //name hashing map key
                            string value1 = address1 + " " + address2 + " " + city + " " + country + " " + number;
                            string key2 = city; // city hashing map key
                            string value2 = lastName + " " + firstName + " " + address1 + " " + address2 + " " + country + " " + number;
                        
                        if(firstName.size()>0) 
                        {
                            cout << key1 << " : " << value1 <<endl;
                            cout << key2 << " : " << value2 <<endl;
                            cout <<"---------"<<endl;
                        
                            if (nameHashMap.search(key1) != "Record Not Found") // check if the entry is already in the hashing map
                            {
                                nameHashMap.insert(key1,value1);
                                cityHashMap.insert(key2,value2);
                            }
                        }

                        }
                        cout<<"File loaded successfully."<<endl;
                    }
                    
                    fin.close();
		          
            } else 
            {
                cout<<"Please initiate the program first."<<endl;
            }
	    } 
	
	
	    else if (command == "allinCity") // to find all the customers from the same city
	    {
	        if(initiated) 
	    	{
                cout << "Customers residing in " << key << " are: " << endl;
                cout << cityHashMap.search(key) << endl; // to look through the map and return with string
            }else 
            {
                cout<<"Please initiate the program first."<<endl;
            }
		}

		else if (command == "add") 
		{
		    if(initiated) 
	    	{
                nameHashMap.insertByInput(key,true); //to add an entry to the city hashing map
                cityHashMap.insertByInput(key,false); // to add an entry to the name hashing map
                cout<< "Added." <<endl;
			}else 
            {
                cout<<"Please initiate the program first."<<endl;
            }
		}
		
		else if (command == "find") // to look for an entry in the hashing map with name as key
		{
		    if(initiated) 
	    	{
                cout << "Customer with a name of " << key << " is: " << nameHashMap.search(key) << endl;
            }else 
            {
                cout<<"Please initiate the program first."<<endl;
            }
		}
		
		else if (command == "dump") // to transfer all entries from the hashing map into a file in sorted order
		{
		    if(initiated) 
	    	{
			    map<string, string> orderedMap = nameHashMap.dump(key); // using the stl map to realize the sorting function
			    
			    ofstream myfile(key, std::ios::trunc);
			    map<string, string>::iterator itr; 
                for (itr = orderedMap.begin(); itr != orderedMap.end(); ++itr) // read from the stl sorted map into the output file
                {   
                    string cityKey = nameHashMap.MemberKeyToCityKey(itr->first);
                    if(cityHashMap.search(cityKey) != "Record Not Found")
                    {
                        cout <<  itr->first << " " << itr->second << endl; // the first is name and the second is the infro
                        myfile << itr->first + " " + itr->second << endl;
                    }
                } 
                myfile.close();
                
                cout<<"-------\nSuccessfully dumped data into "<<key<<endl;
			}else 
            {
                cout<<"Please initiate the program first."<<endl;
            }
		}

		else if (command == "delete") // to delete an entry with name as key
		{
		    if(initiated) 
	    	{
                string cityKey = nameHashMap.MemberKeyToCityKey(key);
                if(cityHashMap.deleteMember(cityKey)) // delete the entry from the city hashing map
                {
                    if(nameHashMap.deleteMember(key)) // delete the entry from the name hashing map
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
		
		else if (command == "quit") // to end the program and clear up memory
		{
		    break;
		}

        else 
        {
           cout << "1. Add Customer (add e)\n2. Find Customer (find k)\n3. Delete Customer ( delete k)\n4. Find All Customers in a City ( allinCity)\n5. Load Customer Database (load f)\n6. Save Customer Database to a File (dump f)\n7. Quit (quit)"<<endl;
        }
	
	}
	exit(0);
}
