/*
1,为什么#2处输入a 1 2,而cl存的是a,不是1,；cr存的是1，不是2？
    答：在#1处把scanf("%d",&n);  改成scanf("%d\n",&n);即加一个\n，因为输入的数据格式有回车换行，而scanf要加入换行才能识别回车，
    如果不加，那么#2处element读的是回车，cl 读的是a,cr读的是1；
    这么做，#2处也得由scanf("%c %c %c",&t[i].element,&cl,&cr);加一个\n；这样做，可以实现功能，但是又有一个新问题，就是最后得加多
    一个字母才能是输入结束；
    最终解决方法：在scanf后面加个fflush(sdtin);用于清空缓冲区；具体原因得参见关于scanf的博客；
2，elment的值在哪里可以看到？
*/
#include <stdio.h>
#include <stdlib.h>

#define maxTree 10
#define elementType char
#define tree int
#define Null -1

struct treeNode{
    elementType element;
    tree left;
    tree right;
}t1[maxTree],t2[maxTree];

tree buildTree(struct treeNode t[]);

tree lsomorphism(tree r1,tree r2);

int main()
{
    tree r1;
    tree r2; //注意这里不要用 tree r1,r2;因为前面是define，这是r2就不是int类型，也不知道是什么类型
//    printf("%d",Null);
    r1 = buildTree(t1);
    r2 = buildTree(t2);

//    printf("%d %d",r1,r2);
    if(lsomorphism(r1,r2)){
        printf("Yes\n");
    }
    else{
        printf("No\n");
    }
    return 0;
}

tree buildTree(struct treeNode t[]){
    int n;
    scanf("%d\n",&n); //#1
    int root;
    if (n){
        int i;
        char cl,cr;
        int check[maxTree];
        for(i=0;i<n;i++){
            check[i] = 0;
        }
        for (i=0;i<n;i++){
            scanf("%c %c %c",&t[i].element,&cl,&cr); // #2 注意这里是t[i],不是t1[i],或者t2[i],因为是函数的代码，t1,t2是传进来的
            fflush(stdin);//刷新缓冲区
            if (cl != '-'){
                t[i].left = cl-'0';
                check[t[i].left] = 1;
            }
            else {
                t[i].left = Null;
            }
            if (cr != '-'){
                t[i].right = cr-'0';
                check[t[i].right] = 1;
            }
            else {
                t[i].right = Null;
            }
        }
        for (i=0;i<n;i++){
            if(!check[i]){
                break;
            }
        }
        root = i;
    }
    return root;
}
tree lsomorphism(tree r1,tree r2){
    if (r1 == Null && r2 == Null){
        return 1;
    }
    else if (((r1 == Null )&& (r2 != Null ))|| ((r1 != Null) && (r2 == Null))){
        return 0;
    }
    else if (t1[r1].element != t2[r2].element){
        return 0;
    }
    else if((t1[r1].left) == Null && (t2[r2].left == Null)){
        return lsomorphism(t1[r1].right,t2[r2].right);
    }
    else if((t1[r1].left != Null)&&(t2[r2].left != Null)&&((t1[t1[r1].left].element)== (t2[t2[r2].left].element))){
        return (lsomorphism(t1[r1].left,t2[r2].left)&&lsomorphism(t1[r1].right,t2[r2].right));
    }
    else{
        return (lsomorphism(t1[r1].left,t2[r2].right)&&lsomorphism(t1[r1].right,t2[r2].left));
    }
}
