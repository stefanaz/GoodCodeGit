//
// GLister.cxx
//
// $Author: gutsche $
// $Date: 2004/09/21 18:30:58 $
// $Revision: 1.31 $
//

#include <GLister.h>

#ifndef GUT_GInclude
#include <GInclude.h>
#endif

#ifndef __CINT__
ClassImp(GLister)
#endif

GLister *gLister = 0;

//__________________________________________________________________
// GLister
// class for ascii lists of Properties
//
//
GLister::GLister(TString path) : TObject() {
  //
  // GLister default contructor
  if ( gDebug ) cout << endl << "GLister::GLister() default ctor called" << endl << endl;

  // initialize global pointer
  gLister = this;

  // initialize path
  fPath = path;

  // initialize strings for selection list
  fSelList96p = "";
  fSelList97p = "";
  fSelList98e = "";
  fSelList99e = "";
  fSelList99p = "";
  fSelList00p = "";
  fSelList02p = "";
  fSelList03p = "";
  fSelList04p = "";
  fSelListMC  = "";
  fSelListGen = "";

  // initialize list pointers
  fErrorList     = 0;
  fProcEvents    = 0;
  fSelectionList = 0;
  fOutputList    = 0;

  // initialize variables
  fError         = kFALSE;
  fOutput        = kFALSE;
  fSelection     = kFALSE;
  fFileName      = "";
  fNewFile       = kFALSE;


  // create lists

  this->GenerateLists();

}

//___________________________________________________________________

GLister::~GLister() {
  //
  // GLister standard destructor
  if ( gDebug ) cout << endl << "GLister::~GLister() dtor called" << endl << endl;

  // delete if pointer is valid
  if ( fProcEvents ) delete fProcEvents;
  if ( fErrorList ) delete fErrorList;
  if ( fSelectionList ) delete fSelectionList;
  if ( fOutputList ) delete fOutputList;

}

//__________________________________________________________________

Bool_t GLister::GenerateLists() {
  //
  // generate ascii lists
  if ( gDebug ) cout << endl << "GLister::GenerateLists() called" << endl << endl;

  TString name = "processed_events";
  name.Append(gCards->GetAddToNames()->Data());
  name.Append(".list");
  this->InitProcEvents(name.Data());
  name = "error";
  name.Append(gCards->GetAddToNames()->Data());
  name.Append(".list");
  this->InitErrorList(name.Data());
  name = "selection";
  name.Append(gCards->GetAddToNames()->Data());
  name.Append(".list");
  this->InitSelectionList(name.Data());
  name = "output";
  name.Append(gCards->GetAddToNames()->Data());
  name.Append(".list");
  this->InitOutputList(name.Data());

  return kTRUE;
}

//__________________________________________________________________

Bool_t GLister::InitProcEvents(TString listname) {
  //
  // generate ascii lists
  if ( gDebug ) cout << endl << "GLister::InitProcEvents() called" << endl << endl;

  if ( gCards->GetListsProcEvents() ) {
    TString dummy(fPath);
    dummy.Append("/");
    dummy.Append(listname);
    fProcEvents = new ofstream(dummy.Data());

    if ( gHeader != 0 )
      gHeader->Header(fProcEvents,"List of processed events");
    else
      this->Header(fProcEvents,"List of processed events");
  }

  return kTRUE;
}

//__________________________________________________________________

Bool_t GLister::InitErrorList(TString listname) {
  //
  // init error list
  if ( gDebug ) cout << endl << "GLister::InitErrorList() called" << endl << endl;

  if ( gCards->GetListsErrorList() ) {
    TString dummy(fPath);
    dummy.Append("/");
    dummy.Append(listname);
    fErrorList = new ofstream(dummy.Data());
    if ( gHeader != 0 )
      gHeader->Header(fErrorList,"List of errors");
    else
      // only for logchecker
      this->Header(fErrorList,"List of LogChecker output");
  }
  return kTRUE;
}

//__________________________________________________________________

Bool_t GLister::InitSelectionList(TString listname) {
  //
  // init selection list
  if ( gDebug ) cout << endl << "GLister::InitSelectionList() called" << endl << endl;

  if ( gCards->GetListsSelectionList() ) {
    TString dummy(fPath);
    dummy.Append("/");
    dummy.Append(listname);
    fSelectionList = new ofstream(dummy.Data());
    if ( gHeader != 0 )
      gHeader->Header(fSelectionList,"Selection after all cuts");
    else
      // only for logchecker
      this->Header(fSelectionList,"List of LogChecker output");
  }
  return kTRUE;
}

