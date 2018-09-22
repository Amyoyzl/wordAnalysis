#include <stdio.h>
#include <string.h>

int isLetter(char c);
int isDigit(char c);
int scanner(void);
void insertNumber(int num);
void insertMark(char *token);
int isChar(char c);

// 代码段，单词 ，单个字符
char prog[2000],token[20],ch;
// 标记号，字符指针，数字
int syn,p,m,n,num;
// 常量表
int nLen;
int number[200];
// 标识符表
int mLen;
char mark[100][20];
// 保留字
char *rwtab[32] = {"auto","break","case","char","const",
                    "continue","default","do","double","else",
                    "enum","extern","float","for","goto",
                    "if","int","long","register","return",
                    "short","signed","sizeof","static","struct",
                    "switch","typedef","union","unsigned","void",
                    "volatile","while"};
// 符号表
char charstb[27] = { '+', '-', '>', '<', '=', '&', '|', '~', '^', '*', '/', '%', '!',
                     '?', ':', ',', '.', ';', '#', '\'', '"', '[', ']', '{', '}','(',')'};

int main(){
    p = 0;
    nLen = 0;
    mLen = 0;
    printf("please input a string(end with '$'):\n");

    do{
        scanf("%c",&ch);
        prog[p++] = ch;
    }while(ch!='$');

    p = 0;
    do{
        syn = scanner();
        if(syn>0&&syn<=32){
            printf("保留字：(%s  %2d)\n",rwtab[syn-1],syn);
        }
        else if(syn == 48){
            printf("标识符：(%s)\n",token);
        }
        else if(syn == 49){
            printf("常数：(%d)\n",num);
        }
        else if(syn>=50&&syn<=76){
            printf("符号：('%c'  %d)\n",prog[p-1],syn);
        }
        else if(syn>76){
            printf("符号：('%s'  %d)\n",token,syn);
        }
        else{
            printf("结束\n");
            break;
        }
    }while(syn!=0);
    printf("常数表：\n");
    for(n=0;n<nLen;n++){
        printf("%d\t",number[n]);
        if((n+1)%6==0)
            printf("\n");
    }
    printf("\n标识符：\n");
    for(n=0;n<mLen;n++){
        printf("%s\t",mark[n]);
        if((n+1)%6==0)
            printf("\n");
    }
	return 0;
}

/* 1.保留字返回1-32
   2.标识符返回48
   3.常数返回49
   4.单个字符返回50-76
   5.双字符返回77~96
   6.为$时返回0
   7.其他情况为-1
*/
int scanner(){
    num = 0;
    for(m=0;m<20;m++)
        token[m++] = ' ';
    ch = prog[p++];
    m = 0;
	while((ch==' ')||(ch=='\n'))
		ch=prog[p++];

    if(ch=='$') {
        return 0;
    }

    else if(isLetter(ch)){
        while(isLetter(ch)||isDigit(ch)){
            token[m++] = ch;
            ch = prog[p++];
        }
        p--;
        token[m++] = '\0';
        // 判断是否是保留字
        for(n=0;n<32;n++){
            if(strcmp(token,rwtab[n])==0){
                return n+1;
            }
        }

         // 将单词插入标识符表中
        insertMark(token);
        return 48;
    }

    else if(isDigit(ch)){
        while(isDigit(ch)){
            num = num*10+ch-'0';
            ch = prog[p++];
        }
        p--;
        // 将数字插入常数表中
        insertNumber(num);
        return 49;
    }

    else if(isChar(ch)>=0){
        int t = 0;
        m = isChar(ch);
        token[0] = ch;
        // 可能是双符号
        if(m>=0&&m<=12){
            ch = prog[p++];
            token[1] = ch;
            token[2] = '\0';
            t = isChar(ch);
            ch = prog[p];
            if(t==4)
                return m+77;
            else if(m!=4&&m==t)
                return m+90;
            else if(m==1&&t==2)
                return 94;
            // 是单符号
            else{
                p--;
                ch = prog[p];
                return m+50;
            }
        }
        // 是单符号
        else{
            ch = prog[p];
         //   printf("------  %c  %d\n",ch,p);
            return m + 50;
        }
    }

    else{
        return -1;
    }
}

void insertMark(char *token){
    int i=0;
    while(i<mLen){
        if(strcmp(token,mark[i])==0)
            return;
        i++;
    }
    strcpy(mark[mLen++],token);
}

void insertNumber(int num){
    int i = 0;
    while(i<nLen){
        if(number[i]==num)
            return;
        i++;
    }
    number[nLen++] = num;
}

int isLetter(char c){
    if((c >= 'A' && c <='Z')||(c >='a'&& c <='z')){
        return 1;
    }
    return 0;
}

int isDigit(char c){
    if(c >= '0' && c <= '9'){
        return 1;
    }
    return 0;
}

// 返回字符所在符号表的下标
int isChar(char c){
    int i=0;
    for(;i<27;i++){
        if(c==charstb[i]){
            return i;
        }
    }
    return -1;
}
