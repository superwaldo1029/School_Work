#include <stdio.h>
#include <string.h>

// Structure definition for student record
typedef struct student {
    char lname[25];
    char fname[25];
    float gpa;
    int age;
} student;

int main() {
    student thisclass[10];  // Create array of 10 student records

    // Input loop to populate student records
    printf("Enter information for 10 students:\n");
    for (int i = 0; i < 10; i++) {
        printf("\nStudent %d:\n", i + 1);

        printf("Enter last name: ");
        scanf("%24s", thisclass[i].lname);  // Limit input to 24 chars to leave room for null terminator

        printf("Enter first name: ");
        scanf("%24s", thisclass[i].fname);

        printf("Enter GPA (0.0-4.0): ");
        scanf("%f", &thisclass[i].gpa);

        printf("Enter age: ");
        scanf("%d", &thisclass[i].age);

        // Clear input buffer
        while (getchar() != '\n');
    }

    // Display all student records
    printf("\nClass Record:\n");
    printf("----------------------------------------\n");
    printf("%-25s %-25s %-6s %-4s\n", "Last Name", "First Name", "GPA", "Age");
    printf("----------------------------------------\n");

    for (int i = 0; i < 10; i++) {
        printf("%-25s %-25s %.2f  %d\n",
               thisclass[i].lname,
               thisclass[i].fname,
               thisclass[i].gpa,
               thisclass[i].age);
    }

    return 0;
}