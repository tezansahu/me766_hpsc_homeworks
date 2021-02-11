#include <iostream>
#include <math.h>
#include <omp.h>

using namespace std;

int DEFAULT_NUM_SAMPLE_PTS = 100000000;
int DEFAULT_NUM_THREADS = 1;

int num_sample_pts;
int num_threads;

double montecarlo_method(double (*f)(double), double xmin, double xmax, double ymax, double ymin){
    long inside = 0;

    srand(1000);        // Seed the pseudorandom number generator for repeatable results

    #pragma omp parallel for reduction(+: inside)
    for (int i = 0; i < num_sample_pts; i++) {
        double x = (xmax - xmin) * ((double)rand()/RAND_MAX) + xmin;
        double y = (ymax - ymin) * ((double)rand()/RAND_MAX) + ymin;

        if (y <= f(x)) {
            inside++;
        }
    }

    double integral = (xmax - xmin) * (ymax - ymin) * ((double)inside / num_sample_pts);
    return integral;
}

int main(int argc, char *argv[]){
    /////////////////////////////////////////////////////////////
    // Arguments to be passed (all optional):                  //
    //                                                         //
    // 1st: Number of sampling points for integral calculation //
    // 2nd: Number of threads to be used                       //
    //                                                         // 
    /////////////////////////////////////////////////////////////
    
    if(argc == 1){
        num_sample_pts = DEFAULT_NUM_SAMPLE_PTS;
        num_threads = DEFAULT_NUM_THREADS;
    }
    else if(argc == 2){
        num_sample_pts = atoi(argv[1]);
        num_threads = DEFAULT_NUM_THREADS;
    }
    else if(argc == 3){
        num_sample_pts = atoi(argv[1]);
        num_threads = atoi(argv[2]);
    }
    else{
        cout<<"Invalid arguments. Exitting."<<endl;
        exit(1);
    }

    omp_set_num_threads(num_threads);

    double integral = montecarlo_method(cos, -M_PI_2, M_PI_2, 1, 0);
    cout<<"Integral: "<<integral<<endl;
}