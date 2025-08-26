#include <math.h>
#include <assert.h>

#include "kvadr.h"

void equation_solver(struct equation_data* equation)
{
    /*assert(coefficients);
    assert(answers);
    assert(number_of_answers);
    assert(coefficients != answers);
    assert(!isnan((double) *coefficients));
    assert(!isnan((double) *(coefficients+1)));
    assert(!isnan((double) *(coefficients+2)));*/

    if (is_close_to_zero(equation->coefficients.a))
    {
        linear_equation_solver(equation);
    }
    else
    {
        quadratic_equation_solver(equation);
    }
    return;
}

void linear_equation_solver(struct equation_data* equation)
{
    if (is_close_to_zero(equation->coefficients.b))
    {
        if (is_close_to_zero(equation->coefficients.c))
        {
            equation->number_of_answers = INF_NUM_OF_SOLUTIONS;
        }
        else
        {
            equation->number_of_answers = NO_SOLUTIONS;
        }
    }
    else
    {
        equation->answers.x1 = - equation->coefficients.c / equation->coefficients.b;
        check_minus_before_zero(&(equation->answers.x1));
        equation->number_of_answers = ONE_SOLUTION;
    }
    return;
}

void quadratic_equation_solver(struct equation_data* equation)
{
    /*assert(coefficients);
    assert(answers);
    assert(number_of_answers);
    assert(coefficients != answers);*/

    double discriminant = equation->coefficients.b * equation->coefficients.b -
                          4 * equation->coefficients.a * equation->coefficients.c;

    if (discriminant > 0)
    {
        equation->answers.x1 = (-equation->coefficients.b + sqrt(discriminant)) /
                                                        (2 * equation->coefficients.a);

        equation->answers.x2 = (-equation->coefficients.b - sqrt(discriminant)) /
                                                        (2 * equation->coefficients.a);

        check_minus_before_zero(&(equation->answers.x1));
        check_minus_before_zero(&(equation->answers.x2));

        equation->number_of_answers = TWO_SOLUTIONS;
    }
    else if (is_close_to_zero(discriminant))
    {
        equation->answers.x1 = -equation->coefficients.b / (2 * equation->coefficients.a);
        check_minus_before_zero(&(equation->answers.x1));
        equation->number_of_answers = ONE_SOLUTION;
    }
    else
        equation->number_of_answers = NO_SOLUTIONS;
    return;
}

int is_close_to_zero (double number_being_checked)
{
    return (fabs(number_being_checked) < NUMBER_CLOSE_TO_ZERO);
}

void check_minus_before_zero (double* number_being_checked)
{
    assert(number_being_checked);

    if (is_close_to_zero(*number_being_checked)) {
        *number_being_checked = fabs(*number_being_checked);
    }
    return;
}
