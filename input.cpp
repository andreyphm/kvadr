#include <stdio.h>
#include <assert.h>
#include <ctype.h>

#include "kvadr.h"

void input_coefficient(struct coefficients_data* coefficients, struct answers_data* answers, int* program_status)
{
    assert(coefficients);
    assert(answers);
    assert(program_status);

    *program_status = PROGRAM_CONTINUE;

    const char numerate[][7] = {"first", "second", "third"};

    for (int i = 0; i <= 2; i++)
    {
        printf("Enter the %s coefficient:\n", numerate[i]);
        int result_of_scanf = scanf("%lg", &(coefficients->a) + i);
        int extra_symbol = 0;

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
        if (*program_status == PROGRAM_QUIT || *program_status == PROGRAM_START_AGAIN)
        {
            break;
        }
    }
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
