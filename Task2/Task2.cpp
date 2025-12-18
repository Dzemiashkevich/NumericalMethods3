#include "../Methods/Sympson.h"
#include <iostream>

#include "../Methods/CentralRect.h"
#include "../Methods/Trapeze.h"
#include "../Methods/GaussKristoff.h"
#include "../Methods/GaussLeg.h"
#include "../Methods/Newton_Kotes.h"

int main () {
    std::function<double(double)> f = [](double x) {return 1/(cos(x)+sin(x));};
    std::function<double(double)> f2 = [](double x) {return 1/(cos(x+1)+sin(x+1));};
    double a=0;
    double b=2;
    double app_err=1e-8;
    std::cout<<Sympson<double>::answer(a,b, f, 1,app_err)<<"\n"<<Trapeze<double>::answer(a,b, f, 1,app_err )<<"\n"<<CentralRect<double>::answer(a,b, f, 1,app_err)<<"\n"<<Newton_Kotes<double>::answer(a,b,f, 0, 12)<<"\n";
    std::cout<<GaussLeg<double>::answer(5,f2);
    return 0;
}
