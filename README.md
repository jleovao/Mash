# Mash

Mash is a 2-player paper and pencil game that kids used to play intended to predict one's future. 
As I was reviewing C++, my siblings were playing this game and I was inspired.This is my version
of this game and it is to be run on the terminal prompt.You can add your own text files with your 
input in the TextFiles folder. For now make sure that the input follows the categories in order 
with 4 items per category. 

This is just the basic implementation of the Mash game. In the future, I would like to scale the
program in a way that would allow a user to create and save their own files in a folder. I would
also like to make the program more flexible by not limiting the options per category to just 4.

To Compile  : g++ -std=c++11 main.cpp Mash.cpp -lpthread -o Mash
Run program : ./Mash
