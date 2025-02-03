#ifndef HEADER_H
#define HEADER_H


#include <iostream>
#include <string>
#include <forward_list>
#include <iterator>
#include <fstream>
#include <sstream>

using namespace std;

class Data
{
    public:
    string key;
    string value;
    int points;

    Data(string command, string description, int points) : key(command), value(description), points(points) {}


   
    friend ostream& operator<<(ostream& os, const Data& data) {
        os << data.key << ", " << data.value<< ", " << data.points;
        return os;
    }


};

template <typename T>
class Node
{

    public:

    T data;
    Node* next;

    Node(T val) : data(val), next(nullptr) {}
};

template <typename T>
class List
{
    public:

    List() : head(nullptr) {}
    ~List() {}

    void insertAtFront(T value)
    {
        Node<T>* newNode = new Node<T>(value);
        if(!head)
        {
            head = newNode;
            return;
        }

        newNode->next = head;
        head = newNode;
    }

    void print() const
    {
        Node<T>* temp = head;
        while(temp)
        {
            cout<< temp->data << endl;
            temp = temp -> next;
        }
    }

    private:
    Node<T>* head;
   
};


class Game
{
    public:

    Game();
    ~Game();
    
    void run();

    

   
    private:

    void mainMenu();
    void getChoice();

    void displayRules();

    void displayCommands();

    void addCommands();

    void loadCommands();

    int menuChoice;
    string returntoMenu;
    List<Data> commandList;
};


#endif