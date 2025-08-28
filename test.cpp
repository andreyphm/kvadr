#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "test.h"
#include "font.h"

void run_test_solver(struct answers_data* answers, int argc, const char* argv[])
{
    struct test_equation_data array_of_tests[SIZE_OF_TESTS_ARRAY] = {}; //TODO calloc

    FILE* file_pointer = fopen(argv[1] , "r");
    is_input_correct(argc, argv, file_pointer);

    int total_number_of_tests = 0;
    int number_of_failed_tests = 0;

    fscanf(file_pointer, "%d\n", &total_number_of_tests);
    is_number_of_tests_correct(total_number_of_tests);

    for (int i = 0; i < total_number_of_tests; i++)
    {
        number_of_failed_tests += test_one_equation(&array_of_tests[i], answers, file_pointer);
    }

    printf(MAKE_BOLD("Number of failed tests: %d.\n\n"), number_of_failed_tests);

    fclose(file_pointer);

    return;
}

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
        printf(MAKE_BOLD_GREEN("Test passed (%lg %lg %lg).\n"),
                                test->coefficients.a, test->coefficients.b, test->coefficients.c);
        return false;
    }
}

void display_failed_message(struct test_equation_data* test, struct answers_data* answers)
{
    printf(MAKE_BOLD_RED("FAILED: equation_solver({%lg, %lg, %lg}, {%lg, %lg, %d})\n"),
                            test->coefficients.a, test->coefficients.b, test->coefficients.c,
                            test->reference_answers.x1, test->reference_answers.x2,
                            test->reference_answers.number_of_answers);

    printf(MAKE_BOLD("Our solution: %lg, %lg, %d\n\n"),
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

void is_input_correct(int argc, const char* argv[], FILE* file_pointer)
{
    if (argc != 2)
    {
        printf(MAKE_BOLD_RED("Please, use: %s file_name\n\n"), argv[0]);
        exit(EXIT_FAILURE);
    }

    if (file_pointer  == NULL)
    {
        printf(MAKE_BOLD_RED("Can't open file %s\n\n"), argv[1]);
        exit(EXIT_FAILURE);
    }

    return;
}

void is_number_of_tests_correct(int total_number_of_tests)
{
    if (total_number_of_tests > SIZE_OF_TESTS_ARRAY)
    {
        printf(MAKE_BOLD_RED("Too many tests.\n\n"));
        exit(EXIT_FAILURE);
    }
    else
    {
        return;
    }
}
