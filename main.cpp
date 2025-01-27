#include <iostream>
#include <string>
#include <forward_list>
#include <iterator>

using namespace std;

class Data 
{
    public:
        string key;
        string value;

        Data(string command, string description ): key(command), value(description)
        {}

};

void displayOptions(string correctAnswer, forward_list<Data> &commandList, forward_list<Data>::iterator current)
{
    string distractor1, distractor2;
    auto it = next(current);

    distractor1 = it ->value;
    it = next(it);
    distractor2 = it ->value;

    cout<< "1." <<distractor1<< endl;
    cout<< "2." << distractor2 << endl;
}

int main()
{   
    forward_list<Data> commandList = 
    {
        Data("ls", "list directory"),
        Data("cd", "change directory"),
        Data("rmdir", "remove directory")
    
    };

    auto it = commandList.begin();
    string userInput;
    
    while(it != commandList.end())
    {
        string command = it->key;
        string correctAnswer = it->value;

        cout<<"What does the command " << command << " do ?" << endl;
        displayOptions(correctAnswer, commandList, it);
        
        cout<< "enter choice: " << endl;
        cin >> userInput;

        if(userInput == "quit")
        {
            cout << "done" << endl;
            return 0;
        }

        int choice = stoi(userInput);

        if(choice == 1)
        {
            cout<< "correct" << endl;
            it = next(it);
        }
        else
        {
            cout<< "incorrect" << endl;
        }
    }

    return 0;
}