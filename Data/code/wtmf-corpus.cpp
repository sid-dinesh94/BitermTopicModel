#include "wtmf-corpus.hpp"


//void initialize_weights(Sparse_Mat<double> &weight, Sparse_Mat<double> &data);

Vec<double>* get_smat_value(Sparse_Mat<double> &smat);


/*
 * initialize data structure wtmf_corpus
 */ 
void initialize_wtmf_corpus(wtmf_corpus &corpus, Sparse_Mat<double> &data_mat, Sparse_Mat<double> &weight_mat) {
  cout << "[wtmf-corpus.cpp initialize_wtmf_corpus()]: initializing wtmf corpus..." << endl;
  corpus.sent_data = data_mat;
  corpus.sent_weight = weight_mat;

  corpus.word_data = corpus.sent_data.transpose();
  corpus.word_weight = corpus.sent_weight.transpose();
  
  corpus.r4w = get_smat_value(corpus.word_data);
  corpus.r4s = get_smat_value(corpus.sent_data);
  corpus.w4w = get_smat_value(corpus.word_weight);
  corpus.w4s = get_smat_value(corpus.sent_weight);
}


/*
 * delete the dynamically allocated vectors
 */
void delete_wtmf_corpus(wtmf_corpus &corpus) {
  delete[] corpus.r4s;
  delete[] corpus.r4w;
  delete[] corpus.w4s;
  delete[] corpus.w4w;
}


Vec<double>* get_smat_value(Sparse_Mat<double> &smat) {
  Vec<double>* values = new Vec<double>[smat.cols()];
  for (int c = 0; c < smat.cols(); c++) {
    Sparse_Vec<double> svec = smat.get_col(c);
    values[c].set_size(svec.nnz());
    for (int r = 0; r < svec.nnz(); r++) {
      values[c].set(r, svec.get_nz_data(r));
    }
  }
  return values;
}

/*
void initialize_weights(Sparse_Mat<double> &weight, Sparse_Mat<double> &data) {
  int no_rows = data.rows();
  int no_cols = data.cols();
  weight.set_size(no_rows, no_cols);
  for (int c = 0; c < data.cols(); c++) {
    Sparse_Vec<double> sense_sv = data.get_col(c);
    for (int i = 0; i < sense_sv.nnz(); i++) {
      int r = sense_sv.get_nz_index(i);
      weight.set(r, c, 1);
    }
  }
  }*/



/*
 * read data (text) into a sparse matrix
 */
void read_smat_data(char* data_file, Sparse_Mat<double> &data_mat) {
  ifstream in_file;
  int no_sense, no_word, no_rate;
  int sense, word;
  int sense_size;
  double value;

  cout << "[wtmf-corpus.cpp read_sparse_data()]: reading " << data_file << endl;
  in_file.open(data_file);
  if (!in_file) {
    cout << endl << "[wtmf-corpus.cpp read_sparse_data()]: Cannot open file " << data_file << endl;
    exit(1);
  }

  in_file >> no_sense >> no_word;
  data_mat.set_size(no_word, no_sense);
  no_rate = 0;
  for (int i = 0; i < no_sense; i++) {
    sense = i;
    in_file >> sense_size;
    //cout << "i=" << i << " sense_size=" << sense_size<<endl;
    for (int j = 0; j < sense_size; j++) {
      in_file >> word >> value;
      /*double temp = data_mat(word, sense);
      if (temp != 0) {
	cout << sense << " " << word << endl;
	exit(1);
	}*/
      data_mat.set(word, sense, value);
      no_rate++;
    }
  }
  in_file.close();
  data_mat.compact();

  cout << "[wtmf-corpus.cpp read_sparse_data()]: rows=" << data_mat.rows() << endl;
  cout << "[wtmf-corpus.cpp read_sparse_data()]: colums=" << data_mat.cols() << endl;
  if (no_rate != data_mat.nnz()) {
    cout << "[wtmf-corpus.cpp read_sparse_data()]: no_rate does not match with data_mat.nnz()" << endl;
    cout << no_rate << " " << data_mat.nnz() << endl;
    exit(1);
  }
  //cout << "[wtmf-corpus.cpp read_sparse_data()]: nnz=" << no_rate << endl;
  //cout << "[wtmf-corpus.cpp read_sparse_data()]: sparse matrix density=" << data_mat.density() << endl;
}



