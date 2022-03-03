#include <iostream>
#include "../src/Cypher.h"
#include "../src/Key.h"
#include "../src/SortedIndex.h"
#include "../src/resources/random.h"

using namespace std;

static bool init = (srand(time(0)), true); // seed rand

char* generateData(int length) // generates random data
{
  char* data = new char[length];
  for(int i = 0; i < length; i++) // fill data
  {
    data[i] = rand() % 256; // generate random character
  }
  return(data);
}

int compareEncrypted(Cypher cypher, char* data, int length, char* expectedData, int expectedLength, int type) // encrypts data and compares encrypted data to expected encrypted data
{

}
int compareFinal(char* data, int length, int type) // encrypts and decrypts data and compares decrypted data to original data
{
  // variables:
  Cypher cypher(Key(length / 2));
  char* expectedData = new char[length];
  for(int i = 0; i < length; i++) {expectedData[i] = data[i];} // copy over original data
  bool expected = true;

  // encryption and decryption:
  if(type == 0)
  {
    cypher.encryptLen(data, length);
    cypher.decryptLen(data, length);
  }
  else if(type == 1)
  {
    cypher.encryptVal(data, length);
    cypher.decryptVal(data, length);
  }
  else if(type == 2)
  {
    cypher.encryptPos(data, length);
    cypher.decryptPos(data, length);
  }
  else if(type == 3)
  {
    cypher.encrypt(data, length);
    cypher.decrypt(data, length);
  }

  // compare:
  for(int i = 0; i < length; i++)
  {
    if(data[i] != expectedData[i])
    {
      expected = false;
    }
  }
  if(!expected)
  {
    cout << "TEST FAILED" << endl;
    cout << "expected:" << endl;
    for(int i = 0; i < length; i++) cout << int(data[i]) << " ";
    cout << endl;
    cout << "actual:" << endl;
    for(int i = 0; i < length; i++) cout << int(expectedData[i]) << " ";
    cout << endl;
  }

  // return:
  delete[] expectedData;
  return(expected);
}

int main()
{
  // variables:
  bool encryptedTests = false;
  int finalTests = 10; // number of final tests to run
  bool testLenEncryption = true;
  bool testValEncryption = true;
  bool testPosEncryption = true;
  bool testFullEncryption = true;

  // length tests:
  if(testLenEncryption)
  {
    cout << "Length Encryption Tests: " << endl;
    if(encryptedTests)
    {
      cout << "  Encrypted Tests: " << endl;
    }
    if(finalTests)
    {
      cout << "  Final Tests:" << endl;
      // variable:
      int passed = 0;

      // tests:
      for(int i = 0; i < finalTests; i++)
      {
        int length = rand() % 91 + 10; // generate random length
        char* data = generateData(length);
        passed += compareFinal(data, length, 0);
        delete[] data;
      }
      cout << "    " << passed << "/" << finalTests << " passed" << endl;
    }
  }

  // value tests:
  if(testLenEncryption)
  {
    cout << "Value Encryption Tests: " << endl;
    if(encryptedTests)
    {
      cout << "  Encrypted Tests: " << endl;
    }
    if(finalTests)
    {
      cout << "  Final Tests:" << endl;
      // variable:
      int passed = 0;

      // tests:
      for(int i = 0; i < finalTests; i++)
      {
        int length = rand() % 91 + 10; // generate random length
        char* data = generateData(length);
        passed += compareFinal(data, length, 1);
        delete[] data;
      }
      cout << "    " << passed << "/" << finalTests << " passed" << endl;
    }
  }

  // postions tests:
  if(testPosEncryption)
  {
    cout << "Position Encryption Tests: " << endl;
    if(encryptedTests)
    {
      cout << "  Encrypted Tests: " << endl;
    }
    if(finalTests)
    {
      cout << "  Final Tests:" << endl;
      // variable:
      int passed = 0;

      // tests:
      for(int i = 0; i < finalTests; i++)
      {
        int length = rand() % 21 + 10; // generate random length
        char* data = generateData(length);
        passed += compareFinal(data, length, 2);
        delete[] data;
      }
      cout << "    " << passed << "/" << finalTests << " passed" << endl;
    }
  }

  // full tests:
  if(testFullEncryption)
  {
    cout << "Full Encryption Tests: " << endl;
    if(encryptedTests)
    {
      cout << "  Encrypted Tests: " << endl;
    }
    if(finalTests)
    {
      cout << "  Final Tests:" << endl;
      // variable:
      int passed = 0;

      // tests:
      for(int i = 0; i < finalTests; i++)
      {
        int length = rand() % 91 + 10; // generate random length
        char* data = generateData(length);
        passed += compareFinal(data, length, 3);
        delete[] data;
      }
      cout << "    " << passed << "/" << finalTests << " passed" << endl;
    }
  }
}
