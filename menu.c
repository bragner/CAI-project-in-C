#include <stdio.h>

#include "menu.h"
#include "calculate.h"
#include "feedback.h"

void CalculateMenu(char type[]);

void MainMenu()
{
    int selection;
    do
    {
        printf("You can choose: \n\t1. do practices \n\t2. complete a test\n\t3. display test history\n\t4. best result\n\t5. display my test history\n\t6. display top 5 test results\n\t7. quit the program\nEnter your choice: ");
        scanf(" %d", &selection);

        // Selection decides which action to take and pass the type to the next menu.
        switch(selection)
        {
            case 1: CalculateMenu(DO_PRACTISE);
                break;
            case 2: CalculateMenu(DO_TEST);
                break;
            case 3: PrintAllResults();
                break;
            case 4: PrintTopResult();
                break;
            case 5: PrintAllResultsByName();
                break;
            case 6: PrintTopFiveResults();
                break;
            case 7: printf("Good bye!");
                break;
            default: printf("Invalid input\n");
                break;
        }

    }while(selection != 7);
    return;
}
void CalculateMenu(char type[])
{
    int selection;
    printf("Now, you can choose to %s on: \n\t1. additions \n\t2. subtractions\n\t3. additions and subtractions\n\t4. Go back\nEnter your choice: ", type);
    scanf("%d", &selection);

    // Selection decides which operator and passes the type from previous menu and operator to quiz logic.
    switch(selection)
    {
        case 1: Calculate(type, '+');
            break;
        case 2: Calculate(type, '-');
            break;
        case 3: Calculate(type, '*');
            break;
        case 4: printf("Back to main menu\n");
            break;
        default: printf("Invalid input\n");
            break;
    }
    return;
}
