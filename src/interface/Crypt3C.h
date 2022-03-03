#ifndef CRYPT3C_H
#define CRYPT3C_H

#include "Command.h"
#include "Encrypt.h"
#include "Decrypt.h"
#include "Generate.h"
#include "Help.h"

class Crypt: public Command
{
  private:
    // attributes
    const string name = crypt3;
    const vector<Action> actions = {Encrypt encrypt, Decrypt decrypt, Generate generate, Help help};
  public:
    // constructors:
    Crypt() {} // default
    // destructor:
    ~Crypt() {}
    // friends:
      // TODO
    // overloads:
      // TODO
};

#endif
