#ifndef WTMF_LEARN_HPP
#define WTMF_LEARN_HPP

#include <itpp/itbase.h>
#include "wtmf.hpp"


void wtmf_estimate(wtmf_corpus &corpus, wtmf_model &model, int maxiter);

void wtmf_inference(wtmf_corpus &corpus, wtmf_model &model, Mat<double> &q);


#endif
