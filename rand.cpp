#include"rand.h"
using namespace dpcl;
int Rand::seed=1;
bool Rand::sranded;
std::mutex Rand::lock;