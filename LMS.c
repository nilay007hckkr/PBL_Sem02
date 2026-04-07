#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void printLine()
{
    printf("  ======================================\n");
}

void showWelcome()
{
    printf("\n\n");
    printLine();
    printf("  ||                                  ||\n");
    printf("  ||           WELCOME TO             ||\n");
    printf("  ||      LOAN MANAGEMENT SYSTEM      ||\n");
    printf("  ||                                  ||\n");
    printLine();
    printf("\n");
    printf("    Simple | Fast | Reliable\n");
    printf("\n");
    printLine();
    printf("\n  Press ENTER to continue . . .");

    getchar();

    system("Cls");
}

void showProcessing()
{
    int i;

    printf("\n  Processing");
    fflush(stdout);

    for (i = 0; i < 7; i++)
    {
        long wait;
        for (wait = 0; wait < 500000000; wait++)
            ;

        printf(".");
        fflush(stdout);
    }
}

void showMenu()
{
    printf("\n\n");
    printLine();
    printf("  ||                                  ||\n");
    printf("  ||     TYPES OF LOANS AVAILABLE     ||\n");
    printf("  ||                                  ||\n");
    printLine();
    printf("\n");
    printf("    [ 1 ]  Personal Loan\n");
    printf("    [ 2 ]  Education Loan\n");
    printf("    [ 3 ]  Home Loan\n");
    printf("    [ 4 ]  Vehicle Loan\n");
    printf("    [ 5 ]  Gold Loan\n");
    printf("    [ 6 ]  Business Loan\n");
    printf("    [ 7 ]  Industrial Loan\n");
    printf("    [ 8 ]  Agriculture Loan\n");
    printf("    [ 9 ]  Others\n");
    printf("\n");
    printLine();
    printf("\n  Enter Your Choice : ");
}

int main()
{
    int choice;

    showWelcome();
    showMenu();

    scanf("%d", &choice);

    showProcessing();

    printf("\n");
    printLine();
    printf("\n  You selected option [ %d ]\n\n", choice);
    printLine();

    return 0;
}