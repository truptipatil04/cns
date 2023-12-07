#include <bits/stdc++.h>
using namespace std;

bool check(int m[],int n){
    for (int i=0;i<n;i++){
        for (int j=i+1;j<n;j++)
        {
            if (__gcd(m[i],m[j]) != 1) {
                return true;
            }
        }
    }
    return false;
}

int CRT(int a[],int m[],int n){
    int x[n];
    int q,r,r1,r2,t,t1,t2;

    int M=1;
    for(int i=0;i<n;i++){
        M*=m[i];
    }

    for(int i=0;i<n;i++){
        r1=m[i];
        r2=M/m[i];
        t1=0,t2=1;

        while(r2>0){
            q=r1/r2;
            r=r1-q*r2;
            r1=r2;
            r2=r;

            t=t1-q*t2;
            t1=t2;
            t2=t;
        }

        if(r1==1){
            x[i]=t1;
        }
        if(x[i]<0){
            x[i]+=m[i];
        }
    }

    int res=0;
    for(int i=0;i<n;i++){
        res+=(a[i]*M*x[i])/m[i];
    }
    return res%M;
}

int main(){
    cout<<"Enter size : ";
    int n;
    cin>>n;

    int a[n],m[n];
    cout<<"Enter values of a : ";
    for(int i=0;i<n;i++){
        cin>>a[i];
    }cout<<endl;

    cout<<"Enter values of m : ";
    for(int i=0;i<n;i++){
        cin>>m[i];
    }cout<<endl;

    for(int i=0;i<n;i++){
        cout<<"X = "<<a[i]<<" mod("<<m[i]<<")"<<endl;
    }cout<<endl;

    if(!check(m,n)){
        cout<<"Value of X : "<<CRT(a,m,n)<<endl;
    }else{
        cout<<"Values of m are not co-prime.Thus, Solution does not exist!!!"<<endl;
    }
}