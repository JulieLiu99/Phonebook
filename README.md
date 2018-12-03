# Data-Structure-Project-3

This is a e-phone-book application named fonbook that can help locate both the phone number and postal address for individuals termed customers.
The identification of customers is be based on the key produced by the combination of first and last name. 
The application is also able to return all customers residing in a specific city.

## Prerequisites

All the files including Makefile, fonbook.cpp, functions.cpp, functions.h, and text files should be in the same directory.
You will have to use the Linux/FreeBSD C++/C development environment.

## Getting Started

This instruction will get you a copy of the project up and running on your local machine for development and testing purposes. 
./mycalc -i <inputfile> -o <outputfile>>
The following is an example of running the program via command line.

The fonbook commands are the following:
** – init: initiate the main-memory structure(s) that will accommodate the incoming data. If init is executed for the second time around once your program has commenced operation, it will have no effect.** 
** – add e: all the data provided by string e corresponding to those of a customer 1 are to be inserted using as key k the combination of last and first name. ** 
** – delete k: delete the customer record with key k. If no such element exists, print out a diagnostic message to the standard error.** 
** – load f: read into your data structure(s) the content of the file f. There could be several load operations, i.e., data could be loaded in several batches to a structure that is non-empty.** 
** – dump f: dump the content of the entire structure(s) into the file f and sort the content of the file f according to the last name of the customers in alpha-numerically increasing order.** 
** – quit: terminate the program with graceful release of all dynamically acquired memory.** 

## Algorithmic Analysis

Data are stored in two hashing maps, one with customer name as key, another with city name.
Hashing table takes on average O(1) time complexity to find, insert, and delete.
In allinCity function, the output is in alphabetically sorted order with the help of balanced tree, which takes O(nlogn) time.

## Authors

* **Julie Liu** 
* **Romeno Wenogk Fernando** 

## Acknowledgments

* The project is finished under the guidance of Professor Stavros Kolliopoulos and instructor Khalid Mengal in New York University Abu Dhabi Computer Science Department

