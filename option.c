#include "header.h"
#define MAX 9

FILE *fp;
int options(char *fid, char *password)
{
    system("color 70");
    system("cls");
    int opt;
    printf("\t\t\t---Student Dashboard---\n\n");
    printf("\t\t1. View your information\n\t\t2. Edit your information\n\t\t3. Delete your account\n");
    printf("\t\t4. Course Registration\n\t\t5. View your result\n\t\t6. Logout\n");
    scrolltext("\n\t\tEnter your choice: ");
    scanf("%d", &opt);
    getchar();
    switch (opt)
    {
    case 1:
        printf("\t\t\t---Your information---\n");
        fp = fopen("stdinfo.txt", "r");
        while (fread(&s,sizeof(user),1,fp) != 0)
        {
            if (strcmp(fid,s.roll) == 0)
            {
                fclose(fp);
                printf("\t\tName: %s\n\t\tEmail: %s\n\t\tPhone: %s\n\t\tRoll: %s\n", s.name, s.email, s.phone, s.roll);
                break;
            }
        }
        fclose(fp);
        system("pause");
        options(fid,password);
        break;
    case 2:
        editstdinfo(fid,password);
        options(fid,password); // return back to options
        break;
    case 3:
        dlt(fid,password);
        main();
        break;
    case 4:
        course_reg(fid);
        options(fid,password);
        break;
    case 5:
        stdresult(fid);
        options(fid,password);
        break;
    case 6:
        printf("\n\t\tLogging out");
        for(int i=0; i<3; i++)
        {
            printf(".");
            fflush(stdin);
            Sleep(500);
        }
        login();
        break;
    default:
        scrolltext("\t\t---Invalid choice---");
        Sleep(1000);
        options(fid,password);
        return 0;
    }
}

int optiont(char *femail, char *password)
{
    system("color 70");
    system("cls");
    int opt;
    printf("\t\t\t---Teacher Dashboard---\n\n");
    printf("\t\t1. View your information\n\t\t2. Edit your information\n\t\t3. Insert Student's result\n");
    printf("\t\t4. Calculate CGPA\n\t\t5. Elect CR\n\t\t6. Search student\n\t\t7. Logout\n");
    scrolltext("\n\t\tEnter your choice: ");
    scanf("%d", &opt);
    getchar();
    switch (opt)
    {
    case 1:
        printf("\n\n");
        printf("\t\t\t---Your information---\n");
        fp = fopen("teacherinfo.txt", "r");
        while (fread(&t,sizeof(user),1,fp) != NULL)
        {
            if (strcmp(t.email, femail) == 0)
            {
                printf("\t\tName: %s\n\t\tEmail: %s\n\t\tPhone: %s\n", t.name, t.email, t.phone);
                break;
            }
        }
        system("pause");
        optiont(femail,password);
        break;

    case 2:
        edittcrinfo(femail,password);
        optiont(femail,password);
        break;

    case 3:
        gpcal();
        optiont(femail,password);
        break;

    case 4:
        cgpcal();
        optiont(femail,password);
        break;
    case 5:
        elect_cr();
        optiont(femail,password);
        break;

    case 6:
        searchstd();
        optiont(femail,password);
        break;

    case 7:
        scrolltext("\n\t\tLogging out");
        for(int i=0; i<3; i++)
        {
            printf(".");
            Sleep(500);
        }
        login();
        break;

    default:
        scrolltext("\n\n\t\t---Invalid choice---\n\n");
        Sleep(1000);
        optiont(femail,password);
    }
}

int cgpcal()
{
    int n;
    printf("Enter the number of semesters: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid input! Please enter a positive number of semesters.\n");
        return 1;
    }

    float *gpas = (float *)malloc(n * sizeof(float));
    if (gpas == NULL)
    {
        printf("Memory allocation failed!\n");
        return 1;
    }

    float sum = 0;

    for (int i = 0; i < n; i++)
    {
        printf("Enter GPA for semester %d: ", i + 1);
        scanf("%f", &gpas[i]);
        if (gpas[i] < 0 || gpas[i] > 4.0)
        {
            printf("Invalid GPA! Please enter a value between 0.0 and 4.0.\n");
            free(gpas);
            return 1;
        }
        sum += gpas[i];
    }

    float cgpa = sum / n;
    printf("Your CGPA is: %.2f\n", cgpa);
    free(gpas);

    return 0;
}

