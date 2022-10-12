# Crypt3
Command line extension for encrypting and decrypting the length, values, and positions of data on the Windows OS.

## Description:
Crypt3 is a command line extension for encrypting and decrypting data. The crypt3 cypher uses three algorithms to encrypt data attempting to completely obfuscate the data. These functions are split up to encrypt and decrypt the length, values, or positions of data.

The length algorithm scatters a variable number of bytes into the data. The value algorithm the data with bytes. The position algorithm sorts the data by a key.

These functions hide the true length of the file, introduce the possibility of false bytes, and change bytes values, and scramble their positions in the data. This allows for a lot more possibilities of what the data could be. These algorithms make it very difficult to backtrack from a known encrypted file to the key used to encrypt it. Additionaly the false bytes make each encrypted version of the file unique.

## Installation:
Save the crypt3 executable, and add its location to the path enviroment variable.

## Usage:
Crypt3 /[action] [file] [keyFile] -[flags...]  
Crypt3 /[action] [fromFile] [toFile] [keyFile] -o -[flags...]
