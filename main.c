#include <stdio.h>
#include "menu.h"
#include <string.h>

void GetName();

int main()
{
    GetName();
    MainMenu();
}
void GetName()
{
    printf("Enter your name: ");
    scanf("%s", currentUserTestResult.name);
    printf("Welcome, %s!\n", currentUserTestResult.name);
}

