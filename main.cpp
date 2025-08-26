#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "kvadr.h"

int main(void)
{
    struct equation_data equation =
    {
        .coefficients = {.a = NAN, .b = NAN, .c = NAN},
        .answers = {.x1 = NAN, .x2 = NAN},
        .number_of_answers = NO_SOLUTIONS
    };

    int program_status = PROGRAM_CONTINUE;
    const char numerate[][7] = {"first", "second", "third"};

    printf("Quadratic equation solver\n"
           "# (c) andreyphm, 2025\n\n");

    int number_of_failed_tests = run_test_solver();
    printf("Number of failed tests: %d\n", number_of_failed_tests);

    while (program_status != PROGRAM_QUIT)
    {
        program_status = PROGRAM_CONTINUE;
        int i = 0;

        for (i = 0; i <= 2; i++)
        {
            printf("Enter the %s coefficient:\n", numerate[i]);
            input_coefficient(&(equation.coefficients.a) + i, &program_status);

            if (program_status == PROGRAM_QUIT || program_status == PROGRAM_START_AGAIN)
            {
                break;
            }
        }
        if (program_status == PROGRAM_QUIT || program_status == PROGRAM_START_AGAIN)
        {
            continue;
        }
        equation_solver(&equation);
        output_answer(&equation);
    }

    printf("Program completed.\n");
    return 0;
}
