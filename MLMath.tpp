// classes example
//#include "MLMath.h"


using namespace std;

template<class Matrix>
void MLMath<Matrix>::linearMultiply () {

  cout << "Inside Math" << endl;

  /*  Useful  */

  // endr represents the end of a row
  // in a matrix
  // mat A;
  //
  // A << 1.0 << 2.0 << endr
  //   << 2.0 << 3.0 << endr
  //   << 1.0 << 3.0 << endr;
  //cout << conv_to<ivec>::from(tsjoined.t() * joined.t()) << endl;
  //conv_to<ivec>::from(result).print();
  //cout << conv_to<ivec>::from(tsjoined * joined) << endl;
  //cout << solve(A,b) << endl;

  // MLMath::displayValueRaw("Input Matrix:", MLMath::inputMatrix);
  //
  // MLMath::displayValueRaw("Hypotheses:", MLMath::hypotheses);
  //
  // MLMath::result = MLMath::calculate(MLMath::inputMatrix, MLMath::hypotheses);
  //
  // MLMath::displayValueRaw("Result Calculation: inputMatrix * Hypotheses", MLMath::result);
  //
  // MLMath::ateOutputMatrix();
  //
  // MLMath::calculateObjectiveFunctionLinear();
  //
  this -> calculateGradientWeights();

}


template<class Matrix>
void MLMath<Matrix>::displayValueRaw(const string &s, Matrix value){
  cout << s << endl;
  cout <<  "-------------------" << endl;
  cout << value << endl;
}

template<class Matrix>
void MLMath<Matrix>::displayValueInt(const string &s, Matrix value){
  cout << s << endl;
  cout <<  "-------------------" << endl;
  conv_to<imat>::from(value).print();
}


template<class Matrix>
void MLMath<Matrix>::displayValueDouble(const string &s, double v){
  cout << s << endl;
  cout <<  "-------------------" << endl;
  cout << v << endl;
}

template<class Matrix>
mat MLMath<Matrix>::calculate(Matrix inputMatrix, Matrix hypotheses){
  //can be hypotheses.t() * inputMatrix
   return inputMatrix * hypotheses;
  //return hypotheses.t() * inputMatrix;
}

template<class Matrix>
void MLMath<Matrix>::generateOutputMatrix(){
  mat outVector;
  outVector.load("output.txt", raw_ascii);
  //MLMath::displayValueRaw("output vector:", outVector);

  //mat tmp;
  //tmp.copy_size(MLMath::result);
  //tmp.ones();
  //MLMath::displayValueRaw("size:", tmp);
  //MLMath::outputMatrix = outVector * tmp;
  MLMath::outputMatrix = outVector;
  MLMath::displayValueRaw("output matrix:", MLMath::outputMatrix);

}

template<class Matrix>
void MLMath<Matrix>::calculateObjectiveFunctionLinear(){
  mat difference = MLMath::calculateOutputAndResultDifference();
  mat squaredDifference = MLMath::calculateSquareDifference(difference);
  double sumOFSquaredDifferences = MLMath::calculateSum(squaredDifference);
  MLMath::numberOfExamples = MLMath::inputMatrix.n_rows;
  float objectiveFunction = MLMath::calculateAverageOfSquaredDifference(MLMath::numberOfExamples,sumOFSquaredDifferences);
  cout << " --------- cost ------" << endl;
  cout << objectiveFunction << endl;
  cout << " " << endl;

}

template<class Matrix>
struct thread_args {
    MLMath<Matrix> *a;
    Plotter<mat> *b;
};

