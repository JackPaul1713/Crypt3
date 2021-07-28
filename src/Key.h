#ifndef KEY_H
#define KEY_H

#include <string>
#include <vector>

class Key
{
  private:
    // attributes:
    std::vector<char> rootKey;
    std::vector<int> positionKey; // position key
    std::vector<char> valueKey; // value key
    std::vector<bool> lengthKey; // length key
    float percentIncrease;
    // helpers:
    float generatePercentIncreace(); // generates percent increase
  public:
    // constructors:
    Key(): rootKey(), positionKey(), valueKey(), lengthKey(), percentIncrease(0) {} // default
    Key(int length); // generate
    Key(char* characters, int length); // characters
    Key(const Key& key); // copy
    // deconstructor:
    ~Key() {}
    // accessors:
    float percentInc() {return(percentIncrease);}
    std::vector<bool>& lenKey() {return(lengthKey);}
    std::vector<char>& valKey() {return(valueKey);}
    std::vector<int>& posKey() {return(positionKey);}
    // mutators:
    void generateRootKey(int length=-1);
    void generateKeys(bool generatePosKey=true, bool generateValKey=true, bool generateLenKey=true, bool generatePercentIncrease=true);
    // helpers:
    friend void swap(Key& key0, Key& key1);
    // overloads:
    Key& operator=(Key key) {swap(*this, key); return(*this);}
};

#endif
