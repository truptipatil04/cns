#include <bits/stdc++.h>
using namespace std;

int EuclideanAlgo(int a,int b){
    int s1=1,s2=0,s,t1=0,t2=1,t;
    int r1=a,r2=b,q,r;

    cout<<"     q           r1          r2          r           t1          t2          t       "<<endl;
    while(r2>0){
        q=r1/r2;

        r=r1-q*r2;
        r1=r2;
        r2=r;

        // s=s1-q*s2;
        // s1=s2;
        // s2=s;

        t=t1-q*t2;
        t1=t2;
        t2=t;
        cout<<"     "<<q<<"           "<<r1<<"          "<<r2<<"          "<<r<<"           "<<t1<<"          "<<t2<<"          "<<t<<endl;
    }
    cout<<endl;
    
    int res=-1;
    if(r1==1){
        res=t1;
    }
    return res;
}

int main(){
    int a,b;
    cout<<"Enter number a : ";
    cin>>a;

    cout<<"Enter number b : ";
    cin>>b;

    cout<<endl;

    int ans=INT_MAX;
    if(b>a){
        ans=EuclideanAlgo(b,a);
    }else{
        ans=EuclideanAlgo(a,b);
    }

    if(ans!=-1){
        cout<<"Multiplicative inverse of "<<b<<" in "<<a<<" : "<<ans;
        if(ans<0){
            if(b>a){
                ans+=b;
            }else{
                ans+=a;
            }
            cout<<" and "<<ans<<endl;
        }
    }else{
        cout<<"Multiplicative inverse is not present."<<endl;
    }
    cout<<endl;
}