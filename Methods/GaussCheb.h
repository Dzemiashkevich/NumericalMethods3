//
// Created by Dzemiashkevich Vlad on 12.11.25.
//

#ifndef GAUSSCHEB_H
#define GAUSSCHEB_H
#include "GaussKristoff.h"
#define PI 3.1415926535897932384626433832795
template <typename T>
class GaussCheb:public GaussKristoff<T>{
public:
     GaussCheb(int n) {
        T xi=0,c=0;
        this->arr=new std::pair<T,T>[n];
        switch (n) {
            case 2:
                xi=PI/2;
                c=PI/2;
                this->arr[0]=std::pair<T,T>(xi,c);
                this->arr[1]=std::pair<T,T>(-xi,c);
                break;
            case 3:
                xi=1/2.;
                c=PI/8;
                this->arr[0]=std::pair<T,T>(xi,c);
                this->arr[1]=std::pair<T,T>(-xi,c);
                xi=0.;
                c=PI/4;
                this->arr[2]=std::pair<T,T>(xi,c);
                break;
            case 4:
                xi=(1+sqrt(5))/4;
                c=PI*(5-sqrt(5))/40;
                this->arr[0]=std::pair<T,T>(xi,c);
                this->arr[1]=std::pair<T,T>(-xi,c);
                xi=(-1+sqrt(5))/4;
                c=PI*(5+sqrt(5))/40;
                this->arr[2]=std::pair<T,T>(xi,c);
                this->arr[3]=std::pair<T,T>(-xi,c);
                break;
        }
    }
    GaussCheb(int n, const std::string& Filename):GaussKristoff<T>::GaussKristoff(n, Filename){}
};



#endif //GAUSSCHEB_H
