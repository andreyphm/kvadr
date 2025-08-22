#include <stdio.h>
#include <TXLib.h>
#include <math.h>
#include <stdbool.h>

const double NUMBER_CLOSE_TO_ZERO = 0.000001;
const int INF_NUM_OF_SOLUTIONS = -1;

void input_coefficients(double*, bool*);
void clear_input_buffer_and_end_of_program_check(int*);
void equation_solver(double*, double*, int*);
void linear_equation_solver(double*, double*, int*);
void quadratic_equation_solver(double*, double*, int*);
int is_close_to_zero(double*);
void output_answer(double*, int);

int main()
{
    double coefficients[3] = {}, answers[2] = {};
    int number_of_answers = 0;
    bool quit_program = false;

    while (1)
    {
        input_coefficients(coefficients, &quit_program);
        if (quit_program == true)
            break;
        equation_solver(coefficients, answers, &number_of_answers);
        output_answer(answers, number_of_answers);
    }

    printf("Программа завершена.\n");
    return 0;
}

void input_coefficients(double *coefficients, bool *quit_program)
{
    int number_of_coefficients = 0, number_of_q = 0;
    while (number_of_coefficients != 3)
    {
        printf("Введите коэффициенты квадратного уравнения. Для завершения введите q q q.\n");
        number_of_coefficients = scanf("%lf %lf %lf", &coefficients[0], &coefficients[1], &coefficients[2]);
        clear_input_buffer_and_end_of_program_check(&number_of_q);
        if (number_of_q == 3)
        {
            *quit_program = true;
            break;
        }
    }
}

void clear_input_buffer_and_end_of_program_check(int *number_of_q)
{
    int entered_character = 0;
    do
    {
        entered_character = getchar();
        if (entered_character == 'q')
            *number_of_q = *number_of_q + 1;
    }   while (entered_character != '\n' && entered_character != EOF);
}

void equation_solver(double *coefficients, double *answers, int *number_of_answers)
{
    if (is_close_to_zero(&coefficients[0]))
        linear_equation_solver(coefficients, answers, number_of_answers);
    else
        quadratic_equation_solver(coefficients, answers, number_of_answers);
}

void linear_equation_solver(double *coefficients, double *answers, int *number_of_answers)
{
    if (is_close_to_zero(&coefficients[1]))
    {
        if (is_close_to_zero(&coefficients[2]))
            *number_of_answers = INF_NUM_OF_SOLUTIONS;
        else
            *number_of_answers = 0;
    }
    else
    {
        answers[0] = -coefficients[2] / coefficients[1];
        *number_of_answers = 1;
    }
}

void quadratic_equation_solver(double *coefficients, double *answers, int *number_of_answers)
{
    double discriminant = 0;
    discriminant = coefficients[1] * coefficients[1] - 4 * coefficients[0] * coefficients[2];

    if (discriminant > 0)
    {
        answers[0] = (-coefficients[1] + sqrt(discriminant)) / (2 * coefficients[0]);
        answers[1] = (-coefficients[1] - sqrt(discriminant)) / (2 * coefficients[0]);
        *number_of_answers = 2;
    }
    else if (is_close_to_zero(&discriminant))
    {
        answers[0] = -coefficients[1] / (2 * coefficients[0]);
        *number_of_answers = 1;
    }
    else if (discriminant < 0)
        *number_of_answers = 0;
}

int is_close_to_zero (double *number_being_checked)
{
    if (fabs((*number_being_checked) < NUMBER_CLOSE_TO_ZERO))
        return 1;
    else
        return 0;
}

void output_answer(double *answers, int number_of_answers)
{
    switch (number_of_answers)
    {
        case 0:
            printf("Уравнение не имеет решений.\n");
            break;
        case 1:
            printf("Уравнение имеет одно решение, равное %f.\n", answers[0]);
            break;
        case 2:
            printf("Уравнение имеет два решения: %f и %f.\n", answers[0], answers[1]);
            break;
        case INF_NUM_OF_SOLUTIONS:
            printf("Корень уравнения - любое число.\n");
        default:
            break;
    }
}
