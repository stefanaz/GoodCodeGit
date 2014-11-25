//
// GMuonEfficiency.cxx
//
// $Author: gutsche $
// $Date: 2005/05/26 12:23:41 $
// $Revision: 1.4 $
//

#include <GMuonEfficiency.h>

#ifndef GUT_GInclude
#include <GInclude.h>
#endif

#ifndef __CINT__
ClassImp(GMuonEfficiency)
#endif

GMuonEfficiency *gMuonEfficiency = 0;

//_____________________________________________________________
// GMuonEfficiency
//
// muon  efficiency class
//
GMuonEfficiency::GMuonEfficiency() : TObject() {
  //
  // GMuonEfficiency default constructor
  if ( gDebug ) cout << endl << "GMuonEfficiency::GMuonEfficiency default ctor called" << endl << endl;

  // initialize global pointer
  gMuonEfficiency = this;

  if ( gCards->GetMUONEfficiencyCorrection() || gCards->GetMUONReadEfficiencyFiles() ) {
    fOK = ReadinHistograms();
  } else {
    fOK = kTRUE;
  }

}

//_____________________________________________________________

GMuonEfficiency::~GMuonEfficiency() {
  //
  // GMuonEfficiency default destructor
  if ( gDebug ) cout << endl << "GMuonEfficiency::~GMuonEfficiency dtor called" << endl << endl;

  if ( fFile != 0 )
    fFile->Close();

}

//_____________________________________________________________

