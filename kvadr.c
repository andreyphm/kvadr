#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

const double NUMBER_CLOSE_TO_ZERO = 10e-12;

enum num_of_roots
{
    INF_NUM_OF_SOLUTIONS = -1,
    NO_SOLUTIONS         =  0,
    ONE_SOLUTION         =  1,
    TWO_SOLUTIONS        =  2
};

enum program_what_to_do
{
    PROGRAM_QUIT         = -1,
    PROGRAM_START_AGAIN  =  0,
    PROGRAM_CONTINUE     =  1
};

void input_coefficient(double* coefficients, int* program_status);
void clear_input_buffer(void);
void request_re_entry(int* program_status);

void equation_solver(double* coefficients, double* answers, int* number_of_answers);
void linear_equation_solver(double* coefficients, double* answers, int* number_of_answers);
void quadratic_equation_solver(double* coefficients, double* answers, int* number_of_answers);

int  is_close_to_zero(double number_being_checked);
void check_minus_before_zero (double* number_being_checked);

void output_answer(double* answers, int number_of_answers);

struct equation_parameters {
    double coefficients[3] = {NAN, NAN, NAN};
    double answers[2] = {NAN, NAN};
    int number_of_answers = NO_SOLUTIONS;
} equation;

int main(void)
{
    int program_status = PROGRAM_CONTINUE;
    const char numerate[3][7] = {"first", "second", "third"};

    printf("Quadratic equation solver\n"
           "# (c) andreyphm, 2025\n\n");

    while (program_status != PROGRAM_QUIT)
    {
        program_status = PROGRAM_CONTINUE;
        int i = 0;
        for (i = 0; i <= 2; i++)
        {
            printf("Enter the %s coefficient:\n", numerate[i]);
            input_coefficient(&equation.coefficients[i], &program_status);
            if (program_status == PROGRAM_QUIT || program_status == PROGRAM_START_AGAIN)
            {
                break;
            }
        }
        if (program_status == PROGRAM_QUIT || program_status == PROGRAM_START_AGAIN)
        {
            continue;
        }
        equation_solver(equation.coefficients, equation.answers, &equation.number_of_answers);
        output_answer(equation.answers, equation.number_of_answers);
    }

    printf("Program completed.\n");
    return 0;
}

void input_coefficient(double* coefficients, int* program_status)
{
    assert(coefficients);
    assert(program_status);

    int extra_symbol = 0;
    int result_of_scanf = scanf("%lg", coefficients);
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

    int user_answer = 0, extra_symbol = 0;

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
        extra_symbol = getchar();
        if (extra_symbol == '\n' || extra_symbol == EOF)
        {
            *program_status = PROGRAM_START_AGAIN;
        }
        else
            *program_status = PROGRAM_QUIT;
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

void equation_solver(double* coefficients, double* answers, int* number_of_answers)
{
    assert(coefficients);
    assert(answers);
    assert(number_of_answers);
    assert(coefficients != answers);
    assert(!isnan((double) coefficients[0]));
    assert(!isnan((double) coefficients[1]));
    assert(!isnan((double) coefficients[2]));

    if (is_close_to_zero(coefficients[0])) {
        linear_equation_solver(coefficients, answers, number_of_answers);
    }
    else {
        quadratic_equation_solver(coefficients, answers, number_of_answers);
    }
    return;
}

void linear_equation_solver(double* coefficients, double* answers, int* number_of_answers)
{
    assert(coefficients);
    assert(answers);
    assert(number_of_answers);
    assert(coefficients != answers);

    if (is_close_to_zero(coefficients[1]))
    {
        if (is_close_to_zero(coefficients[2])) {
            *number_of_answers = INF_NUM_OF_SOLUTIONS;
        }
        else {
            *number_of_answers = NO_SOLUTIONS;
        }
    }
    else
    {
        answers[0] = -coefficients[2] / coefficients[1];
        check_minus_before_zero(&answers[0]);
        *number_of_answers = ONE_SOLUTION;
    }
    return;
}

void quadratic_equation_solver(double* coefficients, double* answers, int* number_of_answers)
{
    assert(coefficients);
    assert(answers);
    assert(number_of_answers);
    assert(coefficients != answers);

    double discriminant = coefficients[1] * coefficients[1] - 4 * coefficients[0] * coefficients[2];

    if (discriminant > 0)
    {
        answers[0] = (-coefficients[1] + sqrt(discriminant)) / (2 * coefficients[0]);
        answers[1] = (-coefficients[1] - sqrt(discriminant)) / (2 * coefficients[0]);
        check_minus_before_zero(&answers[0]);
        check_minus_before_zero(&answers[1]);
        *number_of_answers = TWO_SOLUTIONS;
    }
    else if (is_close_to_zero(discriminant))
    {
        answers[0] = -coefficients[1] / (2 * coefficients[0]);
        check_minus_before_zero(&answers[0]);
        *number_of_answers = ONE_SOLUTION;
    }
    else
        *number_of_answers = NO_SOLUTIONS;
    return;
}

int is_close_to_zero (double number_being_checked)
{
    return (fabs(number_being_checked) < NUMBER_CLOSE_TO_ZERO);
}

void output_answer(double* answers, int number_of_answers)
{
    assert(answers);

    switch (number_of_answers)
    {
        case NO_SOLUTIONS:
            printf("The equation has no solutions.\n");
            break;
        case ONE_SOLUTION:
            printf("The equation has one solution: %lg.\n", answers[0]);
            break;
        case TWO_SOLUTIONS:
            printf("The equation has two solutions: %lg and %lg.\n", answers[0], answers[1]);
            break;
        case INF_NUM_OF_SOLUTIONS:
            printf("The root of the equation is any number.\n");
            break;
        default:
            printf("Input error");
            break;
    }
    return;
}

void check_minus_before_zero (double* number_being_checked)
{
    assert(number_being_checked);

    if (is_close_to_zero(*number_being_checked)) {
        *number_being_checked = fabs(*number_being_checked);
    }
    return;
}
