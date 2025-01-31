#ifndef HEADER_H
#define HEADER_H


#include <iostream>
#include <string>
#include <forward_list>
#include <iterator>
#include <fstream>


using namespace std;


class Game
{
    public:

    Game();
    
    void run();

    

   
    private:

    void mainMenu();
    void getChoice();

    void displayRules();

    void displayCommands();

    int menuChoice;
    string returntoMenu;
};


#endif