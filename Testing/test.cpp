#include <iostream>
#include <chrono>
#include <thread>
using namespace std::this_thread;
using namespace std::chrono;

int main() {
  std::cout << "Time Passed: 0 sec" << std::endl;
  for(int i = 1; i <= 10; i++) {
    sleep_until(system_clock::now() + seconds(1));
    std::cout << "Time Passed: " << i <<" sec" << std::endl;
  }
  
  return 0;
}
