#include <cstdlib>
#include <iostream>
#include "workers/worker.hpp"


int main(int argc,char** argv)
{

    arma::mat A(2,3);
    A.fill(5.0);
    workers::Worker *worker1 = new workers::Worker("worker1","localhost:9092");   
    while(1)
    {
        worker1->publish_data( &A );
    }
    return 0;
}
