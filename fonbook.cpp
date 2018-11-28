#include<iostream>
#include<fstream>
#include<sstream>

using namespace std;

class HashNode{

	private:
	
		string key;
		string value;
		
	public:
	
		HashNode(string key, string value){
			this->key = key;
			this->value = value;
		}
		
		string getKey(){
			return this->key;
		}
		
		string getValue(){
			return this->value;
		}

};

class HashMap{

	private:
	
		HashNode **nodeArray;		// Array of Pointers to Hash Nodes
		int size;					//Current Size of HashMap
		int capacity;				// Total Capacity of HashMap
		
	public:
	
		HashMap(int capacity){
			nodeArray = new HashNode*[capacity];
			this->capacity = capacity;
			this->size = 0;
		}
		
		//Create Hashcode for key
		int hashCode(const string key){
			int sum=0;
			for(int i=0; i<key.length(); i++)
				sum+=int(key[i]);
			return sum%(this->capacity);
		}
		
		// Insert the key and value in Hash Map using Linear Probing
		void insert(const string key, const string value){
		
			HashNode *tempNode= new HashNode(key,value);
			int index = hashCode(key);
			
			while(nodeArray[index]!=NULL){
				index = (index+1) % this->capacity;
			}

			nodeArray[index] = tempNode;
			this->size++;
		}
        
        // Apply hash function to find index for given key 
		string search(const string key){
			int index = hashCode(key);
			int counter = 0;

			while(nodeArray[index] != NULL && counter < this->capacity){
			
				if (nodeArray[index]->getKey() == key){
					stringstream cnt;			// To Convert int to string
					cnt<<counter;				// converting counter into stringstream cnt

					return string(nodeArray[index]->getValue())+"   (comparisions = "+cnt.str()+")";
				}
				
				//If not found return message 
				index = (index+1)%this->capacity;
				if(++counter >= this->capacity)
					return "Record Not Found";
			}
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
	fin.open("zipcodes.txt");
	
	if(!fin){
		cout<<"Can not open the file...!";
		exit(-1);
	}

	string line;
	HashMap myHashMap(19880);
	getline(fin,line);  //skip first line
	
	while(!fin.eof()){
		string key, value;
		getline(fin,value,',');
		getline(fin,key);
		cout<<key<<":"<<value<<endl;
		myHashMap.insert(key,value);
	}
	fin.close();

	cout<<"Hash Map size = "<<myHashMap.getSize()<<endl;

	string choice;
	
	while(true){
		cout<<"Enter City Name:";
		getline(cin,choice);		//Input strings which might contain spaces
		if (choice == "exit")
			break;
		
		cout<<"Zip code for "<<choice<<" is: "<<myHashMap.search(choice)<<endl;
	}
	exit(0);
}

