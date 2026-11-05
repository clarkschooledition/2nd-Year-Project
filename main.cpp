#include <iostream>
#include <string>
#include <type_traits>
#include <algorithm>
#include <limits>
#include <stack>

// imports
using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::numeric_limits;
using std::stack;
using std::streamsize;
using std::string;

// Prototype
void AddStudents();
void SearchStudent();
void BinarySearchStudent();
void DeleteStudentMenu();
void DisplayRecentDeletions();
void StudentServiceMenu();
int checkInt(const string& prompt, int minVal, int maxVal);
float checkFloat(const string& question, float minVal, float maxVal);
string checkString(const string& question);
string checkUniqueID();
struct Student
{
    string firstName, middleInitials, surname, studentID, courseName;
    float GPA;
};
// ProtoType but needed student
void printStudent(const Student& s);
struct Node
{
    Student data;
    Node* prev;
    Node* next;
    Node(const Student& s) : data(s), prev(nullptr), next(nullptr) {}
};

class StudentServiceQueue
{
private:
    Node* front;
    Node* rear;

public:

    // Constructor
    StudentServiceQueue()
    {
        front = nullptr;
        rear = nullptr;
    }

    // Destructor
    ~StudentServiceQueue()
    {
        while (front != nullptr)
        {
            Node* temp = front;
            front = front->next;
            delete temp;
        }

        rear = nullptr;
    }

    // ENQUEUE
    void Enqueue(const Student& student)
    {
        Node* newNode = new Node(student);

        if (front == nullptr)
        {
            front = newNode;
            rear = newNode;
        }
        else
        {
            rear->next = newNode;
            newNode->prev = rear;
            rear = newNode;
        }

        cout << "\nStudent successfully added to service queue!\n";
    }

    // DEQUEUE
    void Dequeue()
    {
        if (front == nullptr)
        {
            cout << "\nService queue is empty.\n";
            return;
        }

        Node* temp = front;

        cout << "\n===== STUDENT SERVED =====\n";
        printStudent(temp->data);

        front = front->next;

        if (front == nullptr)
        {
            rear = nullptr;
        }
        else
        {
            front->prev = nullptr;
        }

        delete temp;

        cout << "Student successfully removed from queue.\n";
    }

    // PEEK 
    void Peek()
    {
        if (front == nullptr)
        {
            cout << "\nService queue is empty.\n";
            return;
        }

        cout << "\n===== NEXT STUDENT =====\n";
        printStudent(front->data);
    }

    // DISPLAY 
    void Display()
    {
        if (front == nullptr)
        {
            cout << "\nService queue is empty.\n";
            return;
        }

        Node* current = front;
        int position = 1;

        cout << "\n===== STUDENT SERVICE QUEUE =====\n";

        while (current != nullptr)
        {
            cout << "\nPosition: " << position << endl;

            printStudent(current->data);

            current = current->next;
            position++;
        }

        cout << "=================================\n";
    }

    // Check if queue is empty
    bool IsEmpty() const
    {
        return front == nullptr;
    }
};

class LinkedList
{
private:
    Node* head;
    Node* tail;

public:
    LinkedList() : head(nullptr), tail(nullptr) {}

    ~LinkedList()
    {
        while (head != nullptr)
        {
            Node* toDelete = head;
            head = head->next;
            delete toDelete;
        }
        tail = nullptr;
    };

    // Delete Student function, by ID and return the deleted student
    bool DeleteStudent(const string& id, Student& deletedStudent)
    {
        Node* cur = head;

        while (cur != nullptr && cur->data.studentID != id)
        {
            cur = cur->next;
        }
        if (cur == nullptr)
            return false;

        deletedStudent = cur->data;

        if (cur->prev != nullptr)
            cur->prev->next = cur->next;
        else
            head = cur->next;

        if (cur->next != nullptr)
            cur->next->prev = cur->prev;
        else
            tail = cur->prev;

        delete cur;
        return true;
    }

    void AppendStudent(const Student& s)
    {
        Node* newNode = new Node(s);

        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
            return;
        }

        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    void DisplayStudent() const
    {
        if (checkStudentListIfEmpty()) { return; }

        for (Node* cur = head; cur != nullptr; cur = cur->next)
        {
            printStudent(cur->data);
        }
    }

