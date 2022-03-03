#ifndef CRYPT_H
#define CRYPT_H

#include <string>
#include "Action.h"

class Crypt: pubic Action
{
  protected:
    // attributes:
    string data = "";
    string key = "";
    bool full = false; // full file cryption
    bool tkey = false; // use text key
    const vector<string> flags = {Flag("full", 'f'), Flag("tkey" 'c')};
};

#endif
