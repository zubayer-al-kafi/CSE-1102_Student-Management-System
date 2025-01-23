#include "header.h"
#define MAX 9

FILE *fp;
int options(char *fid, char *password)
{
    system("color 0B");
    system("cls");
    int opt;
    printf("\t\t1. View your information\n\t\t2. Edit your information\n\t\t3. Delete your account\n");
    printf("\t\t4. Course Registration\n\t\t5. Logout\n");
    scrolltext("\n\t\tEnter your choice: ");
    scanf("%d", &opt);
    getchar();
    switch (opt)
    {
    case 1:
        printf("\t\t\t---Your information---\n");
        fp = fopen("stdinfo.txt", "r");
        while (fread(&s,sizeof(user),1,fp) != NULL)
        {
            if (strcmp(fid,s.roll) == 0)
            {
                fclose(fp);
                printf("\t\tName: %s\n\t\tEmail: %s\n\t\tPhone: %s\n\t\tRoll: %s\n", s.name, s.email, s.phone, s.roll);
                printf("\n\t\tPress any key to continue...");
                getchar();
                options(fid,password);
            }
        }
        fclose(fp);
        options(fid,password);
        break;
    case 2:
        editstdinfo(fid,password);
        options(fid,password);
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
    system("color 0B");
    system("cls");
    int opt;
    printf("\t\t1. View your information\n\t\t2. Edit your information\n\t\t3. Calculate GPA\n");
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
        printf("\n\t\tPress any key to continue...");
        getchar();
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
        Sleep(2000);
        optiont(femail,password);
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
            scrolltext("Invalid input\n");
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
        scrolltext("Please give input carefully.\n");
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
    scrolltext("Enter the number of semesters : ");
    scanf("%d", &n);
    getchar();
    system("cls");
    printf("\t\t\tCGPA Calculator\n\n");
    float gp[n];
    for (int i = 0; i < n; i++)
    {
        scanf("\t\tGPA of semester %d : %f",i+1, &gp[i]);
        getchar();
    }
    float sum = 0;
    for (int i = 0; i < n; i++)
        sum += gp[i];
    printf("The CGPA is : %.2f\n", sum / n);
    printf("\n\t\tPress any key to continue...");
    getchar();
    return 0;
}


int course_reg(char *fid)
{
    system("cls");
    system("color 0B");
    char sem[8], fsem[8];
    printf("\t\tCourse Registration for ID : %s\n\n", fid);
    printf("Enter the semester (Example: CSE 1-1): ");
    fgets(sem, sizeof(sem), stdin);
    sem[strcspn(sem, "\n")] = 0; // Remove the newline character
    getchar();

    //now add id and sem with a space between them
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

    fp=fopen("reginfo.txt","r");//check if it is already registered or not
    char fcheck[20];
    while (fgets(fcheck,sizeof(fcheck),fp) != NULL)
    {
        if (strcmp(check,fcheck)==0)
        {
            scrolltext("\n\t\tYou are already registered for this semester.\n");
            printf("\n\t\tPress any key to continue...");
            getchar();
            fclose(fp);
            return 0;
        }

    }
    fclose(fp);

    fp = fopen("semester.txt", "r");
    while (fgets(fsem, sizeof(fsem), fp) != NULL)
    {
        fsem[strcspn(fsem, "\n")] = 0; // Remove the newline character
        if (strcmp(sem, fsem) == 0)
        {
            fclose(fp);
            fp = fopen("reginfo.txt","a");
            fprintf(fp,"%s %s\n",fid,sem);
            fclose(fp);
            printf("\n\t\tID %s is registered for %s\n", fid, fsem);
            printf("\n\t\tPress any key to continue...");
            getchar();
            fclose(fp);
            return 0;
        }
    }
    fclose(fp);
    scrolltext("\n\t\tSomething went wrong\n");
    printf("\n\t\tPress any key to continue...");
    getchar();

    return 0;
}


typedef struct
{
    char name[50];
    int votes;
} candidate;

candidate candidates[MAX];
int candidates_count;

bool vote(char name[]);
void print_winner(void);
bool check_tie(int most_votes);
void reset_votes(void);

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
        printf("\n\t\tPress any key to continue...");
        getchar();
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

        // Determine the highest votes
        int most_votes = 0;
        for (int i = 0; i < candidates_count; i++)
        {
            if (candidates[i].votes > most_votes)
            {
                most_votes = candidates[i].votes;
            }
        }

        // Check if there is a tie
        if (check_tie(most_votes))
        {
            printf("\nThere is a tie. A re-election is required among the tied candidates.\n");

            // Retain only the tied candidates and reset their votes
            reset_votes();
        }
        else
        {
            // Print the winner(s) and exit the loop
            print_winner();
            break;
        }
    }

    // Wait for user input to keep the console open
    printf("\nPress any key to continue...");
    getchar();
    return 0;
}

