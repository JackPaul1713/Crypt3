#include <windows.h>
#include <fileapi.h>
#include <filesystem>
#include <stdio.h>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

bool valid(std::string file)
{
  for(int i = 0; i < file.size(); i++)
    if(file[i] < 32 && file[i] != 127)
      return false;
  return true;
}
bool exists(std::string file)
{
  std::ifstream check(file);
  if (!check)
  {
    return false;
  }
  return true;
}
int fileLength(string file)
{
  // variables:
  int length; // length of file
  streampos begin; // begining position
  streampos end; // end position
  ifstream ifs(file, ios::binary);
  // find length:
  begin = ifs.tellg(); // get begining position
  ifs.seekg(0, ios::end); // move stream position to the end
  end = ifs.tellg(); // get end positon
  length = end - begin; // calculate length
  // return:
  ifs.close();
  return(length); // return length
}
char* readFile(string file)
{
  // variables:
  int length = fileLength(file); // length of file
  char* data = new char[length]; // file contents
  ifstream ifs(file, ios::binary);
  // read:
  ifs.read(data, length); // read file
  //return:
  ifs.close();
  return(data); // return data
}
void writeFile(string file, char* data, int length)
{
  // variables:
  ofstream ofs(file, ios::binary);
  // write:
  ofs.write(data, length); // write file
  ofs.close();
}
void renameFile(string file, string newFile)
{
  // variables:
  char* file_ = new char[file.length()];
  char* newFile_ = new char[newFile.length()];
  // copy data:
  strcpy(file_, file.c_str()); // convert string to cstring
  strcpy(newFile_, newFile.c_str());// convert string to cstring
  // rename:
  rename(file_, newFile_);
}
void getFileTimes(string file, FILETIME& created, FILETIME& modified, FILETIME& accessed)
{
  // variables:
  char* data = new char[file.length()];
  LPCSTR name;
  DWORD access = GENERIC_READ | GENERIC_WRITE; // allow read and write access
  DWORD share = 0x00000000; // no share
  DWORD action = OPEN_EXISTING; // open existing file
  DWORD attributes = FILE_ATTRIBUTE_NORMAL; // normal file attributes
  HANDLE handle;
  // settup:
  strcpy(data, file.c_str());  // copy string to cstring
  name = data; // set file name
  handle = CreateFileA(name, access, share, NULL, action, attributes, NULL); // open handle
  // set file times:
  GetFileTime(handle, &created, &accessed, &modified);
  // cleanup:
  CloseHandle(handle); // close handle
  delete[] data;
}
void setFileTimes(string file, FILETIME created, FILETIME modified, FILETIME accessed)
{
  // variables:
  char* data = new char[file.length()];
  LPCSTR name;
  DWORD access = GENERIC_READ | GENERIC_WRITE; // allow read and write access
  DWORD share = 0x00000000; // no share
  DWORD action = OPEN_EXISTING; // open existing file
  DWORD attributes = FILE_ATTRIBUTE_NORMAL; // normal file attributes
  HANDLE handle;
  // settup:
  strcpy(data, file.c_str());  // copy string to cstring
  name = data; // set file name
  handle = CreateFileA(name, access, share, NULL, action, attributes, NULL); // open handle
  // set file times:
  SetFileTime(handle, &created, &accessed, &modified);
  // cleanup:
  CloseHandle(handle); // close handle
  delete[] data;
}
