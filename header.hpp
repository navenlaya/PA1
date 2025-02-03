#ifndef HEADER_H
#define HEADER_H


#include <iostream>
#include <string>
#include <forward_list>
#include <iterator>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>
#include <unordered_set>

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

class Player {
public:
    string name;
    int points;
    
    Player() : name(""), points(0) {} 
    Player(const string &name, int points) : name(name), points(points) {} 
    
    void displayProfile() {
        cout << "Name: " << name << ", Points: " << points << endl;
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
    List() : head(nullptr), size(0) {}  
    ~List() {}

    void insertAtFront(T value)
    {
        Node<T>* newNode = new Node<T>(value);
        if (!head) {
            head = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        size++;  
    }

    bool deleteAtPosition(const string& key) {
        Node<T>* current = head;
        Node<T>* prev = nullptr;

        while (current != nullptr) {
            if (current->data.key == key) {
                if (prev == nullptr) { 
                    head = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                size--;  
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false;
    }

    void print() const
    {
        Node<T>* temp = head;
        while (temp) {
            cout << temp->data << endl;
            temp = temp->next;
        }
    }

    Node<T>* getHead() const
    {
        return head;
    }

    int getSize() const {
        return size;
    }

private:
    Node<T>* head;
    int size;  
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
    void playGame();
    void loadPreviousGame();
    void addCommands();
    void removeCommands();
    void displayCommands();



    void loadCommands();
    void loadProfiles();
    void saveProfiles();
    void askQuestion(int n);

    int menuChoice;
    string returntoMenu;
    List<Data> commandList;
    Player playerProfiles[100]; 
    int profileCount;
};


#endif