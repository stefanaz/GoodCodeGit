//
// main.cxx
//
// $Author: gutsche $
// $Date: 2003/01/27 13:43:02 $
// $Revision: 1.1 $
//

#include <iostream>

#ifndef GUT_GZsmsm
#include <GZsmsm.h>
#endif

using namespace std;

int main(int argc, char **argv) {
  
  // set debug mode
#ifdef CF__DEBUG
  gDebug = 1;
#endif

  GZsmsm *release = new GZsmsm(argc, argv);
  delete release;

  return 0;
}
