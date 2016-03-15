#include <fstream>
#include <vector>
#include <map>
#include <limits>
#include <cmath>
#include <cstdio>
#include "boost/tuple/tuple.hpp" //<boost/tuple/tuple.hpp>
#include "boost/foreach.hpp" // <boost/foreach.hpp>
#include <armadillo>

#ifndef MLMATH
#define MLMATH

#include "MLMath.h"

#endif

// Warn about use of deprecated functions.
#define GNUPLOT_DEPRECATE_WARN
//#include "plot.h"

#ifndef M_PI
#	define M_PI 3.14159265358979323846
#endif

// http://stackoverflow.com/a/1658429
#ifdef _WIN32
	#include <windows.h>
	inline void mysleep(unsigned millis) {
		::Sleep(millis);
	}
#else
	#include <unistd.h>
	inline void mysleep(unsigned millis) {
		::usleep(millis * 1000);
	}
#endif

void pause_if_needed() {
#ifdef _WIN32
	// For Windows, prompt for a keystroke before the Gnuplot object goes out of scope so that
	// the gnuplot window doesn't get closed.
	std::cout << "Press enter to exit." << std::endl;
	std::cin.get();
#endif
}

// Tell MSVC to not warn about using fopen.
// http://stackoverflow.com/a/4805353/1048959
#if defined(_MSC_VER) && _MSC_VER >= 1400
#pragma warning(disable:4996)
#endif

using namespace std;
using namespace arma;

void demo_basic() {
	Gnuplot gp;
	// For debugging or manual editing of commands:
	//Gnuplot gp(std::fopen("plot.gnu"));
	// or
	//Gnuplot gp("tee plot.gnu | gnuplot -persist");

	std::vector<std::pair<double, double> > xy_pts_A;
	for(double x=-2; x<2; x+=0.01) {
		double y = x*x*x;
		xy_pts_A.push_back(std::make_pair(x, y));
	}



	std::vector<std::pair<double, double> > xy_pts_B;
	for(double alpha=0; alpha<1; alpha+=1.0/24.0) {
		double theta = alpha*2.0*3.14159;
		xy_pts_B.push_back(std::make_pair(cos(theta), sin(theta)));
	}

	gp << "set xrange [-2:2]\nset yrange [-2:2]\n";
	gp << "plot '-' with lines title 'cubic', '-' with points title 'circle'\n";
	gp.send1d(xy_pts_A);
	gp.send1d(xy_pts_B);

	pause_if_needed();
}

void demo_binary() {
	Gnuplot gp;

	std::vector<std::pair<double, double> > xy_pts_A;
	for(double x=-2; x<2; x+=0.01) {
		double y = x*x;
		xy_pts_A.push_back(std::make_pair(x, y));
	}

	// std::vector<std::pair<double, double> > xy_pts_B;
	// for(double alpha=0; alpha<1; alpha+=1.0/24.0) {
	// 	double theta = alpha*2.0*3.14159;
	// 	xy_pts_B.push_back(std::make_pair(cos(theta), sin(theta)));
	// }

	gp << "set xrange [-2:2]\nset yrange [-2:2]\n";
	gp << "plot '-' binary" << gp.binFmt1d(xy_pts_A, "record") << "with lines title 'cubic'\n";
		//<< "'-' binary" << gp.binFmt1d(xy_pts_B, "record") << "with points title 'circle'\n";
	gp.sendBinary1d(xy_pts_A);
	//gp.sendBinary1d(xy_pts_B);

	pause_if_needed();
}

