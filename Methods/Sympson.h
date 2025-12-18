//
// Created by Dzemiashkevich Vlad on 6.11.25.
//

#ifndef SYMPSON_H
#define SYMPSON_H
#include <cmath>
#include <functional>
#include <__math/exponential_functions.h>
#include <fstream>
#include <iostream>
#include "GeneralInteg.h"



template <typename T>
class Sympson:public General_Integ<T> {
public:
    Sympson(T a, T b, std::function<T(T)> f,T h0,T app_err, int gamma):General_Integ<T>(a,b,f,h0, app_err, gamma){}
    static T answer(T a, T b, std::function<T(T)> f,int show_graphs=1, T app_err=1e-7) {
        int gamma=4;
        if (a==0) {
           a=app_err;
        }
        std::fstream fileR_k;
        std::fstream fileGamma_k;
        T h0=(b-a)/11;
        Sympson<T> g( a, b, f, h0, app_err, gamma);
        T r=2, R1=0, lg_R1=0,  R0=0, lg_R0=0, lg_nk0=0, lg_nk=0, xi0=g.a, gamma_k=0;
        if (show_graphs==1) {
            fileR_k.open("../SympsonR_k.txt", std::ios::out);
            fileGamma_k.open("../SympsonGamma_k.txt", std::ios::out);
            if (!fileR_k.is_open() || !fileGamma_k.is_open()) {
                std::cerr << "Ошибка: не удалось открыть файлы для записи!\n";
                std::cerr << "Текущая директория: " << std::filesystem::current_path() << "\n";
            }


        }
        T h=(g.b-g.a);
        g.I0=(f(g.a+h)+4*f((2*g.a+h)/2)+f(g.a))*h/6.;
        for (int i=2; ;i*=2 ) {
            g.I1=0;
            h=(g.b-g.a)/i;
            for ( int step=0; step<i; ++step) {
                g.I1+=(f(g.a+(step+1)*h)+4*f((2*g.a+(2*step+1)*h)/2)+f(g.a+step*h))*h/6;
            }


            R1=(g.I1-g.I0)/3;

            if (abs(R1)<app_err) {
                break;
            }

            lg_nk=std::log(i);

            if (show_graphs==1 && i>0) {
                lg_R1=safe_log(abs(R1));
                fileR_k<<("%d", lg_R1)<<"\t"<<lg_nk<<"\n";
                fileGamma_k<<("%d",safe_log((R0)/R1))/ safe_log(2)<<"\t"<<(lg_nk+lg_nk0)/2<<"\n";
            }


            R0=R1;
            lg_nk0=lg_nk;
            g.I0=g.I1;
        }
    if (show_graphs==1) {
        fileR_k.close();
        fileGamma_k.close();
        system("gnuplot -e \"set terminal png; set output '../SympsonR_k.png' ; plot '../SympsonR_k.txt' using 2:1 with linespoints\"");
        system("gnuplot -e \"set terminal png; set output '../SympsonGamma_k.png' ; plot '../SympsonGamma_k.txt' using 2:1 with linespoints\"");
    }
        return g.I1+R1;
    }
};



#endif //SYMPSON_H
