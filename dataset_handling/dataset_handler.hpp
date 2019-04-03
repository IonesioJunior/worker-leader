#ifndef _APP_DATASET_HANDLER_HPP_
#define _APP_DATASET_HANDLER_HPP_

#include <armadillo>
#include <vector>
#include <limits.h>

using namespace arma;
namespace dataset_handler
{
    std::vector<mat> split_matrix( mat *recv_mat,int shared_matrices );
    mat merge_shared_matrices(std::vector<mat> shared_matrices);
}

#endif  // _APP_DATASET_HANDLER_HPP_
