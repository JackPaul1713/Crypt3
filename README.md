# Crypt3
Command line extension for encrypting and decrypting the length, values, and positions of data

## Description:
Crypt3 is a command line extension for encrypting and decrypting data. The crypt3 cypher uses three functions to encrypt data attempting to completely obfuscate the data. These functions are split up to encrypt and decrypt length, values, or positions of data. Each function has it's own key.

The length function scatters a variable number of bytes into the data.

The value function adds bytes to the data.

The position function sorts the data by a key.

These functions hide the true length of the file, introduce the possibility of false bytes, and change bytes values and positions in the data. This allows for a lot more possibilities of what the data could be. One cool thing this does is make it impossible to backtrack from a decrypted version of data and an encrypted version data to find the value of the key.

## Installation:
IN PROGRESS

## Usage:
Crypt3 [/action] [data] [key] [-flags...]
