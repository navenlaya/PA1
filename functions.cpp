#include "header.hpp"

Game::Game(){}


Game::~Game() {}



void Game::run()
{
    loadProfiles();
    loadCommands();
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
            //play Game
            playGame();
            break;
            case 3:
            //load Previous Game
            loadPreviousGame();
            break;
            case 4:
            //add Commands
            addCommands();
            break;
            case 5:
            //remove Commands
            removeCommands();
            break;
            case 6:
            //display All Commands
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

void Game::loadCommands()
{
    ifstream inputFile("commands.csv");

    if (inputFile.is_open())
    {
        string line;
        while (getline(inputFile, line))
        {
            stringstream ss(line);
            string key, value, points_str;
            int points;

            getline(ss, key, ',');
            getline(ss, value, ',');
            getline(ss, points_str);

            points = stoi(points_str);  

            Data newCommand(key, value, points);
            commandList.insertAtFront(newCommand); 
        }

        inputFile.close();
    }
    else
    {
        cout << "Error opening file for loading commands." << endl;
    }
}

void Game::loadProfiles()
{
    ifstream inputFile("profiles.csv");

    if (!inputFile.is_open())
    {
        cout << "Error opening profiles.csv!" << endl;
        return;
    }

    profileCount = 0;
    string line;
    while (getline(inputFile, line) && profileCount < 100)
    {
        stringstream ss(line);
        string name, points_str;
        int points;

        getline(ss, name, ',');
        getline(ss, points_str);

        try
        {
            points = stoi(points_str);
        }
        catch (invalid_argument &e)
        {
            cout << "Error reading profile data for: " << name << endl;
            continue;
        }

        playerProfiles[profileCount] = Player(name, points);
        profileCount++;
    }

    inputFile.close();
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
    cout << "---- Game Rules ----" << endl;
    cout << "1. Goal: Answer questions correctly to earn points." << endl;
    cout << "2. How to Play:" << endl;
    cout << "   - Choose the correct answer (1, 2, or 3) for each question." << endl;
    cout << "   - Each correct answer earns points." << endl;
    cout << "--------------------" << endl;
}

void Game::playGame()
{
    string playerName;

    if (profileCount >= 100) {
        cout << "Max number of profiles reached!" << endl;
        return;
    }

    cout << "Enter player name: ";
    cin >> playerName;

    int playerIndex = -1;
    for (int i = 0; i < profileCount; i++) {
        if (playerProfiles[i].name == playerName) {
            playerIndex = i;
            break;
        }
    }

    if (playerIndex == -1) {
        playerProfiles[profileCount] = Player(playerName, 0);
        playerIndex = profileCount;
        profileCount++;

        ofstream outputFile("profiles.csv", ios::app);
        if (outputFile.is_open()) {
            outputFile << playerName << ",0" << endl;
            outputFile.close();
            cout << "Profile created!" << endl;
        } else {
            cout << "Error creating profile." << endl;
            return;
        }
    }

    //ask user how many questions they want.
    int numQuestions;
    cout << "How many questions?";
    cin >> numQuestions;

    // Start the game
    for (int i = 0; i < numQuestions; i++) {
        askQuestion(playerIndex);
    }

    //save updated profile
    saveProfiles();
}

void Game::askQuestion(int questionNum) {
    srand(time(0)); 
    int randIndex = rand() % commandList.getSize();  
    Node<Data>* current = commandList.getHead();

    //goes to the random command
    for (int i = 0; i < randIndex; i++) {
        current = current->next;
    }

    Data selectedCommand = current->data;
    string correctAnswer = selectedCommand.value;
    
    string answers[4];  

    //shuffles the correct answer
    int correctAnswerIndex = rand() % 3 + 1;  //between 1 and 3
    answers[correctAnswerIndex] = correctAnswer;

    unordered_set<string> selectedIncorrectAnswers;
    selectedIncorrectAnswers.insert(correctAnswer);  

    //make the other 2 questions incorrect
    Node<Data>* temp = commandList.getHead();
    int incorrectIndex = 1;

    while (incorrectIndex < 3) {
        string randomAnswer;
        while (true) {
            //randomly choose
            randomAnswer = temp->data.value;
            temp = temp->next;

            //skip so no duplicates
            if (randomAnswer != correctAnswer && selectedIncorrectAnswers.find(randomAnswer) == selectedIncorrectAnswers.end()) {
                selectedIncorrectAnswers.insert(randomAnswer);  
                break;  
            }
        }

        //assign answers
        if (answers[1] == "") {
            answers[1] = randomAnswer;
        } else if (answers[2] == "") {
            answers[2] = randomAnswer;
        } else {
            answers[3] = randomAnswer;
        }
        incorrectIndex++;
    }

    //shuffle
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(answers + 1, answers + 4, g);  

    //display
    cout << "Question: " << selectedCommand.key << endl;
    for (int i = 1; i <= 3; i++) {
        cout << i << ". " << answers[i] << endl;
    }


    int choice;
    cout << "Enter your choice: ";
    while (true) {
        cin >> choice;

        if (choice < 1 || choice > 3) {
            cout << "Invalid choice.";
        } else {
            break;  
        }
    }

    //check if answer is correct
    if (answers[choice] == correctAnswer) {
        cout << "Correct. + " << selectedCommand.points << " points." << endl;
        playerProfiles[0].points += selectedCommand.points;
    } else {
        cout << "Wrong. The correct answer was: " << correctAnswer << endl;
    }

    cout << "Player: " << playerProfiles[0].name << " | Points: " << playerProfiles[0].points << endl;
}

void Game::saveProfiles()
{
    ofstream outputFile("profiles.csv");
    if (outputFile.is_open()) {
        for (int i = 0; i < profileCount; i++) {
            outputFile << playerProfiles[i].name << "," << playerProfiles[i].points << endl;
        }
        outputFile.close();
        cout << "Updated" << endl;
    } else {
        cout << "Error." << endl;
    }
}


void Game::loadPreviousGame()
{
    ifstream inputFile("profiles.csv");
    if (!inputFile.is_open())
    {
        cout << "Erro" << endl;
        return;
    }

    profileCount = 0;
    string line;
    while (getline(inputFile, line) && profileCount < 100)
    {
        stringstream ss(line);
        string name;
        int points = 0;

        getline(ss, name, ',');
        string points_str;
        getline(ss, points_str);

        if (!points_str.empty())
        {
            try
            {
                points = stoi(points_str);
            }
            catch (const invalid_argument &e)
            {
                cout << "Invalid" << endl;
                continue;  
            }
        }

        playerProfiles[profileCount] = Player(name, points);
        profileCount++;
    }

    inputFile.close();

    string playerName;
    cout << "Enter Name: ";
    cin >> playerName;

    // Search for the player
    for (int i = 0; i < profileCount; i++)
    {
        if (playerProfiles[i].name == playerName)
        {
            cout << "Player" << endl;
            playerProfiles[i].displayProfile();

            playGame();
            return;
        }
    }

    cout << "No player" << endl;

    
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

    Data newCommand(key, value, points);
    commandList.insertAtFront(newCommand);

    ofstream outputFile("commands.csv", ios::app);

    if (outputFile.is_open()) 
    {
        outputFile << key << ",\"" << value << "\"," << points << endl;
        outputFile.close();
        cout << "Command added." << endl;
    } 
    else 
    {
        cout << "Error opening file." << endl;
    }

    
}

void Game::removeCommands()
{
    string key;
    cout << "Enter command name: ";
    cin >> key;

    if (!commandList.deleteAtPosition(key))
    {
        cout << "No command found";
        return;
    }

    cout << "Command removed" << endl;

    
    ofstream outputFile("commands.csv");
    if (outputFile.is_open())
    {
        Node<Data>* current = commandList.getHead(); 

        while (current)
        {
            outputFile << current->data.key << ",\"" << current->data.value << "\"," << current->data.points << endl;
            current = current->next;
        }

        outputFile.close();
    }
    else
    {
        cout << "Error" << endl;
    }
}

void Game::displayCommands()
{

    commandList.print();

}

