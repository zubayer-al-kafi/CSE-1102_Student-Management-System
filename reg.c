#include "header.h"

void scrolltext(char *str)
{
    for(int i=0; i<strlen(str); i++)
    {
        printf("%c",str[i]);
        fflush(stdin);
        Sleep(10);
    }
}

void takeinput(char ch[50])
{
    fgets(ch,50,stdin);
    ch[strlen(ch)-1] = '\0';
}

FILE *fp, *fpid;
int registration()
{
    system("color 70");
    system("cls");
    int choice;
    printf("\t\t\t---Registration---\n");
    printf("\t\t1. Register as a student\n\t\t2. Register as a teacher\n\t\t3. Go back\n");
    scrolltext("\n\t\tEnter your choice: ");
    scanf("%d", &choice);
    getchar();
    switch (choice)
    {
    case 1:
        fp = fopen("stdinfo.txt", "a");
        system("cls");
        printf("\t\t\t---Student Registration---\n");
        printf("\t\tEnter your name: \t");
        takeinput(s.name);
        printf("\t\tEnter your email: \t");
        takeinput(s.email);
        printf("\t\tEnter your number: \t");
        takeinput(s.phone);
        printf("\t\tEnter your roll: \t");
        takeinput(s.roll);
        printf("\t\tEnter your password: \t");
        takepassword(s.password);
        char pass2[50];
        printf("\t\tConfirm your password: \t");
        takepassword(pass2);
        if (strcmp(s.password, pass2) != 0)
        {
            fclose(fp);
            printf("\033[1;31m\n\t\tPasswords do not match.\n\033[0m\n");
            Beep(823, 500);
            Sleep(1000);
            registration();
            return 0;
        }
        else
        {
            fwrite(&s, sizeof(user), 1, fp);
            fclose(fp);
            scrolltext("\n\n\t\tRegistering");
            for(int i=0; i<3; i++)
            {
                printf(".");
                Sleep(500);
            }
            printf("\033[1;32m\r\t\tRegistration successful!\n\033[0m\n");
            printf("\n\t\tYour ID is your roll number : %s\n", s.roll);
            system("pause");
            login();
        }
        break;
    case 2:
        fp = fopen("teacherinfo.txt", "a");
        system("cls");
        printf("\t\t\t---Teacher Registration---\n");
        printf("\t\tEnter your name: \t");
        takeinput(t.name);
        printf("\t\tEnter your email: \t");
        takeinput(t.email);
        printf("\t\tEnter your number: \t");
        takeinput(t.phone);
        printf("\t\tEnter your password: \t");
        takepassword(t.password);
        printf("\t\tConfirm your password: \t");
        takepassword(pass2);
        if (strcmp(t.password, pass2) != 0)
        {
            printf("\033[1;31m\n\t\tPasswords do not match.\n\033[0m\n");
            fclose(fp);
            Beep(523, 500);
            Sleep(1000);
            registration();
            return 0;
        }
        else
        {
            fwrite(&t, sizeof(user), 1, fp);
            fclose(fp);
            scrolltext("\n\n\t\tRegistering");
            for(int i=0; i<3; i++)
            {
                printf(".");
                Sleep(500);
            }
            printf("\033[1;32m\r\t\tRegistration successful!\n\033[0m\n");
            system("pause");
            login();
        }
        break;
    case 3:
        main();
        break;
    default:
        printf("\n\t\t\t---Invalid choice---\n");
        registration();
        break;
    }
}

int login()
{
    system("color 70");
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
        takeinput(id);
        printf("\t\tEnter your password : \t\t");
        takepassword(password);
        fp = fopen("stdinfo.txt", "r");

        while (fread(&s, sizeof(user),1,fp) != NULL)
        {
            if (strcmp(id, s.roll) == 0)
            {
                if (strcmp(password, s.password) == 0)
                {
                    fclose(fp);
                    scrolltext("\n\t\tLogging in");
                    for(int i=0; i<3; i++)
                    {
                        printf(".");
                        Sleep(500);
                    }
                    printf("\033[1;32m\r\t\tLogin successful!\n\033[0m\n");
                    system("pause");
                    options(id,password);
                    return 1;
                }
                else
                {
                    fclose(fp);
                    scrolltext("\033[1;31m\n\t\tWrong Password.\n\033[0m\n");
                    Beep(823,500);
                    Sleep(2000);
                    login();
                    return 0;
                }
            }
        }
        fclose(fp);
        printf("\033[1;31m\n\t\tUser not found.\n\033[0m");
        Beep(823,500);
        system("pause");
        login();
        break;
    case 2:
        system("cls");
        char email[50];
        printf("\t\t\t---Teacher Login---\n\n");
        printf("\t\tEnter your email: \t");
        takeinput(email);
        printf("\t\tEnter your password: \t");
        takepassword(password);
        fp = fopen("teacherinfo.txt", "r");

        while (fread(&t,sizeof(user),1,fp) != NULL)
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
                    system("pause");
                    optiont(email,password);
                    return 1;
                }
                else
                {
                    fclose(fp);
                    scrolltext("\033[1;31m\t\tWrong Password.\n\033[0m\n");
                    Sleep(2000);
                    return 0;
                }
            }
        }
        fclose(fp);
        scrolltext("\t\tUser not found.\n");
        Sleep(1000);
        login();
        return 0;
        break;
    case 3:
        main();
        break;
    default:
        scrolltext("\t\t\t---Invalid choice---\n");
        Sleep(1000);
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
            if (i >0)
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
