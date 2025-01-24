#include "header.h"
FILE *fp;
int stdresult(char *fid)
{
    system("cls");

    char id[8];
    printf("\t\tYour Result for 1-1\n");
    fp = fopen("gpa.txt", "r");

    if (fp == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    float gp[8], gpa;
    while (fscanf(fp, "%s %f %f %f %f %f %f %f %f %f",
                  id, &gp[0], &gp[1], &gp[2], &gp[3],
                  &gp[4], &gp[5], &gp[6], &gp[7], &gpa) != EOF)
    {
        if (strcmp(fid, id) == 0)
        {
            printf("\tCSE  1101 : %.2f\n", gp[0]);
            printf("\tCSE  1102 : %.2f\n", gp[1]);
            printf("\tCSE  1107 : %.2f\n", gp[2]);
            printf("\tPHY  1107 : %.2f\n", gp[3]);
            printf("\tPHY  1108 : %.2f\n", gp[4]);
            printf("\tMATH 1107 : %.2f\n", gp[5]);
            printf("\tHUM  1107 : %.2f\n", gp[6]);
            printf("\tHUM  1108 : %.2f\n\n", gp[7]);
            printf("\tGPA       : %.2f\n", gpa);
            break;
        }
    }
    fclose(fp);
    system("pause");
    return 0;
}

int gpcal()
{
    system("cls");
    printf("\t\tGPA Calculator\n\n");

    // Input student ID
    char id[8];
    printf("Enter the ID of student: ");
    takeinput(id);

    // Course credits and names
    float credits[] = {3, 1.5, 3, 3, 1.5, 3, 3, 0.75};
    char *courseCodes[] =
    {
        "CSE  1101", "CSE  1102", "CSE  1107",
        "PHY  1107", "PHY  1108", "MATH 1107",
        "HUM  1107", "HUM  1108"
    };

    float sum = 0, gpa, gp[8];
    int numCourses = 8;

    // Input grades and calculate weighted sum
    for (int i = 0; i < numCourses; i++)
    {
        printf("\t%s : ", courseCodes[i]);
        scanf("%f", &gp[i]);
        sum += credits[i] * gp[i];
    }
    fflush(stdin);

    float totalCredits = 0;
    for (int i = 0; i < numCourses; i++)
    {
        totalCredits += credits[i];
    }
    gpa = sum / totalCredits;

    printf("\n\tGPA is: %.2f\n", gpa);

    fp = fopen("gpa.txt", "a");
    if (fp == NULL)
    {
        printf("Error opening file");
        return 1;
    }

    fprintf(fp, "%s %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f\n",
            id, gp[0], gp[1], gp[2], gp[3], gp[4], gp[5], gp[6], gp[7], gpa);

    fclose(fp);
    system("pause");

    return 0;
}
