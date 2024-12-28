//CSE 1102 Project


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include "reg.h"
#include "option.h"
#include "mystruct.h"

int main()
{
    system("color 0B");
    SetConsoleTitle("STUDENT MANAGEMENT SYSTEM");
    int opt;
    printf("\t\t\t---Welcome to the student management system---\n\n");
    printf("\t\t1. Registration\n\t\t2. Login\n\t\t3. Exit\n");
    scrolltext("\n\t\tEnter your choice: ");
    scanf_s("%d", &opt);
    getchar();
    switch (opt)
    {
    case 1:
        system("cls");
        registration(); //calling the registration function
        break;
    case 2:
        system("cls");
        login(); //calling the login function
        break;
    case 3:
        system("cls");
        scrolltext("\t\t\tExiting");
        for(int i=0; i<3; i++)
        {
            printf(".");
            Sleep(500);
        }
        exit(0); //exiting the program
        break;
    default:
        scrolltext("\t\t\t---Invalid choice---\n");
        Sleep(1000);
        system("cls");
        main();
        break;
    }
}
