#include <stdio.h>
#include <stdlib.h>
#include <math.h>

  
  
struct shape;
struct shape_ops
{
    /*���ؼ���������*/
    float (*so_area)(struct shape*); 
    /*���ؼ�������ܳ�*/
    int (*so_perimeter)(struct shape*);
};
struct shape
{
    int* s_type;
    char* s_name;
    struct shape_ops* s_ops; /*��ӿڣ������������ʵ��*/
};

float shape_area(struct shape* s)  /*����״���*/
{
    return s->s_ops->so_area(s);  
}
int shape_perimeter(struct shape* s) /*���ܳ�*/
{
    return s->s_ops->so_perimeter(s);
}



/*������*/
struct triangle
{
    struct shape t_base;
    int t_side_a;
    int t_side_b;
    int t_side_c;
};

float triangle_area(struct shape* s)  /*������������ú��׹�ʽ*/
{
    struct triangle* t=(struct triangle*)s;
    int a=t->t_side_a;
    int b=t->t_side_b;
    int c=t->t_side_c;
    float p=(a+b+c)/2;
    return  p;//sqrt((p*(p-a)*(p-b)*(p-c)));
}
int triangle_perimeter(struct shape* s)  /*�������ܳ�*/
{
    struct triangle* t=(struct triangle*)s;
    int a=t->t_side_a;
    int b=t->t_side_b;
    int c=t->t_side_c;
    return a+b+c;
}
struct shape_ops triangle_ops=    /*�Ը�����ӿڵ�ʵ��*/
{
    triangle_area,
    triangle_perimeter,
};
struct triangle* triangle_create(int a,int b,int c)  /*����������*/
{
    struct triangle* ret=(struct triangle*)malloc(sizeof (*ret));
    ret->t_base.s_name="triangle";
    ret->t_base.s_ops=&triangle_ops;
    ret->t_side_a=a;
    ret->t_side_b=b;
    ret->t_side_c=c;
    return ret;
}









//�����塰���Σ�rectangle�����̳и��ࡰ��״����ͬ��Ҳʵ�ֵĸ����������ӿڡ�����������r_width��r_height���ֱ��ʾ���εĳ��Ϳ�
/*����*/
struct rectangle
{
    struct shape r_base;
    int r_width;
    int r_height;
};

float rectangle_area(struct shape* s)  /*�������*/
{
    struct rectangle* r=(struct rectangle*)s;
    return r->r_width*r->r_height;
}
int rectangle_perimeter(struct shape* s)/*�����ܳ�*/
{
    struct rectangle* r=(struct rectangle*)s;
    return (r->r_width+r->r_height)*2;
}
struct shape_ops rectangle_ops=      /*�Ը�����ӿڵ�ʵ��*/
{
    rectangle_area,
    rectangle_perimeter,
};

struct rectangle* rectangle_create(int width, int height)  /*��������*/
{
    struct rectangle* ret=(struct rectangle*)malloc(sizeof(*ret));
    ret->r_base.s_name="rectangle";
    ret->r_base.s_ops=&rectangle_ops;
    ret->r_height=height;
    ret->r_width=width;
    return ret;
}









int main()
{
    struct shape* s[4];
    s[0]=triangle_create(5,5,4);
    s[1]=triangle_create(3,4,5);
    s[2]=rectangle_create(10,12);
    s[3]=rectangle_create(5,8);

    int i=0;
    for(i=0;i<4;i++)
    {
        float area=shape_area(s[i]);    
        int perimeter=shape_perimeter(s[i]);
        char* name=s[i]->s_name;

        printf("name:%s ,area:%.2f ,perimeter:%d\n",name,area,perimeter);
    }
    return 0;
}