Bool_t GMuonEfficiency::ReadinHistograms() {
  //
  // read in histograms from root-file

  // loose configuration (corresponds to standard configuration)

  TString filename = gSystem->Getenv("GUTCODEDIR");
  filename.Append("/analysis/efficiencies/");
  filename.Append(gCards->GetMUONEfficiencyFile());

  fFile = new TFile(filename);

  if ( fFile->IsZombie() ) {
    cout << "ERROR: GMuonEfficiency::ReadinHistograms histogram-file: " << filename << " can not be found!" << endl;
    return kFALSE;
  }

  // get histograms for BREMAT
  fNBins_BREMAT =  gCards->GetMUONEfficiencyBREMATPtNBins();
  fBins_BREMAT  =  gCards->GetMUONEfficiencyBREMATPtBins();
  fBins_Data_BREMAT = new TH1D *[fNBins_BREMAT];
  fBins_MC_BREMAT = new TH1D *[fNBins_BREMAT];
  for ( Int_t i = 0; i < fNBins_BREMAT; ++i ) {
    TString dataname = "Efficiencies/Data/MV_BREMAT_MuonEtaPtBins_";
    TString mcname = "Efficiencies/MC/MV_BREMAT_MuonEtaPtBins_";
    TString addname = gInclude->FormatedDouble(fBins_BREMAT[i],0,2);
    addname.Append("_");
    addname.Append(gInclude->FormatedDouble(fBins_BREMAT[i+1],0,2));
    dataname.Append(addname);
    mcname.Append(addname);
    fBins_Data_BREMAT[i] = (TH1D*)fFile->Get(dataname);
    if ( fBins_Data_BREMAT[i] == 0 ) {
      cout << "GMuonEfficiency::ReadinHistograms problems with Data histogram: " << dataname << endl;
      return kFALSE;
    }

    fBins_MC_BREMAT[i] = (TH1D*)fFile->Get(mcname);
    if ( fBins_MC_BREMAT[i] == 0 ) {
      cout << "GMuonEfficiency::ReadinHistograms problems with MC histogram: " << mcname << endl;
      return kFALSE;
    }
  }
  
  // get histograms for MPMATCH
  fNBins_MPMATCH =  gCards->GetMUONEfficiencyMPMATCHPtNBins();
  fBins_MPMATCH  = gCards->GetMUONEfficiencyMPMATCHPtBins();
  fBins_Data_MPMATCH = new TH1D *[fNBins_MPMATCH];
  fBins_MC_MPMATCH = new TH1D *[fNBins_MPMATCH];
  for ( Int_t i = 0; i < fNBins_MPMATCH; ++i ) {
    TString dataname = "Efficiencies/Data/MV_MPMATCH_MuonEtaPtBins_";
    TString mcname = "Efficiencies/MC/MV_MPMATCH_MuonEtaPtBins_";
    TString addname = gInclude->FormatedDouble(fBins_MPMATCH[i],0,2);
    addname.Append("_");
    addname.Append(gInclude->FormatedDouble(fBins_MPMATCH[i+1],0,2));
    dataname.Append(addname);
    mcname.Append(addname);
    fBins_Data_MPMATCH[i] = (TH1D*)fFile->Get(dataname);
    if ( fBins_Data_MPMATCH[i] == 0 ) {
      cout << "GMuonEfficiency::ReadinHistograms problems with Data histogram: " << dataname << endl;
      return kFALSE;
    }

    fBins_MC_MPMATCH[i] = (TH1D*)fFile->Get(mcname);
    if ( fBins_MC_MPMATCH[i] == 0 ) {
      cout << "GMuonEfficiency::ReadinHistograms problems with MC histogram: " << mcname << endl;
      return kFALSE;
    }
  }
  
  // get histograms for MUBAC
  fNBins_MUBAC =  gCards->GetMUONEfficiencyMUBACPtNBins();
  fBins_MUBAC  = gCards->GetMUONEfficiencyMUBACPtBins();
  fBins_Data_MUBAC = new TH1D *[fNBins_MUBAC];
  fBins_MC_MUBAC = new TH1D *[fNBins_MUBAC];
  for ( Int_t i = 0; i < fNBins_MUBAC; ++i ) {
    TString dataname = "Efficiencies/Data/MV_MUBAC_MuonEtaPtBins_";
    TString mcname = "Efficiencies/MC/MV_MUBAC_MuonEtaPtBins_";
    TString addname = gInclude->FormatedDouble(fBins_MUBAC[i],0,2);
    addname.Append("_");
    addname.Append(gInclude->FormatedDouble(fBins_MUBAC[i+1],0,2));
    dataname.Append(addname);
    mcname.Append(addname);
    fBins_Data_MUBAC[i] = (TH1D*)fFile->Get(dataname);
    if ( fBins_Data_MUBAC[i] == 0 ) {
      cout << "GMuonEfficiency::ReadinHistograms problems with Data histogram: " << dataname << endl;
      return kFALSE;
    }

    fBins_MC_MUBAC[i] = (TH1D*)fFile->Get(mcname);
    if ( fBins_MC_MUBAC[i] == 0 ) {
      cout << "GMuonEfficiency::ReadinHistograms problems with MC histogram: " << mcname << endl;
      return kFALSE;
    }
  }
  
  // tight configuration, if not valid, set to single bin with content 1 for all histos
  // take care which access functions are called

  TString tightfilename = gSystem->Getenv("GUTCODEDIR");
  tightfilename.Append("/analysis/efficiencies/");
  tightfilename.Append(gCards->GetMUONTIGHTEfficiencyFile());

  fTIGHTFile = new TFile(tightfilename);
  
  if ( fTIGHTFile->IsZombie() ) {
    cout << "ERROR: GMuonEfficiency::ReadinHistograms histogram-file: " << tightfilename << " can not be found for tight configuration!" << endl;
    cout << "ERROR: setting efficiencies for tight configuration to single bin with content 1. for all histos!" << endl;
    
    // set histograms for BREMAT
    fNBins_TIGHT_BREMAT =  1;
    fBins_TIGHT_BREMAT  =  new Double_t[2];
    fBins_TIGHT_BREMAT[0]=0.;
    fBins_TIGHT_BREMAT[1]=999999.99;
    fBins_TIGHT_Data_BREMAT = new TH1D *[fNBins_TIGHT_BREMAT];
    fBins_TIGHT_MC_BREMAT = new TH1D *[fNBins_TIGHT_BREMAT];
    for ( Int_t i = 0; i < fNBins_TIGHT_BREMAT; ++i ) {
      fBins_TIGHT_Data_BREMAT[i] = new TH1D("bremat_data","bremat_data",1,-10.,10.);
      fBins_TIGHT_Data_BREMAT[i]->Fill(1,1.);
      fBins_TIGHT_MC_BREMAT[i] = new TH1D("bremat_mc","bremat_mc",1,-10.,10.);
      fBins_TIGHT_MC_BREMAT[i]->Fill(1,1.);
    }
    
    // set histograms for MPMATCH
    fNBins_TIGHT_MPMATCH =  1;
    fBins_TIGHT_MPMATCH  =  new Double_t[2];
    fBins_TIGHT_MPMATCH[0]=0.;
    fBins_TIGHT_MPMATCH[1]=999999.99;
    fBins_TIGHT_Data_MPMATCH = new TH1D *[fNBins_TIGHT_MPMATCH];
    fBins_TIGHT_MC_MPMATCH = new TH1D *[fNBins_TIGHT_MPMATCH];
    for ( Int_t i = 0; i < fNBins_TIGHT_MPMATCH; ++i ) {
      fBins_TIGHT_Data_MPMATCH[i] = new TH1D("mpmatch_data","mpmatch_data",1,-10.,10.);
      fBins_TIGHT_Data_MPMATCH[i]->Fill(1,1.);
      
      fBins_TIGHT_MC_MPMATCH[i] = new TH1D("mpmatch_mc","mpmatch_mc",1,-10.,10.);
      fBins_TIGHT_MC_MPMATCH[i]->Fill(1,1.);
    }
    
    // set histograms for MUBAC
    fNBins_TIGHT_MUBAC =  1;
    fBins_TIGHT_MUBAC  =  new Double_t[2];
    fBins_TIGHT_MUBAC[0]=0.;
    fBins_TIGHT_MUBAC[1]=999999.99;
    fBins_TIGHT_Data_MUBAC = new TH1D *[fNBins_TIGHT_MUBAC];
    fBins_TIGHT_MC_MUBAC = new TH1D *[fNBins_TIGHT_MUBAC];
    for ( Int_t i = 0; i < fNBins_TIGHT_MUBAC; ++i ) {
      fBins_TIGHT_Data_MUBAC[i] = new TH1D("mubac_data","mubac_data",1,-10.,10.);
      fBins_TIGHT_Data_MUBAC[i]->Fill(1,1.);
      
      fBins_TIGHT_MC_MUBAC[i] = new TH1D("mubac_mc","mpmatch_mc",1,-10.,10.);
      fBins_TIGHT_MC_MPMATCH[i]->Fill(1,1.);
    }
    
  } else {
  
    // get histograms for BREMAT
    fNBins_TIGHT_BREMAT =  gCards->GetMUONTIGHTEfficiencyBREMATPtNBins();
    fBins_TIGHT_BREMAT  =  gCards->GetMUONTIGHTEfficiencyBREMATPtBins();
    fBins_TIGHT_Data_BREMAT = new TH1D *[fNBins_TIGHT_BREMAT];
    fBins_TIGHT_MC_BREMAT = new TH1D *[fNBins_TIGHT_BREMAT];
    for ( Int_t i = 0; i < fNBins_TIGHT_BREMAT; ++i ) {
      TString dataname = "Efficiencies/Data/MV_BREMAT_MuonEtaPtBins_";
      TString mcname = "Efficiencies/MC/MV_BREMAT_MuonEtaPtBins_";
      TString addname = gInclude->FormatedDouble(fBins_TIGHT_BREMAT[i],0,2);
      addname.Append("_");
      addname.Append(gInclude->FormatedDouble(fBins_TIGHT_BREMAT[i+1],0,2));
      dataname.Append(addname);
      mcname.Append(addname);
      fBins_TIGHT_Data_BREMAT[i] = (TH1D*)fTIGHTFile->Get(dataname);
      if ( fBins_TIGHT_Data_BREMAT[i] == 0 ) {
	cout << "GMuonEfficiency::ReadinHistograms problems with Data histogram: " << dataname << endl;
	return kFALSE;
      }

      fBins_TIGHT_MC_BREMAT[i] = (TH1D*)fTIGHTFile->Get(mcname);
      if ( fBins_TIGHT_MC_BREMAT[i] == 0 ) {
	cout << "GMuonEfficiency::ReadinHistograms problems with MC histogram: " << mcname << endl;
	return kFALSE;
      }
    }
  
    // get histograms for MPMATCH
    fNBins_TIGHT_MPMATCH =  gCards->GetMUONTIGHTEfficiencyMPMATCHPtNBins();
    fBins_TIGHT_MPMATCH  = gCards->GetMUONTIGHTEfficiencyMPMATCHPtBins();
    fBins_TIGHT_Data_MPMATCH = new TH1D *[fNBins_TIGHT_MPMATCH];
    fBins_TIGHT_MC_MPMATCH = new TH1D *[fNBins_TIGHT_MPMATCH];
    for ( Int_t i = 0; i < fNBins_TIGHT_MPMATCH; ++i ) {
      TString dataname = "Efficiencies/Data/MV_MPMATCH_MuonEtaPtBins_";
      TString mcname = "Efficiencies/MC/MV_MPMATCH_MuonEtaPtBins_";
      TString addname = gInclude->FormatedDouble(fBins_TIGHT_MPMATCH[i],0,2);
      addname.Append("_");
      addname.Append(gInclude->FormatedDouble(fBins_TIGHT_MPMATCH[i+1],0,2));
      dataname.Append(addname);
      mcname.Append(addname);
      fBins_TIGHT_Data_MPMATCH[i] = (TH1D*)fTIGHTFile->Get(dataname);
      if ( fBins_TIGHT_Data_MPMATCH[i] == 0 ) {
	cout << "GMuonEfficiency::ReadinHistograms problems with Data histogram: " << dataname << endl;
	return kFALSE;
      }

      fBins_TIGHT_MC_MPMATCH[i] = (TH1D*)fTIGHTFile->Get(mcname);
      if ( fBins_TIGHT_MC_MPMATCH[i] == 0 ) {
	cout << "GMuonEfficiency::ReadinHistograms problems with MC histogram: " << mcname << endl;
	return kFALSE;
      }
    }
  
    // get histograms for MUBAC
    fNBins_TIGHT_MUBAC =  gCards->GetMUONTIGHTEfficiencyMUBACPtNBins();
    fBins_TIGHT_MUBAC  = gCards->GetMUONTIGHTEfficiencyMUBACPtBins();
    fBins_TIGHT_Data_MUBAC = new TH1D *[fNBins_TIGHT_MUBAC];
    fBins_TIGHT_MC_MUBAC = new TH1D *[fNBins_TIGHT_MUBAC];
    for ( Int_t i = 0; i < fNBins_TIGHT_MUBAC; ++i ) {
      TString dataname = "Efficiencies/Data/MV_MUBAC_MuonEtaPtBins_";
      TString mcname = "Efficiencies/MC/MV_MUBAC_MuonEtaPtBins_";
      TString addname = gInclude->FormatedDouble(fBins_TIGHT_MUBAC[i],0,2);
      addname.Append("_");
      addname.Append(gInclude->FormatedDouble(fBins_TIGHT_MUBAC[i+1],0,2));
      dataname.Append(addname);
      mcname.Append(addname);
      fBins_TIGHT_Data_MUBAC[i] = (TH1D*)fTIGHTFile->Get(dataname);
      if ( fBins_TIGHT_Data_MUBAC[i] == 0 ) {
	cout << "GMuonEfficiency::ReadinHistograms problems with Data histogram: " << dataname << endl;
	return kFALSE;
      }

      fBins_TIGHT_MC_MUBAC[i] = (TH1D*)fTIGHTFile->Get(mcname);
      if ( fBins_TIGHT_MC_MUBAC[i] == 0 ) {
	cout << "GMuonEfficiency::ReadinHistograms problems with MC histogram: " << mcname << endl;
	return kFALSE;
      }
    }
  }
  
  return kTRUE;
}

//_____________________________________________________________

Double_t GMuonEfficiency::GetWeight(GMuon *muon) {
  //
  // return of weight according to muon type and runperiod
  if ( gDebug ) cout << endl << "GMuonEfficiency::GetWeight called" << endl << endl;

  Double_t weight = 1.0;

  if ( gCards->GetMC() ) {
    if ( muon->GetType() == kForward ) {
      weight = GetWeightForward(muon);
    } else if ( muon->GetType() == kBarrel ) {
      weight = GetWeightBarrel(muon);
    } else if ( muon->GetType() == kRear ) {
      weight = GetWeightRear(muon);
    }
  }

  return weight;
}

//_____________________________________________________________

