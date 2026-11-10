
#include "Common.h"
#include "StudentRecords.h"
#include "Sorting.h"
#include "StackOperations.h"
#include "QueueOperations.h"
#include "StudentStatistics.h"

// ==========================================
// MAIN MENU
// ==========================================
int main() {
    int choice;

    do {
        cout << "\n";
        cout << "========================================\n";
        cout << "   STUDENT RECORD MANAGEMENT SYSTEM\n";
        cout << "========================================\n";

        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Sort Students\n";
        cout << "7. Stack Operations\n";
        cout << "8. Queue Operations\n";
        cout << "9. Student Statistics\n";
        cout << "10. Exit\n";

        cout << "========================================\n";

        choice = getInt("Enter your choice: ");

        switch (choice) {
        case 1:
            addStudent();
            break;

        case 2:
            displayStudents();
            break;

        case 3:
            searchStudent();
            break;

        case 4:
            updateStudent();
            break;

        case 5:
            deleteStudent();
            break;

        case 6:
            sortStudents();
            break;

        case 7:
            stackOperations();
            break;

        case 8:
            queueOperations();
            break;

        case 9:
            studentStatistics();
            break;

        case 10:
            cout << "\nThank you for using the system!\n";
            freeMemory();
            break;

        default:
            cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 10);

    return 0;
}
