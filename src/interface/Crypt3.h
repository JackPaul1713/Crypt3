#ifndef CRYPT3_H
#define CRYPT3_H

#include <iostream> // DEBUG
#include "Command.h"
#include "Action.h"
#include "Encrypt.h"
#include "Decrypt.h"
#include "Help.h"

class Crypt3: public Command
{
  private:
    // helpers:
    void initiate() {name = "crypt3"; this->actions = {new Encrypt, new Decrypt, new Help};} // loads preset data
    void reset() {}
  public:
    // constructors:
    Crypt3() {initiate();} // default
    Crypt3(const Crypt3& crypt3): Command(crypt3) {} // copy
    // destructor:
    ~Crypt3() {}
    // friends:
    friend void swap(Crypt3& c0, Crypt3& c1) {std::swap(c0.name, c1.name); std::swap(c0.actions, c1.actions); std::swap(c0.selectedAction, c1.selectedAction);};
    // overloads:
    Crypt3& operator=(Crypt3 crypt3) {swap(*this, crypt3); return(*this);} // assignment
};

#endif
