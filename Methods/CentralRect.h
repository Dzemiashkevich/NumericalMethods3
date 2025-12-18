//
// Created by Dzemiashkevich Vlad on 6.11.25.
//

#ifndef CENTRALRECT_H
#define CENTRALRECT_H
#include "GeneralInteg.h"
#include "diff.h"
#include <cmath>
#include <fstream>
#include <iostream>


template <typename T>
class CentralRect: public General_Integ<T> {
public:
    CentralRect(T a, T b, std::function<T(T)> f,T h0,T app_err, int gamma):General_Integ<T>(a,b,f,h0, app_err, gamma){}
    static T answer(T a, T b, std::function<T(T)> f,int show_graphs=1, T app_err=1e-10) {

        int gamma=2;
        int MaxIterations=10000000;
        double h=0.0;
        CentralRect g( a, b, f, h, app_err, gamma);
        T r=2, R1=0, lg_R1=0,  R0=0, lg_R0=0, lg_nk0=0, lg_nk=0, xi0=g.a, gamma_k=0;
        std::fstream fileR_k;
        std::fstream fileGamma_k;
        if (show_graphs==1) {
            fileR_k.open("../CentralRectR_k.txt", std::ios::out);
            fileGamma_k.open("../CentralRectGamma_k.txt", std::ios::out);
            if (!fileR_k.is_open() || !fileGamma_k.is_open()) {
                std::cerr << "Ошибка: не удалось открыть файлы для записи!\n";
                std::cerr << "Текущая директория: " << std::filesystem::current_path() << "\n";
            }
        }
        g.I0=f((g.a+g.b)/2)*(-g.a+g.b);
        for (int i=2;;i*=2) {
            g.I1=0;
            h=(-g.a+g.b)/i;
            for (int step=0; step<i; ++step) {
                g.I1+=f((2*g.a+(2*step+1)*h)/2);
            }
            g.I1*=h;

            R1=(g.I1-g.I0)/3;

            if (abs(R1)<app_err) {
               break;
            }

            lg_nk=std::log(i);

            if (show_graphs==1 && i>0) {
                lg_R1=safe_log(abs(R1));
                fileR_k<<("%d", lg_R1)<<"\t"<<lg_nk<<"\n";
                fileGamma_k<<("%d",safe_log((R0)/R1))/safe_log(2)<<"\t"<<(lg_nk+lg_nk0)/2<<"\n";
            }


            R0=R1;
            lg_nk0=lg_nk;
            g.I0=g.I1;

        }
        if (show_graphs==1) {
            fileR_k.close();
            fileGamma_k.close();
            system("gnuplot -e \"set terminal png; set output '../Graphics/CentralRectR_k.png' ; plot '../CentralRectR_k.txt' using 2:1 with linespoints\"");
            system("gnuplot -e \"set terminal png; set output '../Graphics/CentralRectGamma_k.png' ; plot '../CentralRectGamma_k.txt' using 2:1 with linespoints\"");
        }
        return g.I1+R1;
    }
};



#endif //CENTRALRECT_H
