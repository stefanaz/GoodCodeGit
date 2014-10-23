//
// GRuns.cxx
//
// $Author: ibloch $
// $Date: 2005/03/01 20:11:43 $
// $Revision: 1.11 $
//

#include <GRuns.h>

#ifndef GUT_GInclude
#include <GInclude.h>
#endif

#ifndef __CINT__
ClassImp(GRuns)
#endif

GRuns *gRuns = 0;

//_____________________________________________________________
// GRuns
// Runs Class for everything which is related only to run information
//
//
GRuns::GRuns() : GPhysObj() {
  //
  // GRuns default constructor
  if ( gDebug ) cout << endl << "GRuns::GRuns ctor called" << endl << endl;

  // initialize global pointer
  gRuns = this;

  // initialize ok flag
  fOK = kTRUE;

  // initialize clonesarray
  fRuns     = 0;
  fNRuns    = 0;
  fMVDRuns  = 0;
  fNMVDRuns = 0;

  // initialize variables
  fPeriod = kUnidentified;
  
  fCurrentRunNumber        = 0;
  fCurrentRunEvtake  = kFALSE;
  fCurrentMVDRunNumber     = 0;
  fCurrentRunMvdtake = kFALSE;
  
  fLumiAddedToHeader = kFALSE;
  
  fLastAddedLuminosity = 0.0;

}

//_____________________________________________________________

GRuns::~GRuns() {
  //
  // GRuns default destructor
  if ( gDebug ) cout << endl << "GRuns::~GRuns dtor called" << endl << endl;

  if ( fRuns != 0 ) {
    fRuns->Delete();
    fNRuns = 0;
    delete fRuns;
  }

  if ( fMVDRuns != 0 ) {
    fMVDRuns->Delete();
    fNMVDRuns = 0;
    delete fMVDRuns;
  }

}

//_____________________________________________________________

TString GRuns::PrintMessage(TString option) {
  //
  // return print message
  if ( gDebug ) cout << endl << "GRuns::PrintMessage() called" << endl << endl;

  TString dummy = "GRuns:\n\n";

  if ( fCurrentRunNumber != 0 ) {
    dummy.Append(gInclude->FormatedChar("Current Run: ",14));
    dummy.Append(gInclude->FormatedInt(fCurrentRunNumber,6,0," "));
    dummy.Append(gInclude->FormatedChar(" evtake flag: ",14));
    dummy.Append(gInclude->FormatedBool(fCurrentRunEvtake));
    dummy.Append("\n");
  }
  if ( fCurrentMVDRunNumber != 0 ) {
    dummy.Append(gInclude->FormatedChar("Current MVD Run: ",18));
    dummy.Append(gInclude->FormatedInt(fCurrentMVDRunNumber,6,0," "));
    dummy.Append(gInclude->FormatedChar(" mvdtake flag: ",15));
    dummy.Append(gInclude->FormatedBool(fCurrentRunMvdtake));
    dummy.Append("\n");
  }

  dummy.Append("\n");

  return dummy;
}

//_____________________________________________________________

