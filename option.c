#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "option.h"
#include "reg.h"
#include "mystruct.h"

FILE *fp;
void options(char *fid)
{
    system("cls");
    int opt;
    printf("\t\t1. View your information\n\t\t2. Edit your information\n\t\t3. Delete your account\n\t\t4. Logout\n");
    printf("\n\t\tEnter your choice: ");
    scanf("%d", &opt);
    switch (opt)
    {
    case 1:
        printf("\t\t\t---Your information---\n");
        fp = fopen("stdinfo.txt", "r");
        while (fscanf(fp, "%s %s %s %s", s.roll, s.name, s.email, s.phone) != EOF)
        {
            if (strcmp(s.roll, fid) == 0)
            {
                printf("\t\tName: %s\n\t\tEmail: %s\n\t\tPhone: %s\n\t\tRoll: %s\n", s.name, s.email, s.phone, s.roll);
                break;
            }
        }
        break;
    case 2:

    default:
        printf("\t\t---Invalid choice---");
        Sleep(1000);
        options(fid);
        return 0;
    }
}

void optiont(char *femail)
{
    system("cls");
    int opt;
    printf("\t\t1. View your information\n\t\t2. Edit your information\n\t\t3. Calculate GPA\n");
    printf("\t\t4. CGPA Calculator\n\t\t5. Elect CR\n\t\t6. Logout\n");
    printf("\n\t\tEnter your choice: ");
    scanf("%d", &opt);
    getchar();
    switch (opt)
    {
    case 1:
        printf("\t\t\t---Your information---\n");
        fp = fopen("teacherinfo.txt", "r");
        while (fscanf(fp, "%s %s %s", t.email, t.name, t.phone) != EOF)
        {
            if (strcmp(t.email, femail) == 0)
            {
                printf("\t\tName: %s\n\t\tEmail: %s\n\t\tPhone: %s\n", t.name, t.email, t.phone);
                break;
            }
        }
        printf("Press any key to continue...");
        getchar();
        optiont(femail);
        break;
    case 2:
        break;
    case 3:
        gpcal();
        optiont(femail);
        break;
    case 4:
        cgpcal();
        optiont(femail);
        break;
    case 5:
        elect_cr();
        optiont(femail);
        break;
    }
}

int gpcal()
{
    printf("\t\tGPA Calculator\n\n");
    int courses;
    printf("Enter the total number of courses: ");
    scanf("%d", &courses);
    float gp[courses][2];
    printf("Enter Grade point and CREDIT for each course: \n");
    printf("READ CARFULLY : GP and Credit have to be space separated. Otherwise it'll produce error.\n");
    printf("\n\t\tGP- Credit\n");
    printf("---------------------------------------------------------\n");
    for (int i = 0; i < courses; i++)
    {
        printf("\t\t");
        scanf("%f %f", &gp[i][0], &gp[i][1]);
        getchar();
        if (gp[i][0] > 4)
        {
            printf("Invalid input\n");
            printf("Press any key to continue...");
            getchar();
            return 0;
        }
    }
    float total_credit = 0;
    for (int i = 0; i < courses; i++)
    {
        total_credit += gp[i][1];
    }
    float score = 0;
    for (int i = 0; i < courses; i++)
    {
        score += gp[i][0] * gp[i][1];
    }
    float cg;
    cg = (float)score / (float)total_credit;
    if (cg > 4)
    {
        printf("Please give input carefully.\n");
    }
    else
        printf("THE GPA IS %.2f\n\n", cg);

    printf("Press any key to continue...");
    getchar();
    return 0;
}

int cgpcal()
{
    int n;
    printf("How many semesters?");
    scanf("%d", &n);
    getchar();
    float gp[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%f", &gp[i]);
        getchar();
    }
    float sum = 0;
    for (int i = 0; i < n; i++)
        sum += gp[i];
    printf("The CGPA is : %.2f\n", sum / n);
    printf("Press any key to continue...");
    getchar();
    return 0;
}

int elect_cr()
{
    int candidate, voter;
    printf("Number of candidates: ");
    scanf("%d", &candidate);
    printf("Total number of students: ");
    scanf("%d", voter);
    printf("\nThe maximum candidate is limited to 5 and not less than 2\n\n");
    printf("Enter the candidates roll number: ");


    return;
}
