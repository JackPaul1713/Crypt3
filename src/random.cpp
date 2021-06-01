#include <cstdlib>
#include <ctime>

static bool init = (srand(time(0)), true);
bool randomBool(double seed)
{
  srand(rand() + seed * 10000000);
  return(rand() % 2);
}
char randomChar(double seed)
{
  srand(rand() + seed * 10000000);
  return((rand() % 256) - 128);
}
int randomInt(double seed)
{
  srand(rand() + seed * 10000000);
  return(rand());
}