void demo_animation() {
  #ifdef _WIN32
  	// No animation demo for Windows.  The problem is that every time the plot
  	// is updated, the gnuplot window grabs focus.  So you can't ever focus the
  	// terminal window to press Ctrl-C.  The only way to quit is to right-click
  	// the terminal window on the task bar and close it from there.  Other than
  	// that, it seems to work.
  	std::cout << "Sorry, the animation demo doesn't work in Windows." << std::endl;
  	return;
  #endif

	Gnuplot gp;

	std::cout << "Press Ctrl-C to quit (closing gnuplot window doesn't quit)." << std::endl;

	//gp << "set yrange [0:100]\n";
  //gp << "set xrange [0:10]\n";

  //default for default animation
  gp << "set yrange [-1:1]\n";

	const int N = 100;
	std::vector<double> pts(N);
  std::vector<double> pts2(N);

	double theta = 0;

	while(1) {

		for(int i=0; i<N; i++) {
			double alpha = (double(i)/N-0.5) * 10;

      //default animations
			pts[i] = sin(alpha*8.0 + theta) * exp(-alpha*alpha/2.0);
      pts2[i] = sin(alpha*100.0 + theta) * exp(-alpha*alpha/2.0);

      //pts[i] = pow(i,2) + 1;
      //pts2[i] = i;
		}

		//gp << "plot '-' binary" << gp.binFmt1d(pts, "array") << "with lines notitle\n";

    //gp << "plot '-' binary" << gp.binFmt1d(pts, "array") << "with lines notitle\n";


    //working double plot
    gp << "plot '-' binary" << gp.binFmt1d(pts, "array")
		<< "with lines notitle, '-' binary" << gp.binFmt1d(pts2, "array")
		<< "with lines notitle\n";

    // gp << "plot '-' binary" << gp.binFmt1d(pts, "array") << "with lines notitle, '-' binary" << gp.binFmt1d(pts2,"array") << "with lines notitle\n";



    //<< "'-' binary" << gp.binFmt1d(pts2, "record") << "with points title 'circle'\n";

    //gp << "set xrange [-2:2]\nset yrange [-2:2]\n";
  	//gp << "plot '-' with lines title 'cubic', '-' with points title 'circle'\n";
  	//gp.send1d(xy_pts_A);
  	//gp.send1d(xy_pts_B);


		gp.sendBinary1d(pts);
    gp.sendBinary1d(pts2);
		gp.flush();

		theta += 0.2;
		mysleep(100);
	}

}

void demo_contour(){

  Gnuplot gp;


	gp << "set samples 20\nset isosamples 21\nset xlabel 'X axis'\nset ylabel 'Y axis'\n"<<
  "set zlabel 'Z '' offset 1, 0\nset view 60, 30, 0.85, 1.1\nset key at screen 1.0, 0.9\n"<<
  "set style textbox opaque noborder margins 0.5, 0.5\n";

  gp << "set title 'contour plot'\nset contour\n";
  gp << "splot x*y\n";

	//gp << "plot '-' with lines title 'cubic', '-' with points title 'circle'\n";
	//gp.send1d(xy_pts_A);
	//gp.send1d(xy_pts_B);

	//gp << "pause -1\n";


}

void callthis(){
  cout <<  "called this" <<  endl;
  // demo_binary();
  demo_animation();
  //demo_contour();
  //rm demo_basic();
}


template<class T>
void Plotter<T>::plotInputOutputScatter(arma::mat &hypotheses){

	cout << "***Plotting Input Output***" << endl <<  endl;


	cout << &hypotheses << endl << endl;
	cout << hypotheses << endl << endl;


	#ifdef _WIN32
  	std::cout << "Sorry, the animation demo doesn't work in Windows." << std::endl;
  	return;
  #endif


	Gnuplot gp,gp2;
	mat x = *this->x;
	mat y = *this->y;
	mat both;
	const int N = 100;
	std::vector<double> pts(N);


	gp << "set xrange [0:50]\nset yrange [0:50]\n";




while(1) {

		for(int i=0; i<N; i++) {
      //default animations
			//	i * x + 1
			double insideSum = 0;
			//cout << "hypotheses" << endl;
			//cout << hypotheses << endl;

			for(int j = 0; j < hypotheses.n_rows; j++){
				insideSum += ( hypotheses(j,0) ) * i;
				//cout << "--insideSum "<< j << " value: " << hypotheses(j,0) <<"--" << endl;
				//cout << insideSum << endl;
			}

			//theta + theta * i



			pts[i] = insideSum;
			//cout << pts[i] << endl;

		}

    //working double plot
    // gp << "plot '-' binary" << gp.binFmt1d(pts, "array") << "with lines notitle";

		//////////

		//cout << " ---- plotting input and output ----" << endl;
		//cout << x << endl;
		//cout << y << endl;
		//cout << " ---- end plotting input and output ----" << endl;

		for(int i = 0; i < x.n_rows; i++){
			mat xt = x;
			//remove identity column
			//xt.shed_col(0);
			mat yt = y;
			both = join_rows(xt,yt);
			both.save("scatter.dat", raw_ascii);
		}

		//cout << "------- Points -----" << endl;
		//cout << both << endl;

		//gp << "set xrange [-10:10]\nset yrange [-10:10]\n";

		//gp << "set data style points\n";
		//gp << "plot '-' with lines title 'cubic', '-' with points title 'circle'\n";
		//gp << "plot " << gp.binFmt1d(xy_pts_A, "record") << " using 1:2 with points\n";

		gp << "plot '-' binary"
		<< gp.binFmt1d(pts, "array")
		<< "with lines notitle, 'scatter.dat' \n";

		//gp << "plot 'scatter.dat' \n";

		pause_if_needed();

		gp.sendBinary1d(pts);
		gp.flush();

		mysleep(50);

}//while end


		///////animations


}

