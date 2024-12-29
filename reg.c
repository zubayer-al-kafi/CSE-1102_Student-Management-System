#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "option.h"
#include "reg.h"
#include "mystruct.h"
void scrolltext(char *str)
{
    for(int i=0; i<strlen(str); i++)
    {
        printf("%c",str[i]);
        fflush(stdin);
        Sleep(10);
    }
}
FILE *fp, *fpid;
int registration()
{
    system("color 0B");
    int choice;
    printf("\t\t\t---Registration---\n");
    printf("\t\t1. Register as a student\n\t\t2. Register as a teacher\n");
    scrolltext("\n\t\tEnter your choice: ");
    scanf_s("%d", &choice);
    getchar();
    switch (choice)
    {
    case 1:
        fp = fopen("stdinfo.txt", "a");
        system("cls");
        printf("\t\t\t---Student Registration---\n");
        printf("\t\tEnter your name: \t");
        gets(s.name);
        printf("\t\tEnter your email: \t");
        gets(s.email);
        printf("\t\tEnter your number: \t");
        gets(s.phone);
        printf("\t\tEnter your roll: \t");
        gets(s.roll);
        printf("\t\tEnter your password: \t");
        takepassword(s.password);
        char pass2[50];
        printf("\t\tConfirm your password: \t");
        takepassword(pass2);
        if (strcmp(s.password, pass2) != 0)
        {
            printf("\033[1;31m\n\t\tPasswords do not match.\n\033[0m\n");
            Beep(523, 500);
            Sleep(2000);
            fclose(fp);
            return 0;
        }
        else
        {
            fprintf(fp, "%s %s %s %s\n", s.roll, s.name, s.email, s.phone);
            fclose(fp);
            fpid = fopen("stdidpass.txt", "a");
            fprintf(fpid, "%s %s\n", s.roll, s.password);
            fclose(fpid);
            scrolltext("\n\n\t\tRegistering");
            for(int i=0; i<3; i++)
            {
                printf(".");
                Sleep(500);
            }
            printf("\033[1;32m\n\t\tRegistration successful!\n\033[0m\n");
            printf("\n\t\tYour ID is your roll number : %s\n", s.roll);
            printf("\t\tPress any key to continue...\n");
            getchar();
            login();
        }
        break;
    case 2:
        fp = fopen("teacherinfo.txt", "a");
        system("cls");
        printf("\t\t\t---Teacher Registration---\n");
        printf("\t\tEnter your name: \t");
        gets(t.name);
        printf("\t\tEnter your email: \t");
        gets(t.email);
        printf("\t\tEnter your number: \t");
        gets(t.phone);
        printf("\t\tEnter your password: \t");
        takepassword(t.password);
        printf("\t\tConfirm your password: \t");
        takepassword(pass2);
        if (strcmp(t.password, pass2) != 0)
        {
            printf("\033[1;31m\n\t\tPasswords do not match.\n\033[0m\n");
            fclose(fp);
            Beep(523, 500);
            Sleep(2000);
            return 0;
        }
        else
        {
            fprintf(fp, "%s %s %s\n", t.email, t.name, t.phone);
            fclose(fp);
            fpid = fopen("teacheridpass.txt", "a");
            fprintf(fpid, "%s %s\n", t.email, t.password);
            fclose(fpid);
            scrolltext("\n\n\t\tRegistering");
            for(int i=0; i<3; i++)
            {
                printf(".");
                Sleep(500);
            }
            printf("\033[1;32m\r\t\tRegistration successful!\n\033[0m\n");
            printf("\t\tPress any key to continue...\n");
            getchar();
            login();
        }
        break;
    default:
        printf("\n\t\t\t---Invalid choice---\n");
        registration();
        break;
    }
}

int login()
{
    system("color 0B");
    system("cls");
    int choice;
    printf("\t\t\t---Login---\n");
    printf("\t\t1. Login as a student\n\t\t2. Login as a teacher\n\t\t3. Go Back\n");
    scrolltext("\n\t\tEnter your choice: ");
    scanf("%d", &choice);
    getchar();
    char id[10], password[50];
    switch (choice)
    {
    case 1:
        system("cls");
        printf("\t\t\t---Student login---\n\n");
        printf("\t\tEnter your ID : \t\t");
        gets(id);
        printf("\t\tEnter your password : \t\t");
        takepassword(password);
        fp = fopen("stdidpass.txt", "r");
        char fid[10], fpass[50];
        while (fscanf(fp, "%s %s", fid, fpass) != EOF)
        {
            if (strcmp(id, fid) == 0)
            {
                if (strcmp(password, fpass) == 0)
                {
                    fclose(fp);
                    scrolltext("\n\t\tLogging in");
                    for(int i=0; i<3; i++)
                    {
                        printf(".");
                        Sleep(500);
                    }
                    printf("\033[1;32m\r\t\tLogin successful!\n\033[0m\n");
                    printf("\t\tPress any key to continue...\n");
                    getchar();
                    options(fid);
                    return 1;
                }
                else
                {
                    fclose(fp);
                    scrolltext("\033[1;31m\n\t\tWrong Password.\n\033[0m\n");
                    //printf("\033[1;31m\t\tWrong Password.\n\033[0m\n");
                    Sleep(2000);
                    login();
                }
            }
        }
        fclose(fp);
        printf("User not found.\n");
        printf("Press any key to continue...");
        getchar();
        login();
        break;
    case 2:
        system("cls");
        char email[50];
        printf("\t\t\t---Teacher Login---\n\n");
        printf("\t\tEnter your email: \t");
        gets(email);
        printf("\t\tEnter your password: \t");
        takepassword(password);
        fp = fopen("teacheridpass.txt", "r");

        while (fscanf(fp, "%s %s", t.email, t.password) != EOF)
        {
            if (strcmp(email, t.email) == 0)
            {
                if (strcmp(password, t.password) == 0)
                {
                    fclose(fp);
                    printf("\n\t\tLogging in");
                    for(int i=0; i<3; i++)
                    {
                        printf(".");
                        Sleep(500);
                    }
                    printf("\033[1;32m\r\t\tLogin successful!\n\033[0m\n");
                    printf("\t\tPress any key to continue...\n");
                    getchar();
                    optiont(email);
                    return 1;
                }
                else
                {
                    fclose(fp);
                    scrolltext("\033[1;31m\t\tWrong Password.\n\033[0m\n");
                    //printf("Wrong Password.\n");
                    Sleep(2000);
                    return 0;
                }
            }
        }
        fclose(fp);
        printf("User not found.\n");
        Sleep(1000);
        login();
        return 0;
        break;
    case 3:
        main();
        break;
    default:
        scrolltext("\t\t\t---Invalid choice---\n");
        login();
        break;
    }
}

int takepassword(char pass[50])
{
    char ch;
    int i = 0;
    while (1)
    {
        ch = getch();
        if (ch == 32 || ch == 9 || ch == 10 || ch == 11 || ch == 12 || ch == 27)
        {
            continue;
        }
        else if (ch == 13)
        {
            pass[i] = '\0';
            printf("\n");
            break;
        }
        else if (ch == 8)
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else
        {
            pass[i] = ch;
            i++;
            printf("*");
        }
    }
}
