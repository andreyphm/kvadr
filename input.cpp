#include <stdio.h>
#include <assert.h>
#include <ctype.h>

#include "kvadr.h"

void input_coefficient(double* coefficient, int* program_status)
{
    assert(coefficient);
    assert(program_status);

    int extra_symbol = 0;
    int result_of_scanf = scanf("%lg", coefficient);

    if (result_of_scanf == 1)
    {
        extra_symbol = getchar();

        if (!(extra_symbol == '\n' || extra_symbol == EOF))
        {
            request_re_entry(program_status);
        }
    }
    else
    {
        request_re_entry(program_status);
    }
    return;
}

void request_re_entry(int* program_status)
{
    assert(program_status);

    int user_answer = 0;

    clear_input_buffer();

    printf("You entered the coefficients incorrectly.\n"
            "Do you want to continue the program?\n"
            "Answer 1 to start again and write something else to exit:\n");

    scanf("%d", &user_answer);

    if (user_answer != 1)
    {
        *program_status = PROGRAM_QUIT;
    }
    else
    {
        int extra_symbol = 0;
        *program_status = PROGRAM_START_AGAIN;

        do {
            extra_symbol = getchar();

            if(!isspace(extra_symbol))
            {
                *program_status = PROGRAM_QUIT;
                clear_input_buffer();
                break;
            }

        } while(extra_symbol != '\n' && extra_symbol != EOF);
    }
    return;
}

void clear_input_buffer(void)
{
    int entered_character = 0;

    do {
        entered_character = getchar();
    } while (entered_character != '\n' && entered_character != EOF);
}
