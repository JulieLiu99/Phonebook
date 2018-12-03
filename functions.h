//#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include<iostream>
#include<fstream>
#include<cmath>
#include<istream>
#include<string>
#include <iterator> 
#include <sstream>

using namespace std;


class HashNode
{
	private:
	
		string key;
		string value;
		
	public:
	
		HashNode(string key, string value);
		string getKey();
		string getValue();

};



class HashMap
{
	private:
	
		HashNode **nodeArray;		// Array of Pointers to Hash Nodes
		int size;					//Current Size of HashMap
		int capacity;				// Total Capacity of HashMap
		
	public:
	
		HashMap();
		HashMap(int capacity);
		int hashCode(const string key);
		void insert(const string key, const string value);
		void insertByInput(const string input, bool isNameMap);
		string search(const string key);
		bool deleteMember(const string key2);
	    string MemberKeyToCityKey(const string key3);	
		void dump(const string filename);
		int getSize();
		~HashMap();
};
