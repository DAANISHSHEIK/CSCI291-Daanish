#include <stdio.h>

int main() {
    // Initial balance
    int balance = 1000;
    
    // Transactions array
    int transactions[] = {200, -150, -500, -400, -50, -200, 300};
    int numTransactions = sizeof(transactions) / sizeof(transactions[0]);
    
    // Array for storing unprocessed transactions
    int tobeprocessed[numTransactions];
    int unprocessedCount = 0;
    
    // Procesing transaction
    for (int i = 0; i < numTransactions; i++) {
        int transaction = transactions[i];
        
        if (transaction < 0) { // Withdrawal
            if (-transaction > balance) { // Check if withdrawal exceeds balance
                printf("Invalid transaction: %d. Not enough balance.\n", transaction);
                tobeprocessed[unprocessedCount++] = transaction;
                continue; // Skip to next transaction
            }
        }
         balance += transaction; // Update balance for valid transactions
        
        if (balance <= 0) { // Stop if thebalance reaches zero
            printf("Balance is zero. No further transactions will be processed.\n");
            for (int j = i + 1; j < numTransactions; j++) {
                tobeprocessed[unprocessedCount++] = transactions[j];
            }
            break;
        }
    }
    
    // Output final balance
    printf("Final balance: %d AED\n", balance);
    // Output unprocessed transaction
    printf("Unprocessed transactions: ");
    for (int i = 0; i < unprocessedCount; i++) {
        printf("%d ", tobeprocessed[i]);
    }
    printf("\n");
    
    return 0;
}