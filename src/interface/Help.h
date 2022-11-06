#ifndef HELP_H
#define HELP_H

#include <vector>
#include "Action.h"

//// objects ////
class Help: public Action
{
  protected:
    // actions:
    void execute(std::vector<std::string> arguments);
    // helpers:
    void initiate() {this->name = "help"; this->letter = 'h';} // loads preset data
    void activate() {} // activates input data
    void reset() {} // wipes input data
  public:
    // constructors:
    Help() {initiate();} // default
    // Help(const Help& help); // copy
    // destructor:
    ~Help() {}
    // friends:
    //friend void swap(Help h0, Help h1);
    // overloads:
    //Help& operator=(Help help) {swap(*this, help); return(*this);} // assignment
};

#endif
