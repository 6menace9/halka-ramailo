#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "bank_data.txt"

void createAccount();
void depositMoney();
void withdrawMoney();
void viewCustomers();

int main() {
    int choice;
    while (1) {
        printf("Simple Banking System\n");
        printf("1. Create Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. View Customers\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createAccount(); break;
            case 2: depositMoney(); break;
            case 3: withdrawMoney(); break;
            case 4: viewCustomers(); break;
            case 5: exit(0);
            default: printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}

void createAccount() {
    FILE *file = fopen(FILE_NAME, "a");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    int account_number;
    char name[50];
    float balance;
    
    printf("Enter account number: ");
    scanf("%d", &account_number);
    printf("Enter name: ");
    scanf("%s", name);
    printf("Enter initial balance: ");
    scanf("%f", &balance);

    fprintf(file, "%d %s %.2f\n", account_number, name, balance);
    fclose(file);

    printf("Account created successfully!\n");
}

void depositMoney() {
    FILE *file = fopen(FILE_NAME, "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (!file || !tempFile) {
        printf("Error opening file!\n");
        return;
    }

    int accNo, account_number, found = 0;
    float amount, balance;
    char name[50];
    
    printf("Enter account number: ");
    scanf("%d", &accNo);
    printf("Enter amount to deposit: ");
    scanf("%f", &amount);

    while (fscanf(file, "%d %s %f", &account_number, name, &balance) != EOF) {
        if (account_number == accNo) {
            balance += amount;
            found = 1;
        }
        fprintf(tempFile, "%d %s %.2f\n", account_number, name, balance);
    }
    fclose(file);
    fclose(tempFile);
    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found)
        printf("Amount deposited successfully!\n");
    else
        printf("Account not found!\n");
}

void withdrawMoney() {
    FILE *file = fopen(FILE_NAME, "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (!file || !tempFile) {
        printf("Error opening file!\n");
        return;
    }

    int accNo, account_number, found = 0;
    float amount, balance;
    char name[50];
    
    printf("Enter account number: ");
    scanf("%d", &accNo);
    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);

    while (fscanf(file, "%d %s %f", &account_number, name, &balance) != EOF) {
        if (account_number == accNo) {
            if (balance >= amount) {
                balance -= amount;
                found = 1;
            } else {
                printf("Insufficient balance!\n");
                found = -1;
            }
        }
        fprintf(tempFile, "%d %s %.2f\n", account_number, name, balance);
    }
    fclose(file);
    fclose(tempFile);
    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found == 1)
        printf("Amount withdrawn successfully!\n");
    else if (found == 0)
        printf("Account not found!\n");
}

void viewCustomers() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    int account_number;
    char name[50];
    float balance;
    printf("\nAccount Details:\n");
    while (fscanf(file, "%d %s %f", &account_number, name, &balance) != EOF) {
        printf("Account Number: %d\nName: %s\nBalance: %.2f\n\n", account_number, name, balance);
    }
    fclose(file);
}