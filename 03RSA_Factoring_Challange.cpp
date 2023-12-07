#include <bits/stdc++.h>
using namespace std;
int m = 1e9+7;
pair<long long, long long> factorize(long long n){
    for(long long i=2; i*i<=n; i++){
        if(n % i == 0){
            return {i,n/i};
        }
    }
    return {0,0};
}


int main(){
    cout<<"Enter long number which is multiplication of 2 prime numbers :";
    long long n;
    cin>>n;

    auto ans = factorize(n);
    if(ans.first == 0 && ans.second == 0){
        cout<<"Enter number which is multiplication of 2 prime numbers \n";
    }else{
        cout << 1LL*n << " is multiplication of "<<ans.first << " and "<<ans.second<<endl;
    }
    return 0;
}