//__________________________________________________________________

Bool_t GLister::InitOutputList(TString listname) {
  //
  // init output list
  if ( gDebug ) cout << endl << "GLister::InitOutputList() called" << endl << endl;

  if ( gCards->GetListsOutputList() ) {
    TString dummy(fPath);
    dummy.Append("/");
    dummy.Append(listname);
    fOutputList = new ofstream(dummy.Data());
    if ( gHeader != 0 )
      gHeader->Header(fOutputList,"Outputs after all cuts");
    else
      // only for logchecker
      this->Header(fOutputList,"List of LogChecker output");
  }
  return kTRUE;
}

//__________________________________________________________________

Bool_t GLister::FillLists() {
  //
  // fill ascii lists
  if ( gDebug ) cout << endl << "GLister:FillLists() called" << endl << endl;

  if ( gCards->GetListsProcEvents() ) {
    *fProcEvents << setw(5) << setfill(' ') << gData->Getrunnr() << " " << setw(6) << setfill(' ') << gData->Geteventnr() << endl;
  }

  if ( gHeader->GetAllCuts() || fSelection ) {
    this->FillSelectionList(gData->Getrunnr(), gData->Geteventnr());
  }

  this->FillOutputList(gData->Getrunnr(), gData->Geteventnr());

  return kTRUE;

}

//__________________________________________________________________

Bool_t GLister::FinalizeLists() {
  //
  // fill ascii lists
  if ( gDebug ) cout << endl << "GLister:FinalizeLists() called" << endl << endl;

  this->FinalizeProcEvents();
  this->FinalizeErrorList();
  this->FinalizeSelectionList();
  this->FinalizeOutputList();

  return kTRUE;
}

//__________________________________________________________________

Bool_t GLister::FinalizeProcEvents() {
  //
  // fill ascii lists
  if ( gDebug ) cout << endl << "GLister:FinalizeProcEvents() called" << endl << endl;

  if ( gCards->GetListsProcEvents() ) {
    
    // fill with last line

    if ( gHeader != 0 )
      gHeader->Footer(fProcEvents,"List of processed events");
    else
      this->Footer(fProcEvents,"List of processed events");

    delete fProcEvents;
    fProcEvents = 0;

  }

  return kTRUE;
}

//__________________________________________________________________

Bool_t GLister::FinalizeErrorList() {
  //
  // fill ascii lists
  if ( gDebug ) cout << endl << "GLister:FinalizeErrorList() called" << endl << endl;


  if ( gCards->GetListsErrorList() ) {

    // fill with last line
    if ( gHeader != 0 )
      gHeader->Footer(fErrorList,"List of errors");
    else
      this->Footer(fErrorList,"List of LogChecker output");

    delete fErrorList;
    fErrorList = 0;

  }
  return kTRUE;
}

//__________________________________________________________________

Bool_t GLister::FinalizeSelectionList() {
  //
  // fill ascii lists
  if ( gDebug ) cout << endl << "GLister:FinalizeSelectionList() called" << endl << endl;
  
  if ( gCards->GetListsSelectionList() ) {
    // fill run period strings in list

    if ( fSelList96p.Length() > 0 ) {
      this->SelListHeader(fSelectionList,"96p");
      *fSelectionList << fSelList96p.Data() << endl;
    }
    
    if ( fSelList97p.Length() > 0 ) {
      this->SelListHeader(fSelectionList,"97p");
      *fSelectionList << fSelList97p.Data() << endl;
    }
    
    if ( fSelList98e.Length() > 0 ) {
      this->SelListHeader(fSelectionList,"98e");
      *fSelectionList << fSelList98e.Data() << endl;
    }
    
    if ( fSelList99e.Length() > 0 ) {
      this->SelListHeader(fSelectionList,"99e");
      *fSelectionList << fSelList99e.Data() << endl;
    }
    
    if ( fSelList99p.Length() > 0 ) {
      this->SelListHeader(fSelectionList,"99p");
      *fSelectionList << fSelList99p.Data() << endl;
    }
    
    if ( fSelList00p.Length() > 0 ) {
      this->SelListHeader(fSelectionList,"00p");
      *fSelectionList << fSelList00p.Data() << endl;
    }
    
    if ( fSelList02p.Length() > 0 ) {
      this->SelListHeader(fSelectionList,"02p");
      *fSelectionList << fSelList02p.Data() << endl;
    }
    
    if ( fSelList03p.Length() > 0 ) {
      this->SelListHeader(fSelectionList,"03p");
      *fSelectionList << fSelList03p.Data() << endl;
    }

    if ( fSelList04p.Length() > 0 ) {
      this->SelListHeader(fSelectionList,"04p");
      *fSelectionList << fSelList04p.Data() << endl;
    }
    
    if ( fSelListMC.Length() > 0 ) {
      this->SelListHeader(fSelectionList,"MC");
      *fSelectionList << fSelListMC.Data() << endl;
    }

    if ( fSelListGen.Length() > 0 ) {
      this->SelListHeader(fSelectionList,"generic");
      *fSelectionList << fSelListGen.Data() << endl;
    }

    // fill last
    if ( gHeader != 0 )
      gHeader->Footer(fSelectionList,"Selection after all cuts");
    else
      this->Footer(fSelectionList,"List of LogChecker output");

    delete fSelectionList;
    fSelectionList = 0;

  }
  return kTRUE;
}