Bool_t GRuns::Print(TString option) {
  //
  // print message
  if ( gDebug ) cout << endl << "GRuns::Print() called" << endl << endl;

  option.ToUpper();

  if ( option.Contains("OUTPUTLIST") ) {
    if ( option.Contains("RUNS") || option.Contains("ALL") ) {
      gLister->FillOutputList(PrintMessage(""));
    }
  } else {
    cout << PrintMessage("")<< endl;
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GRuns::GetAllCuts() {
  //
  // get all cuts
  if ( gDebug ) cout << endl << "GRuns::GetAllCuts called" << endl << endl;

  Bool_t returny = kTRUE;

  if ( !gCards->GetMC() ) {
    if ( gData->Getrunnr() != fCurrentRunNumber )
      fLumiAddedToHeader = kFALSE;

    if ( (gGeneral->GetRunPeriod() == k03p) || (gGeneral->GetRunPeriod() == k04p) || (gGeneral->GetRunPeriod() == k05e) || (gGeneral->GetRunPeriod() == k06e) || (gGeneral->GetRunPeriod() == k06p) || (gGeneral->GetRunPeriod() == k07p)) {
      returny = CheckUpgradeRun();
    } else {
      returny = CheckRun();
    }

    // if mbtake is 0, remove event
    returny = returny && CheckMBTake();
    
    // if fmutake is 0, remove forward muons for pre--upgrade
    // for post--upgrade, remove event
    if ( (gGeneral->GetRunPeriod() == k03p) || (gGeneral->GetRunPeriod() == k04p) || (gGeneral->GetRunPeriod() == k05e) || (gGeneral->GetRunPeriod() == k06e) || (gGeneral->GetRunPeriod() == k06p) || (gGeneral->GetRunPeriod() == k07p)) {
      returny = returny && CheckFMUTake();
    }
    returny = returny && CheckShiftedVertexRuns();

    if ( !fLumiAddedToHeader ) {
      if ( returny ) {
	gHeader->IncreaseLuminosity(fLastAddedLuminosity);
	fLumiAddedToHeader = kTRUE;
      }
    }

  }

  return returny;
}

//_____________________________________________________________

Bool_t GRuns::CheckUpgradeRun() {
  //
  // check take event of upgrade periods
  if ( gDebug ) cout << endl << "GRuns::CheckUpgradeRun called" << endl << endl;

  Bool_t returny = kTRUE;

  if ( gCards->GetEvtake() ) {
    returny = CheckEvtake();
  }

  if ( gCards->GetMvdtake() ) {
    returny = CheckMvdtake();
  }

  return returny;
}

//_____________________________________________________________

Bool_t GRuns::CheckRun() {
  //
  // check take event of pre-upgrade periods
  if ( gDebug ) cout << endl << "GRuns::CheckRun called" << endl << endl;

  Bool_t returny = kTRUE;

  if ( gCards->GetEvtake() ) {
    returny = CheckEvtake();
  }

  return returny;
}

//_____________________________________________________________

Bool_t GRuns::CheckEvtake() {
  //
  // check evtake
  if ( gDebug ) cout << endl << "GRuns::CheckEvtake called" << endl << endl;

  Bool_t returny = kTRUE;


  // initialize arrays if not done or if runperiod changed
  EZRunPeriod period = gGeneral->GetRunPeriod();
  if ( fPeriod != period ) {
    InitEvtakeList(period);
    fPeriod = period;
  }

  Int_t runnr = gData->Getrunnr();

  if ( runnr == fCurrentRunNumber ) {
    returny = fCurrentRunEvtake;
  } else {
    returny = CheckEvtakeList(runnr);
    fCurrentRunNumber = runnr;
    fCurrentRunEvtake = returny;
  }

  return returny;
}

//_____________________________________________________________

Bool_t GRuns::CheckMvdtake() {
  //
  // check mvdtake
  if ( gDebug ) cout << endl << "GRuns::CheckMvdtake called" << endl << endl;

  Bool_t returny = kTRUE;

  // initialize arrays if not done or if runperiod changed
  EZRunPeriod period = gGeneral->GetRunPeriod();
  if ( fMVDPeriod != period ) {
    InitMvdtakeList(period);
    fMVDPeriod = period;
  }

  Int_t runnr = gData->Getrunnr();

  if ( runnr == fCurrentMVDRunNumber ) {
    returny = fCurrentRunMvdtake;
  } else {
    returny = CheckMvdtakeList(runnr);
    fCurrentMVDRunNumber = runnr;
    fCurrentRunMvdtake = returny;
  }

  return returny;
}

//_____________________________________________________________

Bool_t GRuns::InitEvtakeList(EZRunPeriod period) {
  //
  // initialize evtake list
  if ( gDebug ) cout << endl << "GRuns::InitEvtakeList called" << endl << endl;

  Bool_t returny = kTRUE;

  // init evtake array
  if ( fRuns == 0 ) {
    fRuns = new TClonesArray("GRun",1050);
    fNRuns = 0;
  } else {
    fRuns->Clear();
    fNRuns = 0;
  }

  // get lumi lists from web
  TString local = gSystem->Getenv("VALIDRUNSDIR");
  local.Append("/");
  TString command = "wget -q http://www-zeus.desy.de/physics/lumi/lumi";
  TString filename = "validruns_";
  if ( period == k96p ) {
    local.Append("96");
    command.Append("96");
    filename.Append("96p.html");
  } else if ( period == k97p ) {
    local.Append("97");
    command.Append("97");
    filename.Append("97p.html");
  } else if ( period == k98e ) {
    local.Append("98");
    command.Append("98");
    filename.Append("98e.html");
  } else if ( period == k99e ) {
    local.Append("99e");
    command.Append("99e");
    filename.Append("99e.html");
  } else if ( period == k99p ) {
    command.Append("99");
    local.Append("99");
    filename.Append("99p.html");
  } else if ( period == k00p ) {
    local.Append("00");
    command.Append("00");
    filename.Append("00p.html");
  } else if ( period == k02p ) {
    local.Append("0203");
    command.Append("0203");
    filename.Append("02p-03p.html");
  } else if ( period == k03p ) {
    local.Append("03");
    command.Append("03");
    filename.Append("03p.html");
  } else if ( period == k04p ) {
    local.Append("04");
    command.Append("04");
    filename.Append("04p.html");
  } else if ( period == k05e ) {
    local.Append("05");
    command.Append("05");
    filename.Append("05e.html");
  } else if ( period == k06e ) {
    local.Append("06e");
    command.Append("06e");
    filename.Append("06e.html");
  } else if ( period == k06p ) {
    local.Append("06p");
    command.Append("06p");
    filename.Append("06p.html");
  } else if ( period == k07p ) {
    local.Append("07");
    command.Append("07");
    filename.Append("07p.html");
  }  


  command.Append("/validruns.html");
  TString localfile = gSystem->Which(local.Data(),"validruns.html");

//   if ( localfile.Length() > 0 ) {
//     TString loccom = "cp -f ";
//     loccom.Append(localfile);
//     loccom.Append(" ");
//     loccom.Append(filename);
//     gSystem->Exec(loccom.Data());
//   } else {
    gSystem->Exec(command.Data());

    // rename downloaded file
    command = "mv validruns.html ";
    command.Append(filename);
    gSystem->Exec(command.Data());
//   }


  // parse lists
  if ( (period == k96p) ) {
    ifstream stream(filename.Data());
    TString line = "";
    Bool_t start = kFALSE;
    while (line.ReadLine(stream)) {
      if ( !line.BeginsWith("<") ) {
	if ( start ) {
	  istrstream input(line.Data());
	  TString dummy = "";
	  Int_t run          = 0;
	  Int_t events       = 0;
	  Double_t lumi_cal  = 0.0;
	  Double_t lumi_spec = 0.0;
	  input >> dummy;
	  input >> run;
	  input >> lumi_cal;
	  TClonesArray &runs = *fRuns;
	  new(runs[fNRuns++]) GRun(run,events,lumi_cal,lumi_spec);
	}
	if ( line.Contains("nbarn") ) {
	  start = kTRUE;
	}
      }
    }
  } else if ( (period == k97p) ||
	      (period == k98e) ||
	      (period == k99e) ||
	      (period == k99p) ||
	      (period == k00p) ) {
    ifstream stream(filename.Data());
    TString line = "";
    Bool_t start = kFALSE;
    while (line.ReadLine(stream)) {
      if ( !line.BeginsWith("<") ) {
	if ( start ) {
	  istrstream input(line.Data());
	  TString dummy = "";
	  Int_t run          = 0;
	  Int_t events       = 0;
	  Double_t lumi_cal  = 0.0;
	  Double_t lumi_spec = 0.0;
	  input >> dummy;
	  input >> run;
	  input >> lumi_cal;
	  input >> events;
	  TClonesArray &runs = *fRuns;
	  new(runs[fNRuns++]) GRun(run,events,lumi_cal,lumi_spec);
	}
	if ( line.Contains("nbarn") && line.Contains("evt") && line.Contains("range") ) {
	  start = kTRUE;
	}
      }
    }
  } else if ( (period == k03p) ||
	      (period == k04p) ||
	      (period == k05e) ||
	      (period == k06e) ||
              (period == k06p) ||
              (period == k07p) ){
    ifstream stream(filename.Data());
    TString line = "";
    Bool_t start = kFALSE;
    while (line.ReadLine(stream)) {
      if ( !line.BeginsWith("<") ) {
	if ( start ) {
	  istrstream input(line.Data());
	  TString dummy = "";
	  Int_t run          = 0;
	  Int_t events       = 0;
	  Double_t lumi_cal  = 0.0;
	  Double_t lumi_spec = 0.0;
	  TString type = "";
	  EZRunType runtype = kNormal;
	  input >> dummy;
	  input >> run;
	  input >> events;
	  input >> lumi_cal;
	  input >> lumi_spec;
	  input >> dummy;
	  input >> type;
	  type.ToUpper();
	  if ( type.Contains("LOW") )
	    runtype = kLow;
	  else if ( type.Contains("HIGH") )
	    runtype = kHigh;
	  else if ( type.Contains("LTRKV") )
	    runtype = kLTRKV;
	  else if ( type.Contains("NOTTV") )
	    runtype = kNOTTV;
	  TClonesArray &runs = *fRuns;
	  new(runs[fNRuns++]) GRun(run,events,lumi_cal,lumi_spec,runtype);
	}
	if ( line.Contains("run") && line.Contains("events") && line.Contains("CAL") ) {
	  start = kTRUE;
	}
      }
    }
  }

//   GRun *run = 0;

//   ofstream output("runs.txt");
  

//   for ( Int_t i = 0; i < fNRuns; ++i ) {
//     run = (GRun*)fRuns->At(i);
//     TString line = "";
//     line += run->GetRun();
//     line.Append("\n");
//     output << line;
//     cout << line;
//     output << run->PrintMessage("");
//     cout << run->PrintMessage("");
//   }

  return returny;
}

//_____________________________________________________________

Bool_t GRuns::InitMvdtakeList(EZRunPeriod period) {
  //
  // initialize mvdtake list
  if ( gDebug ) cout << endl << "GRuns::InitMvdtakeList called" << endl << endl;

  Bool_t returny = kTRUE;

  // init evtake array
  if ( fMVDRuns == 0 ) {
    fMVDRuns = new TClonesArray("GRun",1050);
    fNMVDRuns = 0;
  } else {
    fMVDRuns->Clear();
    fNMVDRuns = 0;
  }

  // get lumi lists from web
  TString command = "wget -q http://www-zeus.desy.de/physics/lumi/lumi";
  TString filename = "mvd_validruns_";
  if ( period == k03p ) {
    command.Append("03");
    filename.Append("03p.html");
  } else if ( period == k04p ) {
    command.Append("04");
    filename.Append("04p.html");
  } else if ( period == k05e ) {
    command.Append("05");
    filename.Append("05e.html");
  } else if ( period == k06e ) {
    command.Append("06e");
    filename.Append("06e.html");
  } else if ( period == k06p ) {
    command.Append("06p");
    filename.Append("06p.html");
  } else if ( period == k07p ) {
    command.Append("07");
    filename.Append("07p.html");
  }  
  command.Append("/mvd_validruns.html");
  gSystem->Exec(command.Data());

  // rename downloaded file
  command = "mv mvd_validruns.html ";
  command.Append(filename);
  gSystem->Exec(command.Data());

  // parse lists
  if ( (period == k03p) ||
       (period == k04p) ||
       (period == k05e) ||
       (period == k06e) ||
       (period == k06p) ||
       (period == k07p) ) {
    ifstream stream(filename.Data());
    TString line = "";
    Bool_t start = kFALSE;
    while (line.ReadLine(stream)) {
      if ( !line.BeginsWith("<") ) {
	if ( start ) {
	  istrstream input(line.Data());
	  TString dummy = "";
	  Int_t run          = 0;
	  Int_t events       = 0;
	  Double_t lumi_cal  = 0.0;
	  Double_t lumi_spec = 0.0;
	  TString type = "";
	  EZRunType runtype = kNormal;
	  input >> dummy;
	  input >> run;
	  input >> events;
	  input >> lumi_cal;
	  input >> lumi_spec;
	  input >> type;
	  type.ToUpper();
	  if ( type.Contains("LOW") || type.Contains("LTRKVT"))
	    runtype = kLow;
	  else if ( type.Contains("HIGH") )
	    runtype = kHigh;
	  else if ( type.Contains("LTRKV") )
	    runtype = kLTRKV;
	  else if ( type.Contains("NOTTV") )
	    runtype = kNOTTV;
	  TClonesArray &runs = *fMVDRuns;
	  new(runs[fNMVDRuns++]) GRun(run,events,lumi_cal,lumi_spec,runtype);
	}
	if ( line.Contains("run") && line.Contains("events") && line.Contains("CAL") ) {
	  start = kTRUE;
	}
      }
    }
  }

//   GRun *run = 0;

//   ofstream output("mvdruns.txt");
  

//   for ( Int_t i = 0; i < fNMVDRuns; ++i ) {
//     run = (GRun*)fMVDRuns->At(i);
//     TString line = "";
//     line += run->GetRun();
//     line.Append("\n");
//     output << line;
//     cout << line;
//     output << run->PrintMessage("");
//     cout << run->PrintMessage("");
//   }

  return returny;
}

//_____________________________________________________________

Bool_t GRuns::CheckEvtakeList(Int_t runnr) {
  //
  // check evtake list for runnr
  if ( gDebug ) cout << endl << "GRuns::CheckEvtakeList called" << endl << endl;

  Bool_t returny = kFALSE;

  GRun *run = 0;
  for ( Int_t i = 0; i < fNRuns; i++ ) {
    run = ((GRun*)(fRuns->At(i)));
    if ( run->GetRun() == runnr  ) {
      // pre-upgrade
      if ( runnr < 40000 ) {
	Double_t lumi = run->GetLumi_Cal();
	if ( lumi == 0.0 ) 
	  lumi = run->GetLumi_Spec();
// 	gHeader->IncreaseLuminosity(lumi/1000);
	fLastAddedLuminosity = lumi/1000;
      } else {
	if ( !gCards->GetMvdtake() ) {
	Double_t lumi = run->GetLumi_Cal();
	if ( lumi == 0.0 ) 
	  lumi = run->GetLumi_Spec();
// 	  gHeader->IncreaseLuminosity(lumi/1000);
	  fLastAddedLuminosity = lumi/1000;
	}
      }
      returny = kTRUE;
      return returny;
    }
  }

  return returny;
}

//_____________________________________________________________

Bool_t GRuns::CheckMvdtakeList(Int_t runnr) {
  //
  // check mvdtake list for runnr
  if ( gDebug ) cout << endl << "GRuns::CheckMvdtakeList called" << endl << endl;

  Bool_t returny = kFALSE;

  GRun *run = 0;
  for ( Int_t i = 0; i < fNMVDRuns; i++ ) {
    run = ((GRun*)(fMVDRuns->At(i)));
    if ( run->GetRun() == runnr  ) {
      Double_t lumi = run->GetLumi_Cal();
      if ( lumi == 0.0 ) 
	lumi = run->GetLumi_Spec();
//       gHeader->IncreaseLuminosity(lumi/1000);
      fLastAddedLuminosity = lumi/1000;
      returny = kTRUE;
      return returny;
    }
  }

  return returny;
}

//_____________________________________________________________

GRun* GRuns::GetRun(Int_t runnr) {
  //
  // get run with runnumber, if mvdtake is selected, look in mvdtake runlist
  // else look in evtake runlist
  if ( gDebug ) cout << endl << "GRuns::GetRun called" << endl << endl;

  GRun *run = 0;
  if ( gCards->GetMvdtake() ) {
    for ( Int_t i = 0; i < fNMVDRuns; i++ ) {
      run = ((GRun*)(fMVDRuns->At(i)));
      if ( run->GetRun() == runnr ) {
	return run;
      }
    }
  } else {
    for ( Int_t i = 0; i < fNRuns; i++ ) {
      run = ((GRun*)(fRuns->At(i)));
      if ( run->GetRun() == runnr ) {
	return run;
      }
    }
  }

  return run;
}

//_____________________________________________________________

Bool_t GRuns::CheckMBTake() {
  //
  // check mbtake list
  if ( gDebug ) cout << endl << "GRuns::CheckMBTake called" << endl << endl;

  Bool_t returny = kTRUE;

  if ( gCards->GetMBTake() > 0 ) {
    Int_t mbtake = MBTAKE(gData->Getrunnr());
    if ( mbtake < 0 ) {
      TString msg = "GRuns::CheckMBTake problem for run: ";
      msg += gData->Getrunnr();
      msg.Append(" returning: ");
      msg += mbtake;
      gLister->FillErrorList(msg);
    }
    if ( gCards->GetMBTake() == 1 ) {
      if ( mbtake == 1 ) {
	returny = kTRUE;
      } else {
	returny = kFALSE;
      }
    } else if ( gCards->GetMBTake() == 2 ) {
      if ( (mbtake == 1) || (mbtake == 2) ) {
	returny = kTRUE;
      } else {
	returny = kFALSE;
      }
    }
  }

  return returny;
}

//_____________________________________________________________

Bool_t GRuns::CheckFMUTake() {
  //
  // check fmutake list
  if ( gDebug ) cout << endl << "GRuns::CheckFMUTake called" << endl << endl;

  Bool_t returny = kTRUE;

  if ( !gCards->GetMC() ) {
    if ( gCards->GetFMUTake() > 0 ) {
      Int_t fmutake = FMUTAKE(gData->Getrunnr());
      if ( fmutake < 0 ) {
	TString msg = "GRuns::CheckFMUTake problem for run: ";
	msg += gData->Getrunnr();
	msg.Append(" returning: ");
	msg += fmutake;
	gLister->FillErrorList(msg);
      }
      if ( gCards->GetFMUTake() == 1 ) {
	if ( fmutake == 1 ) {
	  returny = kTRUE;
	} else {
	  returny = kFALSE;
	}
      } else if ( gCards->GetFMUTake() == 2 ) {
	if ( (fmutake == 1) || (fmutake == 2) ) {
	  returny = kTRUE;
	} else {
	  returny = kFALSE;
	}
      }
    }
  }

  return returny;
}

//_____________________________________________________________

Bool_t GRuns::CheckShiftedVertexRuns() {
  //
  // check shifted vertex runs list
  if ( gDebug ) cout << endl << "GRuns::CheckShiftedVertexRuns called" << endl << endl;

  Bool_t returny = kTRUE;

  if ( gCards->GetExcludeShiftedVertexRuns() ) {
    Int_t run = gData->Getrunnr();
    if ( (run>=10157) && (run<=10159) ) {
      returny = kFALSE;
    } else if ( (run>=37588) && (run<=37639) ) {
      returny = kFALSE;
    } 
  }

  return returny;
}

//_____________________________________________________________

Int_t GRuns::MBTAKE(Int_t run) {
  //
  //      Flag good/bad BRMUON runs
  //
  //      -1:  undefined/unknown
  //       0:  bad run, do not use
  //           (e.g. chambers or trigger completely off or major problem)
  //       1:  fully Ok, use!
  //       2:  some part of detector with problems 
  //           (e.g. one or two chambers off)
  //           use only with special care for effiency correction 
  if ( gDebug ) cout << endl << "GRuns::MBTAKE called" << endl << endl;


  //  set undefined 
  Int_t mbtake = -1;
  
  //  defined for 95-05 and MC
  if (run < 10) mbtake = 1;
  if ((run > 10000) && (run < 99999)) mbtake = 1;

  //  then exclude/flag bad runs


  //=== 1995 data =====================================
  //still need to check reasons -> change to 2 for some

  if ( run == 12514 ) mbtake = 0;
  //    shifted vertex runs
  if ( (run >= 14075)  &&  (run <= 14146) ) mbtake = 0;
  if ( (run >= 14166)  &&  (run <= 14208) ) mbtake = 0;

  //=== 1996 data =====================================
  //still need to check reasons -> change to 2 for some

  if ( (run >= 20870)  &&  (run <= 21202) ) mbtake = 0;
  if ( (run >= 21634)  &&  (run <= 21637) ) mbtake = 0;
  if ( (run >= 21639)  &&  (run <= 21642) ) mbtake = 0;
  if ( (run >= 21646)  &&  (run <= 21648) ) mbtake = 0;

  //=== 1997 data =====================================
  //still need to check reasons -> change to 2 for some

  if ( run == 25202 ) mbtake = 0;
  if ( run == 25204 ) mbtake = 0;
  if ( run == 25290 ) mbtake = 0;
  if ( run == 25414 ) mbtake = 0;
  if ( run == 25463 ) mbtake = 0;
  if ( run == 25884 ) mbtake = 0;
  if ( (run >= 26064)  &&  (run <= 26065) ) mbtake = 0;
  if ( (run >= 26227)  &&  (run <= 26229) ) mbtake = 0;
  if ( run == 26394 ) mbtake = 0;
  if ( (run >= 26396)  &&  (run <= 26399) ) mbtake = 0;
  if ( run == 26550 ) mbtake = 0;
  if ( (run >= 26601)  &&  (run <= 26605) ) mbtake = 0;
  if ( run == 26672 ) mbtake = 0;
  if ( run == 26830 ) mbtake = 0;
  if ( run == 26841 ) mbtake = 0;
  if ( run == 26949 ) mbtake = 0;
  if ( run == 26981 ) mbtake = 0;
  if ( (run >= 27059)  &&  (run <= 27060) ) mbtake = 0;
  if ( (run >= 27110)  &&  (run <= 27112) ) mbtake = 0;
  if ( run == 27208 ) mbtake = 0;
  if ( (run >= 27241)  &&  (run <= 27242) ) mbtake = 0;
  if ( run == 27396 ) mbtake = 0;
  if ( run == 27551 ) mbtake = 0;
  if ( run == 27602 ) mbtake = 0;
  if ( run == 27686 ) mbtake = 0;
  if ( run == 27722 ) mbtake = 0;
  if ( run == 27739 ) mbtake = 0;

  //=== 1998 data =====================================
  
  //    BMUON excluded
  if ((run >= 30875) && (run <= 30880)) mbtake=0;
  //    HV problems
  if (run == 31110) mbtake=0;
  //    Chamber 11 has no data
  if (run == 31316) mbtake=2;
  //    GLOMU rate too low
  if (run == 31522) mbtake=0;
  //     Problems on CH42
  if ((run > 31540) && (run < 31641)) mbtake=2;

  //=== 1999 electron data ============================
  
  //    HV problems, chambers 21 and 31
  if ((run == 31866) || (run == 31867)) mbtake=2;
  //    BMUON excluded
  if (run == 31869) mbtake=0;
  //    HV off for chambers 21 and 31
  if ((run == 32189) || (run == 32191)) mbtake=2;
  //    GLOMU rate too low
  if (run == 32726) mbtake=0;

  //=== 1999 positron data ============================

  //    GLOMU rate too low
  if ((run == 33162) || (run == 33427)) mbtake=0;
  //    Problems on DSP24
  if (run == 33474) mbtake=2;
  //    HV off
  if ((run >= 33709) && (run <= 33711)) mbtake=0;
  //    No yoke and compensators
  if (run == 33853) mbtake=0;
  //    Problems with CH95? (to verify!!!!)
  if ((run >= 33885) && (run <= 33945)) mbtake=2;

  //=== 2000 data =====================================

  //    CH61-72-96 missing
  if (run == 35075) mbtake=2;
  //    CH96 missing
  if ((run >= 35077) && (run <= 35083)) mbtake=2;
  //    CH98, no hits in planes 1 and 2
  if (run == 35091) mbtake=2;
  //    GLOMU rate too low
  if ((run == 35161) || (run == 36079)) mbtake=0;
  //    Plane 3, CH62 empty
  if (run == 36636) mbtake=2;
  //    Problems on planes 3 and 4, CH11
  if (run == 36797) mbtake=2;
  //    GLOMU rate too low
  if (run == 37158) mbtake=0;
  //    No entries on plane 3, CH12
  if ((run == 37164) || (run == 37165)) mbtake=2;
  //    GLOMU rate too low
  if (run == 37235) mbtake=0;
  //    Problems after a power glitch
  if ((run >= 37260) && (run <= 37266)) mbtake=0;
  //    Planes 1 and 2, CH11 empty
  if (run == 37298) mbtake=2;
  //    1/2 BMUON with HV off
  if (run == 37376) mbtake=0;
  //    Slot 14 and 15* still need to check reasons prescaled to 0
  if ((run >= 36344) && (run <= 36347)) mbtake=2;
  if ((run >= 37587) && (run <= 37639)) mbtake=2;
  //    Problems on crate R19/DSP24 (TDC CH11)
  if ((run == 35031) || (run == 35043) || ((run >= 37269) && (run <= 37320)) || ((run >= 37344) && (run <= 37367))) mbtake=2;

  return mbtake;
}

//_____________________________________________________________

Int_t GRuns::FMUTAKE(Int_t run) {
  // 
  // Input:   run number
  // Output:  1=accept, 2=do not use fmu trigger, 0 reject, -1=undef
  //
  if ( gDebug ) cout << endl << "GRuns::FMUTAKE called" << endl << endl;

  Int_t fmutake = -1;
  
  if (run < 20000) {
    //  no fmutake for 92-95, exclude!
    fmutake = 0;
  } else if (run < 25000) {
    fmutake = FMUTAKE96(run);
  } else if (run <= 30000) {
    fmutake = FMUTAKE97(run);
  } else if (run <= 31752) {
    // problems for most of 98, include (?)
    fmutake = 0;
  } else if (run < 35000) {
    fmutake = FMUTAKE99(run);
  } else if (run < 40000) {
    fmutake = FMUTAKE00(run);
  } else if (run < 47000) {
    //  no fmutake in 2001-03, include
    fmutake = 1;
  } else if (run < 52000) {
    fmutake = FMUTAKE04(run);
  } else {
    // otherwise, include
    fmutake = 1;
  }

  return fmutake;
}  

//_____________________________________________________________

Int_t GRuns::FMUTAKE96(Int_t run) {
  // 
  // Input:   run number
  // Output:  1=accept, 2=do not use fmu trigger, 0 reject, -1=undef
  //
  if ( gDebug ) cout << endl << "GRuns::FMUTAKE96 called" << endl << endl;

  Int_t fmutake = 1;

  //  HV LT high from 20821
  //  HV DC high from 20881
  if ( (run >= 20449) && (run <= 20881) ) fmutake = 0;         
  //  TDC 3 crate 8 without clock
  if ( (run >= 20930) && (run <= 20935) ) fmutake = 0;
  //  TDC 3 crate 8 test 
  if ( (run >= 20970) && (run <= 20970) ) fmutake = 0;
  //  FMUON offline 
  if ( (run >= 20597) && (run <= 20602) ) fmutake = 0;
  if ( (run >= 20820) && (run <= 20820) ) fmutake = 0;
  if ( (run >= 21106) && (run <= 21106) ) fmutake = 0;
  if ( (run >= 21118) && (run <= 21118) ) fmutake = 0;
  //  FMUON offline 
  if ( (run >= 21167) && (run <= 21168) ) fmutake = 0;
  if ( (run >= 21186) && (run <= 21193) ) fmutake = 0;
  //  events are not useful, after a power glitch 
  if ( (run >= 21246) && (run <= 21297) ) fmutake = 0;
  //  LT LW oct 7 not useful, wrong clock in PPLU 7 
  if ( (run >= 21259) && (run <= 21496) ) fmutake = 0;
  //  FMUON offline 
  if ( (run >= 21286) && (run <= 21290) ) fmutake = 0;
  //  LT plane 1 without signals
  if ( (run >= 21904) && (run <= 21905) ) fmutake = 0;
  //  FMUON offline 
  if ( (run >= 21906) && (run <= 21906) ) fmutake = 0;
  if ( (run >= 22027) && (run <= 22027) ) fmutake = 0;
  //  TDC crate 3 (DC plane 3 oct 1,2,3,4) OFF
  if ( (run >= 22169) && (run <= 22169) ) fmutake = 0;
  //  HV LT,LW,DC OFF 
  if ( (run >= 22234) && (run <= 22234) ) fmutake = 0;
  //  TDC crate 3 (DC plane 3 oct 1,2,3,4) OFF
  if ( (run >= 22276) && (run <= 22278) ) fmutake = 0;
  //  FMUON offline 
  if ( (run >= 22516) && (run <= 22516) ) fmutake = 0;
  if ( (run >= 22548) && (run <= 22548) ) fmutake = 0;
  if ( (run >= 22571) && (run <= 22584) ) fmutake = 0;
  //  TDC all data missing
  if ( (run >= 22591) && (run <= 22599) ) fmutake = 0;
  if ( (run >= 22640) && (run <= 22648) ) fmutake = 0;
  if ( (run >= 22658) && (run <= 22662) ) fmutake = 0;
  //  FMUON offline 
  if ( (run >= 22681) && (run <= 22681) ) fmutake = 0;
  if ( (run >= 22753) && (run <= 22753) ) fmutake = 0;
  //  TDC crate 6 (DC plane 2 oct 5,6,7,8) OFF
  if ( (run >= 22767) && (run <= 22767) ) fmutake = 0;
  //  FMUON offline 
  if ( (run >= 22800) && (run <= 22800) ) fmutake = 0;
  //  test on DC plane 2 oct 3,4
  if ( (run >= 22887) && (run <= 22932) ) fmutake = 0;

  return fmutake;
}

//_____________________________________________________________

Int_t GRuns::FMUTAKE97(Int_t run) {
  // 
  // Input:   run number
  // Output:  1=accept, 2=do not use fmu trigger, 0 reject, -1=undef
  //
  if ( gDebug ) cout << endl << "GRuns::FMUTAKE97 called" << endl << endl;
  
  Int_t fmutake = 1;

  if ( (run == 25388) || 
       (run == 25685) || 
       (run == 25686) || 
       (run == 25693) || 
       (run == 25694) || 
       (run == 25695) || 
       (run == 25923) || 
       (run == 25925) || 
       (run == 25939) || 
       (run == 25947) || 
       (run == 25948) || 
       (run == 26027) || 
       (run == 26034) || 
       (run == 26036) || 
       (run == 26043) || 
       (run == 26112) || 
       (run == 26113) || 
       (run == 26114) || 
       (run == 26115) || 
       (run == 26383) || 
       (run == 26666) || 
       (run == 26667) || 
       (run == 26671) || 
       (run == 26672) || 
       (run == 26673) || 
       (run == 26674) || 
       (run == 26675) || 
       (run == 26679) || 
       (run == 26680) || 
       (run == 26681) || 
       (run == 26682) || 
       (run == 26683) || 
       (run == 26684) || 
       (run == 26685) || 
       (run == 26690) || 
       (run == 26691) || 
       (run == 26695) || 
       (run == 26701) || 
       (run == 26702) || 
       (run == 26705) || 
       (run == 26707) || 
       (run == 26709) || 
       (run == 26711) || 
       (run == 26712) || 
       (run == 26720) || 
       (run == 26722) || 
       (run == 26907) || 
       (run == 26924) || 
       (run == 26925) || 
       (run == 26949) || 
       (run == 26993) || 
       (run == 26994) || 
       (run == 26995) || 
       (run == 26996) || 
       (run == 27028) || 
       (run == 27395) || 
       (run == 27396) || 
       (run == 27412) || 
       (run == 27413) || 
       (run == 27429) || 
       (run == 27450) || 
       (run == 27743) || 
       (run == 27761) || 
       (run == 27762) || 
       (run == 27763) || 
       (run == 26380) || 
       (run == 27265) || 
       (run == 27266) || 
       (run == 27267) || 
       (run == 27268) ) {
    fmutake = 0;
  }

  if ( (run == 25516) || 
       (run == 25718) || 
       (run == 25719) || 
       (run == 25721) || 
       (run == 25722) || 
       (run == 25723) || 
       (run == 25724) || 
       (run == 25725) || 
       (run == 25730) || 
       (run == 25731) || 
       (run == 27329) || 
       (run == 27402) || 
       (run == 27590) || 
       (run == 27621) || 
       (run == 27678) ) {
    fmutake = 2;
  }
  
  return fmutake;
}

//_____________________________________________________________

Int_t GRuns::FMUTAKE99(Int_t run) {
  // 
  // Input:   run number
  // Output:  1=accept, 2=do not use fmu trigger, 0 reject, -1=undef
  //
  if ( gDebug ) cout << endl << "GRuns::FMUTAKE99 called" << endl << endl;
  
  Int_t fmutake = 1;

  if ( (run == 33473) || 
       (run == 33474) || 
       (run == 33482) || 
       (run == 33940) || 
       (run == 33944) || 
       (run == 33945) || 
       (run == 34158) || 
       (run == 34395) ) {
    fmutake = 0;
  }

  return fmutake;
}

//_____________________________________________________________

Int_t GRuns::FMUTAKE00(Int_t run) {
  // 
  // Input:   run number
  // Output:  1=accept, 2=do not use fmu trigger, 0 reject, -1=undef
  //
  if ( gDebug ) cout << endl << "GRuns::FMUTAKE00 called" << endl << endl;
  
  Int_t fmutake = 1;

  if ( (run == 35850) || 
       (run == 35898) || 
       (run == 35902) || 
       (run == 36152) || 
       (run == 36153) || 
       (run == 36154) || 
       (run == 36344) || 
       (run == 36345) || 
       (run == 36346) || 
       (run == 36347) || 
       (run == 36437) || 
       (run == 36438) || 
       (run == 36439) || 
       (run == 36440) || 
       (run == 36441) || 
       (run == 36442) || 
       (run == 36443) || 
       (run == 36444) || 
       (run == 36445) || 
       (run == 36447) || 
       (run == 36448) || 
       (run == 36449) || 
       (run == 36450) || 
       (run == 36592) || 
       (run == 36593) || 
       (run == 36594) || 
       (run == 36595) || 
       (run == 36604) || 
       (run == 36605) || 
       (run == 36610) || 
       (run == 36611) || 
       (run == 36612) || 
       (run == 36614) || 
       (run == 36615) || 
       (run == 36622) || 
       (run == 36623) || 
       (run == 36624) || 
       (run == 36633) || 
       (run == 36634) || 
       (run == 36635) || 
       (run == 36636) || 
       (run == 36637) || 
       (run == 36639) || 
       (run == 36650) || 
       (run == 36651) || 
       (run == 36652) || 
       (run == 36654) || 
       (run == 36666) || 
       (run == 36667) || 
       (run == 36668) || 
       (run == 36671) || 
       (run == 36672) || 
       (run == 36673) || 
       (run == 36674) || 
       (run == 36678) || 
       (run == 36679) || 
       (run == 36680) || 
       (run == 36681) || 
       (run == 36682) || 
       (run == 36687) || 
       (run == 36688) || 
       (run == 36689) || 
       (run == 36690) || 
       (run == 36701) || 
       (run == 36702) || 
       (run == 36703) || 
       (run == 36704) || 
       (run == 36705) || 
       (run == 36706) || 
       (run == 36707) || 
       (run == 36708) || 
       (run == 36709) || 
       (run == 36710) || 
       (run == 36716) || 
       (run == 36717) || 
       (run == 36718) || 
       (run == 36719) || 
       (run == 36720) || 
       (run == 36721) || 
       (run == 36723) || 
       (run == 36724) || 
       (run == 36730) || 
       (run == 36737) || 
       (run == 36738) || 
       (run == 36739) || 
       (run == 36740) || 
       (run == 36741) || 
       (run == 36743) || 
       (run == 36744) || 
       (run == 36749) || 
       (run == 36750) || 
       (run == 36752) || 
       (run == 36754) || 
       (run == 36758) || 
       (run == 36759) || 
       (run == 36760) || 
       (run == 36771) || 
       (run == 36773) || 
       (run == 36779) || 
       (run == 36781) || 
       (run == 36786) || 
       (run == 36787) || 
       (run == 36788) || 
       (run == 36789) || 
       (run == 36790) || 
       (run == 36795) || 
       (run == 36797) || 
       (run == 36798) || 
       (run == 36804) || 
       (run == 36806) || 
       (run == 36807) || 
       (run == 36808) || 
       (run == 36814) || 
       (run == 36817) || 
       (run == 36818) || 
       (run == 36819) || 
       (run == 36820) || 
       (run == 36821) || 
       (run == 36825) || 
       (run == 36826) || 
       (run == 36834) || 
       (run == 36835) || 
       (run == 36836) || 
       (run == 36837) || 
       (run == 36838) || 
       (run == 36842) || 
       (run == 36843) || 
       (run == 36844) || 
       (run == 36848) || 
       (run == 36849) || 
       (run == 36851) || 
       (run == 36861) ) {
    fmutake = 0;
  }

  return fmutake;
}

//_____________________________________________________________

Int_t GRuns::FMUTAKE04(Int_t run) {
  // 
  // Input:   run number
  // Output:  1=accept, 2=do not use fmu trigger, 0 reject, -1=undef
  //
  if ( gDebug ) cout << endl << "GRuns::FMUTAKE04 called" << endl << endl;
  
  Int_t fmutake = 1;

  if ( ( run == 47010) ||
       ( run == 47014) ||
       ( run == 47015) ||
       ( run == 47019) ||
       ( run == 47020) ||
       ( run == 47021) ||
       ( run == 47022) ||
       ( run == 47023) ||
       ( run == 47033) ||
       ( run == 47034) ||
       ( run == 47040) ||
       ( run == 47097) ||
       ( run == 47098) ||
       ( run == 47101) ||
       ( run == 47363) ||
       ( run == 47380) ||
       ( run == 47381) ||
       ( run == 47382) ||
       ( run == 47383) ||
       ( run == 47385) ||
       ( run == 47386) ||
       ( run == 47390) ||
       ( run == 47627) ||
       ( run == 47654) ||
       ( run == 48212) ||
       ( run == 48213) ||
       ( run == 48561) ||
       ( run == 48565) ||
       ( run == 48566) ||
       ( run == 48567) ||
       ( run == 48568) ||
       ( run == 48569) ||
       ( run == 48570) ||
       ( run == 48571) ||
       ( run == 48803) ||
       ( run == 48804) ||
       ( run == 48805) ||
       ( run == 49171) ||
       ( run == 49174) ||
       ( run == 49175) ||
       ( run == 49176) ||
       ( run == 49976) ||
       ( run == 50020) ||
       ( run == 50026) ||
       ( run == 50028) ||
       ( run == 50029) ||
       ( run == 50030) ||
       ( run == 50031) ||
       ( run == 50032) ||
       ( run == 50033) ||
       ( run == 50034) ||
       ( run == 50035) ||
       ( run == 50036) ||
       ( run == 50037) ||
       ( run == 50038) ||
       ( run == 50039) ||
       ( run == 50040) ||
       ( run == 50172) ||
       ( run == 50204) ||
       ( run == 51186) ||
       ( run == 51187) ||
       ( run == 49163) ||
       ( run == 49170) ||
       ( run == 49172) 
// C ---- excluded run from fmuon shift reports
//         IF(run.eq.49163.or.
//      &     run.eq.49170.or.
//      &     run.eq.49172) THEN
//           iwant=0
//           return
//         ENDIF
       ) {
    fmutake = 0;
  }

  if ( ( run == 49614) ||
       ( run == 49615) ||
       ( run == 49616) ||
       ( run == 49617) ||
       ( run == 49719) ||
       ( run == 50348) ||
       ( run == 50359) ||
       ( run == 50360) ||
       ( run == 50362) ||
       ( run == 50363) ||
       ( run == 50364) ||
       ( run == 50365) ||
       ( run == 50411) ||
       ( run == 51158) ||
       ( run >= 51092 && run <= 51162 )
// C ---  Problems detected in LT oct 7
//         IF ( Run.GE.51092.AND.Run.LE.51162) THEN
//           IWant = 3
//           RETURN
//         ENDIF
       ) {
    fmutake = 2;
  }

  return fmutake;
}

