#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "testresult.h"
#include "menu.h"
#include "score.h"

#define LINE 150
#define RESULTS_PATH "testresults/results.txt"

void MapCurrentUserTestResult(char calc)
{
    // Get the current time
    time_t t;
    struct tm * timeinfo;
    time ( &t );
    timeinfo = localtime ( &t );

    strcpy(currentUserTestResult.date, asctime (timeinfo));

    // Parsing selected type of test
    int type = 0;
    if(calc == '+')
        type = 1;
    else if(calc == '-')
        type = 2;
    else
        type = 3;

    currentUserTestResult.type = type;
    currentUserTestResult.result = GetTestResultInPercent();
}
int GetNumberOfTestResults()
{
    FILE *fPointer = fopen(RESULTS_PATH, "r");
    int c, numberOfLines = 0;

    // Counting number of lines in text file for loops
    do
    {
        c = fgetc(fPointer);
        if(c == '\n')
            numberOfLines++;
    } while (c != EOF);

    fclose(fPointer);

    return numberOfLines;
}
void GetAllResults(struct TestResult * previousTestResults)
{
    FILE *fPointer;
    fPointer = fopen(RESULTS_PATH, "r");
    char line[LINE];
    int i = 0;
    while(!feof(fPointer))
    {
        fgets(line, LINE, fPointer);

        // Checking for each comma which separates the struct members
        char *comma;
        comma = strtok(line, ",");

        const char *currentTestResult[4];
        int counter = 0;
        while( comma != NULL )
        {
            currentTestResult[counter] = comma;
            comma = strtok(NULL, ",");
            counter++;
        }

        // Setting struct members from text file values.
        struct TestResult currentTestStruct;
        strcpy(currentTestStruct.name, currentTestResult[0]);
        currentTestStruct.type = atoi(currentTestResult[1]);
        currentTestStruct.result = atof(currentTestResult[2]);
        strcpy(currentTestStruct.date, currentTestResult[3]);

        previousTestResults[i] = currentTestStruct;
        i++;
    }
    fclose(fPointer);

}
void AddTestResult(char calc)
{
    MapCurrentUserTestResult(calc);

    char line[LINE];
    sprintf(line, "%s,%d,%.2f,%s", currentUserTestResult.name, currentUserTestResult.type, currentUserTestResult.result, currentUserTestResult.date);

    // Appending current testresult to textfile
    FILE *fPointer;
    fPointer = fopen(RESULTS_PATH, "a+");
    fputs(line, fPointer);
    fclose(fPointer);
}

void SortResults(struct TestResult * previousTestResults)
{
    // Bubble sort for ordering the test results
    int swapped = 1;

    while(swapped)
    {
        swapped = 0;
        for(int i = 0; i < GetNumberOfTestResults(); i++)
        {
            if(previousTestResults[i].result < previousTestResults[i + 1].result)
            {
                struct TestResult temp = previousTestResults[i];
                previousTestResults[i] = previousTestResults[i + 1];
                previousTestResults[i + 1] = temp;
                swapped = 1;
            }
        }
    }
}



