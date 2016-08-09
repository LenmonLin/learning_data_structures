#include <stdio.h>
#include <stdlib.h>
/*
    1,为什么结点的定义，函数的声明这些都只能放在main函数的外面，放在里面就报错？？
        报错信息：指出Polynomial 未定义;
    2,出现了非常经典的报警提示：warning: suggest parentheses around assignment used as truth value？
        原因：判断语句中应该写 a == b，我写成 a = b
*/

typedef struct PolyNode *Polynomial;    /*用这种方式定义指针替代量，方便下面代码使用,
                                            为什么这么做，因为不论是读入链表还是操作链表相加，都是
                                            返回链表的头指针，不可能说返回头结点； */
struct PolyNode{
    int coef;
    int expon;
    struct PolyNode *link;
    };
void Attach(int c,int e,Polynomial *pRear);
Polynomial ReadPoly();
void PrintPoly();
Polynomial Add(Polynomial p1,Polynomial p2);

int main()
{
    Polynomial p1,p2,ps;
    p1 = ReadPoly();
    p2 = ReadPoly();
    ps = Add(p1,p2);
    PrintPoly(ps);
//    PrintPoly(p1);
//    PrintPoly(p2);
    return 0;
}

void Attach(int c,int e,Polynomial *pRear){ //需要修改指针，所以定义指针的指针
    Polynomial p;
    p = (Polynomial)malloc(sizeof(struct PolyNode));//注意sizeof后面要用struct PolyNode，不能用Polynomail,Polynomail代表struct PolyNode *
    p->coef = c;
    p->expon = e;
    p->link = NULL;
    (*pRear)->link = p;//横向
    *pRear = p; //纵向
}
Polynomial ReadPoly(){ //读入操作函数，不用参数
    Polynomial p,rear,temp;
    p = (Polynomial)malloc(sizeof(struct PolyNode));
    p->link = NULL;
    rear = p;
    int num,c,e;
    scanf("%d",&num);
    while (num--){
        scanf("%d %d",&c,&e);
        Attach(c,e,&rear); //传入的应该是&rear
    }
    temp = p;
    p = p->link;
    free(temp);
    return p;

}
void PrintPoly(Polynomial p){
    while(p){
        printf("%d%d ",p->coef,p->expon);
        p = p->link;
    }
}
Polynomial Add(Polynomial p1,Polynomial p2){
    Polynomial front,temp,rear;
    front = (Polynomial)malloc(sizeof(struct PolyNode));
    front->link = NULL;
    rear = front;
    int sum;
    while (p1&&p2){
        if (p1->expon>p2->expon){
            Attach(p1->coef,p1->expon,&rear);
            p1 = p1->link;
        }
        else if (p1->expon<p2->expon){
            Attach(p2->coef,p2->expon,&rear);
            p2 = p2->link;
        }
        else{
            sum = p1->coef + p2->coef;
            if (sum){
                Attach(sum,p1->expon,&rear);
                p1 = p1->link;
                p2 = p2->link;
            }
        }
    }
    if (p1){
        for(;p1!=NULL;p1=p1->link){
            Attach(p1->coef,p1->expon,&rear);
        }
    }
    if (p2){
        for(;p2!=NULL;p2=p2->link){
            Attach(p2->coef,p2->expon,&rear);
        }
    }
    rear->link = NULL;

    temp = front;
    front = front->link;
    free(temp);
    return front;
}