Double_t GMuonEfficiency::GetWeightForward(GMuon *muon) {
  //
  // return of weight according to muon type and runperiod for forward region
  if ( gDebug ) cout << endl << "GMuonEfficiency::GetWeightForward called" << endl << endl;
  
  Double_t weight = 1.0;

  if ( gCards->GetGMuon() ) {
    if ( gCards->GetMUONEfficiencyCorrection() ) {
      // check for combinations of mpmatch anc mubac
      if ( (muon->GetMPMatch()||muon->GetMufo()) && muon->GetMuBac() ) {
	weight = GetWeightForwardMPMATCHandMUBAC(muon);
      } else if ( (muon->GetMPMatch()||muon->GetMufo()) && !muon->GetMuBac() ) {
	weight = GetWeightForwardMPMATCHandNotMUBAC(muon);
      } else if ( !(muon->GetMPMatch()||muon->GetMufo()) && muon->GetMuBac() ) {
	weight = GetWeightForwardNotMPMATCHandMUBAC(muon);
      } else {
	weight = 1.0;
      }
    }
  } else {
    if ( gGeneral->GetRunPeriod() == k96p97p ) {
      weight = gCards->GetFMUONEfficiency96p97p();
    } else if ( gGeneral->GetRunPeriod() == k98e99e ) {
      weight = gCards->GetFMUONEfficiency98e99e();
    } else if ( gGeneral->GetRunPeriod() == k99p00p ) {
      weight = gCards->GetFMUONEfficiency99p00p();
    } else if ( gGeneral->GetRunPeriod() == k03p04p ) {
      weight = gCards->GetFMUONEfficiency03p04p();
    } else if ( gGeneral->GetRunPeriod() == k05e06e ) {
      weight = gCards->GetFMUONEfficiency05e06e();
    } else if ( gGeneral->GetRunPeriod() == k06p07p ) {
      weight = gCards->GetFMUONEfficiency99p00p();
    }
  }
  return weight;
}

//_____________________________________________________________

Double_t GMuonEfficiency::GetWeightForwardMPMATCHandMUBAC(GMuon *muon) {
  //
  // return of weight according to muon type and runperiod for forward region
  // muon found by MPMATCH and MUBAC
  if ( gDebug ) cout << endl << "GMuonEfficiency::GetWeightForwardMPMATCHandMUBAC called" << endl << endl;
  
  Double_t weight = 1.0;

  Double_t mpmatch_data = GetForwardEfficiencyMPMATCHData(muon);
  Double_t mubac_data   = GetForwardEfficiencyMUBACData(muon);
  Double_t mpmatch_mc   = GetForwardEfficiencyMPMATCHMC(muon);
  Double_t mubac_mc     = GetForwardEfficiencyMUBACMC(muon);

  if ( (mpmatch_mc != 0) &&
       (mubac_mc != 0) ) {
    weight = mpmatch_data * mubac_data / mpmatch_mc / mubac_mc;
  } else {
    muon->SetEfficiencyReset(kTRUE);
  }
  
  return weight;
}

//_____________________________________________________________

Double_t GMuonEfficiency::GetWeightForwardMPMATCHandNotMUBAC(GMuon *muon) {
  //
  // return of weight according to muon type and runperiod for forward region
  // muon found by MPMATCH and not by MUBAC
  if ( gDebug ) cout << endl << "GMuonEfficiency::GetWeightForwardMPMATCHandNotMUBAC called" << endl << endl;
  
  Double_t weight = 1.0;

  Double_t mpmatch_data = GetForwardEfficiencyMPMATCHData(muon);
  Double_t mubac_data   = 1-GetForwardEfficiencyMUBACData(muon);
  Double_t mpmatch_mc   = GetForwardEfficiencyMPMATCHMC(muon);
  Double_t mubac_mc     = 1-GetForwardEfficiencyMUBACMC(muon);

  if ( (mpmatch_mc != 0) &&
       (mubac_mc != 0) ) {
    weight = mpmatch_data * mubac_data / mpmatch_mc / mubac_mc;
  } else {
    muon->SetEfficiencyReset(kTRUE);
  }
  
  return weight;
}

//_____________________________________________________________

Double_t GMuonEfficiency::GetWeightForwardNotMPMATCHandMUBAC(GMuon *muon) {
  //
  // return of weight according to muon type and runperiod for forward region
  // muon found not by MPMATCH, but by MUBAC
  if ( gDebug ) cout << endl << "GMuonEfficiency::GetWeightForwardNotMPMATCHandMUBAC called" << endl << endl;
  
  Double_t weight = 1.0;

  Double_t mpmatch_data = 1-GetForwardEfficiencyMPMATCHData(muon);
  Double_t mubac_data   = GetForwardEfficiencyMUBACData(muon);
  Double_t mpmatch_mc   = 1-GetForwardEfficiencyMPMATCHMC(muon);
  Double_t mubac_mc     = GetForwardEfficiencyMUBACMC(muon);

  if ( (mpmatch_mc != 0) &&
       (mubac_mc != 0) ) {
    weight = mpmatch_data * mubac_data / mpmatch_mc / mubac_mc;
  } else {
    muon->SetEfficiencyReset(kTRUE);
  }

  return weight;
}

//_____________________________________________________________

Double_t GMuonEfficiency::GetWeightBarrel(GMuon *muon) {
  //
  // return of weight according to muon type and runperiod for barrel region
  if ( gDebug ) cout << endl << "GMuonEfficiency::GetWeightBarrel called" << endl << endl;
  
  Double_t weight = 1.0;

  if ( gCards->GetGMuon() ) {
    if ( gCards->GetMUONEfficiencyCorrection() ) {
      // check for combinations of bremat anc mubac
      if ( muon->GetBremat() && muon->GetMuBac() ) {
	weight = GetWeightBarrelBREMATandMUBAC(muon);
      } else if ( muon->GetBremat() && !muon->GetMuBac() ) {
	weight = GetWeightBarrelBREMATandNotMUBAC(muon);
      } else if ( !muon->GetBremat() && muon->GetMuBac() ) {
	weight = GetWeightBarrelNotBREMATandMUBAC(muon);
      } else {
	weight = 1.0;
      }
    }
  } else {
    if ( gGeneral->GetRunPeriod() == k96p97p ) {
      weight = gCards->GetBMUONEfficiency96p97p();
    } else if ( gGeneral->GetRunPeriod() == k98e99e ) {
      weight = gCards->GetBMUONEfficiency98e99e();
    } else if ( gGeneral->GetRunPeriod() == k99p00p ) {
      weight = gCards->GetBMUONEfficiency99p00p();
    } else if ( gGeneral->GetRunPeriod() == k03p04p ) {
      weight = gCards->GetBMUONEfficiency03p04p();
    } else if ( gGeneral->GetRunPeriod() == k05e06e ) {
      weight = gCards->GetBMUONEfficiency05e06e();
    } else if ( gGeneral->GetRunPeriod() == k06p07p ) {
      weight = gCards->GetBMUONEfficiency06p07p();
    }

  }
  return weight;
}

//_____________________________________________________________

Double_t GMuonEfficiency::GetWeightBarrelBREMATandMUBAC(GMuon *muon) {
  //
  // return of weight according to muon type and runperiod for barrel region
  // muon found by BREMAT and MUBAC
  if ( gDebug ) cout << endl << "GMuonEfficiency::GetWeightBarrelBREMATandMUBAC called" << endl << endl;
  
  Double_t weight = 1.0;

  Double_t bremat_data  = GetBarrelEfficiencyBREMATData(muon);
  Double_t mubac_data   = GetBarrelEfficiencyMUBACData(muon);
  Double_t bremat_mc    = GetBarrelEfficiencyBREMATMC(muon);
  Double_t mubac_mc     = GetBarrelEfficiencyMUBACMC(muon);

  if ( (bremat_mc != 0) &&
       (mubac_mc != 0) ) {
    weight = bremat_data * mubac_data / bremat_mc / mubac_mc;
  } else {
    muon->SetEfficiencyReset(kTRUE);
  }
  
  return weight;
}

//_____________________________________________________________

Double_t GMuonEfficiency::GetWeightBarrelBREMATandNotMUBAC(GMuon *muon) {
  //
  // return of weight according to muon type and runperiod for barrel region
  // muon found by BREMAT and not by MUBAC
  if ( gDebug ) cout << endl << "GMuonEfficiency::GetWeightBarrelBREMATandNotMUBAC called" << endl << endl;
  
  Double_t weight = 1.0;

  Double_t bremat_data  = GetBarrelEfficiencyBREMATData(muon);
  Double_t mubac_data   = 1-GetBarrelEfficiencyMUBACData(muon);
  Double_t bremat_mc    = GetBarrelEfficiencyBREMATMC(muon);
  Double_t mubac_mc     = 1-GetBarrelEfficiencyMUBACMC(muon);

  if ( (bremat_mc != 0) &&
       (mubac_mc != 0) ) {
    weight = bremat_data * mubac_data / bremat_mc / mubac_mc;
  } else {
    muon->SetEfficiencyReset(kTRUE);
  }
  
  return weight;
}