/*
 * write dense matrix data into a file
 */
void write_mat_data(char* data_file, Mat<double> &data_mat) {
  ofstream out_file;

  cout << "[wtmf-corpus.cpp write_mat_data()]: writing " << data_file << endl;
  out_file.open(data_file);
  if (!out_file) {
    cout << endl << "[wtmf-corpus.cpp write_mat_data()]: Cannot open file " << data_file << endl;
    exit(1);
  }

  cout << "[wtmf-corpus.cpp write_mat_data()]: cols=" << data_mat.cols() << " rows=" << data_mat.rows() << endl;
  out_file << data_mat.cols() << " " << data_mat.rows() << endl;
  for (int i = 0; i < data_mat.cols(); i++) {
    for (int j = 0; j < data_mat.rows(); j++) {
      out_file << data_mat(j,i) << " ";
    }
    out_file << endl;
  }
  out_file.close();
}


/*
 * read dense matrix data (sense_pos) into a matrix
 */
void read_mat_data(char* data_file, Mat<double> &data_mat) {
  ifstream in_file;
  int no_rows, no_cols;
  double value;

  cout << "[wtmf-corpus.cpp read_mat_data()]: reading " << data_file << endl;
  in_file.open(data_file);
  if (!in_file) {
    cout << endl << "[wtmf-corpus.cpp read_mat_data()]: Cannot open file " << data_file << endl;
    exit(1);
  }

  in_file >> no_cols >> no_rows;
  data_mat.set_size(no_rows, no_cols);
  for (int i = 0; i < no_cols; i++) {
    for (int j = 0; j < no_rows; j++) {
      in_file >> value;
      data_mat(j, i) = value;
    }
  }
  in_file.close();

  cout << "[wtmf-corpus.cpp read_mat_data()]: rows=" << data_mat.rows() << endl;
  cout << "[wtmf-corpus.cpp read_mat_data()]: colums=" << data_mat.cols() << endl;
}


/*
 * read dense matrix data (sense_pos) into a matrix
 */
void read_mat_data(char* data_file, Mat<int> &data_mat) {
  ifstream in_file;
  int no_rows, no_cols;
  double value;

  cout << "[wtmf-corpus.cpp read_mat_data()]: reading " << data_file << endl;
  in_file.open(data_file);
  if (!in_file) {
    cout << endl << "[wtmf-corpus.cpp read_mat_data()]: Cannot open file " << data_file << endl;
    exit(1);
  }

  in_file >> no_cols >> no_rows;
  data_mat.set_size(no_rows, no_cols);
  for (int i = 0; i < no_cols; i++) {
    for (int j = 0; j < no_rows; j++) {
      in_file >> value;
      data_mat(j, i) = value;
    }
  }
  in_file.close();

  cout << "[wtmf-corpus.cpp read_mat_data()]: rows=" << data_mat.rows() << endl;
  cout << "[wtmf-corpus.cpp read_mat_data()]: colums=" << data_mat.cols() << endl;
}


/*
 * write dense matrix data into a file
 */
void write_mat_data(char* data_file, Mat<int> &data_mat) {
  ofstream out_file;

  cout << "[wtmf-corpus.cpp write_mat_data()]: writing " << data_file << endl;
  out_file.open(data_file);
  if (!out_file) {
    cout << endl << "[wtmf-corpus.cpp write_mat_data()]: Cannot open file " << data_file << endl;
    exit(1);
  }

  cout << "[wtmf-corpus.cpp write_mat_data()]: cols=" << data_mat.cols() << " rows=" << data_mat.rows() << endl;
  out_file << data_mat.cols() << " " << data_mat.rows() << endl;
  for (int i = 0; i < data_mat.cols(); i++) {
    for (int j = 0; j < data_mat.rows(); j++) {
      out_file << data_mat(j,i) << " ";
    }
    out_file << endl;
  }
  out_file.close();
}
