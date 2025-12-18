//
// Created by Dzemiashkevich Vlad on 6.11.25.
//

#ifndef TRAPEZE_H
#define TRAPEZE_H
#include "GeneralInteg.h"


template <typename T>
class Trapeze:public General_Integ<T> {
public:
    Trapeze(T a, T b, std::function<T(T)> f,T h0,T app_err, int gamma):General_Integ<T>(a,b,f,h0, app_err, gamma){}
    static T answer(T a, T b, std::function<T(T)> f,int show_graphs=1, T app_err=1e-8) {
        int gamma=2;
        T h0=(b-a)/7;
        Trapeze<T> g( a, b, f, h0, app_err, gamma);
        T r=2, R1=0, lg_R1=0,  R0=0, lg_R0=0, lg_nk0=0, lg_nk=0, xi0=g.a, gamma_k=0;
        std::fstream fileR_k;
        std::fstream fileGamma_k;
        if (show_graphs==1) {
            fileR_k.open("../TrapezeR_k.txt", std::ios::out);
            fileGamma_k.open("../TrapezeGamma_k.txt", std::ios::out);
            if (!fileR_k.is_open() || !fileGamma_k.is_open()) {
                std::cerr << "Ошибка: не удалось открыть файлы для записи!\n";
                std::cerr << "Текущая директория: " << std::filesystem::current_path() << "\n";
            }


        }
        T h=0.0;
        g.I0=(f(-g.a)/2+f(g.b)/2)*(g.a-g.b)/2;
        for (int i=1;;i*=2) {
            g.I1=0;
            h=(-g.a+g.b)/i;
            for (int step=0; step<i; ++step) {
                g.I1+=(f(g.a+(step+1)*h)+f(g.a+step*h))*h/2;
            }


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
            lg_R0=lg_R1;
            lg_nk0=lg_nk;
            g.I0=g.I1;

        }
        if (show_graphs==1) {
            fileR_k.close();
            fileGamma_k.close();
            system("gnuplot -e \"set terminal png; set output '../TrapezeR_k.png' ; plot '../TrapezeR_k.txt' using 2:1 with linespoints\"");
            system("gnuplot -e \"set terminal png; set output '../TrapezeGamma_k.png' ; plot '../TrapezeGamma_k.txt' using 2:1 with linespoints\"");
        }
        return g.I1+R1;
    }
};



#endif //TRAPEZE_H
