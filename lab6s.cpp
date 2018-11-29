#include<iostream>
#include<fstream>
#include<cmath>
#include<sstream>


using namespace std;
class HashNode
{
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

class HashMap
{
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

		string search(const string key)
		{
			int index = hashCode(key);
			int counter = 0;

			while(nodeArray[index] != NULL && counter < this->capacity)
			{
				if (nodeArray[index]->getKey() == key)
				{
					stringstream cnt;			// To Convert int to string
					cnt<<counter;				// converting counter into stringstream cnt
					
					string comparison =  "(comparisons = " + cnt.str() + ")";
					return string(nodeArray[index]->getValue()) + "\n" + comparison;
				}
				
				//otherwise
				index = (index+1) % this->capacity;
				if(++counter >= this->capacity) return "Record Not Found";
			}
		}

		int getSize()
		{
			return this->size;
		}

		~HashMap()
		{
			delete[] this->nodeArray;
		}
};


int main(void)
{
	ifstream fin;
	fin.open("file1.txt");
	if(!fin){
		cout<<"Can not open the file...!";
		exit(-1);
	}

	string line;
	HashMap myHashMap(19880);

	while(!fin.eof())
	{

		string firstName, lastName, address1, address2, city, country, number;
		getline(fin,firstName,' ');
		getline(fin,lastName,' ');
		getline(fin,address1,' ');
		getline(fin,address2,' ');
		getline(fin,city,' ');
		getline(fin,country,' ');
		getline(fin,number);

		string key = city;
		string value = firstName + " " + lastName + " " + address1 + " " + address2 + " " + country + " " + number;
		
		cout << key << " : " << value <<endl;
		myHashMap.insert(key,value);

	}
	fin.close();

	cout<<"Hash Map size = "<<myHashMap.getSize()<<endl;

	string choice;
	while(true)
	{
		cout<<"Enter City Name:";
		getline(cin,choice);		//Input strings which might contain spaces
		if (choice == "exit")
			break;
		
		cout << "Customers residing in " << choice << " are: " << endl;
		cout << myHashMap.search(choice) << endl;
	}
	exit(0);
}

