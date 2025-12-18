//
// Created by Dzemiashkevich Vlad on 11.11.25.
//

#ifndef GAUSSKRISTOFF_H
#define GAUSSKRISTOFF_H
#include <fstream>
#include <utility>

#include "GeneralInteg.h"

template <typename T>
class GaussKristoff:public General_Integ<T>{
    int n;


    GaussKristoff(int n, const std::string& Filename) {
        this->arr=new std::pair<T,T>[n];
        std::ifstream file(Filename,std::ios::in);
        if (file.is_open()){
            std::string in;
            double xi=0, c=0;
            for (int i=0;i<n;i++) {
                getline(file, in, '\t');
                if (in.empty()) {
                    throw std::invalid_argument("Wrong input file");
                }
                xi=T(std::stod(in));
                getline(file, in, '\n');
                if (in.empty()) {
                    throw std::invalid_argument("Wrong input file");
                }
                c=T(std::stod(in));
                this->arr[i]=std::pair<T,T>(xi, c);
            }
        }
        else {
            throw std::invalid_argument("Wrong input file");
        }

    }
public:
    GaussKristoff() {}
    std::pair<T,T>* arr;
};



#endif //GAUSSKRISTOFF_H
