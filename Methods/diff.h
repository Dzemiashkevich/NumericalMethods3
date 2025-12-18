//
// Created by Dzemiashkevich Vlad on 10.10.25.
//

#ifndef DIFF_H
#define DIFF_H
#include <functional>
#include <cmath>

template <typename T>
class diff {
    public:
    static T differ(std::function<T(T)> f, T oldx, T x, int r){
        double k=0;
        if (r<3) k=r/3.;
        else k=1;
        double h=pow((10e-16), 1/3.)*pow(abs(x-oldx), k);
        return (f(h+x)-f(x-h))/(2*h);
    }
    static T differ(std::function<T(T)> f,  T x){
        double h=1e-10;
        return (f(h+x)-f(x-h))/(2*h);
    }

    static T differ2(std::function<T( T)> f, T oldx, T x, int r){
        double k=0;
        if (r<3) k=r/3.;
        else k=1;
        T h=pow((10e-16), 1/3.)*pow(abs(x-oldx), k);
        return (f(2*h+x)+f(x-2*h)-2*f(x))/(4*h*h);
    }
    static T differ2(std::function<T(T)> f, T x) {
        double h=1e-5;
        return (f(2*h+x)+f(x-2*h)-2*f(x))/(4*h*h);
    }
};



#endif //DIFF_H
