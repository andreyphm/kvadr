#include <assert.h>
#include <math.h>
#include <stdbool.h>

#include "kvadr.h"
#include "font.h"

int main(int argc, const char* argv[])
{
    bool do_tests = true;
    FILE* file_pointer = fopen(argv[1] , "rb");
    parse_argc_argv(argc, argv, &do_tests, file_pointer);

    struct coefficients_data coefficients = {.a = NAN, .b = NAN, .c = NAN};
    struct answers_data answers = {.x1 = NAN, .x2 = NAN,.number_of_answers = ERROR_SOLUTIONS};

    int program_status = PROGRAM_CONTINUE;

    display_a_greeting();

    if (do_tests)
    {
        run_test_solver(&answers, file_pointer);
    }

    while (program_status != PROGRAM_QUIT)
    {
        input_coefficient(&coefficients, &answers, &program_status);

        if (program_status == PROGRAM_QUIT || program_status == PROGRAM_START_AGAIN)
        {
            continue;
        }

        equation_solver(&coefficients, &answers);
        output_answer(&answers);
    }

    program_completed();

    return 0;
}

void display_a_greeting(void)
{
    printf(MAKE_BOLD("Quadratic equation solver\n"
                     "Meow # (c) andreyphm, 2025\n\n"));
    return;
}

void program_completed(void)
{
    printf(MAKE_BOLD("Program completed. COMMIT GITHUB\n"));

    return;
}

void parse_argc_argv(int argc, const char* argv[], bool* do_tests, FILE* file_pointer)
{
    if (argc != 2)
    {
        printf(MAKE_BOLD_RED("Please, use: %s file_name to do tests.\n\n"), argv[0]);
        *do_tests = false;

        return;
    }
    else if (file_pointer  == NULL)
    {
        printf(MAKE_BOLD_RED("Can't open file %s\n\n"), argv[1]);
        *do_tests = false;

        return;
    }
    else
    {
        return;
    }
}