//__________________________________________________________________

Bool_t GLister::FinalizeOutputList() {
  //
  // fill ascii lists
  if ( gDebug ) cout << endl << "GLister:FinalizeOutputList() called" << endl << endl;
  
  if ( gCards->GetListsOutputList() ) {

    // fill last
    if ( gHeader != 0 )
      gHeader->Footer(fOutputList,"Output after all cuts");
    else
      this->Footer(fOutputList,"List of LogChecker output");

    delete fOutputList;
    fOutputList = 0;

  }
  return kTRUE;
}

//__________________________________________________________________

Bool_t GLister::FillErrorList(TString message) {
  //
  // fill error list, init list for the first time, set flags for error in analysis and error in event
  if ( gDebug ) cout << endl << "GLister:FillErrorList(const char* message) called" << endl << endl;
  
  if ( gCards->GetListsErrorList() ) {

    // generate event header if message is first error message of event
    if ( !fError && ( gData != 0 )) {
      fError = kTRUE;
      *fErrorList << endl << "run: " << setw(5) << setfill(' ') << gData->Getrunnr() << " event: " << setw(6) << setfill(' ') << gData->Geteventnr() << endl << endl;
    }
    
    *fErrorList << message.Data() << endl;

  }

  return kTRUE;
}

//__________________________________________________________________

Bool_t GLister::FillSelectionList(Int_t run, Int_t event) {
  //
  // fill selection list strings
  if ( gDebug ) cout << endl << "GLister:FillSelectionList(Int_t run, Int_t event) called" << endl << endl;
  
  if ( gCards->GetListsSelectionList() ) {

    TString dummy = "";
    dummy += run;
    dummy.Append(" ");
    dummy += event;
    dummy.Append("\n");
    if ( run == 1 ) {
      if ( fNewFile ) {
	fSelListMC.Append("File: ");
	fSelListMC.Append(fFileName);
	fSelListMC.Append("\n");
	fNewFile = kFALSE;
      }
      fSelListMC.Append(dummy);
    }else if ( ( run >= gGeneral->Get96p_low() ) && ( run <= gGeneral->Get96p_up() ) )
      fSelList96p.Append(dummy);
    else if ( ( run >= gGeneral->Get97p_low() ) && ( run <= gGeneral->Get97p_up() ) )
      fSelList97p.Append(dummy);
    else if ( ( run >= gGeneral->Get98e_low() ) && ( run <= gGeneral->Get98e_up() ) )
      fSelList98e.Append(dummy);
    else if ( ( run >= gGeneral->Get99e_low() ) && ( run <= gGeneral->Get99e_up() ) )
      fSelList99e.Append(dummy);
    else if ( ( run >= gGeneral->Get99p_low() ) && ( run <= gGeneral->Get99p_up() ) )
      fSelList99p.Append(dummy);
    else if ( ( run >= gGeneral->Get00p_low() ) && ( run <= gGeneral->Get00p_up() ) )
      fSelList00p.Append(dummy);
    else if ( ( run >= gGeneral->Get02p_low() ) && ( run <= gGeneral->Get02p_up() ) )
      fSelList02p.Append(dummy);
    else if ( ( run >= gGeneral->Get03p_low() ) && ( run <= gGeneral->Get03p_up() ) )
      fSelList03p.Append(dummy);
    else if ( ( run >= gGeneral->Get04p_low() ) && ( run <= gGeneral->Get04p_up() ) )
      fSelList04p.Append(dummy);
    else
      fSelListGen.Append(dummy);

  }

  return kTRUE;
}

