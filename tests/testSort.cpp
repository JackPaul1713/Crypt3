#include <cstring>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int main()
{
  // variables:
  int length;
  char data[4] = {'q', 'w', 'e', 'r'};
  char key[4] = {'z', 'x', 'c', 'v'};
  int indexes[4] = {0, 1, 2, 3};
  // values:
  cout << "values: " << endl;
  cout << "  data: "; for(char c: data) cout << c; cout << endl;
  cout << "  key: "; for(char c: key) cout << c; cout << endl;
  cout << "  indexes: "; for(int i: indexes) cout << i; cout << endl;
  // encrypt:
  std::sort(data, data + 4, [&](char n0, char n1) {return(key[n0] < key[n1]);});
  cout << "encrypted: " << endl;
  cout << "  data: "; for(char c: data) cout << c; cout << endl;
  cout << "  key: "; for(char c: key) cout << c; cout << endl;
  cout << "  indexes: "; for(int i: indexes) cout << i; cout << endl;
  // decrypt:
  std::sort(indexes, indexes + 4, [&](char n0, char n1) {return(key[n0] < key[n1]);});
  std::sort(data, data + 4, [&](int n0, int n1) {return(indexes[n0] < indexes[n1]);});
  cout << "decrypted: " << endl;
  cout << "  data: "; for(char c: data) cout << c; cout << endl;
  cout << "  key: "; for(char c: key) cout << c; cout << endl;
  cout << "  indexes: "; for(int i: indexes) cout << i; cout << endl;
  return(0);
}
