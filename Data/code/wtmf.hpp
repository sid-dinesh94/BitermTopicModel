#ifndef WTMF_HPP
#define WTMF_HPP

#include <itpp/itbase.h>

using namespace std;
using namespace itpp;

// data structure
struct wtmf_corpus {
  Sparse_Mat<double> sent_data;
  Sparse_Mat<double> word_data;
  Sparse_Mat<double> sent_weight;
  Sparse_Mat<double> word_weight;
  Vec<double>* r4s;
  Vec<double>* r4w;
  Vec<double>* w4s;
  Vec<double>* w4w;
  
  Sparse_Mat<double> syn;
};

// parameter and latent variables
struct wtmf_model {
  Mat<double> p;
  Mat<double> q;
  double dim;
  double lambda;
  double wm;
  double delta;
};


#endif
