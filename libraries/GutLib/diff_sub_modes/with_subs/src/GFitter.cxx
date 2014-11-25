//
// GFitter.cxx
//
// $Author: gutsche $
// $Date: 2005/02/07 12:31:20 $
// $Revision: 1.20 $
//

#include <GFitter.h>

#ifndef GUT_GInclude
#include <GInclude.h>
#endif

using namespace std;

GFitter *gFitter = 0;

#ifndef __CINT__
ClassImp(GFitter)
#endif

//_____________________________________________________________
// GFitter
//
//
GFitter::GFitter() : TObject() {
  //
  // GFitter default constructor
  if ( gDebug ) cout << "GFitter::GFitter default ctor called" << endl;

  // initialize global pointer
  gFitter = this;

  // initialize variables
  gMinuit          = 0;
  fBins            = 0;
  fHistos          = 0;
  fData            = 0;
  fDataErr         = 0;
  fMC              = 0;
  fMCErr           = 0;
  fStartArray      = 0;
  fStepArray       = 0;
  fParameter       = 0;
  fParameterArray  = 0;
  fParaErrArray    = 0;
  fChi2            = 0;
}

//_____________________________________________________________

GFitter::GFitter(TFile *file, Int_t parameter, Double_t *startArray, Double_t *stepArray) : TObject() {
  //
  // GFitter normal constructor
  if ( gDebug ) cout << "GFitter::GFitter normal called" << endl;

  // initialize global pointer
  gFitter = this;

  // initialize variables
  gMinuit          = 0;
  fBins            = 0;
  fHistos          = 0;
  fData            = 0;
  fDataErr         = 0;
  fMC              = 0;
  fMCErr           = 0;
  fStartArray      = startArray;
  fStepArray       = stepArray;
  fParameter       = parameter;
  fParameterArray  = new Double_t[fParameter];
  fParaErrArray    = new Double_t[fParameter];
  fChi2            = 0;

}

//_____________________________________________________________

GFitter::GFitter(int argc, char **argv) : TObject() {
  //
  // GFitter command line constructor
  if ( gDebug ) cout << "GFitter::GFitter command line ctor called" << endl;

  // initialize global pointer
  gFitter = this;

}

//_____________________________________________________________

GFitter::~GFitter() {
  //
  // GFitter default destructor
  if ( gDebug ) cout << "GFitter::~GFitter dtor called" << endl;

  if ( gMinuit != 0 )
    delete gMinuit;

  if ( fData != 0 )
    delete [] fData;
  if ( fDataErr != 0 )
    delete [] fDataErr;

  for ( Int_t i = 0; i < fBins; i++ ) {
    if ( fMC[i] != 0 )
      delete [] fMC[i];
    if ( fMCErr[i] != 0 )
      delete [] fMCErr[i];
  }

  if ( fStartArray != 0 )
    delete [] fStartArray;
  if ( fStepArray != 0 )
    delete [] fStepArray;

}

//_____________________________________________________________

