#include "wtmf-learn.hpp"


/*
 * Perform all rank. 
 */
void wtmf_estimate(wtmf_corpus &corpus, wtmf_model &model, int maxiter) {
  int no_words = corpus.sent_data.rows();
  int no_sents = corpus.sent_data.cols();

  cout << "[wtmf-learn.cpp wtmf_estimate()]: model: dim=" << model.dim << " lambda=" << model.lambda << " wm=" << model.wm << " delta=" << model.delta << endl;
  cout << "[wtmf-learn.cpp wtmf_estimate()]: corpus: no_words=" << no_words << " no_sents=" << no_sents << endl;

  // reciprocal length of model.p
  //Vec<double> qlen = elem_div(1.0, sqrt(sum_sqr(model.q)));
  Vec<double> qlen = 1.0 / sqrt(sum_sqr(model.q));

  /* 2. iteration */
  for (int iter = 0; iter < maxiter; iter++) {
    /* 2.1 calculating p... */
    cout << "[wtmf-learn.cpp wtmf_estimate()]: iteration=" << iter << endl;
    cout << "[wtmf-learn.cpp wtmf_estimate()]: calculating p..." << endl;

    Mat<double> qqte = model.q * model.q.transpose() * model.wm;
    for (int i = 0; i < no_words; i++) {
      if (corpus.r4w[i].size() == 0) {
	model.p.set_col(i, zeros(model.dim));
	continue;
      }
      Mat<double> qv = model.q.get_cols(corpus.word_data.get_col(i).get_nz_indices());
      model.p.set_col(i, inv(qqte + qv * elem_mult(repmat(corpus.w4w[i],1,model.dim)-model.wm,qv.transpose()) + model.lambda*eye(model.dim))  *  qv * elem_mult(corpus.r4w[i],corpus.w4w[i]));
    }
    
    /* 2.2 calculating q... */
    cout << "[wtmf_learn.cpp wtmf_estimate()]: calculating q..." << endl;
    Mat<double> ppte = model.p * model.p.transpose() * model.wm;
    for (int j = 0; j < no_sents; j++) {
      if (corpus.r4s[j].size() == 0) {
	model.q.set_col(j, zeros(model.dim));
	continue;
      }
      Mat<double> pv = model.p.get_cols(corpus.sent_data.get_col(j).get_nz_indices());
      if (corpus.syn.cols() == 0 || model.delta == 0) {
	model.q.set_col(j, inv(ppte + pv * elem_mult(repmat(corpus.w4s[j],1,model.dim)-model.wm,pv.transpose()) + model.lambda*eye(model.dim))  *  pv * elem_mult(corpus.r4s[j],corpus.w4s[j]));
	continue;
      }

      Mat<double> qnv = model.q.get_cols(corpus.syn.get_col(j).get_nz_indices()); // vectors of neighbors
      Vec<double> values = qlen.get(corpus.syn.get_col(j).get_nz_indices()) * qlen(j); // the product of reciprocal length of neighbor vector and current vector
      
      if (qnv.cols() == 0) {
	model.q.set_col(j, inv(ppte + pv * elem_mult(repmat(corpus.w4s[j],1,model.dim)-model.wm,pv.transpose()) + model.lambda*eye(model.dim))  *  pv * elem_mult(corpus.r4s[j],corpus.w4s[j]));
      } else {
	model.q.set_col(j, inv(ppte + pv * elem_mult(repmat(corpus.w4s[j],1,model.dim)-model.wm,pv.transpose()) + model.delta*qnv*qnv.transpose() + model.lambda*eye(model.dim))  *  (pv*elem_mult(corpus.r4s[j],corpus.w4s[j]) + model.delta*qnv*values));
      }
      qlen(j) = 1/sqrt(sum_sqr(model.q.get_col(j)));
    }
  }
}



void wtmf_inference(wtmf_corpus &corpus, wtmf_model &model, Mat<double> &q) {
  cout << "[wtmf-learn.cpp wtmf_inference()]: entries=" << corpus.sent_data.cols() << endl;
  Mat<double> ppte;
  ppte = model.p * model.p.transpose() * model.wm;
  q.set_size(model.dim, corpus.sent_data.cols());
  
  for (int i = 0; i < corpus.sent_data.cols(); i++) {
    if (corpus.sent_data.get_col(i).nnz() == 0) {
      q.set_col(i, zeros(model.dim));
      continue;
    }
    Mat<double> pv = model.p.get_cols(corpus.sent_data.get_col(i).get_nz_indices());
    q.set_col(i, inv(ppte + pv * elem_mult(repmat(corpus.w4s[i],1,model.dim)-model.wm,pv.transpose()) + model.lambda*eye(model.dim))  *  pv * elem_mult(corpus.r4s[i],corpus.w4s[i]));
  }
}
