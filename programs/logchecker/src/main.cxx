//
// main.cxx
//
// $Author: gutsche $
// $Date: 2002/11/06 08:50:10 $
// $Revision: 1.1 $
//

#include <iostream>

#ifndef GUT_GLogChecker
#include <GLogChecker.h>
#endif

using namespace std;

int main(int argc, char **argv) {
  
  // set debug mode
#ifdef CF__DEBUG
  gDebug = 1;
#endif

  GLogChecker *checker = new GLogChecker(argc, argv);
  delete checker;

  return 0;
}
