#include <stdio.h>
/*  求最大子列和
    在线处理方法
    1，一维数组定义时要确定大小，如果要自己输入大小，scanf在前，定义数组大小在scanf之后
    2，注意初始化数组的那个for循环
    3，使用MaxSubseqSum4函数传入的是数组的地址A,传入A[]会报错，这与定义和声明不一样，注意区分
    4,在任意一个{}内的是局部变量，超出{}就不能使用大括号里面的局部变量
*/
int main ()
{
    int MaxSubseqSum4(int A[],int n);
    int n,i;
    scanf("%d",&n);
    if (n>0){
        int A[n];
        for (i=0;i<n;i++){
            scanf("%d",&A[i]);
        }
    int temp;
    temp = MaxSubseqSum4(A,n);
    printf("%d",temp);
    }

    return 0;
}

int MaxSubseqSum4(int A[],int n)
{
    int ThisSum=0,MaxSum=0;
    int i;
    for (i=0;i<n;i++){
        ThisSum += A[i];
        if (ThisSum>MaxSum){
            MaxSum = ThisSum;
        }
        else if (ThisSum < 0){
            ThisSum =0;
        }
    }
    return MaxSum;
}
