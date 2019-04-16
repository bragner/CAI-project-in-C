#include "calculate.h"

char savedQuestions[MAX_TEST][50];

void SaveQuestion(int questionNumber, int realAnswer, int firstNumber, char operatorToShow, int secondNumber, int userAnswer);
float GetTestResultInPercent();
