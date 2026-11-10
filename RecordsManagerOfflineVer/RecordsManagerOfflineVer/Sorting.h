#pragma once

#include "Common.h"

// ==========================================
// PART 3: CONVERT LINKED LIST TO ARRAY
// ==========================================
Student* createArray(int& count) {
	count = countStudents(head);

	if (count == 0) {
		return nullptr;
	}

	Student* arr = new Student[count];

	Node* current = head;

	for (int i = 0; i < count; i++) {
		arr[i] = current->data;
		current = current->next;
	}

	return arr;
}

// ==========================================
// SORTING COMPARISON FUNCTION
// ==========================================
bool compareStudents(Student a, Student b, int criteria) {
	if (criteria == 1) {
		return a.id > b.id;
	}

	if (criteria == 2) {
		return a.lastName > b.lastName;
	}

	return a.gpa > b.gpa;
}

// ==========================================
// PART 3: BUBBLE SORT
// ==========================================
void bubbleSort(Student arr[], int n, int criteria) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {

			if (compareStudents(arr[j], arr[j + 1], criteria)) {
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}

// ==========================================
// PART 3: SELECTION SORT
// ==========================================
void selectionSort(Student arr[], int n, int criteria) {
	for (int i = 0; i < n - 1; i++) {
		int minIndex = i;

		for (int j = i + 1; j < n; j++) {
			if (compareStudents(arr[minIndex], arr[j], criteria)) {
				minIndex = j;
			}
		}

		if (minIndex != i) {
			swap(arr[i], arr[minIndex]);
		}
	}
}

// ==========================================
// PART 3: MERGE SORT
// ==========================================
void mergeSortRecursive(Student arr[], Student temp[], int left, int right, int criteria) {
	if (left >= right) {
		return;
	}

	int middle = left + (right - left) / 2;

	mergeSortRecursive(arr, temp, left, middle, criteria);
	mergeSortRecursive(arr, temp, middle + 1, right, criteria);

	int leftIndex = left;
	int rightIndex = middle + 1;
	int tempIndex = left;

	while (leftIndex <= middle && rightIndex <= right) {
		if (!compareStudents(arr[leftIndex], arr[rightIndex], criteria)) {
			temp[tempIndex++] = arr[leftIndex++];
		}
		else {
			temp[tempIndex++] = arr[rightIndex++];
		}
	}

	while (leftIndex <= middle) {
		temp[tempIndex++] = arr[leftIndex++];
	}

	while (rightIndex <= right) {
		temp[tempIndex++] = arr[rightIndex++];
	}

	for (int i = left; i <= right; i++) {
		arr[i] = temp[i];
	}
}

void mergeSort(Student arr[], int n, int criteria) {
	Student* temp = new Student[n];
	mergeSortRecursive(arr, temp, 0, n - 1, criteria);
	delete[] temp;
}

// ==========================================
// DISPLAY SORTED ARRAY
// ==========================================
void displayArray(Student arr[], int n) {
	displayHeader();

	for (int i = 0; i < n; i++) {
		displayStudent(arr[i]);
	}
}

// ==========================================
// PART 3: SORT STUDENTS
// ==========================================
void sortStudents() {
	cout << "\n========== SORT STUDENTS ==========\n";

	int count;
	Student* arr = createArray(count);

	if (arr == nullptr) {
		cout << "No student records available.\n";
		return;
	}

	cout << "\nSort By:\n";
	cout << "1. Student ID\n";
	cout << "2. Last Name\n";
	cout << "3. GPA\n";

	int criteria = getInt("Enter choice: ");

	if (criteria < 1 || criteria > 3) {
		cout << "Invalid choice!\n";
		delete[] arr;
		return;
	}

	cout << "\nSorting Algorithm:\n";
	cout << "1. Bubble Sort\n";
	cout << "2. Selection Sort\n";
	cout << "3. Merge Sort\n";

	int algorithm = getInt("Enter choice: ");

	if (algorithm == 1) {
		bubbleSort(arr, count, criteria);
		cout << "\nSorted using Bubble Sort.\n";
	}
	else if (algorithm == 2) {
		selectionSort(arr, count, criteria);
		cout << "\nSorted using Selection Sort.\n";
	}
	else if (algorithm == 3) {
		mergeSort(arr, count, criteria);
		cout << "\nSorted using Merge Sort.\n";
	}
	else {
		cout << "Invalid choice!\n";
		delete[] arr;
		return;
	}

	displayArray(arr, count);

	delete[] arr;
}
