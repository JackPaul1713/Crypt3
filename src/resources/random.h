#ifndef RANDOM_H
#define RANDOM_H

/* the following fuctions can be modified for more secure random numbers */
bool randomBool(double seed = 0.0); // returns a random boolean
char randomChar(double seed = 0.0); // returns a random character
int randomInt(double seed = 0.0); // return a random integer
int fixedRandom(double seed); // returns the same random for the same seed

#endif
