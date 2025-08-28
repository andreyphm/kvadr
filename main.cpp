#include <assert.h>
#include <math.h>

#include "kvadr.h"
#include "font.h"

int main(int argc, const char* argv[])
{
    struct coefficients_data coefficients = {.a = NAN, .b = NAN, .c = NAN};
    struct answers_data answers = {.x1 = 0, .x2 = 0,.number_of_answers = ERROR_SOLUTIONS};

    int program_status = PROGRAM_CONTINUE;

    display_a_greeting();
    run_test_solver(&answers, argc, argv);

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
