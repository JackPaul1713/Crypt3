#ifndef CRYPTION_H
#define CRYPTION_H

#include <vector>
#include <string>
#include "Action.h"

class Generate: pubic Action
{
  protected:
    // attributes:
    const string name = "generate";
    const vector<string> flags = {};
    string file = "";
    int length = "";
};

#endif
