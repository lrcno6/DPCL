#ifndef _RAND_H_
#define _RAND_H_
#include<mutex>
#include<ctime>
namespace dpcl{
	class Rand{
		public:
			static int rand(){
				using namespace std;
				lock_guard<mutex> l(lock);
				if(!sranded){
					srand(time(nullptr));
					sranded=true;
				}
				return ((seed=seed*214013L+2531011L)>>16)&0x7fff;
			}
		private:
			static int seed;
			static bool sranded;
			static std::mutex lock;
			static void srand(int s){
				seed=s;
			}
	};
}
#endif