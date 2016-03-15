#include <iostream>
#include <armadillo>
//#include <pthread.h>
#include <thread>


#ifndef PLOTTER
#define PLOTTER

#include "plot.h"

#endif

#ifndef MLMATHCPP
#define MLMATHCPP

//#include "MLMath.cpp"

#endif


using namespace std;
using namespace arma;

template<class Matrix>
class MLMath {
    int numberOfExamples;
    float learningRate;
    vec identity, input;
    mat hypotheses, inputMatrix, result, outputMatrix;
  public:
    MLMath(Matrix inputMatrix, Matrix hypotheses){
      cout << "inside constructor" << endl;
      MLMath::inputMatrix = inputMatrix;
      MLMath::hypotheses = hypotheses;
    }
    void linearMultiply ();
    void displayValueRaw(const string &s, Matrix value);
    void displayValueInt(const string &s, Matrix value);
    void displayValueDouble(const string &s, double value);

    void generateOutputMatrix();
    void calculateObjectiveFunctionLinear(); //cost
    void calculateGradientWeights();
    float calculateAverageOfSquaredDifference(int numberOfExamples, double sumOFSquaredDifferences);
    float calculateAverageOfDifference(int numberOfExamples, double sumOFSquaredDifferences);


    mat calculateOutputAndResultDifference();
    mat calculate(Matrix inputMatrix, Matrix hypotheses);
    mat calculateSquareDifference(Matrix differenceMatrix);


    double calculateSum(Matrix m);

    static void *test(void *test);



};

//void *test(void *test);

#include "MLMath.tpp"

// template<class T> T Repo<T>::test(){
// 	cout << "Hello world" << endl;
// 	return a;
// }
