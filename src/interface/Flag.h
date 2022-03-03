#ifndef FLAG_H
#define FLAG_H

#include <vector>

class Action
{
  private:
    // attributes:
    string name;
    char letter;
  public:
    // constructors:
    Flag() {} // default
    Flag(string name, char letter): name_(name) letter_(letter) {} // full
    // destructor:
    ~Flag() {}
    // accessors:
    string getName() {return(name);}
    char getLetter() {return(letter);}
};

#endif
