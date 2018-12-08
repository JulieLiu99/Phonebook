#include<iostream>
#include<fstream>
#include<cmath>
#include<istream>
#include<string>
#include <iterator> 
#include <sstream> //for delete function
#include "functions.h"


using namespace std;


int main(int count, char * args[])
{
    cout << "mymachine-prompt >> ./fonbook -f <filename>" << endl;
    cout << "1. Add Customer (add e)\n2. Find Customer (find k)\n3. Delete Customer ( delete k)\n4. Find All Customers in a City ( allinCity)\n5. Load Customer Database (load f)\n6. Save Customer Database to a File (dump f)\n7. Quit (quit)"<<endl;
	ifstream fin;
	bool initiated = false;
	string line;
	string inputFile;
	HashMap cityHashMap; //The hash map for the data structure with the name as the key
	HashMap nameHashMap; //The hash map for the data structure with the city as the key
    bool fileLoaded=false;
    //take as parameters names of the input textfile
    //cout<<"COUNT:"<<count<<endl;
    if(count>2) //To handle more arguments when initializing
    {
        for (int i = 1; i < count; i++) 
        {
            if ((string(args[i]) == "-f") && ((i + 1) < count)){
                inputFile = args[i + 1];
                fileLoaded=true; //File is going to be loaded
            }

        }
    }

    if(fileLoaded) 
    {
    //print out names of the input textfile
        cout << "Input file is " << inputFile << endl; //Printing the file name
    } 
	
	while(true) {
	    
	    string line;
	    cout << "Enter your command: " << endl; //Asking the user for input command
	    getline(cin, line); 
	    string command = line.substr(0, line.find(" ")); //Finding the command name substring
	    string key = line.substr(line.find(" ")+1, line.length()); //Finding the subrstring except for the command name
	    
	    if(command=="init") //If the command name is init
	    { 
	    	if((!initiated)) //If not yet initialized
	    	{
				cityHashMap=HashMap(18000); //Initiate a hashmap of size 18000
				nameHashMap=HashMap(18000); //Initiate a hashmap of size 18000
	    		cout<<"Initiated."<<endl; //Success message to user
	    		initiated=true; //Set initiated bool to true so that other functions can be called seamlessly
	    		
                if(fileLoaded)
                {
                    fin.open(inputFile); //Open the file
                    if(!fin) // If the file cannot be opened
                    {
                        fileLoaded=false;
                        cout<<"Cannot open the file. Please use load function to load your file."<<endl;
                    } else //If the file successfullt opened
                    {
                        cout <<"---------"<<endl;
                        while(!fin.eof())
                        {
                            string lastName, firstName, address1, address2, city, country, number;
                            getline(fin,lastName,' '); //Get last name string
                            getline(fin,firstName,' '); //Get first name string
                            getline(fin,address1,' '); //Get address 1 string
                            getline(fin,address2,' ');//Get address 2 string
                            getline(fin,city,' '); //Get city string
                            getline(fin,country,' '); //Get country string
                            getline(fin,number); //Get phone number string

                            string key1 = lastName + " " + firstName;
                            string value1 = address1 + " " + address2 + " " + city + " " + country + " " + number;
                            string key2 = city;
                            string value2 = lastName + " " + firstName + " " + address1 + " " + address2 + " " + country + " " + number;
                            
                            if(firstName.size()>0) 
                            {
                                cout << key1 << " : " << value1 <<endl;
                                cout << key2 << " : " << value2 <<endl;
                                cout <<"---------"<<endl;
                                nameHashMap.insert(key1,value1);
                                cityHashMap.insert(key2,value2);
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
	    
	    else if(command=="load") 
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

                        string key1 = lastName + " " + firstName;
                        string value1 = address1 + " " + address2 + " " + city + " " + country + " " + number;
                        string key2 = city;
                        string value2 = lastName + " " + firstName + " " + address1 + " " + address2 + " " + country + " " + number;
                        
                        if(firstName.size()>0) 
                        {
                            cout << key1 << " : " << value1 <<endl;
                            cout << key2 << " : " << value2 <<endl;
                            cout <<"---------"<<endl;
                        
                            if (nameHashMap.search(key1) == "Record Not Found")
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
                cout << "Customer with a name of " << key << " is: " << cityHashMap.search(key) << endl;
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
                cout<<"-------\nSuccessfully dumped data into "<<key<<endl;
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

        else 
        {
           cout << "1. Add Customer (add e)\n2. Find Customer (find k)\n3. Delete Customer ( delete k)\n4. Find All Customers in a City ( allinCity)\n5. Load Customer Database (load f)\n6. Save Customer Database to a File (dump f)\n7. Quit (quit)"<<endl;
        }
	
	}
	exit(0);
}
