#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    int accNo;
    char name[50];
    float balance;
};

void createAccount() {
    struct Account acc;
    FILE *fp = fopen("bank.txt", "a");

    printf("\nEnter Account Number: ");
    scanf("%d", &acc.accNo);
    printf("Enter Name: ");
    scanf(" %[^\n]", acc.name);
    printf("Enter Initial Balance: ");
    scanf("%f", &acc.balance);

    fwrite(&acc, sizeof(acc), 1, fp);
    fclose(fp);

    printf("\nAccount Created Successfully!\n");
}

void displayAccounts() {
    struct Account acc;
    FILE *fp = fopen("bank.txt", "r");

    if (fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    printf("\n--- Account Details ---\n");
    while (fread(&acc, sizeof(acc), 1, fp)) {
        printf("\nAccount No: %d", acc.accNo);
        printf("\nName: %s", acc.name);
        printf("\nBalance: %.2f\n", acc.balance);
    }

    fclose(fp);
}

void depositMoney() {
    struct Account acc;
    FILE *fp = fopen("bank.txt", "r+");
    int accNo;
    float amount;
    int found = 0;

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accNo == accNo) {
            printf("Enter amount to deposit: ");
            scanf("%f", &amount);

            acc.balance += amount;
            fseek(fp, -sizeof(acc), SEEK_CUR);
            fwrite(&acc, sizeof(acc), 1, fp);

            printf("Amount Deposited Successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Account not found!\n");

    fclose(fp);
}

void withdrawMoney() {
    struct Account acc;
    FILE *fp = fopen("bank.txt", "r+");
    int accNo;
    float amount;
    int found = 0;

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accNo == accNo) {
            printf("Enter amount to withdraw: ");
            scanf("%f", &amount);

            if (amount > acc.balance) {
                printf("Insufficient Balance!\n");
            } else {
                acc.balance -= amount;
                fseek(fp, -sizeof(acc), SEEK_CUR);
                fwrite(&acc, sizeof(acc), 1, fp);
                printf("Withdrawal Successful!\n");
            }

            found = 1;
            break;
        }
    }

    if (!found)
        printf("Account not found!\n");

    fclose(fp);
}

int main() {
    int choice;

    while (1) {
        printf("\n====== BANK MANAGEMENT SYSTEM ======\n");
        printf("1. Create Account\n");
        printf("2. Display Accounts\n");
        printf("3. Deposit Money\n");
        printf("4. Withdraw Money\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createAccount(); break;
            case 2: displayAccounts(); break;
            case 3: depositMoney(); break;
            case 4: withdrawMoney(); break;
            case 5: exit(0);
            default: printf("Invalid Choice!\n");
        }
    }

    return 0;
}

