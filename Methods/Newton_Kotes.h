//
// Created by Dzemiashkevich Vlad on 6.11.25.
//

#ifndef NEWTON_KOTES_H
#define NEWTON_KOTES_H
#include "GeneralInteg.h"
#include "Ature_Coefficients.h"

template  <typename T>
class Newton_Kotes:public General_Integ<T> {
    int alpha;
    int n;
    T* arr;
    Newton_Kotes(T a, T b, std::function<T(T)> f,int alpha, int n, T app_err=1e-5 ): General_Integ<T>(a, b, f, 0, app_err) {
        this->alpha=alpha;
        this->n=n;
    }
    public:
    static T answer(T a, T b, std::function<T(T)> f,  int alpha, int n=3, T app_err=1e-5) {

        Newton_Kotes g (a,b,f,alpha,n, app_err);
        g.arr=Ature_Coefficients<T>::Calc_Ature_Coefficients(n, alpha);
        g.h=(b-a)/(n-1+alpha);
        T R1=0;
        T R0=0;
        T xhalf=(g.a+g.b)/2;
        T dxhalf=(g.b-g.a)/2;
        for (;;){
            for (int k=0;k<n;++k) {
                g.I1+=g.arr[k]*f(g.a+k*g.h);
            }
            g.I1*=(g.b-g.a);
            R1=g.I1-g.I0;
            if (n%2) {
                g.gamma=n;
            }
            else{g.gamma=n+1;}
            return g.I1;
        }
    }
};



#endif //NEWTON_KOTES_H
