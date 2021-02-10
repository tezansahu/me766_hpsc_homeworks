#include <iostream>
#include <math.h>

using namespace std;

int DEFAULT_NUM_DIVS = 1000;
int num_divs;

double trapezoidal_rule(double (*f)(double), double xmin, double xmax){
    double integral = 0;
    double step_size = (xmax - xmin) / num_divs;
    
    for(int i = 0; i < num_divs; i++){
        double x = xmin + step_size*i;
        double y = f(x);
        integral += (y * step_size);
    }

    return integral;
}

int main(int argc, char *argv[]){
    ///////////////////////////////////////////////////////
    // Arguments to be passed (all optional):            //
    //                                                   //
    // 1st: Number of divisions for integral calculation //
    //                                                   // 
    ///////////////////////////////////////////////////////

    if (argc == 1){
        num_divs = DEFAULT_NUM_DIVS;
    }
    else if (argc == 2){
        num_divs = atoi(argv[1]);
    }
    else{
        cout<<"Invalid arguments. Exitting."<<endl;
        exit(1);
    }

    double integral = trapezoidal_rule(cos, -M_PI_2, M_PI_2);
    cout<<"Integral: "<<integral<<endl;
}