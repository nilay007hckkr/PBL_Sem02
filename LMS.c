#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void Type_01();
void Type_02();
void Type_03();
void Type_04();
void showMenu();
void printLine();
void showWelcome();
void showProcessing();

float emi,total,principal,newprincipal;
float rateinterest,processfee,cardfee,dailyavg,amtspent;

int months,collegemonths;

void Type_01()
{
    printf("Enter Principal Amount, Total Months, Rate of Interest(%%), Processing Fee:\n");

    scanf("%f%d%f%f",
          &principal,
          &months,
          &rateinterest,
          &processfee);

    rateinterest = rateinterest/(12*100);

    emi = principal *
         ((rateinterest*pow((1+rateinterest),months))/
         (pow((1+rateinterest),months)-1));

    total = emi*months + processfee;

    printf("EMI per month: Rs %.2f\n",emi);
    printf("Total Amount to be repaid: Rs %.2f\n",total);

    printLine();
}

void Type_02()
{
    printf("Enter Principal Amount, Repayment Months, Course Months, Interest Rate(%%), Processing Fee:\n");

    scanf("%f%d%d%f%f",
          &principal,
          &months,
          &collegemonths,
          &rateinterest,
          &processfee);

    rateinterest = rateinterest/100;

    newprincipal =
    principal +
    (principal*rateinterest*collegemonths/12);

    rateinterest = rateinterest/12;

    emi = newprincipal*
         ((rateinterest*pow((1+rateinterest),months))/
         (pow((1+rateinterest),months)-1));

    total=(emi*months)+processfee;

    printf("EMI per month: Rs %.2f\n",emi);
    printf("Total Amount to be repaid: Rs %.2f\n",total);

    printLine();
}

void Type_03()
{
    printf("Enter Principal Amount, Total Months, Interest Rate(%%), Processing Fee:\n");

    scanf("%f%d%f%f",
          &principal,
          &months,
          &rateinterest,
          &processfee);

    total = principal +
            (principal*months*rateinterest)
            /(100*12.0)
            + processfee;

    printf("Total Amount to be repaid: Rs %.2f\n",total);

    printLine();
}

void Type_04()
{
    printf("Enter Amount Spent, Average Daily Balance, Interest Rate(%%), Card Fee:\n");

    scanf("%f%f%f%f",
          &amtspent,
          &dailyavg,
          &rateinterest,
          &cardfee);

    total =
    amtspent+
    (dailyavg*rateinterest)/100
    +cardfee;

    printf("Total Amount to be repaid: Rs %.2f\n",total);

    printLine();
}

void printLine()
{
    printf("====================================\n");
}

void showWelcome()
{
    printf("\n");

    printLine();

    printf("      WELCOME TO\n");
    printf("      LOAN CALCULATOR\n");

    printLine();

    printf("Simple | Fast | Reliable\n");

    printLine();

    printf("Press ENTER to continue");

    getchar();
    getchar();

    system("cls");
}

void showProcessing()
{
    int i;

    printf("\nProcessing");
    fflush(stdout);

    for(i=0;i<7;i++)
    {
        long wait;

        for(wait=0;wait<50000000;wait++);

        printf(".");
        fflush(stdout);
    }

    printf("\n");
}

void showMenu()
{
    printLine();

    printf("TYPES OF LOANS\n");

    printLine();

    printf("1. Personal Loan\n");
    printf("2. Vehicle Loan\n");
    printf("3. Home Loan\n");
    printf("4. Business Loan\n");
    printf("5. Industrial Loan\n");
    printf("6. Educational Loan\n");
    printf("7. Gold Loan\n");
    printf("8. Agriculture Loan\n");
    printf("9. Credit Loan\n");

    printLine();

    printf("Enter Choice: ");
}

int main()
{
    int choice;

    showWelcome();

    showMenu();

    scanf("%d",&choice);

    showProcessing();

    if(choice>0 && choice<6)
        Type_01();

    else if(choice==6)
        Type_02();

    else if(choice==7 || choice==8)
        Type_03();

    else if(choice==9)
        Type_04();

    else
    {
        printf("INVALID CHOICE\n");
        printLine();
    }

    return 0;
}