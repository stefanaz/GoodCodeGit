//
// main.cxx
//
// $Author: gutsche $
// $Date: 2003/12/02 16:21:51 $
// $Revision: 1.4 $
//

#include <iostream>

#ifndef GUT_GMerger
#include <GMerger.h>
#endif

#ifndef ROOT_TString
#include <TString.h>
#endif

using namespace std;

int main(int argc, char **argv) {
  
  // set debug mode
#ifdef CF__DEBUG
  gDebug = 1;
#endif

  GMerger *merger = new GMerger(argc,argv);
  delete merger;

  return 0;
}
