//#ifndef FUNCTIONS_H
#define FUNCTIONS_H
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
		long size;					//Current Size of HashMap
		long capacity;				// Total Capacity of HashMap
		
	public:
	
		HashMap();
		HashMap(long capacity);
		long hashCode(const string key);
		void insert(const string key, const string value);
		void insertByInput(const string input, bool isNameMap);
		string search(const string key);
		bool deleteMember(const string key2);
	    string MemberKeyToCityKey(const string key3);	
		map<string, string> dump(const string filename);
		long getSize();
		~HashMap();
};