//_____________________________________________________________

Double_t GMuonEfficiency::GetWeightBarrelNotBREMATandMUBAC(GMuon *muon) {
  //
  // return of weight according to muon type and runperiod for barrel region
  // muon found not by BREMAT, but by MUBAC
  if ( gDebug ) cout << endl << "GMuonEfficiency::GetWeightBarrelNotBREMATandMUBAC called" << endl << endl;
  
  Double_t weight = 1.0;

  Double_t bremat_data  = 1-GetBarrelEfficiencyBREMATData(muon);
  Double_t mubac_data   = GetBarrelEfficiencyMUBACData(muon);
  Double_t bremat_mc    = 1-GetBarrelEfficiencyBREMATMC(muon);
  Double_t mubac_mc     = GetBarrelEfficiencyMUBACMC(muon);

  if ( (bremat_mc != 0) &&
       (mubac_mc != 0) ) {
    weight = bremat_data * mubac_data / bremat_mc / mubac_mc;
  } else {
    muon->SetEfficiencyReset(kTRUE);
  }
  
  return weight;
}

//_____________________________________________________________

Double_t GMuonEfficiency::GetWeightRear(GMuon *muon) {
  //
  // return of weight according to muon type and runperiod for rear region
  if ( gDebug ) cout << endl << "GMuonEfficiency::GetWeightRear called" << endl << endl;
  
  Double_t weight = 1.0;

  if ( gCards->GetGMuon() ) {
    if ( gCards->GetMUONEfficiencyCorrection() ) {
      // check for combinations of bremat anc mubac
      if ( muon->GetBremat() && muon->GetMuBac() ) {
	weight = GetWeightRearBREMATandMUBAC(muon);
      } else if ( muon->GetBremat() && !muon->GetMuBac() ) {
	weight = GetWeightRearBREMATandNotMUBAC(muon);
      } else if ( !muon->GetBremat() && muon->GetMuBac() ) {
	weight = GetWeightRearNotBREMATandMUBAC(muon);
      } else {
	weight = 1.0;
      }
    }
  } else {
    if ( gGeneral->GetRunPeriod() == k96p97p ) {
      weight = gCards->GetRMUONEfficiency96p97p();
    } else if ( gGeneral->GetRunPeriod() == k98e99e ) {
      weight = gCards->GetRMUONEfficiency98e99e();
    } else if ( gGeneral->GetRunPeriod() == k99p00p ) {
      weight = gCards->GetRMUONEfficiency99p00p();
    }   if ( gGeneral->GetRunPeriod() == k03p04p ) {
      weight = gCards->GetRMUONEfficiency03p04p();
    } else if ( gGeneral->GetRunPeriod() == k05e06e ) {
      weight = gCards->GetRMUONEfficiency05e06e();
    } else if ( gGeneral->GetRunPeriod() == k06p07p ) {
      weight = gCards->GetRMUONEfficiency06p07p();
    }
  }
  return weight;
}

//_____________________________________________________________

Double_t GMuonEfficiency::GetWeightRearBREMATandMUBAC(GMuon *muon) {
  //
  // return of weight according to muon type and runperiod for rear region
  // muon found by BREMAT and MUBAC
  if ( gDebug ) cout << endl << "GMuonEfficiency::GetWeightRearBREMATandMUBAC called" << endl << endl;
  
  Double_t weight = 1.0;

  Double_t bremat_data  = GetRearEfficiencyBREMATData(muon);
  Double_t mubac_data   = GetRearEfficiencyMUBACData(muon);
  Double_t bremat_mc    = GetRearEfficiencyBREMATMC(muon);
  Double_t mubac_mc     = GetRearEfficiencyMUBACMC(muon);

  if ( (bremat_mc != 0) &&
       (mubac_mc != 0) ) {
    weight = bremat_data * mubac_data / bremat_mc / mubac_mc;
  } else {
    muon->SetEfficiencyReset(kTRUE);
  }
  
  return weight;
}

//_____________________________________________________________

Double_t GMuonEfficiency::GetWeightRearBREMATandNotMUBAC(GMuon *muon) {
  //
  // return of weight according to muon type and runperiod for rear region
  // muon found by BREMAT and not by MUBAC
  if ( gDebug ) cout << endl << "GMuonEfficiency::GetWeightRearBREMATandNotMUBAC called" << endl << endl;
  
  Double_t weight = 1.0;

  Double_t bremat_data  = GetRearEfficiencyBREMATData(muon);
  Double_t mubac_data   = 1-GetRearEfficiencyMUBACData(muon);
  Double_t bremat_mc    = GetRearEfficiencyBREMATMC(muon);
  Double_t mubac_mc     = 1-GetRearEfficiencyMUBACMC(muon);

  if ( (bremat_mc != 0) &&
       (mubac_mc != 0) ) {
    weight = bremat_data * mubac_data / bremat_mc / mubac_mc;
  } else {
    muon->SetEfficiencyReset(kTRUE);
  }
  
  return weight;
}

//_____________________________________________________________

Double_t GMuonEfficiency::GetWeightRearNotBREMATandMUBAC(GMuon *muon) {
  //
  // return of weight according to muon type and runperiod for rear region
  // muon found not by BREMAT, but by MUBAC
  if ( gDebug ) cout << endl << "GMuonEfficiency::GetWeightRearNotBREMATandMUBAC called" << endl << endl;
  
  Double_t weight = 1.0;

  Double_t bremat_data  = 1-GetRearEfficiencyBREMATData(muon);
  Double_t mubac_data   = GetRearEfficiencyMUBACData(muon);
  Double_t bremat_mc    = 1-GetRearEfficiencyBREMATMC(muon);
  Double_t mubac_mc     = GetRearEfficiencyMUBACMC(muon);

  if ( (bremat_mc != 0) &&
       (mubac_mc != 0) ) {
    weight = bremat_data * mubac_data / bremat_mc / mubac_mc;
  } else {
    muon->SetEfficiencyReset(kTRUE);
  }
  
  return weight;
}

//_____________________________________________________________

