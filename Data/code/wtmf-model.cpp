#include "wtmf-model.hpp"


/*
 * initialize wtmf model
 */
void initialize_wtmf_model(wtmf_model &model, int no_sents, int no_words, int dim, double lambda, double wm, double delta) {
  cout << "[wtmf_model.cpp initialize_wtmf_model()]: initializing wtmf model...\n";
  model.dim = dim;
  model.lambda = lambda;
  model.wm = wm;
  model.delta = delta;

  //cout << randu(1) << endl;
  
  model.p = randu(model.dim, no_words);
  model.p = model.p * 0.2 - 0.1;
  model.q = randu(model.dim, no_sents);
  model.q = model.q * 0.2 - 0.1;
}



/*
 * read wtmf model from file
 */
void read_wtmf_model(char* data_file, wtmf_model &model) {
  ifstream in_file;

  // 1. open file 
  cout << "[wtmf_model.cpp read_wtmf_model()]: reading wtmf_model from " << data_file << endl;
  in_file.open(data_file);
  if (!in_file) {
    cout << endl << "[wtmf_model.cpp read_wtmf_model()]: Cannot open file " << data_file << endl;
    exit(1);
  }

  // 2. read parameters
  in_file >> model.dim >> model.lambda >> model.wm >> model.delta;
  cout << "[wtmf_model.cpp read_wtmf_model()]: parameters: dim=" << model.dim << " lambda=" << model.lambda << " wm=" << model.wm << endl;

  // 3. read word vectors
  char filename[100];
  strcpy(filename, data_file);
  strcat(filename, ".p");
  read_mat_data(filename, model.p);
}


/*
 * write wtmf latent model into file
 */
void write_wtmf_model(char* data_file, wtmf_model &model) {
  ofstream out_file;

  // 1. open file
  cout << "[wtmf_model.cpp write_wtmf_model()]: writing wtmf_model into " << data_file << endl;
  out_file.open(data_file);
  if (!out_file) {
    cout << endl << "[wtmf_model.cpp write_wtmf_model()]: Cannot open file " << data_file << endl;
    exit(1);
  }

  // 2. write parameters
  out_file << model.dim << endl;
  out_file << model.lambda << endl;
  out_file << model.wm << endl;
  out_file.close();

  // 3. write word vectors
  char filename[100];
  strcpy(filename, data_file);
  strcat(filename, ".p");
  write_mat_data(filename, model.p);

  // 4. and sentence vectors
  strcpy(filename, data_file);
  strcat(filename, ".q");
  write_mat_data(filename, model.q);
}
