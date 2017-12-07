#include <iostream>
#include <thread>
#include <string>
using namespace std::this_thread; // sleep_until
using namespace std::chrono;  // system_clock, seconds


int main() {
  std::cout << "The counter has started. Press the ENTER key to stop counter...\n";
  int count = 0;
  char input;
  do {
    std::cout << count << " sec" << std::endl;
    count++;
    sleep_until(system_clock::now() + seconds(1));
  }
  //while((std::cin.get()) != '\n');
  while(count < 10);
  
  std::cout << "You waited "<< count << " seconds to press enter."<< std::endl;
  std::cout << "Goodbye." << std::endl;
  
  return 0;
}
