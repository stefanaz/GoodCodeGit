//
// GMuonEfficiency.h
//
// $Author: gutsche $
// $Date: 2005/05/26 12:23:40 $
// $Revision: 1.2 $
//

#ifndef GUT_GMuonEfficiency
#define GUT_GMuonEfficiency

#ifndef ROOT_TObject
#include <TObject.h>
#endif

class TH1D;
class TFile;
class GMuon;
class TString;

class GMuonEfficiency : public TObject {

private:

  Bool_t    fOK;                                     // ok flag for initialization

  TFile    *fFile;                                   // muon efficiency histogram file
  TFile    *fTIGHTFile;                              // muon efficiency histogram file

  Int_t     fNBins_BREMAT;                           // number of pt bins for BREMAT (loose configuration corresponds to standard)
  Double_t *fBins_BREMAT;                            // pt bins for BREMAT (loose configuration corresponds to standard)
  TH1D    **fBins_Data_BREMAT;                       // histograms with eta histograms in pt bins for BREMAT (Data) (loose configuration corresponds to standard)
  TH1D    **fBins_MC_BREMAT;                         // histograms with eta histograms in pt bins for BREMAT (MC) (loose configuration corresponds to standard)

  Int_t     fNBins_MPMATCH;                          // number of pt bins for MPMATCH (loose configuration corresponds to standard)
  Double_t *fBins_MPMATCH;                           // pt bins for MPMATCH (loose configuration corresponds to standard)
  TH1D    **fBins_Data_MPMATCH;                      // histograms with eta histograms in pt bins for MPMATCH (Data) (loose configuration corresponds to standard)
  TH1D    **fBins_MC_MPMATCH;                        // histograms with eta histograms in pt bins for MPMATCH (MC) (loose configuration corresponds to standard)
  
  Int_t     fNBins_MUBAC;                            // number of pt bins for MUBAC (loose configuration corresponds to standard)
  Double_t *fBins_MUBAC;                             // pt bins for MUBAC (loose configuration corresponds to standard)
  TH1D    **fBins_Data_MUBAC;                        // histograms with eta histograms in pt bins for MUBAC (Data) (loose configuration corresponds to standard)
  TH1D    **fBins_MC_MUBAC;                          // histograms with eta histograms in pt bins for MUBAC (MC) (loose configuration corresponds to standard)

  Int_t     fNBins_TIGHT_BREMAT;                     // number of pt bins for BREMAT (tight configuration)
  Double_t *fBins_TIGHT_BREMAT;                      // pt bins for BREMAT (tight configuration)
  TH1D    **fBins_TIGHT_Data_BREMAT;                 // histograms with eta histograms in pt bins for BREMAT (Data) (tight configuration)
  TH1D    **fBins_TIGHT_MC_BREMAT;                   // histograms with eta histograms in pt bins for BREMAT (MC) (tight configuration)

  Int_t     fNBins_TIGHT_MPMATCH;                    // number of pt bins for MPMATCH (tight configuration)
  Double_t *fBins_TIGHT_MPMATCH;                     // pt bins for MPMATCH (tight configuration)
  TH1D    **fBins_TIGHT_Data_MPMATCH;                // histograms with eta histograms in pt bins for MPMATCH (Data) (tight configuration)
  TH1D    **fBins_TIGHT_MC_MPMATCH;                  // histograms with eta histograms in pt bins for MPMATCH (MC) (tight configuration)
  
  Int_t     fNBins_TIGHT_MUBAC;                      // number of pt bins for MUBAC (tight configuration)
  Double_t *fBins_TIGHT_MUBAC;                       // pt bins for MUBAC (tight configuration)
  TH1D    **fBins_TIGHT_Data_MUBAC;                  // histograms with eta histograms in pt bins for MUBAC (Data) (tight configuration)
  TH1D    **fBins_TIGHT_MC_MUBAC;                    // histograms with eta histograms in pt bins for MUBAC (MC) (tight configuration)

public:
  GMuonEfficiency();
  virtual ~GMuonEfficiency();

  virtual Bool_t ReadinHistograms();

  virtual Double_t GetWeight(GMuon *muon);
  virtual Double_t GetWeightForward(GMuon *muon);
  virtual Double_t GetWeightForwardMPMATCHandMUBAC(GMuon *muon);
  virtual Double_t GetWeightForwardMPMATCHandNotMUBAC(GMuon *muon);
  virtual Double_t GetWeightForwardNotMPMATCHandMUBAC(GMuon *muon);
  virtual Double_t GetWeightBarrel(GMuon *muon);
  virtual Double_t GetWeightBarrelBREMATandMUBAC(GMuon *muon);
  virtual Double_t GetWeightBarrelBREMATandNotMUBAC(GMuon *muon);
  virtual Double_t GetWeightBarrelNotBREMATandMUBAC(GMuon *muon);
  virtual Double_t GetWeightRear(GMuon *muon);
  virtual Double_t GetWeightRearBREMATandMUBAC(GMuon *muon);
  virtual Double_t GetWeightRearBREMATandNotMUBAC(GMuon *muon);
  virtual Double_t GetWeightRearNotBREMATandMUBAC(GMuon *muon);

