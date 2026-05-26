#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addExpense();
void viewExpenses();
void resetExpenses();




int main() {
    int option;
    
    while (1) {
        printf("\nExpense Manager\n");
        printf("1. Add Expense\n");
        printf("2. View Expenses\n");
        printf("3. Reset Expense List\n");
        printf("4. Exit\n");
        printf("Select an option: ");
        scanf("%d", &option);
        getchar();  // Consume newline left in input buffer
        if(option == 1){
            addExpense();
        }
        else if(option == 2){
            viewExpenses();
        }
        else if(option == 3){
            resetExpenses();
        }
        else if(option == 4){
            break;
        }
    }
    return 0;
}

void addExpense() {
    FILE *file = fopen("expenses.txt", "a");
    /////////////////////////
    //write your logic here
    ////////////////////////
    char name[100], date[11];
    float amount;
    printf("Enter Expense Name: ");
    scanf("%s", name);
    printf("Enter Date: ");
    scanf("%s", date);
    printf("Enter Amount ");
    scanf("%f", &amount);
    fprintf(file, "%s %s %.2f\n", name, date, amount);
    fclose(file);
    printf("Expense added successfully!\n");
}

void viewExpenses() {
    FILE *file = fopen("expenses.txt", "r");
    /////////////////////////
    //write your logic here
    ////////////////////////
    char name[100], date[11];
    float amount, total = 0.0;
    int c = 1;
    printf("Expense List: ");
    while(fscanf(file, "%s %s %f", name, date, &amount) == 3){
        printf("%d. Name: %s, Date: %s, Amount: %.2f", c, name, date, amount);
        total = total + amount;
        c = c + 1;
    }
    rewind(file);
    fclose(file);
    printf("Total Expenses: %.2f\n", total);
}

void resetExpenses() {
    FILE *file = fopen("expenses.txt", "w");
   /////////////////////////
    //write your logic here
    ////////////////////////
    fclose(file);
    printf("Expense list has been reset.\n");
}
