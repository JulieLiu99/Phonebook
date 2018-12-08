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
    cout << "mymachine-prompt >> ./fonbook -f <filename>" << endl;
    cout << "1. Add Customer (add e)\n2. Find Customer (find k)\n3. Delete Customer ( delete k)\n4. Find All Customers in a City ( allinCity)\n5. Load Customer Database (load f)\n6. Save Customer Database to a File (dump f)\n7. Quit (quit)"<<endl;
	ifstream fin;
	bool initiated = false;
	string line;
	string inputFile;
	HashMap cityHashMap;
	HashMap nameHashMap;
    bool fileLoaded=false;
    //take as parameters names of the input textfile
    //cout<<"COUNT:"<<count<<endl;
    if(count>2) {
    for (int i = 1; i < count; i++) {
        if ((string(args[i]) == "-f") && ((i + 1) < count)){
            inputFile = args[i + 1];
            fileLoaded=true;
        }

    }
}
    //remind user of the way to invocate the application
    if (inputFile == "" ) {
        //return -1;
    }
    if(fileLoaded) {
    //print out names of the input textfile
    cout << "Input file is " << inputFile << endl;
} 
	
	while(true) {
	    
	    string line;
	    cout << "Enter your command: " << endl;
	    getline(cin, line);
	    string command = line.substr(0, line.find(" "));
	    string key = line.substr(line.find(" ")+1, line.length());
	    
	    if(command=="init") 
	    { 
	    	if((!initiated)) 
	    	{
				cityHashMap=HashMap(18000);
				nameHashMap=HashMap(18000);
	    		cout<<"Initiated."<<endl;
	    		initiated=true;
                if(fileLoaded){
            fin.open(inputFile);
            
            if(!fin)
            {
                fileLoaded=false;
                cout<<"Cannot open the file. Please use load function to load your file."<<endl;
            } else 
            {
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
                          if(firstName.size()>1) {
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
                if(!fileLoaded)
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
                            if(firstName.size()>1) {
                            cout << key1 << " : " << value1 <<endl;
                            cout << key2 << " : " << value2 <<endl;
                            cout <<"---------"<<endl;
                            nameHashMap.insert(key1,value1);
                            cityHashMap.insert(key2,value2);
                        }

                            }
                            cout<<"File loaded successfully."<<endl;
                        }
                        
                        fin.close();
		          } else {
                    cout<<"File already loaded into program."<<endl;
                  }
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

        else {
           cout << "1. Add Customer (add e)\n2. Find Customer (find k)\n3. Delete Customer ( delete k)\n4. Find All Customers in a City ( allinCity)\n5. Load Customer Database (load f)\n6. Save Customer Database to a File (dump f)\n7. Quit (quit)"<<endl;
     
        }
	
	}
	exit(0);
}
