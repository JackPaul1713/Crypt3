#ifndef KEY_H
#define KEY_H

#include <string>
#include <vector>

class Key
{
  private:
    // attributes:
    std::vector<bool> lenKey_;
    std::vector<char> valKey_;
    std::vector<int> locKey_;
    // helpers:
    std::vector<bool> generateLenKey(int length); // generates length key
    std::vector<char> generateValKey(int length); // generates value key
    std::vector<int> generateLocKey(int length); // generates location key
  public:
    // constructors:
    Key() {} // default
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
    std::vector<bool> lenKey() {return(lenKey_);}
    std::vector<char> valKey() {return(valKey_);}
    std::vector<int> locKey() {return(locKey_);}
    bool lenAt(int pos) {return(lenKey_.at(pos));}
    char valAt(int pos) {return(valKey_.at(pos));}
    int locAt(int pos) {return(locKey_.at(pos));}
    int lenLength() {return(lenKey_.size());}
    int valLength() {return(valKey_.size());}
    int locLength() {return(locKey_.size());}
    // mutators:
    void regenerate(int length = -1, bool len = true, bool val = true, bool loc = true);
    // helpers:
    friend void swap(Key& key0, Key& key1);
    // overloads:
    Key& operator=(Key key) {swap(*this, key); return(*this);}
};

#endif
