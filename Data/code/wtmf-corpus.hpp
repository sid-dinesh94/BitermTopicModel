#ifndef WTMF_CORPUS_HPP
#define WTMF_CORPUS_HPP


#include <iostream>
#include <fstream>
#include <itpp/itbase.h>
#include "wtmf.hpp"

void initialize_wtmf_corpus(wtmf_corpus &corpus, Sparse_Mat<double> &data_mat, Sparse_Mat<double> &weight_mat);

void read_smat_data(char* data_file, Sparse_Mat<double> &data_mat);

void read_mat_data(char* data_file, Mat<int> &data_mat);

void read_mat_data(char* data_file, Mat<double> &data_mat);

void write_mat_data(char* data_file, Mat<double> &data_mat);

void write_mat_data(char* data_file, Mat<int> &data_mat);

void delete_wtmf_corpus(wtmf_corpus &corpus);

#endif
