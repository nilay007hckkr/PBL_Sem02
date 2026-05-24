#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

void calculateStandardLoan(float interestRate, float processFeeRate);
void calculateEducationLoan(float interestRate, float processFeeRate);
void calculateSimpleInterestLoan(float interestRate, float processFeeRate);
void calculateCreditCardLoan(float interestRate, float cardFeeRate);
void showMenu();
void printLine();
void showWelcome();
void showProcessing();
void clearScreen();
void waitMilliseconds(int ms);

typedef struct {
    char name[30];
    float interestRate;
    float feeRate;
} LoanType;

LoanType loans[9] = {
    {"Personal Loan",     14.0f,  2.0f},
    {"Vehicle Loan",      10.0f,  1.0f},
    {"Home Loan",          8.5f,  0.5f},
    {"Business Loan",     15.0f,  2.0f},
    {"Industrial Loan",   12.0f,  1.5f},
    {"Educational Loan",  10.0f,  0.5f},
    {"Gold Loan",          9.0f,  0.5f},
    {"Agriculture Loan",   7.0f,  0.5f},
    {"Credit Card Loan",  30.0f,  2.5f}
};

void clearScreen()
{
    #ifdef _WIN32
        system("cls");
    #else
        printf("\033[2J\033[H");
    #endif
}

void waitMilliseconds(int ms)
{
    #ifdef _WIN32
        Sleep(ms);
    #else
        usleep(ms * 1000);
    #endif
}

void calculateStandardLoan(float interestRate, float processFeeRate)
{
    float principal, processFee, emi, total, rateInterest;
    int months;

    printf("Enter Principal Amount and Total Months:\n");
    printf("> ");

    if (scanf("%f %d", &principal, &months) != 2
        || principal <= 0 || months <= 0)
    {
        printf("Invalid input. Please enter positive values.\n");
        printLine();
        return;
    }

    processFee  = principal * processFeeRate / 100;
    rateInterest = interestRate / (12 * 100);

    emi = principal *
          ((rateInterest * pow((1 + rateInterest), months)) /
           (pow((1 + rateInterest), months) - 1));

    total = (emi * months) + processFee;

    printf("\nInterest Rate     : %.1f%%\n", interestRate);
    printf("Processing Fee    : Rs %.2f (%.1f%%)\n", processFee, processFeeRate);
    printf("EMI per month     : Rs %.2f\n", emi);
    printf("Total to be repaid: Rs %.2f\n", total);

    printLine();
}

void calculateEducationLoan(float interestRate, float processFeeRate)
{
    float principal, processFee, newPrincipal, emi, total, rateInterest;
    int repayMonths, courseMonths;

    printf("Enter Principal Amount, Repayment Months, Course Months:\n");
    printf("> ");

    if (scanf("%f %d %d", &principal, &repayMonths, &courseMonths) != 3
        || principal <= 0 || repayMonths <= 0 || courseMonths <= 0)
    {
        printf("Invalid input. Please enter positive values.\n");
        printLine();
        return;
    }

    processFee   = principal * processFeeRate / 100;
    rateInterest = interestRate / 100;

    newPrincipal = principal + (principal * rateInterest * courseMonths / 12);

    rateInterest = rateInterest / 12;

    emi = newPrincipal *
          ((rateInterest * pow((1 + rateInterest), repayMonths)) /
           (pow((1 + rateInterest), repayMonths) - 1));

    total = (emi * repayMonths) + processFee;

    printf("\nInterest Rate     : %.1f%%\n", interestRate);
    printf("Processing Fee    : Rs %.2f (%.1f%%)\n", processFee, processFeeRate);
    printf("EMI per month     : Rs %.2f\n", emi);
    printf("Total to be repaid: Rs %.2f\n", total);

    printLine();
}

void calculateSimpleInterestLoan(float interestRate, float processFeeRate)
{
    float principal, processFee, total;
    int months;

    printf("Enter Principal Amount and Total Months:\n");
    printf("> ");

    if (scanf("%f %d", &principal, &months) != 2
        || principal <= 0 || months <= 0)
    {
        printf("Invalid input. Please enter positive values.\n");
        printLine();
        return;
    }

    processFee = principal * processFeeRate / 100;

    total = principal +
            (principal * months * interestRate) / (100 * 12.0) +
            processFee;

    printf("\nInterest Rate     : %.1f%%\n", interestRate);
    printf("Processing Fee    : Rs %.2f (%.1f%%)\n", processFee, processFeeRate);
    printf("Total to be repaid: Rs %.2f\n", total);

    printLine();
}

void calculateCreditCardLoan(float interestRate, float cardFeeRate)
{
    float amountSpent, dailyAvgBalance, cardFee, total;

    printf("Enter Amount Spent and Average Daily Balance:\n");
    printf("> ");

    if (scanf("%f %f", &amountSpent, &dailyAvgBalance) != 2
        || amountSpent < 0 || dailyAvgBalance < 0)
    {
        printf("Invalid input. Please enter non-negative values.\n");
        printLine();
        return;
    }

    cardFee = amountSpent * cardFeeRate / 100;

    total = amountSpent + (dailyAvgBalance * interestRate) / 100 + cardFee;

    printf("\nInterest Rate     : %.1f%%\n", interestRate);
    printf("Card Fee          : Rs %.2f (%.1f%%)\n", cardFee, cardFeeRate);
    printf("Total to be repaid: Rs %.2f\n", total);

    printLine();
}

void printLine()
{
    printf("============================================\n");
}

void showWelcome()
{
    printf("\n");
    printLine();
    printf("           LOAN CALCULATOR\n");
    printf("      Simple | Fast | Reliable\n");
    printLine();
    printf("Press ENTER to continue...");

    getchar();

    clearScreen();
}

void showProcessing()
{
    int i;
    printf("\nProcessing");
    fflush(stdout);

    for (i = 0; i < 5; i++)
    {
        waitMilliseconds(300);
        printf(".");
        fflush(stdout);
    }

    printf("\n\n");
}

void showMenu()
{
    int i;

    printLine();
    printf("           TYPES OF LOANS\n");
    printLine();

    for (i = 0; i < 9; i++)
    {
        printf("  %d. %-20s %5.1f%% | Fee: %4.1f%%\n",
               i + 1,
               loans[i].name,
               loans[i].interestRate,
               loans[i].feeRate);
    }

    printf("  0. Exit\n");
    printLine();
    printf("Enter Choice: ");
}

int main()
{
    int choice;

    showWelcome();

    while (1)
    {
        showMenu();

        if (scanf("%d", &choice) != 1)
        {
            printf("Please enter a valid number.\n");
            while (getchar() != '\n');
            continue;
        }

        if (choice == 0)
        {
            printf("\nThank you for using Loan Calculator. Goodbye!\n");
            printLine();
            break;
        }

        if (choice < 1 || choice > 9)
        {
            printf("Invalid choice. Please enter a number between 0 and 9.\n");
            printLine();
            continue;
        }

        printf("\n--- %s ---\n", loans[choice - 1].name);

        showProcessing();

        if (choice >= 1 && choice <= 5)
            calculateStandardLoan(loans[choice - 1].interestRate, loans[choice - 1].feeRate);

        else if (choice == 6)
            calculateEducationLoan(loans[choice - 1].interestRate, loans[choice - 1].feeRate);

        else if (choice == 7 || choice == 8)
            calculateSimpleInterestLoan(loans[choice - 1].interestRate, loans[choice - 1].feeRate);

        else if (choice == 9)
            calculateCreditCardLoan(loans[choice - 1].interestRate, loans[choice - 1].feeRate);
    }

    return 0;
}