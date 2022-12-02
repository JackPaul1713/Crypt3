#include <string>
#include <vector>
#include "interface/Crypt3.h"

using namespace std;

int main(int argc, char const *argv[])
{
  // variables:
  vector<string> arguments;
  Crypt3 crypt3;
  // process:
  for(int i = 0; i < argc; i++) // loop through argv
    arguments.push_back(argv[i]); // add to arguments
  // execute:
  crypt3.execute(arguments);
  // return:
  cout << "exiting" << endl; // DEBUG
  return(0);
}
