//
// GAnalysis.cxx
//
// $Author: roloff $
// $Date: 2009/07/30 17:13:45 $
// $Revision: 1.46 $
//

#include <GAnalysis.h>

#ifndef GUT_GInclude
#include <GInclude.h>
#endif

#ifndef ROOT_TChain
#include <TChain.h>
#endif

#ifndef ROOT_TFile
#include <TFile.h>
#endif

#ifndef ROOT_TDirectory
#include <TDirectory.h>
#endif

#ifndef ROOT_TTree
#include <TTree.h>
#endif

#ifndef ROOT_TList
#include <TList.h>
#endif

#ifndef __CINT__
ClassImp(GAnalysis)
#endif

GAnalysis *gAnalysis = 0;

//__________________________________________________________________
// GAnalysis
// Gutsche analysis class
//
//
GAnalysis::GAnalysis(TString cardname) : TObject() {
  //
  // GAnalysis default contructor
  if ( gDebug ) cout << endl << "GAnalysis::GAnalysis(TString path) default ctor called" << endl << endl;

  // set errorignorlevel to neglect light error messages
  if ( !gDebug )
    gErrorIgnoreLevel = 2001;

  // initialize global analysis pointer;
  gAnalysis = this;

  // initialize analysis flag
  fEnableAnalysis = kTRUE;

  // initialize physics objects list
  fPhysicsObjs = new TList();

  // initialize pointers
  fChain                = 0;
  fOutputFile           = 0;
  fHistogramDir         = 0;
  fGeneralDir           = 0;
  fHeaderTree           = 0;

  this->InitAnalysis(cardname);

}

//___________________________________________________________________

GAnalysis::~GAnalysis() {
  //
  // GAnalysis standard destructor
  if ( gDebug ) cout << endl << "GAnalysis::~GAnalysis() dtor called" << endl << endl;

  if ( fEnableAnalysis ) {

    // finalize File operations
    if ( fOutputFile != 0 )
      this->FinalizeOutputFile();

    // finalize Lists
    if ( gLister != 0 )
      gLister->FinalizeLists();

    // print footer
    fHeader->Footer("Analysis Job:");

  }

  if ( fPhysicsObjs       != 0 ) delete fPhysicsObjs;

  // destroy pointers if necessary
  if ( gCards             != 0 ) delete gCards;
  if ( gLister            != 0 ) delete gLister;
  if ( gHistogrammer      != 0 ) delete gHistogrammer;
  if ( gData              != 0 ) delete gData;
  if ( fHistogramDir      != 0 ) delete fOutputFile;
  if ( fGeneralDir        != 0 ) delete fOutputFile;
  if ( fOutputFile        != 0 ) delete fOutputFile;
  if ( fChain             != 0 ) delete fChain;
}

//__________________________________________________________________

