#include <iostream>
#include <math.h>
#include <omp.h>

using namespace std;

int DEFAULT_NUM_DIVS = 1000;
int DEFAULT_NUM_THREADS = 1;

int num_divs;
int num_threads;

double trapezoidal_rule(double (*f)(double), double xmin, double xmax){
    double integral = 0;

    double step_size = (xmax - xmin) / num_divs;
    
    #pragma omp parallel for reduction(+: integral)
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
    // 2nd: Number of threads to be used                 //
    //                                                   // 
    ///////////////////////////////////////////////////////
    
    if(argc == 1){
        num_divs = DEFAULT_NUM_DIVS;
        num_threads = DEFAULT_NUM_THREADS;
    }
    else if(argc == 2){
        num_divs = atoi(argv[1]);
        num_threads = DEFAULT_NUM_THREADS;
    }
    else if(argc == 3){
        num_divs = atoi(argv[1]);
        num_threads = atoi(argv[2]);
    }
    else{
        cout<<"Invalid arguments. Exitting."<<endl;
        exit(1);
    }

    omp_set_num_threads(num_threads);

    double integral = trapezoidal_rule(cos, -M_PI_2, M_PI_2);
    cout<<"Integral: "<<integral<<endl;
}