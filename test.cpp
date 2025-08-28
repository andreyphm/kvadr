#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "kvadr.h"

bool test_one_equation(struct test_equation_data* test, struct answers_data* answers, FILE* file_pointer)
{
    assert(test);
    assert(answers);

    char num_of_answers[MAX_LEN_STR_NUM_ROOTS] = "";

    fscanf(file_pointer, "a = %lf, b = %lf, c = %lf, x1 = %lf, x2 = %lf, number_of_answers = %s\n",
            &(test->coefficients.a), &(test->coefficients.b), &(test->coefficients.c),
            &(test->reference_answers.x1), &(test->reference_answers.x2), num_of_answers);

    test->reference_answers.number_of_answers = str_to_enum(num_of_answers);

    equation_solver(&(test->coefficients), answers);

    if (!(is_close_to_zero(answers->x1 - test->reference_answers.x1) &&
          is_close_to_zero(answers->x2 - test->reference_answers.x2) &&
          answers->number_of_answers == test->reference_answers.number_of_answers))
    {
        display_failed_message(test, answers);

        return true;
    }

    else
    {
        printf("Test passed (%lg %lg %lg).\n", test->coefficients.a, test->coefficients.b, test->coefficients.c);
        return false;
    }
}

void run_test_solver(struct answers_data* answers)
{
    struct test_equation_data array_of_tests[SIZE_OF_TESTS_ARRAY] = {};

    FILE* file_pointer = fopen("tests.txt", "r");

    assert(file_pointer);

    int total_number_of_tests = 0;
    int number_of_failed_tests = 0;

    fscanf(file_pointer, "%d\n", &total_number_of_tests);

    if (total_number_of_tests > SIZE_OF_TESTS_ARRAY)
    {
        printf("Too many tests\n");
        return;
    }

    for (int i = 0; i < total_number_of_tests; i++)
    {
        number_of_failed_tests += test_one_equation(&array_of_tests[i], answers, file_pointer);
    }

    printf("Number of failed tests: %d\n\n", number_of_failed_tests);

    fclose(file_pointer);

    return;
}

void display_failed_message(struct test_equation_data* test, struct answers_data* answers)
{
    printf("FAILED: equation_solver({%lg, %lg, %lg}, {%lg, %lg, %d})\n"
               "Our solution: %lg, %lg, %d\n\n",
        test->coefficients.a, test->coefficients.b, test->coefficients.c,
        test->reference_answers.x1, test->reference_answers.x2,
        test->reference_answers.number_of_answers,
        answers->x1, answers->x2,
        answers->number_of_answers);

    return;
}

number_of_roots str_to_enum(char* number_of_answers)
{
    if (!strncmp(number_of_answers, "INF_SOLUTIONS", strlen("INF_SOLUTIONS")))
        return INF_SOLUTIONS;
    else if (!strncmp(number_of_answers, "NO_SOLUTIONS", strlen("NO_SOLUTIONS")))
        return NO_SOLUTIONS;
    else if (!strncmp(number_of_answers, "ONE_SOLUTION", strlen("ONE_SOLUTION")))
        return ONE_SOLUTION;
    else if (!strncmp(number_of_answers, "TWO_SOLUTIONS", strlen("TWO_SOLUTIONS")))
        return TWO_SOLUTIONS;
    else
        return ERROR_SOLUTIONS;
}