Bool_t GAnalysis::InitAnalysis(TString cardname) {
  //
  // init Analysis
  if ( gDebug ) cout << endl << "GAnalysis::InitAnalysis() called" << endl << endl;
  
  fEnableAnalysis = this->InitInclude();
  fEnableAnalysis = this->ReadControlCards(cardname);

  if ( fEnableAnalysis ) {
    fEnableAnalysis = this->CreateOutputFile();
    fEnableAnalysis = this->ChainRootFiles();
    fEnableAnalysis = this->GenerateHistogrammer();

    if ( !(new GLister(gCards->GetOutputPath()->Data())) )
      fEnableAnalysis = kFALSE;

    GGeneral *General = new GGeneral();
    fPhysicsObjs->AddLast(General);
    if ( !General || !General->IsOK() ) {
      cout << "GAnalysis:InitAnalysis() problems with General object" << endl;
      fEnableAnalysis = kFALSE;
    }

    GRuns *Runs = new GRuns();
    fPhysicsObjs->AddLast(Runs);
    if ( !Runs || !Runs->IsOK() ) {
      cout << "GAnalysis:InitAnalysis() problems with Runs object" << endl;
      fEnableAnalysis = kFALSE;
    }

    if (gCards->GetMC()&& !(gCards->GetMCLF() && gCards->GetDoFake())){
      GMCs *mc = new GMCs();
      fPhysicsObjs->AddLast(mc);
      if ( !mc || !mc->IsOK() ) {
	cout << "GAnalysis:InitAnalysis() problems with MCs object" << endl;
	fEnableAnalysis = kFALSE;
      }
    }
    GTrigger *trigger = new GTrigger();
    fPhysicsObjs->AddLast(trigger);
    if ( !trigger || !trigger->IsOK() ) {
      cout << "GAnalysis:InitAnalysis() problems with Trigger object" << endl;
      fEnableAnalysis = kFALSE;
    }

    GVertex *vertex = new GVertex();
    fPhysicsObjs->AddLast(vertex);
    if ( !vertex || !vertex->IsOK() ) {
      cout << "GAnalysis:InitAnalysis() problems with Vertex object" << endl;
      fEnableAnalysis = kFALSE;
    }
    
    GSinistra *Sinistra = new GSinistra();
    fPhysicsObjs->AddLast(Sinistra);
    if ( !Sinistra || !Sinistra->IsOK() ) {
      cout << "GAnalysis:InitAnalysis() problems with Sinistra object" << endl;
      fEnableAnalysis = kFALSE;
    }

    GCal *Cal = new GCal();
    fPhysicsObjs->AddLast(Cal);
    if ( !Cal || !Cal->IsOK() ) {
      cout << "GAnalysis:InitAnalysis() problems with Cal object" << endl;
      fEnableAnalysis = kFALSE;
    }

    GBac *Bac = new GBac();
    fPhysicsObjs->AddLast(Bac);
    if ( !Bac || !Bac->IsOK() ) {
      cout << "GAnalysis:InitAnalysis() problems with Bac object" << endl;
      fEnableAnalysis = kFALSE;
    }

    GZufo *Zufo = new GZufo();
    fPhysicsObjs->AddLast(Zufo);
    if ( !Zufo || !Zufo->IsOK() ) {
      cout << "GAnalysis:InitAnalysis() problems with Zufo object" << endl;
      fEnableAnalysis = kFALSE;
    }

    GJets *Jets = new GJets();
    fPhysicsObjs->AddLast(Jets);
    if ( !Jets || !Jets->IsOK() ) {
      cout << "GAnalysis:InitAnalysis() problems with Jets object" << endl;
      fEnableAnalysis = kFALSE;
    }

    GTracks *Tracks = new GTracks();
    fPhysicsObjs->AddLast(Tracks);
    if ( !Tracks || !Tracks->IsOK() ) {
      cout << "GAnalysis:InitAnalysis() problems with Tracks object" << endl;
      fEnableAnalysis = kFALSE;
    }

    GMuons *Muons = new GMuons();
    fPhysicsObjs->AddLast(Muons);
    if ( !Muons || !Muons->IsOK() ) {
      cout << "GAnalysis:InitAnalysis() problems with Muons object" << endl;
      fEnableAnalysis = kFALSE;
    }

    GMJMatchs *MJMatchs = new GMJMatchs();
    fPhysicsObjs->AddLast(MJMatchs);
    if ( !MJMatchs || !MJMatchs->IsOK() ) {
      cout << "GAnalysis:InitAnalysis() problems with MJMatchs object" << endl;
      fEnableAnalysis = kFALSE;
    }

    GTJMatchs *TJMatchs = new GTJMatchs();
    fPhysicsObjs->AddLast(TJMatchs);
    if ( !TJMatchs || !TJMatchs->IsOK() ) {
      cout << "GAnalysis:InitAnalysis() problems with TJMatchs object" << endl;
      fEnableAnalysis = kFALSE;
    }

    GDIMuons *DIMuons = new GDIMuons();
    fPhysicsObjs->AddLast(DIMuons);
    if ( !DIMuons || !DIMuons->IsOK() ) {
      cout << "GAnalysis:InitAnalysis() problems with DIMuons object" << endl;
      fEnableAnalysis = kFALSE;
    }
    
    GTriMuons *TriMuons = new GTriMuons();
    fPhysicsObjs->AddLast(TriMuons);
    if ( !TriMuons || !TriMuons->IsOK() ) {
      cout << "GAnalysis:InitAnalysis() problems with TriMuons object" << endl;
      fEnableAnalysis = kFALSE;
    }
    
    GMVD *mvd = new GMVD();
    fPhysicsObjs->AddLast(mvd);
    if ( !mvd || !mvd->IsOK() ) {
      cout << "GAnalysis:InitAnalysis() problems with MVD object" << endl;
      fEnableAnalysis = kFALSE;
    }

  }

  return kTRUE;
}

