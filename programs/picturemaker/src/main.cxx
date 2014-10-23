//
// main.cxx
//
// $Author: gutsche $
// $Date: 2003/05/14 09:56:29 $
// $Revision: 1.1 $
//

#include <iostream>

#ifndef GUT_GPictureMaker
#include <GPictureMaker.h>
#endif

using namespace std;

int main(int argc, char **argv) {
  
  // set debug mode
#ifdef CF__DEBUG
  gDebug = 1;
#endif

  GPictureMaker *maker = new GPictureMaker(argc, argv);
  delete maker;

  return 0;
}
