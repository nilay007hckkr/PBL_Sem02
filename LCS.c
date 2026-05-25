#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#else
    #include <unistd.h>
    #include <termios.h>
#endif

#define KEY_ENTER 13
#define KEY_ESC   27

int calculateStandardLoan(float interestRate, float processFeeRate);
int calculateEducationLoan(float interestRate, float processFeeRate);
int calculateSimpleInterestLoan(float interestRate, float processFeeRate);
int calculateCreditCardLoan(float interestRate, float cardFeeRate);
void showMenu();
void printLine();
void showWelcome();
void showProcessing();
void clearScreen();
void waitMilliseconds(int ms);
int  getKeyPress();
int  waitForChoice();
void flushInput();

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

void flushInput()
{
    while (getchar() != '\n');
}

int getKeyPress()
{
    #ifdef _WIN32
        return _getch();
    #else
        int ch;
        struct termios oldt, newt;

        tcgetattr(0, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(0, TCSANOW, &newt);

        ch = getchar();

        tcsetattr(0, TCSANOW, &oldt);
        return ch;
    #endif
}

int waitForChoice()
{
    int key;

    printf("Press ENTER for another option or ESC to close: ");
    fflush(stdout);

    while (1)
    {
        key = getKeyPress();

        if (key == KEY_ENTER || key == '\n')
            return 1;

        if (key == KEY_ESC)
            return 0;
    }
}

int calculateStandardLoan(float interestRate, float processFeeRate)
{
    float principal, processFee, emi, total, rateInterest;
    int months, tries = 0;

    while (tries < 3)
    {
        printf("Enter Principal Amount and Total Months:\n");
        printf("> ");

        if (scanf("%f %d", &principal, &months) == 2
            && principal > 0 && months > 0)
            break;

        flushInput();
        tries++;

        if (tries < 3)
            printf("Invalid input. Principal and months must be positive. Try again. (%d/3)\n\n", tries);
    }

    if (tries == 3)
    {
        printf("\nToo many invalid attempts.\n");
        printLine();
        return waitForChoice();
    }

    processFee   = principal * processFeeRate / 100;
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
    return -1;
}

int calculateEducationLoan(float interestRate, float processFeeRate)
{
    float principal, processFee, newPrincipal, emi, total, rateInterest;
    int repayMonths, courseMonths, tries = 0;

    while (tries < 3)
    {
        printf("Enter Principal Amount, Repayment Months, Course Months:\n");
        printf("> ");

        if (scanf("%f %d %d", &principal, &repayMonths, &courseMonths) == 3
            && principal > 0 && repayMonths > 0 && courseMonths > 0)
            break;

        flushInput();
        tries++;

        if (tries < 3)
            printf("Invalid input. All values must be positive. Try again. (%d/3)\n\n", tries);
    }

    if (tries == 3)
    {
        printf("\nToo many invalid attempts.\n");
        printLine();
        return waitForChoice();
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
    return -1;
}

int calculateSimpleInterestLoan(float interestRate, float processFeeRate)
{
    float principal, processFee, total;
    int months, tries = 0;

    while (tries < 3)
    {
        printf("Enter Principal Amount and Total Months:\n");
        printf("> ");

        if (scanf("%f %d", &principal, &months) == 2
            && principal > 0 && months > 0)
            break;

        flushInput();
        tries++;

        if (tries < 3)
            printf("Invalid input. Principal and months must be positive. Try again. (%d/3)\n\n", tries);
    }

    if (tries == 3)
    {
        printf("\nToo many invalid attempts.\n");
        printLine();
        return waitForChoice();
    }

    processFee = principal * processFeeRate / 100;

    total = principal +
            (principal * months * interestRate) / (100 * 12.0) +
            processFee;

    printf("\nInterest Rate     : %.1f%%\n", interestRate);
    printf("Processing Fee    : Rs %.2f (%.1f%%)\n", processFee, processFeeRate);
    printf("Total to be repaid: Rs %.2f\n", total);

    printLine();
    return -1;
}

int calculateCreditCardLoan(float interestRate, float cardFeeRate)
{
    float amountSpent, dailyAvgBalance, cardFee, total;
    int tries = 0;

    while (tries < 3)
    {
        printf("Enter Amount Spent and Average Daily Balance:\n");
        printf("> ");

        if (scanf("%f %f", &amountSpent, &dailyAvgBalance) == 2
            && amountSpent >= 0 && dailyAvgBalance >= 0)
            break;

        flushInput();
        tries++;

        if (tries < 3)
            printf("Invalid input. Values cannot be negative. Try again. (%d/3)\n\n", tries);
    }

    if (tries == 3)
    {
        printf("\nToo many invalid attempts.\n");
        printLine();
        return waitForChoice();
    }

    cardFee = amountSpent * cardFeeRate / 100;

    total = amountSpent + (dailyAvgBalance * interestRate) / 100 + cardFee;

    printf("\nInterest Rate     : %.1f%%\n", interestRate);
    printf("Card Fee          : Rs %.2f (%.1f%%)\n", cardFee, cardFeeRate);
    printf("Total to be repaid: Rs %.2f\n", total);

    printLine();
    return -1;
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
            flushInput();
            printf("Please enter a valid number.\n");
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
            continue;
        }

        printf("\n--- %s ---\n", loans[choice - 1].name);

        showProcessing();

        int result = -1;

        if (choice >= 1 && choice <= 5)
            result = calculateStandardLoan(loans[choice - 1].interestRate, loans[choice - 1].feeRate);

        else if (choice == 6)
            result = calculateEducationLoan(loans[choice - 1].interestRate, loans[choice - 1].feeRate);

        else if (choice == 7 || choice == 8)
            result = calculateSimpleInterestLoan(loans[choice - 1].interestRate, loans[choice - 1].feeRate);

        else if (choice == 9)
            result = calculateCreditCardLoan(loans[choice - 1].interestRate, loans[choice - 1].feeRate);

        if (result == 0)
        {
            printf("\n\nThank you for using Loan Calculator. Goodbye!\n");
            printLine();
            break;
        }

        if (result == 1)
        {
            clearScreen();
            continue;
        }

        flushInput();

        if (waitForChoice() == 0)
        {
            printf("\n\nThank you for using Loan Calculator. Goodbye!\n");
            printLine();
            break;
        }

        clearScreen();
    }

    return 0;
}