//__________________________________________________________________

Bool_t GAnalysis::DoAnalysis() {
  //
  // conduct analysis
  if ( gDebug ) cout << endl << "GAnalysis::DoAnalysis() called" << endl << endl;

  // ask for analysis flag
  if ( fEnableAnalysis ) {
    
    // loop start 
    Int_t start = 0;
    Int_t end   = 0;

    // file number
    Int_t filenumber   = 9999;
    Int_t eventperfile = 0;

    if ( gCards->GetStartEntry() != 0 )
      start = gCards->GetStartEntry();

    if ( gCards->GetEndEntry() != -1 ) {
      end = gCards->GetEndEntry();
      if ( end > (Int_t)fChain->GetEntries() )
	end = (Int_t)fChain->GetEntries();
    }
    else
      end = (Int_t)fChain->GetEntries();

    // set eventlist, if chosen - produce small ntuple
    // ***************************************************
    // *********** define eventlistss - begin  ***********
    // ***************************************************
    if( gCards->GetDoEventlist() ) {
      //    if( make_eventlist ) {
      fevlistfilename="evlist";
      //      fevlistfilename+=batch_run; // Oli: need to know which batch we are processing - some var?
      //      fevlistfilename+=42;
      fevlistfilename.Append(".root");
      
      ffile_ev = new TFile(fevlistfilename,"RECREATE");
      fevlist = new TEventList("fevlist","fevlist");
      cout << fevlistfilename <<" - file recreated" << endl;
    }
    else if( gCards->GetWriteEventlistNtuple() ) {
    //    else if( writesmallntuple ) {
      fevlistfilename="evlist";
      //      fevlistfilename+=batch_run;
      fevlistfilename.Append(".root");
      ffile_ev = new TFile(fevlistfilename,"READ");
      ffile_ev->cd();
      fevlist_use = (TEventList*)gDirectory->Get("fevlist");
      fevlist_use->SetDirectory(0);
      cout<<"open this eventlist: "<<endl;
      fevlist_use->Print();
      fChain->SetEventList(fevlist_use);
      cout<<"Start writing small ntuple based on TEventList! "<<endl;
      
      TString smallfilename;
      smallfilename="smallntuple";
      //      smallfilename+=batch_run;
      smallfilename.Append(".root");
      
      TFile *f2 = new TFile(smallfilename,"recreate");
      TTree *small = fChain->CopyTree("");
      small->Write();
      small->Print();
      f2 = small->GetCurrentFile();
      f2->Close();
      cout<<"Written small ntuple! "<<endl;
    }
    // ***************************************************
    // *********** define eventlistss - end  *************
    // ***************************************************
    

    // chain loop
    for ( Int_t i = start; i < end; i++) {
      
      // end loop here if we are writing out the small ntuple
      if ( gCards->GetWriteEventlistNtuple() ) break;
      //      if ( writesmallntuple ) break;

      // reset lists for new event
      gLister->ResetLists();

      // get chain entry
      fChain->GetEntry(i);
      eventperfile += 1;

      // output if file changed
      if ( fChain->GetTreeNumber() != filenumber ) {
	filenumber = fChain->GetTreeNumber();
	cout << "Processing of new file: " << fChain->GetFile()->GetName() << endl;
	gLister->SetFileName(fChain->GetFile()->GetName());
	eventperfile = 0;
      }

      // output processed events
      if ( gCards->GetEventOut() != 0 ) {
	if ( (i % gCards->GetEventOut()) == 0 ) {
	  TString output = "Processing of entry: global: ";
	  output.Append(gInclude->FormatedInt(i,8,0," "));
	  output.Append(" per file: ");
	  output.Append(gInclude->FormatedInt(eventperfile,6,0," "));
	  cout << output.Data() << endl;
	}
      }

      Bool_t run = kFALSE;
      if ( gCards->GetMC() )
	run = kTRUE;
      else if ( (gData->Getrunnr() >= gCards->GetMinimalRunnr())&&(gData->Getrunnr() <= gCards->GetMaximalRunnr()) )
	run = kTRUE;

      if ( run ) {

	// reset physics objects
	// fPhysicsObjs->ForEach(GPhysObj,Reset)();
	fPhysicsObjs->R__FOR_EACH(GPhysObj,Reset)();
	
	// process physics objects
	// fPhysicsObjs->ForEach(GPhysObj,Do)();
	fPhysicsObjs->R__FOR_EACH(GPhysObj,Do)();

	// increase counters in header
	fHeader->Increase();
	
	// determine weight
	fHeader->CheckWeight();

	// fill histos in physics objects
	// fPhysicsObjs->ForEach(GPhysObj,FillHistos)();
	fPhysicsObjs->R__FOR_EACH(GPhysObj,FillHistos)();

	// fill lists
	gLister->FillLists();

	// add event to eventlist if it fullfilled the cuts
	//     // Add to eventlist if in eventlist production mode:
	//     if( mode.Contains("make_eventlist") ) {
	//       fevlist->Enter(jentry_local);
	//       cout<<"added entry number: "<<jentry_local<<" with slected count of: "<<events_selected<<endl;
	//     }
	if( gHeader->GetAllCuts() && gCards->GetDoEventlist() ) fevlist->Enter(i);
	//	if( gHeader->GetAllCuts() && make_eventlist ) fevlist->Enter(i);

      }
      
    }
    
  } else {
    cout << endl << "GAnalysis::DoAnalysis() problems with initialization of GAnalysis" << endl << endl;
    return kFALSE;
  }

  // line to next output element
  cout << endl;

  // finalize physics objects
  // fPhysicsObjs->ForEach(GPhysObj,Finalize)();
  fPhysicsObjs->R__FOR_EACH(GPhysObj,Finalize)();
  // Write eventlist file:
  if( gCards->GetDoEventlist() ) {
    //  if( make_eventlist ) {
    // -- for ROOT 5.14  next two lines  should be commented out
    ffile_ev->Append( fevlist->Clone() );
    ffile_ev->Write();
    // -- and this one line uncommented
//     fevlist->Write();
    ffile_ev->Close();
  }

  return kTRUE;
}

