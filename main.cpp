#include <iostream>
#include <cmath>
#include <iterator>
#include <string.h>
#include <string>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <windows.h>
using namespace std;
vector <unsigned long long> divisors;
unsigned long long gcd(unsigned long long e, unsigned long long t)
{
    while (e>0)
    {
        unsigned long long f;
        f=e;
        e=t%e;
        t=f;
    }

    return t;
}
unsigned long long coprime(unsigned long long t) {
    unsigned long long e;
    for (e = 2; e < t; e++ )
    {
        if (gcd(e,t) == 1 )
        {
            return e;
        }
    }
    return -1;
}
unsigned long long mult_reverse(unsigned long long e, unsigned long long t) {
    unsigned long long d,k; k=1;
    while (1) {
        k=k+t;
        if (k%e==0) {
            d=(k/e);
            return d;
        }
    }
}
unsigned long long encrypt(long long k, long long e, long long n) {
    unsigned long long ans; ans=1;
    for (unsigned long long i=0; i<e; i++)
    {
        ans=ans*k;
        ans=ans%n;
    }
    return ans;
}
unsigned long long decrypt(long long k, long long d, long long n) {
    long long ans; ans=1;
    for (unsigned long long i=0; i<d; i++)
    {
        ans=ans*k;
        ans=ans%n;
    }
    return ans;
}
int main()
{
    system("color F5");
    setlocale(LC_ALL,"Russian");
    ios::sync_with_stdio(0);
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    unsigned long long p,q,n,t,e,d;
    unsigned long long enc[50];
    unsigned long long dec[50];
    memset(enc, 0, sizeof(enc));
    memset(dec, 0, sizeof(dec));
    string s;
    cout << "========================================================================" << endl;
    cout << "====================== RSA Encrypt/Decrypt program =====================" << endl;
    cout << "======================= Created by d3n37 (Ñ) 2021 ======================" << endl;
    cout << "========================================================================" << endl;
    cout << "============================= Alphabet in use ==========================" << endl;
    string alph="ABCDEFGHIJKLMNOPQRSTUVWXYZàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ ,.:!?";
    cout << alph << endl; int lendiv,rezhim;
    cout << "========================================================================" << endl;
    cout << "Enter N (N=PQ) (Ex. 5087857):" << endl;
    cin >> n;
    for (long long i=1; i*i<=n; i++) {
        if (n%i==0) {
            if(i*i!=n)
                divisors.push_back(i);
            divisors.push_back(n/i);
        }
    }
    sort(divisors.begin(), divisors.end());
    divisors.pop_back();
    divisors.erase(divisors.cbegin());
    lendiv=divisors.size();
    if (lendiv!=2) {
        cout << "Error! The number is decomposed into more than 2 divisors!";
        exit(0);
    }
    else {
        p=divisors[0];
        q=divisors[1];
    }
    t=(p-1)*(q-1);
    e=coprime(t);
    d=mult_reverse(e,t);
    cout << "Result of decomposing N on P and Q: P = " << p << ", Q = " << q << ";" << endl;
    cout << "Euler function: " << t << ";" << endl;
    cout << "Open key: N=" << n << ", E=" << e << ";" << endl;
    cout << "Close key: N=" << n << ", D=" << d << ";" << endl;
    rezhim=0;
    while (true) {
        cout << "Select mode:" << endl;
        cout << "Choose '1', if you want to encrypt text" << endl;
        cout << "Choose '2', if you want to decrypt text" << endl;
        cout << "Choose '3', if you want both to encrypt and to decrypt text" << endl;
        cin >> rezhim;
        if (rezhim<1 || rezhim>3) {
            cout << "Error! You have chosen an incorrect mode!" << endl;
        }
        else if (rezhim==1) {
            cout << "Your mode: " << rezhim << " - Encrypt" << endl;
            cout << "Enter the message you want to encrypt:" << endl;
            std::cin.ignore();
            std::getline(std::cin,s);
            cout << "============================ ENCRYPTED TEXT: ===========================" << endl;
            for (unsigned long long i=0; i<s.length(); i++) {
                unsigned long long f=alph.find(s[i]);
                enc[i]=encrypt(f,e,n);
                cout << enc[i] << " ";
            }
            cout << endl;
            cout << "========================================================================" << endl;
        }
        else if (rezhim==2) {
            cout << "Your mode: " << rezhim << " - Decrypt" << endl;
            cout << "You can ONLY enter the NUMBERS in this mode!" << endl;
            cout << "Enter the message you want to decrypt (ONLY NUMBERS):" << endl;
            vector<unsigned long long> c;
            unsigned long long z;
            while (cin >> z) {
                c.push_back(z);
                if (cin.get()=='\n') break;
            }
            cout << "============================ DECRYPTED TEXT: ===========================" << endl;
            for (unsigned long long i=0; i<c.size(); i++) {
                int f=c[i];
                dec[i]=decrypt(f,d,n);
                f=dec[i];
                cout << alph[f];
            }
            cout << endl;
            cout << "========================================================================" << endl;
        }
        else if (rezhim==3) {
            cout << "Your mode: " << rezhim << " - Encrypt and decrypt" << endl;
            cout << "Enter the message you want to encrypt and then decrypt:" << endl;
            std::cin.ignore();
            std::getline(std::cin,s);
            cout << "============================ ENCRYPTED TEXT: ===========================" << endl;
            for (unsigned long long i=0; i<s.length(); i++) {
                unsigned long long f=alph.find(s[i]);
                enc[i]=encrypt(f,e,n);
                cout << enc[i] << " ";
            }
            cout << endl;
            cout << "========================================================================" << endl;
            cout << "============================ DECRYPTED TEXT: ===========================" << endl;
            for (unsigned long long i=0; i<s.length(); i++) {
                unsigned long long f=enc[i];
                dec[i]=decrypt(f,d,n);
                f=dec[i]%64;
                cout << alph[f];
            }
            cout << endl;
            cout << "========================================================================" << endl;
        }
    }
}
