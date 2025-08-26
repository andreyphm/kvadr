#include <stdio.h>
#include <math.h>

#include "kvadr.h"

int test_one_equation(struct test_equation_data* test_equation)
{
    test_equation_solver(test_equation);

    if (!(is_close_to_zero(test_equation->answers.x1 - test_equation->reference_answers.x1_ref) &&
          is_close_to_zero(test_equation->answers.x2 - test_equation->reference_answers.x2_ref) &&
          test_equation->number_of_answers == test_equation->reference_number_of_answers))
    {
        printf("FAILED: equation_solution ({%lg, %lg, %lg}, {%lg, %lg}, %d, "
               "but our solution: %lg, %lg, %d)\n",
        test_equation->coefficients.a, test_equation->coefficients.b, test_equation->coefficients.c,
        test_equation->reference_answers.x1_ref, test_equation->reference_answers.x2_ref,
        test_equation->reference_number_of_answers,
        test_equation->answers.x1, test_equation->answers.x2,
        test_equation->number_of_answers);

        return 0;
    }
    else
    {
        return 1;
    }
}

int run_test_solver()
{
    struct test_equation_data array_of_test_equations[] = {{{.a = 0,.b = 0,.c = 0}, {.x1 = NAN,.x2 = NAN},.number_of_answers = -1,
                                                            {.x1_ref = NAN,.x2_ref = NAN}, .reference_number_of_answers = -1},
                                                           {{.a = 1,.b = 2,.c = 3}, {.x1 = NAN,.x2 = NAN},.number_of_answers = 0,
                                                            {.x1_ref = NAN,.x2_ref = NAN}, .reference_number_of_answers = 0},
                                                           {{.a = 1,.b = 0,.c = 4}, {.x1 = NAN,.x2 = NAN},.number_of_answers = 0,
                                                            {.x1_ref = NAN,.x2_ref = NAN}, .reference_number_of_answers = 0},
                                                           {{.a = 1,.b = 0,.c = -4}, {.x1 = 2,.x2 = -2},.number_of_answers = 2,
                                                            {.x1_ref = 2,.x2_ref = -2}, .reference_number_of_answers = 2},
                                                           {{.a = 0,.b = 1,.c = 3}, {.x1 = -3,.x2 = NAN},.number_of_answers = 1,
                                                            {.x1_ref = -3,.x2_ref = NAN}, .reference_number_of_answers = 1},
                                                           {{.a = 0,.b = 0,.c = 3}, {.x1 = NAN,.x2 = NAN},.number_of_answers = 0,
                                                            {.x1_ref = NAN,.x2_ref = NAN}, .reference_number_of_answers = 0},
                                                           {{.a = 0,.b = 10000,.c = 0}, {.x1 = 0,.x2 = NAN},.number_of_answers = 1,
                                                            {.x1_ref = 0,.x2_ref = NAN}, .reference_number_of_answers = 1},
                                                           {{.a = 4,.b = 8,.c = 4}, {.x1 = -1,.x2 = NAN},.number_of_answers = 1,
                                                            {.x1_ref = -1,.x2_ref = NAN}, .reference_number_of_answers = 1},
                                                           {{.a = 9,.b = 99999,.c = 0}, {.x1 = 0,.x2 = -11111},.number_of_answers = 2,
                                                            {.x1_ref = 0,.x2_ref = -11111}, .reference_number_of_answers = 2},
                                                           {{.a = 1,.b = 0.864,.c = -0.121401}, {.x1 = 0.123,.x2 = -0.987},.number_of_answers = 2,
                                                            {.x1_ref = -0.123,.x2_ref = -0.987}, .reference_number_of_answers = 2}};
    int failed_tests = 0;
    int total_number_of_tests = 0;
    size_t number_of_equations = sizeof(array_of_test_equations) / sizeof(array_of_test_equations[0]);
    for (size_t i = 0; i < number_of_equations; i++)
    {
        total_number_of_tests++;
        failed_tests += !test_one_equation(&array_of_test_equations[i]);
    }
    printf("Total number of tests: %d\n", total_number_of_tests);
    return failed_tests;
}
