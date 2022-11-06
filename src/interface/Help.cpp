#include <iostream>
#include "Help.h"

using namespace std;

//// actions ////
void Help::execute(std::vector<std::string> arguments)
{
  cout << "syntex:" << endl;
  cout << "  crypt3 /*action* *file* *key* -*flags*" << endl;
  cout << "  crypt3 /*action* *inputfile* *outputfile* *key* -o -*flags*" << endl;
  cout << "actions:" << endl;
  cout << "  encrypt e - encrypts file data" << endl;
  cout << "  decrypt d - decrypts file data" << endl;
  cout << "  help h - displays help" << endl;
  cout << "encryption decryption flags: " << endl;
  cout << "  safe s - prevents incorrect decryption (1/4096 chance of failure)" << endl;
  cout << "  directory d - INCOMPLETE" << endl;
  cout << "  output o - outputs to specifed file" << endl;
  cout << "  ghost g - outputs to the terminal" << endl;
  cout << "  tkey t - takes in text in as key" << endl;
}
