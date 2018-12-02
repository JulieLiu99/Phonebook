#include<iostream>
#include<fstream>
#include<cmath>
#include<istream>
#include<string>
#include <iterator> 
#include <sstream> //for delete function
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
		void deleteMember() {
			//this->value=NULL;
			//this->key=NULL;
		}

};

class HashMap{

	private:
		HashNode **nodeArray;		// Array of Pointers to Hash Nodes
		int size;					//Current Size of HashMap
		int capacity;				// Total Capacity of HashMap
	public:
		HashMap() {

		}
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

		void insertByInput(const string input, bool isNameMap) {
			string line = input;
			int numInputs=7;
			string arr[numInputs];
				int i = 0;
				stringstream ssin(line);
				    while (ssin.good() && i < numInputs) {
				        ssin >> arr[i];
				        ++i;
				   }
		if(isNameMap) {
			string fullName = arr[0] + " " + arr[1];
			string values = arr[2] + " " + arr[3] + " " + arr[4] + " " + arr[5] + " " + arr[6];
			this->insert(fullName,values);
		} else {
			string city = arr[4];
			string values = arr[0] + " " + arr[1] + " " + arr[2] + " " + arr[3] + " " + arr[5] + " " + arr[6];
			this->insert(city,values);
		}

			}
		

		string search(const string key)
		{
		
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

		bool deleteMember(const string key2) 
		{
			int index2 = this->hashCode(key2);
			int counter2 = 0;
			string restring;
			bool deleted=false;

			while(this->nodeArray[index2] != NULL && counter2 < this->capacity){

				if (this->nodeArray[index2]->getKey() == key2){	
		
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

	string MemberKeyToCityKey(const string key3) 
		{
			int index2 = hashCode(key3);
			int counter2 =0;
			string restring;
			string result="";
			while(this->nodeArray[index2] != NULL && counter2 < this->capacity){
				if (this->nodeArray[index2]->getKey() == key3) {			
					//this->nodeArray[index2]=NULL;
				string line = this->nodeArray[index2]->getValue();
				string arr[5];
				int i = 0;
				stringstream ssin(line);
				    while (ssin.good() && i < 5) {
				    	//cout<<"WHILE LOOP LINE THING"<<endl;
				        ssin >> arr[i];
				        ++i;
				   }
				   for(i = 0; i < 5; i++){
        			//cout << "arr["  << i << "]: " << arr[i] << endl;
    				}
				    result = arr[2];
					break;
				}
				index2 = (index2+1) % this->capacity;
				counter2 ++;
			}
			return result;
		}
		/*
string line = "test one two three.";
    string arr[4];
    int i = 0;
    stringstream ssin(line);
    while (ssin.good() && i < 4){
        ssin >> arr[i];
        ++i;
    }
		*/
		
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
	bool initiated = false;

	string line;
	HashMap cityHashMap;
	HashMap nameHashMap;
	//cout << "Hash Map size = " << cityHashMap.getSize() << endl;

	
	while(true) {
	    
	    string line;
	    cout << "Enter your command: " << endl;
	    getline(cin, line);
	    string command = line.substr(0, line.find(" "));
	    string key = line.substr(line.find(" ")+1, line.length());
	    
	    if(command=="init") { 
	    	if(!initiated) {
				cityHashMap=HashMap(180);
				nameHashMap=HashMap(180);
	    		cout<<"Initiated."<<endl;
	    		initiated=true;
			} else {
				cout<<"Already initiated."<<endl;
			}
	    }
	    else if(command=="load") {
	    	if(initiated) {
		    	fin.open(key);
	    	
		
			if(!fin){
				cout<<"Cannot open the file."<<endl;
			} else {
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
	}
		fin.close();
		} else {
			cout<<"Have to init first."<<endl;
		}

	} else if (command == "allinCity") {
	    
            cout << "Customers residing in " << key << " are: " << endl;
            cout << cityHashMap.search(key) << endl;
		
		}

		else if (command == "add") {
			nameHashMap.insertByInput(key,true);
			cityHashMap.insertByInput(key,false);
			cout<< "Added." <<endl;
		}
		
		else if (command == "find"){
        
            cout << "Customer with a name of " << key << " is: " << endl;
            cout << nameHashMap.search(key) << endl;
		
		}
		
		else if (command == "dump") {
			nameHashMap.dump(key);
		}

		else if (command == "delete") {
			string cityKey = nameHashMap.MemberKeyToCityKey(key);
			cout << "CITY KEY for cityHashMap IS: "<<cityKey<<endl;
			//if((nameHashMap.deleteMember(key))) { //&&(cityHashMap.deleteMember(cityKey))
			if(cityHashMap.deleteMember(cityKey)) {
				if(nameHashMap.deleteMember(key)) {
				 cout << "Deleted"<<endl;
				} else {
				cout << "Record not found to be deleted."<<endl;
			}
			} 
		}
		
		else if (command == "quit"){
		    break;
		}
		
	}
	
	
	exit(0);
}

