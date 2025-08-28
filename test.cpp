#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "kvadr.h"

int test_one_equation(struct test_equation_data* test, struct answers_data* answers, FILE* file_pointer)
{
    assert(test);
    assert(answers);

    char num_of_answers_str[40] = "";

    fscanf(file_pointer, "a = %lg, b = %lg, c = %lg, x1 = %lg, x2 = %lg, number_of_answers = %s\n",
            &(test->coefficients.a), &(test->coefficients.b), &(test->coefficients.c),
            &(test->reference_answers.x1), &(test->reference_answers.x2), num_of_answers_str);

    test->reference_answers.number_of_answers = str_to_enum(num_of_answers_str);

    equation_solver(&(test->coefficients), answers);

    if (!(is_close_to_zero(answers->x1 - test->reference_answers.x1) &&
          is_close_to_zero(answers->x2 - test->reference_answers.x2) &&
          answers->number_of_answers == test->reference_answers.number_of_answers))
    {
        printf("FAILED: equation_solver({%lg, %lg, %lg}, {%lg, %lg, %d})\n"
               "Our solution: %lg, %lg, %d\n\n",
        test->coefficients.a, test->coefficients.b, test->coefficients.c,
        test->reference_answers.x1, test->reference_answers.x2,
        test->reference_answers.number_of_answers,
        answers->x1, answers->x2,
        answers->number_of_answers);

        return 1;
    }

    else
    {
        return 0;
    }
}

void run_test_solver(struct answers_data* answers)
{
    struct test_equation_data array_of_tests[1];

    FILE* file_pointer = fopen("tests.txt", "r");
    int total_number_of_tests = 0;
    int number_of_failed_tests = 0;

    fscanf(file_pointer, "%d\n", &total_number_of_tests);

    for (int i = 0; i < total_number_of_tests; i++)
    {
        number_of_failed_tests += test_one_equation(&array_of_tests[i], answers, file_pointer);
    }

    printf("Number of failed tests: %d\n", number_of_failed_tests);

    fclose(file_pointer);

    return;
}

number_of_roots str_to_enum(char* num_of_answers_str)
{
    assert(num_of_answers_str);

    if (!strncmp(num_of_answers_str, "INF_NUM_OF_SOLUTIONS", 21))
        return INF_NUM_OF_SOLUTIONS;

    else if (!strncmp(num_of_answers_str, "NO_SOLUTIONS", 13))
        return NO_SOLUTIONS;

    else if (!strncmp(num_of_answers_str, "ONE_SOLUTION", 13))
        return ONE_SOLUTION;

    else if (!strncmp(num_of_answers_str, "TWO_SOLUTIONS", 14))
        return TWO_SOLUTIONS;

    else
        printf("str_to_enum error\n");
        return NO_SOLUTIONS;
}

