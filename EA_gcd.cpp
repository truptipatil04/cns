#include <bits/stdc++.h>
using namespace std;

int main(){
	int a,b;
    cout<<"Enter 1st number : ";
    cin>>a;

    cout<<"Enter 2nd number : ";
    cin>>b;
    
    cout<<"   q         r1          r2           r      "<<endl;
    int q,r1,r2,r;
    r1=a,r2=b;
    while(r2>0){
        q=r1/r2;
        r=r1-q*r2;
        r1=r2;
        r2=r;
    cout<<"   "<<q<<"         "<<r1<<"          "<<r2<<"           "<<r<<endl;
    }
    
    cout<<endl;
	cout << "GCD(" << a << ", " << b << ") = "<<r1<<endl;
	return 0;
}