void demo_3d(){

	Gnuplot gp;

	std::cout << "Press Ctrl-C to quit (closing gnuplot window doesn't quit)." << std::endl;

	//gp << "set yrange [0:100]\n";
  //gp << "set xrange [0:10]\n";

  //default for default animation
  //gp << "set yrange [-1:1]\n";

	const int N = 100;
	std::vector<double> pts(N);
  std::vector<double> pts2(N);

	double theta = 0;

	while(1) {

		for(int i=0; i<N; i++) {
			double alpha = (double(i)/N-0.5) * 10;

      //default animations
			pts[i] = sin(alpha*8.0 + theta) * exp(-alpha*alpha/2.0);

      //pts[i] = pow(i,2) + 1;
      //pts2[i] = i;
		}

    //working double plot
    // gp << "plot '-' binary" << gp.binFmt1d(pts, "array")
		// << "with lines notitle, '-' binary" << gp.binFmt1d(pts2, "array")
		// << "with lines notitle\n";

		//gp << "set xrange [-10:10]\nset yrange [-10:10]\nset zrange[-10:10]\nset cbrange[-10:10]\n";


		gp << "set samples 20\nset isosamples 21\nset xlabel 'Theta_1'\nset ylabel 'Theta_2'\n"
		<< "set zlabel 'J'\nset view 60, 30, 0.85, 1.1\nset key at screen 1.0, 0.9\n"
		<< "set style textbox opaque noborder margins 0.5, 0.5\n";

	  gp << "set title 'Gradient Descent'\nset pm3d\n";


		gp << "unset surface\n";

		//												  h(x)						y
	  //gp << "splot (  (1/(2*3)) * ( ( ((x*0.8)+(y*0.5)) - (x**3) )**2 )  )  \n";

		//gp << "splot " << gp.binFmt1d(pts, "array") << "  \n";
		gp << "splot (1/1)*( ( ((x*1.8)+(y*1.5)) - (0.02) )**2 )  \n";



		//gp.sendBinary1d(pts);
		gp.flush();

		theta += 0.2;
		mysleep(1000);
	}




}



void demo_3d2(){

  Gnuplot gp;

	//gp << "set xrange [-10:10]\nset yrange [-10:10]\nset zrange[-10:10]\nset cbrange[-10:10]\n";

	gp << "set samples 20\nset isosamples 21\nset xlabel 'Theta_1'\nset ylabel 'Theta_2'\n"<<
  "set zlabel 'J'\nset view 60, 30, 0.85, 1.1\nset key at screen 1.0, 0.9\n"<<
  "set style textbox opaque noborder margins 0.5, 0.5\n";

  gp << "set title 'Gradient Descent'\nset pm3d\n";

	//gp << "set border 4095 front lt black linewidth 1.000 dashtype solid\n";
	//gp << "set pm3d implicit at s\nset pm3d scansbackward\n";
	gp << "unset surface\n";

	//												  h(x)						y
  //gp << "splot (  (1/(2*3)) * ( ( ((x*0.8)+(y*0.5)) - (x**3) )**2 )  )  \n";

	gp << "splot (1/1)*( ( ((x*1.8)+(y*1.5)) - (0.02) )**2 )  \n";

	//gp << "splot x*y**2 \n";

	//gp << "plot '-' with lines title 'cubic', '-' with points title 'circle'\n";
	//gp.send1d(xy_pts_A);
	//gp.send1d(xy_pts_B);

	//gp << "pause -1\n";



}
