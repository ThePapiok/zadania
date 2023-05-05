#include <iostream>
#include <cassert>
using namespace std;

int f(int x, int n)
{
   return x-n;
}

int main(){
    int x,n,k,w;
    cin >> x;
    assert(x>=0);
    assert(x>=0 && k==k && n==n && w==w);
    k=1; n=0; w=0;
    assert(x>=n && k==1 && n==0 && w==0);
    assert(x>=n && w==n*n && k==2*n+1);
    while (n<x){
        assert(x>=n && n<x  && x-n>0 && x-n==x-n && w==n*n && k==2*n+1);
        assert(n<x  && x-n>0 && x-n==x-n && w==n*n && k==2*n+1);
        int const X=f(x,n);
        assert(n<x  && x-n>0 && x-n==x-n && w+k==n*n+k && k==2*n+1);
        w = w+k;
        assert(n<x  && x-n>0 && x-n==x-n && w==n*n+k && k==2*n+1);
        assert(n<x  && x-n>0 && x-n==x-n && w+2==n*n+k+2 && k+2==2*n+3);
        k = k+2;
        assert(n<x  && x-n>0 && x-n==x-n && w+2==n*n+k && k==2*n+3);
        assert(n<x  && x-n>0 && x-n==x-n && w==n*n+k-2 && k==2*n+3);
        assert(n<x  && x-n>0 && x-n==x-n && w==n*n+2*n+1 && k==2*n+3);
        assert(n+1<=x && X>0 && X>x-(n+1) && w==(n+1)*(n+1) && k==2*(n+1)+1);
        n = n+1;
        assert(n<=x && X>0 && X>x-n && w==n*n && k==2*n+1);
    }
    assert(n<=x && n>=x && w==n*n && k==2*n+1);
    assert(n==x && w==n*n && k==2*n+1);
    assert(w==x*x && k==2*n+1);
    assert(w==x*x);
    cout << w << endl;
}
