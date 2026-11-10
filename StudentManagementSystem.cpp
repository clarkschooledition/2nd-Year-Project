
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
    } else {
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
         [](Student a, Student b) {
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
        } else {
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
    } else {
        previous->next = current->next;
    }

    delete current;

    cout << "\nStudent deleted successfully!\n";
    cout << "Record saved in Recently Deleted Stack.\n";
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

    int algorithm = getInt("Enter choice: ");

    if (algorithm == 1) {
        bubbleSort(arr, count, criteria);
        cout << "\nSorted using Bubble Sort.\n";
    } else if (algorithm == 2) {
        selectionSort(arr, count, criteria);
        cout << "\nSorted using Selection Sort.\n";
    } else {
        cout << "Invalid choice!\n";
        delete[] arr;
        return;
    }

    displayArray(arr, count);

    delete[] arr;
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
    } else {
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