TString GMuonEfficiency::PrintEfficiencyInfo(GMuon *muon) {
  //
  // print debug info
  if ( gDebug ) cout << endl << "GMuonEfficiency::PrintEfficiencyInfo called" << endl << endl;

  TString output = "";
  Double_t weight = GetWeight(muon);
  output = "weight: ";
  output += weight;
  output.Append("\n");

  if ( muon->GetType() == kForward ) {
    output.Append("Forward, MPMATCH: ");
    output += (muon->GetMPMatch()||muon->GetMufo());
    output.Append(" MUBAC: ");
    output += muon->GetMuBac();
    output.Append(" pt: ");
    output += muon->Pt();
    output.Append(" eta: ");
    output += muon->Eta();
    output.Append("\n");
    if ( gCards->GetMUONEfficiencyCorrection() ) {
      output.Append("Efficiencies MPMATCH Data:");
      for ( Int_t i = 0; i < fNBins_MPMATCH; ++i ) {
	output.Append(" ");
	output += fBins_Data_MPMATCH[i]->GetBinContent(fBins_Data_MPMATCH[i]->FindBin(muon->Eta()));
      }
      output.Append("\n");
      output.Append("Efficiencies MPMATCH MC:");
      for ( Int_t i = 0; i < fNBins_MPMATCH; ++i ) {
	output.Append(" ");
	output += fBins_MC_MPMATCH[i]->GetBinContent(fBins_MC_MPMATCH[i]->FindBin(muon->Eta()));
      }
      output.Append("\n");
      output.Append("Efficiencies MUBAC Data:");
      for ( Int_t i = 0; i < fNBins_MUBAC; ++i ) {
	output.Append(" ");
	output += fBins_Data_MUBAC[i]->GetBinContent(fBins_Data_MUBAC[i]->FindBin(muon->Eta()));
      }
      output.Append("\n");
      output.Append("Efficiencies MUBAC MC:");
      for ( Int_t i = 0; i < fNBins_MUBAC; ++i ) {
	output.Append(" ");
	output += fBins_MC_MUBAC[i]->GetBinContent(fBins_MC_MUBAC[i]->FindBin(muon->Eta()));
      }
      output.Append("\n");
    }
  } else if ( muon->GetType() == kBarrel ) {
    if ( muon->GetBremat() ) 
      output.Append("Barrel, BREMAT: 1");
    else
      output.Append("Barrel, BREMAT: 0");
    if ( muon->GetMuBac() )
      output.Append(" MUBAC: 1");
    else
      output.Append(" MUBAC: 0");
    output.Append(" pt: ");
    output += muon->Pt();
    output.Append(" eta: ");
    output += muon->Eta();
    output.Append("\n");
    if ( gCards->GetMUONEfficiencyCorrection() ) {
      output.Append("Efficiencies BREMAT Data:");
      for ( Int_t i = 0; i < fNBins_BREMAT; ++i ) {
	output.Append(" ");
	output += fBins_Data_BREMAT[i]->GetBinContent(fBins_Data_BREMAT[i]->FindBin(muon->Eta()));
      }
      output.Append("\n");
      output.Append("Efficiencies BREMAT MC:");
      for ( Int_t i = 0; i < fNBins_BREMAT; ++i ) {
	output.Append(" ");
	output += fBins_MC_BREMAT[i]->GetBinContent(fBins_MC_BREMAT[i]->FindBin(muon->Eta()));
      }
      output.Append("\n");
      output.Append("Efficiencies MUBAC Data:");
      for ( Int_t i = 0; i < fNBins_MUBAC; ++i ) {
	output.Append(" ");
	output += fBins_Data_MUBAC[i]->GetBinContent(fBins_Data_MUBAC[i]->FindBin(muon->Eta()));
      }
      output.Append("\n");
      output.Append("Efficiencies MUBAC MC:");
      for ( Int_t i = 0; i < fNBins_MUBAC; ++i ) {
	output.Append(" ");
	output += fBins_MC_MUBAC[i]->GetBinContent(fBins_MC_MUBAC[i]->FindBin(muon->Eta()));
      }
      output.Append("\n");
    }
  } else if ( muon->GetType() == kRear ) {
    output.Append("Rear, BREMAT: ");
    output += muon->GetBremat();
    output.Append(" MUBAC: ");
    output += muon->GetMuBac();
    output.Append(" pt: ");
    output += muon->Pt();
    output.Append(" eta: ");
    output += muon->Eta();
    output.Append("\n");
    if ( gCards->GetMUONEfficiencyCorrection() ) {
      output.Append("Efficiencies BREMAT Data:");
      for ( Int_t i = 0; i < fNBins_BREMAT; ++i ) {
	output.Append(" ");
	output += fBins_Data_BREMAT[i]->GetBinContent(fBins_Data_BREMAT[i]->FindBin(muon->Eta()));
      }
      output.Append("\n");
      output.Append("Efficiencies BREMAT MC:");
      for ( Int_t i = 0; i < fNBins_BREMAT; ++i ) {
	output.Append(" ");
	output += fBins_MC_BREMAT[i]->GetBinContent(fBins_MC_BREMAT[i]->FindBin(muon->Eta()));
      }
      output.Append("\n");
      output.Append("Efficiencies MUBAC Data:");
      for ( Int_t i = 0; i < fNBins_MUBAC; ++i ) {
	output.Append(" ");
	output += fBins_Data_MUBAC[i]->GetBinContent(fBins_Data_MUBAC[i]->FindBin(muon->Eta()));
      }
      output.Append("\n");
      output.Append("Efficiencies MUBAC MC:");
      for ( Int_t i = 0; i < fNBins_MUBAC; ++i ) {
	output.Append(" ");
	output += fBins_MC_MUBAC[i]->GetBinContent(fBins_MC_MUBAC[i]->FindBin(muon->Eta()));
      }
      output.Append("\n");
    }
  }

  return output;
}

//_____________________________________________________________

Double_t GMuonEfficiency::GetLooseForwardEfficiencyMPMATCHData(GMuon *muon) {
  //
  // return forward MPMATCH Data Efficiency depending on pt
  if ( gDebug ) cout << endl << "GMuonEfficiency::GetLooseForwardEfficiencyMPMATCHData called" << endl << endl;

  Double_t efficiency = 1.0;

  if ( fNBins_MPMATCH != -99 ) {
    for ( Int_t i = 0; i < fNBins_MPMATCH; ++i ) {
      if ( (muon->Pt() >= fBins_MPMATCH[i]) && (muon->Pt() < fBins_MPMATCH[i+1]) ) {
	efficiency = fBins_Data_MPMATCH[i]->GetBinContent(fBins_Data_MPMATCH[i]->FindBin(muon->Eta()));
      }
    }
    if ( muon->Pt() >= fBins_MPMATCH[fNBins_MPMATCH]) {
      efficiency = fBins_Data_MPMATCH[fNBins_MPMATCH-1]->GetBinContent(fBins_Data_MPMATCH[fNBins_MPMATCH-1]->FindBin(muon->Eta()));
    }
  }

  return efficiency;
}

//_____________________________________________________________

Double_t GMuonEfficiency::GetLooseForwardEfficiencyMPMATCHMC(GMuon *muon) {
  //
  // return forward MPMATCH MC efficiency depending on pt
  if ( gDebug ) cout << endl << "GMuonEfficiency::GetLooseForwardEfficiencyMPMATCHMC called" << endl << endl;

  Double_t efficiency = 1.0;

  if ( fNBins_MPMATCH != -99 ) {
    for ( Int_t i = 0; i < fNBins_MPMATCH; ++i ) {
      if ( (muon->Pt() >= fBins_MPMATCH[i]) && (muon->Pt() < fBins_MPMATCH[i+1]) ) {
	efficiency = fBins_MC_MPMATCH[i]->GetBinContent(fBins_MC_MPMATCH[i]->FindBin(muon->Eta()));
      }
    }
    if ( muon->Pt() >= fBins_MPMATCH[fNBins_MPMATCH]) {
      efficiency = fBins_MC_MPMATCH[fNBins_MPMATCH-1]->GetBinContent(fBins_MC_MPMATCH[fNBins_MPMATCH-1]->FindBin(muon->Eta()));
    }
  }

  return efficiency;
}

//_____________________________________________________________

Double_t GMuonEfficiency::GetLooseForwardEfficiencyMUBACData(GMuon *muon) {
  //
  // return forward MUBAC Data efficiency depending on pt
  if ( gDebug ) cout << endl << "GMuonEfficiency::GetLooseForwardEfficiencyMUBACData called" << endl << endl;

  Double_t efficiency = 1.0;

  if ( fNBins_MUBAC != -99 ) {
    for ( Int_t i = 0; i < fNBins_MUBAC; ++i ) {
      if ( (muon->Pt() >= fBins_MUBAC[i]) && (muon->Pt() < fBins_MUBAC[i+1]) ) {
	efficiency = fBins_Data_MUBAC[i]->GetBinContent(fBins_Data_MUBAC[i]->FindBin(muon->Eta()));
      }
    }
    if ( muon->Pt() >= fBins_MUBAC[fNBins_MUBAC]) {
      efficiency = fBins_Data_MUBAC[fNBins_MUBAC-1]->GetBinContent(fBins_Data_MUBAC[fNBins_MUBAC-1]->FindBin(muon->Eta()));
    }
  }

  return efficiency;
}

//_____________________________________________________________

Double_t GMuonEfficiency::GetLooseForwardEfficiencyMUBACMC(GMuon *muon) {
  //
  // return forward MUBAC MC efficiency depending on pt
  if ( gDebug ) cout << endl << "GMuonEfficiency::GetLooseForwardEfficiencyMUBACMC called" << endl << endl;

  Double_t efficiency = 1.0;

  if ( fNBins_MUBAC != -99 ) {
    for ( Int_t i = 0; i < fNBins_MUBAC; ++i ) {
      if ( (muon->Pt() >= fBins_MUBAC[i]) && (muon->Pt() < fBins_MUBAC[i+1]) ) {
	efficiency = fBins_MC_MUBAC[i]->GetBinContent(fBins_MC_MUBAC[i]->FindBin(muon->Eta()));
      }
    }
    if ( muon->Pt() >= fBins_MUBAC[fNBins_MUBAC]) {
      efficiency = fBins_MC_MUBAC[fNBins_MUBAC-1]->GetBinContent(fBins_MC_MUBAC[fNBins_MUBAC-1]->FindBin(muon->Eta()));
    }
  }

  return efficiency;
}
//_____________________________________________________________