//__________________________________________________________________

Bool_t GAnalysis::ReadControlCards(TString cardname) {
  //
  // read in control cards
  if ( gDebug ) cout << endl << "GAnalysis::ReadControlCards() called" << endl << endl;

  // instance of cards variables class
  GCards *fCards = new GCards(cardname);

  if ( !fCards->IsOK() ) {
    cout << endl << "GAnalysis::ReadControlCards() problems with Reading Control Cards" << endl << endl;
    return kFALSE;
  }

  if ( fCards == 0 ) {
    cout << endl << "GAnalysis::ReadControlCards() problems with Reading Control Cards" << endl << endl;
    return kFALSE;
  }

  return kTRUE;
}

//__________________________________________________________________

Bool_t GAnalysis::ChainRootFiles() {
  //
  // chain root files in fInputFilePath
  if ( gDebug ) cout << endl << "GAnalysis::ChainRootFiles() called" << endl << endl;


  if(gCards->GetHERA1() ){
    fChain  = new TChain("h1");
  } 
  else if (gCards->GetHERA2()){

    fChain = new TChain("orange");
  }

  TString dummy = gCards->GetInputFilePath()->Data();
  if ( dummy.Length() > 0 ) {
    if ( gCards->GetdCache()&&!gCards->GetMC()) {
      gSystem->Load("libdcap.so");
      gSystem->Load("libzio.so");
      TString line = "";
      TString filename = gSystem->Getenv("GUTCODEDIR");
      filename.Append("/analysis/dcache/");
      filename.Append(gCards->GetDCacheFileName());
      cout << filename << endl;
      ifstream file(filename.Data());
      while ( line.ReadLine(file) ) {
	cout << line << endl;
	fChain->Add(line);
      }
    }
    if ( gCards->GetdCache()&& gCards->GetMC()) {
      gSystem->Load("libdcap.so");
      gSystem->Load("libzio.so");
      TString line = "";
      TString filename = gSystem->Getenv("GUTCODEDIR");
      filename.Append("/analysis/dcache/");
      filename.Append(gCards->GetDCacheFileName());
      cout << filename << endl;
      ifstream file(filename.Data());
      while ( line.ReadLine(file) ) {
	cout << line << endl;
	fChain->Add(line);
      }
    } else {
      dummy.Append("/*.root");
      fChain->Add(dummy.Data());
    }
  
    if ( fChain->GetNtrees() <= 0 ) {
      cout << endl << "GAnalysis::ChainRootFiles() no files in chain, problems with InputFilePath" << endl << endl;
      return kFALSE;
    }

    new GConnectTree(fChain);

    if ( !gData->IsOK() ) {
      cout << endl << "GAnalysis() problems with GConnectTree" << endl << endl;
      return kFALSE;
    }

    return kTRUE;
  } else {
      cout << endl << "GAnalysis::ChainRootFiles() empty fInputFilePath" << endl << endl;
      return kFALSE;
  }
}

