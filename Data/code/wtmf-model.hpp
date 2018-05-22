#ifndef WTMF_MODEL_HPP
#define WTMF_MODEL_HPP


#include <iostream>
#include <fstream>
#include <itpp/itbase.h>
#include "wtmf.hpp"
#include "wtmf-corpus.hpp"


using namespace std;
using namespace itpp;


void initialize_wtmf_model(wtmf_model &model, int no_sents, int no_words, int dim, double lambda, double wm, double delta);

void read_wtmf_model(char* data_file, wtmf_model &lm);

void write_wtmf_model(char* data_file, wtmf_model &lm);

#endif
