/* Author  : Joseph Leovao
 * Date    : November 24, 2017
 * Filename: Mash.h
 * Purpose : This is the class specification file declares
 *           the functions and variables necessary to build my 
 *           own implementation of the game MASH. 
 */

#ifndef MASH_H
#define MASH_H
#include <string>
#include <vector>

class Mash {
  private:
    bool generateInput;
    int counterValue;

  public:
    // For simplicity purposes, switched from arrays to vectors
    // Can use linked-list in the future...
    std::vector<std::string> marrying;
    std::vector<std::string> living_quarters;
    std::vector<std::string> car;
    std::vector<std::string> pet;
    std::vector<std::string> occupation;
    std::vector<int> kids;
    std::vector<int> income;
    std::vector<std::string> school;
    std::vector<std::string> hobby;
    std::vector<std::string> building;
    std::vector<int> weight;

    // These variables will hold the final values that will
    // be passed into the generateStory function.
    std::string final_marrying;
    std::string final_living_quarters;
    std::string final_car;
    std::string final_pet;
    std::string final_occupation;
    int final_kids;
    int final_income;
    std::string final_school;
    std::string final_hobby;
    int final_weight;
    std::string final_building;

    // Defined in Mash.cpp
    Mash(bool, int);
    void ClearScreen();
    void parseFile(std::string filename);
    void manualInput();
    void beginMash(int, std::string&, std::string&, std::string&, std::string&,
                        std::string&, int&, int&, std::string&, std::string&,
                        int&);
    void crossOffCheckString(int&, std::vector<std::string>&, int);
    void crossOffCheckInt(int&, std::vector<int>&, int);
    bool finishedMash();
    void determineBuilding(int,std::string&);
    void generateStory(std::string, std::string, std::string, std::string, 
                       std::string, int k, int i, std::string s, std::string h,
                       int w, std::string building);
    void printData();
    void checkInt(int, int&);

    // Setters and Getters
    void setGenerateInput(bool gi) {
      generateInput = gi;
    }
    bool getGenerateInput() {
      return generateInput;
    }
    void setCounterValue(int cv) {
      counterValue = cv;
    }
    int getCounterValue() {
      return counterValue;
    }
};
#endif
