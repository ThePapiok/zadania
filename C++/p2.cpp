#include <iostream>
#include <cassert>
using namespace std;

int main(){
    int x,n,k,w;
    cin >> x;
    assert(x>=0);
    assert(x>=0&& 1==1 && 0==0 && 0==0&& 1>0);
    k=1; n=0; w=0;
    assert(x>=0&& k==1 && n==0 && w==0 && w==n && k>n);
    while (n<x){
        assert(n<x && x>=0 && x-n>0 && x-n==x-n);
        const int X=x-n;
        assert(n<x && x>=0 && X>0 && X==x-n);
        assert(n<x && x>=0 && X>0 && X==x-n);
        w = w+k;
        assert(n<x && x>=0 && X>0 && X==x-n);
        assert(n<x && x>=0 && X>0 && X==x-n);
        k = k+2;
        assert(n<x && x>=0 && X>0 && X==x-n);
        assert(n+1<x+1 && x>=0 && X>0 && X>x-(n+1) && k>n+1);
        n = n+1;
        assert(n<x+1 && x>=0 && X>x-n && w==n*n && k>n);
        assert(n<=x && x>=0 && X>x-n  && w==n*n);

    }
    assert(k>n);
    assert(k>2*n);
    assert(w==n*n && k==2*n+1 && n>=x && n<=x);
    assert(w==n*n && k==2*n+1 && n==x);
    assert(w==x*x);
    cout << w << endl;

    return 0;
}
