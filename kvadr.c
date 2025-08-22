#include <stdio.h>
#include <TXLib.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>

const double NUMBER_CLOSE_TO_ZERO = 10e-6;

enum num_of_roots {
    INF_NUM_OF_SOLUTIONS = -1,
    NO_SOLUTIONS         = 0,
    ONE_SOLUTION         = 1,
    TWO_SOLUTIONS        = 2
};

void input_coefficients(double*, bool*);
void clear_input_buffer();

void equation_solver(double*, double*, int*);
void linear_equation_solver(double*, double*, int*);
void quadratic_equation_solver(double*, double*, int*);

int  is_close_to_zero(double);

void output_answer(double*, int);

int main()
{
    double coefficients[3] = {}, answers[2] = {};
    int number_of_answers = NO_SOLUTIONS;
    bool quit_program = false;

    while (!quit_program)
    {
        input_coefficients(coefficients, &quit_program);
        if (quit_program == true)
            continue;
        equation_solver(coefficients, answers, &number_of_answers);
        output_answer(answers, number_of_answers);
    }

    printf("                   .\n");
    return 0;
}

void input_coefficients(double *coefficients, bool *quit_program)
{
    assert (coefficients);
    assert (quit_program);

    int number_of_coefficients = 0;
    char input_row[200] = {};

    while (number_of_coefficients != 3)
    {
        printf("                                          .\n");
        number_of_coefficients = sscanf(input_row, "%lg %lg %lg", &coefficients[0], &coefficients[1], &coefficients[2]);
        if (input_row[0] == '\n')
            *quit_program = true;
            break;
        clear_input_buffer();
    }
}

void clear_input_buffer()
{
    int entered_character = 0;
    do {
        entered_character = getchar();
    } while (entered_character != '\n' && entered_character != EOF);
}

void equation_solver(double *coefficients, double *answers, int *number_of_answers)
{
    assert (coefficients);
    assert (answers);
    assert (number_of_answers);
    assert (coefficients != answers);

    if (is_close_to_zero(coefficients[0]))
        linear_equation_solver(coefficients, answers, number_of_answers);
    else
        quadratic_equation_solver(coefficients, answers, number_of_answers);
}

void linear_equation_solver(double *coefficients, double *answers, int *number_of_answers)
{
    assert (coefficients);
    assert (answers);
    assert (number_of_answers);
    assert (coefficients != answers);

    if (is_close_to_zero(coefficients[1]))
    {
        if (is_close_to_zero(coefficients[2]))
            *number_of_answers = INF_NUM_OF_SOLUTIONS;
        else
            *number_of_answers = NO_SOLUTIONS;
    }
    else
    {
        answers[0] = -coefficients[2] / coefficients[1];
        *number_of_answers = ONE_SOLUTION;
    }
}

void quadratic_equation_solver(double *coefficients, double *answers, int *number_of_answers)
{
    assert (coefficients);
    assert (answers);
    assert (number_of_answers);
    assert (coefficients != answers);

    double discriminant = coefficients[1] * coefficients[1] - 4 * coefficients[0] * coefficients[2];

    if (discriminant > 0)
    {
        answers[0] = (-coefficients[1] + sqrt(discriminant)) / (2 * coefficients[0]);
        answers[1] = (-coefficients[1] - sqrt(discriminant)) / (2 * coefficients[0]);
        *number_of_answers = TWO_SOLUTIONS;
    }
    else if (is_close_to_zero(discriminant))
    {
        answers[0] = -coefficients[1] / (2 * coefficients[0]);
        *number_of_answers = ONE_SOLUTION;
    }
    else
        *number_of_answers = NO_SOLUTIONS;
}

int is_close_to_zero (double number_being_checked)
{
    if (fabs(number_being_checked) < NUMBER_CLOSE_TO_ZERO)
        return 1;
    else
        return 0;
}

void output_answer(double *answers, int number_of_answers)
{
    assert (*answers);

    switch (number_of_answers)
    {
        case NO_SOLUTIONS:
            printf("                          .\n");
            break;
        case ONE_SOLUTION:
            printf("                            ,        %g.\n", answers[0]);
            break;
        case TWO_SOLUTIONS:
            printf("                           : %g   %g.\n", answers[0], answers[1]);
            break;
        case INF_NUM_OF_SOLUTIONS:
            printf("                 -            .\n");
        default:
            break;
    }
}
