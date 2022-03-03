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