Double_t GMuonEfficiency::GetLooseBarrelEfficiencyBREMATData(GMuon *muon) {
  //
  // return barrel BREMAT Data efficiency depending on pt
  if ( gDebug ) cout << endl << "GMuonEfficiency::GetLooseBarrelEfficiencyBREMATData called" << endl << endl;

  Double_t efficiency = 1.0;

  if ( fNBins_BREMAT != -99 ) {
    for ( Int_t i = 0; i < fNBins_BREMAT; ++i ) {
      if ( (muon->Pt() >= fBins_BREMAT[i]) && (muon->Pt() < fBins_BREMAT[i+1]) ) {
	efficiency = fBins_Data_BREMAT[i]->GetBinContent(fBins_Data_BREMAT[i]->FindBin(muon->Eta()));
      }
    }
    if ( muon->Pt() >= fBins_BREMAT[fNBins_BREMAT]) {
      efficiency = fBins_Data_BREMAT[fNBins_BREMAT-1]->GetBinContent(fBins_Data_BREMAT[fNBins_BREMAT-1]->FindBin(muon->Eta()));
    }
  }

  return efficiency;
}

//_____________________________________________________________

Double_t GMuonEfficiency::GetLooseBarrelEfficiencyBREMATMC(GMuon *muon) {
  //
  // return barrel BREMAT MC efficiency depending on pt
  if ( gDebug ) cout << endl << "GMuonEfficiency::GetLooseBarrelEfficiencyBREMATMC called" << endl << endl;

  Double_t efficiency = 1.0;

  if ( fNBins_BREMAT != -99 ) {
    for ( Int_t i = 0; i < fNBins_BREMAT; ++i ) {
      if ( (muon->Pt() >= fBins_BREMAT[i]) && (muon->Pt() < fBins_BREMAT[i+1]) ) {
	efficiency = fBins_MC_BREMAT[i]->GetBinContent(fBins_MC_BREMAT[i]->FindBin(muon->Eta()));
      }
    }
    if ( muon->Pt() >= fBins_BREMAT[fNBins_BREMAT]) {
      efficiency = fBins_MC_BREMAT[fNBins_BREMAT-1]->GetBinContent(fBins_MC_BREMAT[fNBins_BREMAT-1]->FindBin(muon->Eta()));
    }
  }

  return efficiency;
}

//_____________________________________________________________

Double_t GMuonEfficiency::GetLooseBarrelEfficiencyMUBACData(GMuon *muon) {
  //
  // return barrel MUBAC Data efficiency depending on pt
  if ( gDebug ) cout << endl << "GMuonEfficiency::GetLooseBarrelEfficiencyMUBACData called" << endl << endl;

  Double_t efficiency = 1.0;

  if ( fNBins_MUBAC != -99 ) {
    for ( Int_t i = 0; i < fNBins_MUBAC; ++i ) {
      if ( (muon->Pt() >= fBins_MUBAC[i]) && (muon->Pt() < fBins_MUBAC[i+1]) ) {
	efficiency = fBins_Data_MUBAC[i]->GetBinContent(fBins_Data_MUBAC[i]->FindBin(muon->Eta()));
      }
    }
    if ( muon->Pt() >= fBins_MUBAC[fNBins_MUBAC]) {
      efficiency = fBins_Data_MUBAC[fNBins_MUBAC-1]->GetBinContent(fBins_Data_MUBAC[fNBins_MUBAC-1]->FindBin(muon->Eta()));
    }
  }

  return efficiency;
}

//_____________________________________________________________

Double_t GMuonEfficiency::GetLooseBarrelEfficiencyMUBACMC(GMuon *muon) {
  //
  // return barrel MUBAC MC efficiency depending on pt
  if ( gDebug ) cout << endl << "GMuonEfficiency::GetLooseBarrelEfficiencyMUBACMC called" << endl << endl;

  Double_t efficiency = 1.0;

  if ( fNBins_MUBAC != -99 ) {
    for ( Int_t i = 0; i < fNBins_MUBAC; ++i ) {
      if ( (muon->Pt() >= fBins_MUBAC[i]) && (muon->Pt() < fBins_MUBAC[i+1]) ) {
	efficiency = fBins_MC_MUBAC[i]->GetBinContent(fBins_MC_MUBAC[i]->FindBin(muon->Eta()));
      }
    }
    if ( muon->Pt() >= fBins_MUBAC[fNBins_MUBAC]) {
      efficiency = fBins_MC_MUBAC[fNBins_MUBAC-1]->GetBinContent(fBins_MC_MUBAC[fNBins_MUBAC-1]->FindBin(muon->Eta()));
    }
  }

  return efficiency;
}

//_____________________________________________________________

Double_t GMuonEfficiency::GetLooseRearEfficiencyBREMATData(GMuon *muon) {
  //
  // return rear BREMAT Data efficiency depending on pt
  if ( gDebug ) cout << endl << "GMuonEfficiency::GetLooseRearEfficiencyBREMATData called" << endl << endl;

  Double_t efficiency = 1.0;

  if ( fNBins_BREMAT != -99 ) {
    for ( Int_t i = 0; i < fNBins_BREMAT; ++i ) {
      if ( (muon->Pt() >= fBins_BREMAT[i]) && (muon->Pt() < fBins_BREMAT[i+1]) ) {
	efficiency = fBins_Data_BREMAT[i]->GetBinContent(fBins_Data_BREMAT[i]->FindBin(muon->Eta()));
      }
    }
    if ( muon->Pt() >= fBins_BREMAT[fNBins_BREMAT]) {
      efficiency = fBins_Data_BREMAT[fNBins_BREMAT-1]->GetBinContent(fBins_Data_BREMAT[fNBins_BREMAT-1]->FindBin(muon->Eta()));
    }
  }

  return efficiency;
}

//_____________________________________________________________

Double_t GMuonEfficiency::GetLooseRearEfficiencyBREMATMC(GMuon *muon) {
  //
  // return rear BREMAT MC efficiency depending on pt
  if ( gDebug ) cout << endl << "GMuonEfficiency::GetLooseRearEfficiencyBREMATMC called" << endl << endl;

  Double_t efficiency = 1.0;

  if ( fNBins_BREMAT != -99 ) {
    for ( Int_t i = 0; i < fNBins_BREMAT; ++i ) {
      if ( (muon->Pt() >= fBins_BREMAT[i]) && (muon->Pt() < fBins_BREMAT[i+1]) ) {
	efficiency = fBins_MC_BREMAT[i]->GetBinContent(fBins_MC_BREMAT[i]->FindBin(muon->Eta()));
      }
    }
    if ( muon->Pt() >= fBins_BREMAT[fNBins_BREMAT]) {
      efficiency = fBins_MC_BREMAT[fNBins_BREMAT-1]->GetBinContent(fBins_MC_BREMAT[fNBins_BREMAT-1]->FindBin(muon->Eta()));
    }
  }

  return efficiency;
}

//_____________________________________________________________

Double_t GMuonEfficiency::GetLooseRearEfficiencyMUBACData(GMuon *muon) {
  //
  // return rear MUBAC Data Efficiency depending on pt
  if ( gDebug ) cout << endl << "GMuonEfficiency::GetLooseRearEfficiencyMUBACData called" << endl << endl;

  Double_t efficiency = 1.0;

  if ( fNBins_MUBAC != -99 ) {
    for ( Int_t i = 0; i < fNBins_MUBAC; ++i ) {
      if ( (muon->Pt() >= fBins_MUBAC[i]) && (muon->Pt() < fBins_MUBAC[i+1]) ) {
	efficiency = fBins_Data_MUBAC[i]->GetBinContent(fBins_Data_MUBAC[i]->FindBin(muon->Eta()));
      }
    }
    if ( muon->Pt() >= fBins_MUBAC[fNBins_MUBAC]) {
      efficiency = fBins_Data_MUBAC[fNBins_MUBAC-1]->GetBinContent(fBins_Data_MUBAC[fNBins_MUBAC-1]->FindBin(muon->Eta()));
    }
  }

  return efficiency;
}

//_____________________________________________________________

