//
// GGeneral.cxx
//
// $Author: gutsche $
// $Date: 2005/02/18 12:07:42 $
// $Revision: 1.21 $
//

#include <GGeneral.h>

#ifndef GUT_GInclude
#include <GInclude.h>
#endif

#ifndef __CINT__
ClassImp(GGeneral)
#endif
  
        
GGeneral *gGeneral = 0;

//_____________________________________________________________
// GGeneral
// General class for general properties
//
//
GGeneral::GGeneral() : GPhysObj() {
  //
  // GGeneral default constructor
  if ( gDebug ) cout << endl << "GGeneral::GGeneral ctor called" << endl << endl;

  gGeneral = this;

  // init run summary borders, upper border according to run lists, add one for histogram booking
  f96p_low = 20718;
  f96p_up  = 22954;
  f97p_low = 25190;
  f97p_up  = 27889;
  f98e_low = 30758;
  f98e_up  = 31752;
  f99e_low = 31784;
  f99e_up  = 32906;
  f99p_low = 33125;
  f99p_up  = 34486;
  f00p_low = 35031;
  f00p_up  = 37716;
  f02p_low = 42000;
  f02p_up  = 44999;
  f03p_low = 45000;
  f03p_up  = 46999;
  f04p_low = 47000;
  f04p_up  = 51999;
  f05e_low = 52000;
  f05e_up  = 57999;
  f06e_low = 58000;
  f06e_up  = 59999;
  f06p_low = 60000;
  f06p_up  = 61746;
  f07p_low = 61747;
  f07p_up  = 62999;

  fPeriod = kUnidentified;

  f96p_uncut = 0;
  f97p_uncut = 0;
  f98e_uncut = 0;
  f99e_uncut = 0;
  f99p_uncut = 0;
  f00p_uncut = 0;
  f02p_uncut = 0;
  f03p_uncut = 0;
  f04p_uncut = 0;
  f05e_uncut = 0;
  f06e_uncut = 0;
  f06p_uncut = 0;
  f07p_uncut = 0;

  f96p = 0;
  f97p = 0;
  f98e = 0;
  f99e = 0;
  f99p = 0;
  f00p = 0;
  f02p = 0;
  f03p = 0;
  f04p = 0;
  f05e = 0;
  f06e = 0;
  f06p = 0;
  f07p = 0;

  f96p_Taked = 0;
  f97p_Taked = 0;
  f98e_Taked = 0;
  f99e_Taked = 0;
  f99p_Taked = 0;
  f00p_Taked = 0;
  f02p_Taked = 0;
  f03p_Taked = 0;
  f04p_Taked = 0;
  f05e_Taked = 0;
  f06e_Taked = 0;
  f06p_Taked = 0;
  f07p_Taked = 0;


  fWeight_uncut = 0;
  fWeight = 0;

  // create histograms
  fOK = CreateHistograms();

}

//_____________________________________________________________

GGeneral::~GGeneral() {
  //
  // GGeneral default destructor
  if ( gDebug ) cout << endl << "GGeneral::~GGeneral dtor called" << endl << endl;

}

//_____________________________________________________________

Bool_t GGeneral::Do() {
  //
  // execute per event
  if ( gDebug ) cout << endl << "GGeneral::Do() called" << endl << endl;

  CheckRunPeriod();
  CheckProperties();

  return kTRUE;
}

//_____________________________________________________________

