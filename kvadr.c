#include <stdio.h>
#include <TXLib.h>
#include <math.h>
int main() {
	float a,b,c, D;
	printf("Введите коэффициенты квадратного уравнения. Для завершения программы введите q q q.\n");
	while (scanf("%f %f %f", &a, &b, &c) == 3)
	{
        D=b*b-4*a*c;
        if (D<0)
            printf("Уравнение не имеет решений в действительных числах.\n");
        else if (D==0)
        {
            printf("Уравнение имеет одно решение, равное %f.\n", (-b+sqrt(D))/(2*a));
        }
        else if (D>0)
        {
            printf("Уравнение имеет два решения: %f и %f.\n", (-b+sqrt(D))/(2*a), (-b-sqrt(D))/(2*a));
        }
    }
    printf("Удачи!");
    return 0;
}
