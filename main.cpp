#include <cstdlib>
#include <iostream>
#include "workers/worker.hpp"
#include "dataset_handling/dataset_handler.hpp"

using namespace arma;


int main(int argc,char** argv)
{
   mat tst(6,7);
   tst.fill(5);
   std::vector<mat> shared_matrix = dataset_handler::split_matrix(&tst,5);

   mat result = dataset_handler::merge_shared_matrices( shared_matrix );
   return 0;
}
