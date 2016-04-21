/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: User
 *
 * Created on April 18, 2016, 5:58 PM
 */

#include <cstdlib>
#include <iostream>
using namespace std;

long long EEA(long long a, long long b, long long &x, long long &y);
long long getFact(long long n, long long k , long long p);
long long CRT(long long a, long long b, long long p, long long q);
/*
 * now you can see there are long long before some integer variables
 * even though they don't have to, reason is that I had overflow error 
 * and not enough time to finish it nicely
 */
int main(int argc, char** argv) {
    int n, k, p, q;
    // C(n,k) mod (pq)
    //cout << EEA(47, 7, n, k) << endl;
    //cout << n << " " << k << endl << endl;
    cin >> n >> k >> p >> q;
    if(p < q){
        int tmp = q;
        q = p;
        p = tmp;
    }
    long long fact1, fact2;
    fact1 = getFact(n, k, p);
    fact2 = getFact(n, k, q);
    //cout << fact1 << " " << fact2 << endl;
    long long res = CRT(fact2, fact1, q, p);
    if(res < 0) res = res + p*q;
    cout << res << endl;
    return 0;
}
/**
 * pretty much copied this answer and changed it to c++ code
 * note that we are working in group Z_q when calculating inner modulo
 * and then when we have answer we move to Z_pq, now this is little dangerous
 * as pq is not a prime so we cant make multiplication + mod operation as it is
 * not safe, however we can make addition which is still 
 * safe(this needs verification, i know that Z_p with multiply modulo must be prime to work,
 * but i am not sure with add modulo and I don't have time right now to check it)
 * 
 * http://math.stackexchange.com/a/130045
 */
long long CRT(long long a, long long b, long long p, long long q){
    long long pInverse, qInverse;
    EEA(p, q, pInverse, qInverse);
    if(pInverse < 0)pInverse = q + pInverse;
    //cout << " " << p << " " << pInverse << " + " << q << " " << qInverse << endl;
    //cout << a << "+" << p << "*(((" << b << " - " << a << ")*" << pInverse << ") % " << q << ")" << endl;
    return a + p*(((b - a)* pInverse) % q);
}

// Extended Euclid algorithm
long long EEA(long long a, long long b, long long &x, long long &y) {
    if(b == 0) {
       x = 1;
       y = 0;
       return a;
    }

    long long x1, y1, gcd = EEA(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}
/**
 * computes binomial coefficient C(n, k) modulo p
 * 
 * There is no problem, if n is smaller than p as there can be no 
 * multiples of p, however if p is smaller we have to work around it
 * because otherwise we get 0 which is not always the right answer.
 * 
 * We count "zeros" which can be interpreted as if upper is n! then 
 * upper = k * p^zeros, where k is some integer
 * 
 * then we subtract the lower zeros now we can end in two possible scenarios
 * either zeros == 0 then this coefficient isn't multiple of p otherwise return 0
 * 
 * @param n
 * @param k
 * @param p
 * @return 
 */
long long getFact(long long n, long long k , long long p){
long long upper, lower, zeros;
    upper = 1;
    zeros = 0;
    for(long long i = n; i > (k); --i){
        if((i % p) == 0){
            long long pom = i;
            while((pom % p) == 0){
                zeros++;
                pom /= p;
            }
            upper *= pom;
        }else{
            upper *= i;
        }
        
        upper %= p;
        
    }
    lower = 1;
    for(long long i = (n-k); i > 0; --i){
        if((i % p) == 0){
            long long pom = i;
            while((pom % p) == 0){
                zeros--;
                pom /= p;
            }
            lower *= pom;
        }else{
            lower *= i;
        }
       
        lower %= p;
    }
    if(zeros)return 0;
    long long x, y;
    EEA(p, lower, x, y);
    if(y < 0)y = p + y;
    lower = y;
    return (upper*lower)% p;
}