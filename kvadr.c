#include <stdio.h>
#include <TXLib.h>
#include <math.h>
int main() {
	float a,b,c, D;
	printf("������� ������������ ����������� ���������. ��� ���������� ��������� ������� q q q.\n");
	while (scanf("%f %f %f", &a, &b, &c) == 3)
	{
        D=b*b-4*a*c;
        if (D<0)
            printf("��������� �� ����� ������� � �������������� ������.\n");
        else if (D==0)
        {
            printf("��������� ����� ���� �������, ������ %f.\n", (-b+sqrt(D))/(2*a));
        }
        else if (D>0)
        {
            printf("��������� ����� ��� �������: %f � %f.\n", (-b+sqrt(D))/(2*a), (-b-sqrt(D))/(2*a));
        }
    }
    printf("�����!");
    return 0;
}
