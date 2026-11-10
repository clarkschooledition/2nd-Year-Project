#pragma once

#include "Common.h"

// ==========================================
// PART 4: STUDENT STATISTICS
// ==========================================

void studentStatistics() {
	cout << "\n========== STUDENT STATISTICS ==========\n";

	int total = countStudents(head);

	if (total == 0) {
		cout << "No student records available.\n";
		return;
	}

	double totalGPA = 0;
	double highestGPA = 5.0;
	double lowestGPA = 0.0;

	int highestCount = 0;
	int averageCount = 0;
	int lowestCount = 0;

	Node* current = head;

	while (current != nullptr) {
		double gpa = current->data.gpa;

		totalGPA += gpa;

		if (gpa == 1.00) {
			highestCount++;
		}
		else if (gpa > 1.00 && gpa <= 3.00) {
			averageCount++;
		}
		else if (gpa > 3.00) {
			lowestCount++;
		}

		if (gpa < highestGPA) {
			highestGPA = gpa;
		}

		if (gpa > lowestGPA) {
			lowestGPA = gpa;
		}

		current = current->next;
	}

	double average = totalGPA / total;

	cout << fixed << setprecision(2);

	cout << "\nTotal Students: " << total << endl;
	cout << "Average GPA: " << average << endl;

	cout << "\n========== GPA CLASSIFICATION ==========\n";

	cout << "Highest (1.00): " << highestCount << " student(s)\n";
	cout << "Average (1.01 - 3.00): " << averageCount << " student(s)\n";
	cout << "Lowest (Above 3.00): " << lowestCount << " student(s)\n";

	cout << "\nLowest Numerical GPA: " << highestGPA << endl;
	cout << "Highest Numerical GPA: " << lowestGPA << endl;

	cout << "\nStudent Count (Using Recursion): "
		<< countStudents(head) << endl;
}
