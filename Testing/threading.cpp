// Link: https://stackoverflow.com/questions/19463602/compiling-multithread-code-with-g
// Detecting enter key: http://www.cplusplus.com/forum/beginner/2624/
// Timed delay: https://stackoverflow.com/questions/158585/how-do-you-add-a-timed-delay-to-a-c-program
// Threading: https://stackoverflow.com/questions/266168/simple-example-of-threading-in-c
// simultaneous IO: https://stackoverflow.com/questions/6736536/c-input-and-output-to-the-console-window-at-the-same-time
// Compile with: g++ -std=c++11 threading.cpp -lpthread -o threading

#include <atomic>
#include <thread>
#include <iostream>
#include <chrono>

using namespace std::this_thread; // sleep_until
using namespace std::chrono;    // system_clock, seconds

void ReadCin(std::atomic<bool> &run) {
  // Automatically loads and returns the current value of the atomic variable.
  while(run.load()) {
    // Once user has pressed the ENTER key, exit.
    if(std::cin.get() == '\n') {
      run.store(false);
    }
  }
}

int main() {
  // Explicitly set to synchronize two threads.
  std::atomic<bool> run(true);
  std::thread cinThread(ReadCin, std::ref(run));
  int count = 0;
  
  std::cout << "Starting timer...\n";
  std::cout << "Press the ENTER key to stop...";

  while(run.load()) {
    sleep_until(system_clock::now() + seconds(1));
    count++;
  }
  run.store(false);
  cinThread.join();
  
  std::cout << "Time elapsed: " << count << " sec.\n";
  
  return 0;
}
