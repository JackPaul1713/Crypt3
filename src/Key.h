#ifndef KEY_H
#define KEY_H

#include <string>
#include <vector>

class Key
{
  private:
    // attributes:
    float percentIncrease_;
    std::vector<bool> lenKey_; // length key
    std::vector<char> valKey_; // value key
    std::vector<int> locKey_; // location key
    // helpers:
    float generatePercentIncreace(); // generates percent increase
    std::vector<bool> generateLenKey(int length); // generates length key
    std::vector<char> generateValKey(int length); // generates value key
    std::vector<int> generateLocKey(int length); // generates location key
  public:
    // constructors:
    Key(): percentIncrease_(0) {} // default
    Key(int length); // generate
    Key(char* characters, int length); // c-string custom
    Key(std::string str); // string custom
    Key(const Key& key); // copy
    // deconstructor:
    ~Key() {}
    // save:
    void upload(std::string filename, std::string password);
    void download(std::string filename, std::string password);
    // accessors:
    float percentIncrease() {return(percentIncrease_);}
    std::vector<bool>& lenKey() {return(lenKey_);}
    std::vector<char>& valKey() {return(valKey_);}
    std::vector<int>& locKey() {return(locKey_);}
    // mutators:
    void regenerate(int length = -1, bool lenP = true, bool len = true, bool val = true, bool loc = true);
    // helpers:
    friend void swap(Key& key0, Key& key1);
    // overloads:
    Key& operator=(Key key) {swap(*this, key); return(*this);}
};

#endif
