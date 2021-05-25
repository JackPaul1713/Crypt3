#include <cstdlib>
#include <ctime>

static bool init = (srand(time(0)), true);
bool generateRandomBool(double seed)
{
  srand(rand() + seed * 10000000);
  return(rand() % 2);
}
char generateRandomChar(double seed)
{
  srand(rand() + seed * 10000000);
  return((rand() % 256) - 128);
}
int generateRandomInt(double seed)
{
  srand(rand() + seed * 10000000);
  return(rand());
}
