#include <stdio.h>
#include <TXLib.h>
#include <math.h>
int main() {
	float a,b,c, D, x1, x2;
	printf("Введите коэффициенты квадратного уравнения: ");
	scanf("%f %f %f", &a, &b, &c);
	D=b*b-4*a*c;
    if (D<0)
        printf("Уравнение не имеет решений в действительных числах.");
    else if (D==0)
    {
        x1=(-b+sqrt(D))/(2*a);
        printf("Уравнение имеет одно решение, равное %f.", x1);
    }
    else if (D>0)
    {
        x1=(-b+sqrt(D))/(2*a);
        x2=(-b-sqrt(D))/(2*a);
        printf("Уравнение имеет два решения: %f и %f.", x1, x2);
    }
    return 0;
}
