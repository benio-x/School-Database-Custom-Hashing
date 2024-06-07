/*
we will read records and store into hashmap for student files
*/
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "hashMap.cpp"
#include "hashMap.h"

using namespace std;

struct studentRecord {
  string first, last;
  double gpa, credits;
  string university;
};

int main() {
  ifstream iFile;// for ifile read
  string iFileName = "NSHE.txt";

  do {
    iFile.open(iFileName);
    // openining our file, by filename given through an argument
    if (!iFile.is_open()) {  // if improper file name,
     // give error
      cout << "File not found" << endl;
      return 0;
    }
  } while (!iFile.is_open());

  // declare thy hashmappys
  hashMap<string, studentRecord> nshe;
  hashMap<string, bool> studentExists;
  hashMap<string, int> failedSearches;

  string lines;// for file read
// read from input file
  while (getline(iFile, lines)) {
    stringstream ss(lines);
    string first;
    string last;
    string id;
    string uni;
    double gpa;
    double credits;
// get info from line
    ss >> first >> last >> id >> gpa >> credits >> uni;
    // check if empty
    if (!first.empty() && !last.empty() && !id.empty()) {
      string key = first + last + id;// concatenate for key
      // create the student record
      studentRecord record = {first, last, gpa, credits, uni};
      // put record into the nshe map
      nshe[key] = record;
      studentExists[first + last] = true;// student exists
    }
  }
  iFile.close();

  string input;

  cout << "Enter student's full name and NSHE id: ";
  
  while (true) {
    getline(cin, input);// read
    if (input.empty())// check if empty
    break;
    cout << input;

    stringstream ss(input);// parse input
    string firstName;
    string lastName;
    string studentId;
// get information
    ss >> firstName >> lastName >> studentId;
  // concatenate
    string fullName = firstName + lastName;
    string fullNameWId = fullName + studentId;
// start of checks!
    if (!studentExists[fullName]) {// check if exists by the name
      cout << endl;
      cout << "Student does not exist" << endl << endl;
    } else if (failedSearches[fullName] >= 3) {// check for failure search
      cout << endl << endl;
      cout << "Too many failed nshe searches on this student" << endl << endl;
    } else if (nshe[fullNameWId].first == "") {// check for NSHE match
      cout << endl << endl;
      cout << "NSHE ID does not match student's record" << endl<< endl;
      failedSearches[fullName]++;// increment failure
    } else {// get student record
      const studentRecord& record = nshe[fullNameWId];
      cout << endl << endl;
      cout << record.last << ", " << record.first
           << "\nCredits: " << record.credits << " GPA: " << record.gpa << "\n"
           << record.university << endl << endl;
    }
    cout << "Do you wish to continue? (Y/N): ";
    
    getline(cin, input);
    cout << input << endl;
    if (input != "Y" && input != "y")
    break;
    cout << endl;
    cout << "Enter student's full name and NSHE id: ";
  
  }
  return 0;
}
