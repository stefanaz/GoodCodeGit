//
// GLogChecker.cxx
//
// $Author: gutsche $
// $Date: 2003/12/05 21:04:23 $
// $Revision: 1.6 $
//

#include <GLogChecker.h>

#ifndef GUT_GInclude
#include <GInclude.h>
#endif

#ifndef ROOT_TSystem
#include <TSystem.h>
#endif

using namespace std;

#ifndef __CINT__
ClassImp(GLogChecker)
#endif

//_____________________________________________________________
// GLogChecker
// checks logfiles for terms give in cardfile, makes error list
//
//
GLogChecker::GLogChecker(Int_t argc, char **argv) : TObject() {
  //
  // GLogChecker default constructor
  if ( gDebug ) cout << "GLogChecker::GLogChecker ctor called" << endl;

  // set errorignorlevel to neglect light error messages
  if ( !gDebug )
    gErrorIgnoreLevel = 2001;

  if ( !(this-Init(argc, argv)) )
    cout << "GLogChecker::GLogChecker() there was an error!" << endl;

  if ( !this->CheckLogFiles(argc, argv) )
    cout << "GLogChecker::GLogChecker() there was an error with checking the logfiles!" << endl;
    

}

//_____________________________________________________________

GLogChecker::~GLogChecker() {
  //
  // GLogChecker default destructor
  if ( gDebug ) cout << "GLogChecker::~GLogChecker dtor called" << endl;

  if ( gCards             != 0 ) delete gCards;
  if ( gLister            != 0 ) delete gLister;

}

//_____________________________________________________________

TString GLogChecker::ReturnHelpMessage() {
  //
  // return help message
  if ( gDebug ) cout << "GLogChecker::ReturnHelpMessage() called" << endl;

  TString dummy;

  dummy.Append("\n");
  dummy.Append("----------------------------------------------------------------------\n");
  dummy.Append("logchecker.exe [logchecker cards-file] [list of log-files to check]\n");
  dummy.Append("----------------------------------------------------------------------\n");
  dummy.Append("options:\n");
  dummy.Append("-help                     : print this message\n");
  dummy.Append("--help                    : print this message\n");
  dummy.Append("----------------------------------------------------------------------\n");
  
  return dummy;

}

//_____________________________________________________________

Bool_t GLogChecker::PrintHelpMessage() {
  //
  // print help message
  if ( gDebug ) cout << "GLogChecker::PrintHelpMessage() called" << endl;

  cout << this->ReturnHelpMessage() << endl;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GLogChecker::Init(Int_t argc, char **argv) {
  //
  // init logchecker
  if ( gDebug ) cout << "GLogChecker::Init() called" << endl;

  // check for command line parameters
  if ( argc <= 1 ) {
    this->PrintHelpMessage();
    return kTRUE;
  }

  TString input[argc];

  for ( Int_t i = 0; i < argc; i++ ) {
    input[i] = argv[i];
  }

  // check if first argument is a cards file and exists
  if ( !input[1].EndsWith(".cards") ) {
    char* dir = gSystem->Which(input[1].Data(),"");
    if ( !dir ) {
      this->PrintHelpMessage();
      return kTRUE;
    }
  }
  
  GCards *cards = new GCards(argv[1]);
  if ( !cards ) {
    cout << "GLogChecker::Init() there was an error with creating the cards-object!" << endl;
    return kTRUE;
  }

  GLister *lister = new GLister(gSystem->pwd());
  if ( !lister ) {
    cout << "GLogChecker::Init() there was an error with creating the lister-object!" << endl;
    return kTRUE;
  }

  //switch on error list after constructor, get control of initialization and finalization
  gCards->SetListsErrorList(kTRUE);

  return kTRUE;
}

//_____________________________________________________________

Bool_t GLogChecker::CheckLogFiles(Int_t argc, char **argv) {
  //
  // check logfiles
  if ( gDebug ) cout << "GLogChecker::CheckLogFiles() called" << endl;

  for ( Int_t i = 2; i < argc; i++ ) {
    this->CheckLogFile(argv[i]);
  }


  return kTRUE;
}

//_____________________________________________________________

Bool_t GLogChecker::CheckLogFile(TString file) {
  //
  // check logfile
  if ( gDebug ) cout << "GLogChecker::CheckLogFile() called" << endl;


  // init error list
  TString output(file);
  output.ReplaceAll(".log",".check");
  output.ReplaceAll(".gz",""); 
  gLister->InitErrorList(output.Data());

  // generate line counter
  Int_t linenumber = 0;
  
  // read in file to check
  // check for gzipped
  Bool_t gzipped = kFALSE;
  TString line = "";
  TString input(file);
    
  if ( input.Contains(".gz") ) {
    gzipped = kTRUE;
    TString command = "";
    command.Append("gunzip ");
    command.Append(input.Data());
    gSystem->Exec(command.Data());
    input.ReplaceAll(".gz","");
  }
  ifstream input_stream(input.Data(),ios::in);

  // make variables for counting terms
  Int_t counts[gCards->GetLogCountNumber()];

  // initialization of count variables
  for ( Int_t i = 0; i < gCards->GetLogCountNumber(); i++ ) {
    counts[i] = 0;
  }

  // loop over lines
  while ( line.ReadLine(input_stream) ) {
    linenumber++;
    line.ToLower();
    if ( !line.BeginsWith("c") ) {
      for ( Int_t i = 0; i < gCards->GetLogTermNumber(); i++ ) {
	if ( line.Contains((gCards->GetLogTerms())[i].Data()) ) {
	  TString dummy = "";
	  dummy.Append("Line: ");
	  dummy += linenumber;
	  dummy.Append(" ");
	  dummy.Append((gCards->GetLogTerms())[i].Data());
	  dummy.Append(" line: ");
	  dummy.Append(line.Data());
	  gLister->FillErrorList(dummy.Data());
	}
      }
      for ( Int_t i = 0; i < gCards->GetLogCountNumber(); i++ ) {
	if ( line.Contains((gCards->GetLogCountTerms())[i].Data()) ) {
	  counts[i] += 1;
	}
      }
    }
  }

  // output for counts
  for ( Int_t i = 0; i < gCards->GetLogCountNumber(); i++ ) {
    TString dummy = "";
    dummy.Append("Counts for: \"");
    dummy.Append((gCards->GetLogCountTerms())[i].Data());
    dummy.Append("\" Counted: ");
    dummy += counts[i];
    dummy.Append(" times.");
    gLister->FillErrorList(dummy.Data());
  }

  if ( gzipped ) {
    TString command = "";
    command.Append("gzip -9 ");
    command.Append(input.Data());
    gSystem->Exec(command.Data());
  }

  gLister->FinalizeErrorList();

  return kTRUE;
}
