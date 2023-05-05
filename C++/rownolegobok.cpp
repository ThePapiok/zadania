#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
    float x[5],y[5];
    int i=0;
    while(scanf("%f %f",&x[i],&y[i])!=EOF)
    {
        i++;
        if(i==4)
        {
            x[4]=(x[0]+x[3])-x[1];
            y[4]=(y[0]+y[3])-y[1];
            printf("%.3f %.3f\n", x[4],y[4]);
            i=0;
        }

    }
    return 0;
}