Bool_t GFitter::ReadInContents(TH1D** histos) {
  //
  // read in histograms
  if ( gDebug ) cout << "GFitter::ReadInContents() called" << endl;

  Bool_t returny = kTRUE;

  if ( histos == 0 )
    return kFALSE;

  GHistogrammer histogrammer;

  if ( !histogrammer.CheckHistoCompat(fHistos,histos) ) {
    cout << "GFitter::ReadInContents histograms are not compatible" << endl;
    return kFALSE;
  }


  fBins = histos[0]->GetNbinsX();
  Int_t end = fBins;
  // check for empty bins in all three input histograms from the back
  for ( Int_t i = 1; i <= histos[0]->GetNbinsX(); ++i ) {
    if ( (histos[0]->GetBinContent(histos[0]->GetNbinsX()+1-i) == 0.0) &&
	 (histos[1]->GetBinContent(histos[1]->GetNbinsX()+1-i) == 0.0) &&
	 (histos[2]->GetBinContent(histos[2]->GetNbinsX()+1-i) == 0.0) ) {
      fBins -= 1;
      end   -= 1;
    } else {
     break;
    }
  }
  
  Int_t start = 0;
  // check for emtpy bins from the start
  for ( Int_t i = 1; i <= end; ++i ) {
    if ( (histos[0]->GetBinContent(i) == 0.0) &&
	 (histos[1]->GetBinContent(i) == 0.0) &&
	 (histos[2]->GetBinContent(i) == 0.0) ) {
      fBins -= 1;
      start = i;
    } else {
      break;
    }
  }

//   cout << "start: " << start << endl;
//   cout << "end: " << end << endl;
//   cout << "fBins: " << fBins << endl;

  // generate data arrays from boundaries
  fData    = new Double_t[fBins];
  fDataErr = new Double_t[fBins];

  // generate MC arrays from boundaries
  fMC    = new Double_t *[fBins];
  fMCErr = new Double_t *[fBins];
  Int_t tempbin = 0;
  for ( Int_t i = start; i < end; i++ ) {
    fMC[tempbin]    = new Double_t[fHistos-1];
    fMCErr[tempbin] = new Double_t[fHistos-1];
    ++tempbin;
  }

  for ( Int_t i = 0; i < fHistos; i++ ) {
    tempbin = 0;
    for ( Int_t j = start; j < end; j++ ) {
      if ( i == 0 ) {
	fData[tempbin]    = histos[i]->GetBinContent(j+1);
	fDataErr[tempbin] = histos[i]->GetBinError(j+1);
// 	cout << "fData[" << tempbin << "]: " << fData[tempbin] << " fDataErr[" << tempbin << "]: " << fDataErr[tempbin] << endl;
	++tempbin;
      } else {
	fMC[tempbin][i-1]      = histos[i]->GetBinContent(j+1);
	fMCErr[tempbin][i-1]   = histos[i]->GetBinError(j+1);
// 	cout << "fMC[" << tempbin << "][" << i-1 << "]: " << fMC[tempbin][i-1] << " fMCErr[" << tempbin << "][" << i-1 << "]: " << fMCErr[tempbin][i-1] << endl;
	++tempbin;
      }
    }
  }

  return returny;

}

//_____________________________________________________________

Bool_t GFitter::ReadInContentsImpact(TH1D** histos) {
  //
  // read in positive half of histograms, assume symmetric histograms
  if ( gDebug ) cout << "GFitter::ReadInContentsImpact() called" << endl;

  Bool_t returny = kTRUE;

  if ( histos == 0 )
    return kFALSE;

  GHistogrammer histogrammer;

  if ( !histogrammer.CheckHistoCompat(fHistos,histos) ) {
    cout << "GFitter::ReadInContents histograms are not compatible" << endl;
    return kFALSE;
  }


  fBins = histos[0]->GetNbinsX()-10;
  Int_t start = histos[0]->GetNbinsX()/2;
  Int_t end = histos[0]->GetNbinsX();
  // check for empty bins in all three input histograms from the back
  for ( Int_t i = start; i <= end; ++i ) {
    if ( (histos[0]->GetBinContent(histos[0]->GetNbinsX()+1-i) == 0.0) &&
	 (histos[1]->GetBinContent(histos[1]->GetNbinsX()+1-i) == 0.0) &&
	 (histos[2]->GetBinContent(histos[2]->GetNbinsX()+1-i) == 0.0) ) {
      fBins -= 1;
      end   -= 1;
    } else {
     break;
    }
  }
  
  // check for emtpy bins from the start
  for ( Int_t i = start; i <= end; ++i ) {
    if ( (histos[0]->GetBinContent(i) == 0.0) &&
	 (histos[1]->GetBinContent(i) == 0.0) &&
	 (histos[2]->GetBinContent(i) == 0.0) ) {
      fBins -= 1;
      start = i;
    } else {
      break;
    }
  }

//   cout << "start: " << start << endl;
//   cout << "end: " << end << endl;
//   cout << "fBins: " << fBins << endl;

  // generate data arrays from boundaries
  fData    = new Double_t[fBins];
  fDataErr = new Double_t[fBins];

  // generate MC arrays from boundaries
  fMC    = new Double_t *[fBins];
  fMCErr = new Double_t *[fBins];
  Int_t tempbin = 0;
  for ( Int_t i = start; i < end; i++ ) {
    fMC[tempbin]    = new Double_t[fHistos-1];
    fMCErr[tempbin] = new Double_t[fHistos-1];
    ++tempbin;
  }

  for ( Int_t i = 0; i < fHistos; i++ ) {
    tempbin = 0;
    for ( Int_t j = start; j < end; j++ ) {
      if ( i == 0 ) {
	fData[tempbin]    = histos[i]->GetBinContent(j+1);
	fDataErr[tempbin] = histos[i]->GetBinError(j+1);
// 	cout << "fData[" << tempbin << "]: " << fData[tempbin] << " fDataErr[" << tempbin << "]: " << fDataErr[tempbin] << endl;
	++tempbin;
      } else {
	fMC[tempbin][i-1]      = histos[i]->GetBinContent(j+1);
	fMCErr[tempbin][i-1]   = histos[i]->GetBinError(j+1);
// 	cout << "fMC[" << tempbin << "][" << i-1 << "]: " << fMC[tempbin][i-1] << " fMCErr[" << tempbin << "][" << i-1 << "]: " << fMCErr[tempbin][i-1] << endl;
	++tempbin;
      }
    }
  }

  return returny;

}

