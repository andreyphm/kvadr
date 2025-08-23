#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

const double NUMBER_CLOSE_TO_ZERO = 10e-12;

enum num_of_roots {
    INF_NUM_OF_SOLUTIONS = -1,
    NO_SOLUTIONS         =  0,
    ONE_SOLUTION         =  1,
    TWO_SOLUTIONS        =  2
};

void input_coefficients(double* coefficients, bool* quit_program);
void clear_input_buffer(void);
void request_re_entry(bool* introduced_yes, bool* introduced_no);

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
    bool quit_program = false;

    printf("Quadratic equation solver\n"
           "# (c) andreyphm, 2025\n\n");

    while (!quit_program)
    {
        input_coefficients(equation.coefficients, &quit_program);

        if (quit_program == true) {
            continue;
        }

        equation_solver(equation.coefficients, equation.answers, &equation.number_of_answers);
        output_answer(equation.answers, equation.number_of_answers);
    }

    printf("Program completed.\n");
    return 0;
}

void input_coefficients(double* coefficients, bool* quit_program)
{
    assert(coefficients);
    assert(quit_program);

    int  number_of_coefficients = 0;
    bool introduced_yes = false, introduced_no = false;

    while (number_of_coefficients != 3)
    {
        printf("Enter the coefficients:\n");
        number_of_coefficients = scanf("%lg %lg %lg", &coefficients[0], &coefficients[1], &coefficients[2]);

        if (number_of_coefficients != 3)
        {
            clear_input_buffer();
            request_re_entry(&introduced_yes, &introduced_no);

            if (introduced_yes)
            {
                *quit_program = true;
                break;
            }
            else if (introduced_no) {
                continue;
            }
        }
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
    assert(!isnan((float) coefficients[0]));
    assert(!isnan((float) coefficients[1]));
    assert(!isnan((float) coefficients[2]));

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

void request_re_entry(bool *introduced_yes, bool *introduced_no)
{
    char input_row[100] = {};

    printf("You entered the coefficients incorrectly.\n"
                   "Do you want to exit the program?\n"
                   "Answer YES or NO:\n");

    while (!(*introduced_yes || *introduced_no))
    {
        fgets(input_row, 100, stdin);

        if (strncmp(input_row, "YES", 3) == 0) {
            *introduced_yes = true;
        }
        else if (strncmp(input_row, "NO", 2) == 0) {
            *introduced_no = true;
        }
        else {
            printf("Please, write YES to exit the program and NO to continue entering coefficients:\n");
        }
    }
    return;
}

void check_minus_before_zero (double* number_being_checked)
{
    if (is_close_to_zero(*number_being_checked)) {
        *number_being_checked = fabs(*number_being_checked);
    }
    return;
}
