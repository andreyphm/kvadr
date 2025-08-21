#include <stdio.h>
#include <TXLib.h>
#include <math.h>
#define NUMBER_CLOSE_TO_ZERO 0.000001
#define INFINITY 999999

void input_coefficients(double[], int*);
void equation_solution(double[], double[], int*);
void linear_equation_solution(double[], double[], int*);
void quadratic_equation_solution(double[], double[], int*);
void output_answer(double[], int);
void clear_input_buffer(void);

int main()
{
    double coefficients[3] = {}, answers[2] = {};
    int number_of_coefficients = 0, number_of_answers = 0;

    while (1)
    {
        input_coefficients(coefficients, &number_of_coefficients);
        equation_solution(coefficients, answers, &number_of_answers);
        output_answer(answers, number_of_answers);
    }

    printf("Программа завершена.\n");
    return 0;
}

void output_answer(double answers[], int number_of_answers)
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
        case INFINITY:
            printf("Корень уравнения - любое число.\n");
        default:
            break;
    }
}

void equation_solution(double coefficients[], double answers[], int *number_of_answers)
{
    if (fabs(coefficients[0]) < NUMBER_CLOSE_TO_ZERO)
        linear_equation_solution(coefficients, answers, number_of_answers);
    else
        quadratic_equation_solution(coefficients, answers, number_of_answers);
}

void input_coefficients(double coefficients[], int *number_of_coefficients)
{
    *number_of_coefficients = 0;

    while (*number_of_coefficients != 3)
    {
        printf("Введите коэффициенты квадратного уравнения.\n");
        *number_of_coefficients = scanf("%lf %lf %lf", &coefficients[0], &coefficients[1], &coefficients[2]);
        clear_input_buffer();
    }
}

void linear_equation_solution(double coefficients[], double answers[], int *number_of_answers)
{
    if (fabs(coefficients[1]) < NUMBER_CLOSE_TO_ZERO)
    {
        if (fabs(coefficients[2]) < NUMBER_CLOSE_TO_ZERO)
            *number_of_answers = INFINITY;
        else
            *number_of_answers = 0;
    }
    else
    {
        answers[0] = -coefficients[2] / coefficients[1];
        *number_of_answers = 1;
    }
}

void quadratic_equation_solution(double coefficients[], double answers[], int *number_of_answers)
{
    double discriminant = 0;
    discriminant = coefficients[1] * coefficients[1] - 4 * coefficients[0] * coefficients[2];

    if (discriminant > 0)
    {
        answers[0] = (-coefficients[1] + sqrt(discriminant)) / (2 * coefficients[0]);
        answers[1] = (-coefficients[1] - sqrt(discriminant)) / (2 * coefficients[0]);
        *number_of_answers = 2;
    }
    else if (fabs(discriminant) < NUMBER_CLOSE_TO_ZERO)
    {
        answers[0] = -coefficients[1] / (2 * coefficients[0]);
        *number_of_answers = 1;
    }
    else if (discriminant < 0)
        *number_of_answers = 0;
}

void clear_input_buffer()
{
    int entered_character;
    do
    {
        entered_character = getchar();
    }   while (entered_character != '\n' && entered_character != EOF);
}
