#include <assert.h>

#include "kvadr.h"
#include "font.h"

void output_answer(struct answers_data* answers)
{
    assert(answers);

    switch (answers->number_of_answers)
    {
        case NO_SOLUTIONS:
            printf(MAKE_BOLD("The equation has no solutions.\n"));
            break;
        case ONE_SOLUTION:
            printf(MAKE_BOLD("The equation has one solution: %lg.\n"), answers->x1);
            break;
        case TWO_SOLUTIONS:
            printf(MAKE_BOLD("The equation has two solutions: %lg and %lg.\n"), answers->x1, answers->x2);
            break;
        case INF_SOLUTIONS:
            printf(MAKE_BOLD("The root of the equation is any number.\n"));
            break;
        case ERROR_SOLUTIONS:
        default:
            printf(MAKE_BOLD_RED("Input error.\n"));
            break;
    }
    return;
}