typedef struct
{
    char name[50];
    int votes;
} candidate;

candidate candidates[MAX];
int candidates_count;


int elect_cr()
{
    system("cls");
    printf("\t\t\t---CR Election---");
    printf("\n\nEnter the number of candidates (max %d): ", MAX);
    scanf("%d", &candidates_count);
    getchar();
    if (candidates_count <= 1 || candidates_count > MAX)
    {
        printf("\t\tInvalid number of candidates. Maximum is %d.\n", MAX);
        system("pause");
        return 1;
    }

    for (int i = 0; i < candidates_count; i++)
    {
        printf("Enter name/symbol for candidate %d: ", i + 1);
        scanf("%s", candidates[i].name);
        candidates[i].votes = 0;
    }

    while (1)
    {
        int voters_count;
        printf("\nEnter the number of voters: ");
        scanf("%d", &voters_count);
        getchar();
        printf("\n\n");
        for (int i = 0; i < voters_count; i++)
        {
            char name[50];
            printf("\tVote %d: ", i + 1);
            fflush(stdout);
            takeinput(name);
            printf("\033[F");//get back cursor to the previous line
            printf("\033[K");//clear the line
            if (!vote(name))
            {
                scrolltext("Invalid vote.");
                i--;
            }
        }

        int most_votes = 0;
        for (int i = 0; i < candidates_count; i++)
        {
            if (candidates[i].votes > most_votes)
            {
                most_votes = candidates[i].votes;
            }
        }

        if (check_tie(most_votes))
        {
            printf("\nThere is a tie. A re-election is required among the tied candidates.\n");
            reset_votes();
        }
        else
        {
            print_winner();
            break;
        }
    }

    system("pause");
    return 0;
}

