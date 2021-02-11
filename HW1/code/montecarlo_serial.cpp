#include <iostream>
#include <math.h>

using namespace std;

int DEFAULT_NUM_SAMPLE_PTS = 100000000;
int num_sample_pts;

double montecarlo_method(double (*f)(double), double xmin, double xmax, double ymax, double ymin){
    int inside = 0;

    srand(1000);        // Seed the pseudorandom number generator for repeatable results

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
    //                                                         // 
    /////////////////////////////////////////////////////////////

    if (argc == 1){
        num_sample_pts = DEFAULT_NUM_SAMPLE_PTS;
    }
    else if (argc == 2){
        num_sample_pts = atoi(argv[1]);
    }
    else{
        cout<<"Invalid arguments. Exitting."<<endl;
        exit(1);
    }

    double integral = montecarlo_method(cos, -M_PI_2, M_PI_2, 1, 0);
    cout<<"Integral: "<<integral<<endl;
}