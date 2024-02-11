/**********************************************
 ** File: proj3.cpp
 ** Project: CMSC 202 Project 3, Spring 2023
 ** Author: Joshua Hur
 ** Date: 3/14/23
 ** E-mail: jhur1@umbc.edu
 **
 ** This file simulates a DNA sequencer that transcript and translate DNA and mRNA.
 ************************************************************************/

#include "Sequencer.h"
#include <iostream>
using namespace std;

//This allows data to be passed when calling the executable
//For example, ./proj3 proj3_data1.txt would pass proj3_data1.txt as argv[1] below
int main () {
    string file = "proj3_data1.txt";
    cout << endl << "***Transcription and Translation***" << endl << endl;
    Sequencer D = Sequencer(file); //Passes the file name into the Sequencer constructor
    D.StartSequencing();//Starts the sequencer

  return 0;
}