//_____________________________________________________________

Bool_t GFitter::DoFit() {
  //
  // fit with TMinuit
  if ( gDebug ) cout << "GFitter::DoFit() called" << endl;

  Bool_t returny = kTRUE;

  //initialize TMinuit
  gMinuit = new TMinuit(fParameter);
  gMinuit->SetFCN(GFitter::Chi2Function);
  gMinuit->SetPrintLevel(-1);

  Double_t arglist[10];
  Int_t ierflg = 0;

  arglist[0] = 1;
  gMinuit->mnexcm("SET ERR", arglist ,2,ierflg);

  // Set starting values and step sizes for parameters
  for ( Int_t i = 0; i < fParameter; i++) {
    TString name = "a";
    name += i;
    gMinuit->mnparm(i, name.Data(), fStartArray[i], fStepArray[i], 0.,100.,ierflg);
  }

  // Now ready for minimization step
  arglist[0] = 500;
  arglist[1] = 1.;
  gMinuit->mnexcm("MIGRAD", arglist ,2,ierflg);

  // save to parameter array
  if ( fParameterArray == 0 ) {
    fParameterArray = new Double_t[fParameter];
  }
  if ( fParaErrArray == 0 ) {
    fParaErrArray = new Double_t[fParameter];
  }

  if ( ierflg == 0 ) {
    for ( Int_t i = 0; i < fParameter; i++ ) {
      gMinuit->GetParameter(i,fParameterArray[i],fParaErrArray[i]);
    }
  } else {
    for ( Int_t i = 0; i < fParameter; i++ ) {
      fParameterArray[i] = 0.;
      fParaErrArray[i] = 0.;
    }
  }

  // Print results
  Double_t amin,edm,errdef;
  Int_t nvpar,nparx,icstat;
  gMinuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat);
  fChi2 = amin;
  
  return returny;

}

//______________________________________________________________________________

Double_t GFitter::FitFunction(Double_t *input, Double_t *par) {
  //
  // fit function
  if ( gDebug ) cout << "GFitter::FitFunction() called" << endl;
  Double_t value = 0;
  for ( Int_t i = 0; i < fParameter; i++ ) {
    value += par[i]*input[i];
  }

  return value;
}

//______________________________________________________________________________

void GFitter::Chi2Function(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag) {

  // chi2 function
  if ( gDebug ) cout << "GFitter::Chi2Function() called" << endl;
  Double_t   bins    = gFitter->GetBins();
  Double_t   histos  = gFitter->GetHistos();
  Double_t  *data    = gFitter->GetData();
  Double_t  *dataerr = gFitter->GetDataErr();
  Double_t **mc      = gFitter->GetMC();
  Double_t **mcerr   = gFitter->GetMCErr();

  Double_t chisq = 0;
  Double_t nominator = 0;
  Double_t denominator = 0;
  
  for (Int_t i = 0; i < bins; i++) {
    nominator = ( data[i] - gFitter->FitFunction(mc[i],par) ) *
                ( data[i] - gFitter->FitFunction(mc[i],par) );
    denominator  = 0;
    denominator += dataerr[i]*dataerr[i];
    for ( Int_t j = 0; j < (histos-1); j++ ) 
   	denominator += mcerr[i][j]*mcerr[i][j];
    chisq += nominator / denominator;
  }

  f = chisq;

}
