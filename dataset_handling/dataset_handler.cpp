#include "dataset_handler.hpp"

template<typename T>
T mod(T a, int n)
{
    return a - floor(a/n)*n;
}


std::vector<mat> dataset_handler::split_matrix( mat *recv_matrix, int shared_matrices)
{
    std::vector<mat> shared_matrix_vector;
    mat result = *recv_matrix;
    for(int i = 0;i < shared_matrices;i++){
        mat shared = randi<mat>(recv_matrix->n_rows, recv_matrix->n_cols, distr_param(INT_MIN, INT_MAX));
        result -= shared;
        shared_matrix_vector.push_back(shared);
    }
    result = mod(result,INT_MAX);
    shared_matrix_vector.push_back(result);
    arma_rng::set_seed_random();
    return shared_matrix_vector;
}

mat dataset_handler::merge_shared_matrices(std::vector<mat> shared_matrices)
{
    mat result_matrix(shared_matrices[0].n_rows,shared_matrices[0].n_cols);
    result_matrix.fill(0);
    for(int i = 0; i < shared_matrices.size();i++)
    {
        result_matrix += shared_matrices[i];
    }
    result_matrix = mod(result_matrix, INT_MAX);
    return result_matrix;
}
