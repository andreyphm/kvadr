#include <math.h>
#include <assert.h>

#include "kvadr.h"

void test_equation_solver(struct test_equation_data* test_equation)
{
    /*assert(coefficients);
    assert(answers);
    assert(number_of_answers);
    assert(coefficients != answers);
    assert(!isnan((double) *coefficients));
    assert(!isnan((double) *(coefficients+1)));
    assert(!isnan((double) *(coefficients+2)));*/

    if (test_is_close_to_zero(test_equation->coefficients.a))
    {
        test_linear_equation_solver(test_equation);
    }
    else
    {
        test_quadratic_equation_solver(test_equation);
    }
    return;
}

void test_linear_equation_solver(struct test_equation_data* test_equation)
{
    if (test_is_close_to_zero(test_equation->coefficients.b))
    {
        if (test_is_close_to_zero(test_equation->coefficients.c))
        {
            test_equation->number_of_answers = INF_NUM_OF_SOLUTIONS;
            test_equation->answers.x1 = NAN;
            test_equation->answers.x2 = NAN;
        }
        else
        {
            test_equation->number_of_answers = NO_SOLUTIONS;
            test_equation->answers.x1 = NAN;
            test_equation->answers.x2 = NAN;
        }
    }
    else
    {
        test_equation->answers.x1 = - test_equation->coefficients.c / test_equation->coefficients.b;
        test_equation->answers.x2 = NAN;
        test_check_minus_before_zero(&(test_equation->answers.x1));
        test_equation->number_of_answers = ONE_SOLUTION;
    }
    return;
}

void test_quadratic_equation_solver(struct test_equation_data* test_equation)
{
    /*assert(coefficients);
    assert(answers);
    assert(number_of_answers);
    assert(coefficients != answers);*/

    double discriminant = test_equation->coefficients.b * test_equation->coefficients.b -
                          4 * test_equation->coefficients.a * test_equation->coefficients.c;

    if (discriminant > 0)
    {
        test_equation->answers.x1 = (-test_equation->coefficients.b + sqrt(discriminant)) /
                                                        (2 * test_equation->coefficients.a);

        test_equation->answers.x2 = (-test_equation->coefficients.b - sqrt(discriminant)) /
                                                        (2 * test_equation->coefficients.a);

        test_check_minus_before_zero(&(test_equation->answers.x1));
        test_check_minus_before_zero(&(test_equation->answers.x2));

        test_equation->number_of_answers = TWO_SOLUTIONS;
    }
    else if (test_is_close_to_zero(discriminant))
    {
        test_equation->answers.x1 = -test_equation->coefficients.b / (2 * test_equation->coefficients.a);
        test_equation->answers.x2 = NAN;
        test_check_minus_before_zero(&(test_equation->answers.x1));
        test_equation->number_of_answers = ONE_SOLUTION;
    }
    else
        test_equation->answers.x1 = NAN;
        test_equation->answers.x2 = NAN;
        test_equation->number_of_answers = NO_SOLUTIONS;
    return;
}

int test_is_close_to_zero (double number_being_checked)
{
    return (fabs(number_being_checked) < NUMBER_CLOSE_TO_ZERO);
}

void test_check_minus_before_zero (double* number_being_checked)
{
    assert(number_being_checked);

    if (test_is_close_to_zero(*number_being_checked))
    {
        *number_being_checked = fabs(*number_being_checked);
    }
    return;
}