Double_t GMuonEfficiency::GetLooseRearEfficiencyMUBACMC(GMuon *muon) {
  //
  // return rear MUBAC MC efficiency depending on pt
  if ( gDebug ) cout << endl << "GMuonEfficiency::GetLooseRearEfficiencyMUBACMC called" << endl << endl;

  Double_t efficiency = 1.0;

  if ( fNBins_MUBAC != -99 ) {
    for ( Int_t i = 0; i < fNBins_MUBAC; ++i ) {
      if ( (muon->Pt() >= fBins_MUBAC[i]) && (muon->Pt() < fBins_MUBAC[i+1]) ) {
	efficiency = fBins_MC_MUBAC[i]->GetBinContent(fBins_MC_MUBAC[i]->FindBin(muon->Eta()));
      }
    }
    if ( muon->Pt() >= fBins_MUBAC[fNBins_MUBAC]) {
      efficiency = fBins_MC_MUBAC[fNBins_MUBAC-1]->GetBinContent(fBins_MC_MUBAC[fNBins_MUBAC-1]->FindBin(muon->Eta()));
    }
  }

  return efficiency;
}

//_____________________________________________________________

Double_t GMuonEfficiency::GetTightForwardEfficiencyMPMATCHData(GMuon *muon) {
  //
  // return forward MPMATCH Data Efficiency depending on pt
  if ( gDebug ) cout << endl << "GMuonEfficiency::GetTightForwardEfficiencyMPMATCHData called" << endl << endl;

  Double_t efficiency = 1.0;

  if ( fNBins_TIGHT_MPMATCH != -99 ) {
    for ( Int_t i = 0; i < fNBins_TIGHT_MPMATCH; ++i ) {
      if ( (muon->Pt() >= fBins_TIGHT_MPMATCH[i]) && (muon->Pt() < fBins_TIGHT_MPMATCH[i+1]) ) {
	efficiency = fBins_TIGHT_Data_MPMATCH[i]->GetBinContent(fBins_TIGHT_Data_MPMATCH[i]->FindBin(muon->Eta()));
      }
    }
    if ( muon->Pt() >= fBins_TIGHT_MPMATCH[fNBins_TIGHT_MPMATCH]) {
      efficiency = fBins_TIGHT_Data_MPMATCH[fNBins_TIGHT_MPMATCH-1]->GetBinContent(fBins_TIGHT_Data_MPMATCH[fNBins_TIGHT_MPMATCH-1]->FindBin(muon->Eta()));
    }
  }

  return efficiency;
}

//_____________________________________________________________

Double_t GMuonEfficiency::GetTightForwardEfficiencyMPMATCHMC(GMuon *muon) {
  //
  // return forward MPMATCH MC efficiency depending on pt
  if ( gDebug ) cout << endl << "GMuonEfficiency::GetTightForwardEfficiencyMPMATCHMC called" << endl << endl;

  Double_t efficiency = 1.0;

  if ( fNBins_TIGHT_MPMATCH != -99 ) {
    for ( Int_t i = 0; i < fNBins_TIGHT_MPMATCH; ++i ) {
      if ( (muon->Pt() >= fBins_TIGHT_MPMATCH[i]) && (muon->Pt() < fBins_TIGHT_MPMATCH[i+1]) ) {
	efficiency = fBins_TIGHT_MC_MPMATCH[i]->GetBinContent(fBins_TIGHT_MC_MPMATCH[i]->FindBin(muon->Eta()));
      }
    }
    if ( muon->Pt() >= fBins_TIGHT_MPMATCH[fNBins_TIGHT_MPMATCH]) {
      efficiency = fBins_TIGHT_MC_MPMATCH[fNBins_TIGHT_MPMATCH-1]->GetBinContent(fBins_TIGHT_MC_MPMATCH[fNBins_TIGHT_MPMATCH-1]->FindBin(muon->Eta()));
    }
  }

  return efficiency;
}

//_____________________________________________________________

Double_t GMuonEfficiency::GetTightForwardEfficiencyMUBACData(GMuon *muon) {
  //
  // return forward MUBAC Data efficiency depending on pt
  if ( gDebug ) cout << endl << "GMuonEfficiency::GetTightForwardEfficiencyMUBACData called" << endl << endl;

  Double_t efficiency = 1.0;

  if ( fNBins_TIGHT_MUBAC != -99 ) {
    for ( Int_t i = 0; i < fNBins_TIGHT_MUBAC; ++i ) {
      if ( (muon->Pt() >= fBins_TIGHT_MUBAC[i]) && (muon->Pt() < fBins_TIGHT_MUBAC[i+1]) ) {
	efficiency = fBins_TIGHT_Data_MUBAC[i]->GetBinContent(fBins_TIGHT_Data_MUBAC[i]->FindBin(muon->Eta()));
      }
    }
    if ( muon->Pt() >= fBins_TIGHT_MUBAC[fNBins_TIGHT_MUBAC]) {
      efficiency = fBins_TIGHT_Data_MUBAC[fNBins_TIGHT_MUBAC-1]->GetBinContent(fBins_TIGHT_Data_MUBAC[fNBins_TIGHT_MUBAC-1]->FindBin(muon->Eta()));
    }
  }

  return efficiency;
}

//_____________________________________________________________

Double_t GMuonEfficiency::GetTightForwardEfficiencyMUBACMC(GMuon *muon) {
  //
  // return forward MUBAC MC efficiency depending on pt
  if ( gDebug ) cout << endl << "GMuonEfficiency::GetTightForwardEfficiencyMUBACMC called" << endl << endl;

  Double_t efficiency = 1.0;

  if ( fNBins_TIGHT_MUBAC != -99 ) {
    for ( Int_t i = 0; i < fNBins_TIGHT_MUBAC; ++i ) {
      if ( (muon->Pt() >= fBins_TIGHT_MUBAC[i]) && (muon->Pt() < fBins_TIGHT_MUBAC[i+1]) ) {
	efficiency = fBins_TIGHT_MC_MUBAC[i]->GetBinContent(fBins_TIGHT_MC_MUBAC[i]->FindBin(muon->Eta()));
      }
    }
    if ( muon->Pt() >= fBins_TIGHT_MUBAC[fNBins_TIGHT_MUBAC]) {
      efficiency = fBins_TIGHT_MC_MUBAC[fNBins_TIGHT_MUBAC-1]->GetBinContent(fBins_TIGHT_MC_MUBAC[fNBins_TIGHT_MUBAC-1]->FindBin(muon->Eta()));
    }
  }

  return efficiency;
}
//_____________________________________________________________

Double_t GMuonEfficiency::GetTightBarrelEfficiencyBREMATData(GMuon *muon) {
  //
  // return barrel BREMAT Data efficiency depending on pt
  if ( gDebug ) cout << endl << "GMuonEfficiency::GetTightBarrelEfficiencyBREMATData called" << endl << endl;

  Double_t efficiency = 1.0;

  if ( fNBins_TIGHT_BREMAT != -99 ) {
    for ( Int_t i = 0; i < fNBins_TIGHT_BREMAT; ++i ) {
      if ( (muon->Pt() >= fBins_TIGHT_BREMAT[i]) && (muon->Pt() < fBins_TIGHT_BREMAT[i+1]) ) {
	efficiency = fBins_TIGHT_Data_BREMAT[i]->GetBinContent(fBins_TIGHT_Data_BREMAT[i]->FindBin(muon->Eta()));
      }
    }
    if ( muon->Pt() >= fBins_TIGHT_BREMAT[fNBins_TIGHT_BREMAT]) {
      efficiency = fBins_TIGHT_Data_BREMAT[fNBins_TIGHT_BREMAT-1]->GetBinContent(fBins_TIGHT_Data_BREMAT[fNBins_TIGHT_BREMAT-1]->FindBin(muon->Eta()));
    }
  }

  return efficiency;
}

//_____________________________________________________________

Double_t GMuonEfficiency::GetTightBarrelEfficiencyBREMATMC(GMuon *muon) {
  //
  // return barrel BREMAT MC efficiency depending on pt
  if ( gDebug ) cout << endl << "GMuonEfficiency::GetTightBarrelEfficiencyBREMATMC called" << endl << endl;

  Double_t efficiency = 1.0;

  if ( fNBins_TIGHT_BREMAT != -99 ) {
    for ( Int_t i = 0; i < fNBins_TIGHT_BREMAT; ++i ) {
      if ( (muon->Pt() >= fBins_TIGHT_BREMAT[i]) && (muon->Pt() < fBins_TIGHT_BREMAT[i+1]) ) {
	efficiency = fBins_TIGHT_MC_BREMAT[i]->GetBinContent(fBins_TIGHT_MC_BREMAT[i]->FindBin(muon->Eta()));
      }
    }
    if ( muon->Pt() >= fBins_TIGHT_BREMAT[fNBins_TIGHT_BREMAT]) {
      efficiency = fBins_TIGHT_MC_BREMAT[fNBins_TIGHT_BREMAT-1]->GetBinContent(fBins_TIGHT_MC_BREMAT[fNBins_TIGHT_BREMAT-1]->FindBin(muon->Eta()));
    }
  }

  return efficiency;
}

