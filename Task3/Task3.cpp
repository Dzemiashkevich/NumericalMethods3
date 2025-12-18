#include <iostream>
#include "../Methods/GaussLag.h"
#include "../Methods/Newton_Kotes.h"
#include "../Methods/Sympson.h"

int main() {
    auto f = [](double x) {
        double x13 = std::pow(x, 1.0/3.0);
        return  1;
    };
    auto f1 = [](double x) {return (1.0/9.0)*sin(pow(x,1.0/3.0))*log(x)*pow(x,-2.0/3.0);};
    auto f2 = [](double x) {return exp(x-pow(x,3))*sin(x)*log(x);};
std::cout<<GaussLag<double>::answer(50, f1)<<"\n"<<GaussLag<double>::answer(50, f2)<<"\n";
    return 0;
}