//__________________________________________________________________

Bool_t GAnalysis::CreateOutputFile() {
  //
  // create output file with name fOutputFileName
  if ( gDebug ) cout << endl << "GAnalysis::CreateOutputFile() called" << endl << endl;

  if ( (gCards->GetOutputFileName() != 0) && (gCards->GetOutputFileName()->Length() > 0) ) {
    fOutputFile = new TFile((gCards->GetOutputFileName())->Data(),"RECREATE","Output of GAnalysis",9);
  
    fHistogramDir = fOutputFile->mkdir("Histograms","Histograms");
    fGeneralDir   = fOutputFile->mkdir("Generalities","Generalities");
    
    // save time in GAnalysisHeader
    
    // make tree for single instance of GAnalysisHeader

    fHeaderTree = new TTree("general","generalities");

    fHeader = new GAnalysisHeader();

    fHeaderTree->Branch("header","GAnalysisHeader",&fHeader);

    fHeader->SetStart();
    
    // print header
    fHeader->Header("Analysis Job:");

    return kTRUE;
  } else {
    cout << endl << "GAnalysis::CreateOutputFile() problems with GCards variables" << endl << endl;
    return kFALSE;
  }
}


//__________________________________________________________________

Bool_t GAnalysis::FinalizeOutputFile() {
  //
  // finalize output file with name fOutputFileName
  if ( gDebug ) cout << endl << "GAnalysis::FinalizeOutputFile() called" << endl << endl;

  if ( fOutputFile != 0 ) {

    if ( fOutputFile->IsWritable() ) {
      fHeader->SetEnd();
      fHeaderTree->Fill();
      fOutputFile->Write();
    }
    fOutputFile->Close();
    fOutputFile = 0;
  }

  return kTRUE;
}

//__________________________________________________________________

Bool_t GAnalysis::GenerateHistogrammer() {
  //
  // make GHistogrammer object for histograms
  if ( gDebug ) cout << endl << "GAnalysis::GenerateHistogrammer() called" << endl << endl;

  if ( fHistogramDir != 0 ) {
    new GHistogrammer(fHistogramDir);
    return kTRUE;
  } else {
    cout << endl << "GAnalysis::GenerateHistogrammer() fHistgramDir does not exists" << endl << endl;
    return kFALSE;
  }
}

//__________________________________________________________________

Bool_t GAnalysis::InitInclude() {
  //
  // init include object for helper fucntions
  if ( gDebug ) cout << endl << "GAnalysis::InitInclude() called" << endl << endl;

  new GInclude();
  return kTRUE;
}


//_____________________________________________________________

TString GAnalysis::PrintMessage(TString option) {
  //
  // return print message
  if ( gDebug ) cout << endl << "Analysis::PrintMessage() called" << endl << endl;

  TString dummy = "";

  return dummy;
}

//_____________________________________________________________

Bool_t GAnalysis::Print(TString option) {
  //
  // print message
  if ( gDebug ) cout << endl << "GAnalysis::Print() called" << endl << endl;

  TIter next(fPhysicsObjs);

  while ( GPhysObj *obj = (GPhysObj*)next() ) {
    obj->Print(option);
  }

  return kTRUE;
}


//_____________________________________________________________

TString GAnalysis::GetFileName() {
  //
  // print message
  if ( gDebug ) cout << endl << "GAnalysis::GetFileName() called" << endl << endl;
  return fChain->GetFile()->GetName();

}
