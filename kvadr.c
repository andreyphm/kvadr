#include <stdio.h>
#include <TXLib.h>
#include <math.h>

void input_coefficients(float[], int*);
void equation_solution(float[], float*, float[], int*);
void output_answer(float[], int);

int main()
{
    float coefficients[3]={}, answers[2]={}, discriminant=0;
    int number_of_coefficients=0, number_of_answers=0;

	printf("Введите коэффициенты квадратного уравнения. Для завершения программы введите q q q.\n");
	input_coefficients(coefficients, &number_of_coefficients);

	while (number_of_coefficients == 3)
    {
        equation_solution(coefficients, &discriminant, answers, &number_of_answers);
        output_answer(answers, number_of_answers);
        input_coefficients(coefficients, &number_of_coefficients);
    }

    printf("Программа завершена.\n");
    return 0;
}

void output_answer(float answers[], int number_of_answers)
{
    if (number_of_answers == 0)
        printf("Уравнение не имеет решений.\n");

    else if (number_of_answers == 1)
        printf("Уравнение имеет одно решение, равное %f.\n", answers[0]);

    else if (number_of_answers == 2)
        printf("Уравнение имеет два решения: %f и %f.\n", answers[0], answers[1]);

    else
        printf("Корень уравнения - любое число.\n");
}

void equation_solution(float coefficients[], float *discriminant, float answers[], int *number_of_answers)
{
    if (fabs(coefficients[0] - 0) < 0.00001)
    {
        if (fabs(coefficients[1] - 0) < 0.00001)
        {
            if (fabs(coefficients[2] - 0) < 0.00001)
                *number_of_answers=99999;
            else
                *number_of_answers=0;
        }
        else
        {
            answers[0] = -coefficients[2] / coefficients[1];
            *number_of_answers=1;
        }
    }
    else
    {
        *discriminant = coefficients[1] * coefficients[1] - 4 * coefficients[0] * coefficients[2];

        if (*discriminant > 0)
        {
            answers[0] = (float) (-coefficients[1] + sqrt(*discriminant)) / (2 * coefficients[0]);
            answers[1] = (float) (-coefficients[1] - sqrt(*discriminant)) / (2 * coefficients[0]);
            *number_of_answers=2;
        }
        else if (fabs(*discriminant - 0) < 0.00001)
        {
            answers[0] = -coefficients[1] / (2 * coefficients[0]);
            *number_of_answers=1;
        }
    }
}

void input_coefficients(float coefficients[], int *number_of_coefficients)
{
    *number_of_coefficients = scanf("%f %f %f", &coefficients[0], &coefficients[1], &coefficients[2]);
}
