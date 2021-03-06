// BinaryInsertionRecords.cpp : Defines the entry point for the console application.
//Stephan Brown, for Design & Analysis, of Algorithms.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <sstream>
using namespace std;

//Declare an array for just the integer IDs to be sorted, and one for the full string records.
int recordsArr[20];
string recordsSorted[20];

//This function reads the records from StudentRecords.txt twice, first printing the file and storing only the studentID#s as ints
//Then second storing the strings from each line. 
void ReadRecords() {
	ifstream StudentRecordsInput;
	StudentRecordsInput.open("C:\\Users\\steph\\source\\repos\\BinaryInsertion\\BinaryInsertionRecords\\StudentRecords.txt");
	int i = 0;
	int j = 0;
	string name;
	string age;
	string gpa;
	string ID;
	string line;

	if (StudentRecordsInput.is_open())
	{
		cout << "File Opened-- Unsorted Record List:" << '\n';

		// read file line by line
		for (int i = 0; i < 20; i++) {
			getline(StudentRecordsInput, name, ',');
			cout << name << ": ";

			getline(StudentRecordsInput, age, ',');
			cout << " age: " << age;

			getline(StudentRecordsInput, gpa, ',');
			cout << " gpa: " << gpa;

			getline(StudentRecordsInput, ID, '\n');
			cout << " ID# " << ID << '\n';
			recordsArr[i] = atoi(ID.c_str());
		}
		StudentRecordsInput.close();
	}
	else
	{
		cout << "Error opening file";
	}

	StudentRecordsInput.open("C:\\Users\\steph\\source\\repos\\BinaryInsertion\\BinaryInsertionRecords\\StudentRecords.txt");

	if (StudentRecordsInput.is_open())
	{
		for (int i = 0; i < 20; i++) {
			string line;
			getline(StudentRecordsInput, line, '\n');
			recordsSorted[i] = line;
		}

		StudentRecordsInput.close();
	}
	else
	{
		cout << "Error opening file";
	}
}

//This functions does a binary search on an array (for use in the insertion sort function)
int binarysearch(int arr[], int l, int r, int num) {
	int middle;
	//while the Left ref is less than the right ref
	while (l < r)
	{
		middle = l + (r - l) / 2; //set middle ref to midpoint
		if (arr[middle] > num)
		{
			return binarysearch(arr, l, middle, num); //recursively performs binary search again while setting the right ref to the middle if num searched is less than middle
		}
		else if (arr[middle] < num)
		{
			return binarysearch(arr, middle + 1, r, num); // recursively performs binary search again while setting the left ref to the middle if num is greater than middle
		}
		else
		{
			return middle;
		}
	}
}


//This function performs the binary insertion sort on the arrays
void binaryinsertionsort(int arr[], string arra[], int n) {
	int i, j, ins, temp;
	string temp2;
	for (i = 1; i < n; i++)
	{
		ins = binarysearch(arr, 0, i, arr[i]);
		temp = arr[i];
		temp2 = arra[i];
		for (j = i - 1; j >= ins; j--)
		{
			arr[j + 1] = arr[j];
			arra[j + 1] = arra[j];

		}
		for (j = 0; j >= ins; j--)
		{
		}
		arr[ins] = temp;
		arra[ins] = temp2;
	}
}

//This function just prints an array of integers
void print(int arr[], int n) {
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << " ";
	}
	cout << "\n";
}

void OutputRecords() {
	string input;
	ofstream out("C:\\Users\\steph\\source\\repos\\BinaryInsertion\\BinaryInsertionRecords\\SortedStudents.txt");

	//for each line, sets input to the sorted string record and the prints to file.
	for (int i = 0; i < 20; i++) { 
		input = recordsSorted[i];
		out << input << std::endl;
	}
	out.close();
	cout << "Sorted records output to SortedStudents.txt";

}

int main()
{
	ReadRecords();
	cout << "\n" << "here is the unsorted array of IDs:" << "\n";
	print(recordsArr, 20);
	
	binaryinsertionsort(recordsArr, recordsSorted, 20);

	cout << "\n" << "here is the sorted array of IDs:" << "\n";
	print(recordsArr, 20);

	cout << "\n" << "here is the sorted record list:";
	cout << "\n";
	for (int j = 0; j < 20; j++) {
		cout << recordsSorted[j] << "\n";
	}

	OutputRecords();
	system("pause");
    return 0;
}

