# Crypt3
Command line extension for symmetric encryptio of files on the Windows OS.

## Description:
Crypt3 is a command line extension for encrypting and decrypting files. The crypt3 cypher is made up of three algorithms. These algorithms are split up to encrypt and decrypt the length, values, or positions of data.

The length algorithm scatters a variable number of bytes into the data. The value algorithm sums the data with bytes. The position algorithm sorts the data by a key.

These functions hide the true length of the file, introduce the possibility of false bytes, and change bytes values, and scramble their positions in the data. This allows for a lot more possibilities of what the data could be. These algorithms make it very difficult to backtrack from a known encrypted file to the key used to encrypt it. Additionally the false bytes make each encrypted version of the file unique.

## Complexety
Overall the crypt3 cypher is O(nlog2(n))

The position algorithm is O(nlog2(n))
The value algorithm is O(n)
The length algorithm is O(n)

Where n is the length of the data.

## Installation:
Save the crypt3 executable, and add its location to the path environment variable.

## Usage:
Crypt3 /[action] [file] [keyFile] -[flags...]  
Crypt3 /[action] [fromFile] [toFile] [keyFile] -o -[flags...]
