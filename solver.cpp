#include <math.h>
#include <assert.h>

#include "kvadr.h"

void equation_solver(struct coefficients_data* coefficients,
                     struct answers_data* answers)
{
    assert(coefficients);
    assert(answers);
    is_not_special_value(coefficients->a);
    is_not_special_value(coefficients->b);
    is_not_special_value(coefficients->c);

    answers->x1 = 0;
    answers->x2 = 0;

    if (is_close_to_zero(coefficients->a))
    {
        linear_equation_solver(coefficients, answers);
    }
    else
    {
        quadratic_equation_solver(coefficients, answers);
    }

    return;
}

void linear_equation_solver(struct coefficients_data* coefficients,
                            struct answers_data* answers)
{
    assert(coefficients);
    assert(answers);

    if (is_close_to_zero(coefficients->b))
    {
        if (is_close_to_zero(coefficients->c))
        {
            answers->number_of_answers = INF_SOLUTIONS;
        }
        else
        {
            answers->number_of_answers = NO_SOLUTIONS;
        }
    }
    else
    {
        answers->x1 = - coefficients->c / coefficients->b;
        check_minus_before_zero(&(answers->x1));
        answers->number_of_answers = ONE_SOLUTION;
    }

    return;
}

void quadratic_equation_solver(struct coefficients_data* coefficients,
                               struct answers_data* answers)
{
    assert(coefficients);
    assert(answers);

    double discriminant = coefficients->b * coefficients->b -
                          4 * coefficients->a * coefficients->c;

    if (discriminant > 0)
    {
        answers->x1 = (-coefficients->b + sqrt(discriminant)) /
                                                        (2 * coefficients->a);

        answers->x2 = (-coefficients->b - sqrt(discriminant)) /
                                                        (2 * coefficients->a);
        if (answers->x2 > answers->x1)
        {
            swap_value(&answers->x2, &answers->x1);
        }

        check_minus_before_zero(&(answers->x1));
        check_minus_before_zero(&(answers->x2));

        answers->number_of_answers = TWO_SOLUTIONS;
    }
    else if (is_close_to_zero(discriminant))
    {
        answers->x1 = -coefficients->b / (2 * coefficients->a);
        check_minus_before_zero(&(answers->x1));
        answers->number_of_answers = ONE_SOLUTION;
    }
    else
    {
        answers->number_of_answers = NO_SOLUTIONS;
    }

    return;
}

int is_close_to_zero (double number_being_checked)
{
    is_not_special_value(number_being_checked);

    return (fabs(number_being_checked) < NUMBER_CLOSE_TO_ZERO);
}

void check_minus_before_zero (double* number_being_checked)
{
    assert(number_being_checked);

    if (is_close_to_zero(*number_being_checked))
    {
        *number_being_checked = fabs(*number_being_checked);
    }

    return;
}

void is_not_special_value(double coefficient)
{
    assert(!isnan(coefficient) && !isinf(coefficient));
    return;
}

void swap_value(double* answer_1, double* answer_2)
{
    double first_value_answer_1 = *answer_1;
    *answer_1 = *answer_2;
    *answer_2 = first_value_answer_1;

    return;
}
