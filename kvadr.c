#include <stdio.h>
#include <TXLib.h>
#include <math.h>
void vvod(float koef1, float koef2, float koef3, float n_koef);
void vivod(float Disc, float kor1, float kor2);
void resh(float koef1, float koef2, float koef3, float Disc);
int main()
{
    float n_koef;
	printf("Введите коэффициенты квадратного уравнения. Для завершения программы введите q q q.\n");
	vvod();
	while (n_koef == 3)
    {
        resh();
        vivod();
        vvod();
    }
    printf("Удачи!");
    return 0;
}
void vivod(float Disc, float kor1, float kor2)
{
    if Disc<0
        printf("Уравнение не имеет решений в действительных числах.\n");
    else if Disc==0
        printf("Уравнение имеет одно решение, равное %f.\n", kor1);
    else if Disc>0
        printf("Уравнение имеет два решения: %f и %f.\n", kor1, kor2);
}
void resh(float koef1, float koef2, float koef3, float Disc)
{
    Disc=koef2*koef2-4*koef1*koef3;
    if Disc>0
    {
        kor1=(-koef2+sqrt(Disc))/(2*koef1);
        kor2=(-koef2-sqrt(Disc))/(2*koef1);
    }
    else if Disc==0
        kor1=(-koef2)/(2*koef1);
}
void vvod(float koef1, float koef2, float koef3, float n_koef)
{
    n_koef = scanf("%f %f %f", &koef1, &koef2, &koef3);
}
