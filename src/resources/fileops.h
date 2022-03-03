#ifndef FILE_H
#define FILE_H

#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <string>

/* the following functions can be modified for differnt operating systems */
int fileLength(std::string file); // gets file length
char* readFile(std::string file); // reads file data
void renameFile(std::string file, std::string newFile); // renames file
void writeFile(std::string file, char* data, int length); // writes data to file
void getFileTimes(std::string file, FILETIME& created, FILETIME& modified, FILETIME& accessed); // TODO
void setFileTimes(std::string file, FILETIME created, FILETIME modified, FILETIME accessed); // TODO

#endif
