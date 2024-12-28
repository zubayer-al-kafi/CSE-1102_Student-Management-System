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
    SetConsoleTitle("STUDENT MANAGEMENT SYSTEM");
    system("color 0B");
    int opt;
    printf("\t\t\t---Welcome to the student management system---\n\n");
    //scroll text
    char *msg = "\t\t1. Registration\n\t\t2. Login\n\t\t3. Exit\n\n\t\tEnter your choice: ";
    for(int i=0;msg[i]!='\0';i++)
    {
        printf("%c",msg[i]);
        fflush(stdout);
        Sleep(10);
    }


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
        printf("\t\t\t---Exiting---\n");
        Sleep(1000);
        exit(0); //exiting the program
        break;
    default:
        printf("\t\t\t---Invalid choice---\n");
        break;
    }
}
