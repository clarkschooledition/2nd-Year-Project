#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <algorithm>
using namespace std;

// ==========================================
// STUDENT STRUCTURE
// ==========================================
struct Student {
	int id;
	string firstName;
	string lastName;
	int age;
	string course;
	double gpa;
};

// ==========================================
// LINKED LIST NODE
// ==========================================
struct Node {
	Student data;
	Node* next;

	Node(Student s) {
		data = s;
		next = nullptr;
	}
};

// ==========================================
// STACK NODE
// ==========================================
struct StackNode {
	Student data;
	StackNode* next;

	StackNode(Student s) {
		data = s;
		next = nullptr;
	}
};

// ==========================================
// QUEUE NODE
// ==========================================
struct QueueNode {
	Student data;
	QueueNode* next;

	QueueNode(Student s) {
		data = s;
		next = nullptr;
	}
};

// ==========================================
// GLOBAL DATA STRUCTURES
// ==========================================
Node* head = nullptr;

StackNode* stackTop = nullptr;

QueueNode* frontNode = nullptr;
QueueNode* rearNode = nullptr;

// ==========================================
// INPUT FUNCTIONS
// ==========================================
int getInt(string message) {
	int value;

	while (true) {
		cout << message;

		if (cin >> value) {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return value;
		}

		cout << "Invalid input! Enter a number.\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}

double getDouble(string message) {
	double value;

	while (true) {
		cout << message;

		if (cin >> value && value >= 0 && value <= 5) {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return value;
		}

		cout << "Invalid GPA! Enter a value from 0 to 5.\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}

string getString(string message) {
	string value;

	cout << message;
	getline(cin, value);

	return value;
}

// ==========================================
// DISPLAY STUDENT INFORMATION
// ==========================================
void displayStudent(Student s) {
	cout << left
		<< setw(10) << s.id
		<< setw(18) << s.firstName
		<< setw(18) << s.lastName
		<< setw(8) << s.age
		<< setw(15) << s.course
		<< fixed << setprecision(2)
		<< s.gpa << endl;
}

void displayHeader() {
	cout << "\n";
	cout << left
		<< setw(10) << "ID"
		<< setw(18) << "First Name"
		<< setw(18) << "Last Name"
		<< setw(8) << "Age"
		<< setw(15) << "Course"
		<< "GPA" << endl;

	cout << string(80, '-') << endl;
}

// ==========================================
// SEARCH LINKED LIST BY STUDENT ID
// ==========================================
Node* findStudent(int id) {
	Node* current = head;

	while (current != nullptr) {
		if (current->data.id == id) {
			return current;
		}

		current = current->next;
	}

	return nullptr;
}

// ==========================================
// PART 3: COUNT STUDENTS
// ==========================================
int countStudents(Node* current) {
	if (current == nullptr) {
		return 0;
	}

	return 1 + countStudents(current->next);
}

// ==========================================
// FREE MEMORY
// ==========================================
void freeMemory() {
	while (head != nullptr) {
		Node* temp = head;
		head = head->next;
		delete temp;
	}

	while (stackTop != nullptr) {
		StackNode* temp = stackTop;
		stackTop = stackTop->next;
		delete temp;
	}

	while (frontNode != nullptr) {
		QueueNode* temp = frontNode;
		frontNode = frontNode->next;
		delete temp;
	}

	rearNode = nullptr;
}
