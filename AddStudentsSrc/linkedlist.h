#pragma once
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

struct Node {
    int studentID;
    Node* next;
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList();

    void addStudent(int id);
    void displayStudents();
    bool searchStudent(int id);
};

#endif

