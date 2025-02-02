#ifndef HEADER_H
#define HEADER_H


#include <iostream>
#include <string>
#include <forward_list>
#include <iterator>
#include <fstream>


using namespace std;

class Data
{
    public:
    string key;
    string value;
    int points;

    Data(string command, string description, int points) : key(command), value(description), points(points) {}



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

    int menuChoice;
    string returntoMenu;
};


#endif