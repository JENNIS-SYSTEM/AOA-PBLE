#include <stdio.h>

#define MAX 100

struct Package {
    int id;
    float value;
    float weight;
    float ratio;
    float fraction;
};

struct Package p[MAX];
int n = 0;
float capacity = 0;

void enterDetails() {
    int i;

    printf("\nEnter number of packages: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        p[i].id = i + 1;

        printf("\nPackage %d\n", i + 1);

        printf("Enter value/profit: ");
        scanf("%f", &p[i].value);

        printf("Enter weight: ");
        scanf("%f", &p[i].weight);

        p[i].ratio = 0;
        p[i].fraction = 0;
    }

    printf("\nEnter vehicle capacity: ");
    scanf("%f", &capacity);

    printf("\nPackage details entered successfully!\n");
}

void displayDetails() {
    int i;

    printf("\n-------------------------------------------------\n");
    printf("ID\tValue\tWeight\tRatio\n");
    printf("-------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("%d\t%.2f\t%.2f\t%.2f\n",
               p[i].id,
               p[i].value,
               p[i].weight,
               p[i].ratio);
    }
}

void calculateRatio() {
    int i;

    for (i = 0; i < n; i++) {
        p[i].ratio = p[i].value / p[i].weight;
    }

    printf("\nValue/Weight ratio calculated successfully!\n");
}

void sortPackages() {
    int i, j;
    struct Package temp;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (p[j].ratio < p[j + 1].ratio) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    printf("\nPackages sorted by decreasing Value/Weight ratio.\n");

    printf("\nID\tValue\tWeight\tRatio\n");
    printf("---------------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("%d\t%.2f\t%.2f\t%.2f\n",
               p[i].id,
               p[i].value,
               p[i].weight,
               p[i].ratio);
    }
}

void findMaximumValue() {
    int i;
    float remaining = capacity;
    float totalValue = 0;
    float totalWeight = 0;

    for (i = 0; i < n; i++) {
        p[i].fraction = 0;

        if (remaining <= 0)
            break;

        if (p[i].weight <= remaining) {
            // Take complete package
            p[i].fraction = 1;
            remaining = remaining - p[i].weight;
            totalValue = totalValue + p[i].value;
            totalWeight = totalWeight + p[i].weight;
        } else {
            // Take fraction of package
            p[i].fraction = remaining / p[i].weight;
            totalValue = totalValue + (p[i].value * p[i].fraction);
            totalWeight = totalWeight + remaining;
            remaining = 0;
        }
    }

    printf("\n=============================================\n");
    printf("Total Weight Used : %.2f\n", totalWeight);
    printf("Maximum Value     : %.2f\n", totalValue);
    printf("=============================================\n");
}

void displaySelected() {
    int i;

    printf("\nSelected Packages:\n");
    printf("---------------------------------------------\n");
    printf("ID\tFraction\tWeight Used\tValue\n");
    printf("---------------------------------------------\n");

    for (i = 0; i < n; i++) {
        if (p[i].fraction > 0) {
            printf("%d\t%.2f\t\t%.2f\t\t%.2f\n",
                   p[i].id,
                   p[i].fraction,
                   p[i].weight * p[i].fraction,
                   p[i].value * p[i].fraction);
        }
    }
}

int main() {
    int choice;

    do {
        printf("\n\n===== SMART DELIVERY PLANNING =====\n");
        printf("1. Enter Package Details\n");
        printf("2. Display Package Details\n");
        printf("3. Calculate Value/Weight Ratio\n");
        printf("4. Sort Packages by Ratio\n");
        printf("5. Find Maximum Value\n");
        printf("6. Display Selected Packages\n");
        printf("7. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                enterDetails();
                break;

            case 2:
                displayDetails();
                break;

            case 3:
                calculateRatio();
                break;

            case 4:
                sortPackages();
                break;

            case 5:
                findMaximumValue();
                break;

            case 6:
                displaySelected();
                break;

            case 7:
                printf("\nExiting program...\n");
                break;

            default:
                printf("\nInvalid choice! Try again.\n");
        }

    } while (choice != 7);

    return 0;
}
