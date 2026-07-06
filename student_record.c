#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LENGTH 50

// Structure to store student details
struct Student {
    int id;
    char name[NAME_LENGTH];
    float gpa;
};

// Function prototypes
void addStudent(struct Student students[], int *count);
void displayStudents(const struct Student students[], int count);
void searchStudent(const struct Student students[], int count);

int main() {
    struct Student students[MAX_STUDENTS];
    int count = 0;
    int choice;

    while (1) {
        printf("\n=== Student Record Management System ===\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student by ID\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            // Clear input buffer
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                addStudent(students, &count);
                break;
            case 2:
                displayStudents(students, count);
                break;
            case 3:
                searchStudent(students, count);
                break;
            case 4:
                printf("Exiting program. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please select between 1 and 4.\n");
        }
    }

    return 0;
}

// Function to add a new student record
void addStudent(struct Student students[], int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("Database is full! Cannot add more students.\n");
        return;
    }

    struct Student newStudent;
    
    printf("\nEnter Student ID: ");
    scanf("%d", &newStudent.id);
    
    // Check if ID already exists
    for (int i = 0; i < *count; i++) {
        if (students[i].id == newStudent.id) {
            printf("Error: A student with ID %d already exists.\n", newStudent.id);
            return;
        }
    }

    printf("Enter Student Name: ");
    // Clear newline character left in buffer by scanf
    getchar(); 
    fgets(newStudent.name, NAME_LENGTH, stdin);
    // Remove trailing newline from fgets
    newStudent.name[strcspn(newStudent.name, "\n")] = '\0';

    printf("Enter Student GPA: ");
    scanf("%f", &newStudent.gpa);

    // Save to array and increment total count
    students[*count] = newStudent;
    (*count)++;
    
    printf("Student added successfully!\n");
}

// Function to print all student records
void displayStudents(const struct Student students[], int count) {
    if (count == 0) {
        printf("\nNo student records found.\n");
        return;
    }

    printf("\n%-10s %-30s %-5s\n", "ID", "Name", "GPA");
    printf("---------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-10d %-30s %-5.2f\n", students[i].id, students[i].name, students[i].gpa);
    }
}

// Function to find a student by their unique ID
void searchStudent(const struct Student students[], int count) {
    if (count == 0) {
        printf("\nNo records available to search.\n");
        return;
    }

    int searchId;
    printf("\nEnter Student ID to search: ");
    scanf("%d", &searchId);

    for (int i = 0; i < count; i++) {
        if (students[i].id == searchId) {
            printf("\nStudent Found:\n");
            printf("ID: %d\n", students[i].id);
            printf("Name: %s\n", students[i].name);
            printf("GPA: %.2f\n", students[i].gpa);
            return;
        }
    }

    printf("Student with ID %d not found.\n", searchId);
}