//_____________________________________________________________

Double_t GMuonEfficiency::GetTightBarrelEfficiencyMUBACData(GMuon *muon) {
  //
  // return barrel MUBAC Data efficiency depending on pt
  if ( gDebug ) cout << endl << "GMuonEfficiency::GetTightBarrelEfficiencyMUBACData called" << endl << endl;

  Double_t efficiency = 1.0;

  if ( fNBins_TIGHT_MUBAC != -99 ) {
    for ( Int_t i = 0; i < fNBins_TIGHT_MUBAC; ++i ) {
      if ( (muon->Pt() >= fBins_TIGHT_MUBAC[i]) && (muon->Pt() < fBins_TIGHT_MUBAC[i+1]) ) {
	efficiency = fBins_TIGHT_Data_MUBAC[i]->GetBinContent(fBins_TIGHT_Data_MUBAC[i]->FindBin(muon->Eta()));
      }
    }
    if ( muon->Pt() >= fBins_TIGHT_MUBAC[fNBins_TIGHT_MUBAC]) {
      efficiency = fBins_TIGHT_Data_MUBAC[fNBins_TIGHT_MUBAC-1]->GetBinContent(fBins_TIGHT_Data_MUBAC[fNBins_TIGHT_MUBAC-1]->FindBin(muon->Eta()));
    }
  }

  return efficiency;
}

//_____________________________________________________________

Double_t GMuonEfficiency::GetTightBarrelEfficiencyMUBACMC(GMuon *muon) {
  //
  // return barrel MUBAC MC efficiency depending on pt
  if ( gDebug ) cout << endl << "GMuonEfficiency::GetTightBarrelEfficiencyMUBACMC called" << endl << endl;

  Double_t efficiency = 1.0;

  if ( fNBins_TIGHT_MUBAC != -99 ) {
    for ( Int_t i = 0; i < fNBins_TIGHT_MUBAC; ++i ) {
      if ( (muon->Pt() >= fBins_TIGHT_MUBAC[i]) && (muon->Pt() < fBins_TIGHT_MUBAC[i+1]) ) {
	efficiency = fBins_TIGHT_MC_MUBAC[i]->GetBinContent(fBins_TIGHT_MC_MUBAC[i]->FindBin(muon->Eta()));
      }
    }
    if ( muon->Pt() >= fBins_TIGHT_MUBAC[fNBins_TIGHT_MUBAC]) {
      efficiency = fBins_TIGHT_MC_MUBAC[fNBins_TIGHT_MUBAC-1]->GetBinContent(fBins_TIGHT_MC_MUBAC[fNBins_TIGHT_MUBAC-1]->FindBin(muon->Eta()));
    }
  }

  return efficiency;
}

//_____________________________________________________________

Double_t GMuonEfficiency::GetTightRearEfficiencyBREMATData(GMuon *muon) {
  //
  // return rear BREMAT Data efficiency depending on pt
  if ( gDebug ) cout << endl << "GMuonEfficiency::GetTightRearEfficiencyBREMATData called" << endl << endl;

  Double_t efficiency = 1.0;

  if ( fNBins_TIGHT_BREMAT != -99 ) {
    for ( Int_t i = 0; i < fNBins_TIGHT_BREMAT; ++i ) {
      if ( (muon->Pt() >= fBins_TIGHT_BREMAT[i]) && (muon->Pt() < fBins_TIGHT_BREMAT[i+1]) ) {
	efficiency = fBins_TIGHT_Data_BREMAT[i]->GetBinContent(fBins_TIGHT_Data_BREMAT[i]->FindBin(muon->Eta()));
      }
    }
    if ( muon->Pt() >= fBins_TIGHT_BREMAT[fNBins_TIGHT_BREMAT]) {
      efficiency = fBins_TIGHT_Data_BREMAT[fNBins_TIGHT_BREMAT-1]->GetBinContent(fBins_TIGHT_Data_BREMAT[fNBins_TIGHT_BREMAT-1]->FindBin(muon->Eta()));
    }
  }

  return efficiency;
}

//_____________________________________________________________

Double_t GMuonEfficiency::GetTightRearEfficiencyBREMATMC(GMuon *muon) {
  //
  // return rear BREMAT MC efficiency depending on pt
  if ( gDebug ) cout << endl << "GMuonEfficiency::GetTightRearEfficiencyBREMATMC called" << endl << endl;

  Double_t efficiency = 1.0;

  if ( fNBins_TIGHT_BREMAT != -99 ) {
    for ( Int_t i = 0; i < fNBins_TIGHT_BREMAT; ++i ) {
      if ( (muon->Pt() >= fBins_TIGHT_BREMAT[i]) && (muon->Pt() < fBins_TIGHT_BREMAT[i+1]) ) {
	efficiency = fBins_TIGHT_MC_BREMAT[i]->GetBinContent(fBins_TIGHT_MC_BREMAT[i]->FindBin(muon->Eta()));
      }
    }
    if ( muon->Pt() >= fBins_TIGHT_BREMAT[fNBins_TIGHT_BREMAT]) {
      efficiency = fBins_TIGHT_MC_BREMAT[fNBins_TIGHT_BREMAT-1]->GetBinContent(fBins_TIGHT_MC_BREMAT[fNBins_TIGHT_BREMAT-1]->FindBin(muon->Eta()));
    }
  }

  return efficiency;
}

//_____________________________________________________________

Double_t GMuonEfficiency::GetTightRearEfficiencyMUBACData(GMuon *muon) {
  //
  // return rear MUBAC Data Efficiency depending on pt
  if ( gDebug ) cout << endl << "GMuonEfficiency::GetTightRearEfficiencyMUBACData called" << endl << endl;

  Double_t efficiency = 1.0;

  if ( fNBins_TIGHT_MUBAC != -99 ) {
    for ( Int_t i = 0; i < fNBins_TIGHT_MUBAC; ++i ) {
      if ( (muon->Pt() >= fBins_TIGHT_MUBAC[i]) && (muon->Pt() < fBins_TIGHT_MUBAC[i+1]) ) {
	efficiency = fBins_TIGHT_Data_MUBAC[i]->GetBinContent(fBins_TIGHT_Data_MUBAC[i]->FindBin(muon->Eta()));
      }
    }
    if ( muon->Pt() >= fBins_TIGHT_MUBAC[fNBins_TIGHT_MUBAC]) {
      efficiency = fBins_TIGHT_Data_MUBAC[fNBins_TIGHT_MUBAC-1]->GetBinContent(fBins_TIGHT_Data_MUBAC[fNBins_TIGHT_MUBAC-1]->FindBin(muon->Eta()));
    }
  }

  return efficiency;
}

//_____________________________________________________________

Double_t GMuonEfficiency::GetTightRearEfficiencyMUBACMC(GMuon *muon) {
  //
  // return rear MUBAC MC efficiency depending on pt
  if ( gDebug ) cout << endl << "GMuonEfficiency::GetTightRearEfficiencyMUBACMC called" << endl << endl;

  Double_t efficiency = 1.0;

  if ( fNBins_TIGHT_MUBAC != -99 ) {
    for ( Int_t i = 0; i < fNBins_TIGHT_MUBAC; ++i ) {
      if ( (muon->Pt() >= fBins_TIGHT_MUBAC[i]) && (muon->Pt() < fBins_TIGHT_MUBAC[i+1]) ) {
	efficiency = fBins_TIGHT_MC_MUBAC[i]->GetBinContent(fBins_TIGHT_MC_MUBAC[i]->FindBin(muon->Eta()));
      }
    }
    if ( muon->Pt() >= fBins_TIGHT_MUBAC[fNBins_TIGHT_MUBAC]) {
      efficiency = fBins_TIGHT_MC_MUBAC[fNBins_TIGHT_MUBAC-1]->GetBinContent(fBins_TIGHT_MC_MUBAC[fNBins_TIGHT_MUBAC-1]->FindBin(muon->Eta()));
    }
  }

  return efficiency;
}
