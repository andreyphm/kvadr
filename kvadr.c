#include <stdio.h>
#include <TXLib.h>
#include <math.h>
void vvod(float*, float*, float*, float*);
void vivod(float, float, float, float, float, float);
void resh(float, float, float, float*, float*, float*);
int main()
{
    float v_koef1=0, v_koef2=0, v_koef3=0, v_n_koef=0, v_Disc=0, v_kor1=0, v_kor2=0;
	printf("������� ������������ ����������� ���������. ��� ���������� ��������� ������� q q q.\n");
	vvod(&v_koef1, &v_koef2, &v_koef3, &v_n_koef);
	while (v_n_koef == 3)
    {
        resh(v_koef1, v_koef2, v_koef3, &v_Disc, &v_kor1, &v_kor2);
        vivod(v_Disc, v_kor1, v_kor2, v_koef1, v_koef2, v_koef3);
        vvod(&v_koef1, &v_koef2, &v_koef3, &v_n_koef);
    }
    printf("��������� ���������.\n");
    return 0;
}
void vivod(float Disc, float kor1, float kor2, float koef1, float koef2, float koef3)
{
    if (koef1==0)
    {
        if (koef2==0)
        {
            if (koef3==0)
                printf("������ ��������� - ����� �����.\n");
            else
                printf("��������� �� ����� �������.\n");
        }
        else
            printf("��������� ����� ���� �������, ������ %f.\n", kor1);
    }
    else
    {
        if (Disc<0)
            printf("��������� �� ����� ������� � �������������� ������.\n");
        else if (Disc==0)
            printf("��������� ����� ���� �������, ������ %f.\n", kor1);
        else
            printf("��������� ����� ��� �������: %f � %f.\n", kor1, kor2);
    }
}
void resh(float koef1, float koef2, float koef3, float *Disc, float *kor1, float *kor2)
{
    if (koef1==0)
    {
        if (koef2!=0)
            *kor1=-koef3/koef2;
    }
    else
    {
        *Disc=koef2*(koef2)-4*(koef1)*(koef3);
        if (*Disc>0)
        {
            *kor1=(-koef2+sqrt(*Disc))/(2*(koef1));
            *kor2=(-koef2-sqrt(*Disc))/(2*(koef1));
        }
        else if (*Disc==0)
            *kor1=-koef2/(2*koef1);
    }
}
void vvod(float *koef1, float *koef2, float *koef3, float *n_koef)
{
    *n_koef = scanf("%f %f %f", koef1, koef2, koef3);
}
