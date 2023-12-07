#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

long long modExp(long long base, long long exponent, long long modulus) {
    if (modulus == 1) return 0; 
    long long result = 1;
    base = base % modulus;
    while (exponent > 0) {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}

int prime_checker(int p) {
    if (p < 1) {
        return -1;
    } else if (p > 1) {
        if (p == 2) {
            return 1;
        }

        for (int i = 2; i < p; i++) {
            if (p % i == 0) {
                return -1;
            }
            return 1;
        }
    }
}

ll gcd(ll a, ll b)
{
    if (!a)
        return b;
    return gcd(b % a, a);
}

void RSA(int p,int q,int msg){
    long long int n=p*q;
    long long int phi=(p-1)*(q-1);
    cout<<"Phi : "<<phi<<endl;
    cout<<endl;

    long long int e;

    for(int i=2;i<=phi;i++){
        if(gcd(i,phi)==1){
            e=i;
            break;
        }
    }

    long long int j=0,d;
    while(true){
        if((j*e)%phi == 1){
            d=j;
            break;
        }
        j+=1;
    }

    cout<<"Public Key <"<<e<<", "<<n<<">"<<endl;
    long long int ct = modExp(msg, e, n);
    cout<<"Encrypted message : "<<ct<<endl;

    cout<<endl;

    cout<<"Private Key <"<<d<<", "<<n<<">"<<endl;
    long long int mes = modExp(ct, d, n);
    cout<<"Decrypted message : "<<mes<<endl;
}

int main(){
    long long int p,q;
    while(1){
        cout<<"Enter p : ";
        cin>>p;
        if (prime_checker(p) == -1){
		    cout<<"Number Is Not Prime, Please Enter Again!"<<endl;
		    continue;
        }
	    break;
    }

    while(1){
        cout<<"Enter q : ";
        cin>>q;
        if (prime_checker(q) == -1){
		    cout<<"Number Is Not Prime, Please Enter Again!"<<endl;
		    continue;
        }
	    break;
    }

    long long int msg;
    cout<<"Enter message : ";
    cin>>msg;

    cout<<endl;
    RSA(p,q,msg);

}