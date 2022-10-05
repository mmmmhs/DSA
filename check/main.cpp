#include<stdio.h>
#include<string.h>
#include <cmath>

//10^9进制
unsigned long long *A, *B, *Ans;
char *tmpA, *tmpB;
int lenA, lenB;
const unsigned long long MAX_NUM = 1000000000;

inline int max(int a, int b)
{
    return a > b ? a : b;
}
void multiply();
void input();
void output();

int main()
{

    
    int n = 0;
    scanf("%d", &n);
    while (n-- > 0)
    {
        A = new unsigned long long [600];
        B = new unsigned long long [600];
        memset(A, 0, 600 * sizeof (unsigned long long));
        memset(B, 0, 600 * sizeof (unsigned long long));
        input();
        multiply();
        output();
        delete[] A;
        delete[] B;
        delete[] Ans;
    }
    return 0;
}

void multiply()
{
    Ans = new unsigned long long [lenA + lenB + 2];
    // memset(Ans, 0, lenA + lenB + 2);
    memset(Ans, 0, (lenA + lenB + 2)  * sizeof (unsigned long long));

    for(int i = 0; i < lenA; i++)
    {
        for(int j = 0; j < lenB; j ++)
        {
            Ans[i + j] += A[i] * B[j];
            Ans[i + j + 1] += Ans[i + j] / MAX_NUM;
            Ans[i + j] = Ans[i + j] % MAX_NUM;
        }

    }

    for(int i = 0; i < lenA + lenB + 2; i ++)
    {
            Ans[i + 1] += Ans[i] / MAX_NUM;
            Ans[i] = Ans[i] % MAX_NUM;
    }

}



void output()
{

    // printf("***************output****************\n");
    // printf("%llu", A[lenA - 1]);
    // for(int i = lenA - 2; i >= 0; i --)
    //     printf("%09llu", A[i]);
    // printf("\n");
    
    // printf("%llu", B[lenB - 1]);
    // for(int i = lenB - 2; i >= 0; i --)
    //     printf("%09llu", B[i]);
    // printf("\n");

    int hi = 0;
    bool flag = 0;
    for(int i = lenA + lenB + 1; i >= 0; i --)
    {
        if(Ans[i] != 0)
        {
            printf("%llu", Ans[i]);
            hi = i;
            flag = 1;
            break;
        }
            
    }
    for(int i = hi - 1; i >= 0; i --)
        printf("%09llu", Ans[i]);
    printf("\n");

    if (!flag)
    {
        printf("0");
    }
    
}

unsigned long long stollu(char buffer[], int lo, int hi)
{
    unsigned long long base = 1, ans = 0;
    if(lo < 0)
        lo = 0;
    for(int i = hi - 1; i >= lo; i --)
    {
        ans += (buffer[i] - '0') * base;
        base *= 10;
    }
    return ans;
}


void input()
{
    tmpA = new char [5100];
    tmpB = new char [5100];
    memset(tmpA, 0, sizeof tmpA);
    memset(tmpB, 0, sizeof tmpB);

    //读入A
    scanf("%s", tmpA);
    scanf("%s", tmpB);

    int strlenA = strlen(tmpA);
    int strlenB = strlen(tmpB);
    lenA = 0;
    while(strlenA > 0)
    {
        A[lenA ++] = stollu(tmpA, strlenA - 9, strlenA);
        strlenA -= 9;
    }
    //debug
    // printf("______________A_______________\n");
    // for(int i = lenA - 1; i >= 0; i --)
    //     printf("%llu\n", A[i]);

    lenB = 0;
    while(strlenB > 0)
    {
        B[lenB ++] = stollu(tmpB, strlenB - 9, strlenB);
        strlenB -= 9;
    }
    //debug
    // printf("______________B_______________\n");
    // for(int i = lenB - 1; i >= 0; i --)
    //     printf("%llu\n", B[i]);

    delete [] tmpA;
    delete [] tmpB;
}
