//
// Created by Dzemiashkevich Vlad on 6.11.25.
//

#ifndef GENERALINTEG_H
#define GENERALINTEG_H
#include <functional>
#include "diff.h"

inline double safe_log(double x) {
    if (x<0) {
        return 0;
    }
    else {
        return std::log(x);
    }

}

template <typename T>
class General_Integ {
public:
    T a, b, h, app_err, I1, I0, gamma ;
    std::function<T(T)> f;
    std::vector<std::pair<T,T>> gammak_vs_nk, err_vs_nk ;
    General_Integ() {}
    General_Integ(T a, T b, std::function<T(T)> f, T h=0.0005, T app_err=1e-5, int gamma=1) {
        this->a = a;
        this->b = b;
        this->h = h;
        this->app_err = app_err;
        if ((this->app_err==0 && this->h==0) || (this->app_err==0)) {
            throw std::invalid_argument("Wrong arguments");
        }
        this->f = f;
        I1 = 0;
        I0 = 0;
        gammak_vs_nk = std::vector<std::pair<T,T>>();
        err_vs_nk = std::vector<std::pair<T,T>>();

    }



};



#endif //GENERALINTEG_H
