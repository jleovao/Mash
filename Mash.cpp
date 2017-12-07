/* Author  : Joseph Leovao
 * Date    : November 24, 2017
 * Filename: Mash.cpp
 * Purpose : This is the function implementation file that defines
 *           the functions necessary to build the game MASH. 
 */

// File Mash.cpp -- Mash class of function implementation file
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <cstdlib>
#include "Mash.h"
using namespace std::this_thread; // sleep_until
using namespace std::chrono;  // system_clock, seconds

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                  Constructor                              *
 * Input  : boolean value, integer value count                               *
 * Output : None                                                             *
 * Purpose: When the constructor is called, the boolean value passed in is   *
 *          used to determine whether the user wants to input the MASH data  *
 *          manually or use existing values from a text file. The function   *
 *          manualInput is called for user inputted data and parseFile is    *
 *          used if the user does not want to enter the data. The values are *
 *          stored in vectors for now. In a later implementation, I will use *
 *          linked lists instead for better efficiency.                      *
 *          Once the data is entered, the beginMash function is called to    *
 *          eliminate values from each vector until each vector is of        *
 *          size 1. Once that is done, generateStory will be called.         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

Mash::Mash(bool input, int count) {
  char startMashing;
  setGenerateInput(input);

  if(getGenerateInput()) {
    manualInput();
  }
  else {
    // Note: Can later have the option to create and save
    //       files for later use.
    parseFile("TextFiles/input.txt");
  }

  // Prints the value from user input or file
  printData();
  std::cout << "\nPress 'm' to begin MASH: ";
  std::cin >> startMashing;
  while((char)toupper(startMashing) != 'M') {
    std::cout << "Press 'm' to begin MASH: ";
    std::cin >> startMashing;
  }
  
  // Using the data from vectors and the count from the user, begin
  // eliminating elements from each vector until one element is left
  // in each. Then save the values.
  beginMash(count, final_marrying, final_living_quarters,final_car,
            final_pet, final_occupation, final_kids, final_income,
            final_school,final_hobby, final_weight);
  
  // Same logic as beginMash but with only the building vector
  determineBuilding(count, final_building);

  ClearScreen();
  // Generate story with final variables
  generateStory(final_marrying, final_living_quarters,final_car,
            final_pet, final_occupation, final_kids, final_income,
            final_school,final_hobby, final_weight, final_building);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                              Mash::parseFile                              *
 * Input  : filename to be read                                              *
 * Output : None                                                             *
 * Purpose: This function reads from the file whose name is passed in by     *
 *          input. The function then reads in each line and stores each      *
 *          value into every category vector. For now the default number of  *
 *          elements per vector is 4.                                        *
 *          NOTE: In a later implementation, I can allow more than 4         *
 *                elements per category and just select 4 elements randomly  *
 *                from each category. It would make the game more            *
 *                interesting. Use rand() % #number of elements per vector.  *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void Mash::parseFile(std::string filename) {
  std::ifstream inFile;
  int numOpt;
  std::string string1, string2, string3, string4;
  int int1, int2, int3, int4;

  inFile.open(filename);
  if(inFile.fail()) {
    std::cout << "Error opening " << filename << std::endl;
  }
  else {
    // Marriage category
    std::getline(inFile, string1);
    std::getline(inFile, string2);
    std::getline(inFile, string3);
    std::getline(inFile, string4);
    marrying = {string1, string2, string3, string4};
    // Living Quarters category
    std::getline(inFile, string1);
    std::getline(inFile, string2);
    std::getline(inFile, string3);
    std::getline(inFile, string4);
    living_quarters = {string1, string2, string3, string4};
    // Car category
    std::getline(inFile, string1);
    std::getline(inFile, string2);
    std::getline(inFile, string3);
    std::getline(inFile, string4);
    car = {string1, string2, string3, string4};
    // Pet category
    std::getline(inFile, string1);
    std::getline(inFile, string2);
    std::getline(inFile, string3);
    std::getline(inFile, string4);
    pet = {string1, string2, string3, string4};
    // Occupation category
    std::getline(inFile, string1);
    std::getline(inFile, string2);
    std::getline(inFile, string3);
    std::getline(inFile, string4);
    occupation = {string1, string2, string3, string4};
    // Kids category
    inFile >> int1 >> int2 >> int3 >> int4;
    kids = {int1, int2, int3, int4};
    // Income category
    inFile >> int1 >> int2 >> int3 >> int4;
    income = {int1, int2, int3, int4};

    // Need to read in the rest of the line
    std::getline(inFile, string1);

    // School category
    std::getline(inFile, string1);
    std::getline(inFile, string2);
    std::getline(inFile, string3);
    std::getline(inFile, string4);
    school = {string1, string2, string3, string4};
    // Hobby category
    std::getline(inFile, string1);
    std::getline(inFile, string2);
    std::getline(inFile, string3);
    std::getline(inFile, string4);
    hobby = {string1, string2, string3, string4};
    // Weight category
    inFile >> int1 >> int2 >> int3 >> int4;
    weight = {int1, int2, int3, int4};
    inFile.close();

    // Building vector is always the same
    building = {"mansion","apartment","shack","house"};
  }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                           Mash::manualInput                               *
 * Input  : None                                                             *
 * Output : None                                                             *
 * Purpose: This function prompts the user to input values for every         *
 *          category. The default for now is 4 but I can scale it up         *
 *          to any value in future updates. When the user is prompted to     *
 *          enter an integer value, the checkInt function is called to make  *
 *          sure the user has entered an Integer value.                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void Mash::manualInput() {
  std::string string1, string2, string3, string4;
  int int1, int2, int3, int4;
  std::cout << "\nFor each value, enter one value at a time. Make sure you use"
       << " numbers when necessary!" << std::endl;
  std::cout << "Example:\n";
  std::cout << "Dog [Press Enter]" << std::endl;
  std::cout << "Cat [Press Enter]" << std::endl;  
  std::cout << "Gorilla [Press Enter]" << std::endl;
  std::cout << "Snake [Press Enter]\n" << std::endl;

  // Note: in a future implementation, I want to simplify this
  //       via helper function. It should take in the reference values
  //       and assign it to user input and finally initialize the 
  //       vector passed into the parameter
  std::cout << "Enter values for people to marry:" << std::endl;
  std::cout << "1) ";
  std::cin.ignore();
  std::getline(std::cin, string1);
  std::cout << "2) ";
  std::getline(std::cin, string2);
  std::cout << "3) ";
  std::getline(std::cin, string3);
  std::cout << "4) ";
  std::getline(std::cin, string4);
  marrying = {string1, string2, string3, string4};
  
  std::cout << "Enter cities:" << std::endl;
  std::cout << "1) ";
  std::getline(std::cin, string1);
  std::cout << "2) ";
  std::getline(std::cin, string2);
  std::cout << "3) ";
  std::getline(std::cin, string3);
  std::cout << "4) ";
  std::getline(std::cin, string4);
  living_quarters = {string1, string2, string3, string4};

  std::cout << "Enter cars here:" << std::endl;
  std::cout << "1) ";
  std::getline(std::cin, string1);
  std::cout << "2) ";
  std::getline(std::cin, string2);
  std::cout << "3) ";
  std::getline(std::cin, string3);
  std::cout << "4) ";
  std::getline(std::cin, string4);
  car = {string1, string2, string3, string4};   
  
  std::cout << "Enter any kind of pet:" << std::endl;
  std::cout << "1) ";
  std::getline(std::cin, string1);
  std::cout << "2) ";
  std::getline(std::cin, string2);
  std::cout << "3) ";
  std::getline(std::cin, string3);
  std::cout << "4) ";
  std::getline(std::cin, string4);
  pet = {string1, string2, string3, string4};

  std::cout << "Enter values for jobs:" << std::endl;
  std::cout << "1) ";
  std::getline(std::cin, string1);
  std::cout << "2) ";
  std::getline(std::cin, string2);
  std::cout << "3) ";
  std::getline(std::cin, string3);
  std::cout << "4) ";
  std::getline(std::cin, string4);
  occupation = {string1, string2, string3, string4};

  std::cout << "Enter random positive numbers:" << std::endl;
  std::cout << "1) ";
  std::cin >> int1;
  checkInt(1, int1);
  std::cout << "2) ";
  std::cin >> int2;
  checkInt(2, int2);
  std::cout << "3) ";
  std::cin >> int3;
  checkInt(3, int3);
  std::cout << "4) ";
  std::cin >> int4;
  checkInt(4, int4);
  kids = {int1, int2, int3, int4};

  std::cout << "Enter random positive numbers to represent income:" << std::endl;
  std::cout << "1) ";
  std::cin.ignore();
  std::cin >> int1;
  checkInt(1, int1);
  std::cout << "2) ";
  std::cin >> int2;
  checkInt(2, int2);
  std::cout << "3) ";
  std::cin >> int3;
  checkInt(3, int3);
  std::cout << "4) ";
  std::cin >> int4;
  income = {int1, int2, int3, int4};

  std::cout << "Enter schools here:" << std::endl;
  std::cout << "1) ";
  std::cin.ignore();
  std::getline(std::cin, string1);
  std::cout << "2) ";
  std::getline(std::cin, string2);
  std::cout << "3) ";
  std::getline(std::cin, string3);
  std::cout << "4) ";
  std::getline(std::cin, string4);
  school = {string1, string2, string3, string4};

  std::cout << "Enter some hobbies or things you like to do:" << std::endl;
  std::cout << "1) ";
  std::getline(std::cin, string1);
  std::cout << "2) ";
  std::getline(std::cin, string2);
  std::cout << "3) ";
  std::getline(std::cin, string3);
  std::cout << "4) ";
  std::getline(std::cin, string4);
  hobby = {string1, string2, string3, string4};

  std::cout << "Enter random positive Integer values:" << std::endl;
  std::cout << "1) ";
  std::cin >> int1;
  checkInt(1, int1);
  std::cout << "2) ";
  std::cin >> int2;
  checkInt(2, int2);
  std::cout << "3) ";
  std::cin >> int3;
  checkInt(3, int3);
  std::cout << "4) ";
  std::cin >> int4;
  checkInt(4, int4);
  weight = {int1, int2, int3, int4};

  //Building vector is always the same
  building = {"mansion","apartment","shack","house"};
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                             Mash::beginMash                               *
 * Input  : counter variable and reference variables for each category       *
 * Output : None                                                             *
 * Purpose: This function uses the count variable to eliminate elements from *
 *          values of each category until there is only one element in each  *
 *          category vector. After that, each reference variable will be     *
 *          assigned to the corresponding element of each category vector.   *
 *   Note : Would like to add a helper function to shorten this function.    * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void Mash::beginMash(int count, std::string &refMarrying, 
                     std::string &refLivingQuarters, std::string &refCar, 
                     std::string &refPet, std::string &refOccupation, 
                     int &refKids, int &refIncome, std::string &refSchool, 
                     std::string &refHobby, int &refWeight) {
  // pos is an internal counter that increments after visiting every element
  // of a vector. Once pos is a multiple of count, the current element is 
  // erased. This is to simulate crossing off an element after visiting 
  // "count" number of nodes.
  int pos = 0;
  // While there exists a vector of size > 1 cycle through
  // each vector and cross off elements at every count until
  // one element remains in each vector
  while(!finishedMash()) {
    // Start at marrying vector
    crossOffCheckString(pos, marrying, count);
    // Living Quarters vector
    crossOffCheckString(pos, living_quarters, count);
    // Cars vector
    crossOffCheckString(pos, car, count);
    // Pet vector
    crossOffCheckString(pos, pet, count);
    // Occupation vector
    crossOffCheckString(pos, occupation, count);
    // Kids vector
    crossOffCheckInt(pos, kids, count);
    // Income vector
    crossOffCheckInt(pos, income, count);
    // School vector
    crossOffCheckString(pos, school, count);
    // Hobby vector
    crossOffCheckString(pos, hobby, count);
    // Weight vector
    crossOffCheckInt(pos, weight, count);

  } // end while
  
  std::cout << "Mash Complete!" << std::endl;

  // Set reference variables
  refMarrying = marrying.front();
  refLivingQuarters = living_quarters.front();
  refCar = car.front();
  refPet = pet.front();
  refOccupation = occupation.front();
  refKids = kids.front();
  refIncome = income.front();
  refSchool = school.front();
  refHobby = hobby.front();
  refWeight = weight.front();

}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                         Mash::generateStory                               *
 * Input  : Once each category has one element each, each element will be    *
 *          passed in to this function as a variable.                        *
 * Output : None                                                             *
 * Purpose: This function takes each value from input and saves it into a    *
 *          variable. Then a story is printed out using the input variables. *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void Mash::generateStory(std::string m, std::string l, std::string c, 
                        std::string p, std::string o, int k, int i, 
                        std::string s, std::string h, int w, 
                        std::string building) {
  std::string marrying = m;
  std::string living = l;
  std::string pet = p;
  std::string car = c;
  std::string occupation = o;
  int kids = k;
  int income = i;
  std::string school = s;
  std::string hobby = h;
  int weight = w;
  std::string mash = building;
  printData();
  std::cout << "\n\nStory Time!\n\n";
  std::cout << "You will graduate from " << school << ", and after graduation, you \nwill marry " << marrying; 
  std::cout << ". Both of you will settle down in \n" << living << " living in a nice " << mash << " spending your ";
  std::cout << "days\n as a " << occupation << " making $" << income << " a year driving a fancy "<< car <<".\nYou and " << marrying << " will have ";
  std::cout << kids << " kid(s) and will adopt \na " << weight << "lb pet " << pet << ". When you retire, you will spend the ";
  std::cout << "rest of your \nlife " << hobby << ".\n\nThe end!\n";
 }

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                             Mash::printData                               *
 * Input  : None                                                             *
 * Output : None                                                             *
 * Purpose: This function prints the values of the vectors holding the       *
 *          values of each category. This is used for testing purposes.      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void Mash::printData() {
  const std::string cyan("\033[0;36m");
  const std::string green_u("\033[4;32m");
  const std::string reset("\033[0m");

  std::cout << green_u << "Marry" << reset << std::endl;
  for(auto i : marrying) {
    std::cout << " - " << i << "\n";
  }

  std::cout << green_u << "Living Quarters" << reset << std::endl;
  for(auto i : living_quarters) {
    std::cout << " - " << i << "\n";
  }

  std::cout << green_u << "Car" << reset << std::endl;
  for(auto i : car) {
    std::cout << " - " << i << "\n";
  }

  std::cout << green_u << "Pet" << reset << std::endl;
  for(auto i : pet) {
    std::cout << " - " << i << "\n";
  }

  std::cout << green_u << "Occupation" << reset << std::endl;
  for(auto i : occupation) {
    std::cout << " - " << i << "\n";
  }
  
  std::cout << green_u << "Kids" << reset << std::endl;
  for(int i : kids) {
    std::cout << " - " << i << "\n";
  }

  std::cout << green_u << "Income" << reset << std::endl;
  for(int i : income) {
    std::cout << " - " << i << "\n";
  }

  std::cout << green_u << "School" << reset << std::endl;
  for(auto i : school) {
    std::cout << " - " << i << "\n";
  }
  
  std::cout << green_u << "Hobby" << reset << std::endl;
  for(auto i : hobby) {
    std::cout << " - " << i << "\n";
  }

  std::cout << green_u << "Weight" << reset << std::endl;
  for(int i : weight) {
    std::cout << " - " << i << "\n";
  }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                               Mash::checkInt                              *
 * Input  : List number and Integer reference variable                       *
 * Output : None                                                             *
 * Purpose: This helper function checks if a user has entered an Integer     *
 *          value. If not, then a loop makes sure of that. Once the user has *
 *          entered an Integer value, the value is saved to the reference    *
 *          variable.                                                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void Mash::checkInt(int listNum, int &refVar) {
  while(std::cin.fail()) {
    std::cout << "Error! Please enter 'Integer' values only!" << std::endl;
    std::cout << listNum << ") ";
    std::cin.clear();
    std::cin.ignore(256,'\n');
    std::cin >> refVar;
  }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                            Mash::finishedMash                             *
 * Input  : None                                                             *
 * Output : bool value                                                       *
 * Purpose: This helper function checks the size of each category vector     *
 *          and returns true if each vector has only one element.            *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

bool Mash::finishedMash() {
  bool status = false;
  if(marrying.size() == 1 && living_quarters.size() == 1 &&
     car.size() == 1 && pet.size() == 1 &&
     occupation.size() == 1 && kids.size() == 1 &&
     income.size() == 1 && school.size() == 1 &&
     hobby.size() == 1 && weight.size() == 1)
    status = true;

  return status;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                       Mash::determineBuilding                             *
 * Input  : counter and reference variable to building                       *
 * Output : None                                                             *
 * Purpose: This function uses the counter variable to determine the         *
 *          final building variable value. This uses the same logic as the   *
 *          beginMash function but only using the building vector and the    *
 *          user count variable. This function was created because           *
 *          in my siblings version of this game, they leave the building     *
 *          category alone until after the other final elements in each      *
 *          category are defined. Then they proceed to use the count         *
 *          variable and the building vector to determine the final          *
 *          building.                                                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void Mash::determineBuilding(int count, std::string &refBuilding) {
  const std::string green_u("\033[4;32m");
  const std::string reset("\033[0m");
  int pos = 0;

  while(building.size() > 1) {
    // If size of vector is 1, move on
    if(building.size() == 1) {
      // Do nothing
    }
    // If the size of vector is less than counter, subtract size from counter
    else if(pos + building.size() < count) {
      pos += building.size();
    }
    // Size of vector is greater than or equal to counter
    else {
      for(std::vector<std::string>::iterator it = building.begin(); it != building.end();) {
        pos++;
        if((pos % count) == 0) {
          ClearScreen();
          std::cout << "* * * Deleting " << *it << " * * * " << std::endl;
          it = building.erase(it);
          std::cout << green_u << "Building" << reset << std::endl;
          for(auto i : building) {
            std::cout << " - " << i << "\n";
          }
          sleep_until(system_clock::now() + seconds(1));
          if(it == building.end()) {
            pos = 0;
            //break;
          }
          else {
            // Do nothing
          }
        }
        else
          ++it;
      }
    }

  }
  refBuilding = building.front();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                      Mash::crossOffCheckString                            *
 * Input  : integer for position and count and reference to vector           *
 * Output : None                                                             *
 * Purpose: This helper function uses 2 reference variables and a count      * 
 *          (determined by user) to update a position value that increments  *
 *          every time we go through each element of each vector. If the     *
 *          size of the vector is one, then this vector is done and we move  *
 *          on. If the position plus the size of the vector is less than the *
 *          count, we can just add the size of the vector to position value  *
 *          and move on to the next vector. Once the position value is a     *
 *          multiple of the count variable, we erase the current element     *
 *          from the vector, display the new updated list, and move on.      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void Mash::crossOffCheckString(int &refPos, std::vector<std::string> &refVector, int count) {
    // If size of vector is 1, move on
    if(refVector.size() == 1) {
      // Do nothing
    }
    // If the size of vector is less than counter, subtract size from counter
    else if(refPos + refVector.size() < count) {
      refPos += refVector.size();
    }
    // If pos + size of vector is greater than or equal to counter
    else {
      for(std::vector<std::string>::iterator it = refVector.begin(); it != refVector.end();) {
        refPos++;
        // The position value is a multiple of count means we are at the element
        // that should be deleted
        if((refPos % count) == 0) {
          // Erase element and print updated list
          ClearScreen();
          std::cout << "* * * Deleting " << *it << " * * * " << std::endl;
          it = refVector.erase(it);
          printData();
          sleep_until(system_clock::now() + seconds(1));

          if(it == refVector.end()) {
            refPos = 0;
          }
          else {
            // Do nothing
          }
        }
        else 
          ++it;
      }
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                         Mash::crossOffCheckInt                            *
 * Input  : integer for position and count and reference to vector           *
 * Output : None                                                             *
 * Purpose: This function is the same as the crossOffCheckString except that *
 *          the input vector should be of type Integer instead of string.    *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void Mash::crossOffCheckInt(int &refPos, std::vector<int> &refVector, int count) {
    // If size of vector is 1, move on
    if(refVector.size() == 1) {
      // Do nothing
    }
    // If the size of vector is less than counter, subtract size from counter
    else if(refPos + refVector.size() < count) {
      refPos += refVector.size();
    }
    // If pos + size of vector is greater than or equal to counter
    else {
      for(std::vector<int>::iterator it = refVector.begin(); it != refVector.end();) {
        refPos++;
        // The position value is a multiple of count means we are at the element
        // that should be deleted
        if((refPos % count) == 0) {
          // Erase element and print updated list.
          ClearScreen();
          std::cout << "* * * Deleting " << *it << " * * * " << std::endl;
          it = refVector.erase(it);
          printData();
          sleep_until(system_clock::now() + seconds(1));
          if(it == refVector.end()) {
            refPos = 0;
          }
          else {
            // Do nothing
          }
        }
        else 
          ++it;
      }
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                             Mash::ClearScreen                             *
 * Input  : None                                                             *
 * Output : None                                                             *
 * Purpose: This function "clears" the screen by printing a bunch of         *
 *          newlines. There are better ways to clear the screen, but this is *
 *          the easiest way to do it for now.                                *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void Mash::ClearScreen() {
  std::cout << std::string(50,'\n');
}
