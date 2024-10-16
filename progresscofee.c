#include <stdio.h>
#include <stdlib.h>

// Coffee Prices as Modifiable Variables
float espresso_price = 3.5;
float cappuccino_price = 4.5;
float mocha_price = 5.5;

// Ingredient Constants
#define ESPRESSO_BEANS 8
#define ESPRESSO_WATER 30
#define CAPPUCCINO_BEANS 8
#define CAPPUCCINO_WATER 30
#define CAPPUCCINO_MILK 70
#define MOCHA_BEANS 8
#define MOCHA_WATER 39
#define MOCHA_MILK 160
#define MOCHA_SYRUP 30

// Low Ingredient Thresholds
#define LOW_BEANS_THRESHOLD 8
#define LOW_WATER_THRESHOLD 30
#define LOW_MILK_THRESHOLD 70
#define LOW_SYRUP_THRESHOLD 30

// Admin Password
#define ADMIN_PASSWORD 1234

// Global Variables for Ingredients and Sales
int beans = 100, water = 1000, milk = 500, syrup = 100;
float total_sales = 0.0;

// Function Declarations
void orderCoffee();
void adminMode();
void displayIngredients();
void replenishIngredients();
void changeCoffeePrice();

int main() {
    int choice;

    while (1) {
        printf("\n--- Coffee Machine ---\n");
        printf("1. Order a Coffee\n");
        printf("2. Admin Mode\n");
        printf("3. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        if (choice == 1) {
            orderCoffee();
        } else if (choice == 2) {
            adminMode();
        } else if (choice == 3) {
            printf("Exiting... Goodbye!\n");
            break;
        } else {
            printf("Invalid option. Try again.\n");
        }
    }

    return 0;
}

void orderCoffee() {
    int choice, confirm;
    float total_paid = 0;
    float price = 0;

    while (1) {
        printf("\nAvailable Coffees:\n");
        if (beans >= ESPRESSO_BEANS && water >= ESPRESSO_WATER) {
            printf("1. Espresso - AED %.2f\n", espresso_price);
        } else {
            printf("1. Espresso - Unavailable due to insufficient ingredients\n");
        }

        if (beans >= CAPPUCCINO_BEANS && water >= CAPPUCCINO_WATER && milk >= CAPPUCCINO_MILK) {
            printf("2. Cappuccino - AED %.2f\n", cappuccino_price);
        } else {
            printf("2. Cappuccino - Unavailable due to insufficient ingredients\n");
        }

        if (beans >= MOCHA_BEANS && water >= MOCHA_WATER && milk >= MOCHA_MILK && syrup >= MOCHA_SYRUP) {
            printf("3. Mocha - AED %.2f\n", mocha_price);
        } else {
            printf("3. Mocha - Unavailable due to insufficient ingredients\n");
        }
        printf("0. Exit\n");

        printf("Select your coffee: ");
        scanf("%d", &choice);

        if (choice == 0) {
            return;
        }

        if (choice == 1 && beans >= ESPRESSO_BEANS && water >= ESPRESSO_WATER) {
            price = espresso_price;
            printf("You selected Espresso. Confirm? (1 for Yes, 0 for No): ");
        } else if (choice == 2 && beans >= CAPPUCCINO_BEANS && water >= CAPPUCCINO_WATER && milk >= CAPPUCCINO_MILK) {
            price = cappuccino_price;
            printf("You selected Cappuccino. Confirm? (1 for Yes, 0 for No): ");
        } else if (choice == 3 && beans >= MOCHA_BEANS && water >= MOCHA_WATER && milk >= MOCHA_MILK && syrup >= MOCHA_SYRUP) {
            price = mocha_price;
            printf("You selected Mocha. Confirm? (1 for Yes, 0 for No): ");
        } else {
            printf("Invalid selection or unavailable coffee.\n");
            continue;
        }

        scanf("%d", &confirm);
        if (confirm != 1) {
            printf("Order cancelled.\n");
            continue;
        }

        total_paid = 0;
        while (total_paid < price) {
            float coin;
            printf("Insert 1 or 0.5 Dirham coins: ");
            scanf("%f", &coin);

            if (coin == 1 || coin == 0.5) {
                total_paid += coin;
            } else {
                printf("Invalid coin. Please collect and insert a valid one.\n");
            }
        }

        float change = total_paid - price;
        if (change > 0) {
            printf("Your change: AED %.2f\n", change);
        }

        printf("Coffee purchased! Enjoy your drink.\n");

        if (choice == 1) {
            beans -= ESPRESSO_BEANS;
            water -= ESPRESSO_WATER;
        } else if (choice == 2) {
            beans -= CAPPUCCINO_BEANS;
            water -= CAPPUCCINO_WATER;
            milk -= CAPPUCCINO_MILK;
        } else if (choice == 3) {
            beans -= MOCHA_BEANS;
            water -= MOCHA_WATER;
            milk -= MOCHA_MILK;
            syrup -= MOCHA_SYRUP;
        }

        total_sales += price;

        // Check for low ingredients
        if (beans <= LOW_BEANS_THRESHOLD) {
            printf("Warning: Low coffee beans!\n");
        }
        if (water <= LOW_WATER_THRESHOLD) {
            printf("Warning: Low water!\n");
        }
        if (milk <= LOW_MILK_THRESHOLD) {
            printf("Warning: Low milk!\n");
        }
        if (syrup <= LOW_SYRUP_THRESHOLD) {
            printf("Warning: Low chocolate syrup!\n");
        }
    }
}

