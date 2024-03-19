#include <stdio.h>
#include <string.h>

enum Constants {
    MAX_ITEMS = 10,
    MAX_NAME_LEN = 50,
    SHIPPING_FEE_BASE = 50,
	ID_LAST_DIGITS_SUM = 18 //16-0433-477; 4+7+7 = 18
};
const float SHIPPING_FEE = SHIPPING_FEE_BASE + ID_LAST_DIGITS_SUM; // Calculate based on your requirements ID LAST DIGITS SUM


// Global arrays to store item names, prices, and selected items for checkout
char itemNames[MAX_ITEMS][MAX_NAME_LEN];
float itemPrices[MAX_ITEMS];
int selectedItems[MAX_ITEMS];
int itemCount = 0; // Track number of items in the cart
float totalPayment = 0.0;// This would be set by calculateTotalPayment()

// Function prototypes
void addItem();
void displayCart();
void selectItemsForCheckout();
void calculateTotalPayment();
void getPaymentChange();

int main() {
    int choice;

    while(1) {
        printf("\n1. Add Item to Cart\n");
        printf("2. Display Items in Cart\n");
        printf("3. Select Items for Checkout\n");
        printf("4. Calculate Total Payment\n");
        printf("5. Get Payment Change\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addItem(); break;
            case 2: displayCart(); break;
            case 3: selectItemsForCheckout(); break;
            case 4: calculateTotalPayment(); break;
            case 5: getPaymentChange(); break;
            case 6: return 0;
            default: printf("Invalid choice. Please enter a number between 1 and 6.\n");
        }
    }
}
//Add an item Function
void addItem() {
    if(itemCount >= MAX_ITEMS) {
        printf("Cart is full. Cannot add more items.\n");
        return;
    }

    printf("Enter item name: ");
    // Ensure the input does not exceed array bounds
    scanf("%49s", itemNames[itemCount]); 

    printf("Enter item price: ");
    scanf("%f", &itemPrices[itemCount]);

    itemCount++;
    printf("Item added successfully.\n");
}
//Display all the add to cart items
void displayCart() {
    if(itemCount == 0) {
        printf("\nYour cart is empty.\n");
        return;
    }

    printf("\nItems in your cart:\n");
    for(int i = 0; i < itemCount; i++) {
        printf("%d. %s - P%.2f\n", i+1, itemNames[i], itemPrices[i]);
    }
}
//Select Items CheckOut Function
void selectItemsForCheckout() {
    // Initialize or reset the selection status of all items
    for (int i = 0; i < MAX_ITEMS; i++) {
        selectedItems[i] = 0; // 0 means not selected, 1 means selected
    }

    if (itemCount == 0) {
        printf("Your cart is empty. Add items before checking out.\n");
        return;
    }

    printf("Select items for checkout by entering the item number. Enter 0 to finish selection.\n");
    displayCart(); // Show the items for easier selection

    int selection;
    while (1) {
        printf("Enter item number (0 to finish): ");
        scanf("%d", &selection);

        if (selection == 0) {
            break; // Exit the selection loop
        } else if (selection < 1 || selection > itemCount) {
            printf("Invalid item number. Please try again.\n");
        } else {
            selectedItems[selection - 1] = 1; // Mark the item as selected
            printf("Item %d selected.\n", selection);
        }
    }

    printf("Selection complete. Proceeding to checkout.\n");
}


//Sum Of Total Selected Item
void calculateTotalPayment() {
    totalPayment = 0; // Reset total payment
    for (int i = 0; i < itemCount; i++) {
        if (selectedItems[i]) { // If the item is selected
            totalPayment += itemPrices[i]; // Add its price to the total
        }
    }
    totalPayment += SHIPPING_FEE; // Add shipping fee to the total payment
    printf("Total payment including shipping fee: $%.2f\n", totalPayment);
}

//Payment Change

void getPaymentChange() {
    float amountPaid;
    printf("Enter the amount paid: ");
    scanf("%f", &amountPaid);

    // Ensure total payment is up-to-date
    calculateTotalPayment();

    if (amountPaid < totalPayment) {
        printf("The amount paid is not enough to cover the total payment. Please pay at least $%.2f\n", totalPayment);
    } else {
        float change = amountPaid - totalPayment;
        printf("Payment successful. Your change is $%.2f\n", change);
    }
}