  virtual Double_t GetLooseForwardEfficiencyMPMATCHData(GMuon *muon);
  virtual Double_t GetLooseForwardEfficiencyMPMATCHMC(GMuon *muon);
  virtual Double_t GetLooseForwardEfficiencyMUBACData(GMuon *muon);
  virtual Double_t GetLooseForwardEfficiencyMUBACMC(GMuon *muon);
  virtual Double_t GetLooseBarrelEfficiencyBREMATData(GMuon *muon);
  virtual Double_t GetLooseBarrelEfficiencyBREMATMC(GMuon *muon);
  virtual Double_t GetLooseBarrelEfficiencyMUBACData(GMuon *muon);
  virtual Double_t GetLooseBarrelEfficiencyMUBACMC(GMuon *muon);
  virtual Double_t GetLooseRearEfficiencyBREMATData(GMuon *muon);
  virtual Double_t GetLooseRearEfficiencyBREMATMC(GMuon *muon);
  virtual Double_t GetLooseRearEfficiencyMUBACData(GMuon *muon);
  virtual Double_t GetLooseRearEfficiencyMUBACMC(GMuon *muon);

  virtual Double_t GetTightForwardEfficiencyMPMATCHData(GMuon *muon);
  virtual Double_t GetTightForwardEfficiencyMPMATCHMC(GMuon *muon);
  virtual Double_t GetTightForwardEfficiencyMUBACData(GMuon *muon);
  virtual Double_t GetTightForwardEfficiencyMUBACMC(GMuon *muon);
  virtual Double_t GetTightBarrelEfficiencyBREMATData(GMuon *muon);
  virtual Double_t GetTightBarrelEfficiencyBREMATMC(GMuon *muon);
  virtual Double_t GetTightBarrelEfficiencyMUBACData(GMuon *muon);
  virtual Double_t GetTightBarrelEfficiencyMUBACMC(GMuon *muon);
  virtual Double_t GetTightRearEfficiencyBREMATData(GMuon *muon);
  virtual Double_t GetTightRearEfficiencyBREMATMC(GMuon *muon);
  virtual Double_t GetTightRearEfficiencyMUBACData(GMuon *muon);
  virtual Double_t GetTightRearEfficiencyMUBACMC(GMuon *muon);

  virtual TString PrintEfficiencyInfo(GMuon* muon);

  inline virtual Bool_t IsOK() { return fOK; }

  // standard efficiencies are loose efficiencies
  inline virtual Double_t GetForwardEfficiencyMPMATCHData(GMuon *muon) { return GetLooseForwardEfficiencyMPMATCHData(muon); }
  inline virtual Double_t GetForwardEfficiencyMPMATCHMC(GMuon *muon) { return GetLooseForwardEfficiencyMPMATCHMC(muon); }
  inline virtual Double_t GetForwardEfficiencyMUBACData(GMuon *muon) { return GetLooseForwardEfficiencyMUBACData(muon); }
  inline virtual Double_t GetForwardEfficiencyMUBACMC(GMuon *muon) { return GetLooseForwardEfficiencyMUBACMC(muon); }
  inline virtual Double_t GetBarrelEfficiencyBREMATData(GMuon *muon) { return GetLooseBarrelEfficiencyBREMATData(muon); }
  inline virtual Double_t GetBarrelEfficiencyBREMATMC(GMuon *muon) { return GetLooseBarrelEfficiencyBREMATMC(muon); }
  inline virtual Double_t GetBarrelEfficiencyMUBACData(GMuon *muon) { return GetLooseBarrelEfficiencyMUBACData(muon); }
  inline virtual Double_t GetBarrelEfficiencyMUBACMC(GMuon *muon) { return GetLooseBarrelEfficiencyMUBACMC(muon); }
  inline virtual Double_t GetRearEfficiencyBREMATData(GMuon *muon) { return GetLooseRearEfficiencyBREMATData(muon); }
  inline virtual Double_t GetRearEfficiencyBREMATMC(GMuon *muon) { return GetLooseRearEfficiencyBREMATMC(muon); }
  inline virtual Double_t GetRearEfficiencyMUBACData(GMuon *muon) { return GetLooseRearEfficiencyMUBACData(muon); }
  inline virtual Double_t GetRearEfficiencyMUBACMC(GMuon *muon) { return GetLooseRearEfficiencyMUBACMC(muon); }

  ClassDef(GMuonEfficiency,0) // muon efficiency class
};

R__EXTERN GMuonEfficiency *gMuonEfficiency;

#endif
