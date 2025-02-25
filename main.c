/*
            CSE 1102 Project
    PROJECT NAME : STUDENT MANAGEMENT SYSTEM
                by
    2307073,2307074,2307076
*/

#include "header.h"

int main()
{
    system("color 70");
    system("cls");
    SetConsoleTitle("STUDENT MANAGEMENT SYSTEM");
    int opt;
    printf("\t\t\t---Welcome to the Student Management System---\n\n");
    printf("\t\t1. Registration\n\t\t2. Login\n\t\t3. Exit\n");
    scrolltext("\n\t\tEnter your choice: ");
    scanf("%d", &opt);
    getchar();
    switch (opt)
    {
    case 1:
        system("cls");
        registration();
        break;
    case 2:
        system("cls");
        login();
        break;
    case 3:
        scrolltext("\t\t\tExiting");
        for(int i=0; i<3; i++)
        {
            printf(".");
            Sleep(500);
        }
        exit(0);
        break;
    default:
        scrolltext("\t\t\t---Invalid choice---\n");
        Beep(800,500);
        Sleep(500);
        system("cls");

        main();
        break;
    }
}
