#include<iostream>
#include<fstream>
#include<cmath>
#include<istream>
#include<string>
#include <iterator> 

using namespace std;


class HashNode{

	private:
		string key;
		string value;
	public:
		HashNode(string key, string value)
		{
			this->key = key;
			this->value = value;
		}
		string getKey()
		{
			return this->key;
		}
		string getValue()
		{
			return this->value;
		}

};

class HashMap{

	private:
		HashNode **nodeArray;		// Array of Pointers to Hash Nodes
		int size;					//Current Size of HashMap
		int capacity;				// Total Capacity of HashMap
	public:
		HashMap(int capacity)
		{
			nodeArray = new HashNode*[capacity];
			this->capacity = capacity;
			this->size = 0;
		}
		
		int hashCode(const string key)
		{
			long sum=0;
			for(int i=0; i<key.length(); i++)
				sum+=pow(2,i)*int(key[i]);
			return sum%(this->capacity);
		}
		
		void insert(const string key, const string value)
		{
			HashNode *tempNode= new HashNode(key,value);
			int index = hashCode(key);
			while(nodeArray[index]!=NULL)
			{
				index = (index+1) % this->capacity;
			}

			nodeArray[index] = tempNode;
			this->size++;
		}

		string search(const string key){
		
			int index = hashCode(key);
			int counter = 0;
			string restring;

			while(nodeArray[index] != NULL && counter < this->capacity){
			
				if (nodeArray[index]->getKey() == key){			
					restring = restring + string(nodeArray[index]->getValue()) + "\n";
				}
				
				index = (index+1) % this->capacity;
				counter ++;
				
			}

			if(restring != ""){
			    string comparison =  "(comparisons = " + to_string(counter) + ")";
			    restring = restring + comparison;		
			    return restring;	
			}else{
			    return "Record Not Found";
			}
		}
		
		void dump(const string filename){
		    
		    ofstream myfile(filename, std::ios::trunc);
		    
		    int index = 0;
			while(index < this->capacity){
			
			    if(nodeArray[index] != NULL){
				    cout << nodeArray[index]->getKey() <<  " " << nodeArray[index]->getValue() << endl;
				    myfile << nodeArray[index]->getKey() + " " + nodeArray[index]->getValue() << endl;
                }
                
				index ++;	
			}	
			myfile.close();
		}

		int getSize(){
			return this->size;
		}

		~HashMap(){
			delete[] this->nodeArray;
		}
};


int main(void){

	ifstream fin;
	fin.open("file1.txt");
	
	if(!fin){
		cout<<"Can not open the file...!";
		exit(-1);
	}

	string line;
	HashMap cityHashMap(180);
	HashMap nameHashMap(180);
	

	while(!fin.eof()){

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
	fin.close();

	cout << "Hash Map size = " << cityHashMap.getSize() << endl;

	
	while(true){
	    
	    string line;
	    cout << "Enter your command: " << endl;
	    getline(cin, line);
	    string command = line.substr(0, line.find(" "));
	    string key = line.substr(line.find(" ")+1, line.length());
	    
	    if (command == "allinCity"){
	    
            cout << "Customers residing in " << key << " are: " << endl;
            cout << cityHashMap.search(key) << endl;
		
		}
		
		else if (command == "find"){
        
            cout << "Customer with a name of " << key << " is: " << endl;
            cout << nameHashMap.search(key) << endl;
		
		}
		
		else if (command == "dump") {
			nameHashMap.dump(key);
		}
		
		else if (command == "quit"){
		    break;
		}
		
	}
	
	
	exit(0);
}

