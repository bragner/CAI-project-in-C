#include "score.h"
#include <string.h>

int realAnswers[MAX_TEST];
int userAnswers[MAX_TEST];

void SaveQuestion( int questionNumber, int realAnswer, int firstNumber, char operatorToShow, int secondNumber, int userAnswer )
{
    int index = questionNumber - 1;
    realAnswers[index] = realAnswer; // Store all the correct answers
    userAnswers[index] = userAnswer; // Store all the user answers

    char question[50] = {};
    snprintf(question, sizeof(question), "%d. %d %c %d\t %d\t\t %d", questionNumber,
                                                                     firstNumber,
                                                                     operatorToShow,
                                                                     secondNumber,
                                                                     realAnswer,
                                                                     userAnswer);
    // Save the question
    strcpy(savedQuestions[index], question);
    *question = '\0'; // reset for next question.
}
float GetTestResultInPercent()
{
    float incorrectAnswers = 0;

    for(int i = 0; i < MAX_TEST; i++)
    {
        // Compare answers to later calculate percentage.
        if( userAnswers[i] != realAnswers[i] )
        {
            incorrectAnswers++;
        }
    }

    return ((MAX_TEST - incorrectAnswers) / MAX_TEST) * 100;
}
