#include <assert.h>

#include "kvadr.h"

void output_answer(struct answers_data* answers)
{
    assert(answers);

    switch (answers->number_of_answers)
    {
        case NO_SOLUTIONS:
            printf("The equation has no solutions.\n");
            break;
        case ONE_SOLUTION:
            printf("The equation has one solution: %lg.\n", answers->x1);
            break;
        case TWO_SOLUTIONS:
            printf("The equation has two solutions: %lg and %lg.\n", answers->x1, answers->x2);
            break;
        case INF_NUM_OF_SOLUTIONS:
            printf("The root of the equation is any number.\n");
            break;
        default:
            printf("Input error");
            break;
    }
    return;
}
