#pragma once

#include "Common.h"

// ==========================================
// STACK: PUSH RECENTLY DELETED STUDENT
// ==========================================
void pushStack(Student s) {
	StackNode* newNode = new StackNode(s);

	newNode->next = stackTop;
	stackTop = newNode;
}

// ==========================================
// STACK: POP
// ==========================================
void popStack() {
	if (stackTop == nullptr) {
		cout << "Stack is empty!\n";
		return;
	}

	StackNode* temp = stackTop;

	cout << "\nRecently deleted student removed from stack:\n";
	displayHeader();
	displayStudent(temp->data);

	stackTop = stackTop->next;

	delete temp;
}

// ==========================================
// STACK: DISPLAY
// ==========================================
void displayStack() {
	cout << "\n========== RECENTLY DELETED STUDENTS ==========\n";

	if (stackTop == nullptr) {
		cout << "No recently deleted students.\n";
		return;
	}

	cout << "TOP OF STACK\n";

	displayHeader();

	StackNode* current = stackTop;

	while (current != nullptr) {
		displayStudent(current->data);
		current = current->next;
	}

	cout << "\nBOTTOM OF STACK\n";
}

// ==========================================
// STACK OPERATIONS MENU
// ==========================================
void stackOperations() {
	int choice;

	do {
		cout << "\n========== STACK OPERATIONS ==========\n";
		cout << "1. Display Recently Deleted Students\n";
		cout << "2. Pop (Remove Top Student)\n";
		cout << "3. Return to Main Menu\n";

		choice = getInt("Enter choice: ");

		switch (choice) {
		case 1:
			displayStack();
			break;

		case 2:
			popStack();
			break;

		case 3:
			cout << "Returning to main menu...\n";
			break;

		default:
			cout << "Invalid choice!\n";
		}

	} while (choice != 3);
}
