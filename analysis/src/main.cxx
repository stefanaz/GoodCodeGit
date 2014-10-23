// main.cxx
//
// $Author: gutsche $
// $Date: 2003/12/04 19:34:00 $
// $Revision: 1.6 $
//

#include <iostream>

#ifndef GUT_GAnalysis
#include <GAnalysis.h>
#endif

#ifndef ROOT_TString
#include <TString.h>
#endif

using namespace std;

int main(int argc, char **argv) {
  if ( gDebug ) cout << "main called" << endl;

  // set debug mode
// #ifdef CF__DEBUG
//   gDebug = 1;
// #endif

  // variables
  TString cardfile;

  TString helptext = "";
  helptext.Append("\n");
  helptext.Append("analysis [options] card-filename\n");
  helptext.Append("\n");
  helptext.Append("Options:\n");
  helptext.Append("---------------------------------------------------------------------------------\n");
  helptext.Append("-help                   : this message\n");
  helptext.Append("--help                  : this message\n");
  helptext.Append("card-filename           : card-file to be used, default ../cards/analysis.cards\n");

  if ( argc >= 1 ) {
    // put argv in TStrings

    TString opt[argc];
    for ( Int_t i = 0; i < argc; i++ ) {
      opt[i] = argv[i];
    }

    // help message
    for ( Int_t i = 1; i < argc; i++ ) {
      TString tempopt = opt[i];
      tempopt.ToUpper();
      if ( tempopt.Contains("HELP") ) {
	cout << helptext.Data() << endl;
	return 0;
      }
    }

    // card file
    if ( argc == 1 )
      cardfile = "../cards/analysis.cards";
    else if ( opt[argc-1].Length() > 0 ) {
      cardfile = opt[argc-1];
    }
  }

  GAnalysis *analysis = new GAnalysis(cardfile.Data());
  analysis->DoAnalysis();

  delete analysis;
  return 0;
}

