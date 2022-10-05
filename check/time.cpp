#include <iostream>
#include <time.h>
int main(){
 clock_t start,finish;
 start = clock();
 for(int i = 1;i<1000; i*=5)
 {
  std::cout<<i<<std::endl;
 }
 finish = clock();
 std::cout<<finish-start<<std::endl;
 return 0;
}