Bool_t GGeneral::Reset() {
  //
  // reset event
  if ( gDebug ) cout << endl << "GGeneral::Reset() called" << endl << endl;

  fPeriod = kUnidentified;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GGeneral::CheckRunPeriod() {
  //
  // check for run period
  if ( gDebug ) cout << endl << "GGeneral::Do() called" << endl << endl;
  
  if ( gCards->GetMC() ) {
    if ( gCards->GetMCRunPeriod().Contains("96p-97p") ) {
      fPeriod = k96p97p;
    } else if ( gCards->GetMCRunPeriod().Contains("98e-99e") ) {
      fPeriod = k98e99e;
    } else if ( gCards->GetMCRunPeriod().Contains("99p-00p") ) {
      fPeriod = k99p00p;
    } else if ( gCards->GetMCRunPeriod().Contains("03p-04p") ) {
      fPeriod = k03p04p;
    } else if ((gCards->GetMCRunPeriod().Contains("05e-06e"))||(gCards->GetMCRunPeriod().Contains("05e"))||(gCards->GetMCRunPeriod().Contains("06e")) ) {
      fPeriod = k05e06e;
    } else if ( gCards->GetMCRunPeriod().Contains("06p-07p") ) {
      fPeriod = k06p07p;
    } 
  } else {
    Int_t run = gData->Getrunnr();
    if ( (f96p_low <= run) && (run <= f96p_up) ) {
      fPeriod = k96p;
    } else if ( (f97p_low <= run) && (run <= f97p_up) ) {
      fPeriod = k97p;
    } else if ( (f98e_low <= run) && (run <= f98e_up) ) {
      fPeriod = k98e;
    } else if ( (f99e_low <= run) && (run <= f99e_up) ) {
      fPeriod = k99e;
    } else if ( (f99p_low <= run) && (run <= f99p_up) ) {
      fPeriod = k99p;
    } else if ( (f00p_low <= run) && (run <= f00p_up) ) {
      fPeriod = k00p;
    } else if ( (f02p_low <= run) && (run <= f02p_up) ) {
      fPeriod = k02p;
    } else if ( (f03p_low <= run) && (run <= f03p_up) ) {
      fPeriod = k03p;
    } else if ( (f04p_low <= run) && (run <= f04p_up) ) {
      fPeriod = k04p;
    } else if ( (f05e_low <= run) && (run <= f05e_up) ) {
      fPeriod = k05e;
    } else if ( (f06e_low <= run) && (run <= f06e_up) ) {
      fPeriod = k06e;
    } else if ( (f06p_low <= run) && (run <= f06p_up) ) {
      fPeriod = k06p;
    } else if ( (f07p_low <= run) && (run <= f07p_up) ) {
      fPeriod = k07p;
    } 
  }  

  return kTRUE;
}

//_____________________________________________________________

Bool_t GGeneral::CreateControl() {
  //
  // create general histograms
  if ( gDebug ) cout << endl << "GGeneral::CreateControl() called" << endl << endl;

  if ( gCards->GetGGeneralControl() ) {

    f96p_uncut = gHistogrammer->TH1DFactory("General_Control","96p_uncut","uncut run summary for 96p",(f96p_up-f96p_low+1),f96p_low,(f96p_up+1),"run number","Events");
    f97p_uncut = gHistogrammer->TH1DFactory("General_Control","97p_uncut","uncut run summary for 97p",(f97p_up-f97p_low+1),f97p_low,(f97p_up+1),"run number","Events");
    f98e_uncut = gHistogrammer->TH1DFactory("General_Control","98e_uncut","uncut run summary for 98e",(f98e_up-f98e_low+1),f98e_low,(f98e_up+1),"run number","Events");
    f99e_uncut = gHistogrammer->TH1DFactory("General_Control","99e_uncut","uncut run summary for 99e",(f99e_up-f99e_low+1),f99e_low,(f99e_up+1),"run number","Events");
    f99p_uncut = gHistogrammer->TH1DFactory("General_Control","99p_uncut","uncut run summary for 99p",(f99p_up-f99p_low+1),f99p_low,(f99p_up+1),"run number","Events");
    f00p_uncut = gHistogrammer->TH1DFactory("General_Control","00p_uncut","uncut run summary for 00p",(f00p_up-f00p_low+1),f00p_low,(f00p_up+1),"run number","Events");
    f02p_uncut = gHistogrammer->TH1DFactory("General_Control","02p_uncut","uncut run summary for 02p",(f02p_up-f02p_low+1),f02p_low,(f02p_up+1),"run number","Events");
    f03p_uncut = gHistogrammer->TH1DFactory("General_Control","03p_uncut","uncut run summary for 03p",(f03p_up-f03p_low+1),f03p_low,(f03p_up+1),"run number","Events");
    f04p_uncut = gHistogrammer->TH1DFactory("General_Control","04p_uncut","uncut run summary for 04p",(f04p_up-f04p_low+1),f04p_low,(f04p_up+1),"run number","Events");
    f05e_uncut = gHistogrammer->TH1DFactory("General_Control","05e_uncut","uncut run summary for 05e",(f05e_up-f05e_low+1),f05e_low,(f05e_up+1),"run number","Events");
    f06e_uncut = gHistogrammer->TH1DFactory("General_Control","06e_uncut","uncut run summary for 06e",(f06e_up-f06e_low+1),f06e_low,(f06e_up+1),"run number","Events");
    f06p_uncut = gHistogrammer->TH1DFactory("General_Control","06p_uncut","uncut run summary for 06p",(f06p_up-f06p_low+1),f06p_low,(f06p_up+1),"run number","Events");
    f07p_uncut = gHistogrammer->TH1DFactory("General_Control","07p_uncut","uncut run summary for 07p",(f07p_up-f07p_low+1),f07p_low,(f07p_up+1),"run number","Events");


    f96p = gHistogrammer->TH1DFactory("General_Control","96p","run summary for 96p",(f96p_up-f96p_low+1),f96p_low,(f96p_up+1),"run number","Events");
    f97p = gHistogrammer->TH1DFactory("General_Control","97p","run summary for 97p",(f97p_up-f97p_low+1),f97p_low,(f97p_up+1),"run number","Events");
    f98e = gHistogrammer->TH1DFactory("General_Control","98e","run summary for 98e",(f98e_up-f98e_low+1),f98e_low,(f98e_up+1),"run number","Events");
    f99e = gHistogrammer->TH1DFactory("General_Control","99e","run summary for 99e",(f99e_up-f99e_low+1),f99e_low,(f99e_up+1),"run number","Events");
    f99p = gHistogrammer->TH1DFactory("General_Control","99p","run summary for 99p",(f99p_up-f99p_low+1),f99p_low,(f99p_up+1),"run number","Events");
    f00p = gHistogrammer->TH1DFactory("General_Control","00p","run summary for 00p",(f00p_up-f00p_low+1),f00p_low,(f00p_up+1),"run number","Events");
    f02p = gHistogrammer->TH1DFactory("General_Control","02p","run summary for 02p",(f02p_up-f02p_low+1),f02p_low,(f02p_up+1),"run number","Events");
    f03p = gHistogrammer->TH1DFactory("General_Control","03p","run summary for 03p",(f03p_up-f03p_low+1),f03p_low,(f03p_up+1),"run number","Events");
    f04p = gHistogrammer->TH1DFactory("General_Control","04p","run summary for 04p",(f04p_up-f04p_low+1),f04p_low,(f04p_up+1),"run number","Events");
    f05e = gHistogrammer->TH1DFactory("General_Control","05e","run summary for 05e",(f05e_up-f05e_low+1),f05e_low,(f05e_up+1),"run number","Events");
    f06e = gHistogrammer->TH1DFactory("General_Control","06e","run summary for 06e",(f06e_up-f06e_low+1),f06e_low,(f06e_up+1),"run number","Events");
    f06p = gHistogrammer->TH1DFactory("General_Control","06p","run summary for 06p",(f06p_up-f06p_low+1),f06p_low,(f06p_up+1),"run number","Events");
    f07p = gHistogrammer->TH1DFactory("General_Control","07p","run summary for 07p",(f07p_up-f07p_low+1),f07p_low,(f07p_up+1),"run number","Events");

    f96p_Taked = gHistogrammer->TH1DFactory("General_Control","96p_Taked","run summary for taked 96p",(f96p_up-f96p_low+1),f96p_low,(f96p_up+1),"run number","Events");
    f97p_Taked = gHistogrammer->TH1DFactory("General_Control","97p_Taked","run summary for taked 97p",(f97p_up-f97p_low+1),f97p_low,(f97p_up+1),"run number","Events");
    f98e_Taked = gHistogrammer->TH1DFactory("General_Control","98e_Taked","run summary for taked 98e",(f98e_up-f98e_low+1),f98e_low,(f98e_up+1),"run number","Events");
    f99e_Taked = gHistogrammer->TH1DFactory("General_Control","99e_Taked","run summary for taked 99e",(f99e_up-f99e_low+1),f99e_low,(f99e_up+1),"run number","Events");
    f99p_Taked = gHistogrammer->TH1DFactory("General_Control","99p_Taked","run summary for taked 99p",(f99p_up-f99p_low+1),f99p_low,(f99p_up+1),"run number","Events");
    f00p_Taked = gHistogrammer->TH1DFactory("General_Control","00p_Taked","run summary for taked 00p",(f00p_up-f00p_low+1),f00p_low,(f00p_up+1),"run number","Events");
    f02p_Taked = gHistogrammer->TH1DFactory("General_Control","02p_Taked","run summary for taked 02p",(f02p_up-f02p_low+1),f02p_low,(f02p_up+1),"run number","Events");
    f03p_Taked = gHistogrammer->TH1DFactory("General_Control","03p_Taked","run summary for taked 03p",(f03p_up-f03p_low+1),f03p_low,(f03p_up+1),"run number","Events");
    f04p_Taked = gHistogrammer->TH1DFactory("General_Control","04p_Taked","run summary for taked 04p",(f04p_up-f04p_low+1),f04p_low,(f04p_up+1),"run number","Events");
    f05e_Taked = gHistogrammer->TH1DFactory("General_Control","05e_Taked","run summary for taked 05e",(f05e_up-f05e_low+1),f05e_low,(f05e_up+1),"run number","Events");
    f06e_Taked = gHistogrammer->TH1DFactory("General_Control","06e_Taked","run summary for taked 06e",(f06e_up-f06e_low+1),f06e_low,(f06e_up+1),"run number","Events");
    f06p_Taked = gHistogrammer->TH1DFactory("General_Control","06p_Taked","run summary for taked 06p",(f06p_up-f06p_low+1),f06p_low,(f06p_up+1),"run number","Events");
    f07p_Taked = gHistogrammer->TH1DFactory("General_Control","07p_Taked","run summary for taked 07p",(f07p_up-f07p_low+1),f07p_low,(f07p_up+1),"run number","Events");
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GGeneral::FillControl() {
  //
  // fill general histograms
  if ( gDebug ) cout << endl << "GGeneral::FillControl() called" << endl << endl;

  if ( gCards->GetGGeneralControl() ) {
    Int_t run = gData->Getrunnr();
    if ( fPeriod == k96p ) {
      f96p_uncut->Fill(run);
      if ( gRuns->CheckRun() )
	f96p_Taked->Fill(run);
      if ( gHeader->GetAllCuts() )
	f96p->Fill(run);
    } else if ( fPeriod == k97p ) {
      f97p_uncut->Fill(run);
      if ( gRuns->CheckRun() )
	f97p_Taked->Fill(run);
      if ( gHeader->GetAllCuts() )
	f97p->Fill(run);
    } else if ( fPeriod == k98e ) {
      f98e_uncut->Fill(run);
      if ( gRuns->CheckRun() )
	f98e_Taked->Fill(run);
      if ( gHeader->GetAllCuts() )
	f98e->Fill(run);
    } else if ( fPeriod == k99e ) {
      f99e_uncut->Fill(run);
      if ( gRuns->CheckRun() )
	f99e_Taked->Fill(run);
      if ( gHeader->GetAllCuts() )
	f99e->Fill(run);
    } else if ( fPeriod == k99p ) {
      f99p_uncut->Fill(run);
      if ( gRuns->CheckRun() )
	f99p_Taked->Fill(run);
      if ( gHeader->GetAllCuts() )
	f99p->Fill(run);
    } else if ( fPeriod == k00p ) {
      f00p_uncut->Fill(run);
      if ( gRuns->CheckRun() )
	f00p_Taked->Fill(run);
      if ( gHeader->GetAllCuts() )
	f00p->Fill(run);
    } else if ( fPeriod == k02p ) {
      f02p_uncut->Fill(run);
      if ( gRuns->CheckUpgradeRun() )
	f02p_Taked->Fill(run);
      if ( gHeader->GetAllCuts() )
	f02p->Fill(run);
    } else if ( fPeriod == k03p ) {
      f03p_uncut->Fill(run);
      if ( gRuns->CheckUpgradeRun() )
	f03p_Taked->Fill(run);
      if ( gHeader->GetAllCuts() )
	f03p->Fill(run);
    } else if ( fPeriod == k04p ) {
      f04p_uncut->Fill(run);
      if ( gRuns->CheckUpgradeRun() )
	f04p_Taked->Fill(run);
      if ( gHeader->GetAllCuts() )
	f04p->Fill(run);
    } else if ( fPeriod == k05e ) {
      f05e_uncut->Fill(run);
      if ( gRuns->CheckUpgradeRun() )
	f05e_Taked->Fill(run);
      if ( gHeader->GetAllCuts() )
	f05e->Fill(run);
    } else if ( fPeriod == k06e ) {
      f06e_uncut->Fill(run);
      if ( gRuns->CheckUpgradeRun() )
	f06e_Taked->Fill(run);
      if ( gHeader->GetAllCuts() )
	f06e->Fill(run);
    } else if ( fPeriod == k06p ) {
      f06p_uncut->Fill(run);
      if ( gRuns->CheckUpgradeRun() )
	f06p_Taked->Fill(run);
      if ( gHeader->GetAllCuts() )
	f06p->Fill(run);
    } else if ( fPeriod == k07p ) {
      f07p_uncut->Fill(run);
      if ( gRuns->CheckUpgradeRun() )
	f07p_Taked->Fill(run);
      if ( gHeader->GetAllCuts() )
	f07p->Fill(run);
    }
  }

  return kTRUE;
}

//_____________________________________________________________

TString GGeneral::PrintMessage(TString option) {
  //
  // returns print message
  if ( gDebug ) cout << endl << "GPhysObj::PrintMessage() called" << endl << endl;

  TString dummy = "General:\n\n";
  dummy.Append("run period ");
  if ( fPeriod == k96p ) {
    dummy.Append("96p");
  } else if ( fPeriod == k97p ) {
    dummy.Append("97p");
  } else if ( fPeriod == k98e ) {
    dummy.Append("98e");
  } else if ( fPeriod == k99e ) {
    dummy.Append("99e");
  } else if ( fPeriod == k99p ) {
    dummy.Append("99p");
  } else if ( fPeriod == k00p ) {
    dummy.Append("00p");
  } else if ( fPeriod == k02p ) {
    dummy.Append("02p");
  } else if ( fPeriod == k03p ) {
    dummy.Append("03p");
  } else if ( fPeriod == k04p ) {
    dummy.Append("04p");
  } else if ( fPeriod == k05e ) {
    dummy.Append("05e");
  } else if ( fPeriod == k06e ) {
    dummy.Append("06e");
  } else if ( fPeriod == k06p ) {
    dummy.Append("06p");
  } else if ( fPeriod == k07p ) {
    dummy.Append("07p");
  } else if ( fPeriod == k96p97p ) {
    dummy.Append("96p-97p");
  } else if ( fPeriod == k98e99e ) {
    dummy.Append("98e-99e");
  } else if ( fPeriod == k99p00p ) {
    dummy.Append("99p-00p");
  } else if ( fPeriod == k03p04p ) {
    dummy.Append("03p-04p");
  } else if ( fPeriod == k05e06e ) {
    dummy.Append("05e-06e");
  } else if ( fPeriod == k06p07p ) {
    dummy.Append("06p-07p");
  }  
  dummy.Append("\n");

  return dummy;
}

//_____________________________________________________________

Bool_t GGeneral::CheckProperties() {
  //
  // checks which protonenergy corresponds to the current run period
  if ( gDebug ) cout << endl << "GPhysObj::PrintMessage() called" << endl << endl;

  if ( fPeriod == k96p ) {
    gCards->SetMachineEnergyProton(gCards->GetMachineLowerEnergyProton());
    gCards->SetVertexNomX(gCards->GetVertexNomXOld());
    gCards->SetMachinePositron(kTRUE);
    gCards->SetVertexBeamSpotX(gCards->GetVertexOldBeamSpotX());
    gCards->SetVertexBeamSpotXSigma(gCards->GetVertexOldBeamSpotXSigma());
    gCards->SetVertexBeamSpotY(gCards->GetVertexOldBeamSpotY());
    gCards->SetVertexBeamSpotYSigma(gCards->GetVertexOldBeamSpotYSigma());
    gCards->SetVertexBeamSpotZ(gCards->GetVertexOldBeamSpotZ());
    gCards->SetVertexBeamSpotZSigma(gCards->GetVertexOldBeamSpotZSigma());
  } else if ( fPeriod == k97p ) {
    gCards->SetMachineEnergyProton(gCards->GetMachineLowerEnergyProton());
    gCards->SetVertexNomX(gCards->GetVertexNomXOld());
    gCards->SetMachinePositron(kTRUE);
    gCards->SetVertexBeamSpotX(gCards->GetVertexOldBeamSpotX());
    gCards->SetVertexBeamSpotXSigma(gCards->GetVertexOldBeamSpotXSigma());
    gCards->SetVertexBeamSpotY(gCards->GetVertexOldBeamSpotY());
    gCards->SetVertexBeamSpotYSigma(gCards->GetVertexOldBeamSpotYSigma());
    gCards->SetVertexBeamSpotZ(gCards->GetVertexOldBeamSpotZ());
    gCards->SetVertexBeamSpotZSigma(gCards->GetVertexOldBeamSpotZSigma());
  } else if ( fPeriod == k98e ) {
    gCards->SetMachineEnergyProton(gCards->GetMachineHigherEnergyProton());
    gCards->SetVertexNomX(gCards->GetVertexNomXOld());
    gCards->SetMachinePositron(kFALSE);
    gCards->SetVertexBeamSpotX(gCards->GetVertexOldBeamSpotX());
    gCards->SetVertexBeamSpotXSigma(gCards->GetVertexOldBeamSpotXSigma());
    gCards->SetVertexBeamSpotY(gCards->GetVertexOldBeamSpotY());
    gCards->SetVertexBeamSpotYSigma(gCards->GetVertexOldBeamSpotYSigma());
    gCards->SetVertexBeamSpotZ(gCards->GetVertexOldBeamSpotZ());
    gCards->SetVertexBeamSpotZSigma(gCards->GetVertexOldBeamSpotZSigma());
  } else if ( fPeriod == k99e ) {
    gCards->SetMachineEnergyProton(gCards->GetMachineHigherEnergyProton());
    gCards->SetVertexNomX(gCards->GetVertexNomXOld());
    gCards->SetMachinePositron(kFALSE);
    gCards->SetVertexBeamSpotX(gCards->GetVertexOldBeamSpotX());
    gCards->SetVertexBeamSpotXSigma(gCards->GetVertexOldBeamSpotXSigma());
    gCards->SetVertexBeamSpotY(gCards->GetVertexOldBeamSpotY());
    gCards->SetVertexBeamSpotYSigma(gCards->GetVertexOldBeamSpotYSigma());
    gCards->SetVertexBeamSpotZ(gCards->GetVertexOldBeamSpotZ());
    gCards->SetVertexBeamSpotZSigma(gCards->GetVertexOldBeamSpotZSigma());
  } else if ( fPeriod == k99p ) {
    gCards->SetMachineEnergyProton(gCards->GetMachineHigherEnergyProton());
    gCards->SetVertexNomX(gCards->GetVertexNomXOld());
    gCards->SetMachinePositron(kTRUE);
    gCards->SetVertexBeamSpotX(gCards->GetVertexOldBeamSpotX());
    gCards->SetVertexBeamSpotXSigma(gCards->GetVertexOldBeamSpotXSigma());
    gCards->SetVertexBeamSpotY(gCards->GetVertexOldBeamSpotY());
    gCards->SetVertexBeamSpotYSigma(gCards->GetVertexOldBeamSpotYSigma());
    gCards->SetVertexBeamSpotZ(gCards->GetVertexOldBeamSpotZ());
    gCards->SetVertexBeamSpotZSigma(gCards->GetVertexOldBeamSpotZSigma());
  } else if ( fPeriod == k00p ) {
    gCards->SetMachineEnergyProton(gCards->GetMachineHigherEnergyProton());
    gCards->SetVertexNomX(gCards->GetVertexNomXOld());
    gCards->SetMachinePositron(kTRUE);
    gCards->SetVertexBeamSpotX(gCards->GetVertexOldBeamSpotX());
    gCards->SetVertexBeamSpotXSigma(gCards->GetVertexOldBeamSpotXSigma());
    gCards->SetVertexBeamSpotY(gCards->GetVertexOldBeamSpotY());
    gCards->SetVertexBeamSpotYSigma(gCards->GetVertexOldBeamSpotYSigma());
    gCards->SetVertexBeamSpotZ(gCards->GetVertexOldBeamSpotZ());
    gCards->SetVertexBeamSpotZSigma(gCards->GetVertexOldBeamSpotZSigma());
  } else if ( fPeriod == k02p ) {
    gCards->SetMachineEnergyProton(gCards->GetMachineHigherEnergyProton());
    gCards->SetVertexNomX(gCards->GetVertexNomXNew());
    gCards->SetMachinePositron(kTRUE);
    gCards->SetVertexBeamSpotX(gCards->GetVertexNewBeamSpotX());
    gCards->SetVertexBeamSpotXSigma(gCards->GetVertexNewBeamSpotXSigma());
    gCards->SetVertexBeamSpotY(gCards->GetVertexNewBeamSpotY());
    gCards->SetVertexBeamSpotYSigma(gCards->GetVertexNewBeamSpotYSigma());
    gCards->SetVertexBeamSpotZ(gCards->GetVertexNewBeamSpotZ());
    gCards->SetVertexBeamSpotZSigma(gCards->GetVertexNewBeamSpotZSigma());
  } else if ( fPeriod == k03p ) {
    gCards->SetMachineEnergyProton(gCards->GetMachineHigherEnergyProton());
    gCards->SetVertexNomX(gCards->GetVertexNomXNew());
    gCards->SetMachinePositron(kTRUE);
    gCards->SetVertexBeamSpotX(gCards->GetVertexNewBeamSpotX());
    gCards->SetVertexBeamSpotXSigma(gCards->GetVertexNewBeamSpotXSigma());
    gCards->SetVertexBeamSpotY(gCards->GetVertexNewBeamSpotY());
    gCards->SetVertexBeamSpotYSigma(gCards->GetVertexNewBeamSpotYSigma());
    gCards->SetVertexBeamSpotZ(gCards->GetVertexNewBeamSpotZ());
    gCards->SetVertexBeamSpotZSigma(gCards->GetVertexNewBeamSpotZSigma());
  } else if ( fPeriod == k04p ) {
    gCards->SetMachineEnergyProton(gCards->GetMachineHigherEnergyProton());
    gCards->SetVertexNomX(gCards->GetVertexNomXNew());
    gCards->SetMachinePositron(kTRUE);
    gCards->SetVertexBeamSpotX(gCards->GetVertexNewBeamSpotX());
    gCards->SetVertexBeamSpotXSigma(gCards->GetVertexNewBeamSpotXSigma());
    gCards->SetVertexBeamSpotY(gCards->GetVertexNewBeamSpotY());
    gCards->SetVertexBeamSpotYSigma(gCards->GetVertexNewBeamSpotYSigma());
    gCards->SetVertexBeamSpotZ(gCards->GetVertexNewBeamSpotZ());
    gCards->SetVertexBeamSpotZSigma(gCards->GetVertexNewBeamSpotZSigma());
  } else if ( fPeriod == k05e ) {
    gCards->SetMachineEnergyProton(gCards->GetMachineHigherEnergyProton());
    gCards->SetVertexNomX(gCards->GetVertexNomXNew());
    gCards->SetMachinePositron(kFALSE);
    gCards->SetVertexBeamSpotX(gCards->GetVertexNewBeamSpotX());
    gCards->SetVertexBeamSpotXSigma(gCards->GetVertexNewBeamSpotXSigma());
    gCards->SetVertexBeamSpotY(gCards->GetVertexNewBeamSpotY());
    gCards->SetVertexBeamSpotYSigma(gCards->GetVertexNewBeamSpotYSigma());
    gCards->SetVertexBeamSpotZ(gCards->GetVertexNewBeamSpotZ());
    gCards->SetVertexBeamSpotZSigma(gCards->GetVertexNewBeamSpotZSigma());
  } else if ( fPeriod == k06e ) {
    gCards->SetMachineEnergyProton(gCards->GetMachineHigherEnergyProton());
    gCards->SetVertexNomX(gCards->GetVertexNomXNew());
    gCards->SetMachinePositron(kFALSE);
    gCards->SetVertexBeamSpotX(gCards->GetVertexNewBeamSpotX());
    gCards->SetVertexBeamSpotXSigma(gCards->GetVertexNewBeamSpotXSigma());
    gCards->SetVertexBeamSpotY(gCards->GetVertexNewBeamSpotY());
    gCards->SetVertexBeamSpotYSigma(gCards->GetVertexNewBeamSpotYSigma());
    gCards->SetVertexBeamSpotZ(gCards->GetVertexNewBeamSpotZ());
    gCards->SetVertexBeamSpotZSigma(gCards->GetVertexNewBeamSpotZSigma());
  } else if ( fPeriod == k06p ) {
    gCards->SetMachineEnergyProton(gCards->GetMachineHigherEnergyProton());
    gCards->SetVertexNomX(gCards->GetVertexNomXNew());
    gCards->SetMachinePositron(kFALSE);
    gCards->SetVertexBeamSpotX(gCards->GetVertexNewBeamSpotX());
    gCards->SetVertexBeamSpotXSigma(gCards->GetVertexNewBeamSpotXSigma());
    gCards->SetVertexBeamSpotY(gCards->GetVertexNewBeamSpotY());
    gCards->SetVertexBeamSpotYSigma(gCards->GetVertexNewBeamSpotYSigma());
    gCards->SetVertexBeamSpotZ(gCards->GetVertexNewBeamSpotZ());
    gCards->SetVertexBeamSpotZSigma(gCards->GetVertexNewBeamSpotZSigma());
  } else if ( fPeriod == k07p ) {
    gCards->SetMachineEnergyProton(gCards->GetMachineHigherEnergyProton());
    gCards->SetVertexNomX(gCards->GetVertexNomXNew());
    gCards->SetMachinePositron(kFALSE);
    gCards->SetVertexBeamSpotX(gCards->GetVertexNewBeamSpotX());
    gCards->SetVertexBeamSpotXSigma(gCards->GetVertexNewBeamSpotXSigma());
    gCards->SetVertexBeamSpotY(gCards->GetVertexNewBeamSpotY());
    gCards->SetVertexBeamSpotYSigma(gCards->GetVertexNewBeamSpotYSigma());
    gCards->SetVertexBeamSpotZ(gCards->GetVertexNewBeamSpotZ());
    gCards->SetVertexBeamSpotZSigma(gCards->GetVertexNewBeamSpotZSigma());
  } else if ( fPeriod == k96p97p ) {
    gCards->SetMachineEnergyProton(gCards->GetMachineLowerEnergyProton());
    gCards->SetVertexNomX(gCards->GetVertexNomXOld());
    gCards->SetMachinePositron(kTRUE);
    gCards->SetVertexBeamSpotX(gCards->GetVertexOldBeamSpotX());
    gCards->SetVertexBeamSpotXSigma(gCards->GetVertexOldBeamSpotXSigma());
    gCards->SetVertexBeamSpotY(gCards->GetVertexOldBeamSpotY());
    gCards->SetVertexBeamSpotYSigma(gCards->GetVertexOldBeamSpotYSigma());
    gCards->SetVertexBeamSpotZ(gCards->GetVertexOldBeamSpotZ());
    gCards->SetVertexBeamSpotZSigma(gCards->GetVertexOldBeamSpotZSigma());
  } else if ( fPeriod == k98e99e ) {
    gCards->SetMachineEnergyProton(gCards->GetMachineHigherEnergyProton());
    gCards->SetVertexNomX(gCards->GetVertexNomXOld());
    gCards->SetMachinePositron(kFALSE);
    gCards->SetVertexBeamSpotX(gCards->GetVertexOldBeamSpotX());
    gCards->SetVertexBeamSpotXSigma(gCards->GetVertexOldBeamSpotXSigma());
    gCards->SetVertexBeamSpotY(gCards->GetVertexOldBeamSpotY());
    gCards->SetVertexBeamSpotYSigma(gCards->GetVertexOldBeamSpotYSigma());
    gCards->SetVertexBeamSpotZ(gCards->GetVertexOldBeamSpotZ());
    gCards->SetVertexBeamSpotZSigma(gCards->GetVertexOldBeamSpotZSigma());
  } else if ( fPeriod == k99p00p ) {
    gCards->SetMachineEnergyProton(gCards->GetMachineHigherEnergyProton());
    gCards->SetVertexNomX(gCards->GetVertexNomXOld());
    gCards->SetMachinePositron(kTRUE);
    gCards->SetVertexBeamSpotX(gCards->GetVertexOldBeamSpotX());
    gCards->SetVertexBeamSpotXSigma(gCards->GetVertexOldBeamSpotXSigma());
    gCards->SetVertexBeamSpotY(gCards->GetVertexOldBeamSpotY());
    gCards->SetVertexBeamSpotYSigma(gCards->GetVertexOldBeamSpotYSigma());
    gCards->SetVertexBeamSpotZ(gCards->GetVertexOldBeamSpotZ());
    gCards->SetVertexBeamSpotZSigma(gCards->GetVertexOldBeamSpotZSigma());
  } else if ( fPeriod == k03p04p ) {
    gCards->SetMachineEnergyProton(gCards->GetMachineHigherEnergyProton());
    gCards->SetVertexNomX(gCards->GetVertexNomXNew());
    gCards->SetMachinePositron(kTRUE);
    gCards->SetVertexBeamSpotX(gCards->GetVertexNewBeamSpotX());
    gCards->SetVertexBeamSpotXSigma(gCards->GetVertexNewBeamSpotXSigma());
    gCards->SetVertexBeamSpotY(gCards->GetVertexNewBeamSpotY());
    gCards->SetVertexBeamSpotYSigma(gCards->GetVertexNewBeamSpotYSigma());
    gCards->SetVertexBeamSpotZ(gCards->GetVertexNewBeamSpotZ());
    gCards->SetVertexBeamSpotZSigma(gCards->GetVertexNewBeamSpotZSigma());
  } else if ( fPeriod == k05e06e ) {
    gCards->SetMachineEnergyProton(gCards->GetMachineHigherEnergyProton());
    gCards->SetVertexNomX(gCards->GetVertexNomXNew());
    gCards->SetMachinePositron(kFALSE);
    gCards->SetVertexBeamSpotX(gCards->GetVertexNewBeamSpotX());
    gCards->SetVertexBeamSpotXSigma(gCards->GetVertexNewBeamSpotXSigma());
    gCards->SetVertexBeamSpotY(gCards->GetVertexNewBeamSpotY());
    gCards->SetVertexBeamSpotYSigma(gCards->GetVertexNewBeamSpotYSigma());
    gCards->SetVertexBeamSpotZ(gCards->GetVertexNewBeamSpotZ());
    gCards->SetVertexBeamSpotZSigma(gCards->GetVertexNewBeamSpotZSigma());
  } else if ( fPeriod == k06p07p ) {
    gCards->SetMachineEnergyProton(gCards->GetMachineHigherEnergyProton());
    gCards->SetVertexNomX(gCards->GetVertexNomXNew());
    gCards->SetMachinePositron(kFALSE);
    gCards->SetVertexBeamSpotX(gCards->GetVertexNewBeamSpotX());
    gCards->SetVertexBeamSpotXSigma(gCards->GetVertexNewBeamSpotXSigma());
    gCards->SetVertexBeamSpotY(gCards->GetVertexNewBeamSpotY());
    gCards->SetVertexBeamSpotYSigma(gCards->GetVertexNewBeamSpotYSigma());
    gCards->SetVertexBeamSpotZ(gCards->GetVertexNewBeamSpotZ());
    gCards->SetVertexBeamSpotZSigma(gCards->GetVertexNewBeamSpotZSigma());
  } 

  return kTRUE;
}

//_____________________________________________________________

Bool_t GGeneral::Print(TString option) {
  //
  // print message
  if ( gDebug ) cout << endl << "GPhysObj::Print() called" << endl << endl;

  option.ToUpper();

  if ( option.Contains("OUTPUTLIST") ) {
    if ( option.Contains("GGENERAL") || option.Contains("ALL") ) {
      gLister->FillOutputList(PrintMessage(option));
      gLister->FillOutputList("\n");
    }
  } else {
    cout << PrintMessage(option);
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GGeneral::CreateGeneral() {
  //
  // create general histograms
  if ( gDebug ) cout << endl << "GGeneral::CreateGeneral() called" << endl << endl;

  Int_t    weightbins = 100;
  Double_t weightlow  = 0.0;
  Double_t weighthigh = 10.0;

  fWeight_uncut = gHistogrammer->TH1DFactory("General","Weight_uncut","uncut event weight",weightbins,weightlow,weighthigh,"weight","Events");
  fWeight       = gHistogrammer->TH1DFactory("General","Weight","event weight",weightbins,weightlow,weighthigh,"weight","Events");

  return kTRUE;
}

//_____________________________________________________________

Bool_t GGeneral::FillGeneral() {
  //
  // fill general histograms
  if ( gDebug ) cout << endl << "GGeneral::FillGeneral() called" << endl << endl;

  fWeight_uncut->Fill(gHeader->GetWeight());

  if ( gHeader->GetAllCuts() ) {
    fWeight->Fill(gHeader->GetWeight());
  }

  return kTRUE;
}