// Update vote totals given a new vote
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

// Print the winner(s) of the election
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

// Check if there is a tie among candidates with the highest votes
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

    // A tie occurs if more than one candidate has the highest votes
    return tie_count > 1;
}

// Reset the votes of all candidates for a re-election
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
    printf("\t\t\t---Information of ID %s---\n\n",roll);
    fp = fopen("stdinfo.txt", "r");
    while (fread(&s,sizeof(user),1,fp) != NULL)
    {
        if (strcmp(s.roll, roll) == 0)
        {
            printf("\t\tName: %s\n\t\tEmail: %s\n\t\tPhone: %s\n\t\tRoll: %s\n", s.name, s.email, s.phone, s.roll);
            printf("\n\nPress any key to continue...");
            getchar();
            return 0;
        }
    }
    printf("\t\tSorry, there is no student with this ID.");
    printf("\n\nPress any key to continue...");
    getchar();
    return 0;
}

int edittcrinfo(char *femail, char *password)
{
    FILE *ft = fopen("temp.txt", "w");
    fp = fopen("teacherinfo.txt", "r");
    if (!fp || !ft)
    {
        printf("Error opening files.\n");
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
            system("color 0B");
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

    if (!fp || !ft)
    {
        printf("Error opening files for final write-back.\n");
        return -1;
    }

    while (fread(&t, sizeof(user), 1, ft) == 1)
    {
        fwrite(&t, sizeof(user), 1, fp);
    }
    fclose(fp);
    fclose(ft);
    printf("Press any key to continue...");
    getchar();
    return 0;
}

int editstdinfo(char *fid, char *password)
{
    FILE *ft = fopen("temp.txt", "w");
    fp = fopen("stdinfo.txt", "r");

    if (!fp || !ft)
    {
        printf("Error opening files.\n");
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
            system("color 0B");
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
                Beep(823, 500);
                Sleep(1000);
                login();
                return -1;
            }
        }
    }
    fclose(fp);
    fclose(ft);
    fp = fopen("stdinfo.txt", "w");
    ft = fopen("temp.txt", "r");

    if (!fp || !ft)
    {
        printf("Error opening files for final write-back.\n");
        return -1;
    }

    while (fread(&s, sizeof(user), 1, ft) == 1)
    {
        fwrite(&s, sizeof(user), 1, fp);
    }
    fclose(fp);
    fclose(ft);
    printf("Press any key to continue...");
    getchar();
    return 0;
}

int dlt(char *fid, char *password)
{
    FILE *ft = fopen("temp.txt", "w");
    fp = fopen("stdinfo.txt", "r");

    if (!fp || !ft)
    {
        printf("Error opening files.\n");
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
    while (fread(&s, sizeof(user), 1, fp) == 1)
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

    if (!fp || !ft)
    {
        printf("Error opening files for final write-back.\n");
        return -1;
    }

    while (fread(&s, sizeof(user), 1, ft) == 1)
    {
        fwrite(&s, sizeof(user), 1, fp);
    }
    fclose(fp);
    fclose(ft);
    scrolltext("\tSuccessfully deleted.\n\n");
    printf("Press any key to continue...");
    getchar();
    return 0;
}