    void LinearSearchStudent()
    {
        bool found = false;

        if (checkStudentListIfEmpty()) { return; }

        string searchTarget = checkString("Enter ID to search for: ");

        for (Node* cur = head; cur != nullptr; cur = cur->next)
        {
            if (cur->data.studentID == searchTarget)
            {
                printStudent(cur->data);
                found = true;
                break;
            }
        }
        if (!found)
        {
            cout << "(Info)Result Not found\n";
        }
    }

    Node* findMiddle(Node* start, Node* end)
    {
        if (start == nullptr)
            return nullptr;

        Node* slow = start;
        Node* fast = start;
        while (fast != end && fast->next != end)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    Node* BinarySearchStudent(const string& id)
    {
        Node* start = head;
        Node* end = nullptr;

        while (start != end)
        {
            Node* mid = findMiddle(start, end);
            if (mid->data.studentID == id)
            {
                return mid;
            }
            else if (mid->data.studentID < id)
            {
                start = mid->next;
            }
            else
            {
                end = mid;
            }
        }
        return nullptr;
    }
    Node* FindById(const string& id) const
    {
        for (Node* cur = head; cur != nullptr; cur = cur->next)
            if (cur->data.studentID == id)
                return cur;
        return nullptr;
    }
    bool checkStudentListIfEmpty() const
    {
        if (head == nullptr) {
            cout << "Student List is Currently Empty, Please Add Student." << endl;
            return true;
        }
        else {
            return false;
        }
    }
};

// Global
LinkedList StudentInfo;
stack<Student> recentDeletions;
StudentServiceQueue ServiceQueue;
int main()
{

    int choice;

    do
    {

        cout << "========================================\n";
        cout << " STUDENT RECORD MANAGEMENT SYSTEM\n";
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

        choice = checkInt("Enter your choice: ", 1, 10);
        switch (choice)
        {
        case 1:
        {
            AddStudents();
        }
        break;
        case 2:
            StudentInfo.DisplayStudent();
            break;
        case 3:
            SearchStudent();
            break;
        case 4:
            cout << "Update Student:\n";
            break;
        case 5:
            DeleteStudentMenu();
            break;
        case 6:
            cout << "Sort Students:\n";
            break;
        case 7:
            DisplayRecentDeletions();
            break;
        case 8:
            StudentServiceMenu();
            break;
        case 9:
            cout << "Student Statistics:\n";
            break;
        case 10:
            cout << "Bye!\n";
            break;
        default:
            cout << "Choice are invalid please choose between 1-10\n";
            break;
        }
    } while (choice != 10);

    return 0;
}

void AddStudents()
{
    string ans;
    Student info;
    do
    {
        cout << "< Add Student below >\n";

        info.studentID = checkUniqueID();

        info.firstName = checkString("First Name: ");

        info.middleInitials = checkString("Middle Initials: ");

        info.surname = checkString("Surname: ");

        info.courseName = checkString("Course: ");

        info.GPA = checkFloat("GPA: ", 1.0, 6.0);

        StudentInfo.AppendStudent(info);
        cout << "Do you want to add another student to the list (y/n): ";
        getline(cin, ans);
    } while (ans == "y" || ans == "Y");
}

void SearchStudent()
{
    int choice;

    do
    {

        cout << "========================================\n";
        cout << "Search Student\n";
        cout << "========================================\n";
        cout << "1. Linear Search (by Student ID)\n";
        cout << "2. Binary Search (by Student ID)\n";
        cout << "3. Return to Main Menu\n";
        cout << "========================================\n";
        choice = checkInt("Enter your choice: ", 1, 3);

        switch (choice)
        {
        case 1:
            StudentInfo.LinearSearchStudent();
            break;
        case 2:
            BinarySearchStudent();
            break;

        case 3:
            cout << "Returning to main menu\n";
            break;
        default:
            cout << "Choice are invalid please choose between 1-3\n";
            break;
        }

    } while (choice != 3);
}

void BinarySearchStudent()
{
    if (StudentInfo.checkStudentListIfEmpty()) { return; }

    string id = checkString("Enter ID to search for: ");
    Node* result = StudentInfo.BinarySearchStudent(id);

    if (result != nullptr)
        printStudent(result->data);
    else
        cout << "Student not found.\n";
}

// Delete Student Menu
void DeleteStudentMenu()
{
    if (StudentInfo.checkStudentListIfEmpty()) { return; }

    string id = checkString("Enter Student ID to delete: ");
    Student deletedStudent;

    Node* student = StudentInfo.FindById(id);
    if (student == nullptr)
    {
		cout << "\nStudent not found...\n";
        return;
    }

    //Student to be deleted's information
	cout << "\n===== STUDENT TO BE DELETED =====\n";
    printStudent(student->data);

	//delete confirmation
    string confirm;
	cout << "Are you sure you want to delete this student? (y/n): ";
    getline(cin, confirm);

    if (confirm == "y" || confirm == "Y")
    {
        if (StudentInfo.DeleteStudent(id, deletedStudent))
        {
            recentDeletions.push(deletedStudent);
            cout << "\n Student successfully deleted!\n";
			cout << "Deleted student information can be viewed in recent deletions.\n";
        }
    }
    else
    {
        cout << "\nDeletion cancelled...\n";
    }
}
// Recent Deletions Menu
void DisplayRecentDeletions()
{
    if (recentDeletions.empty())
    {
        cout << "No recent deletions. \n";
        return;
    }

    stack<Student> temp = recentDeletions;

    cout << "========================================\n";
    cout << "         Recent Deletions\n";
    cout << "========================================\n";

    while (!temp.empty())
    {
        printStudent(temp.top());
        cout << "------------------------------------\n";

        temp.pop();
    }
}

void StudentServiceMenu()
{
    int choice;

    do
    {
        cout << "\n========================================\n";
        cout << "         STUDENT SERVICE QUEUE\n";
        cout << "========================================\n";
        cout << "1. Enqueue Student\n";
        cout << "2. Dequeue Student\n";
        cout << "3. Peek Next Student\n";
        cout << "4. Display Queue\n";
        cout << "5. Return to Main Menu\n";
        cout << "========================================\n";

        choice = checkInt("Enter your choice: ", 1, 5);

        switch (choice)
        {
        case 1:
        {
            string id = checkString("Enter Student ID: ");
            Node* student = StudentInfo.FindById(id);

            if (student != nullptr)
                ServiceQueue.Enqueue(student->data);
            else
                cout << "\nStudent ID not found in records.\n";

            break;
        }

        case 2:
            ServiceQueue.Dequeue();
            break;

        case 3:
            ServiceQueue.Peek();
            break;

        case 4:
            ServiceQueue.Display();
            break;

        case 5:
            cout << "\nReturning to main menu...\n";
            break;
        }

    } while (choice != 5);
}

int checkInt(const string& question, int minVal, int maxVal)
{
    int value;
    while (true)
    {
        cout << question;
        if (cin >> value && value >= minVal && value <= maxVal)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter a number from " << minVal << " to " << maxVal << ".\n";
    }
}

float checkFloat(const string& question, float minVal, float maxVal)
{
    int value;
    while (true)
    {
        cout << question;
        if (cin >> value && value >= minVal && value <= maxVal)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter a number from " << minVal << " to " << maxVal << ".\n";
    }
}

string checkString(const string& question)
{
    string ans;
    while (true)
    {
        cout << question;
        getline(cin, ans);
        if (!ans.empty())
            return ans;
        cout << "This cannot be empty. \n";
    }
}
void printStudent(const Student& s)
{
    cout << "ID: " << s.studentID << "\n";
    cout << "Name: " << s.firstName << " " << s.middleInitials << " " << s.surname << "\n";
    cout << "Course: " << s.courseName << "\n";
    cout << "GPA: " << s.GPA << "\n";
};

string checkUniqueID()
{
    while (true)
    {
        string id = checkString("ID: ");
        if (StudentInfo.FindById(id) == nullptr)
            return id; // not found = ID is free
        cout << "That ID already exists. Enter a different one.\n";
    }
}
