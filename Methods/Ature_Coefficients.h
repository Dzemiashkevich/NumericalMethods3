//
// Created by Dzemiashkevich Vlad on 6.11.25.
//

#ifndef ATURE_COEFFICIENTS_H
#define ATURE_COEFFICIENTS_H
#include <cmath>
#include "CentralRect.h"
#include <fstream>
#include <iostream>
#include "Sympson.h"

inline int Factorial(int n) {
    if (n<0) throw std::invalid_argument("Factorial: n must be greater than zero");
    if (n<=1) return 1;
    return int(n*Factorial(n-1));
}
template <typename T>
std::function<T(T)> PiF (std::function<T(T, int)> f, int n, int k=0) {
    return [=](T x) {
        T fi=1.0;
        for (int i=1; i<=n; i++) {
            if (i==k){continue;}
            fi*=f(x,i);
        }
        return fi;
    };
}
template <typename T>
class Ature_Coefficients {

public:

   static T* Calc_Ature_Coefficients (int n, int alpha) {
       auto* arr=new T[n];
        std::fstream file;
       std::string filename="../Ature_CoefficientsAlpha="+std::to_string(alpha);
       filename+=".txt";
        file.open(filename, std::ios::out);
        std::function<T(T, int)> f = [=](T x, T i) {return x-i;};
       std::function<T(T)> ff;
       T a;
        for (int k=1; k<=n; k++) {
            ff= PiF(f, n, k);
            double Integral=Sympson<T>::answer(T(1-alpha), T(n+alpha), ff, 0);
            a=T(pow(-1,n-k)*Integral)/(T(n-1+2*alpha)*Factorial(k-1)*Factorial(n-k));
            arr[k-1]=a;
            file<<a<<'\n';
        }
       file.close();
       return arr;
    }
};



#endif //ATURE_COEFFICIENTS_H
