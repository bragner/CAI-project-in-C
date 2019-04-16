#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "calculate.h"
#include "menu.h"
#include "score.h"
#include "feedback.h"
#include "results.h"

#define MAX 100

int GetNumberOfQuestions(char type[]);
char RandomizeOperatorToBeUsed();
int CalculateRealAnswer(int *firstNumber, char operatorInCalculation, int *secondNumber);
void ValidateAnswer( int questionNumber, int realAnswer, int firstNumber, char operatorToShow, int secondNumber, char type[]);
void HandleNonNegativeNumber(int *firstNumber, int *secondNumber);

void Calculate(char type[], char calc)
{
    int questions = GetNumberOfQuestions(type);
    printf("Now, you will be given %i questions to solve:\n", questions);

    int correctAnswers = 0;
    srand(time(NULL));
    // Start questions loop.
    while(correctAnswers < questions)
    {
        // Generate random number for upcoming question
        int first = rand() % MAX;
        int second = rand() % MAX;

        int realAnswer;
        char operatorForQuestion;

        if(calc == '*')
        {
            // If the user has choses mixed operators this should be at random.
            operatorForQuestion = RandomizeOperatorToBeUsed();
            realAnswer = CalculateRealAnswer(&first, operatorForQuestion, &second);
        }
        else
        {
            operatorForQuestion = calc;
            realAnswer = CalculateRealAnswer(&first, operatorForQuestion, &second);
        }

        ValidateAnswer(correctAnswers + 1, realAnswer, first, operatorForQuestion, second, type);

        correctAnswers++; // Award the user correct answer.
    }

    // Print result if test has been completed
    if(strcmp(type, DO_PRACTISE) != 0)
    {
        AddTestResult(calc); // Store test result in secondary-memory
        PrintResult(); // Print result to user
    }


    return;
}
int GetNumberOfQuestions(char type[])
{
    // Deciding the number of questions based on selection made in main menu
    if(strcmp(type, DO_PRACTISE) == 0)
        return MAX_PRACTISE;
    else
        return MAX_TEST;
}
char RandomizeOperatorToBeUsed()
{
    // If random number is even select +, else -
    if((rand() % MAX) % 2)
    {
        return '+';
    }
    else
    {
        return '-';
    }
}
int CalculateRealAnswer(int *firstNumber, char operatorInCalculation, int *secondNumber)
{
    if(operatorInCalculation == '+')
    {
        return *firstNumber + *secondNumber;
    }
    else
    {
        HandleNonNegativeNumber(&*firstNumber, &*secondNumber);
        return *firstNumber - *secondNumber;
    }
}
void HandleNonNegativeNumber(int *firstNumber, int *secondNumber)
{
    // Switch first number and second number
    // to avoid negative result.
    if( *firstNumber < *secondNumber )
    {
        int temp = *firstNumber;
        *firstNumber = *secondNumber;
        *secondNumber = temp;
    }
}
void ValidateAnswer( int questionNumber, int realAnswer, int firstNumber, char operatorToShow, int secondNumber, char type[])
{
    int answer = 0;
    // Start re-try loop if the users answers incorrectly
    do
    {
        printf("%d. %d %c %d = \nEnter your answer: ", questionNumber, firstNumber, operatorToShow, secondNumber); // Output to user
        scanf("%d", &answer); // Input from user

        if(strcmp(type, DO_PRACTISE) != 0)
        {
            SaveQuestion(questionNumber, realAnswer, firstNumber, operatorToShow, secondNumber, answer); // Save question if test to output test result at a later stage.
            break;
        }
        else
        {
            GenerateQuestionFeedback(realAnswer, answer); // Correct or incorrect output response to user.
        }

    }while(answer != realAnswer); // Retry if answer was incorrect
    return;
}