//__________________________________________________________________

Bool_t GLister::FillOutputList(Int_t run, Int_t event) {
  //
  // fill output list strings
  if ( gDebug ) cout << endl << "GLister:FillOutputList() called" << endl << endl;
  
  if ( gCards->GetListsOutputList() ) {

    if ( fOutput || (gCards->GetListsOutputSelected() && gHeader->GetAllCuts() ) || gCards->GetListsOutputAll() ) {

      TString dummy = "";
      dummy += run;
      dummy.Append(" ");
      dummy += event;
      dummy.Append("\n\n");
      dummy.Append(gHeader->PrintAllCuts());
      dummy.Append("\n");
    
      *fOutputList << dummy.Data();
      
      TString selection = "OUTPUTLIST";
      if ( gCards->GetListsOutputListGGENERAL() )
	selection.Append(",GGENERAL");
      if ( gCards->GetListsOutputListRUNS() )
	selection.Append(",RUNS");
      if ( gCards->GetListsOutputListMUONS() )
	selection.Append(",MUONS");
      if ( gCards->GetListsOutputListCAL() )
	selection.Append(",CAL");
      if ( gCards->GetListsOutputListJETS() )
	selection.Append(",JETS");
      if ( gCards->GetListsOutputListMJMATCHS() )
	selection.Append(",MJMATCHS");
      if ( gCards->GetListsOutputListTJMATCHS() )
	selection.Append(",TJMATCHS");
      if ( gCards->GetListsOutputListDIMUONS() )
	selection.Append(",DIMUONS");
      if ( gCards->GetListsOutputListMVD() )
	selection.Append(",MVD");
      if ( gCards->GetListsOutputListSINISTRA() )
	selection.Append(",SINISTRA");
      if ( gCards->GetListsOutputListTRACKS() )
	selection.Append(",TRACKS");
      if ( gCards->GetListsOutputListVERTEX() )
	selection.Append(",VERTEX");
      if ( gCards->GetListsOutputListZUFO() )
	selection.Append(",ZUFO");
      if ( gCards->GetListsOutputListMC() )
	selection.Append(",MC");

      gAnalysis->Print(selection.Data());

    }

  }
  return kTRUE;
}

//__________________________________________________________________

Bool_t GLister::FillOutputList(TString string) {
  //
  // fill output list with defined string
  if ( gDebug ) cout << endl << "GLister:FillOutputList(const char*) called" << endl << endl;
  
  if ( gCards->GetListsOutputList() ) {

    *fOutputList << string.Data();

  }
  return kTRUE;
}

//__________________________________________________________________

Bool_t GLister::ResetLists() {
  //
  // reset lists for new event
  if ( gDebug ) cout << endl << "GLister:Reset() called" << endl << endl;

  // flag for error in event set to kFALSE
  fError = kFALSE;

  // output flag
  fOutput = kFALSE;
  fSelection = kFALSE;

  return kTRUE;
}

//__________________________________________________________________

Bool_t GLister::Header(ofstream *stream, TString title) {
  //
  // writes header to output file if gHeader is not available
  if ( gDebug ) cout << endl << "GLister:Header(ofstream *stream, TString title) called" << endl << endl;

  TString dummy;

  dummy.Append("======================================================================\n");
  dummy.Append(title);
  dummy.Append("\nStart\n");
  dummy.Append("======================================================================\n");

  *stream << dummy.Data() << endl;

  return kTRUE;
}

//__________________________________________________________________

Bool_t GLister::Footer(ofstream *stream, TString title) {
  //
  // writes header to output file if gFooter is not available
  if ( gDebug ) cout << endl << "GLister:Footer(ofstream *stream, TString title) called" << endl << endl;

  TString dummy;

  dummy.Append("======================================================================\n");
  dummy.Append(title);
  dummy.Append("\nEnd\n");
  dummy.Append("======================================================================\n");

  *stream << dummy.Data() << endl;

  return kTRUE;
}

//__________________________________________________________________

Bool_t GLister::SelListHeader(ofstream *stream, TString title) {
  //
  // writes selection list header for run period
  if ( gDebug ) cout << endl << "GLister:SelListHeader(ofstream *stream, TString title) called" << endl << endl;

  TString dummy;

  dummy.Append("======================================================================\n");
  dummy.Append("Selection after cuts for period: ");
  dummy.Append(title);
  dummy.Append("\n");
  dummy.Append("======================================================================\n");

  *stream << dummy.Data() << endl;

  return kTRUE;
}