template<class Matrix>
void MLMath<Matrix>::calculateGradientWeights(){

  MLMath::generateOutputMatrix();

  //Plotter<mat> plotxy(MLMath::inputMatrix,MLMath::outputMatrix);
  //plotxy.plotInputOutputScatter(MLMath::hypotheses);

  struct thread_args<Matrix> *args = new thread_args<Matrix>;


  // pthread_t plotThread;
  // pthread_create(&plotThread, NULL,
  //                          &MLMath::test, &args);

  //std::thread test(&MLMath::generateOutputMatrix, this);



  // for(int j = 0; j < 1000; j++){
  //   MLMath::hypotheses += MLMath::hypotheses * 0.0001;
  //   cout << MLMath::hypotheses << endl;
  // }
  //
  //
  //   //join threads
    //test.join();


  //std::thread plotter(&Plotter<mat>::plotInputOutputScatter, this);


  //JOIN!!!!!
  // test.join();
  // nice.join();


  //args->a = this;
  //args->b = &plotxy;


  // if (args != NULL)
  // {
  //     args->a = 0;
  //     args->b = 1;
  //     pthread_create(&threadId, &attr, &function, args);
  // }

  std::thread plotter = std::thread([=] {

    cout << "hammer stein" << endl;

    // for(int i = 0; i < 1000; i++){
    //     cout << "nobody" << endl;
    // }

    Plotter<mat> plotxy(MLMath::inputMatrix,MLMath::outputMatrix);

    plotxy.plotInputOutputScatter(MLMath::hypotheses);




  });


  std::thread calc = std::thread([=] {

    mysleep(100);
    while(1){
        cout << "++++Starting Calculcation++++" << endl << endl;
        for(int i = 0; i < MLMath::outputMatrix.n_rows; i++){

            //cout << endl << endl << " ---------------- training sample << ["<<i<<"]"<<endl<<endl;

            ///standard
            MLMath::displayValueRaw("Input Matrix:", MLMath::inputMatrix);
            MLMath::displayValueRaw("Hypotheses:", MLMath::hypotheses);
            MLMath::result = MLMath::calculate(MLMath::inputMatrix, MLMath::hypotheses);
            mat difference = MLMath::calculateOutputAndResultDifference();
            mat squaredDifference = MLMath::calculateSquareDifference(difference);
            double sumOFSquaredDifferences = MLMath::calculateSum(squaredDifference);
            MLMath::numberOfExamples = MLMath::inputMatrix.n_rows;
            float objectiveFunction = MLMath::calculateAverageOfSquaredDifference(MLMath::numberOfExamples,sumOFSquaredDifferences);
            cout << " --------- cost ------" << endl;
            cout << objectiveFunction << endl;
            cout << " " << endl;
            //////end standard


            //cout << "Getting new weights" << endl << endl;
            //mat difference = MLMath::calculateOutputAndResultDifference();
            double sumOFDifference = MLMath::calculateSum(difference);
            MLMath::numberOfExamples = MLMath::inputMatrix.n_rows;
            float averageOfSumDifference = MLMath::calculateAverageOfDifference(MLMath::numberOfExamples,sumOFDifference);
            //MLMath::learningRate = 0.02031;
              MLMath::learningRate = 0.0001;


            //iterate through thetas
            for(int j = 0; j < MLMath::hypotheses.n_rows; j++){
                //cout << endl << endl << " ---------------- iterating theta ["<< j <<"] ------------ " << endl << endl;
                //cout << "training example before  [" << i << "]: " << MLMath::inputMatrix(i,j) << " :  theta [" << j << "]: " << MLMath::hypotheses(j,0) << endl;
                //cout << "learning rate: " << MLMath::learningRate << endl;
                //cout << "average of sum difference: " << averageOfSumDifference << endl;
                //cout << "input matrix: [" << i << "][" << j << "] " << MLMath::inputMatrix(i,j) << endl;
                MLMath::hypotheses(j,0) = MLMath::hypotheses(j,0) - ( MLMath::learningRate * averageOfSumDifference * MLMath::inputMatrix(i,j) );
                //cout << "training example after  [" << i << "]: " << MLMath::inputMatrix(i,j) << " :  theta [" << j << "]: " << MLMath::hypotheses(j,0) << endl << endl;
            }

            cout << " --------- average of sum difference ------" << endl;
            cout << averageOfSumDifference << endl << endl;

        }
    }
  });



  plotter.join();
  calc.join();





}

template<class Matrix>
mat MLMath<Matrix>::calculateOutputAndResultDifference(){
  mat r = MLMath::result - MLMath::outputMatrix;
  MLMath::displayValueRaw("difference:", r);
  return r;
}

template<class Matrix>
mat MLMath<Matrix>::calculateSquareDifference(Matrix differenceMatrix){
  mat squaredDifference = square(differenceMatrix);
  MLMath::displayValueRaw("squared difference:", squaredDifference);
  return squaredDifference;
}

template<class Matrix>
double MLMath<Matrix>::calculateSum(Matrix m){

  double sum = accu(m);
  MLMath::displayValueDouble("sum of:", sum);
  return sum;
}

template<class Matrix>
float MLMath<Matrix>::calculateAverageOfSquaredDifference(int numberOfExamples, double sumOFSquaredDifferences){
  float part1 = (2*numberOfExamples);
  //cout << part1 << endl;
  float part2 = 1/part1;
  //cout << part2 << endl;
  float part3 = part2 * sumOFSquaredDifferences;
  return part3;
}

template<class Matrix>
float MLMath<Matrix>::calculateAverageOfDifference(int numberOfExamples, double sumOFDifferences){
  //cout << part1 << endl;
  float average = 1/ (float)numberOfExamples;
  //cout << part2 << endl;
  float value = average * sumOFDifferences;
  cout << "average: " << average << " sum of differences: " << sumOFDifferences << " v:" << value << endl;
  return value;
}



template<class Matrix>
void *MLMath<Matrix>::test(void *test){

  struct thread_args<Matrix> *args = (struct thread_args<Matrix> *)test;

  MLMath<Matrix> * ml = args->a;
  Plotter<mat> * plotxy = args->b;

  cout << ml->hypotheses << endl;

  plotxy->plotInputOutputScatter(ml->hypotheses);

  return NULL;
}
//
