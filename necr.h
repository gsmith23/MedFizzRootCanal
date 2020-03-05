#include <iostream> 

using namespace std;

double calculateNECR(double TR = 0.6, 
		     double RR = 0.1, 
		     double SR = 0.3);

double calculateNECR(double TR, 
		     double RR, 
		     double SR){

  double NECR = 0;
 
  cout << endl;
  cout << " ------------------------------------ "  << endl;
  cout << " ------------------------------------ "  << endl;
  cout << "         Calculating NECR             "  << endl;
  cout << "    (Noise Equivalent Count Rate)     "  << endl;	
  cout << " ------------------------------------ "  << endl;
  
  NECR = TR*TR/(TR + SR + RR);
  
  cout << " ------------------------------------ "  << endl;
  cout << " ------------------------------------ "  << endl;
  cout << " The NECR is " << NECR << " cps "        << endl;
  cout << " ------------------------------------ "  << endl;
  cout << " ------------------------------------ "  << endl;

  return NECR;
}	       

