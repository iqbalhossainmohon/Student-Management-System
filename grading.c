//
// Created by iqbal on 06/11/2024.
//
#include <stdio.h>
#include "grading.h"

// File path for student grade data
#define GRADES_FILE "student_grades.csv"

// Function to calculate CGPA based on marks
float calculateCGPA(float bangla, float english, float math, float physics, float chemistry) {
    float average = (bangla + english + math + physics + chemistry) / 5.0;
    return (average / 20.0);  // Scale to 5.0
}

// Function to view all students' grades and CGPA
void viewStudentGrades() {
    FILE *file = fopen(GRADES_FILE, "r");

    if (file == NULL) {
        printf("No grade records found.\n");
        return;
    }

    printf("\n\t\t\t=============== Student Grades ===============\n");
    printf(" ID \t Name \t\t\t Bangla \t English \t Math \t Physics \t Chemistry \t CGPA\n");

    int rollNo;
    char name[100];
    float bangla, english, math, physics, chemistry, cgpa;
    char line[200];

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d,%[^,],%f,%f,%f,%f,%f,%f", &rollNo, name, &bangla, &english, &math, &physics, &chemistry, &cgpa);

        printf("%d \t %s \t\t %.2f \t\t %.2f \t\t %.2f \t %.2f \t\t %.2f \t\t %.2f\n",
               rollNo, name, bangla, english, math, physics, chemistry, cgpa);
    }

    fclose(file);
}
