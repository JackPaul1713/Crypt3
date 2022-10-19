#include <cstdlib>
#include <ctime>

using namespace std;

static bool init = (srand(time(0)), true);
bool randomBool(double seed)
{
  srand(rand() + seed);
  return(rand() % 2);
}
char randomChar(double seed)
{
  srand(rand() + seed);
  return((rand() % 256) - 128);
}
char randomFileChar(double seed)
{
  srand(rand() + seed);
  char fileChar = rand() % 62;
  if(fileChar < 10) fileChar += 48; // 0x30
  else if(fileChar < 36) fileChar += (65 - 10); // 0x41
  else fileChar += (97 - 36); // 0x61
  return(fileChar);
}
int randomInt(double seed)
{
  srand(rand() + seed);
  return(rand());
}
int fixedRandom(double seed)
{
  srand(seed);
  return(rand());
}
