#pragma once

#include "Common.h"

// ==========================================
// QUEUE: ENQUEUE STUDENT
// ==========================================
void enqueueStudent() {
	int id = getInt("Enter Student ID to add to queue: ");

	Node* student = findStudent(id);

	if (student == nullptr) {
		cout << "Student not found!\n";
		return;
	}

	QueueNode* newNode = new QueueNode(student->data);

	if (rearNode == nullptr) {
		frontNode = rearNode = newNode;
	}
	else {
		rearNode->next = newNode;
		rearNode = newNode;
	}

	cout << "Student added to processing queue!\n";
}

// ==========================================
// QUEUE: DEQUEUE STUDENT
// ==========================================
void dequeueStudent() {
	if (frontNode == nullptr) {
		cout << "Queue is empty!\n";
		return;
	}

	QueueNode* temp = frontNode;

	cout << "\nProcessing student:\n";
	displayHeader();
	displayStudent(temp->data);

	frontNode = frontNode->next;

	if (frontNode == nullptr) {
		rearNode = nullptr;
	}

	delete temp;

	cout << "\nStudent removed from queue.\n";
}

// ==========================================
// QUEUE: DISPLAY
// ==========================================
void displayQueue() {
	cout << "\n========== STUDENT PROCESSING QUEUE ==========\n";

	if (frontNode == nullptr) {
		cout << "Queue is empty!\n";
		return;
	}

	displayHeader();

	QueueNode* current = frontNode;

	while (current != nullptr) {
		displayStudent(current->data);
		current = current->next;
	}

	cout << "\nFRONT -> REAR\n";
}

// ==========================================
// QUEUE OPERATIONS MENU
// ==========================================
void queueOperations() {
	int choice;

	do {
		cout << "\n========== QUEUE OPERATIONS ==========\n";
		cout << "1. Enqueue Student\n";
		cout << "2. Dequeue Student\n";
		cout << "3. Display Queue\n";
		cout << "4. Return to Main Menu\n";

		choice = getInt("Enter choice: ");

		switch (choice) {
		case 1:
			enqueueStudent();
			break;

		case 2:
			dequeueStudent();
			break;

		case 3:
			displayQueue();
			break;

		case 4:
			cout << "Returning to main menu...\n";
			break;

		default:
			cout << "Invalid choice!\n";
		}

	} while (choice != 4);
}
