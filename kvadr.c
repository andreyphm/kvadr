#include <stdio.h>
#include <TXLib.h>
#include <math.h>
int main() {
	float a,b,c, D, x1, x2;
	printf("������� ������������ ����������� ���������: ");
	scanf("%f %f %f", &a, &b, &c);
	D=b*b-4*a*c;
    if (D<0)
        printf("��������� �� ����� ������� � �������������� ������.");
    else if (D==0)
    {
        x1=(-b+sqrt(D))/(2*a);
        printf("��������� ����� ���� �������, ������ %f.", x1);
    }
    else if (D>0)
    {
        x1=(-b+sqrt(D))/(2*a);
        x2=(-b-sqrt(D))/(2*a);
        printf("��������� ����� ��� �������: %f � %f.", x1, x2);
    }
    return 0;
}
