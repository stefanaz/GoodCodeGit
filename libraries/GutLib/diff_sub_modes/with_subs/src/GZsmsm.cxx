//
// GZsmsm.cxx
//
// $Author: gutsche $
// $Date: 2003/10/05 16:19:35 $
// $Revision: 1.2 $
//

#include <GZsmsm.h>
#include <iostream>
#include <fstream>
#include <strstream>

#ifndef ROOT_TSystem
#include <TSystem.h>
#endif

using namespace std;

#ifndef __CINT__
ClassImp(GZsmsm)
#endif

//_____________________________________________________________
// GZsmsm
//
// program for generating files for zsmsm release software manager wants
// list of files, which have changed, which were removed and which are
// new 
//
// therefore, a diff for the complete cvs repository is between the
// previous and the current zsmsm release, named by the dev-version tags
// from the versioning page at http://zevis.desy.de
//
// ====================================================================
// execute from $HOME/zeus/zevis
// ====================================================================    
//
// input parameters:
//
// $1: dev-tag of previous zsmsm release
// $2: dev-tag of current zsmsm release
//
// 
//
//
GZsmsm::GZsmsm(Int_t argc, char **argv) : TObject() {
  //
  // GZsmsm default constructor
  if ( gDebug ) cout << "GZsmsm::GZsmsm ctor called" << endl;

  if ( !(this-Init(argc, argv)) )
    cout << "GZsmsm::GZsmsm() there was an error!" << endl;

   if ( !this->RemoveOldFiles() )
     cout << "GZsmsm::GZsmsm() there was an error with removing the old files!" << endl;

   if ( !this->CvsDiff() )
     cout << "GZsmsm::GZsmsm() there was an error generating the cvs diff files!" << endl;

   if ( !this->CvsDiff() )
     cout << "GZsmsm::GZsmsm() there was an error generating the cvs diff files!" << endl;
   
   if ( !this->CheckErr() )
     cout << "GZsmsm::GZsmsm() there was an error checking err.txt!" << endl;

   if ( !this->CheckDiff() )
     cout << "GZsmsm::GZsmsm() there was an error checking diff.txt!" << endl;

   if ( !this->RemoveTempFiles() )
     cout << "GZsmsm::GZsmsm() there was an removing the temporary files!" << endl;

}

//_____________________________________________________________

GZsmsm::~GZsmsm() {
  //
  // GZsmsm default destructor
  if ( gDebug ) cout << "GZsmsm::~GZsmsm dtor called" << endl;

}

//_____________________________________________________________

TString GZsmsm::ReturnHelpMessage() {
  //
  // return help message
  if ( gDebug ) cout << "GZsmsm::ReturnHelpMessage() called" << endl;

  TString dummy;

  dummy.Append("\n");
  dummy.Append("--------------------------------------------------------------------------------\n");
  dummy.Append("zsmsm-release.exe [tag of previous zsmsm release] [tag of current zsmsm release]\n");
  dummy.Append("--------------------------------------------------------------------------------\n");
  dummy.Append("Be sure to be in the zevis cvs checkout directory!\n");
  dummy.Append("--------------------------------------------------------------------------------\n");
  dummy.Append("options:\n");
  dummy.Append("-help                     : print this message\n");
  dummy.Append("--help                    : print this message\n");
  dummy.Append("--------------------------------------------------------------------------------\n");
  
  return dummy;

}

//_____________________________________________________________

Bool_t GZsmsm::PrintHelpMessage() {
  //
  // print help message
  if ( gDebug ) cout << "GZsmsm::PrintHelpMessage() called" << endl;

  cout << this->ReturnHelpMessage() << endl;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GZsmsm::Init(Int_t argc, char **argv) {
  //
  // init zsmsm-releaser
  if ( gDebug ) cout << "GZsmsm::Init() called" << endl;

  // check for command line parameters
  if ( argc <= 2 ) {
    this->PrintHelpMessage();
    return kTRUE;
  }

  TString input[argc];

  for ( Int_t i = 0; i < argc; i++ ) {
    input[i] = argv[i];
  }

  // put options in strings
  previous = argv[1];
  current  = argv[2];

  return kTRUE;
}

//_____________________________________________________________

Bool_t GZsmsm::RemoveOldFiles() {
  //
  // remove old files
  if ( gDebug ) cout << "GZsmsm::RemoveOldFiles() called" << endl;

  gSystem->Exec("rm -f diff.txt err.txt new.txt removed.txt changed.txt");

  return kTRUE;
}

//_____________________________________________________________

Bool_t GZsmsm::CvsDiff() {
  //
  // execute cvs diff

  TString cmd = "cvs diff -r ";
  cmd.Append(previous.Data());
  cmd.Append(" -r ");
  cmd.Append(current.Data());
  cmd.Append(" ZClient ZEvtBuild ZGeomBuild ZesAgent ZevLib ZevLibX cmdtop > diff.txt 2> err.txt");

  gSystem->Exec(cmd.Data());

  return kTRUE;
}

//_____________________________________________________________

Bool_t GZsmsm::CheckErr() {
  //
  // check err.txt
  if ( gDebug ) cout << "GZsmsm::CheckErr() called" << endl;

  ifstream input("err.txt");
  ofstream outnew("new.txt");
  ofstream outremoved("removed.txt");

  TString line = "";

  TString replacenew = "cvs diff: tag ";
  replacenew.Append(previous.Data());
  replacenew.Append(" is not in file ");

  TString replaceremoved = "cvs diff: tag ";
  replaceremoved.Append(current.Data());
  replaceremoved.Append(" is not in file ");

  while ( line.ReadLine(input) ) {
    if ( line.Contains(previous.Data()) ) {
      line.ReplaceAll(replacenew.Data(),"");
      outnew << line.Data() << endl;
    } else if ( line.Contains(current.Data()) ) {
      line.ReplaceAll(replaceremoved.Data(),"");
      outremoved << line.Data() << endl;
    }
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GZsmsm::CheckDiff() {
  //
  // check diff.txt
  if ( gDebug ) cout << "GZsmsm::CheckDiff() called" << endl;

  ifstream input("diff.txt");
  ofstream out("changed.txt");

  TString line = "";

  TString replace = "Index: ";

  while ( line.ReadLine(input) ) {
    if ( line.Contains(replace.Data()) ) {
      line.ReplaceAll(replace.Data(),"");
      out << line.Data() << endl;
    }
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GZsmsm::RemoveTempFiles() {
  //
  // remove temp files
  if ( gDebug ) cout << "GZsmsm::RemoveTempFiles() called" << endl;

  gSystem->Exec("rm -f diff.txt err.txt");

  return kTRUE;
}
