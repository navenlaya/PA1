#include "header.hpp"

Game::Game(){}

Game::~Game() {}



void Game::run()
{
    returntoMenu = "Y";
    while(returntoMenu == "Y")
    {
        mainMenu();
        getChoice();

        switch(menuChoice)
        {
            case 1:
            displayRules();
            break;
            case 2:
            //Play Game
            break;
            case 3:
            //Load Previous Game
            break;
            case 4:
            // Add Commands
            addCommands();
            break;
            case 5:
            //Remove Commands
            break;
            case 6:
            // Display All Commands
            displayCommands();
            break;
            case 7:
            cout << "Exiting..." << endl;
            return;
            
            default:
            cout << "Invalid Choice. Try Again" << endl;
        }

        cout << "Return to the Main Menu? Y/N:" << endl;
        cin >> returntoMenu;

    }

}

void Game::mainMenu()
{
    cout << "---- MAIN MENU ----" << endl;
    cout <<"1. RULES" << endl;
    cout <<"2. PLAY NEW GAME" << endl;
    cout <<"3. LOAD PREVIOUS GAME" << endl;
    cout <<"4. ADD COMMANDS" << endl;
    cout <<"5. REMOVE COMMANDS" << endl;
    cout <<"6. DISPLAY ALL COMMANDS" << endl;
    cout <<"7. EXIT" << endl;
}

void Game::getChoice()
{
    cout<< "Enter Choice:" << endl;
    cin >> menuChoice;
    
}

void Game::displayRules()
{
    cout << "---- RULES ----" << endl;
    
}

void Game::addCommands()
{
    string key;
    string value;
    int points;

    cout << "Enter new command name:";
    cin >> key;
    cin.ignore();

    cout << "Enter description:";
    cin >> value;

    cout << "Enter points:";
    cin >> points;

    ofstream outputFile("commands.csv", ios::app);

    if (outputFile.is_open()) 
    {
        outputFile << key << ",\"" << value << "\"," << points << endl;
        outputFile.close();
        cout << "Command added." << endl;
    } 
    else 
    {
        cout << "Error" << endl;
    }

    
}

void Game::displayCommands()
{
    ifstream inputFile("commands.csv");

    cout << "Commands, Description, Points" << endl;

    string line;
    while(getline(inputFile, line))
    {
        cout<<line<<endl;
    }
    
    inputFile.close();

}

