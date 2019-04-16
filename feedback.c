#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calculate.h"
#include "results.h"
#include "testresult.h"
#include "menu.h"

#include "score.h"

#define CORRECT_RESPONSES_COUNT 6
#define INCORRECT_RESPONSES_COUNT 4
#define NO_AVAILABLE_RESULTS_RESPONSE "\nNo results available yet...\n\n"

char* correctAnswerResponses[CORRECT_RESPONSES_COUNT] = {"Very good!", "Excellent!", "Nice work!", "Well done!", "Great!", "Keep up the good work!"};
char* incorrectAnswerResponses[INCORRECT_RESPONSES_COUNT] = {"No. Please try again", "Wrong. Try once again.", "Don't give up!", "No. Keep trying."};

void GenerateCorrectAnswerResponse();
void GenerateInCorrectAnswerResponse();

void PrintResult()
{
    // Getting the test result from score.c in percentage format
    printf("\nYour test result %.2f (percent) \n", GetTestResultInPercent());
    printf("Detailed questions and answers: \n");

    // Print every question in previous test
    printf("\n   Question\t correct answer\t your answer \n");
    for(int i = 0; i < MAX_TEST; i++)
    {
        printf("%s\n", savedQuestions[i]);
    }
    printf("\n");
}
void PrintAllResults()
{
    // Checking for existing results
    int numberOfTestResults = GetNumberOfTestResults();
    if(numberOfTestResults > 0)
    {
        // Get all results in as struct array
        struct TestResult previousResults[50];
        GetAllResults(previousResults);

        printf("\n");
        printf("ALL RESULTS\n");
        printf("Name\t Type\t Result\t Date\n");
        printf("----\t ----\t ------\t ----\n");
        for(int j = 0; j < numberOfTestResults; j++)
        {
            struct TestResult temp = previousResults[j];
            printf("%s\t %d\t %.2f\t %s", temp.name, temp.type, temp.result, temp.date);
        }
        printf("\n");
    }
    else
    {
        printf(NO_AVAILABLE_RESULTS_RESPONSE);
    }
}
void PrintTopFiveResults()
{
    // Checking for existing results
    int numberOfTestResults = GetNumberOfTestResults();
    if(numberOfTestResults > 0)
    {
        // Get all results in as struct array
        struct TestResult previousResults[50];
        GetAllResults(previousResults);

        // Bubble sort
        SortResults(previousResults);

        int laps;
        if(numberOfTestResults < 5)
            laps = numberOfTestResults;
        else
            laps = 5;


        printf("\n");
        printf("TOP 5 RESULTS\n");
        printf("Name\t Type\t Result\t Date\n");
        printf("----\t ----\t ------\t ----\n");
        for(int j = 0; j < laps; j++)
        {
            struct TestResult temp = previousResults[j];
            printf("%s\t %d\t %.2f\t %s", temp.name, temp.type, temp.result, temp.date);
        }
        printf("\n");
    }
    else
    {
        printf(NO_AVAILABLE_RESULTS_RESPONSE);
    }
}
void PrintTopResult()
{
    // Checking for existing results
    int numberOfTestResults = GetNumberOfTestResults();
    if(numberOfTestResults > 0)
    {
        // Get all results in as struct array
        struct TestResult previousResults[50];
        GetAllResults(previousResults);

        // Bubble sort
        SortResults(previousResults);

        printf("\n");
        printf("TOP RESULT\n");
        printf("Name\t Type\t Result\t Date\n");
        printf("----\t ----\t ------\t ----\n");
        printf("%s\t %d\t %.2f\t %s", previousResults[0].name, previousResults[0].type, previousResults[0].result, previousResults[0].date);
        printf("\n");
    }
    else
    {
        printf(NO_AVAILABLE_RESULTS_RESPONSE);
    }
}
void PrintAllResultsByName()
{
    // Checking for existing results
    int numberOfTestResults = GetNumberOfTestResults();
    if(numberOfTestResults > 0)
    {
        struct TestResult previousResults[50];
        GetAllResults(previousResults);

        printf("\n");
        printf("ALL RESULTS FOR USER: %s \n", currentUserTestResult.name);
        printf("Type\t Result\t Date\n");
        printf("----\t ------\t ----\n");
        for(int j = 0; j < numberOfTestResults; j++)
        {
            struct TestResult temp = previousResults[j];

            if(strcmp(temp.name, currentUserTestResult.name) == 0)
            {
                printf("%d\t %.2f\t %s", temp.type, temp.result, temp.date);
            }
        }
        printf("\n");
    }
    else
    {
         printf(NO_AVAILABLE_RESULTS_RESPONSE);
    }
}

void GenerateQuestionFeedback(int realAnswer, int userAnswer)
{
    // Deciding which user feedback should be printed.
    if(realAnswer != userAnswer)
    {
        GenerateInCorrectAnswerResponse();
    }
    else
    {
        GenerateCorrectAnswerResponse();
    }
}
void GenerateCorrectAnswerResponse()
{
    // Select random index
    printf("%s\n", correctAnswerResponses[rand() % CORRECT_RESPONSES_COUNT]);
}
void GenerateInCorrectAnswerResponse()
{
     // Select random index
    printf("%s\n", incorrectAnswerResponses[rand() % INCORRECT_RESPONSES_COUNT]);
}
