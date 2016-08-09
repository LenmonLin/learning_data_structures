/*
1,输入没有记录结点的值，只是左右孩子的索引，建立的结点需要记录结点的值吗？
答:应该要记录结点的值，结点的值就用索引值去取代，这样在后期处理出队入队的时候带来方便；
2,#1处为什么要设置null?
答：为了区分0结点时if判断无法生效，所以设置null为-1 非常巧妙
3，一直没想明白并且犯错的地方是队列的设置，考虑用数组实现循环队列，有data值，记录队首和队尾的值front和rear；
这三个值可以设置成一个结构，也可以不设置成结构，本题笔者就没设置成结构，但是data应该设置成结构，因为存进队列的元素是树结点；
也就是data值其实是存储结点，而存储data的又是一个队列数组；如果这个队列数组设置成一个结构，那么data值就是结构中的结构，
这个逻辑要理清
4,队列的队头队尾初始化要为-1，不能是0，否则数组0位置没存储东西；
5，队列出队和入队都是先移动指针再赋值，这与堆栈不一样，要注意区别；
6, #2 把tree[root]写成Queue[root]导致一直没有输出
7，#3这里的-1充分规避了结点0的问题，如果写成if（temp.left)那么0结点永远不可能入队
8.#4这里没有用fflush导致回车被读入treeLeft，从而第一个‘-’永远不会读入treeLeft,导致
    while循环不会结束,此bug花费3小时，幸运的是最后发现了；

*/
#include <stdio.h>
#include <stdlib.h>

#define maxTree 9
#define null -1
#define maxSize 10

typedef struct treeNode{
    int data;
    int left;
    int right;
}treeNode;
treeNode tree[maxTree];
treeNode Queue[maxSize];
int front=-1,rear=-1;



int buildTree(struct treeNode t[]);

void levelOrderTraversal(int root);

void enQueue(treeNode Queue[],treeNode x);

int main()
{
    int root;
    root = buildTree(tree); //通常传入数组地址即可，不用多此一举写成tree[]
//    printf("%d",root);
    levelOrderTraversal(root);
    return 0;
}

int buildTree(struct treeNode t[]){ //这里t[]与t有什么区别？因为这里t是数组，所以传入的时候正常要加t[],本来还
                                    //应该加数组的长度 int length;但是因为在宏定义的时候已经定义了maxSize，
                                    //即程序写死maxSize所以不用再定义数组长度；
    int n;
    int root;
    scanf("%d",&n);
    fflush(stdin); ///#4这里没有用fflush导致回车被读入treeLeft，从而第一个‘-’永远不会读入treeLeft,导致
                    ///while循环不会结束,此bug花费3小时，幸运的是最后发现了；

    if (n){ //这里是if不是while循环，只是确定有输入结点就执行if内的程序
        int i;
        int check[maxTree];
        for (i=0;i<n;++i){
            check[i] = 0;
        }
        char treeLeft,treeRight;
        for(i=0;i<n;++i){
            scanf("%c %c",&treeLeft,&treeRight);
            fflush(stdin);
            t[i].data = i;///记录当前节点的索引以便最后打印叶子结点使用
            if (treeLeft != '-'){
                t[i].left = treeLeft-'0';
                check[t[i].left]=1;
            }
            else{
                t[i].left = null; ///#1
            }
            if (treeRight != '-'){
                t[i].right = treeRight-'0';
                check[t[i].right]=1;
            }
            else{
                t[i].right = null;
            }
        }
        for (i=0;i<n;++i){//是按顺序查找根节点，因为输入的行数是按照结点序号的。比如除了第一行输入结点个数以外
                        //第二行就是第0个结点，第三行就是第1个结点，以此类推；
            if (!check[i]){
                break;
            }
        }
        root = i;
    }
    return root;
}

void levelOrderTraversal(int root){
    if (!root){
        return;
    }
    enQueue(Queue,tree[root]); ///#2 把tree[root]写成Queue[root]导致一直没有输出
    while(front != rear){
         //printf("刚进循环front is %d rear is %d",front,rear);
        ///出队
        treeNode temp;
        front = (front+1)%maxSize;
        temp = Queue[front];
       // printf("%d ",temp.data);
        //printf("temp.left is %d\n",temp.left);
        //printf("temp.right is %d\n",temp.right);
        if ((temp.left == null)&&(temp.right == null )){
            printf("%d ",temp.data);
        }


        ///左右孩子入队
        if(temp.left != null){  ///#3这里的-1充分规避了结点0的问题，如果写成if（temp.left)那么0结点永远不可能入队
            enQueue(Queue,tree[temp.left]);
        }
        if(temp.right != null){
            enQueue(Queue,tree[temp.right]);
        }
       // printf("front is %d rear is %d",front,rear);
    }
}

void enQueue(treeNode Queue [],treeNode x){
   // printf("(rear+1)除以maxSize is %d front is %d\n",(rear+1)%maxSize,front);
 //   printf("%d ",((rear+1)%maxSize == front));
    if ((rear+1)%maxSize == front){
        printf("队满");
        return;
    }
   // printf("rear before change %d\n",rear);
    rear = (rear+1)%maxSize;
  //  printf("rear after change %d\n",rear);
    Queue[rear]=x;
  //  printf("x is %d",x.data);
}

