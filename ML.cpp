#include <iostream>
#include <armadillo>

#ifndef MLMATH
#define MLMATH

#include "MLMath.h"

#endif

#ifndef PLOTTER
#define PLOTTER

#include "plot.h"

#endif

using namespace std;
using namespace arma;

int main(int argc, char *argv[])
{


  // for(int i=0; i<argc; i++){
  //   cout << argv[i] << endl;
  // }

  if(argc > 1){
    cout << "param: " << argv[1] << endl;
    string param_1 = argv[1];
    if(param_1 == "test"){
      cout << "running all tests" << endl;
      cout << "------------------------------" << endl;
    }
  }


  // if(test == "test"){
  //   cout << "testing: " << test << endl;
  // }else{
  //   cout << "not testing: " << test << endl;
  // }


  vec identity, input;
  mat hypotheses, inputMatrix;

  //the input values in single value calculations
  // input << 2104 << 1416 << 1534 << 852;

  //identity matrix for input
  // identity << 1 << 1 << 1 << 1;

  //join identity matrix to input values
  // inputMatrix = join_rows(identity,input);
  inputMatrix.load("input.txt", raw_ascii);

  //load hypothesis values
  hypotheses.load("hypotheses.txt", raw_ascii);

  //create MLMath object with inputmatrix, and hypotheses
  MLMath<mat> math(inputMatrix,hypotheses);

  //calculate input matrix times hypotheses matrix
  math.linearMultiply();

  //demo_3d();


  //callthis();
  //return 0;


}