void adminMode() {
    int password, option;

    printf("Enter admin password: ");
    scanf("%d", &password);

    if (password != ADMIN_PASSWORD) {
        printf("Incorrect password!\n");
        return;
    }

    while (1) {
        printf("\nAdmin Menu:\n");
        printf("1. Display Ingredient Levels and Total Sales\n");
        printf("2. Replenish Ingredients\n");
        printf("3. Change Coffee Prices\n");
        printf("0. Exit Admin Mode\n");
        printf("Select an option: ");
        scanf("%d", &option);

        if (option == 1) {
            displayIngredients();
        } else if (option == 2) {
            replenishIngredients();
        } else if (option == 3) {
            changeCoffeePrice();
        } else if (option == 0) {
            printf("Exiting Admin Mode.\n");
            break;
        } else {
            printf("Invalid option. Try again.\n");
        }
    }
}

void displayIngredients() {
    printf("\nCurrent Ingredients:\n");
    printf("Coffee Beans: %d grams\n", beans);
    printf("Water: %d milliliters\n", water);
    printf("Milk: %d milliliters\n", milk);
    printf("Chocolate Syrup: %d milliliters\n", syrup);
    printf("Total Sales: AED %.2f\n", total_sales);
}

void replenishIngredients() {
    beans = 100;
    water = 1000;
    milk = 500;
    syrup = 100;
    printf("Ingredients replenished!\n");
}

void changeCoffeePrice() {
    int coffee_choice;
    float new_price;

    printf("\nWhich coffee price would you like to change?\n");
    printf("1. Espresso (Current Price: AED %.2f)\n", espresso_price);
    printf("2. Cappuccino (Current Price: AED %.2f)\n", cappuccino_price);
    printf("3. Mocha (Current Price: AED %.2f)\n", mocha_price);
    printf("Select: ");
    scanf("%d", &coffee_choice);

    printf("Enter new price: AED ");
    scanf("%f", &new_price);

    if (new_price <= 0) {
        printf("Invalid price. Price must be positive.\n");
        return;
    }

    if (coffee_choice == 1) {
        espresso_price = new_price;
        printf("New Espresso price: AED %.2f\n", espresso_price);
    } else if (coffee_choice == 2) {
        cappuccino_price = new_price;
        printf("New Cappuccino price: AED %.2f\n", cappuccino_price);
    } else if (coffee_choice == 3) {
        mocha_price = new_price;
        printf("New Mocha price: AED %.2f\n", mocha_price);
    } else {
        printf("Invalid coffee selection.\n");
    }
}