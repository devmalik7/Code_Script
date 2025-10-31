#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_CATEGORY_LEN 50
#define MAX_LINE_LEN 256
#define FILENAME "expenses.csv"

typedef struct {
    char date[11];
    double amount;
    char category[MAX_CATEGORY_LEN];
} Expense;

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void getCurrentDate(char *dateStr) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(dateStr, 11, "%Y-%m-%d", tm_info);
}

void initializeFile() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        file = fopen(FILENAME, "w");
        if (file != NULL) {
            fprintf(file, "Date,Amount,Category\n");
            fclose(file);
            printf("Created new expense file: %s\n\n", FILENAME);
        } else {
            printf("Error creating file!\n");
        }
    } else {
        fclose(file);
    }
}

void addExpense() {
    Expense exp;
    FILE *file;
    
    getCurrentDate(exp.date);
    
    printf("\n=== Add New Expense ===\n");
    printf("Date: %s (today)\n", exp.date);
    
    printf("Enter amount: $");
    if (scanf("%lf", &exp.amount) != 1 || exp.amount <= 0) {
        printf("Invalid amount! Please enter a positive number.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();
    
    printf("Enter category: ");
    if (fgets(exp.category, MAX_CATEGORY_LEN, stdin) == NULL) {
        printf("Error reading category!\n");
        return;
    }
    exp.category[strcspn(exp.category, "\n")] = 0;
    
    if (strlen(exp.category) == 0) {
        printf("Category cannot be empty!\n");
        return;
    }
    
    file = fopen(FILENAME, "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    
    fprintf(file, "%s,%.2f,%s\n", exp.date, exp.amount, exp.category);
    fclose(file);
    
    printf("\n✓ Expense added successfully!\n");
    printf("  Date: %s\n", exp.date);
    printf("  Amount: $%.2f\n", exp.amount);
    printf("  Category: %s\n", exp.category);
}

void viewExpenses() {
    FILE *file;
    char line[MAX_LINE_LEN];
    int count = 0;
    double total = 0.0;
    
    file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("No expenses found! File doesn't exist.\n");
        return;
    }
    
    printf("\n=== All Expenses ===\n");
    printf("%-12s %-12s %-20s\n", "Date", "Amount", "Category");
    printf("------------------------------------------------\n");
    
    fgets(line, MAX_LINE_LEN, file);
    
    while (fgets(line, MAX_LINE_LEN, file) != NULL) {
        char date[11];
        double amount;
        char category[MAX_CATEGORY_LEN];
        
        char *token = strtok(line, ",");
        if (token != NULL) strcpy(date, token);
        
        token = strtok(NULL, ",");
        if (token != NULL) amount = atof(token);
        
        token = strtok(NULL, "\n");
        if (token != NULL) strcpy(category, token);
        
        printf("%-12s $%-11.2f %-20s\n", date, amount, category);
        total += amount;
        count++;
    }
    
    fclose(file);
    
    printf("------------------------------------------------\n");
    printf("Total Expenses: %d\n", count);
    printf("Total Amount: $%.2f\n", total);
}

void viewSummaryByCategory() {
    FILE *file;
    char line[MAX_LINE_LEN];
    
    typedef struct {
        char category[MAX_CATEGORY_LEN];
        double total;
        int count;
    } CategorySummary;
    
    CategorySummary summaries[100];
    int numCategories = 0;
    
    file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("No expenses found!\n");
        return;
    }
    
    fgets(line, MAX_LINE_LEN, file);
    
    while (fgets(line, MAX_LINE_LEN, file) != NULL) {
        char category[MAX_CATEGORY_LEN];
        double amount;
        
        strtok(line, ",");
        char *token = strtok(NULL, ",");
        if (token != NULL) amount = atof(token);
        
        token = strtok(NULL, "\n");
        if (token != NULL) strcpy(category, token);
        
        int found = 0;
        for (int i = 0; i < numCategories; i++) {
            if (strcmp(summaries[i].category, category) == 0) {
                summaries[i].total += amount;
                summaries[i].count++;
                found = 1;
                break;
            }
        }
        
        if (!found && numCategories < 100) {
            strcpy(summaries[numCategories].category, category);
            summaries[numCategories].total = amount;
            summaries[numCategories].count = 1;
            numCategories++;
        }
    }
    
    fclose(file);
    
    printf("\n=== Expense Summary by Category ===\n");
    printf("%-20s %-12s %-10s\n", "Category", "Total", "Count");
    printf("------------------------------------------------\n");
    
    for (int i = 0; i < numCategories; i++) {
        printf("%-20s $%-11.2f %d\n", 
               summaries[i].category, 
               summaries[i].total, 
               summaries[i].count);
    }
}

void displayMenu() {
    printf("\n╔════════════════════════════════════╗\n");
    printf("║     EXPENSE TRACKER MENU          ║\n");
    printf("╠════════════════════════════════════╣\n");
    printf("║ 1. Add Expense                    ║\n");
    printf("║ 2. View All Expenses              ║\n");
    printf("║ 3. View Summary by Category       ║\n");
    printf("║ 4. Exit                           ║\n");
    printf("╚════════════════════════════════════╝\n");
    printf("Choose an option: ");
}

int main() {
    int choice;
    
    printf("╔════════════════════════════════════╗\n");
    printf("║   WELCOME TO EXPENSE TRACKER      ║\n");
    printf("╚════════════════════════════════════╝\n\n");
    
    initializeFile();
    
    while (1) {
        displayMenu();
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();
        
        switch (choice) {
            case 1:
                addExpense();
                break;
            case 2:
                viewExpenses();
                break;
            case 3:
                viewSummaryByCategory();
                break;
            case 4:
                printf("\nThank you for using Expense Tracker!\n");
                printf("Your expenses are saved in '%s'\n", FILENAME);
                return 0;
            default:
                printf("Invalid choice! Please select 1-4.\n");
        }
    }
    
    return 0;
}
