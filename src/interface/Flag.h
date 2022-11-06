#ifndef FLAG_H
#define FLAG_H

#include <vector>
#include <string>

class Flag
{
  private:
    // attributes:
    std::string name; // flag name
    char letter; // flag letter
    bool valued; // flag has value
    std::string value; // flag value
    std::vector<char> incompatibilities; // incompatibile flags
  public:
    // constructors:
    Flag(): name(), letter(), valued(), value(), incompatibilities() {} // default
    Flag(std::string name, char letter): name(name), letter(letter), valued(false), value(""), incompatibilities({}) {} // full
    Flag(std::string name, char letter, std::vector<char> incompatibilities): name(name), letter(letter), valued(false), value(""), incompatibilities(incompatibilities) {} // incompatibile
    Flag(std::string name, char letter, bool valued, std::string value, std::vector<char> incompatibilities): name(name), letter(letter), valued(valued), value(value), incompatibilities(incompatibilities) {} // valued
    // destructor:
    ~Flag() {}
    // accessors:
    std::string getName() {return(name);}
    char getLetter() {return(letter);}
    bool isValued() {return(valued);}
    std::string getValue() {return(value);}
    std::vector<char> getIncompatibilities() {return(incompatibilities);}
    // mutators:
    void setValue(std::string value) {this->value = value;}
    // friends:
    friend void swap(Flag f0, Flag f1) {std::swap(f0.name, f1.name); std::swap(f0.letter, f1.letter); std::swap(f0.valued, f1.valued); std::swap(f0.value, f1.value); std::swap(f0.incompatibilities, f1.incompatibilities);};
    // overloads:
    Flag& operator=(Flag flag) {swap(*this, flag); return(*this);} // assignment
};

#endif
