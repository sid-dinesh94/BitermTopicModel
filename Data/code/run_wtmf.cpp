#include <iostream>
#include "wtmf.hpp"
#include "wtmf-learn.hpp"
#include "wtmf-corpus.hpp"
#include "wtmf-model.hpp"
#include <itpp/base/random.h>
#include <time.h>
#include <string.h>

void train(char* data_file, char* weight_file, char* sim_file, char* model_file, int dim, double lambda, double wm, double delta, int iteration);
void test(char* data_file, char* weight_file, char* model_file, char* output_file);


int main(int argc, char *argv[]) {
  time_t start_t, end_t;
  start_t = time(NULL);

  RNG_reset(1012);
  
  char* data_file = 0;
  char* weight_file = 0;
  char* sim_file = 0;
  char* model_file = 0;
  char* output_file = 0;
  if (argc != 11 && argc != 6) {
    cout << "To train a model: ./wtmf 1 data_file weight_file sim_file model_file dim lambda wm delta iteration\nFor test data: ./wtmf 0 data_file weight_file model_file output_file\n";
    exit(1);
  }


  // 1. train a wtmf model
  if (strcmp(argv[1],"1") == 0) {
    data_file = argv[2];
    cout << "[run_wtmf.cpp main()]: data_file = " << data_file << endl;
    weight_file = argv[3];
    cout << "[run_wtmf.cpp main()]: weight_file = " << weight_file << endl;
    sim_file = argv[4];
    cout << "[run_wtmf.cpp main()]: sim_file = " << sim_file << endl;
    model_file = argv[5];
    cout << "[run_wtmf.cpp main()]: model_file = " << model_file << endl;
    int dim = atoi(argv[6]);
    cout << "[run_wtmf.cpp main()]: dim = " << dim << endl;
    double lambda = atof(argv[7]);
    cout << "[run_wtmf.cpp main()]: lambda = " << lambda << endl;
    double wm = atof(argv[8]);
    cout << "[run_wtmf.cpp main()]: wm = " << wm << endl;
    double delta = atof(argv[9]);
    cout << "[run_wtmf.cpp main()]: delta = " << delta << endl;
    int iteration = atof(argv[10]);
    cout << "[run_wtmf.cpp main()]: iteration = " << iteration << endl;
    train(data_file, weight_file, sim_file, model_file, dim, lambda, wm, delta, iteration);
  }
  // 2. use an existing wtmf model file for inference
  else {
    data_file = argv[2];
    cout << "[run_wtmf.cpp main()]: data_file = " << data_file << endl;
    weight_file = argv[3];
    cout << "[run_wtmf.cpp main()]: weight_file = " << weight_file << endl;
    model_file = argv[4];
    cout << "[run_wtmf.cpp main()]: model_file = " << model_file << endl;
    output_file = argv[5];
    cout << "[run_wtmf.cpp main()]: output_file = " << output_file << endl;
    test(data_file, weight_file, model_file, output_file);
  }

  end_t = time(NULL);
  int used_time = difftime(end_t, start_t);
  cout << "[run_wtmf.cpp main()]: used time = " << used_time << " seconds" << endl;
}




void train(char* data_file, char* weight_file, char* sim_file, char* model_file, int dim, double lambda, double wm, double delta, int iteration) {
  wtmf_corpus corpus;
  wtmf_model model;

  Sparse_Mat<double> data_mat, weight_mat;
  read_smat_data(data_file, data_mat);
  read_smat_data(weight_file, weight_mat);
  initialize_wtmf_corpus(corpus, data_mat, weight_mat);
  
  Sparse_Mat<double> syn;
  read_smat_data(sim_file, syn);
  corpus.syn = syn;

  initialize_wtmf_model(model, corpus.sent_data.cols(), corpus.sent_data.rows(), dim, lambda, wm, delta);
  
  wtmf_estimate(corpus, model, iteration);
  write_wtmf_model(model_file, model);
  delete_wtmf_corpus(corpus);
}




void test(char* data_file, char* weight_file, char* model_file, char* output_file) {
  wtmf_corpus corpus;
  wtmf_model model;

  Sparse_Mat<double> data_mat, weight_mat;
  read_smat_data(data_file, data_mat);
  read_smat_data(weight_file, weight_mat);
  initialize_wtmf_corpus(corpus, data_mat, weight_mat);
  read_wtmf_model(model_file, model);
  
  Mat<double> q;
  wtmf_inference(corpus, model, q);
  write_mat_data(output_file, q);
  delete_wtmf_corpus(corpus);
}
