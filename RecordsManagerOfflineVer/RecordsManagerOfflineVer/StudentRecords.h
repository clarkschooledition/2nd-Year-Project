#pragma once

#include "Common.h"
#include "StackOperations.h"

// ==========================================
// PART 1: ADD STUDENT
// ==========================================
void addStudent() {
	Student s;

	cout << "\n========== ADD STUDENT ==========\n";

	s.id = getInt("Enter Student ID: ");

	if (findStudent(s.id) != nullptr) {
		cout << "Student ID already exists!\n";
		return;
	}

	s.firstName = getString("Enter First Name: ");
	s.lastName = getString("Enter Last Name: ");
	s.age = getInt("Enter Age: ");
	s.course = getString("Enter Course: ");
	s.gpa = getDouble("Enter GPA (0-5): ");

	Node* newNode = new Node(s);

	if (head == nullptr) {
		head = newNode;
	}
	else {
		Node* current = head;

		while (current->next != nullptr) {
			current = current->next;
		}

		current->next = newNode;
	}

	cout << "\nStudent added successfully!\n";
}

// ==========================================
// PART 1: DISPLAY ALL STUDENTS
// ==========================================
void displayStudents() {
	cout << "\n========== STUDENT RECORDS ==========\n";

	if (head == nullptr) {
		cout << "No student records found.\n";
		return;
	}

	displayHeader();

	Node* current = head;

	while (current != nullptr) {
		displayStudent(current->data);
		current = current->next;
	}
}

// ==========================================
// PART 2: LINEAR SEARCH
// ==========================================
void linearSearch(int id) {
	Node* current = head;

	while (current != nullptr) {
		if (current->data.id == id) {
			cout << "\nStudent found using Linear Search!\n";
			displayHeader();
			displayStudent(current->data);
			return;
		}

		current = current->next;
	}

	cout << "\nStudent not found!\n";
}

// ==========================================
// PART 2: BINARY SEARCH
// ==========================================
void binarySearch(int id) {
	if (head == nullptr) {
		cout << "No student records available.\n";
		return;
	}

	// Copy linked list into a dynamic array.
	int count = 0;

	for (Node* current = head; current != nullptr;
		current = current->next) {
		count++;
	}

	Student* arr = new Student[count];

	Node* current = head;

	for (int i = 0; i < count; i++) {
		arr[i] = current->data;
		current = current->next;
	}

	// Sort array by Student ID.
	sort(arr, arr + count,
		[] (Student a, Student b) {
			return a.id < b.id;
		});

	// Binary Search.
	int low = 0;
	int high = count - 1;

	while (low <= high) {
		int mid = low + (high - low) / 2;

		if (arr[mid].id == id) {
			cout << "\nStudent found using Binary Search!\n";
			displayHeader();
			displayStudent(arr[mid]);

			delete[] arr;
			return;
		}

		if (arr[mid].id < id) {
			low = mid + 1;
		}
		else {
			high = mid - 1;
		}
	}

	cout << "\nStudent not found!\n";

	delete[] arr;
}

// ==========================================
// PART 1: SEARCH STUDENT
// ==========================================
void searchStudent() {
	cout << "\n========== SEARCH STUDENT ==========\n";

	if (head == nullptr) {
		cout << "No student records available.\n";
		return;
	}

	int id = getInt("Enter Student ID: ");

	cout << "\n1. Linear Search\n";
	cout << "2. Binary Search\n";

	int choice = getInt("Choose Search Algorithm: ");

	switch (choice) {
	case 1:
		linearSearch(id);
		break;

	case 2:
		binarySearch(id);
		break;

	default:
		cout << "Invalid choice!\n";
	}
}

// ==========================================
// PART 1: UPDATE STUDENT
// ==========================================
void updateStudent() {
	cout << "\n========== UPDATE STUDENT ==========\n";

	int id = getInt("Enter Student ID to update: ");

	Node* current = findStudent(id);

	if (current == nullptr) {
		cout << "Student not found!\n";
		return;
	}

	cout << "\nCurrent Student Information:\n";
	displayHeader();
	displayStudent(current->data);

	cout << "\nEnter New Information:\n";

	current->data.firstName =
		getString("Enter First Name: ");

	current->data.lastName =
		getString("Enter Last Name: ");

	current->data.age =
		getInt("Enter Age: ");

	current->data.course =
		getString("Enter Course: ");

	current->data.gpa =
		getDouble("Enter GPA (0-5): ");

	cout << "\nStudent updated successfully!\n";
}

// ==========================================
// PART 1: DELETE STUDENT
// ==========================================
void deleteStudent() {
	cout << "\n========== DELETE STUDENT ==========\n";

	int id = getInt("Enter Student ID to delete: ");

	Node* current = head;
	Node* previous = nullptr;

	while (current != nullptr && current->data.id != id) {
		previous = current;
		current = current->next;
	}

	if (current == nullptr) {
		cout << "Student not found!\n";
		return;
	}

	// Save deleted student in stack.
	pushStack(current->data);

	if (previous == nullptr) {
		head = current->next;
	}
	else {
		previous->next = current->next;
	}

	delete current;

	cout << "\nStudent deleted successfully!\n";
	cout << "Record saved in Recently Deleted Stack.\n";
}