bool vote(char name[])
{
    for (int i = 0; i < candidates_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}


void print_winner(void)
{
    int most_votes = 0;

    for (int i = 0; i < candidates_count; i++)
    {
        if (candidates[i].votes > most_votes)
        {
            most_votes = candidates[i].votes;
        }
    }

    for (int i = 0; i < candidates_count; i++)
    {
        if (candidates[i].votes == most_votes)
        {
            printf("\n\THE CR IS : %s\n", candidates[i].name);
        }
    }
}

bool check_tie(int most_votes)
{
    int tie_count = 0;
    for (int i = 0; i < candidates_count; i++)
    {
        if (candidates[i].votes == most_votes)
        {
            tie_count++;
        }
    }
    return tie_count > 1;
}

void reset_votes(void)
{
    for (int i = 0; i < candidates_count; i++)
    {
        candidates[i].votes = 0;
    }
}


int searchstd()
{
    printf("\n\t\tEnter the ID of the student : ");
    char roll[10];
    gets(roll);
    system("cls");
    printf("\t\t\t---Information of ID %s---\n\n", roll);

    fp = fopen("stdinfo.txt", "r");
    if (fp == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    int found = 0;
    while (fread(&s, sizeof(user), 1, fp) != NULL)
    {
        if (strcmp(s.roll, roll) == 0)
        {
            printf("\t\tName: %s\n\t\tEmail: %s\n\t\tPhone: %s\n\t\tRoll: %s\n", s.name, s.email, s.phone, s.roll);
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found)
    {
        printf("\n\t\tNo student found with ID %s\n", roll);
        system("pause");
        return 1;
    }

    printf("\n\t\t\tResult in 1-1 of %s\n\n", s.roll);
    fp = fopen("gpa.txt", "r");
    if (fp == NULL)
    {
        perror("Error opening file");
        return 1;
    }
    char id[8];
    float gp[8], gpa;
    found = 0;
    while (fscanf(fp, "%s %f %f %f %f %f %f %f %f %f",
                  id, &gp[0], &gp[1], &gp[2], &gp[3],
                  &gp[4], &gp[5], &gp[6], &gp[7], &gpa) != EOF)
    {
        if (strcmp(s.roll, id) == 0)
        {
            printf("\t\tCSE  1101 : %.2f\n", gp[0]);
            printf("\t\tCSE  1102 : %.2f\n", gp[1]);
            printf("\t\tCSE  1107 : %.2f\n", gp[2]);
            printf("\t\tPHY  1107 : %.2f\n", gp[3]);
            printf("\t\tPHY  1108 : %.2f\n", gp[4]);
            printf("\t\tMATH 1107 : %.2f\n", gp[5]);
            printf("\t\tHUM  1107 : %.2f\n", gp[6]);
            printf("\t\tHUM  1108 : %.2f\n\n", gp[7]);
            printf("\t\tGPA       : %.2f\n", gpa);
            found = 1;
            break;
        }
    }
    fclose(fp);
    if (found == 0)
    {
        printf("\n\t\tError : Result not found\n");
    }
    system("pause");
    return 0;
}

int edittcrinfo(char *femail, char *password)
{
    FILE *ft = fopen("temp.txt", "w");
    fp = fopen("teacherinfo.txt", "r");
    if (fp == NULL || ft == NULL)
    {
        perror("Error opening files");
        return -1;
    }
    while (fread(&t, sizeof(user), 1, fp) == 1)
    {
        if (strcmp(femail, t.email) != 0)
        {
            fwrite(&t, sizeof(user), 1, ft);
        }
        else
        {
            system("color 70");
            system("cls");
            scrolltext("\t\t\t---Information Editing---\n");
            printf("\n\t\tEnter your name: \t");
            takeinput(t.name);
            strcpy(femail,t.email);
            printf("\t\tEnter your number: \t");
            takeinput(t.phone);
            printf("\t\tEnter your password: \t");
            takepassword(t.password);

            if (strcmp(password, t.password) == 0)
            {
                fwrite(&t, sizeof(user), 1, ft);
                fclose(fp);
                fclose(ft);
                scrolltext("\033[1;32m\t\tSuccessfully updated...\n\033[0m\n");
            }
            else
            {
                fclose(fp);
                fclose(ft);
                scrolltext("\033[1;31m\n\t\tWrong Password.\n\033[0m\n");
                Beep(823, 500);
                Sleep(1000);
                login();
                return -1;
            }
        }
    }
    fclose(fp);
    fclose(ft);
    fp = fopen("teacherinfo.txt", "w");
    ft = fopen("temp.txt", "r");

    if (fp == NULL || ft == NULL)
    {
        perror("Error opening file");
        return -1;
    }

    while (fread(&t, sizeof(user), 1, ft) == 1)
    {
        fwrite(&t, sizeof(user), 1, fp);
    }
    fclose(fp);
    fclose(ft);
    system("pause");
    return 0;
}

int editstdinfo(char *fid, char *password)
{
    FILE *ft = fopen("temp.txt", "w");
    fp = fopen("stdinfo.txt", "r");

    if (fp == NULL || ft == NULL)
    {
        perror("Error opening files");
        return -1;
    }
    while (fread(&s, sizeof(user), 1, fp) == 1)
    {
        if (strcmp(fid, s.roll) != 0)
        {
            fwrite(&s, sizeof(user), 1, ft);
        }
        else
        {
            system("color 70");
            system("cls");
            scrolltext("\t\t\t---Information Editing---\n");
            printf("\n\t\tEnter your name: \t");
            takeinput(s.name);
            printf("\t\tEnter your email: \t");
            takeinput(s.email);
            printf("\t\tEnter your number: \t");
            takeinput(s.phone);
            strcpy(s.roll, fid);
            printf("\t\tEnter your password: \t");
            takepassword(s.password);

            if (strcmp(password, s.password) == 0)
            {
                fwrite(&s, sizeof(user), 1, ft);
                fclose(fp);
                fclose(ft);
                scrolltext("\033[1;32m\t\tSuccessfully updated...\n\033[0m\n");
            }
            else
            {
                fclose(fp);
                fclose(ft);
                scrolltext("\033[1;31m\n\t\tWrong Password.\n\033[0m\n");
                Beep(800, 500);
                Sleep(500);
                login();
                return -1;
            }
        }
    }
    fclose(fp);
    fclose(ft);
    fp = fopen("stdinfo.txt", "w");
    ft = fopen("temp.txt", "r");

    if (fp == NULL || ft == NULL)
    {
        perror("Error opening file");
        return -1;
    }

    while (fread(&s, sizeof(user), 1, ft) == 1)
    {
        fwrite(&s, sizeof(user), 1, fp);
    }
    fclose(fp);
    fclose(ft);
    system("pause");
    return 0;
}

int dlt(char *fid, char *password)
{
    FILE *ft = fopen("temp.txt", "w");
    fp = fopen("stdinfo.txt", "r");

    if (fp == NULL || ft == NULL)
    {
        perror("Error opening file");
        return -1;
    }
    printf("\tEnter your password : ");
    takepassword(s.password);
    if(strcmp(s.password,password) != 0)
    {
        fclose(fp);
        fclose(ft);
        scrolltext("\033[1;31m\n\t\tWrong Password.\n\033[0m\n");
        Beep(823, 500);
        Sleep(1000);
        login();
        return -1;
    }
    while (fread(&s, sizeof(user), 1, fp) != NULL)
    {
        if (strcmp(fid, s.roll) != 0)
        {
            fwrite(&s, sizeof(user), 1, ft);
        }
    }
    fclose(fp);
    fclose(ft);
    fp = fopen("stdinfo.txt", "w");
    ft = fopen("temp.txt", "r");

    if (fp == NULL || ft == NULL)
    {
        perror("Error opening file");
        return -1;
    }

    while (fread(&s, sizeof(user), 1, ft) == 1)
    {
        fwrite(&s, sizeof(user), 1, fp);
    }
    fclose(fp);
    fclose(ft);
    scrolltext("\tSuccessfully deleted.\n\n");
    system("pause");
    return 0;
}

int course_reg(char *fid)
{
    system("cls");
    system("color 70");
    char sem[8], fsem[8];
    printf("\t\tCourse Registration for ID : %s\n\n", fid);
    printf("Enter the semester (Example: CSE 1-1): ");
    takeinput(sem);


    char check[20];
    int j=0;
    for(int i=0; i<strlen(fid); i++)
    {
        check[j++]=fid[i];
    }
    check[j++]=' ';
    for(int i=0; i<strlen(sem); i++)
    {
        check[j++]=sem[i];
    }
    check[j++]='\n';
    check[j]='\0';

    fp=fopen("reginfo.txt","r");//checking if it is already registered or not
    char fcheck[20];
    while (fgets(fcheck,sizeof(fcheck),fp) != NULL)
    {
        if (strcmp(check,fcheck)==0)
        {
            scrolltext("\n\t\tYou are already registered for this semester.\n");
            system("pause");
            fclose(fp);
            return 0;
        }
    }
    fclose(fp);
    fp = fopen("semester.txt", "r");
    while (fgets(fsem, sizeof(fsem), fp) != NULL)
    {
        fsem[strcspn(fsem, "\n")] = '\0';
        if (strcmp(sem, fsem) == 0)
        {
            fclose(fp);
            fp = fopen("reginfo.txt","a");
            fprintf(fp,"%s %s\n",fid,sem);
            fclose(fp);
            printf("\n\t\tID %s is registered for %s\n", fid, fsem);
            system("pause");
            fclose(fp);
            return 0;
        }
    }
    fclose(fp);
    scrolltext("\n\t\tSomething went wrong\n");
    system("pause");

    return 0;
}
