/* Author  : Joseph Leovao
 * Date    : November 24, 2017
 * Filename: main.cpp
 * Purpose : This client program uses the Mash.h class to simulate
 *           a game that we all used to play when we were children.
 *           This game is called MASH, which is a pencil-and-paper 
 *           2-player game which is used to predict one's future.
 * Compile : g++ -std=c++11 main.cpp Mash.cpp -lpthread -o Mash
 * Run     : ./Mash
 */

#include <iostream>
#include <string>
#include <atomic>
#include <thread>
#include <chrono>
#include "Mash.h"
using namespace std::this_thread; // sleep_until
using namespace std::chrono;    // system_clock, seconds

// Function prototypes
void getMash(int);
void startingMenu();

// Executes in another thread while waiting for user input
void ReadCin(std::atomic<bool> &run) {
  // Automatically loads and returns the current value of the atomic variable.
  while(run.load()) {
    // Once user has pressed the ENTER key, exit.
    if(std::cin.get() == '\n') {
      run.store(false);
    }
  }
}

// Main Function
int main() {
  bool generate_mash;
  char uInput, begin;

  // Clears screen and prints opening menu
  std::cout << std::string(50,'\n');
  startingMenu();
  
  std::cout << "We will begin the program by starting a timer to determine\n";
  std::cout << "the number of ticks that will be used to determine your MASH story.\n";
  std::cout << "\nEnter 's' to start: ";
  std::cin >> begin;

  while ((char)toupper(begin) != 'S') {
    std::cout << "Invalid Input!\nEnter 's' to start timer: ";
    std::cin >> begin;
  }
  std::cin.ignore();
  
  std::atomic<bool> run(true);
  
  // Spawning a new thread
  std::thread cinThread(ReadCin, std::ref(run));
  
  int count = 0;
  
  std::cout << "Starting timer...\n";
  std::cout << "Press the ENTER key to stop...";

  while(run.load()) {
    // Increments counter every half second until user enters ENTER key
    sleep_until(system_clock::now() + nanoseconds(500000000));
    count++;
  }
  run.store(false);
  // Blocks current thread until the cinThread thread finishes execution
  cinThread.join();
  std::cout << "\nYour special number is " << count << ".\n";
  
  // Ask user if they would like to input their own data or use existing
  // values from a text file.
  std::cout << "Would you like to create your own data for MASH?\n";
  std::cout << "Enter 'y' for yes or 'n' for no: ";
  std::cin >> uInput;
  uInput = (char)toupper(uInput);
  // Input validation for mash generation using pretest loop
  while (uInput != 'Y' && uInput != 'N') {
    std::cout << "Invalid Input!\nEnter 'y' for yes or 'n' for no: ";
    std::cin >> uInput;
    std::cout << "You entered: " << (char)uInput << std::endl;
  } 

  // Capitalize input for ease
  uInput = (char)toupper(uInput);
  if(uInput == 'Y') {
    generate_mash = true;
    std::cout << "User-Generated Mash commencing...\n\n";
  } else {
    generate_mash = false;
    std::cout << "MASH automatically generating...\n\n";
  }
  // Create a new Mash object to initialize game.
  Mash newGame(generate_mash, count);
  
  return 0;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                 startingMenu                              *
 * Input  : None                                                             *
 * Output : None                                                             *
 * Purpose: This function just prints out the word MASH in a big font.       *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void startingMenu() {
  const std::string cyan("\033[0;36m");
  const std::string reset("\033[0m");

  std::cout << cyan << " * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << reset << std::endl;
  std::cout << cyan << " *"<< reset <<"    __        __    _______    _______     _     _   "<< cyan << "*" << reset << std::endl;
  std::cout << cyan << " *"<< reset <<"   |  \\      /  |  |  ___  |  |  _____|   | |   | |  "<< cyan << "*" << reset << std::endl;
  std::cout << cyan << " *"<< reset <<"   |    |   |   |  | |___| |  | |_____    | |___| |  "<< cyan << "*" << reset << std::endl;
  std::cout << cyan << " *"<< reset <<"   | |\\  \\ /  | |  |  ___  |  |_____  |   |  ___  |  "<< cyan << "*" << reset << std::endl;
  std::cout << cyan << " *"<< reset <<"   | | \\     /| |  | |   | |        | |   | |   | |  "<< cyan << "*" << reset << std::endl;
  std::cout << cyan << " *"<< reset <<"   | |  \\   / | |  | |   | |   _____| |   | |   | |  "<< cyan << "*" << reset << std::endl;
  std::cout << cyan << " *"<< reset <<"   |_|   \\_/  |_|  |_|   |_|  |_______|   |_|   |_|  "<< cyan << "*" << reset << std::endl;
  std::cout << cyan << " *"<< reset <<"                                                     "<< cyan << "*" << reset  << std::endl;
  std::cout << cyan << " * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n" << reset << std::endl;
  std::cout << "Welcome to my MASH Program! MASH is a pencil-and-paper game\n";
  std::cout << "commonly played by children intended to predict one's future.\n";


}