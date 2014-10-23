//
// main.cxx
//
// $Author: gutsche $
// $Date: 2002/10/28 18:40:40 $
// $Revision: 1.2 $
//

#include <iostream>

#ifndef GUT_GCardManager
#include <GCardManager.h>
#endif

using namespace std;

int main(int argc, char **argv) {
  
  // set debug mode
#ifdef CF__DEBUG
  gDebug = 1;
#endif

  if ( argc <= 1 ) {
    GCardManager *manager = new GCardManager();
    manager->HelpMessage();
    delete manager;
  } else {
    GCardManager *manager = new GCardManager(argc, argv);
    delete manager;
  }

  return 0;
}
