#include <string>
#include <vector>
#include "Cypher.h"

//// save ////
void upload(string filename, string password);
void download(string filename, string password);

// mutators:
void changeLength(int newLength);
void regenerate();

//// helpers ////
friend void swap(Key& key0, Key& key1)
{
  // swap all attributes between objects:
  swap(key0.key, key1.key);
}
char generateRandomByte(int number, int modifier)
{

}
std::vector<char> generateKey(int length) // generates key of lenght length(parameter)
{

}
