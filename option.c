#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>
#include "option.h"
#include "reg.h"
#include "mystruct.h"
#define MAX 9
FILE *fp;
int options(char *fid)
{
    system("color 0B");
    system("cls");
    int opt;
    printf("\t\t1. View your information\n\t\t2. Edit your information\n\t\t3. Delete your account\n");
    printf("\t\t4. Course Registration\n\t\t5. Logout\n");
    printf("\n\t\tEnter your choice: ");
    scanf("%d", &opt);
    getchar();
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
        options(fid);
        break;
    case 2:
        options(fid);
        break;
    case 3:
        options(fid);
        break;
    case 4:
        course_reg(fid);
        options(fid);
        break;
    case 5:
        printf("\n\t\tLogging out");
        for(int i=0;i<3;i++)
        {
            printf(".");
            fflush(stdin);
            Sleep(500);
        }
        login();
        break;
    default:
        printf("\t\t---Invalid choice---");
        Sleep(1000);
        options(fid);
        return 0;
    }
}

int optiont(char *femail)
{
    system("color 0B");
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
        printf("\n\n");
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
        printf("\n\t\tPress any key to continue...");
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
    case 6:
        printf("\n\t\tLogging out");
        for(int i=0;i<3;i++)
        {
            printf(".");
            Sleep(500);
        }
        login();
        break;
    default:
        printf("\n\n\t\t---Invalid choice---\n\n");
        printf("\t\tPress any key to continue...");
        getchar();
        optiont(femail);
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
    for(int i=0;i<strlen(fid);i++)
    {
        check[j++]=fid[i];
    }
    check[j++]=' ';
    for(int i=0;i<strlen(sem);i++)
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
            printf("\n\t\tYou are already registered for this semester.\n");
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
    printf("\n\t\tSomething went wrong\n");
    printf("\n\t\tPress any key to continue...");
    getchar();

    return 0;
}


//creating structures
typedef struct
{
  char name[50];
  int votes;

} candidate;
candidate candidates[MAX]; //ekhane max holo 9
int candidates_count;
int argc; char *argv;
int elect_cr()
{ //check for argument count
    if (argc < 3){

        printf("Usage: Enter more candidates [candidate ...]\n ");
        return 1;

    }
 // check for max candidates
    candidates_count = argc - 1;
    if (candidates_count> MAX ){
        printf("Max of 9 candidate allowed\n");
        return 2;
    }
    // populate candidates
    for (int i=0;i< candidates_count;i++){
        strcpy(candidates[i].name,argv[i+1] );
        candidates[i].votes =0;
    }
    // get number of voters
    int voters_count;
    printf("Number of Voters:\n");
    scanf("%i", &voters_count);
    for (int i=0; i<voters_count;i++)
        { //get the vote
        char name[50];
        printf("Vote: ");
        scanf("%s",name);
     //validate the vote
        if (!vote(name))
            {
            printf("Invalid vote\n");
            }
    }
    // print winner
    print_winner();
return;
}

bool vote (char name[])
{
     for (int i=0;i< candidates_count;i++){
     //checking if there's match by candidate name
       if (strcmp(candidates[i].name,name)== 0){

        candidates[i].votes++; //increment votes
        return true;
       }
     }
     return false;
}
void print_winner(void)
{ // check for the most votes
    int most_votes;
       for (int i=0;i< candidates_count;i++)
        {
      if(candidates[i].votes > most_votes)
      {
          most_votes = candidates[i].votes;

      }

    }
    // check for the candidate with most votes
    for (int i=0;i< candidates_count;i++)
        {
      if(candidates[i].votes == most_votes)
      {
         printf("%s\n",candidates[i].name);

      }

    }


}
