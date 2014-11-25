//
// GHistogrammer.cxx
//
// $Author: meyer $
// $Date: 2008/06/10 07:00:46 $
// $Revision: 1.72 $
//

#include <GHistogrammer.h>

#ifndef GUT_GInclude
#include <GInclude.h>
#endif

#ifndef __CINT__
ClassImp(GHistogrammer)
#endif

  GHistogrammer *gHistogrammer = 0;

//_____________________________________________________________
// GHistogrammer
// Histogram create and store class
//
//
GHistogrammer::GHistogrammer() : TObject() {
  //
  // GHistogrammer default constructor
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::GHistogrammer default ctor called" << endl << endl;

  gHistogrammer = this;

  InitLists();

}

//_____________________________________________________________
GHistogrammer::GHistogrammer(TDirectory *top) : TObject() {
  //
  // GHistogrammer normal constructor
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::GHistogrammer normal ctor called" << endl << endl;

  gHistogrammer = this;

  // initialize directory pointer
  fDirGeneral   = top;

  InitLists();

}

//_____________________________________________________________

GHistogrammer::~GHistogrammer() {
  //
  // GHistogrammer default destructor
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::~GHistogrammer dtor called" << endl << endl;

  if ( fTypes != 0 ) {
    fTypes->Delete();
    delete fTypes;
  }
  if ( fPeriods != 0 ) {
    fPeriods->Delete();
    delete fPeriods;
  }
  if ( fSubdirs != 0 ) {
    fSubdirs->Delete();
    delete fSubdirs;
  }

}

//_____________________________________________________________

TH1D* GHistogrammer::TH1DFactory(TString dir, TString name, TString title,
                                 Int_t nbin, Double_t low, Double_t high,
                                 TString xtitle, TString ytitle, Bool_t store) {
  //
  // TH1D factory
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::TH1DFactory() called" << endl << endl;

  gROOT->cd();

  if ( store ) {
    // if not already created, create directory
    if ( !fDirGeneral->FindObject(dir) )
      fDirGeneral->mkdir(dir,dir);

    fDirGeneral->cd(dir);
  }

  TH1D *dummy = new TH1D(name,title,nbin,low,high);
  dummy->SetXTitle(xtitle);
  dummy->SetYTitle(ytitle);
  dummy->Sumw2();

  return dummy;

}

//_____________________________________________________________

TH1D* GHistogrammer::TH1DVarFactory(TString dir, TString name, TString title,
                                    Int_t nbin, Double_t* array,
                                    TString xtitle, TString ytitle, Bool_t store) {
  //
  // TH1D factory with variable bin sizes
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::TH1DVarFactory() called" << endl << endl;


  gROOT->cd();

  if ( store ) {
    // if not already created, create directory
    if ( !fDirGeneral->FindObject(dir) )
      fDirGeneral->mkdir(dir,dir);

    fDirGeneral->cd(dir);
  }

  TH1D *dummy = new TH1D(name,title,nbin,array);
  dummy->SetXTitle(xtitle);
  dummy->SetYTitle(ytitle);
  dummy->Sumw2();

  return dummy;

}
//_____________________________________________________________

TProfile* GHistogrammer::TH1DProfile(TString dir, TString name, TString title,
                                     Int_t nbin, Double_t lowx, Double_t highx,
                                     Double_t lowy, Double_t highy,
                                     TString xtitle, TString ytitle, Bool_t store) {
  //
  // TProfile for 2dimensional Histograms
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::TH1DProfile() called" << endl << endl;

  gROOT->cd();

  if ( store ) {
    // if not already created, create directory
    if ( !fDirGeneral->FindObject(dir) )
      fDirGeneral->mkdir(dir,dir);

    fDirGeneral->cd(dir);
  }

  TProfile *dummy = new TProfile(name,title,nbin,lowx,highx,lowy,highy);
  dummy->SetXTitle(xtitle);
  dummy->SetYTitle(ytitle);
  dummy->Sumw2();

  return dummy;

}

//_____________________________________________________________

TH1D* GHistogrammer::ProjectionFactory(TFile* file,TString dir, TH2D* hist, TString newhist, TString newtitle,Int_t axis, TString xtitle,TString ytitle,Bool_t store)
 {
  //
  // Projection factory
   if ( gDebug==-1 ) cout << endl << "GHistogrammer::ProjectionFaktory() called " << endl << endl;

  gROOT->cd();
  file->cd(dir);
  Int_t nbin = 0;
  Double_t binmax = 0;
  Double_t binmin = 0;
  TH1D *dummy= new TH1D();
  if(axis == 1){
    nbin = hist->GetXaxis()->GetNbins();
    binmin = hist->GetXaxis()->GetXmin();
    binmax = hist->GetXaxis()->GetXmax();
    dummy->SetName(newhist.Data());
    dummy->SetTitle(newtitle.Data());
    dummy->SetBins(nbin,binmin,binmax);
    dummy->SetXTitle(xtitle);
    dummy->SetYTitle(ytitle);

    Int_t low_bin = hist->GetXaxis()->GetFirst();

    Int_t up_bin  =  hist->GetXaxis()->GetLast();
    hist->ProjectionX(newhist,low_bin,up_bin,"e");
  }

  else if(axis == 2){
    nbin = hist->GetYaxis()->GetNbins();
    binmin = hist->GetYaxis()->GetXmin();
    binmax = hist->GetYaxis()->GetXmax();
    dummy->SetName(newhist.Data());
    dummy->SetTitle(newtitle.Data());
    dummy->SetBins(nbin,binmin,binmax);
    dummy->SetXTitle(xtitle);
    dummy->SetYTitle(ytitle);

    Int_t low_bin = hist->GetYaxis()->GetFirst();
    Int_t up_bin  = hist->GetYaxis()->GetLast();
    hist->ProjectionY(newhist,low_bin,up_bin,"e");
  }
  else  cout <<"in GHistogrammer ProjectionFactory axis option not known" << endl;
  

  
  return dummy;
}

//_____________________________________________________________

TH2D* GHistogrammer::TH2DFactory(TString dir, TString name, TString title,
                                 Int_t nbinx, Double_t lowx, Double_t highx,
                                 Int_t nbiny, Double_t lowy, Double_t highy,
                                 TString xtitle, TString ytitle, TString ztitle, Bool_t store) {
  //
  // TH2D factory
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::TH2DFactory() called" << endl << endl;


  gROOT->cd();

  if ( store ) {
    // if not already created, create directory
    if ( !fDirGeneral->FindObject(dir) )
      fDirGeneral->mkdir(dir,dir);

    fDirGeneral->cd(dir);
  }

  TH2D *dummy = new TH2D(name,title,nbinx,lowx,highx,nbiny,lowy,highy);
  dummy->SetXTitle(xtitle);
  dummy->SetYTitle(ytitle);
  dummy->SetZTitle(ztitle);
  dummy->Sumw2();

  return dummy;

}

//_____________________________________________________________

TH2D* GHistogrammer::TH2DVarFactory(TString dir, TString name, TString title,
				    Int_t nbinx, Double_t* xarray,
				    Int_t nbiny, Double_t lowy, Double_t highy,
				    TString xtitle, TString ytitle, TString ztitle, Bool_t store) {
  //
  // TH2D factory with variable bin sizes in x
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::TH2DVarFactory() called" << endl << endl;


  gROOT->cd();

  if ( store ) {
    // if not already created, create directory
    if ( !fDirGeneral->FindObject(dir) )
      fDirGeneral->mkdir(dir,dir);

    fDirGeneral->cd(dir);
  }
  
  TH2D *dummy = new TH2D(name,title,nbinx,xarray,nbiny,lowy,highy);
  dummy->SetXTitle(xtitle);
  dummy->SetYTitle(ytitle);
  dummy->SetZTitle(ztitle);
  dummy->Sumw2();
  
  return dummy;

}

//_____________________________________________________________

TH2D* GHistogrammer::TH2DVarFactory(TString dir, TString name, TString title,
				    Int_t nbinx, Double_t lowx, Double_t highx,
				    Int_t nbiny, Double_t* yarray,
				    TString xtitle, TString ytitle, TString ztitle, Bool_t store) {
  //
  // TH2D factory with variable bin sizes in y
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::TH2DVarFactory() called" << endl << endl;


  gROOT->cd();
  if ( store ) {
    // if not already created, create directory
    if ( !fDirGeneral->FindObject(dir) )
      fDirGeneral->mkdir(dir,dir);

    fDirGeneral->cd(dir);
  }

  TH2D *dummy = new TH2D(name,title,nbinx,lowx,highx,nbiny,yarray);
  dummy->SetXTitle(xtitle);
  dummy->SetYTitle(ytitle);
  dummy->SetZTitle(ztitle);
  dummy->Sumw2();

  return dummy;

}

//_____________________________________________________________

TH2D* GHistogrammer::TH2DVarFactory(TString dir, TString name, TString title,
				    Int_t nbinx, Double_t* xarray,
				    Int_t nbiny, Double_t* yarray,
				    TString xtitle, TString ytitle, TString ztitle, Bool_t store) {
  //
  // TH2D factory with variable bin sizes in x and y
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::TH2DVarFactory() called" << endl << endl;


  gROOT->cd();
  if ( store ) {
    // if not already created, create directory
    if ( !fDirGeneral->FindObject(dir) )
      fDirGeneral->mkdir(dir,dir);

    fDirGeneral->cd(dir);
  }

  TH2D *dummy = new TH2D(name,title,nbinx,xarray,nbiny,yarray);
  dummy->SetXTitle(xtitle);
  dummy->SetYTitle(ytitle);
  dummy->SetZTitle(ztitle);
  dummy->Sumw2();

  return dummy;

}

//_____________________________________________________________

TH1D* GHistogrammer::TH1DLabelFactory(TString dir, TString name, TString title,
                                      TString binlabels,
                                      TString xtitle, TString ytitle, Bool_t store) {
  //
  // TH1D factory for labeled bins, derived from binlabes char string, separate labes by comma
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::TH1DLabelFactory() called" << endl << endl;

  gROOT->cd();
  if ( store ) {
    // if not already created, create directory
    if ( !fDirGeneral->FindObject(dir) )
      fDirGeneral->mkdir(dir,dir);

    fDirGeneral->cd(dir);
  }

  // put binlabels in string
  TString labels(binlabels);

  // init char variable
  char first = 0;

  // derive number of bins, count number of commas
  Int_t bins = labels.CountChar(44) + 1;

  // fill string array for bins
  TString array[bins];
  for ( Int_t i = 0; i < bins; i++) {
    while ( (first = labels(0)) ) {
      // remove first
      labels.Remove(0,1);
      // sort to arrays or break in case of comma
      if ( first == 44 )
        break;
      else
        array[i].Append(first);
    }
  }

  TH1D *dummy = new TH1D(name,title,bins,0.,(Double_t)bins);
  dummy->SetXTitle(xtitle);
  dummy->SetYTitle(ytitle);

  // set bin labels
  for ( Int_t i = 1; i <= bins; i++)
    dummy->GetXaxis()->SetBinLabel(i,array[i-1].Data());

  // draw vertical labels
  dummy->LabelsOption("v");

  return dummy;
}

//_____________________________________________________________

TH1D* GHistogrammer::IntHist(TH1D* histo) {
  //
  // takes input histogram, calculates content for all bins for entries greater than this bin, returns histogram
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::IntHist() called" << endl << endl;

  Int_t bins = histo->GetNbinsX();

  // generate name
  TString name = histo->GetName();
  name.Append("_int");

  // generate title
  TString title = histo->GetTitle();
  title.Append(" (int)");

  TH1D *dummy = new TH1D(name.Data(),title.Data(),bins,histo->GetXaxis()->GetXmin(),histo->GetXaxis()->GetXmax());
  dummy->SetLineColor(2);
  dummy->SetXTitle(histo->GetXaxis()->GetTitle());
  dummy->SetYTitle(histo->GetYaxis()->GetTitle());
  dummy->Sumw2();

  for ( Int_t j = 0; j < bins; j++ ) {
    Double_t integral = histo->Integral(j,bins);
    dummy->SetBinContent(j,integral);
  }

  if ( !gROOT->IsBatch() )
    dummy->Draw();
  return dummy;

}

//_____________________________________________________________

TH1D* GHistogrammer::InvIntHist(TH1D* histo) {
  //
  // takes input histogram, calculates content for all bins for entries smaller than this bin, returns histogram
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::InvIntHist() called" << endl << endl;

  Int_t bins = histo->GetNbinsX();

  // generate name
  TString name = histo->GetName();
  name.Append("_int");

  // generate title
  TString title = histo->GetTitle();
  title.Append(" (int)");

  TH1D *dummy = new TH1D(name.Data(),title.Data(),bins,histo->GetXaxis()->GetXmin(),histo->GetXaxis()->GetXmax());
  dummy->SetLineColor(2);
  dummy->SetXTitle(histo->GetXaxis()->GetTitle());
  dummy->SetYTitle(histo->GetYaxis()->GetTitle());
  dummy->Sumw2();

  for ( Int_t j = 0; j < bins; j++ ) {
    Double_t integral = histo->Integral(1,j);
    dummy->SetBinContent(j,integral);
  }

  if ( !gROOT->IsBatch() )
    dummy->Draw();
  return dummy;

}

//_____________________________________________________________

TH1D* GHistogrammer::LabelHist(TString name, TString title, TString xaxistitle, TString yaxistitle, TString labels, TString contents) {
  //
  // generate label-histogramm and fill with contents
  // labels, and contents separated by comma
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::LabelHist() called" << endl << endl;

  // put labels in string
  TString label(labels);
  TString content(contents);

  // init char variable
  char first = 0;

  // derive number of bins, count number of commas
  Int_t bins = label.CountChar(44) + 1;
  Int_t bins2 = content.CountChar(44) + 1;
  if ( bins != bins2 ) {
    cout << "Number of labels does not match number of contents!" << endl;
    return 0;
  }


  // fill string array for bins
  TString labelarray[bins];
  TString contarray[bins2];

  for ( Int_t i = 0; i < bins; i++) {
    while ( (first = label(0)) ) {
      // remove first
      label.Remove(0,1);
      // sort to arrays or break in case of comma
      if ( first == 44 )
        break;
      else
        labelarray[i].Append(first);
    }
  }

  for ( Int_t i = 0; i < bins2; i++) {
    while ( (first = content(0)) ) {
      // remove first
      content.Remove(0,1);
      // sort to arrays or break in case of comma
      if ( first == 44 )
        break;
      else
        contarray[i].Append(first);
    }
  }

  TH1D *dummy = new TH1D(name,title,bins,0.,(Double_t)bins);
  dummy->SetXTitle(xaxistitle);
  dummy->SetYTitle(yaxistitle);

  // set bin labels
  for ( Int_t i = 1; i <= bins; i++)
    dummy->GetXaxis()->SetBinLabel(i,labelarray[i-1].Data());

  // fill contents
  for ( Int_t i = 1; i <= bins2; i++) {
    istrstream istream(contarray[i-1].Data());
    Double_t input = 0;
    istream >> input;
    dummy->SetBinContent(i,input);
  }
  dummy->SetFillColor(2);
  dummy->SetStats(kFALSE);
  dummy->SetBarWidth(0.6);
  dummy->SetBarOffset(0.2);

  if ( !gROOT->IsBatch() )
    dummy->Draw("bar");

  return dummy;
}

//_____________________________________________________________

TH1D* GHistogrammer::AddTwoHistograms(TH1D* histo1, Double_t weight1, TH1D* histo2, Double_t weight2) {
  //
  // add two histograms with respective weights
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::AddTwoHistograms() called" << endl << endl;

  if ( !this->CheckTwoHistoCompat(histo1,histo2) ) {
    cout << "addtwohistograms: histograms are not compatible" << endl;
    return 0;
  }
  TString name = "Added: ";
  name.Append(histo1->GetName());
  name.Append(" and ");
  name.Append(histo2->GetName());

  TString title = "Added: ";
  title.Append(histo1->GetTitle());
  title.Append(" and ");
  title.Append(histo2->GetTitle());

  TH1D* dummy = new TH1D(name.Data(),title.Data(),histo1->GetNbinsX(),histo1->GetXaxis()->GetXmin(),histo1->GetXaxis()->GetXmax());
  dummy->Sumw2();

  dummy->Add(histo1,weight1);
  dummy->Add(histo2,weight2);

  return dummy;

}
//_____________________________________________________________

Bool_t GHistogrammer::CheckTwoHistoCompat(TH1D* histo1, TH1D* histo2) {
  //
  // check if two histograms are compatible
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::CheckTwoHistograms() called" << endl << endl;

  Bool_t returny = kTRUE;

  // check for number of bins
  if ( histo1->GetNbinsX() != histo2->GetNbinsX() )
    returny = kFALSE;
  Int_t nbins = histo1->GetNbinsX();
  
  // check compatibility of each bin
  for ( Int_t i = 1; i <= nbins; i++ ) {
    // check bin width compatibility
    if ( histo1->GetBinWidth(i)-histo2->GetBinWidth(i) > 0.00001 ) {
      returny = kFALSE;
    }
    // check bin center compatibility
    if ( histo1->GetBinCenter(i)-histo2->GetBinCenter(i) > 0.00001 ) {
      returny = kFALSE;
    }
  }
  // check if axis titles are the same
  TString title = histo1->GetXaxis()->GetTitle();
  if ( !title.Contains(histo2->GetXaxis()->GetTitle()))
    returny = kFALSE;
  title = histo1->GetYaxis()->GetTitle();
  if ( !title.Contains(histo2->GetYaxis()->GetTitle()))
    returny = kFALSE;
  
  return returny;
}

//_____________________________________________________________

Bool_t GHistogrammer::CheckTwoHistoCompat2D(TH2D* histo1, TH2D* histo2) {
  //
  // check if two histograms are compatible
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::CheckTwoHistograms2D called" << endl << endl;

  Bool_t returny = kTRUE;

  // check for number of bins
  if ( histo1->GetNbinsX() != histo2->GetNbinsX() )
    returny = kFALSE;
  if ( histo1->GetNbinsY() != histo2->GetNbinsY() )
    returny = kFALSE;

  Int_t nbinsx = histo1->GetNbinsX();
  Int_t nbinsy = histo1->GetNbinsY();

  // check compatibility of each bin
  for ( Int_t i = 1; i <= nbinsx; i++ ) {
    // check bin width compatibility
    if ( histo1->GetXaxis()->GetBinWidth(i)-histo2->GetXaxis()->GetBinWidth(i) > 0.00001 ) {
      returny = kFALSE;
    }
    // check bin center compatibility
    if ( histo1->GetXaxis()->GetBinCenter(i)-histo2->GetXaxis()->GetBinCenter(i) > 0.00001 ) {
      returny = kFALSE;
    }
  }

  // check compatibility of each bin
  for ( Int_t i = 1; i <= nbinsy; i++ ) {
    // check bin width compatibility
    if ( histo1->GetYaxis()->GetBinWidth(i)-histo2->GetYaxis()->GetBinWidth(i) > 0.00001 ) {
      returny = kFALSE;
    }
    // check bin center compatibility
    if ( histo1->GetYaxis()->GetBinCenter(i)-histo2->GetYaxis()->GetBinCenter(i) > 0.00001 ) {
      returny = kFALSE;
    }
  }

  // check if axis titles are the same
  TString title = histo1->GetXaxis()->GetTitle();
  if ( !title.Contains(histo2->GetXaxis()->GetTitle()))
    returny = kFALSE;
  title = histo1->GetYaxis()->GetTitle();
  if ( !title.Contains(histo2->GetYaxis()->GetTitle()))
    returny = kFALSE;
  title = histo1->GetZaxis()->GetTitle();
  if ( !title.Contains(histo2->GetZaxis()->GetTitle()))
    returny = kFALSE;

  return returny;
}

//_____________________________________________________________

Bool_t GHistogrammer::CheckHistoCompat(Int_t number, TH1D **histos) {
  //
  // check if histograms are compatible
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::CheckHistoCompat() called" << endl << endl;

  Bool_t returny = kTRUE;

  for ( Int_t i = 0; i < number; i++ ) {
    for ( Int_t j = 0; j < number; j++ ) {
      if ( !this->CheckTwoHistoCompat(histos[i],histos[j]) ) {
        returny = kFALSE;
        cout << "histogram: " << histos[i]->GetName() << " is not compatible with histogram: " <<
          histos[j]->GetName() << endl;
      }
    }
  }
  return returny;
}

//_____________________________________________________________

Bool_t GHistogrammer::CheckHistoCompat(TList *histolist) {
  //
  // check if histograms are compatible
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::CheckHistoCompat() called" << endl << endl;

  Bool_t returny = kTRUE;

  TIter next1(histolist);
  TIter next2(histolist);

  while ( TH1D *histo1 = (TH1D*)next1() ) {
    while ( TH1D *histo2 = (TH1D*)next2() ) {
      if ( !this->CheckTwoHistoCompat(histo1,histo2) ) {
        returny = kFALSE;
        cout << "histogram: " << histo1->GetName() << " is not compatible with histogram: " <<
          histo2->GetName() << endl;
      }
    }
  }
  return returny;
}

//_____________________________________________________________

Bool_t GHistogrammer::CheckHistoCompat2D(Int_t number, TH2D **histos) {
  //
  // check if histograms are compatible
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::CheckHistoCompat2D() called" << endl << endl;

  Bool_t returny = kTRUE;

  for ( Int_t i = 0; i < number; i++ ) {
    for ( Int_t j = 0; j < number; j++ ) {
      if ( !this->CheckTwoHistoCompat2D(histos[i],histos[j]) ) {
        returny = kFALSE;
        cout << "histogram: " << histos[i]->GetName() << " is not compatible with histogram: " <<
          histos[j]->GetName() << endl;
      }
    }
  }
  return returny;
}

//_____________________________________________________________

Bool_t GHistogrammer::CheckHistoCompat2D(TList *histolist) {
  //
  // check if 2D histograms are compatible
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::CheckHistoCompat2D() called" << endl << endl;

  Bool_t returny = kTRUE;

  TIter next1(histolist);
  TIter next2(histolist);

  while ( TH2D *histo1 = (TH2D*)next1() ) {
    while ( TH2D *histo2 = (TH2D*)next2() ) {
      if ( !this->CheckTwoHistoCompat2D(histo1,histo2) ) {
        returny = kFALSE;
        cout << "histogram: " << histo1->GetName() << " is not compatible with histogram: " <<
          histo2->GetName() << endl;
      }
    }
  }
  return returny;
}

// //_____________________________________________________________

// Bool_t GHistogrammer::AddHistos(TFile *file, TString type, TString period, TString histogramname, TString histoname, TString histotitle, TString option) {
//   //
//   // merge histograms to histogram in smallest same directory + merged directory in file
//   if ( gDebug==-1 ) cout << endl << "GHistogrammer::AddHistos called" << endl << endl;

//   Bool_t localdebug = kFALSE;

//   option.ToUpper();
//   if ( option.Contains("DEBUG") )
//     localdebug = kTRUE;

//   TList *histolist = new TList();
//   TList *histodirlist = new TList();
//   TList *typelist = new TList();
//   Int_t histonum = 0;

//   // string to remember the complete period of valid data for stage 3
//   TString compperiod = "";

//   // check if type has "," inside, if yes, merge already merged histos, if not, merge subdirs in type
//   if ( type.Contains(",") ) {

//     TString temptype = type;

//     char first;
//     TString temp = "";
//     // separate entries in types
//     while ( (first = temptype(0)) ) {
//       // remove first
//       temptype.Remove(0,1);
//       // append to temp or break in case of comma
//       if ( first == 44 ) {
// 	typelist->Add(new TObjString(temp));
// 	temp = "";
//       } else {
//         temp.Append(first);
//       }
//     }
//     if ( temp.Length() != 0 ) {
//       typelist->Add(new TObjString(temp));
//     }
    
//     // fill histo list
//     TIter nexttype(typelist);
//     temp = "";
//     while ( TObjString *looptype = (TObjString*)nexttype() ) {
//       if ( option.Contains("DATA") ) {
// 	temp = "Histograms/data/";
// 	temp.Append(looptype->GetString());
// 	temp.Append("/");
// 	temp.Append(histogramname);
//       } else {
// 	temp = "Histograms/mc/";
// 	temp.Append(period);
// 	temp.Append("/");
// 	temp.Append(looptype->GetString());
// 	temp.Append("/merged/");
// 	temp.Append(histogramname);
//       }
//       TH1D* histo = (TH1D*)file->Get(temp);
//       if ( histo != 0 ) {
// 	histolist->Add(histo);
// 	histodirlist->Add(new TObjString(temp));
// 	histonum += 1;
//       }
//     }
//   } else {

//     // fill histo list
//     if ( option.Contains("DATA") ) {
//       TIter nextperiod(fPeriods);
//       TString temp = "";
//       TString compperiodstart = "";
//       TString compperiodend = "";
//       Bool_t first = kTRUE;
//       while ( TObjString *period = (TObjString*)nextperiod() ) {
// 	temp = "Histograms/data/merged/";
// 	temp.Append(histogramname);
// 	temp.Append("_");
// 	temp.Append(period->GetString());
// 	TH1D* histo = (TH1D*)file->Get(temp);
// 	if ( histo != 0 ) {
// 	  histolist->Add(histo);
// 	  histodirlist->Add(new TObjString(temp));
// 	  histonum += 1;
// 	  if ( first ) {
// 	    compperiodstart = period->GetString();
// 	    first = kFALSE;
// 	  }
// 	  compperiodend = period->GetString();
// 	}
//       }
//       compperiodstart.Remove(3,compperiodstart.Length()-3);
//       compperiodend.Remove(0,4);
//       compperiod = compperiodstart;
//       compperiod.Append("-");
//       compperiod.Append(compperiodend);
//     } else {
//       TIter nextsubdir(fSubdirs);
//       TString temp = "";
//       while ( TObjString *subdir = (TObjString*)nextsubdir() ) {
// 	temp = "Histograms/mc/";
// 	temp.Append(period);
// 	temp.Append("/");
// 	temp.Append(type);
// 	temp.Append("/");
// 	temp.Append(subdir->GetString());
// 	temp.Append("/");
// 	temp.Append(histogramname);
// 	TH1D* histo = (TH1D*)file->Get(temp);
// 	if ( histo != 0 ) {
// 	  histolist->Add(histo);
// 	  histodirlist->Add(new TObjString(temp));
// 	  histonum += 1;
// 	}
//       }
//     }
//   }

//   if ( histonum == 0 ) {
//     if ( localdebug ) {
//       cout << "histogram type " << type << " period " << period << " name " << histogramname << " not available" <<  endl;
//     }
//     return kFALSE;
//   }

//   // check for histogram compatibility
//   if ( !this->CheckHistoCompat(histolist) ) {
//     cout << "Histograms are not compatible" << endl;
//     return kFALSE;
//   }
  
//   if ( localdebug ) {
//     cout << "number of histograms: " << histonum << endl;
//     TIter temp(histolist);
//     while (TH1D* temphist = (TH1D*)temp() ) 
//       cout << "histogram-name: " << temphist->GetName() << " histogram-title: " << temphist->GetTitle() << endl;
//   }

//   TString dirname = this->SameDirectory(histonum, histodirlist);

//   if ( dirname.Contains(gInclude->StripLastDir(histogramname)) ) {
//     dirname.ReplaceAll(gInclude->StripLastDir(histogramname),"");
//     dirname = gInclude->StripLastDir(dirname);
//     dirname = gInclude->StripLastDir(dirname);
//   }
//   if ( !dirname.EndsWith("/") )
//     dirname.Append("/");
//   dirname.Append("merged/");
//   if ( !dirname.EndsWith("/") )
//     dirname.Append("/");
//   dirname.Append(gInclude->StripLastDir(histogramname));

//   TDirectory *directory = gInclude->MkdirRecursiveOld(file,dirname);
//   directory->cd();

//   TString mergedname = histoname;
//   TString mergedtitle = histotitle;

//   if ( mergedname.Length() == 0 ) {
//     mergedname = gInclude->StripFirstDir(histogramname);
//     mergedtitle = ((TH1D*)histolist->First())->GetTitle();
   
//     if ( type.Contains(",") ) {
//       if ( option.Contains("DATA") ) {
// 	TString tempidentifier = "";
// 	TIter nexttype(typelist);
// 	while ( TObjString *looptype = (TObjString*)nexttype() ) {
// 	  tempidentifier.Append(looptype->GetString());
// 	  tempidentifier.Append("-");
// 	}
// 	if ( tempidentifier.EndsWith("-") )
// 	  tempidentifier.Remove(tempidentifier.Length()-1,1);
	
// 	// special treatment for special subdirectories for 03p_XX
// 	tempidentifier.ReplaceAll("03p_7a","03p");
// 	tempidentifier.ReplaceAll("03p_8a","03p");
// 	tempidentifier.ReplaceAll("03p_9b","03p");

// 	mergedname.Append("_");
// 	mergedname.Append(tempidentifier);
// 	TIter nexttype2(typelist);
// 	while ( TObjString *looptype2 = (TObjString*)nexttype2() ) {

// 	  if ( mergedtitle.Contains(looptype2->GetString()) ) {
// 	    mergedtitle.ReplaceAll(looptype2->GetString(),tempidentifier);
// 	    break;
// 	  }
// 	}
//       } else {
// 	mergedtitle.Append(" for");
// 	// append to name the different comma separated types
// 	TIter nexttype(typelist);
// 	while ( TObjString *looptype = (TObjString*)nexttype() ) {
// 	  mergedname.Append("_");
// 	  mergedname.Append(looptype->GetString());
// 	  mergedtitle.Append(" ");
// 	  mergedtitle.Append(looptype->GetString());
// 	}

// 	// clean types in title
// 	TIter nexttype2(fTypes);
// 	while ( TObjString *looptype = (TObjString*)nexttype2() ) {
// 	  TString temp = looptype->GetString();
// 	  temp.Prepend("/");
// 	  mergedtitle.ReplaceAll(temp,"");
// 	}
//       }
//     } else {
//       if ( option.Contains("DATA") ) {
// 	TIter nextperiod(fPeriods);
// 	while ( TObjString *period = (TObjString*)nextperiod() ) {
// 	  mergedtitle.ReplaceAll(period->GetString(),"");
// 	}
// 	mergedtitle.ReplaceAll("data/-","");
// 	mergedtitle.ReplaceAll("data/","");
// 	mergedtitle.Prepend(compperiod);
// 	mergedtitle.Prepend("data/");
//       } else {
// 	// clean subdirectories in title
// 	TIter nextsubdir2(fSubdirs);
// 	while ( TObjString *dir = (TObjString*)nextsubdir2() ) {
// 	  TString temp = dir->GetString();
// 	  temp.Prepend("/");
// 	  mergedtitle.ReplaceAll(temp,"");
// 	}
//       }
//     }
//   }
  
//   TH1D* merged = new TH1D(*((TH1D*)histolist->First()));
//   merged->Reset();
//   merged->SetName(mergedname);
//   merged->SetTitle(mergedtitle);
//   merged->SetXTitle(((TH1D*)histolist->First())->GetXaxis()->GetTitle());
//   merged->SetYTitle(((TH1D*)histolist->First())->GetYaxis()->GetTitle());
//   merged->Sumw2();

//   // global scale
//   Double_t globalscale = GetGlobalScale(file,period,"");

//   TIter nexthisto(histolist);

//   while ( TH1D* histo = (TH1D*)nexthisto() ) {
//     if ( (globalscale <= 0.0) || option.Contains("UNWEIGHTED") ) {
//       merged->Add(histo);
//     } else {
//       if ( localdebug ) {
// 	cout << "globalscale: " << globalscale << endl;
// 	cout << "lumi: " << gInclude->GetLumi(file,histo->GetTitle()) << endl;
//       }
//       merged->Add(histo,globalscale/gInclude->GetLumi(file,histo->GetTitle()));
//     }
//   }

//   merged->Write("",kOverwrite);
//   file->Save();
//   file->ReadKeys();

//   histodirlist->Delete();
//   delete histodirlist;
//   histolist->Delete();
//   delete histolist;
//   typelist->Delete();
//   delete typelist;

//   if ( localdebug ) {
//     cout << "end of addhistos()" << endl;
//   }

//   return kTRUE;

// }

// //_____________________________________________________________

// Bool_t GHistogrammer::AddHistos2D(TFile *file, TString type, TString period, TString histogramname, TString histoname, TString histotitle, TString option) {
//   //
//   // merge histograms to histogram in smallest same directory + merged directory in file
//   if ( gDebug==-1 ) cout << endl << "GHistogrammer::AddHistos called" << endl << endl;

//   option.ToUpper();

//   TList *histolist = new TList();
//   TList *histodirlist = new TList();
//   TList *typelist = new TList();
//   Int_t histonum = 0;

//   // string to remember the complete period of valid data for stage 3
//   TString compperiod = "";

//   // check if type has "," inside, if yes, merge already merged histos, if not, merge subdirs in type
//   if ( type.Contains(",") ) {

//     TString temptype = type;

//     char first;
//     TString temp = "";
//     // separate entries in types
//     while ( (first = temptype(0)) ) {
//       // remove first
//       temptype.Remove(0,1);
//       // append to temp or break in case of comma
//       if ( first == 44 ) {
// 	typelist->Add(new TObjString(temp));
// 	temp = "";
//       } else {
//         temp.Append(first);
//       }
//     }
//     if ( temp.Length() != 0 ) {
//       typelist->Add(new TObjString(temp));
//     }
    
//     // fill histo list
//     TIter nexttype(typelist);
//     temp = "";
//     while ( TObjString *looptype = (TObjString*)nexttype() ) {
//       if ( option.Contains("DATA") ) {
// 	temp = "Histograms/data/";
// 	temp.Append(looptype->GetString());
// 	temp.Append("/");
// 	temp.Append(histogramname);
//       } else {
// 	temp = "Histograms/mc/";
// 	temp.Append(period);
// 	temp.Append("/");
// 	temp.Append(looptype->GetString());
// 	temp.Append("/merged/");
// 	temp.Append(histogramname);
//       }
//       TH1D* histo = (TH1D*)file->Get(temp);
//       if ( histo != 0 ) {
// 	histolist->Add(histo);
// 	histodirlist->Add(new TObjString(temp));
// 	histonum += 1;
//       }
//     }
//   } else {

//     // fill histo list
//     if ( option.Contains("DATA") ) {
//       TIter nextperiod(fPeriods);
//       TString temp = "";
//       TString compperiodstart = "";
//       TString compperiodend = "";
//       Bool_t first = kTRUE;
//       while ( TObjString *period = (TObjString*)nextperiod() ) {
// 	temp = "Histograms/data/merged/";
// 	temp.Append(histogramname);
// 	temp.Append("_");
// 	temp.Append(period->GetString());
// 	TH1D* histo = (TH1D*)file->Get(temp);
// 	if ( histo != 0 ) {
// 	  histolist->Add(histo);
// 	  histodirlist->Add(new TObjString(temp));
// 	  histonum += 1;
// 	  if ( first ) {
// 	    compperiodstart = period->GetString();
// 	    first = kFALSE;
// 	  }
// 	  compperiodend = period->GetString();
// 	}
//       }
//       compperiodstart.Remove(3,compperiodstart.Length()-3);
//       compperiodend.Remove(0,4);
//       compperiod = compperiodstart;
//       compperiod.Append("-");
//       compperiod.Append(compperiodend);
//     } else {
//       TIter nextsubdir(fSubdirs);
//       TString temp = "";
//       while ( TObjString *subdir = (TObjString*)nextsubdir() ) {
// 	temp = "Histograms/mc/";
// 	temp.Append(period);
// 	temp.Append("/");
// 	temp.Append(type);
// 	temp.Append("/");
// 	temp.Append(subdir->GetString());
// 	temp.Append("/");
// 	temp.Append(histogramname);
// 	TH1D* histo = (TH1D*)file->Get(temp);
// 	if ( histo != 0 ) {
// 	  histolist->Add(histo);
// 	  histodirlist->Add(new TObjString(temp));
// 	  histonum += 1;
// 	}
//       }
//     }

//   }

//   if ( histonum == 0 )
//     return kFALSE;

//   // check for histogram compatibility
//   if ( !this->CheckHistoCompat2D(histolist) ) {
//     cout << "Histograms are not compatible" << endl;
//     return kFALSE;
//   }
  
//   TString dirname = this->SameDirectory(histonum, histodirlist);
//   if ( dirname.Contains(gInclude->StripLastDir(histogramname)) ) {
//     dirname.ReplaceAll(gInclude->StripLastDir(histogramname),"");
//     dirname = gInclude->StripLastDir(dirname);
//     dirname = gInclude->StripLastDir(dirname);
//   }
//   TString basedirname = dirname;
//   if ( !dirname.EndsWith("/") )
//     dirname.Append("/");
//   dirname.Append("merged/");
//   if ( !dirname.EndsWith("/") )
//     dirname.Append("/");
//   dirname.Append(gInclude->StripLastDir(histogramname));

//   TDirectory *directory = gInclude->MkdirRecursiveOld(file,dirname);
//   directory->cd();

//   TString mergedname = histoname;
//   TString mergedtitle = histotitle;

//   if ( mergedname.Length() == 0 ) {
//     mergedname = gInclude->StripFirstDir(histogramname);
//     mergedtitle = ((TH2D*)histolist->First())->GetTitle();
   
//     if ( type.Contains(",") ) {
//       if ( option.Contains("DATA") ) {
// 	TString tempidentifier = "";
// 	TIter nexttype(typelist);
// 	while ( TObjString *looptype = (TObjString*)nexttype() ) {
// 	  tempidentifier.Append(looptype->GetString());
// 	  tempidentifier.Append("-");
// 	}
// 	if ( tempidentifier.EndsWith("-") )
// 	  tempidentifier.Remove(tempidentifier.Length()-1,1);

// 	mergedname.Append("_");
// 	mergedname.Append(tempidentifier);
// 	TIter nexttype2(typelist);
// 	while ( TObjString *looptype2 = (TObjString*)nexttype2() ) {

// 	  if ( mergedtitle.Contains(looptype2->GetString()) ) {
// 	    mergedtitle.ReplaceAll(looptype2->GetString(),tempidentifier);
// 	    break;
// 	  }
// 	}
//       } else {
// 	mergedtitle.Append(" for");
// 	// append to name the different comma separated types
// 	TIter nexttype(typelist);
// 	while ( TObjString *looptype = (TObjString*)nexttype() ) {
// 	  mergedname.Append("_");
// 	  mergedname.Append(looptype->GetString());
// 	  mergedtitle.Append(" ");
// 	  mergedtitle.Append(looptype->GetString());
// 	}

// 	// clean types in title
// 	TIter nexttype2(fTypes);
// 	while ( TObjString *looptype = (TObjString*)nexttype2() ) {
// 	  TString temp = looptype->GetString();
// 	  temp.Prepend("/");
// 	  mergedtitle.ReplaceAll(temp,"");
// 	}
//       }
//     } else {
//       if ( option.Contains("DATA") ) {
// 	TIter nextperiod(fPeriods);
// 	while ( TObjString *period = (TObjString*)nextperiod() ) {
// 	  mergedtitle.ReplaceAll(period->GetString(),"");
// 	}
// 	mergedtitle.ReplaceAll("data/-","");
// 	mergedtitle.ReplaceAll("data/","");
// 	mergedtitle.Prepend(compperiod);
// 	mergedtitle.Prepend("data/");
//       } else {
// 	// clean subdirectories in title
// 	TIter nextsubdir2(fSubdirs);
// 	while ( TObjString *dir = (TObjString*)nextsubdir2() ) {
// 	  TString temp = dir->GetString();
// 	  temp.Prepend("/");
// 	  mergedtitle.ReplaceAll(temp,"");
// 	}
//       }
//     }
//   }
  
//   TH2D* merged = new TH2D(*((TH2D*)histolist->First()));
//   merged->Reset();
//   merged->SetName(mergedname);
//   merged->SetTitle(mergedtitle);
//   merged->SetXTitle(((TH2D*)histolist->First())->GetXaxis()->GetTitle());
//   merged->SetYTitle(((TH2D*)histolist->First())->GetYaxis()->GetTitle());
//   merged->SetZTitle(((TH2D*)histolist->First())->GetZaxis()->GetTitle());
//   merged->Sumw2();

//   // global scale
//   Double_t globalscale = GetGlobalScale(file,period,"");

//   TIter nexthisto(histolist);

//   while ( TH2D* histo = (TH2D*)nexthisto() ) {
//     if ( (globalscale <= 0.0) || option.Contains("UNWEIGHTED") ) {
//       merged->Add(histo);
//     } else {
//       merged->Add(histo,globalscale/gInclude->GetLumi(file,histo->GetTitle()));
//     }
//   }

//   merged->Write("",kOverwrite);
//   file->Save();
//   file->ReadKeys();

//   histodirlist->Delete();
//   delete histodirlist;
//   histolist->Delete();
//   delete histolist;
//   typelist->Delete();
//   delete typelist;

//   return kTRUE;

// }

//_____________________________________________________________

TString GHistogrammer::SameDirectory(Int_t num, TString *array) {
  //
  // return smallest equal directory
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::SameDirectory(Int_t, TString *) called" << endl << endl;

  // count number of directories in array
  Int_t length[num];
  Int_t smallest = 99;

  for ( Int_t i = 0; i < num; i++ ) {
    length[i] = array[i].CountChar(47);
    if ( length[i] < smallest )
      smallest = length[i];
  }

  // strip histoname from array
  for ( Int_t i = 0; i < num; i++ ) {
    array[i] = gInclude->StripLastDir(array[i]);
  }

  // strip all to the same length
  for ( Int_t i = 0; i < num; i++ ) {
    for ( Int_t j = 0; j < (length[i]-smallest); j++ ) {
      array[i] = gInclude->StripLastDir(array[i]);
    }
  }

  Bool_t same = kFALSE;

  while ( !same ) {
    // check if the same
    same = kTRUE;
    for ( Int_t i = 0; i < num-1; i++ ) {
      if ( !array[i].Contains(array[i+1].Data()) )
        same = kFALSE;
    }
    // strip last dir if not the same
    if ( !same) {
      for ( Int_t i = 0; i < num; i++ ) {
        array[i] = gInclude->StripLastDir(array[i]);
      }
    }

  }

  return array[0];
}

//_____________________________________________________________

TString GHistogrammer::SameDirectory(Int_t histonum, TList *histodirlist) {
  //
  // return smallest equal directory
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::SameDirectory(Int_t, TList) called" << endl << endl;

  // count number of directories in array
  Int_t length[histonum];
  Int_t smallest = 99;

  TIter next(histodirlist);
  Int_t counter = 0;
  while (TObjString *dir = (TObjString*)next() ) {
    length[counter] = dir->GetString().CountChar(47);
    if ( length[counter] < smallest )
      smallest = length[counter];
    ++counter;
    // strip histoname from dir
    dir->SetString(gInclude->StripLastDir(dir->GetString()));
  }

  // strip all to the same length
  TIter next2(histodirlist);
  counter = 0;
  while (TObjString *dir = (TObjString*)next2() ) {
    for ( Int_t j = 0; j < (length[counter]-smallest); j++ ) {
      dir->SetString(gInclude->StripLastDir(dir->GetString()));
    }
  }

  Bool_t same = kFALSE;

  while ( !same ) {
    // check if the same
    same = kTRUE;
    TIter next1(histodirlist);
    TIter next2(histodirlist);
    while (TObjString *dir1 = (TObjString*)next1() ) {
      while (TObjString *dir2 = (TObjString*)next2() ) {
	if ( !dir1->GetString().Contains(dir2->GetString()) ) {
	  same = kFALSE;
	}
      }
    }
    // strip last dir if not the same
    if ( !same) {
      TIter next(histodirlist);
      while (TObjString *dir = (TObjString*)next() ) {
	dir->SetString(gInclude->StripLastDir(dir->GetString()));
      }
    }

  }

  return ((TObjString*)histodirlist->First())->GetString();
}

//_____________________________________________________________

Bool_t GHistogrammer::MergeHistogramsStage1(TFile *file, TString histogramname, TString option) {
  //
  // merge histograms
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::MergeHistogramsStage1 called" << endl << endl;

  cout << "GHistogrammer: MergeHistograms Stage 1 for histogram " << histogramname << endl;

  MergeMCHistogramsStage1(file,histogramname,option);

  MergeDataHistogramsStage1(file,histogramname,option);

  return kTRUE;
}

//_____________________________________________________________

Bool_t GHistogrammer::CopyHistogramsStage1(TFile *file, TString histogramname, TString option) {
  //
  // copy histograms
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::CopyHistogramsStage1 called" << endl << endl;

  cout << "GHistogrammer: CopyHistograms Stage 1 for histogram " << histogramname << endl;

  CopyMCHistogramsStage1(file,histogramname,option);

  return kTRUE;
}

//_____________________________________________________________

Bool_t GHistogrammer::MergeHistogramsStage2(TFile *file, TString histogramname, TString option) {
  //
  // merge histograms
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::MergeHistogramsStage2 called" << endl << endl;

  cout << "GHistogrammer: MergeHistograms Stage 2 for histogram " << histogramname << endl;

  MergeMCHistogramsStage2(file,histogramname,option);

  return kTRUE;
}

//_____________________________________________________________

Bool_t GHistogrammer::MergeHistogramsStage3(TFile *file, TString histogramname, TString option) {
  //
  // merge histograms
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::MergeHistogramsStage3 called" << endl << endl;

  cout << "GHistogrammer: MergeHistograms Stage 3 for histogram " << histogramname << endl;

  MergeMCHistogramsStage3(file,histogramname,option);

  MergeDataHistogramsStage3(file,histogramname,option);

  return kTRUE;
}

//_____________________________________________________________

Bool_t GHistogrammer::CopyHistogramsStage3(TFile *file, TString histogramname, TString option) {
  //
  // copy histograms
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::CopyHistogramsStage3 called" << endl << endl;

  cout << "GHistogrammer: CopyHistograms Stage 3 for histogram " << histogramname << endl;

  CopyMCHistogramsStage3(file,histogramname,option);

  return kTRUE;
}

//_____________________________________________________________

Bool_t GHistogrammer::MergeHistogramsStage4(TFile *file, TString histogramname, TString option) {
  //
  // merge histograms
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::MergeHistogramsStage4 called" << endl << endl;

  cout << "GHistogrammer: MergeHistograms Stage 4 for histogram " << histogramname << endl;

  MergeMCHistogramsStage4(file,histogramname,option);

  return kTRUE;
}

//_____________________________________________________________

Bool_t GHistogrammer::MergeHistograms2DStage1(TFile *file, TString histogramname, TString option) {
  //
  // merge 2D histograms
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::MergeHistograms2DStage1 called" << endl << endl;

  cout << "GHistogrammer: MergeHistograms 2D Stage 1 for histogram " << histogramname << endl;

  MergeMCHistograms2DStage1(file,histogramname,option);

  MergeDataHistograms2DStage1(file,histogramname,option);

  return kTRUE;
}

//_____________________________________________________________

Bool_t GHistogrammer::MergeHistograms2DStage2(TFile *file, TString histogramname, TString option) {
  //
  // merge histograms
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::MergeHistograms2DStage2 called" << endl << endl;

  cout << "GHistogrammer: MergeHistograms 2D Stage 2 for histogram " << histogramname << endl;

  MergeMCHistograms2DStage2(file,histogramname,option);

  return kTRUE;
}

//_____________________________________________________________

Bool_t GHistogrammer::MergeHistograms2DStage3(TFile *file, TString histogramname, TString option) {
  //
  // merge histograms
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::MergeHistograms2DStage3 called" << endl << endl;

  cout << "GHistogrammer: MergeHistograms 2D Stage 3 for histogram " << histogramname << endl;

  MergeMCHistograms2DStage3(file,histogramname,option);

  MergeDataHistograms2DStage3(file,histogramname,option);

  return kTRUE;
}


//_____________________________________________________________

Bool_t GHistogrammer::MergeHistograms2DStage4(TFile *file, TString histogramname, TString option) {
  //
  // merge histograms
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::MergeHistograms2DStage4 called" << endl << endl;

  cout << "GHistogrammer: MergeHistograms 2D Stage 4 for histogram " << histogramname << endl;

  MergeMCHistograms2DStage4(file,histogramname,option);

  return kTRUE;
}

//_____________________________________________________________

Bool_t GHistogrammer::MakeHistogramProjection(TFile *file, TString histogramname, TString option) {
  //
  // make Projections 
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::MakeHistogramsProjection called" << endl << endl;

  TString temp = "";

  TIter nextperiod(fPeriods);

  while ( TObjString *period = (TObjString*)nextperiod() ) {
    TIter nexttype(fTypes);
    while ( TObjString *type = (TObjString*)nexttype() ) {
      TIter nextsubdir(fSubdirs);
      while ( TObjString *subdir = (TObjString*)nextsubdir() ) {
	temp = "Histograms/mc/";
	temp.Append(period->GetString());
	temp.Append("/");
	temp.Append(type->GetString());
	temp.Append("/");
	temp.Append(subdir->GetString());
	temp.Append("/");
	TString dir = temp;
	
	dir.Append( gInclude->StripLastDir(histogramname));
	dir.Append("/");
	temp.Append(histogramname);

	if ( file->Get(temp) != 0 ) {
	  TH2D *dummy = (TH2D*)file->Get(temp);
	  TString newtitle = "";
	  newtitle.Append(dummy->GetTitle());
	  newtitle.Append("_Proj_X");
	  TString newname = dummy->GetName();
	  newname.Append("_Proj_X");
	  
	  //x Projection
	  
	  ProjectionFactory(file,dir,dummy,newname,newtitle,1,dummy->GetXaxis()->GetTitle(),"Entries");

	  newname.ReplaceAll("Proj_X","");
	  newname.Append("Proj_Y");
	  newtitle.ReplaceAll("Proj_X","");
	  newtitle.Append("Proj_Y");
	  // y Projection
	  ProjectionFactory(file,dir,dummy,newname,newtitle,2,dummy->GetYaxis()->GetTitle(),"Entries");
	  
	delete dummy;
	}
      }
    }
  }
  
  return kTRUE;
}
//_____________________________________________________________

Bool_t GHistogrammer::MergeMCHistogramsStage1(TFile *file, TString histogramname, TString option) {
  //
  // merge histograms
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::MergeMCHistogramsStage1 called" << endl << endl;

  TString temp = "";

  TIter nextperiod(fPeriods);

  while ( TObjString *period = (TObjString*)nextperiod() ) {
    TIter nexttype(fTypes);
    while ( TObjString *type = (TObjString*)nexttype() ) {
//       temp = "Histograms/mc/";
//       temp.Append(period->GetString());
//       temp.Append("/");
//       temp.Append(type->GetString());
//       if ( file->Get(temp) != 0 ) {
	AddHistosMCStage1(file,type->GetString(),period->GetString(),histogramname,option);
//       }
    }
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GHistogrammer::CopyMCHistogramsStage1(TFile *file, TString histogramname, TString option) {
  //
  // copy histograms
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::CopyMCHistogramsStage1 called" << endl << endl;

  TString temp = "";

  TIter nextperiod(fPeriods);

  while ( TObjString *period = (TObjString*)nextperiod() ) {
    TIter nexttype(fTypes);
    while ( TObjString *type = (TObjString*)nexttype() ) {
      CopyHistosMCStage1(file,type->GetString(),period->GetString(),histogramname,option);
    }
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GHistogrammer::MergeMCHistogramsStage2(TFile *file, TString histogramname, TString option) {
  //
  // merge histograms
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::MergeMCHistogramsStage2 called" << endl << endl;

  TString temp = "";

  TIter nextperiod(fPeriods);

  while ( TObjString *period = (TObjString*)nextperiod() ) {

    // add more iterations if number of types grows

    TIter nexttype1stage21(fTypes);
    while ( TObjString *type1 = (TObjString*)nexttype1stage21() ) {
      TIter nexttype2stage21(nexttype1stage21);
      while ( TObjString *type2 = (TObjString*)nexttype2stage21() ) {
	TString temp = type1->GetString();
	temp.Append(",");
	temp.Append(type2->GetString());
	TString tempoption = option;
	tempoption.Append(",UNWEIGHTED");
 	AddHistosMCStage2(file,temp,period->GetString(),histogramname,tempoption);
      }
    }

    TIter nexttype1stage22(fTypes);
    while ( TObjString *type1 = (TObjString*)nexttype1stage22() ) {
      TIter nexttype2stage22(nexttype1stage22);
      while ( TObjString *type2 = (TObjString*)nexttype2stage22() ) {
	TIter nexttype3stage22(nexttype2stage22);
	while ( TObjString *type3 = (TObjString*)nexttype3stage22() ) {
	  TString temp = type1->GetString();
	  temp.Append(",");
	  temp.Append(type2->GetString());
	  temp.Append(",");
	  temp.Append(type3->GetString());
	  TString tempoption = option;
	  tempoption.Append(",UNWEIGHTED");
	  AddHistosMCStage2(file,temp,period->GetString(),histogramname,tempoption);
	}
      }
    }

    TIter nexttype1stage23(fTypes);
    while ( TObjString *type1 = (TObjString*)nexttype1stage23() ) {
      TIter nexttype2stage23(nexttype1stage23);
      while ( TObjString *type2 = (TObjString*)nexttype2stage23() ) {
	TIter nexttype3stage23(nexttype2stage23);
	while ( TObjString *type3 = (TObjString*)nexttype3stage23() ) {
	  TIter nexttype4stage23(nexttype3stage23);
	  while ( TObjString *type4 = (TObjString*)nexttype4stage23() ) {
	    TString temp = type1->GetString();
	    temp.Append(",");
	    temp.Append(type2->GetString());
	    temp.Append(",");
	    temp.Append(type3->GetString());
	    temp.Append(",");
	    temp.Append(type4->GetString());
	    TString tempoption = option;
	    tempoption.Append(",UNWEIGHTED");
	    AddHistosMCStage2(file,temp,period->GetString(),histogramname,tempoption);
	  }
	}
      }
    }

  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GHistogrammer::MergeMCHistogramsStage3(TFile *file, TString histogramname, TString option) {
  //
  // merge histograms
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::MergeMCHistogramsStage3 called" << endl << endl;

  
  TIter nexttype(fTypes);
  while ( TObjString *type = (TObjString*)nexttype() ) {
    AddHistosMCStage3(file,type->GetString(),histogramname,option);
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GHistogrammer::CopyMCHistogramsStage3(TFile *file, TString histogramname, TString option) {
  //
  // copy histograms
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::CopyMCHistogramsStage3 called" << endl << endl;

  
  TIter nexttype(fTypes);
  while ( TObjString *type = (TObjString*)nexttype() ) {
    CopyHistosMCStage3(file,type->GetString(),histogramname,option);
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GHistogrammer::MergeMCHistogramsStage4(TFile *file, TString histogramname, TString option) {
  //
  // merge histograms
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::MergeMCHistogramsStage4 called" << endl << endl;

  TString temp = "";

  // add more iterations if number of types grows

  TIter nexttype1stage41(fTypes);
  while ( TObjString *type1 = (TObjString*)nexttype1stage41() ) {
    TIter nexttype2stage41(nexttype1stage41);
    while ( TObjString *type2 = (TObjString*)nexttype2stage41() ) {
      TString temp = type1->GetString();
      temp.Append(",");
      temp.Append(type2->GetString());
      TString tempoption = option;
      tempoption.Append(",UNWEIGHTED");
      AddHistosMCStage4(file,temp,histogramname,tempoption);
    }
  }

  TIter nexttype1stage42(fTypes);
  while ( TObjString *type1 = (TObjString*)nexttype1stage42() ) {
    TIter nexttype2stage42(nexttype1stage42);
    while ( TObjString *type2 = (TObjString*)nexttype2stage42() ) {
      TIter nexttype3stage42(nexttype2stage42);
      while ( TObjString *type3 = (TObjString*)nexttype3stage42() ) {
	TString temp = type1->GetString();
	temp.Append(",");
	temp.Append(type2->GetString());
	temp.Append(",");
	temp.Append(type3->GetString());
	TString tempoption = option;
	tempoption.Append(",UNWEIGHTED");
	AddHistosMCStage4(file,temp,histogramname,tempoption);
      }
    }
  }

  TIter nexttype1stage43(fTypes);
  while ( TObjString *type1 = (TObjString*)nexttype1stage43() ) {
    TIter nexttype2stage43(nexttype1stage43);
    while ( TObjString *type2 = (TObjString*)nexttype2stage43() ) {
      TIter nexttype3stage43(nexttype2stage43);
      while ( TObjString *type3 = (TObjString*)nexttype3stage43() ) {
	TIter nexttype4stage43(nexttype3stage43);
	while ( TObjString *type4 = (TObjString*)nexttype4stage43() ) {
	  TString temp = type1->GetString();
	  temp.Append(",");
	  temp.Append(type2->GetString());
	  temp.Append(",");
	  temp.Append(type3->GetString());
	  temp.Append(",");
	  temp.Append(type4->GetString());
	  TString tempoption = option;
	  tempoption.Append(",UNWEIGHTED");
	  AddHistosMCStage4(file,temp,histogramname,tempoption);
	}
      }
    }
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GHistogrammer::MergeMCHistograms2DStage1(TFile *file, TString histogramname, TString option) {
  //
  // merge 2D histograms
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::MergeMCHistograms2DStage1 called" << endl << endl;

  TString temp = "";

  TIter nextperiod(fPeriods);

  while ( TObjString *period = (TObjString*)nextperiod() ) {
    TIter nexttype(fTypes);
    while ( TObjString *type = (TObjString*)nexttype() ) {
//       temp = "Histograms/mc/";
//       temp.Append(period->GetString());
//       temp.Append("/");
//       temp.Append(type->GetString());
//       if ( file->Get(temp) != 0 ) {
	AddHistos2DMCStage1(file,type->GetString(),period->GetString(),histogramname,option);
//       }
    }
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GHistogrammer::MergeMCHistograms2DStage2(TFile *file, TString histogramname, TString option) {
  //
  // merge histograms
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::MergeMCHistograms2DStage2 called" << endl << endl;

  TString temp = "";

  TIter nextperiod(fPeriods);

  while ( TObjString *period = (TObjString*)nextperiod() ) {

    // add more iterations if number of types grows

    TIter nexttype1stage21(fTypes);
    while ( TObjString *type1 = (TObjString*)nexttype1stage21() ) {
      TIter nexttype2stage21(nexttype1stage21);
      while ( TObjString *type2 = (TObjString*)nexttype2stage21() ) {
	TString temp = type1->GetString();
	temp.Append(",");
	temp.Append(type2->GetString());
	TString tempoption = option;
	tempoption.Append(",UNWEIGHTED");
	AddHistos2DMCStage2(file,temp,period->GetString(),histogramname,tempoption);
      }
    }

    TIter nexttype1stage22(fTypes);
    while ( TObjString *type1 = (TObjString*)nexttype1stage22() ) {
      TIter nexttype2stage22(nexttype1stage22);
      while ( TObjString *type2 = (TObjString*)nexttype2stage22() ) {
	TIter nexttype3stage22(nexttype2stage22);
	while ( TObjString *type3 = (TObjString*)nexttype3stage22() ) {
	  TString temp = type1->GetString();
	  temp.Append(",");
	  temp.Append(type2->GetString());
	  temp.Append(",");
	  temp.Append(type3->GetString());
	  TString tempoption = option;
	  tempoption.Append(",UNWEIGHTED");
	  AddHistos2DMCStage2(file,temp,period->GetString(),histogramname,tempoption);
	}
      }
    }

    TIter nexttype1stage23(fTypes);
    while ( TObjString *type1 = (TObjString*)nexttype1stage23() ) {
      TIter nexttype2stage23(nexttype1stage23);
      while ( TObjString *type2 = (TObjString*)nexttype2stage23() ) {
	TIter nexttype3stage23(nexttype2stage23);
	while ( TObjString *type3 = (TObjString*)nexttype3stage23() ) {
	  TIter nexttype4stage23(nexttype3stage23);
	  while ( TObjString *type4 = (TObjString*)nexttype4stage23() ) {
	    TString temp = type1->GetString();
	    temp.Append(",");
	    temp.Append(type2->GetString());
	    temp.Append(",");
	    temp.Append(type3->GetString());
	    temp.Append(",");
	    temp.Append(type4->GetString());
	    TString tempoption = option;
	    tempoption.Append(",UNWEIGHTED");
	    AddHistos2DMCStage2(file,temp,period->GetString(),histogramname,tempoption);
	  }
	}
      }
    }
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GHistogrammer::MergeMCHistograms2DStage3(TFile *file, TString histogramname, TString option) {
  //
  // merge histograms
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::MergeMCHistograms2DStage3 called" << endl << endl;

  TIter nexttype(fTypes);
  while ( TObjString *type = (TObjString*)nexttype() ) {
    AddHistos2DMCStage3(file,type->GetString(),histogramname,option);
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GHistogrammer::MergeMCHistograms2DStage4(TFile *file, TString histogramname, TString option) {
  //
  // merge histograms
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::MergeMCHistograms2DStage4 called" << endl << endl;

  TString temp = "";

  // add more iterations if number of types grows

  TIter nexttype1stage41(fTypes);
  while ( TObjString *type1 = (TObjString*)nexttype1stage41() ) {
    TIter nexttype2stage41(nexttype1stage41);
    while ( TObjString *type2 = (TObjString*)nexttype2stage41() ) {
      TString temp = type1->GetString();
      temp.Append(",");
      temp.Append(type2->GetString());
      TString tempoption = option;
      tempoption.Append(",UNWEIGHTED");
      AddHistos2DMCStage4(file,temp,histogramname,tempoption);
    }
  }

  TIter nexttype1stage42(fTypes);
  while ( TObjString *type1 = (TObjString*)nexttype1stage42() ) {
    TIter nexttype2stage42(nexttype1stage42);
    while ( TObjString *type2 = (TObjString*)nexttype2stage42() ) {
      TIter nexttype3stage42(nexttype2stage42);
      while ( TObjString *type3 = (TObjString*)nexttype3stage42() ) {
	TString temp = type1->GetString();
	temp.Append(",");
	temp.Append(type2->GetString());
	temp.Append(",");
	temp.Append(type3->GetString());
	TString tempoption = option;
	tempoption.Append(",UNWEIGHTED");
	AddHistos2DMCStage4(file,temp,histogramname,tempoption);
      }
    }
  }
  
  TIter nexttype1stage43(fTypes);
  while ( TObjString *type1 = (TObjString*)nexttype1stage43() ) {
    TIter nexttype2stage43(nexttype1stage43);
    while ( TObjString *type2 = (TObjString*)nexttype2stage43() ) {
      TIter nexttype3stage43(nexttype2stage43);
      while ( TObjString *type3 = (TObjString*)nexttype3stage43() ) {
	TIter nexttype4stage43(nexttype3stage43);
	while ( TObjString *type4 = (TObjString*)nexttype4stage43() ) {
	  TString temp = type1->GetString();
	  temp.Append(",");
	  temp.Append(type2->GetString());
	  temp.Append(",");
	  temp.Append(type3->GetString());
	  temp.Append(",");
	  temp.Append(type4->GetString());
	  TString tempoption = option;
	  tempoption.Append(",UNWEIGHTED");
	  AddHistos2DMCStage4(file,temp,histogramname,tempoption);
	}
      }
    }
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GHistogrammer::MergeDataHistogramsStage1(TFile *file, TString histogramname, TString option) {
  //
  // merge histograms
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::MergeDataHistograms called" << endl << endl;
  
  TString temp = "";

  // merge histograms for 96p-97p
  temp = "96p,97p";
  AddHistosDataStage1(file,temp,histogramname,option);

  // merge histograms for 98e-99e
  temp = "98e,99e";
  AddHistosDataStage1(file,temp,histogramname,option);

  // merge histograms for 99p-00p
  temp = "99p,00p";
  AddHistosDataStage1(file,temp,histogramname,option);

  // new data
  Bool_t newdataprocessed = kFALSE;
  // merge histograms for 03p_7a-04p
  if ( file->Get("Histograms/data/03p_7a") && !newdataprocessed ) {
    temp = "03p_7a,04p";
    AddHistosDataStage1(file,temp,histogramname,option);
    newdataprocessed = kTRUE;
  }

  // merge histograms for 03p_8b-04p
  if ( file->Get("Histograms/data/03p_8a") && !newdataprocessed ) {
    temp = "03p_8a,04p";
    AddHistosDataStage1(file,temp,histogramname,option);
    newdataprocessed = kTRUE;
  }

  // merge histograms for 03p_9b-04p
  if ( file->Get("Histograms/data/03p_9b") && !newdataprocessed ) {
    temp = "03p_9b,04p";
    AddHistosDataStage1(file,temp,histogramname,option);
    newdataprocessed = kTRUE;
  }

  // merge histograms for 03p-04p
  if ( file->Get("Histograms/data/03p") && !newdataprocessed ) {
    temp = "03p,04p";
    AddHistosDataStage1(file,temp,histogramname,option);
    newdataprocessed = kTRUE;
  }

  // merge histograms for 05e-06e
  temp = "05e,06e";
  AddHistosDataStage1(file,temp,histogramname,option);

  // merge histograms for 06p-07p
  temp = "06p,07p";
  AddHistosDataStage1(file,temp,histogramname,option);

  return kTRUE;
}

//_____________________________________________________________

Bool_t GHistogrammer::MergeDataHistogramsStage3(TFile *file, TString histogramname, TString option) {
  //
  // merge histograms
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::MergeDataHistogramsStage3 called" << endl << endl;
  
  AddHistosDataStage3(file,histogramname,option);

  return kTRUE;
}

//_____________________________________________________________

Bool_t GHistogrammer::MergeDataHistograms2DStage1(TFile *file, TString histogramname, TString option) {
  //
  // merge 2D histograms
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::MergeDataHistograms2DStage1 called" << endl << endl;
  
  TString temp = "";
  TString tempoption = option;
  tempoption.Append("UNWEIGHTED,DATA");

  // merge histograms for 96p-97p
  temp = "96p,97p";
  AddHistos2DDataStage1(file,temp,histogramname,tempoption);

  // merge histograms for 98e-99e
  temp = "98e,99e";
  AddHistos2DDataStage1(file,temp,histogramname,tempoption);

  // merge histograms for 99p-00p
  temp = "99p,00p";
  AddHistos2DDataStage1(file,temp,histogramname,tempoption);

  // new data
  Bool_t newdataprocessed = kFALSE;
  // merge histograms for 03p_7a-04p
  if ( file->Get("Histograms/data/03p_7a") && !newdataprocessed ) {
    temp = "03p_7a,04p";
    AddHistos2DDataStage1(file,temp,histogramname,tempoption);
    newdataprocessed = kTRUE;
  }

  // merge histograms for 03p_8b-04p
  if ( file->Get("Histograms/data/03p_8a") && !newdataprocessed ) {
    temp = "03p_8a,04p";
    AddHistos2DDataStage1(file,temp,histogramname,tempoption);
    newdataprocessed = kTRUE;
  }

  // merge histograms for 03p_9b-04p
  if ( file->Get("Histograms/data/03p_9b") && !newdataprocessed ) {
    temp = "03p_9b,04p";
    AddHistos2DDataStage1(file,temp,histogramname,tempoption);
    newdataprocessed = kTRUE;
  }

  // merge histograms for 03p-04p
  if ( file->Get("Histograms/data/03p") && !newdataprocessed ) {
    temp = "03p,04p";
    AddHistos2DDataStage1(file,temp,histogramname,tempoption);
    newdataprocessed = kTRUE;
  }

  // merge histograms for 05e-06e
  temp = "05e-06e";
  AddHistos2DDataStage1(file,temp,histogramname,tempoption);

  // merge histograms for 06p-07p
  temp = "06p-07p";
  AddHistos2DDataStage1(file,temp,histogramname,tempoption);

  return kTRUE;
}

//_____________________________________________________________

Bool_t GHistogrammer::MergeDataHistograms2DStage3(TFile *file, TString histogramname, TString option) {
  //
  // merge 2D histograms
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::MergeDataHistograms2DStage3 called" << endl << endl;
  
  AddHistos2DDataStage3(file,histogramname,option);

  return kTRUE;
}

//_____________________________________________________________

Bool_t GHistogrammer::MergeMCHistogramsUnweighted(TFile *file, TString histogramname, TString histoname, TString histotitle, TString option) {
  //
  // merge histograms unweighted
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::MergeMCHistograms called" << endl << endl;

  TString temp = "";

  TIter nexttype(fTypes);
  TIter nextperiod(fTypes);

  while ( TObjString *type = (TObjString*)nexttype() ) {
    while ( TObjString *period = (TObjString*)nextperiod() ) {
      temp = "Histograms/mc/";
      temp.Append(period->GetString());
      temp.Append("/");
      temp.Append(type->GetString());
      if ( file->Get(temp) != 0 ) {
	// 	AddHistosUnweighted(file,type->GetString(),period->GetString,histogramname);
      }
    }
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GHistogrammer::MergeMCHistogramsUnweighted2D(TFile *file, TString histogramname, TString histoname, TString histotitle, TString option) {
  //
  // merge 2D histograms unweighted
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::MergeMCHistograms2D called" << endl << endl;

  TString temp = "";

  TIter nexttype(fTypes);
  TIter nextperiod(fTypes);

  while ( TObjString *type = (TObjString*)nexttype() ) {
    while ( TObjString *period = (TObjString*)nextperiod() ) {
      temp = "Histograms/mc/";
      temp.Append(period->GetString());
      temp.Append("/");
      temp.Append(type->GetString());
      if ( file->Get(temp) != 0 ) {
	// 	AddHistosUnweighted2D(file,type->GetString(),period->GetString,histogramname);
      }
    }
  }

  return kTRUE;
}

//_____________________________________________________________

TCanvas* GHistogrammer::DataMcPlot(Int_t histonumber, TH1D** histos,
				   TString name, TString title,
				   TString xaxis, TString yaxis,
				   Double_t x1ndc, Double_t y1ndc,
				   Double_t x2ndc, Double_t y2ndc,
				   Double_t leftMargin,
				   TString option) {
  //
  // make data mc plot for TH1F
  //
  // histos array: 0    = data
  //               last = combined mc
  //
  // option = normal (default) (histograms)
  //          STACKED (mc histograms to combined mc hist stacked
  //          ERRORS  (all histograms are shown as markers with their errors)
  //
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::DataMcPlot() called" << endl << endl;

  if ( histos == 0 ) {
    cout << "Problems with histos array" << endl;
    return 0;
  } else if ( histonumber > 9 ) {
    cout << "More than 9 histograms are not supported" << endl;
    return 0;
  }

  option.ToUpper();

  // set color array
  Int_t colorArray[7];
  colorArray[0]=3;
  colorArray[1]=4;
  colorArray[2]=5;
  colorArray[3]=6;
  colorArray[4]=7;
  colorArray[5]=8;
  colorArray[6]=9;


  // initialize canvas and set leftmargin
  TCanvas *canvas = new TCanvas();
  canvas->SetLeftMargin(leftMargin);
    
  TString temptitle = "data";
  // set data histogram
  TString mytitle = title;
  TString myname = name;
  //   if ( option.Contains("STACKED") ) {
  //     mytitle.Append(" stacked");
  //     myname.Append("_stacked");
  //   } else if ( option.Contains("ERRORS") ) {
  //     mytitle.Append(" errors");
  //     myname.Append("_errors");
  //   }
  histos[0]->SetTitle(mytitle.Data());
  histos[0]->SetName(myname.Data());
  histos[0]->SetXTitle(xaxis);
  histos[0]->SetYTitle(yaxis);
  histos[0]->SetMarkerColor(1);
  histos[0]->SetMarkerStyle(8);

  // set maximum of histogramm to max of data or mc combined + 50 %
  Double_t max = histos[0]->GetMaximum();
  if ( max < histos[histonumber-1]->GetMaximum() )
    max = histos[histonumber-1]->GetMaximum();
  max = 1.5*max;

  // draw data first to get the maximum and stats right
  histos[0]->SetMaximum(max);
  if ( option.Contains("NOREDRAW") )
    histos[0]->Draw("PE1");
  else
    histos[0]->Draw("P");

  // instance of THStack
  THStack *stack = 0;
  if ( option.Contains("STACKED") ) {
    stack = new THStack(myname,mytitle);
  }

  for ( Int_t i = 1; i < histonumber-1; i++ ) {
    if ( option.Contains("STACKED") ) {
      ZeroErrors(histos[i]);
      histos[i]->SetFillColor(colorArray[i-1]);
      stack->Add(histos[i]);
    } else if ( option.Contains("ERRORS") ) {
      histos[i]->SetLineColor(colorArray[i-1]);
      histos[i]->SetMarkerColor(colorArray[i-1]);
      histos[i]->SetMarkerStyle(8);
    } else {
      histos[i]->SetLineColor(colorArray[i-1]);
    }
  }

  if ( option.Contains("STACKED") ) {
    stack->Draw("Hist SAME");
  } else if ( option.Contains("ERRORS") ) {
    for ( Int_t i = 1; i < histonumber-1; i++ ) {
      histos[i]->Draw("PE1SAME");
    }
  } else {
    for ( Int_t i = 1; i < histonumber-1; i++ ) {
      histos[i]->Draw("HIST SAME");
    }
  }

  // draw combined mc hist
  if ( histonumber > 1 ) {
    if ( option.Contains("ERRORS") ) {
      histos[histonumber-1]->SetLineColor(2);
      histos[histonumber-1]->SetMarkerColor(2);
      histos[histonumber-1]->SetMarkerStyle(8);
      histos[histonumber-1]->Draw("PE1SAME");
    } else {
      histos[histonumber-1]->SetLineWidth(2);
      histos[histonumber-1]->SetLineColor(2);
      histos[histonumber-1]->Draw("HIST SAME");
    }
  }

  // draw data hist
  if ( !option.Contains("NOREDRAW") )
    histos[0]->Draw("PE1SAME");

  // legend
  TLegend *legend = new TLegend(x1ndc,y1ndc,x2ndc,y2ndc);

  // data legend entry
  legend->AddEntry(histos[0],temptitle.Data(),"P");

  // mc hist entries
  for ( Int_t i = 1; i < histonumber-1; i++ ) {
    if ( option.Contains("STACKED") ) {
      legend->AddEntry(histos[i],histos[i]->GetTitle(),"F");
    } else if ( option.Contains("ERRORS") ) {
      legend->AddEntry(histos[i],histos[i]->GetTitle(),"P");
    } else {
      legend->AddEntry(histos[i],histos[i]->GetTitle(),"L");
    }
  }

  // combined mc entry
  if ( histonumber > 1 ) {
    if ( option.Contains("ERRORS") ) {
      legend->AddEntry(histos[histonumber-1],histos[histonumber-1]->GetTitle(),"P");
    } else { 
      legend->AddEntry(histos[histonumber-1],histos[histonumber-1]->GetTitle(),"L");
    }
  }

  legend->SetBorderSize(1);
  legend->SetFillColor(0);
  legend->SetMargin(0.5);
  legend->Draw("SAME");

  return canvas;
}

//_____________________________________________________________

TCanvas* GHistogrammer::DataMcPlot(Int_t histonumber, TH1F** histos,
				   TString name, TString title,
				   TString xaxis, TString yaxis,
				   Double_t x1ndc, Double_t y1ndc,
				   Double_t x2ndc, Double_t y2ndc,
				   Double_t leftMargin,
				   TString option) {
  //
  // make data mc plot for TH1F
  //
  // histos array: 0    = data
  //               last = combined mc
  //
  // option = normal (default) (histograms)
  //          STACKED (mc histograms to combined mc hist stacked
  //          ERRORS  (all histograms are shown as markers with their errors)
  //
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::DataMcPlot() called" << endl << endl;

  if ( histos == 0 ) {
    cout << "Problems with histos array" << endl;
    return 0;
  } else if ( histonumber > 9 ) {
    cout << "More than 9 histograms are not supported" << endl;
    return 0;
  }

  option.ToUpper();

  // set color array
  Int_t colorArray[7];
  colorArray[0]=3;
  colorArray[1]=4;
  colorArray[2]=5;
  colorArray[3]=6;
  colorArray[4]=7;
  colorArray[5]=8;
  colorArray[6]=9;


  // initialize canvas and set leftmargin
  TCanvas *canvas = new TCanvas();
  canvas->SetLeftMargin(leftMargin);

  TString temptitle = "data";
  // set data histogram
  TString mytitle = title;
  TString myname = name;
  //   if ( option.Contains("STACKED") ) {
  //     mytitle.Append(" stacked");
  //     myname.Append("_stacked");
  //   } else if ( option.Contains("ERRORS") ) {
  //     mytitle.Append(" errors");
  //     myname.Append("_errors");
  //   }
  histos[0]->SetTitle(mytitle.Data());
  histos[0]->SetName(myname.Data());
  histos[0]->SetXTitle(xaxis);
  histos[0]->SetYTitle(yaxis);
  histos[0]->SetMarkerColor(1);
  histos[0]->SetMarkerStyle(8);

  // set maximum of histogramm to max of data or mc combined + 50 %
  Double_t max = histos[0]->GetMaximum();
  if ( max < histos[histonumber-1]->GetMaximum() )
    max = histos[histonumber-1]->GetMaximum();
  max = 1.5*max;

  // draw data first to get the maximum and stats right
  histos[0]->SetMaximum(max);
  if ( option.Contains("NOREDRAW") )
    histos[0]->Draw("PE1");
  else
    histos[0]->Draw("P");

  // instance of THStack
  THStack *stack = 0;
  if ( option.Contains("STACKED") ) {
    stack = new THStack(myname,mytitle);
  }

  for ( Int_t i = 1; i < histonumber-1; i++ ) {
    if ( option.Contains("STACKED") ) {
      ZeroErrors(histos[i]);
      histos[i]->SetFillColor(colorArray[i-1]);
      stack->Add(histos[i]);
    } else if ( option.Contains("ERRORS") ) {
      histos[i]->SetLineColor(colorArray[i-1]);
      histos[i]->SetMarkerColor(colorArray[i-1]);
      histos[i]->SetMarkerStyle(8);
    } else {
      histos[i]->SetLineColor(colorArray[i-1]);
    }
  }

  if ( option.Contains("STACKED") ) {
    stack->Draw("Hist SAME");
  } else if ( option.Contains("ERRORS") ) {
    for ( Int_t i = 1; i < histonumber-1; i++ ) {
      histos[i]->Draw("PE1SAME");
    }
  } else {
    for ( Int_t i = 1; i < histonumber-1; i++ ) {
      histos[i]->Draw("HIST SAME");
    }
  }

  // draw combined mc hist
  if ( histonumber > 1 ) {
    if ( option.Contains("ERRORS") ) {
      histos[histonumber-1]->SetLineColor(2);
      histos[histonumber-1]->SetMarkerColor(2);
      histos[histonumber-1]->SetMarkerStyle(8);
      histos[histonumber-1]->Draw("PE1SAME");
    } else {
      histos[histonumber-1]->SetLineWidth(2);
      histos[histonumber-1]->SetLineColor(2);
      histos[histonumber-1]->Draw("HIST SAME");
    }
  }

  // draw data hist
  if ( !option.Contains("NOREDRAW") )
    histos[0]->Draw("PE1SAME");
  
  // legend
  TLegend *legend = new TLegend(x1ndc,y1ndc,x2ndc,y2ndc);

  // data legend entry
  legend->AddEntry(histos[0],temptitle.Data(),"P");

  // mc hist entries
  for ( Int_t i = 1; i < histonumber-1; i++ ) {
    if ( option.Contains("STACKED") ) {
      legend->AddEntry(histos[i],histos[i]->GetTitle(),"F");
    } else if ( option.Contains("ERRORS") ) {
      legend->AddEntry(histos[i],histos[i]->GetTitle(),"P");
    } else {
      legend->AddEntry(histos[i],histos[i]->GetTitle(),"L");
    }
  }

  // combined mc entry
  if ( histonumber > 1 ) {
    if ( option.Contains("ERRORS") ) {
      legend->AddEntry(histos[histonumber-1],histos[histonumber-1]->GetTitle(),"P");
    } else { 
      legend->AddEntry(histos[histonumber-1],histos[histonumber-1]->GetTitle(),"L");
    }
  }

  legend->SetBorderSize(1);
  legend->SetFillColor(0);
  legend->SetMargin(0.5);
  legend->Draw("SAME");

  return canvas;
}

//_____________________________________________________________

TCanvas* GHistogrammer::DataMcPlot2(Int_t histonumber, TH1D** histos,
				    TString name, TString title,
				    TString datalegend, TString mclegend,
				    TString xaxis, TString yaxis,
				    Double_t x1ndc, Double_t y1ndc,
				    Double_t x2ndc, Double_t y2ndc,
				    Double_t leftMargin,
				    TString option) {
  //
  // make data mc plot for TH1F
  //
  // histos array: 0    = data
  //               last = combined mc
  //
  // option = normal (default) (histograms)
  //          STACKED (mc histograms to combined mc hist stacked
  //          ERRORS  (all histograms are shown as markers with their errors)
  //
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::DataMcPlot() called" << endl << endl;

  if ( histos == 0 ) {
    cout << "Problems with histos array" << endl;
    return 0;
  } else if ( histonumber > 99 ) {
    cout << "More than 2 histograms are not supported" << endl;
    return 0;
  }

  option.ToUpper();

  // initialize canvas and set leftmargin
  TCanvas *canvas = new TCanvas();
  canvas->SetLeftMargin(leftMargin);
  canvas->SetTopMargin(0.03);

  histos[0]->SetTitle("");
  histos[0]->SetName(name);
  histos[0]->SetXTitle(xaxis);
  histos[0]->SetYTitle(yaxis);
  histos[0]->SetMarkerColor(2);
  histos[0]->SetMarkerStyle(8);
  histos[0]->SetLineWidth(1);

  // set maximum of histogramm to max of data or mc combined + 50 %
  Double_t max = histos[0]->GetMaximum();
  if ( max < histos[histonumber-1]->GetMaximum() )
    max = histos[histonumber-1]->GetMaximum();
  max = 1.5*max;

  if ( max > 1000. ) {
    canvas->SetLeftMargin(0.13);
    histos[0]->GetYaxis()->SetTitleOffset(1.6);
  } else if ( max > 100. ) {
    canvas->SetLeftMargin(0.12);
    histos[0]->GetYaxis()->SetTitleOffset(1.3);
  } else if ( max > 0.5 ) {
    canvas->SetLeftMargin(0.1);
    histos[0]->GetYaxis()->SetTitleOffset(1.);
  } else if ( max > 0.5 ) {
    canvas->SetLeftMargin(0.12);
    histos[0]->GetYaxis()->SetTitleOffset(1.2);
  } else if ( max > 0.05 ) {
    canvas->SetLeftMargin(0.13);
    histos[0]->GetYaxis()->SetTitleOffset(1.5);
  } else {
    canvas->SetLeftMargin(0.14);
    histos[0]->GetYaxis()->SetTitleOffset(1.6);
  } 

  // draw data first to get the maximum and stats right
  histos[0]->SetMaximum(max);
  if ( option.Contains("NOREDRAW") )
    histos[0]->Draw("PE1");
  else
    histos[0]->Draw("P");

  TH1D *minus = PlusMinusErrorPerBin(histos[3],kFALSE);
  TH1D *plus = PlusMinusErrorPerBin(histos[3],kTRUE);

  plus->SetFillColor(5);
  plus->SetLineColor(5);
  plus->SetLineWidth(0);
  
  minus->SetFillColor(10);
  minus->SetLineColor(5);
  minus->SetLineWidth(0);

  histos[3]->SetLineColor(1);
  histos[3]->SetLineWidth(1);

  plus->Draw("HIST,SAME,][");
  minus->Draw("HIST,SAME,][");
  histos[3]->Draw("SAME,HIST");

  if ( !option.Contains("NOREDRAW") )
    histos[0]->Draw("PE1SAME");
  
  // legend
  TLegend *legend = new TLegend(x1ndc,y1ndc,x2ndc,y2ndc);

  TH1D* leg_hist= (TH1D*)histos[3]->Clone();

  leg_hist->SetFillColor(5);

  // data legend entry
  legend->AddEntry(histos[0],datalegend,"P");
  legend->AddEntry(leg_hist,mclegend,"LF");
  legend->SetBorderSize(0);
  legend->SetFillColor(10);
  legend->SetMargin(0.15);
  legend->SetTextSize(0.035);
  legend->Draw("SAME");

  canvas->RedrawAxis();

  return canvas;
}

//_____________________________________________________________

TCanvas* GHistogrammer::McPlot(Int_t histonumber, TH1D** histos,
			       TString name, TString title,
			       TString xaxis, TString yaxis,
			       Double_t x1ndc, Double_t y1ndc,
			       Double_t x2ndc, Double_t y2ndc,
			       Double_t leftMargin,
			       TString option) {
  //
  // make mc plot for TH1D
  //
  // histos array: last = combined mc
  //
  // option = normal (default) (histograms)
  //          STACKED (mc histograms to combined mc hist stacked
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::DataMcPlot() called" << endl << endl;

  if ( histos == 0 ) {
    cout << "Problems with histos array" << endl;
    return 0;
  } else if ( histonumber > 8 ) {
    cout << "More than 8 histograms are not supported" << endl;
    return 0;
  }

  option.ToUpper();

  // set color array
  Int_t colorArray[7];
  colorArray[0]=3;
  colorArray[1]=4;
  colorArray[2]=5;
  colorArray[3]=6;
  colorArray[4]=7;
  colorArray[5]=8;
  colorArray[6]=9;

  // initialize canvas and set leftmargin
  TCanvas *canvas = new TCanvas();
  canvas->SetLeftMargin(leftMargin);

  TString temptitle = histos[histonumber-1]->GetTitle();
  // set combined histogram
  TString mytitle = title;
  TString myname = name;
  if ( option.Contains("STACKED") ) {
    mytitle.Append(" stacked");
    myname.Append("_stacked");
  }
  histos[histonumber-1]->SetTitle(mytitle.Data());
  histos[histonumber-1]->SetName(myname.Data());
  histos[histonumber-1]->SetXTitle(xaxis);
  histos[histonumber-1]->SetYTitle(yaxis);

  // set maximum of histogramm to max of data or mc combined + 25 %
  Double_t max = histos[histonumber-1]->GetMaximum();
  max = 1.25*max;

  // draw data first to get the maximum and stats right
  histos[histonumber-1]->SetMaximum(max);
  histos[histonumber-1]->Draw("HIST");

  // instance of THStack
  THStack *stack = 0;
  if ( option.Contains("STACKED") ) {
    stack = new THStack(myname,mytitle);
  }	
    
  for ( Int_t i = 0; i < histonumber-1; i++ ) {
    ZeroErrors(histos[i]);
    if ( option.Contains("STACKED") ) {
      histos[i]->SetFillColor(colorArray[i-1]);
      stack->Add(histos[i]);
    } else {
      histos[i]->SetLineColor(colorArray[i-1]);
    }
  }

  if ( option.Contains("STACKED") ) {
    stack->Draw("Hist SAME");
  } else {
    for ( Int_t i = 0; i < histonumber-1; i++ ) {
      histos[i]->Draw("HIST SAME");
    }
  }

  // draw combined mc hist
  histos[histonumber-1]->SetLineWidth(2);
  histos[histonumber-1]->SetLineColor(2);
  histos[histonumber-1]->Draw("HIST SAME");

  // legend
  TLegend *legend = new TLegend(x1ndc,y1ndc,x2ndc,y2ndc);

  // mc hist entries
  for ( Int_t i = 1; i < histonumber-1; i++ ) {
    if ( option.Contains("STACKED") ) {
      legend->AddEntry(histos[i],histos[i]->GetTitle(),"F");
    } else {
      legend->AddEntry(histos[i],histos[i]->GetTitle(),"L");      
    }
  }

  // combined mc entry
  legend->AddEntry(histos[histonumber-1],temptitle.Data(),"L");      
  
  legend->SetBorderSize(1);
  legend->SetFillColor(0);
  legend->SetMargin(0.5);
  legend->Draw("SAME");

  return canvas;
}

//_____________________________________________________________

TCanvas* GHistogrammer::McPlot(Int_t histonumber, TH1F** histos,
			       TString name, TString title,
			       TString xaxis, TString yaxis,
			       Double_t x1ndc, Double_t y1ndc,
			       Double_t x2ndc, Double_t y2ndc,
			       Double_t leftMargin,
			       TString option) {
  //
  // make mc plot for TH1F
  //
  // histos array: last = combined mc
  //
  // option = normal (default) (histograms)
  //          STACKED (mc histograms to combined mc hist stacked
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::DataMcPlot() called" << endl << endl;

  if ( histos == 0 ) {
    cout << "Problems with histos array" << endl;
    return 0;
  } else if ( histonumber > 8 ) {
    cout << "More than 8 histograms are not supported" << endl;
    return 0;
  }

  option.ToUpper();

  // set color array
  Int_t colorArray[7];
  colorArray[0]=3;
  colorArray[1]=4;
  colorArray[2]=5;
  colorArray[3]=6;
  colorArray[4]=7;
  colorArray[5]=8;
  colorArray[6]=9;

  // initialize canvas and set leftmargin
  TCanvas *canvas = new TCanvas();
  canvas->SetLeftMargin(leftMargin);

  TString temptitle = histos[histonumber-1]->GetTitle();
  // set combined histogram
  TString mytitle = title;
  TString myname = name;
  if ( option.Contains("STACKED") ) {
    mytitle.Append(" stacked");
    myname.Append("_stacked");
  }
  histos[histonumber-1]->SetTitle(mytitle.Data());
  histos[histonumber-1]->SetName(myname.Data());
  histos[histonumber-1]->SetXTitle(xaxis);
  histos[histonumber-1]->SetYTitle(yaxis);

  // set maximum of histogramm to max of data or mc combined + 25 %
  Double_t max = histos[histonumber-1]->GetMaximum();
  max = 1.25*max;

  // draw data first to get the maximum and stats right
  histos[histonumber-1]->SetMaximum(max);
  histos[histonumber-1]->Draw("HIST");

  // instance of THStack
  THStack *stack = 0;
  if ( option.Contains("STACKED") ) {
    stack = new THStack(myname,mytitle);
  }

  for ( Int_t i = 0; i < histonumber-1; i++ ) {
    ZeroErrors(histos[i]);
    if ( option.Contains("STACKED") ) {
      histos[i]->SetFillColor(colorArray[i-1]);
      stack->Add(histos[i]);
    } else {
      histos[i]->SetLineColor(colorArray[i-1]);
    }
  }

  if ( option.Contains("STACKED") ) {
    stack->Draw("Hist SAME");
  } else {
    for ( Int_t i = 0; i < histonumber-1; i++ ) {
      histos[i]->Draw("HIST SAME");
    }
  }

  // draw combined mc hist
  histos[histonumber-1]->SetLineWidth(2);
  histos[histonumber-1]->SetLineColor(2);
  histos[histonumber-1]->Draw("HIST SAME");

  // legend
  TLegend *legend = new TLegend(x1ndc,y1ndc,x2ndc,y2ndc);

  // mc hist entries
  for ( Int_t i = 1; i < histonumber-1; i++ ) {
    if ( option.Contains("STACKED") ) {
      legend->AddEntry(histos[i],histos[i]->GetTitle(),"F");
    } else {
      legend->AddEntry(histos[i],histos[i]->GetTitle(),"L");
    }
  }

  // combined mc entry
  legend->AddEntry(histos[histonumber-1],temptitle.Data(),"L");

  legend->SetBorderSize(1);
  legend->SetFillColor(0);
  legend->SetMargin(0.5);
  legend->Draw("SAME");

  return canvas;
}

//_____________________________________________________________

Bool_t GHistogrammer::ZeroErrors(TH1 *hist) {
  //
  // zero errors of histogram
  for ( Int_t i = 0; i <= hist->GetNbinsX(); i++ ) {
    hist->SetBinError(i,0);
  }
  return kTRUE;
}

//_____________________________________________________________

Bool_t GHistogrammer::ComparePlots(TFile *reference, TFile *compare, TString dir, TString plot, TString option) {
  //
  // compare two plots from tow histogram files
  // Option = "MULT": multiply bin-content with bin value
  if ( gDebug==-1 ) cout << endl << "GInclude::ComparePlots() called" << endl << endl;

  if ( gROOT->IsBatch() ) {
    cout << "Cannot run in batch mode" << endl;
    return 0;
  }

  option.ToUpper();

  TString plotstring = "Histograms/";
  plotstring.Append(dir);
  plotstring.Append("/");
  plotstring.Append(plot);

  TKey *refkey = gInclude->FindKeyAnyRecursive(reference,plotstring);
  TKey *compkey = gInclude->FindKeyAnyRecursive(compare,plotstring);

  TH1D *ref  = 0;
  TH1D *comp = 0;

  if ( refkey != 0 ) {
    ref = (TH1D*)refkey->ReadObj();
  } else {
    return kFALSE;
  }

  if ( compkey != 0 ) {
    comp = (TH1D*)compkey->ReadObj();
  } else {
    return kFALSE;
  }


  ref->SetLineColor(2);
  comp->SetLineColor(4);

  ref->Draw();
  comp->Draw("SAME");

  TLegend *legend = new TLegend(0.78,0.70,0.98,0.81);
  legend->AddEntry(ref,"Reference","L");
  legend->AddEntry(comp,"Comparison","L");

  legend->SetBorderSize(1);
  legend->SetFillColor(0);
  legend->SetMargin(0.5);
  legend->Draw("SAME");

  Int_t refNr = (Int_t)ref->Integral();
  Int_t compNr = (Int_t)comp->Integral();

  if ( option.Contains("MULT") ) {
    refNr = (Int_t)this->IntegrateHistLowEdge(ref);
    compNr = (Int_t)this->IntegrateHistLowEdge(comp);
  }



  TString refString = "Ref.Int. : ";
  refString += refNr;
  TString compString = "Comp.Int.: ";
  compString += compNr;

  TPaveText *text = new TPaveText(0.78,0.58,0.98,0.69,"br,NDC");
  text->AddText(refString.Data());
  text->AddText(compString.Data());
  text->SetBorderSize(1);
  text->SetFillColor(0);
  text->SetMargin(0.5);
  text->Draw("SAME");

  return kTRUE;
}

//_____________________________________________________________

Double_t GHistogrammer::IntegrateHistLowEdge(TH1* hist) {
  //
  // integrate histogram by adding up bin-contend multipied by bin-low-edge
  if ( gDebug==-1 ) cout << endl << "GInclude::IntegrateHistogram() called" << endl << endl;

  Double_t integral = 0.0;

  for ( Int_t i = 0; i < hist->GetNbinsX(); i++ ) {
    integral += hist->GetBinContent(i)*hist->GetBinLowEdge(i);
  }

  return integral;
}

//_____________________________________________________________

Double_t GHistogrammer::GetGlobalScale(TFile *file, TString period, TString option) {
  //
  // get global scale for running period, if returns -9999.99, add all histograms unweighted
  if ( gDebug==-1 ) cout << endl << "GInclude::GetGlobalScale called" << endl << endl;

  Double_t scale = 0.0;

  if ( period.Contains("96p-97p") ) {
    scale += gInclude->GetLumi(file,"data/96p");
    scale += gInclude->GetLumi(file,"data/97p");
  } else if ( period.Contains("98e-99e") ) {
    scale += gInclude->GetLumi(file,"data/98e");
    scale += gInclude->GetLumi(file,"data/99e");
  } else if ( period.Contains("99p-00p") ) {
    scale += gInclude->GetLumi(file,"data/99p");
    scale += gInclude->GetLumi(file,"data/00p");
  } else if ( period.Contains("03p-04p") ) {
    scale += gInclude->GetLumi(file,"data/02p");
    scale += gInclude->GetLumi(file,"data/03p");
    scale += gInclude->GetLumi(file,"data/04p");
  } else if ( period.Contains("05e-06e") ) {
    scale += gInclude->GetLumi(file,"data/05e");
    scale += gInclude->GetLumi(file,"data/06e");
  } else if ( period.Contains("06p-07p") ) {
    scale += gInclude->GetLumi(file,"data/06p");
    scale += gInclude->GetLumi(file,"data/07p");
  }


  if ( scale == 0.0 ) 
    scale = -9999.99;

  return scale;
}

//_____________________________________________________________

Bool_t GHistogrammer::FitPtRel(TFile *file, TString histogramname, TString option){
  //
  // fit ptrel, fit is identified by complete name of data histogram
  if ( gDebug==-1 )   cout << endl << "GHistogrammer::FitPtRel called" << endl << endl;

  option.ToUpper();

  Bool_t localdebug = kTRUE;

  Bool_t do_periods = kFALSE;

  if ( do_periods ) {
    TIter nextperiod(fPeriods);

    while ( TObjString *period = (TObjString*)nextperiod() ) {

      // init variables
      Bool_t dofit = kTRUE;
      Int_t parameter = 2;
      // get histograms
      TH1D **histos = new TH1D *[parameter+1];
      for ( Int_t i = 0; i < parameter+1; ++i ) {
	histos[i] = 0;
      }

      // data
      TString dataname = "Histograms/data/merged/";
      dataname.Append(histogramname);
      dataname.Append("_");
      if ( option.Contains("JETMINMU") ) {
	dataname.Append("JetMinMu_");
      }    
      TString tempperiod = period->GetString();

      // fix for period 03p-04p_ztt
      tempperiod.ReplaceAll("_ztt","");

      dataname.Append(tempperiod);

      histos[0]=(TH1D*)file->Get(dataname);
      if ( !histos[0] ) {
	if ( localdebug ) {
	  cout << "GHistogrammer::FitPtRel problems with histogram: " << dataname << " in period"  << period->GetString() << endl;
	}
	dofit = kFALSE;
      }
      TString bname = "Histograms/mc/";
      bname.Append(period->GetString());
      bname.Append("/b/merged/");
      bname.Append(histogramname);
      if ( option.Contains("JETMINMU") ) {
	bname.Append("_JetMinMu");
      }    

      histos[1]=(TH1D*)file->Get(bname);
      if ( !histos[1] ) {
	if ( localdebug ) {
	  cout << "GHistogrammer::FitPtRel problems with histogram: " << bname << " in period"  << period->GetString() << endl;
	}
	dofit = kFALSE;
      }
      TString cname = "Histograms/mc/";
      cname.Append(period->GetString());
      cname.Append("/c/merged/");
      cname.Append(histogramname);
      if ( option.Contains("JETMINMU") ) {
	cname.Append("_JetMinMu");
      }    

      TH1D *cmc_histo = (TH1D*)file->Get(cname);
      if ( !cmc_histo ) {
	if ( localdebug ) {
	  cout << "GHistogrammer::FitPtRel problems with histogram: " << cname << " in period"  << period->GetString() << endl;
	}
	dofit = kFALSE;
      }
      cname.Append("_Corrections");
      TH1D *cmc_histo_corr =(TH1D*)gFile->Get(cname);
      if ( (cmc_histo_corr != 0) && (cmc_histo != 0) ) {
      
	Double_t old_int = cmc_histo->Integral();
	cmc_histo->Multiply(cmc_histo_corr);
	Double_t new_int = cmc_histo->Integral();
	cmc_histo->Scale(old_int/new_int);
      }

      TString lfname = "Histograms/mc/";
      lfname.Append(period->GetString());
      lfname.Append("/lf/merged/");
      lfname.Append(histogramname);
      if ( option.Contains("JETMINMU") ) {
	lfname.Append("_JetMinMu");
      }    
      TH1D *lfmc_histo = (TH1D*)file->Get(lfname);
      if ( !lfmc_histo ) {
	if ( localdebug ) {
	  cout << "GHistogrammer::FitPtRel problems with histogram: " << lfname << " in period"  << period->GetString() << endl;
	}
	dofit = kFALSE;
      }
      lfname.Append("_Corrections");
      TH1D *lfmc_histo_corr =(TH1D*)gFile->Get(lfname);
      if ( (lfmc_histo_corr != 0) && (lfmc_histo != 0) ) {
      
	Double_t old_int = lfmc_histo->Integral();
	lfmc_histo->Multiply(lfmc_histo_corr);
	Double_t new_int = lfmc_histo->Integral();
	lfmc_histo->Scale(old_int/new_int);
      }
      if ( dofit ) {
	Double_t clfintegral = cmc_histo->Integral();
	clfintegral += lfmc_histo->Integral();
	cmc_histo->Scale(1.);
	cout << "charm scaled" << endl;
	TH1D *clfmc_histo = (TH1D*)cmc_histo->Clone();
	clfmc_histo->Add(lfmc_histo);
	clfmc_histo->Scale(clfintegral/clfmc_histo->Integral());
	histos[2]=clfmc_histo;

	if ( option.Contains("JETMINMU") ) {
	  cout << "GHistogrammer: FitPtRel for histogram " << histogramname << " in mode JetMinMu for period " << period->GetString() << endl;
	} else {
	  cout << "GHistogrammer: FitPtRel for histogram " << histogramname << " for period " << period->GetString() << endl;
	}

	// get histograms from file and initialize fitter
	GFitter *fitter = new GFitter();
	Double_t *start = new Double_t [parameter];
	Double_t *step = new Double_t [parameter];
	for ( Int_t i = 0; i < parameter; i++ ) {
	  start[i] = 1.0;
	  step[i]  = 0.01;
	}
	fitter->SetParameter(parameter);
	fitter->SetStartArray(start);
	fitter->SetStepArray(step);
	fitter->SetHistos(parameter+1);
      
	fitter->ReadInContents(histos);
      
	// do fit
	fitter->DoFit();
      
	Double_t *par = fitter->GetParameterArray();
	Double_t *err = fitter->GetParaErrArray();
    
	// check if fit returns 0 values for fit which did not converge
	if ( (par[0] != 0) && (par[1] != 0) ) { 

	  Double_t bfraction = par[0] * histos[1]->Integral() / ( par[0] * histos[1]->Integral() + par[1] * histos[2]->Integral() );
// 	  Double_t dbfractiondpar1 = ( par[1] * histos[1]->Integral() * histos[2]->Integral() ) / TMath::Power(( par[0] * histos[1]->Integral() + par[1] * histos[2]->Integral() ),2);
// 	  Double_t dbfractiondpar2 = ( par[0] * histos[1]->Integral() * histos[2]->Integral() ) / TMath::Power(( par[0] * histos[1]->Integral() + par[1] * histos[2]->Integral() ),2);
// 	  Double_t bfractionerr = TMath::Sqrt(TMath::Power(dbfractiondpar1,2)*TMath::Power(err[0],2)+TMath::Power(dbfractiondpar2,2)*TMath::Power(err[1],2));

	  Double_t bfractionerr = err[0] * histos[1]->Integral()/ ( par[0] * histos[1]->Integral() + par[1] * histos[2]->Integral() );

	  Double_t chi2 = fitter->GetChi2();
	  Int_t bins = fitter->GetBins();
	  Int_t parameter = fitter->GetParameter();
	
	  gInclude->AddFit(file,dataname,par[0],err[0],par[1],err[1],bfraction,bfractionerr,chi2,bins,parameter);
	} else {
	  gInclude->AddFit(file,bname,0.,0.,0.,0.,0.,0.,0.,0,0);
	}

	if ( clfmc_histo != 0 ) {
	  delete clfmc_histo;
	  clfmc_histo = 0;
	  histos[2]=0;
	}
	delete fitter;
      }

      if ( cmc_histo != 0 ) {
	delete cmc_histo;
	cmc_histo = 0;
      }
      if ( lfmc_histo != 0 ) {
	delete lfmc_histo;
	lfmc_histo = 0;
      }

      if ( cmc_histo_corr != 0 ) {
	delete cmc_histo_corr;
	cmc_histo_corr = 0;
      }
      if ( lfmc_histo_corr != 0 ) {
	delete lfmc_histo_corr;
	lfmc_histo_corr = 0;
      }

      for ( Int_t i = 0; i <= parameter; ++i ) {
	if ( histos[i] != 0 ) {
	  delete histos[i];
	  histos[i]=0;
	}
      }

    }
  }


  // globaler ptrel fit
  // init variables
  Bool_t dofit = kTRUE;
  Int_t parameter = 2;

  // get histograms
  TH1D **histos = new TH1D *[parameter+1];
  for ( Int_t i = 0; i < parameter+1; ++i ) {
    histos[i] = 0;
  }

  // data
  TString dataname = "Histograms/data/merged/";
  dataname.Append(histogramname);
  if ( option.Contains("JETMINMU") ) {
    dataname.Append("_JetMinMu");
  }    
    
  histos[0]=(TH1D*)file->Get(dataname);
  if ( !histos[0] ) {
    dofit = kFALSE;
  }

  TString bname = "Histograms/mc/merged/b/";
  bname.Append(histogramname);
  if ( option.Contains("JETMINMU") ) {
    bname.Append("_JetMinMu");
  }    

  histos[1]=(TH1D*)file->Get(bname);
  if ( !histos[1] ) {
    dofit = kFALSE;
  }
  
  TString cname = "Histograms/mc/merged/c/";
  cname.Append(histogramname);
  if ( option.Contains("JETMINMU") ) {
    cname.Append("_JetMinMu");
  }    
  
  TH1D *cmc_histo = (TH1D*)file->Get(cname);
  if ( !cmc_histo ) {
    dofit = kFALSE;
  }
  cname.Append("_Corrections");
  TH1D *cmc_histo_corr =(TH1D*)gFile->Get(cname);
  if ( (cmc_histo_corr != 0) & (cmc_histo != 0) ) {
    Double_t old_int = cmc_histo->Integral();
    cmc_histo->Multiply(cmc_histo_corr);
    Double_t new_int = cmc_histo->Integral();
    cmc_histo->Scale(old_int/new_int);
  }

  TString lfname = "Histograms/mc/merged/lf/";
  lfname.Append(histogramname);
  if ( option.Contains("JETMINMU") ) {
    lfname.Append("_JetMinMu");
  }    
  
  TH1D *lfmc_histo = (TH1D*)file->Get(lfname);
  if ( !lfmc_histo ) {
    dofit = kFALSE;
  }
  lfname.Append("_Corrections");
  TH1D *lfmc_histo_corr =(TH1D*)gFile->Get(lfname);
  if ( (lfmc_histo_corr != 0) && (lfmc_histo != 0) ) {
    Double_t old_int = lfmc_histo->Integral();
    lfmc_histo->Multiply(lfmc_histo_corr);
    Double_t new_int = lfmc_histo->Integral();
    lfmc_histo->Scale(old_int/new_int);
  }
  
  if ( dofit ) {
    Double_t clfintegral = cmc_histo->Integral();
    clfintegral += lfmc_histo->Integral();
    cmc_histo->Scale(1.0);
    TH1D *clfmc_histo = (TH1D*)cmc_histo->Clone();
    clfmc_histo->Add(lfmc_histo);
    clfmc_histo->Scale(clfintegral/clfmc_histo->Integral());
    histos[2]=clfmc_histo;
    if ( option.Contains("JETMINMU") ) {
      cout << "GHistogrammer: global FitPtRel for histogram " << histogramname << " in mode JetMinMu" << endl;
    } else {
      cout << "GHistogrammer: global FitPtRel for histogram " << histogramname << endl;
    }

    // get histograms from file and initialize fitter
    GFitter *fitter = new GFitter();
    Double_t *start = new Double_t [parameter];
    Double_t *step = new Double_t [parameter];
    for ( Int_t i = 0; i < parameter; i++ ) {
      start[i] = 1.0;
      step[i]  = 0.01;
    }
    fitter->SetParameter(parameter);
    fitter->SetStartArray(start);
    fitter->SetStepArray(step);
    fitter->SetHistos(parameter+1);
    
    fitter->ReadInContents(histos);
      
    // do fit
    fitter->DoFit();
      
    Double_t *par = fitter->GetParameterArray();
    Double_t *err = fitter->GetParaErrArray();

    // check if fit returns 0 values for fit which did not converge
    if ( (par[0] != 0) && (par[1] != 0) ) { 

      Double_t bfraction = par[0] * histos[1]->Integral() / ( par[0] * histos[1]->Integral() + par[1] * histos[2]->Integral() );
//       Double_t dbfractiondpar1 = ( par[1] * histos[1]->Integral() * histos[2]->Integral() ) / TMath::Power(( par[0] * histos[1]->Integral() + par[1] * histos[2]->Integral() ),2);
//       Double_t dbfractiondpar2 = ( par[0] * histos[1]->Integral() * histos[2]->Integral() ) / TMath::Power(( par[0] * histos[1]->Integral() + par[1] * histos[2]->Integral() ),2);
//       Double_t bfractionerr = TMath::Sqrt(TMath::Power(dbfractiondpar1,2)*TMath::Power(err[0],2)+TMath::Power(dbfractiondpar2,2)*TMath::Power(err[1],2));
      Double_t bfractionerr = err[0] * histos[1]->Integral()/ ( par[0] * histos[1]->Integral() + par[1] * histos[2]->Integral() );
      
      Double_t chi2 = fitter->GetChi2();
      Int_t bins = fitter->GetBins();
      Int_t parameter = fitter->GetParameter();
	
      gInclude->AddFit(file,dataname,par[0],err[0],par[1],err[1],bfraction,bfractionerr,chi2,bins,parameter);
    } else {
      gInclude->AddFit(file,bname,0.,0.,0.,0.,0.,0.,0.,0,0);
    }
    
    if ( clfmc_histo != 0 ) {
      delete clfmc_histo;
      clfmc_histo = 0;
      histos[2]=0;
    }
    delete fitter;
  }

  if ( cmc_histo != 0 ) {
    delete cmc_histo;
    cmc_histo = 0;
  }
  if ( lfmc_histo != 0 ) {
    delete lfmc_histo;
    lfmc_histo = 0;
  }

  if ( cmc_histo_corr != 0 ) {
    delete cmc_histo_corr;
    cmc_histo_corr = 0;
  }
  if ( lfmc_histo_corr != 0 ) {
    delete lfmc_histo_corr;
    lfmc_histo_corr = 0;
  }
  
  for ( Int_t i = 0; i <= parameter; ++i ) {
    if ( histos[i] != 0 ) {
      delete histos[i];
      histos[i]=0;
    }
  }
  
  return kTRUE;
}

//_____________________________________________________________

Bool_t GHistogrammer:: FitPtRelMCOnly(TFile *file, TString histogramname, TString option){
  //
  // fit ptrel using MC only, fit is identified by complete name of b histogram
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::FitPtRelMCOnly called" << endl << endl;

  option.ToUpper();

  Bool_t do_periods = kFALSE;

  if ( do_periods ) {

    TIter nextperiod(fPeriods);

    while ( TObjString *period = (TObjString*)nextperiod() ) {

      // init variables
      Bool_t dofit = kTRUE;
      Int_t parameter = 2;

      // get histograms
      TH1D **histos = new TH1D *[parameter+1];
      for ( Int_t i = 0; i < parameter+1; ++i ) {
	histos[i] = 0;
      }

      TString bname = "Histograms/mc/";
      bname.Append(period->GetString());
      bname.Append("/b/merged/");
      bname.Append(histogramname);
      if ( option.Contains("JETMINMU") ) {
	bname.Append("_JetMinMu");
      }    

      histos[1]=(TH1D*)file->Get(bname);
      if ( !histos[1] ) {
	dofit = kFALSE;
      }

      TString cname = "Histograms/mc/";
      cname.Append(period->GetString());
      cname.Append("/c/merged/");
      cname.Append(histogramname);
      if ( option.Contains("JETMINMU") ) {
	cname.Append("_JetMinMu");
      }    

      TH1D *cmc_histo = (TH1D*)file->Get(cname);
      if ( !cmc_histo ) {
	dofit = kFALSE;
      }
      cname.Append("_Corrections");
      TH1D *cmc_histo_corr =(TH1D*)gFile->Get(cname);
      if ( (cmc_histo_corr != 0) && (cmc_histo != 0) ) {
      
	Double_t old_int = cmc_histo->Integral();
	cmc_histo->Multiply(cmc_histo_corr);
	Double_t new_int = cmc_histo->Integral();
	cmc_histo->Scale(old_int/new_int);
      }

      TString lfname = "Histograms/mc/";
      lfname.Append(period->GetString());
      lfname.Append("/lf/merged/");
      lfname.Append(histogramname);
      if ( option.Contains("JETMINMU") ) {
	lfname.Append("_JetMinMu");
      }    

      TH1D *lfmc_histo = (TH1D*)file->Get(lfname);
      if ( !lfmc_histo ) {
	dofit = kFALSE;
      }
      lfname.Append("_Corrections");
      TH1D *lfmc_histo_corr =(TH1D*)gFile->Get(lfname);
      if ( (lfmc_histo_corr != 0) && (lfmc_histo != 0) ) {
      
	Double_t old_int = lfmc_histo->Integral();
	lfmc_histo->Multiply(lfmc_histo_corr);
	Double_t new_int = lfmc_histo->Integral();
	lfmc_histo->Scale(old_int/new_int);
      }

      if ( dofit ) {

	TH1D *bclfmc_histo = (TH1D*)histos[1]->Clone();
	bclfmc_histo->Add(cmc_histo);
	bclfmc_histo->Add(lfmc_histo);

	histos[0]=bclfmc_histo;

	TH1D *clfmc_histo = (TH1D*)cmc_histo->Clone();
	clfmc_histo->Add(lfmc_histo);

	histos[2]=clfmc_histo;

	if ( option.Contains("JETMINMU") ) {
	  cout << "GHistogrammer: FitPtRel for histogram " << histogramname << " for MC only in mode JetMinMu in period " << period->GetString() << endl;
	} else {
	  cout << "GHistogrammer: FitPtRel for histogram " << histogramname << " for MC only in period " << period->GetString() << endl;
	}

	// get histograms from file and initialize fitter
	GFitter *fitter = new GFitter();
	Double_t *start = new Double_t [parameter];
	Double_t *step = new Double_t [parameter];
	for ( Int_t i = 0; i < parameter; i++ ) {
	  start[i] = 1.0;
	  step[i]  = 0.01;
	}
	fitter->SetParameter(parameter);
	fitter->SetStartArray(start);
	fitter->SetStepArray(step);
	fitter->SetHistos(parameter+1);
      
	fitter->ReadInContents(histos);
      
	// do fit
	fitter->DoFit();
      
	Double_t *par = fitter->GetParameterArray();
	Double_t *err = fitter->GetParaErrArray();

	// check if fit returns 0 values for fit which did not converge
	if ( (par[0] != 0) && (par[1] != 0) ) { 

	  Double_t bfraction = par[0] * histos[1]->Integral() / ( par[0] * histos[1]->Integral() + par[1] * histos[2]->Integral() );
// 	  Double_t dbfractiondpar1 = ( par[1] * histos[1]->Integral() * histos[2]->Integral() ) / TMath::Power(( par[0] * histos[1]->Integral() + par[1] * histos[2]->Integral() ),2);
// 	  Double_t dbfractiondpar2 = ( par[0] * histos[1]->Integral() * histos[2]->Integral() ) / TMath::Power(( par[0] * histos[1]->Integral() + par[1] * histos[2]->Integral() ),2);
// 	  Double_t bfractionerr = TMath::Sqrt(TMath::Power(dbfractiondpar1,2)*TMath::Power(err[0],2)+TMath::Power(dbfractiondpar2,2)*TMath::Power(err[1],2));
	  Double_t bfractionerr = err[0] * histos[1]->Integral()/ ( par[0] * histos[1]->Integral() + par[1] * histos[2]->Integral() );

	  Double_t chi2 = fitter->GetChi2();
	  Int_t bins = fitter->GetBins();
	  Int_t parameter = fitter->GetParameter();
	
	  gInclude->AddFit(file,bname,par[0],err[0],par[1],err[1],bfraction,bfractionerr,chi2,bins,parameter);
	} else {
	  gInclude->AddFit(file,bname,0.,0.,0.,0.,0.,0.,0.,0,0);
	}
      
	if ( clfmc_histo != 0 ) {
	  delete clfmc_histo;
	  clfmc_histo = 0;
	  histos[2]=0;
	}
	if ( bclfmc_histo == 0 ) {
	  delete bclfmc_histo;
	  bclfmc_histo = 0;
	  histos[0]=0;
	}
	delete fitter;
      }

      if ( cmc_histo != 0 ) {
	delete cmc_histo;
	cmc_histo = 0;
      }
      if ( lfmc_histo != 0 ) {
	delete lfmc_histo;
	lfmc_histo = 0;
      }

      if ( cmc_histo_corr != 0 ) {
	delete cmc_histo_corr;
	cmc_histo_corr = 0;
      }
      if ( lfmc_histo_corr != 0 ) {
	delete lfmc_histo_corr;
	lfmc_histo_corr = 0;
      }

      for ( Int_t i = 0; i <= parameter; ++i ) {
	if ( histos[i] != 0 ) {
	  delete histos[i];
	  histos[i]=0;
	}
      }

    }
  }

  // complete fit

  // init variables
  Bool_t dofit = kTRUE;
  Int_t parameter = 2;

  // get histograms
  TH1D **histos = new TH1D *[parameter+1];
  for ( Int_t i = 0; i < parameter+1; ++i ) {
    histos[i] = 0;
  }
  
  TString bname = "Histograms/mc/merged/b/";
  bname.Append(histogramname);
  if ( option.Contains("JETMINMU") ) {
    bname.Append("_JetMinMu");
  }    
  
  histos[1]=(TH1D*)file->Get(bname);
  if ( !histos[1] ) {
    dofit = kFALSE;
  }
  
  TString cname = "Histograms/mc/merged/c/";
  cname.Append(histogramname);
  if ( option.Contains("JETMINMU") ) {
    cname.Append("_JetMinMu");
  }    
  
  TH1D *cmc_histo = (TH1D*)file->Get(cname);
  if ( !cmc_histo ) {
    dofit = kFALSE;
  }
  cname.Append("_Corrections");
  TH1D *cmc_histo_corr =(TH1D*)gFile->Get(cname);
  if ( (cmc_histo_corr != 0) && (cmc_histo != 0) ) {
    
    Double_t old_int = cmc_histo->Integral();
    cmc_histo->Multiply(cmc_histo_corr);
    Double_t new_int = cmc_histo->Integral();
    cmc_histo->Scale(old_int/new_int);
  }
  
  TString lfname = "Histograms/mc/merged/lf/";
  lfname.Append(histogramname);
  if ( option.Contains("JETMINMU") ) {
    lfname.Append("_JetMinMu");
  }    
  
  TH1D *lfmc_histo = (TH1D*)file->Get(lfname);
  if ( !lfmc_histo ) {
    dofit = kFALSE;
  }
  lfname.Append("_Corrections");
  TH1D *lfmc_histo_corr =(TH1D*)gFile->Get(lfname);
  if ( (lfmc_histo_corr != 0) && (lfmc_histo != 0) ) {
    
    Double_t old_int = lfmc_histo->Integral();
    lfmc_histo->Multiply(lfmc_histo_corr);
    Double_t new_int = lfmc_histo->Integral();
    lfmc_histo->Scale(old_int/new_int);
  }

  if ( dofit ) {
    
    TH1D *bclfmc_histo = (TH1D*)histos[1]->Clone();
    bclfmc_histo->Add(cmc_histo);
    bclfmc_histo->Add(lfmc_histo);
    
    histos[0]=bclfmc_histo;
    
    TH1D *clfmc_histo = (TH1D*)cmc_histo->Clone();
    clfmc_histo->Add(lfmc_histo);
    
    histos[2]=clfmc_histo;

    if ( option.Contains("JETMINMU") ) {
      cout << "GHistogrammer: global FitPtRel for histogram " << histogramname << " for MC only in mode JetMinMu" << endl;
    } else {
      cout << "GHistogrammer: global FitPtRel for histogram " << histogramname << " for MC only" << endl;
    }
    
    // get histograms from file and initialize fitter
    GFitter *fitter = new GFitter();
    Double_t *start = new Double_t [parameter];
    Double_t *step = new Double_t [parameter];
    for ( Int_t i = 0; i < parameter; i++ ) {
      start[i] = 1.0;
      step[i]  = 0.01;
    }
    fitter->SetParameter(parameter);
    fitter->SetStartArray(start);
    fitter->SetStepArray(step);
    fitter->SetHistos(parameter+1);
    
    fitter->ReadInContents(histos);
    
    // do fit
    fitter->DoFit();
    
    Double_t *par = fitter->GetParameterArray();
    Double_t *err = fitter->GetParaErrArray();

    // check if fit returns 0 values for fit which did not converge
    if ( (par[0] != 0) && (par[1] != 0) ) { 

      Double_t bfraction = par[0] * histos[1]->Integral() / ( par[0] * histos[1]->Integral() + par[1] * histos[2]->Integral() );
//       Double_t dbfractiondpar1 = ( par[1] * histos[1]->Integral() * histos[2]->Integral() ) / TMath::Power(( par[0] * histos[1]->Integral() + par[1] * histos[2]->Integral() ),2);
//       Double_t dbfractiondpar2 = ( par[0] * histos[1]->Integral() * histos[2]->Integral() ) / TMath::Power(( par[0] * histos[1]->Integral() + par[1] * histos[2]->Integral() ),2);
//       Double_t bfractionerr = TMath::Sqrt(TMath::Power(dbfractiondpar1,2)*TMath::Power(err[0],2)+TMath::Power(dbfractiondpar2,2)*TMath::Power(err[1],2));
      Double_t bfractionerr = err[0] * histos[1]->Integral()/ ( par[0] * histos[1]->Integral() + par[1] * histos[2]->Integral() );
      
      Double_t chi2 = fitter->GetChi2();
      Int_t bins = fitter->GetBins();
      Int_t parameter = fitter->GetParameter();

      gInclude->AddFit(file,bname,par[0],err[0],par[1],err[1],bfraction,bfractionerr,chi2,bins,parameter);

    } else {
      gInclude->AddFit(file,bname,0.,0.,0.,0.,0.,0.,0.,0,0);
    }

    if ( clfmc_histo != 0 ) {
      delete clfmc_histo;
      clfmc_histo = 0;
      histos[2]=0;
    }
    if ( bclfmc_histo != 0 ) {
      delete bclfmc_histo;
      bclfmc_histo = 0;
      histos[0]=0;
    }
    delete fitter;
  }

  if ( cmc_histo != 0 ) {
    delete cmc_histo;
    cmc_histo = 0;
  }
  if ( lfmc_histo == 0 ) {
    delete lfmc_histo;
    lfmc_histo = 0;
  }

  if ( cmc_histo_corr != 0 ) {
    delete cmc_histo_corr;
    cmc_histo_corr = 0;
  }
  if ( lfmc_histo_corr != 0 ) {
    delete lfmc_histo_corr;
    lfmc_histo_corr = 0;
  }
  
  for ( Int_t i = 0; i <= parameter; ++i ) {
    if ( histos[i] != 0 ) {
      delete histos[i];
      histos[i]=0;
    }
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GHistogrammer:: FitImpact(TFile *file, TString histogramname, TString option){
  //
  // fit impact parameter, fit is identified by complete name of data histogram
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::FitImpact called" << endl << endl;

  option.ToUpper();

  TIter nextperiod(fPeriods);

  while ( TObjString *period = (TObjString*)nextperiod() ) {

    // init variables
    Bool_t dofit = kTRUE;
    Int_t parameter = 2;

    // get histograms
    TH1D **histos = new TH1D *[parameter+1];
    for ( Int_t i = 0; i < parameter+1; ++i ) {
      histos[i] = 0;
    }

    // data
    TString dataname = "Histograms/data/merged/";
    dataname.Append(histogramname);
    dataname.Append("_");
    
    TString tempperiod = period->GetString();

    // fix for period 03p-04p_ztt
    tempperiod.ReplaceAll("_ztt","");

    dataname.Append(tempperiod);

    histos[0]=(TH1D*)file->Get(dataname);
    if ( !histos[0] ) {
      dofit = kFALSE;
    }

    TString bname = "Histograms/mc/";
    bname.Append(period->GetString());
    bname.Append("/b/merged/");
    bname.Append(histogramname);

    histos[1]=(TH1D*)file->Get(bname);
    if ( !histos[1] ) {
      dofit = kFALSE;
    }

    TString clfname = ("Histograms/mc/");
    clfname.Append(period->GetString());
    clfname.Append("/merged/");
    clfname.Append(histogramname);
    clfname.Append("_c_lf");


    histos[2]=(TH1D*)file->Get(clfname);
    if ( !histos[2] ) {
      dofit = kFALSE;
    }


    if ( dofit ) {

      cout << "GHistogrammer: FitImpact for histogram " << histogramname << endl;

      // get histograms from file and initialize fitter
      GFitter *fitter = new GFitter();
      Double_t *start = new Double_t [parameter];
      Double_t *step = new Double_t [parameter];
      for ( Int_t i = 0; i < parameter; i++ ) {
	start[i] = 1.0;
	step[i]  = 0.01;
      }
      fitter->SetParameter(parameter);
      fitter->SetStartArray(start);
      fitter->SetStepArray(step);
      fitter->SetHistos(parameter+1);
      
      fitter->ReadInContents(histos);
      
      // do fit
      fitter->DoFit();
      
      Double_t *par = fitter->GetParameterArray();
      Double_t *err = fitter->GetParaErrArray();

      // check if fit returns 0 values for fit which did not converge
      if ( (par[0] != 0) && (par[1] != 0) ) { 

	Double_t bfraction = par[0] * histos[1]->Integral() / ( par[0] * histos[1]->Integral() + par[1] * histos[2]->Integral() );
// 	Double_t dbfractiondpar1 = ( par[1] * histos[1]->Integral() * histos[2]->Integral() ) / TMath::Power(( par[0] * histos[1]->Integral() + par[1] * histos[2]->Integral() ),2);
// 	Double_t dbfractiondpar2 = ( par[0] * histos[1]->Integral() * histos[2]->Integral() ) / TMath::Power(( par[0] * histos[1]->Integral() + par[1] * histos[2]->Integral() ),2);
// 	Double_t bfractionerr = TMath::Sqrt(TMath::Power(dbfractiondpar1,2)*TMath::Power(err[0],2)+TMath::Power(dbfractiondpar2,2)*TMath::Power(err[1],2));
	Double_t bfractionerr = err[0] * histos[1]->Integral()/ ( par[0] * histos[1]->Integral() + par[1] * histos[2]->Integral() );
	
	Double_t chi2 = fitter->GetChi2();
	Int_t bins = fitter->GetBins();
	Int_t parameter = fitter->GetParameter();

	gInclude->AddImpactFit(file,dataname,par[0],err[0],par[1],err[1],bfraction,bfractionerr,chi2,bins,parameter);
      } else {
	gInclude->AddImpactFit(file,bname,0.,0.,0.,0.,0.,0.,0.,0,0);
      }


      delete fitter;
    }

  }

  // globaler ptrel fit
  // init variables
  Bool_t dofit = kTRUE;
  Int_t parameter = 2;

  // get histograms
  TH1D **histos = new TH1D *[parameter+1];
  for ( Int_t i = 0; i < parameter+1; ++i ) {
    histos[i] = 0;
  }

  // data
  TString dataname = "Histograms/data/merged/";
  dataname.Append(histogramname);
    
  histos[0]=(TH1D*)file->Get(dataname);
  if ( !histos[0] ) {
    dofit = kFALSE;
  }

  TString bname = "Histograms/mc/merged/b/";
  bname.Append(histogramname);

  histos[1]=(TH1D*)file->Get(bname);
  if ( !histos[1] ) {
    dofit = kFALSE;
  }
  
  TString clfname = "Histograms/mc/merged/merged/";
  clfname.Append(histogramname);
  clfname.Append("_c_lf");

  histos[2]=(TH1D*)file->Get(clfname);
  if ( !histos[2] ) {
    dofit = kFALSE;
  }

  if ( dofit ) {

    cout << "GHistogrammer: FitImpact for histogram " << histogramname << endl;

    // get histograms from file and initialize fitter
    GFitter *fitter = new GFitter();
    Double_t *start = new Double_t [parameter];
    Double_t *step = new Double_t [parameter];
    for ( Int_t i = 0; i < parameter; i++ ) {
      start[i] = 1.0;
      step[i]  = 0.01;
    }
    fitter->SetParameter(parameter);
    fitter->SetStartArray(start);
    fitter->SetStepArray(step);
    fitter->SetHistos(parameter+1);
    
    fitter->ReadInContents(histos);
      
    // do fit
    fitter->DoFit();
      
    Double_t *par = fitter->GetParameterArray();
    Double_t *err = fitter->GetParaErrArray();

    // check if fit returns 0 values for fit which did not converge
    if ( (par[0] != 0) && (par[1] != 0) ) { 

      Double_t bfraction = par[0] * histos[1]->Integral() / ( par[0] * histos[1]->Integral() + par[1] * histos[2]->Integral() );
//       Double_t dbfractiondpar1 = ( par[1] * histos[1]->Integral() * histos[2]->Integral() ) / TMath::Power(( par[0] * histos[1]->Integral() + par[1] * histos[2]->Integral() ),2);
//       Double_t dbfractiondpar2 = ( par[0] * histos[1]->Integral() * histos[2]->Integral() ) / TMath::Power(( par[0] * histos[1]->Integral() + par[1] * histos[2]->Integral() ),2);
//       Double_t bfractionerr = TMath::Sqrt(TMath::Power(dbfractiondpar1,2)*TMath::Power(err[0],2)+TMath::Power(dbfractiondpar2,2)*TMath::Power(err[1],2));
      Double_t bfractionerr = err[0] * histos[1]->Integral()/ ( par[0] * histos[1]->Integral() + par[1] * histos[2]->Integral() );
      
      Double_t chi2 = fitter->GetChi2();
      Int_t bins = fitter->GetBins();
      Int_t parameter = fitter->GetParameter();

      gInclude->AddImpactFit(file,dataname,par[0],err[0],par[1],err[1],bfraction,bfractionerr,chi2,bins,parameter);
    } else {
      gInclude->AddImpactFit(file,bname,0.,0.,0.,0.,0.,0.,0.,0,0);
    }

    delete fitter;
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GHistogrammer:: FitImpactMCOnly(TFile *file, TString histogramname, TString option){
  //
  // fit impact parameter using MC only, fit is identified by complete name of b histogram
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::FitImpactMCOnly called" << endl << endl;

  option.ToUpper();

  TIter nextperiod(fPeriods);

  while ( TObjString *period = (TObjString*)nextperiod() ) {

    // init variables
    Bool_t dofit = kTRUE;
    Int_t parameter = 2;

    // get histograms
    TH1D **histos = new TH1D *[parameter+1];
    for ( Int_t i = 0; i < parameter+1; ++i ) {
      histos[i] = 0;
    }

    // merged mc as data histogram
    TString dataname = ("Histograms/mc/");
    dataname.Append(period->GetString());
    dataname.Append("/merged/");
    dataname.Append(histogramname);
    dataname.Append("_b_c_lf");

    histos[0]=(TH1D*)file->Get(dataname);
    if ( !histos[0] ) {
      dofit = kFALSE;
    }

    TString bname = "Histograms/mc/";
    bname.Append(period->GetString());
    bname.Append("/b/merged/");
    bname.Append(histogramname);

    histos[1]=(TH1D*)file->Get(bname);
    if ( !histos[1] ) {
      dofit = kFALSE;
    }

    TString clfname = ("Histograms/mc/");
    clfname.Append(period->GetString());
    clfname.Append("/merged/");
    clfname.Append(histogramname);
    clfname.Append("_c_lf");

    histos[2]=(TH1D*)file->Get(clfname);
    if ( !histos[2] ) {
      dofit = kFALSE;
    }

    if ( dofit ) {

      cout << "GHistogrammer: FitImpact for histogram " << histogramname << " for MC only" << endl;

      // get histograms from file and initialize fitter
      GFitter *fitter = new GFitter();
      Double_t *start = new Double_t [parameter];
      Double_t *step = new Double_t [parameter];
      for ( Int_t i = 0; i < parameter; i++ ) {
	start[i] = 1.0;
	step[i]  = 0.01;
      }
      fitter->SetParameter(parameter);
      fitter->SetStartArray(start);
      fitter->SetStepArray(step);
      fitter->SetHistos(parameter+1);
      
      fitter->ReadInContents(histos);
      
      // do fit
      fitter->DoFit();
      
      Double_t *par = fitter->GetParameterArray();
      Double_t *err = fitter->GetParaErrArray();

      // check if fit returns 0 values for fit which did not converge
      if ( (par[0] != 0) && (par[1] != 0) ) { 

	Double_t bfraction = par[0] * histos[1]->Integral() / ( par[0] * histos[1]->Integral() + par[1] * histos[2]->Integral() );
// 	Double_t dbfractiondpar1 = ( par[1] * histos[1]->Integral() * histos[2]->Integral() ) / TMath::Power(( par[0] * histos[1]->Integral() + par[1] * histos[2]->Integral() ),2);
// 	Double_t dbfractiondpar2 = ( par[0] * histos[1]->Integral() * histos[2]->Integral() ) / TMath::Power(( par[0] * histos[1]->Integral() + par[1] * histos[2]->Integral() ),2);
// 	Double_t bfractionerr = TMath::Sqrt(TMath::Power(dbfractiondpar1,2)*TMath::Power(err[0],2)+TMath::Power(dbfractiondpar2,2)*TMath::Power(err[1],2));
	Double_t bfractionerr = err[0] * histos[1]->Integral()/ ( par[0] * histos[1]->Integral() + par[1] * histos[2]->Integral() );
	
	Double_t chi2 = fitter->GetChi2();
	Int_t bins = fitter->GetBins();
	Int_t parameter = fitter->GetParameter();

	gInclude->AddImpactFit(file,bname,par[0],err[0],par[1],err[1],bfraction,bfractionerr,chi2,bins,parameter);
      } else {
	gInclude->AddImpactFit(file,bname,0.,0.,0.,0.,0.,0.,0.,0,0);
      }

      delete fitter;
    }

  }

  // complete fit

  // init variables
  Bool_t dofit = kTRUE;
  Int_t parameter = 2;

  // get histograms
  TH1D **histos = new TH1D *[parameter+1];
  for ( Int_t i = 0; i < parameter+1; ++i ) {
    histos[i] = 0;
  }
  
  // merged mc as data histogram
  TString dataname = ("Histograms/mc/merged/merged/");
  dataname.Append(histogramname);
  dataname.Append("_b_c_lf");

  histos[0]=(TH1D*)file->Get(dataname);
  if ( !histos[0] ) {
    dofit = kFALSE;
  }

  TString bname = "Histograms/mc/merged/b/";
  bname.Append(histogramname);

  histos[1]=(TH1D*)file->Get(bname);
  if ( !histos[1] ) {
    dofit = kFALSE;
  }

  TString clfname = ("Histograms/mc/merged/merged/");
  clfname.Append(histogramname);
  clfname.Append("_c_lf");

  histos[2]=(TH1D*)file->Get(clfname);
  if ( !histos[2] ) {
    dofit = kFALSE;
  }

  if ( dofit ) {
    
    cout << "GHistogrammer: FitImpact for histogram " << histogramname << " for MC only" << endl;
    
    // get histograms from file and initialize fitter
    GFitter *fitter = new GFitter();
    Double_t *start = new Double_t [parameter];
    Double_t *step = new Double_t [parameter];
    for ( Int_t i = 0; i < parameter; i++ ) {
      start[i] = 1.0;
      step[i]  = 0.01;
    }
    fitter->SetParameter(parameter);
    fitter->SetStartArray(start);
    fitter->SetStepArray(step);
    fitter->SetHistos(parameter+1);
    
    fitter->ReadInContents(histos);
    
    // do fit
    fitter->DoFit();
    
    Double_t *par = fitter->GetParameterArray();
    Double_t *err = fitter->GetParaErrArray();

    // check if fit returns 0 values for fit which did not converge
    if ( (par[0] != 0) && (par[1] != 0) ) { 

      Double_t bfraction = par[0] * histos[1]->Integral() / ( par[0] * histos[1]->Integral() + par[1] * histos[2]->Integral() );
//       Double_t dbfractiondpar1 = ( par[1] * histos[1]->Integral() * histos[2]->Integral() ) / TMath::Power(( par[0] * histos[1]->Integral() + par[1] * histos[2]->Integral() ),2);
//       Double_t dbfractiondpar2 = ( par[0] * histos[1]->Integral() * histos[2]->Integral() ) / TMath::Power(( par[0] * histos[1]->Integral() + par[1] * histos[2]->Integral() ),2);
//       Double_t bfractionerr = TMath::Sqrt(TMath::Power(dbfractiondpar1,2)*TMath::Power(err[0],2)+TMath::Power(dbfractiondpar2,2)*TMath::Power(err[1],2));
      Double_t bfractionerr = err[0] * histos[1]->Integral() / ( par[0] * histos[1]->Integral() + par[1] * histos[2]->Integral() );
    
      Double_t chi2 = fitter->GetChi2();
      Int_t bins = fitter->GetBins();
      Int_t parameter = fitter->GetParameter();

      gInclude->AddImpactFit(file,bname,par[0],err[0],par[1],err[1],bfraction,bfractionerr,chi2,bins,parameter);
    } else {
      gInclude->AddImpactFit(file,bname,0.,0.,0.,0.,0.,0.,0.,0,0);
    }
    
    delete fitter;
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GHistogrammer::AddHistosDataStage1(TFile *file, TString type, TString histogramname, TString option) {
  //
  // merge histograms to histogram in smallest same directory + merged directory in file
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::AddHistosDataStage1 called" << endl << endl;

  Bool_t localdebug = kFALSE;
  Bool_t label = kFALSE;
  option.ToUpper();

  if ( option.Contains("DEBUG") )
    localdebug = kTRUE;

  if ( option.Contains("LABEL") ) label = kTRUE;

  TList *histolist = new TList();
  TList *histodirlist = new TList();
  TList *typelist = new TList();
  Int_t histonum = 0;

  // separate type entries by comma
  TString temptype = type;
  char first;
  TString temp = "";
  // separate entries in types
  while ( (first = temptype(0)) ) {
    // remove first
    temptype.Remove(0,1);
    // append to temp or break in case of comma
    if ( first == 44 ) {
      typelist->Add(new TObjString(temp));
      temp = "";
    } else {
      temp.Append(first);
    }
  }
  if ( temp.Length() != 0 ) {
    typelist->Add(new TObjString(temp));
  }
  
  // fill histo list
  TIter nexttype(typelist);
  temp = "";
  while ( TObjString *looptype = (TObjString*)nexttype() ) {
    temp = "Histograms/data/";
    temp.Append(looptype->GetString());
    temp.Append("/");
    temp.Append(histogramname);
    TH1D* histo = (TH1D*)file->Get(temp);
    if ( histo != 0 ) {
      histolist->Add(histo);
      histodirlist->Add(new TObjString(temp));
      histonum += 1;
    }
  }

  if ( histonum == 0 ) {
    if ( localdebug ) {
      cout << "histogram type " << type << " name " << histogramname << " not available" <<  endl;
    }
    histodirlist->Delete();
    delete histodirlist;
    histolist->Delete();
    delete histolist;
    typelist->Delete();
    delete typelist;
    return kFALSE;
  }

  // check for histogram compatibility
  if ( !this->CheckHistoCompat(histolist) ) {
    cout << "Histograms are not compatible" << endl;
    histodirlist->Delete();
    delete histodirlist;
    histolist->Delete();
    delete histolist;
    typelist->Delete();
    delete typelist;
    return kFALSE;
  }
  
  if ( localdebug ) {
    cout << "number of histograms: " << histonum << endl;
    TIter temp(histolist);
    while (TH1D* temphist = (TH1D*)temp() ) 
      cout << "histogram-name: " << temphist->GetName() << " histogram-title: " << temphist->GetTitle() << endl;
  }

  TString dirname = this->SameDirectory(histonum, histodirlist);
  if ( dirname.Contains(gInclude->StripLastDir(histogramname)) ) {
    dirname.ReplaceAll(gInclude->StripLastDir(histogramname),"");
    dirname = gInclude->StripLastDir(dirname);
    dirname = gInclude->StripLastDir(dirname);
  }
  if ( !dirname.EndsWith("/") )
    dirname.Append("/");
  dirname.Append("merged/");
  if ( !dirname.EndsWith("/") )
    dirname.Append("/");
  dirname.Append(gInclude->StripLastDir(histogramname));
  TDirectory *directory = gInclude->MkdirRecursiveOld(file,dirname);
  directory->cd();

  TString mergedname = gInclude->StripFirstDir(histogramname);
  TString mergedtitle = ((TH1D*)histolist->First())->GetTitle();
   
  TString tempidentifier = "";
  TIter nexttype2(typelist);
  while ( TObjString *looptype = (TObjString*)nexttype2() ) {
    tempidentifier.Append(looptype->GetString());
    tempidentifier.Append("-");
  }
  if ( tempidentifier.EndsWith("-") )
    tempidentifier.Remove(tempidentifier.Length()-1,1);
	
  // special treatment for special subdirectories for 03p_XX
  tempidentifier.ReplaceAll("03p_7a","03p");
  tempidentifier.ReplaceAll("03p_8a","03p");
  tempidentifier.ReplaceAll("03p_9b","03p");
  
  mergedname.Append("_");
  mergedname.Append(tempidentifier);
  TIter nexttype3(typelist);
  while ( TObjString *looptype2 = (TObjString*)nexttype3() ) {
    
    if ( mergedtitle.Contains(looptype2->GetString()) ) {
      mergedtitle.ReplaceAll(looptype2->GetString(),tempidentifier);
      break;
    }
  }

  TH1D* merged = new TH1D(*((TH1D*)histolist->First()));
  merged->Reset();
  merged->SetName(mergedname);
  merged->SetTitle(mergedtitle);
  merged->SetXTitle(((TH1D*)histolist->First())->GetXaxis()->GetTitle());
  merged->SetYTitle(((TH1D*)histolist->First())->GetYaxis()->GetTitle());
  if( label){
    // set bin labels
    Int_t bins = merged->GetNbinsX();
    for ( Int_t i = 1; i <= bins; i++)
      merged->GetXaxis()->SetBinLabel(i,((TH1D*)histolist->First())->GetXaxis()->GetBinLabel(i));
    // draw vertical labels
    merged->LabelsOption("v");
  }

  merged->Sumw2();
  
  TIter nexthisto(histolist);
  while ( TH1D* histo = (TH1D*)nexthisto() ) {
    merged->Add(histo);
  }

  merged->Write("",kOverwrite);
//   file->Save();
//   file->ReadKeys();

  histodirlist->Delete();
  delete histodirlist;
  histolist->Delete();
  delete histolist;
  typelist->Delete();
  delete typelist;
  
  if ( localdebug ) {
    cout << "end of AddHistosDataStage1" << endl;
  }
  
  return kTRUE;

}

//_____________________________________________________________

Bool_t GHistogrammer::AddHistosDataStage3(TFile *file, TString histogramname, TString option) {
  //
  // merge histograms to histogram in smallest same directory + merged directory in file
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::AddHistosDataStage3 called" << endl << endl;

  Bool_t localdebug = kFALSE;
  option.ToUpper();
  Bool_t label = kFALSE;
  option.ToUpper();
  if ( option.Contains("DEBUG") )
    localdebug = kTRUE;
  if ( option.Contains("LABEL") ) label = kTRUE;

  TList *histolist = new TList();
  TList *histodirlist = new TList();
  Int_t histonum = 0;

  // string to remember the complete period of valid data for stage 3
  TString compperiod = "";
  TString compperiodstart = "";
  TString compperiodend = "";

  TIter nextperiod(fPeriods);
  TString temp = "";
  Bool_t first = kTRUE;
  while ( TObjString *period = (TObjString*)nextperiod() ) {
    temp = "Histograms/data/merged/";
    temp.Append(histogramname);
    temp.Append("_");
    temp.Append(period->GetString());
    TH1D* histo = (TH1D*)file->Get(temp);
    if ( histo != 0 ) {
      histolist->Add(histo);
      histodirlist->Add(new TObjString(temp));
      histonum += 1;
      if ( first ) {
	compperiodstart = period->GetString();
	first = kFALSE;
      }
      compperiodend = period->GetString();
    }
  }
  compperiodstart.Remove(3,compperiodstart.Length()-3);
  compperiodend.Remove(0,4);
  compperiod = compperiodstart;
  compperiod.Append("-");
  compperiod.Append(compperiodend);

  if ( histonum == 0 ) {
    if ( localdebug ) {
      cout << "histogram name " << histogramname << " not available" <<  endl;
    }
    histodirlist->Delete();
    delete histodirlist;
    histolist->Delete();
    delete histolist;
    return kFALSE;
  }

  // check for histogram compatibility
  if ( !this->CheckHistoCompat(histolist) ) {
    cout << "Histograms are not compatible" << endl;
    histodirlist->Delete();
    delete histodirlist;
    histolist->Delete();
    delete histolist;    
    return kFALSE;
  }
  
  if ( localdebug ) {
    cout << "number of histograms: " << histonum << endl;
    TIter temp(histolist);
    while (TH1D* temphist = (TH1D*)temp() ) 
      cout << "histogram-name: " << temphist->GetName() << " histogram-title: " << temphist->GetTitle() << endl;
  }

  TString dirname = this->SameDirectory(histonum, histodirlist);
  if ( dirname.Contains(gInclude->StripLastDir(histogramname)) ) {
    dirname.ReplaceAll(gInclude->StripLastDir(histogramname),"");
    dirname = gInclude->StripLastDir(dirname);
    dirname = gInclude->StripLastDir(dirname);
  }
  if ( !dirname.EndsWith("/") )
    dirname.Append("/");
  dirname.Append("merged/");
  if ( !dirname.EndsWith("/") )
    dirname.Append("/");
  dirname.Append(gInclude->StripLastDir(histogramname));

  TDirectory *directory = gInclude->MkdirRecursiveOld(file,dirname);
  directory->cd();

  TString mergedname = gInclude->StripFirstDir(histogramname);
  TString mergedtitle = ((TH1D*)histolist->First())->GetTitle();
   
  TIter nextperiod2(fPeriods);
  while ( TObjString *period = (TObjString*)nextperiod2() ) {
    mergedtitle.ReplaceAll(period->GetString(),"");
  }
  mergedtitle.ReplaceAll("data/-","");
  mergedtitle.ReplaceAll("data/","");
  mergedtitle.Prepend(compperiod);
  mergedtitle.Prepend("data/");
  
  TH1D* merged = new TH1D(*((TH1D*)histolist->First()));
  merged->Reset();
  merged->SetName(mergedname);
  merged->SetTitle(mergedtitle);
  merged->SetXTitle(((TH1D*)histolist->First())->GetXaxis()->GetTitle());
  merged->SetYTitle(((TH1D*)histolist->First())->GetYaxis()->GetTitle());
  if(label){
    // set bin labels
    Int_t bins = merged->GetNbinsX();
    for ( Int_t i = 1; i <= bins; i++)
      merged->GetXaxis()->SetBinLabel(i,((TH1D*)histolist->First())->GetXaxis()->GetBinLabel(i));
    // draw vertical labels
    merged->LabelsOption("v");
  }
  merged->Sumw2();

  TIter nexthisto(histolist);

  while ( TH1D* histo = (TH1D*)nexthisto() ) {
    merged->Add(histo);
  }

  merged->Write("",kOverwrite);
//   file->Save();
//   file->ReadKeys();

  histodirlist->Delete();
  delete histodirlist;
  histolist->Delete();
  delete histolist;

  if ( localdebug ) {
    cout << "end of AddHistosDataStage3" << endl;
  }

  return kTRUE;

}

//_____________________________________________________________

Bool_t GHistogrammer::AddHistos2DDataStage1(TFile *file, TString type, TString histogramname, TString option) {
  //
  // merge histograms to histogram in smallest same directory + merged directory in file
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::AddHistos2DDataStage1 called" << endl << endl;

  Bool_t localdebug = kFALSE;

  option.ToUpper();
  if ( option.Contains("DEBUG") )
    localdebug = kTRUE;

  TList *histolist = new TList();
  TList *histodirlist = new TList();
  TList *typelist = new TList();
  Int_t histonum = 0;

  // separate type entries by comma
  TString temptype = type;
  char first;
  TString temp = "";
  // separate entries in types
  while ( (first = temptype(0)) ) {
    // remove first
    temptype.Remove(0,1);
    // append to temp or break in case of comma
    if ( first == 44 ) {
      typelist->Add(new TObjString(temp));
      temp = "";
    } else {
      temp.Append(first);
    }
  }
  if ( temp.Length() != 0 ) {
    typelist->Add(new TObjString(temp));
  }
  
  // fill histo list
  TIter nexttype(typelist);
  temp = "";
  while ( TObjString *looptype = (TObjString*)nexttype() ) {
    temp = "Histograms/data/";
    temp.Append(looptype->GetString());
    temp.Append("/");
    temp.Append(histogramname);
    TH2D* histo = (TH2D*)file->Get(temp);
    if ( histo != 0 ) {
      histolist->Add(histo);
      histodirlist->Add(new TObjString(temp));
      histonum += 1;
    }
  }

  if ( histonum == 0 ) {
    if ( localdebug ) {
      cout << "histogram type " << type << " name " << histogramname << " not available" <<  endl;
    }
    histodirlist->Delete();
    delete histodirlist;
    histolist->Delete();
    delete histolist;
    typelist->Delete();
    delete typelist;
    return kFALSE;
  }

  // check for histogram compatibility
  if ( !this->CheckHistoCompat(histolist) ) {
    cout << "Histograms are not compatible" << endl;
    histodirlist->Delete();
    delete histodirlist;
    histolist->Delete();
    delete histolist;
    typelist->Delete();
    delete typelist;
    return kFALSE;
  }
  
  if ( localdebug ) {
    cout << "number of histograms: " << histonum << endl;
    TIter temp2(histolist);
    while (TH2D* temphist = (TH2D*)temp2() ) 
      cout << "histogram-name: " << temphist->GetName() << " histogram-title: " << temphist->GetTitle() << endl;
  }

  TString dirname = this->SameDirectory(histonum, histodirlist);
  if ( dirname.Contains(gInclude->StripLastDir(histogramname)) ) {
    dirname.ReplaceAll(gInclude->StripLastDir(histogramname),"");
    dirname = gInclude->StripLastDir(dirname);
    dirname = gInclude->StripLastDir(dirname);
  }
  if ( !dirname.EndsWith("/") )
    dirname.Append("/");
  dirname.Append("merged/");
  if ( !dirname.EndsWith("/") )
    dirname.Append("/");
  dirname.Append(gInclude->StripLastDir(histogramname));
  TDirectory *directory = gInclude->MkdirRecursiveOld(file,dirname);
  directory->cd();

  TString mergedname = gInclude->StripFirstDir(histogramname);
  TString mergedtitle = ((TH2D*)histolist->First())->GetTitle();
   
  TString tempidentifier = "";
  TIter nexttype2(typelist);
  while ( TObjString *looptype = (TObjString*)nexttype2() ) {
    tempidentifier.Append(looptype->GetString());
    tempidentifier.Append("-");
  }
  if ( tempidentifier.EndsWith("-") )
    tempidentifier.Remove(tempidentifier.Length()-1,1);
	
  // special treatment for special subdirectories for 03p_XX
  tempidentifier.ReplaceAll("03p_7a","03p");
  tempidentifier.ReplaceAll("03p_8a","03p");
  tempidentifier.ReplaceAll("03p_9b","03p");
  
  mergedname.Append("_");
  mergedname.Append(tempidentifier);
  TIter nexttype3(typelist);
  while ( TObjString *looptype2 = (TObjString*)nexttype3() ) {
    
    if ( mergedtitle.Contains(looptype2->GetString()) ) {
      mergedtitle.ReplaceAll(looptype2->GetString(),tempidentifier);
      break;
    }
  }

  TH2D* merged = new TH2D(*((TH2D*)histolist->First()));
  merged->Reset();
  merged->SetName(mergedname);
  merged->SetTitle(mergedtitle);
  merged->SetXTitle(((TH2D*)histolist->First())->GetXaxis()->GetTitle());
  merged->SetYTitle(((TH2D*)histolist->First())->GetYaxis()->GetTitle());
  merged->Sumw2();
  
  TIter nexthisto(histolist);
  while ( TH2D* histo = (TH2D*)nexthisto() ) {
    merged->Add(histo);
  }

  merged->Write("",kOverwrite);
//   file->Save();
//   file->ReadKeys();

  histodirlist->Delete();
  delete histodirlist;
  histolist->Delete();
  delete histolist;
  typelist->Delete();
  delete typelist;
  
  if ( localdebug ) {
    cout << "end of AddHistos2DDataStage1" << endl;
  }
  
  return kTRUE;

}

//_____________________________________________________________

Bool_t GHistogrammer::AddHistos2DDataStage3(TFile *file, TString histogramname, TString option) {
  //
  // merge histograms to histogram in smallest same directory + merged directory in file
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::AddHistos2DDataStage3 called" << endl << endl;

  Bool_t localdebug = kFALSE;

  option.ToUpper();
  if ( option.Contains("DEBUG") )
    localdebug = kTRUE;

  TList *histolist = new TList();
  TList *histodirlist = new TList();
  Int_t histonum = 0;

  // string to remember the complete period of valid data for stage 3
  TString compperiod = "";
  TString compperiodstart = "";
  TString compperiodend = "";

  TIter nextperiod(fPeriods);
  TString temp = "";
  Bool_t first = kTRUE;
  while ( TObjString *period = (TObjString*)nextperiod() ) {
    temp = "Histograms/data/merged/";
    temp.Append(histogramname);
    temp.Append("_");
    temp.Append(period->GetString());
    TH2D* histo = (TH2D*)file->Get(temp);
    if ( histo != 0 ) {
      histolist->Add(histo);
      histodirlist->Add(new TObjString(temp));
      histonum += 1;
      if ( first ) {
	compperiodstart = period->GetString();
	first = kFALSE;
      }
      compperiodend = period->GetString();
    }
  }
  compperiodstart.Remove(3,compperiodstart.Length()-3);
  compperiodend.Remove(0,4);
  compperiod = compperiodstart;
  compperiod.Append("-");
  compperiod.Append(compperiodend);

  if ( histonum == 0 ) {
    if ( localdebug ) {
      cout << "histogram name " << histogramname << " not available" <<  endl;
    }
    histodirlist->Delete();
    delete histodirlist;
    histolist->Delete();
    delete histolist;
    return kFALSE;
  }

  // check for histogram compatibility
  if ( !this->CheckHistoCompat(histolist) ) {
    cout << "Histograms are not compatible" << endl;
    histodirlist->Delete();
    delete histodirlist;
    histolist->Delete();
    delete histolist;
    return kFALSE;
  }
  
  if ( localdebug ) {
    cout << "number of histograms: " << histonum << endl;
    TIter temp(histolist);
    while (TH2D* temphist = (TH2D*)temp() ) 
      cout << "histogram-name: " << temphist->GetName() << " histogram-title: " << temphist->GetTitle() << endl;
  }

  TString dirname = this->SameDirectory(histonum, histodirlist);
  if ( dirname.Contains(gInclude->StripLastDir(histogramname)) ) {
    dirname.ReplaceAll(gInclude->StripLastDir(histogramname),"");
    dirname = gInclude->StripLastDir(dirname);
    dirname = gInclude->StripLastDir(dirname);
  }
  if ( !dirname.EndsWith("/") )
    dirname.Append("/");
  dirname.Append("merged/");
  if ( !dirname.EndsWith("/") )
    dirname.Append("/");
  dirname.Append(gInclude->StripLastDir(histogramname));

  TDirectory *directory = gInclude->MkdirRecursiveOld(file,dirname);
  directory->cd();

  TString mergedname = gInclude->StripFirstDir(histogramname);
  TString mergedtitle = ((TH2D*)histolist->First())->GetTitle();
   
  TIter nextperiod2(fPeriods);
  while ( TObjString *period = (TObjString*)nextperiod2() ) {
    mergedtitle.ReplaceAll(period->GetString(),"");
  }
  mergedtitle.ReplaceAll("data/-","");
  mergedtitle.ReplaceAll("data/","");
  mergedtitle.Prepend(compperiod);
  mergedtitle.Prepend("data/");
  
  TH2D* merged = new TH2D(*((TH2D*)histolist->First()));
  merged->Reset();
  merged->SetName(mergedname);
  merged->SetTitle(mergedtitle);
  merged->SetXTitle(((TH2D*)histolist->First())->GetXaxis()->GetTitle());
  merged->SetYTitle(((TH2D*)histolist->First())->GetYaxis()->GetTitle());
  merged->Sumw2();

  TIter nexthisto(histolist);

  while ( TH2D* histo = (TH2D*)nexthisto() ) {
    merged->Add(histo);
  }

  merged->Write("",kOverwrite);
//   file->Save();
//   file->ReadKeys();

  histodirlist->Delete();
  delete histodirlist;
  histolist->Delete();
  delete histolist;

  if ( localdebug ) {
    cout << "end of AddHistos2DDataStage3" << endl;
  }

  return kTRUE;

}

//_____________________________________________________________

Bool_t GHistogrammer::AddHistosMCStage1(TFile *file, TString type, TString period, TString histogramname, TString option) {
  //
  // merge histograms to histogram in smallest same directory + merged directory in file
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::AddHistosMCStage1 called" << endl << endl;

  Bool_t localdebug = kFALSE;
  option.ToUpper();
  Bool_t label = kFALSE;
  option.ToUpper();
  if ( option.Contains("DEBUG") )
    localdebug = kTRUE;
  if ( option.Contains("LABEL") ) label = kTRUE;

  TList *histolist = new TList();
  TList *histodirlist = new TList();
  Int_t histonum = 0;

  TIter nextsubdir(fSubdirs);
  TString temp = "";
  while ( TObjString *subdir = (TObjString*)nextsubdir() ) {
    temp = "Histograms/mc/";
    temp.Append(period);
    temp.Append("/");
    temp.Append(type);
    temp.Append("/");
    temp.Append(subdir->GetString());
    temp.Append("/");
    temp.Append(histogramname);
    TH1D* histo = (TH1D*)file->Get(temp);
    if ( histo != 0 ) {
      histolist->Add(histo);
      histodirlist->Add(new TObjString(temp));
      histonum += 1;
    }
  }

  if ( histonum == 0 ) {
    if ( localdebug ) {
      cout << "histogram type " << type << " period " << period << " name " << histogramname << " not available" <<  endl;
    }
    histodirlist->Delete();
    delete histodirlist;
    histolist->Delete();
    delete histolist;   
    return kFALSE;
  }

  // check for histogram compatibility
  if ( !this->CheckHistoCompat(histolist) ) {
    cout << "Histograms are not compatible" << endl;
    histodirlist->Delete();
    delete histodirlist;
    histolist->Delete();
    delete histolist;
    return kFALSE;
  }
  
  if ( localdebug ) {
    cout << "number of histograms: " << histonum << endl;
    TIter temp(histolist);
    while (TH1D* temphist = (TH1D*)temp() ) 
      cout << "histogram-name: " << temphist->GetName() << " histogram-title: " << temphist->GetTitle() << endl;
  }

  TString dirname = this->SameDirectory(histonum, histodirlist);

  if ( dirname.Contains(gInclude->StripLastDir(histogramname)) ) {
    dirname.ReplaceAll(gInclude->StripLastDir(histogramname),"");
    dirname = gInclude->StripLastDir(dirname);
    dirname = gInclude->StripLastDir(dirname);
  }
  if ( !dirname.EndsWith("/") )
    dirname.Append("/");
  dirname.Append("merged/");
  if ( !dirname.EndsWith("/") )
    dirname.Append("/");
  dirname.Append(gInclude->StripLastDir(histogramname));

  TDirectory *directory = gInclude->MkdirRecursiveOld(file,dirname);
  directory->cd();

  TString mergedname = gInclude->StripFirstDir(histogramname);
  TString mergedtitle = ((TH1D*)histolist->First())->GetTitle();

  // clean subdirectories in title
  TIter nextsubdir2(fSubdirs);
  while ( TObjString *dir = (TObjString*)nextsubdir2() ) {
    TString temp = dir->GetString();
    temp.Prepend("/");
    mergedtitle.ReplaceAll(temp,"");
  }
  
  TH1D* merged = new TH1D(*((TH1D*)histolist->First()));
  merged->Reset();
  merged->SetName(mergedname);
  merged->SetTitle(mergedtitle);
  merged->SetXTitle(((TH1D*)histolist->First())->GetXaxis()->GetTitle());
  merged->SetYTitle(((TH1D*)histolist->First())->GetYaxis()->GetTitle());
  if(label){
    // set bin labels
    Int_t bins = merged->GetNbinsX();
    for ( Int_t i = 1; i <= bins; i++)
      merged->GetXaxis()->SetBinLabel(i,((TH1D*)histolist->First())->GetXaxis()->GetBinLabel(i));
    // draw vertical labels
    merged->LabelsOption("v");
  }
  merged->Sumw2();

  // global scale
  Double_t globalscale = GetGlobalScale(file,period,"");

  TIter nexthisto(histolist);

  while ( TH1D* histo = (TH1D*)nexthisto() ) {
    if ( (globalscale <= 0.0) || option.Contains("UNWEIGHTED") ) {
      merged->Add(histo);
    } else {
      Double_t lumi = gInclude->GetLumi(file,histo->GetTitle());
      // fix for dir1, dir2, res1, res2 sample addition
      // they are not disjunctive samples, so they have to be treated differently
      TString title = histo->GetTitle();
      if ( title.Contains("dir1") ) {
	TIter tempnexthisto(histolist);
	while ( TH1D* temphist = (TH1D*)tempnexthisto() ) {
	  TString temptitle = temphist->GetTitle();
	  if ( temptitle.Contains("dir2") ) {
	    Double_t lumi2 = gInclude->GetLumi(file,temphist->GetTitle());
	    Double_t new_lumi = lumi+lumi2;
	    if ( localdebug ) {
	      cout << "special lf mode for dir1" << endl;
	      cout << "lumi for dir1: " << lumi << endl;
	      cout << "lumi for dir2: " << lumi2 << endl;
	      cout << "new lumi     : " << new_lumi << endl;
	    }
	    lumi = new_lumi;
	  }
	}
      } else if ( title.Contains("dir2") ) {
	TIter tempnexthisto(histolist);
	while ( TH1D* temphist = (TH1D*)tempnexthisto() ) {
	  TString temptitle = temphist->GetTitle();
	  if ( temptitle.Contains("dir1") ) {
	    Double_t lumi2 = gInclude->GetLumi(file,temphist->GetTitle());
	    Double_t new_lumi = lumi+lumi2;
	    if ( localdebug ) {
	      cout << "special lf mode for dir2" << endl;
	      cout << "lumi for dir2: " << lumi << endl;
	      cout << "lumi for dir1: " << lumi2 << endl;
	      cout << "new lumi     : " << new_lumi << endl;
	    }
	    lumi = new_lumi;
	  }
	}
      } else if ( title.Contains("res1") ) {
	TIter tempnexthisto(histolist);
	while ( TH1D* temphist = (TH1D*)tempnexthisto() ) {
	  TString temptitle = temphist->GetTitle();
	  if ( temptitle.Contains("res2") ) {
	    Double_t lumi2 = gInclude->GetLumi(file,temphist->GetTitle());
	    Double_t new_lumi = lumi+lumi2;
	    if ( localdebug ) {
	      cout << "special lf mode for res1" << endl;
	      cout << "lumi for res1: " << lumi << endl;
	      cout << "lumi for res2: " << lumi2 << endl;
	      cout << "new lumi     : " << new_lumi << endl;
	    }
	    lumi = new_lumi;
	  }
	}
      } else if ( title.Contains("res2") ) {
	TIter tempnexthisto(histolist);
	while ( TH1D* temphist = (TH1D*)tempnexthisto() ) {
	  TString temptitle = temphist->GetTitle();
	  if ( temptitle.Contains("res1") ) {
	    Double_t lumi2 = gInclude->GetLumi(file,temphist->GetTitle());
	    Double_t new_lumi = lumi+lumi2;
	    if ( localdebug ) {
	      cout << "special lf mode for res2" << endl;
	      cout << "lumi for res2: " << lumi << endl;
	      cout << "lumi for res1: " << lumi2 << endl;
	      cout << "new lumi     : " << new_lumi << endl;
	    }
	    lumi = new_lumi;
	  }
	}
      } 
      if ( localdebug ) {
	cout << "globalscale: " << globalscale << endl;
	cout << "lumi: " << lumi << endl;
      }
      merged->Add(histo,globalscale/lumi);
      
    }
  }

  merged->Write("",kOverwrite);
//   file->Save();
//   file->ReadKeys();

  histodirlist->Delete();
  delete histodirlist;
  histolist->Delete();
  delete histolist;

  if ( localdebug ) {
    cout << "end of AddHistosMCStage1" << endl;
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GHistogrammer::CopyHistosMCStage1(TFile *file, TString type, TString period, TString histogramname, TString option) {
  //
  // copy histograms to histogram in smallest same directory + merged directory in file
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::CopyHistosMCStage1 called" << endl << endl;

    Bool_t localdebug = kFALSE;
  option.ToUpper();
  Bool_t label = kFALSE;
  option.ToUpper();
  if ( option.Contains("DEBUG") )
    localdebug = kTRUE;
  if ( option.Contains("LABEL") ) label = kTRUE;

  TList *histolist = new TList();
  TList *histodirlist = new TList();
  Int_t histonum = 0;

  TIter nextsubdir(fSubdirs);
  TString temp = "";
  while ( TObjString *subdir = (TObjString*)nextsubdir() ) {
    temp = "Histograms/mc/";
    temp.Append(period);
    temp.Append("/");
    temp.Append(type);
    temp.Append("/");
    temp.Append(subdir->GetString());
    temp.Append("/");
    temp.Append(histogramname);
    TH1D* histo = (TH1D*)file->Get(temp);
    if ( histo != 0 ) {
      histolist->Add(histo);
      histodirlist->Add(new TObjString(temp));
      histonum += 1;
    }
  }

  if ( histonum == 0 ) {
    if ( localdebug ) {
      cout << "histogram type " << type << " period " << period << " name " << histogramname << " not available" <<  endl;
    }
    histodirlist->Delete();
    delete histodirlist;
    histolist->Delete();
    delete histolist;
    return kFALSE;
  }

  if ( localdebug ) {
    cout << "number of histograms: " << histonum << endl;
    TIter temp(histolist);
    while (TH1D* temphist = (TH1D*)temp() ) 
      cout << "histogram-name: " << temphist->GetName() << " histogram-title: " << temphist->GetTitle() << endl;
  }

  TString dirname = this->SameDirectory(histonum, histodirlist);

  if ( dirname.Contains(gInclude->StripLastDir(histogramname)) ) {
    dirname.ReplaceAll(gInclude->StripLastDir(histogramname),"");
    dirname = gInclude->StripLastDir(dirname);
    dirname = gInclude->StripLastDir(dirname);
  }
  if ( !dirname.EndsWith("/") )
    dirname.Append("/");
  dirname.Append("merged/");
  if ( !dirname.EndsWith("/") )
    dirname.Append("/");
  dirname.Append(gInclude->StripLastDir(histogramname));

  TDirectory *directory = gInclude->MkdirRecursiveOld(file,dirname);
  directory->cd();

  TString mergedname = gInclude->StripFirstDir(histogramname);
  TString mergedtitle = ((TH1D*)histolist->First())->GetTitle();

  // clean subdirectories in title
  TIter nextsubdir2(fSubdirs);
  while ( TObjString *dir = (TObjString*)nextsubdir2() ) {
    TString temp = dir->GetString();
    temp.Prepend("/");
    mergedtitle.ReplaceAll(temp,"");
  }
  
  TH1D* merged = new TH1D(*((TH1D*)histolist->First()));
  merged->Reset();
  merged->SetName(mergedname);
  merged->SetTitle(mergedtitle);
  merged->SetXTitle(((TH1D*)histolist->First())->GetXaxis()->GetTitle());
  merged->SetYTitle(((TH1D*)histolist->First())->GetYaxis()->GetTitle());
  if(label){
    // set bin labels
    Int_t bins = merged->GetNbinsX();
    for ( Int_t i = 1; i <= bins; i++)
      merged->GetXaxis()->SetBinLabel(i,((TH1D*)histolist->First())->GetXaxis()->GetBinLabel(i));
    // draw vertical labels
    merged->LabelsOption("v");
  }
  merged->Sumw2();

  merged->Add((TH1D*)histolist->First());

  merged->Write("",kOverwrite);
//   file->Save();
//   file->ReadKeys();

  histodirlist->Delete();
  delete histodirlist;
  histolist->Delete();
  delete histolist;

  if ( localdebug ) {
    cout << "end of CopyHistosMCStage1" << endl;
  }

  return kTRUE;

}

//_____________________________________________________________

Bool_t GHistogrammer::AddHistosMCStage2(TFile *file, TString type, TString period, TString histogramname, TString option) {
  //
  // merge histograms to histogram in smallest same directory + merged directory in file
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::AddHistosMCStage2 called" << endl << endl;

  Bool_t localdebug = kFALSE;
  option.ToUpper();
  Bool_t label = kFALSE;
  option.ToUpper();
  if ( option.Contains("DEBUG") )
    localdebug = kTRUE;
  if ( option.Contains("LABEL") ) label = kTRUE;

  TList *histolist = new TList();
  TList *histodirlist = new TList();
  TList *typelist = new TList();
  Int_t histonum = 0;
  Int_t typenum = 0;

  // fill typelist
  TString temptype = type;

  char first;
  TString temp = "";
  // separate entries in types
  while ( (first = temptype(0)) ) {
    // remove first
    temptype.Remove(0,1);
    // append to temp or break in case of comma
    if ( first == 44 ) {
      typelist->Add(new TObjString(temp));
      ++typenum;
      temp = "";
    } else {
      temp.Append(first);
    }
  }
  if ( temp.Length() != 0 ) {
    typelist->Add(new TObjString(temp));
    ++typenum;
  }

  // fill histo list
  TIter nexttype(typelist);
  temp = "";
  while ( TObjString *looptype = (TObjString*)nexttype() ) {
    temp = "Histograms/mc/";
    temp.Append(period);
    temp.Append("/");
    temp.Append(looptype->GetString());
    temp.Append("/merged/");
    temp.Append(histogramname);
    TH1D* histo = (TH1D*)file->Get(temp);
    if ( histo != 0 ) {
      histolist->Add(histo);
      histodirlist->Add(new TObjString(temp));
      histonum += 1;
    }
  }

  if ( histonum < typenum ) {
    if ( localdebug ) {
      cout << "histogram type " << type << " period " << period << " name " << histogramname << " not available" <<  endl;
    }
    histodirlist->Delete();
    delete histodirlist;
    histolist->Delete();
    delete histolist;
    typelist->Delete();
    delete typelist;
    return kFALSE;
  }

  // check for histogram compatibility
  if ( !this->CheckHistoCompat(histolist) ) {
    cout << "Histograms are not compatible" << endl;
    histodirlist->Delete();
    delete histodirlist;
    histolist->Delete();
    delete histolist;
    typelist->Delete();
    delete typelist;
    return kFALSE;
  }
  
  if ( localdebug ) {
    cout << "number of histograms: " << histonum << endl;
    TIter temp(histolist);
    while (TH1D* temphist = (TH1D*)temp() ) 
      cout << "histogram-name: " << temphist->GetName() << " histogram-title: " << temphist->GetTitle() << endl;
  }

  TString dirname = this->SameDirectory(histonum, histodirlist);

  if ( dirname.Contains(gInclude->StripLastDir(histogramname)) ) {
    dirname.ReplaceAll(gInclude->StripLastDir(histogramname),"");
    dirname = gInclude->StripLastDir(dirname);
    dirname = gInclude->StripLastDir(dirname);
  }
  if ( !dirname.EndsWith("/") )
    dirname.Append("/");
  dirname.Append("merged/");
  if ( !dirname.EndsWith("/") )
    dirname.Append("/");
  dirname.Append(gInclude->StripLastDir(histogramname));

  TDirectory *directory = gInclude->MkdirRecursiveOld(file,dirname);
  directory->cd();

  TString mergedname = gInclude->StripFirstDir(histogramname);
  TString mergedtitle = ((TH1D*)histolist->First())->GetTitle();
  mergedtitle.Append(" for");
  // append to name the different comma separated types
  TIter nexttype2(typelist);
  while ( TObjString *looptype = (TObjString*)nexttype2() ) {
    mergedname.Append("_");
    mergedname.Append(looptype->GetString());
    mergedtitle.Append(" ");
    mergedtitle.Append(looptype->GetString());
  }
  
  // clean types in title
  TIter nexttype3(fTypes);
  while ( TObjString *looptype = (TObjString*)nexttype3() ) {
    TString temp = looptype->GetString();
    temp.Prepend("/");
    mergedtitle.ReplaceAll(temp,"");
  }
  
  TH1D* merged = new TH1D(*((TH1D*)histolist->First()));
  merged->Reset();
  merged->SetName(mergedname);
  merged->SetTitle(mergedtitle);
  merged->SetXTitle(((TH1D*)histolist->First())->GetXaxis()->GetTitle());
  merged->SetYTitle(((TH1D*)histolist->First())->GetYaxis()->GetTitle());
  if(label){
    // set bin labels
    Int_t bins = merged->GetNbinsX();
    for ( Int_t i = 1; i <= bins; i++)
      merged->GetXaxis()->SetBinLabel(i,((TH1D*)histolist->First())->GetXaxis()->GetBinLabel(i));
    // draw vertical labels
    merged->LabelsOption("v");
  }
  merged->Sumw2();

  TIter nexthisto(histolist);

  while ( TH1D* histo = (TH1D*)nexthisto() ) {
    merged->Add(histo);
  }

  merged->Write("",kOverwrite);
//   file->Save();
//   file->ReadKeys();

  histodirlist->Delete();
  delete histodirlist;
  histolist->Delete();
  delete histolist;
  typelist->Delete();
  delete typelist;

  if ( localdebug ) {
    cout << "end of AddHistosMCStage2" << endl;
  }

  return kTRUE;

}

//_____________________________________________________________

Bool_t GHistogrammer::AddHistosMCStage3(TFile *file, TString type, TString histogramname, TString option) {
  //
  // merge histograms to histogram in smallest same directory + merged directory in file
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::AddHistosMCStage3 called" << endl << endl;

  Bool_t localdebug = kFALSE;
  option.ToUpper();
  Bool_t label = kFALSE;
  option.ToUpper();
  if ( option.Contains("DEBUG") )
    localdebug = kTRUE;
  if ( option.Contains("LABEL") ) label = kTRUE;

  TList *histolist = new TList();
  TList *histodirlist = new TList();
  vector<Double_t> lumi;
  Double_t totalLumi = 0.0;
  Int_t histonum = 0;

  // fill histo list
  TIter nextperiod(fPeriods);
  TString temp = "";
  while ( TObjString *period = (TObjString*)nextperiod() ) {
    temp = "Histograms/mc/";
    temp.Append(period->GetString());
    temp.Append("/");
    temp.Append(type);
    temp.Append("/merged/");
    temp.Append(histogramname);
    TH1D* histo = (TH1D*)file->Get(temp);
    if ( histo != 0 ) {
      histolist->Add(histo);
      histodirlist->Add(new TObjString(temp));
      histonum += 1;
      lumi.push_back(GetGlobalScale(file,period->GetString(),""));
      totalLumi += lumi[histonum-1];
    }
  }

  if ( histonum == 0 ) {
    if ( localdebug ) {
      cout << "histogram type " << type << " name " << histogramname << " not available" <<  endl;
    }
    histodirlist->Delete();
    delete histodirlist;
    histolist->Delete();
    delete histolist;
    return kFALSE;
  }

  // check for histogram compatibility
  if ( !this->CheckHistoCompat(histolist) ) {
    cout << "Histograms are not compatible" << endl;
    histodirlist->Delete();
    delete histodirlist;
    histolist->Delete();
    delete histolist;
    return kFALSE;
  }
  
  if ( localdebug ) {
    cout << "number of histograms: " << histonum << endl;
    TIter temp(histolist);
    while (TH1D* temphist = (TH1D*)temp() ) 
      cout << "histogram-name: " << temphist->GetName() << " histogram-title: " << temphist->GetTitle() << endl;
  }

  TString dirname = this->SameDirectory(histonum, histodirlist);

  if ( histonum > 1 ) {

    if ( dirname.Contains(gInclude->StripLastDir(histogramname)) ) {
      dirname.ReplaceAll(gInclude->StripLastDir(histogramname),"");
      dirname = gInclude->StripLastDir(dirname);
      dirname = gInclude->StripLastDir(dirname);
    }
    if ( !dirname.EndsWith("/") )
      dirname.Append("/");
    dirname.Append("merged/");
    if ( !dirname.EndsWith("/") )
      dirname.Append("/");
    dirname.Append(type);
    dirname.Append("/");
    dirname.Append(gInclude->StripLastDir(histogramname));

  } else {

    dirname = "Histograms/mc/merged/";
    dirname.Append(type);
    dirname.Append("/");
    dirname.Append(gInclude->StripLastDir(histogramname));

  }

  TDirectory *directory = gInclude->MkdirRecursiveOld(file,dirname);
  directory->cd();

  TString mergedname = gInclude->StripFirstDir(histogramname);
  TString mergedtitle = ((TH1D*)histolist->First())->GetTitle();

//   mergedtitle.ReplaceAll(type,"");
  TIter nextperiod2(fPeriods);
  while ( TObjString *period = (TObjString*)nextperiod2() ) {
    mergedtitle.ReplaceAll(period->GetString(),"");
  }
  mergedtitle.ReplaceAll("/-","/");
  mergedtitle.ReplaceAll("//","/");
  mergedtitle.ReplaceAll("//","/");
  
  TH1D* merged = new TH1D(*((TH1D*)histolist->First()));
  merged->Reset();
  merged->SetName(mergedname);
  merged->SetTitle(mergedtitle);
  merged->SetXTitle(((TH1D*)histolist->First())->GetXaxis()->GetTitle());
  merged->SetYTitle(((TH1D*)histolist->First())->GetYaxis()->GetTitle());
  if(label){
    // set bin labels
    Int_t bins = merged->GetNbinsX();
    for ( Int_t i = 1; i <= bins; i++)
      merged->GetXaxis()->SetBinLabel(i,((TH1D*)histolist->First())->GetXaxis()->GetBinLabel(i));
    // draw vertical labels
    merged->LabelsOption("v");
  }
  merged->Sumw2();
  
  TIter nexthisto(histolist);
  Int_t counter = 0;
  while ( TH1D* histo = (TH1D*)nexthisto() ) {
    if ( option.Contains("UNWEIGHTED") ) {
      merged->Add(histo);
    } else {
      if ( localdebug ) {
	cout << "globalscale: " << totalLumi << endl;
	cout << "lumi: " << lumi[counter] << endl;
      }
      merged->Add(histo,totalLumi/lumi[counter++]);
    }
  }
  
  merged->Write("",kOverwrite);
//   file->Save();
//   file->ReadKeys();

  histodirlist->Delete();
  delete histodirlist;
  histolist->Delete();
  delete histolist;
  
  if ( localdebug ) {
    cout << "end of AddHistosMCStage3" << endl;
  }
  
  return kTRUE;
  
}

//_____________________________________________________________

Bool_t GHistogrammer::CopyHistosMCStage3(TFile *file, TString type, TString histogramname, TString option) {
  //
  // copy histograms to histogram in smallest same directory + merged directory in file
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::CopyHistosMCStage3 called" << endl << endl;

  Bool_t localdebug = kFALSE;
  option.ToUpper();
  Bool_t label = kFALSE;
  option.ToUpper();
  if ( option.Contains("DEBUG") )
    localdebug = kTRUE;
  if ( option.Contains("LABEL") ) label = kTRUE;

  TList *histolist = new TList();
  TList *histodirlist = new TList();
  vector<Double_t> lumi;
  Double_t totalLumi = 0.0;
  Int_t histonum = 0;

  // fill histo list
  TIter nextperiod(fPeriods);
  TString temp = "";
  while ( TObjString *period = (TObjString*)nextperiod() ) {
    temp = "Histograms/mc/";
    temp.Append(period->GetString());
    temp.Append("/");
    temp.Append(type);
    temp.Append("/merged/");
    temp.Append(histogramname);
    TH1D* histo = (TH1D*)file->Get(temp);
    if ( histo != 0 ) {
      histolist->Add(histo);
      histodirlist->Add(new TObjString(temp));
      histonum += 1;
      lumi.push_back(GetGlobalScale(file,period->GetString(),""));
      totalLumi += lumi[histonum-1];
    }
  }

  if ( histonum == 0 ) {
    if ( localdebug ) {
      cout << "histogram type " << type << " name " << histogramname << " not available" <<  endl;
    }
    histodirlist->Delete();
    delete histodirlist;
    histolist->Delete();
    delete histolist;
    return kFALSE;
  }

  if ( localdebug ) {
    cout << "number of histograms: " << histonum << endl;
    TIter temp(histolist);
    while (TH1D* temphist = (TH1D*)temp() ) 
      cout << "histogram-name: " << temphist->GetName() << " histogram-title: " << temphist->GetTitle() << endl;
  }

  TString dirname = this->SameDirectory(histonum, histodirlist);

  if ( histonum > 1 ) {

    if ( dirname.Contains(gInclude->StripLastDir(histogramname)) ) {
      dirname.ReplaceAll(gInclude->StripLastDir(histogramname),"");
      dirname = gInclude->StripLastDir(dirname);
      dirname = gInclude->StripLastDir(dirname);
    }
    if ( !dirname.EndsWith("/") )
      dirname.Append("/");
    dirname.Append("merged/");
    if ( !dirname.EndsWith("/") )
      dirname.Append("/");
    dirname.Append(type);
    dirname.Append("/");
    dirname.Append(gInclude->StripLastDir(histogramname));

  } else {

    dirname = "Histograms/mc/merged/";
    dirname.Append(type);
    dirname.Append("/");
    dirname.Append(gInclude->StripLastDir(histogramname));

  }

  TDirectory *directory = gInclude->MkdirRecursiveOld(file,dirname);
  directory->cd();

  TString mergedname = gInclude->StripFirstDir(histogramname);
  TString mergedtitle = ((TH1D*)histolist->First())->GetTitle();

//   mergedtitle.ReplaceAll(type,"");
  TIter nextperiod2(fPeriods);
  while ( TObjString *period = (TObjString*)nextperiod2() ) {
    mergedtitle.ReplaceAll(period->GetString(),"");
  }
  mergedtitle.ReplaceAll("/-","/");
  mergedtitle.ReplaceAll("//","/");
  mergedtitle.ReplaceAll("//","/");
  
  TH1D* merged = new TH1D(*((TH1D*)histolist->First()));
  merged->Reset();
  merged->SetName(mergedname);
  merged->SetTitle(mergedtitle);
  merged->SetXTitle(((TH1D*)histolist->First())->GetXaxis()->GetTitle());
  merged->SetYTitle(((TH1D*)histolist->First())->GetYaxis()->GetTitle());
  if(label){
    // set bin labels
    Int_t bins = merged->GetNbinsX();
    for ( Int_t i = 1; i <= bins; i++)
      merged->GetXaxis()->SetBinLabel(i,((TH1D*)histolist->First())->GetXaxis()->GetBinLabel(i));
    // draw vertical labels
    merged->LabelsOption("v");
  }
  merged->Sumw2();
  
  merged->Add((TH1D*)histolist->First());
  
  merged->Write("",kOverwrite);
//   file->Save();
//   file->ReadKeys();

  histodirlist->Delete();
  delete histodirlist;
  histolist->Delete();
  delete histolist;
  
  if ( localdebug ) {
    cout << "end of AddHistosMCStage3" << endl;
  }
  
  return kTRUE;
  
}

//_____________________________________________________________

Bool_t GHistogrammer::AddHistosMCStage4(TFile *file, TString type, TString histogramname, TString option) {
  //
  // merge histograms to histogram in smallest same directory + merged directory in file
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::AddHistosMCStage4 called" << endl << endl;

  Bool_t localdebug = kFALSE;
  option.ToUpper();
  Bool_t label = kFALSE;
  option.ToUpper();
  if ( option.Contains("DEBUG") )
    localdebug = kTRUE;
  if ( option.Contains("LABEL") ) label = kTRUE;

  TList *histolist = new TList();
  TList *histodirlist = new TList();
  TList *typelist = new TList();
  Int_t histonum = 0;
  Int_t typenum = 0;

  // fill typelist
  TString temptype = type;

  char first;
  TString temp = "";
  // separate entries in types
  while ( (first = temptype(0)) ) {
    // remove first
    temptype.Remove(0,1);
    // append to temp or break in case of comma
    if ( first == 44 ) {
      typelist->Add(new TObjString(temp));
      ++typenum;
      temp = "";
    } else {
      temp.Append(first);
    }
  }
  if ( temp.Length() != 0 ) {
    typelist->Add(new TObjString(temp));
    ++typenum;
  }

  // fill histo list
  TIter nexttype(typelist);
  temp = "";
  while ( TObjString *looptype = (TObjString*)nexttype() ) {
    temp = "Histograms/mc/merged/";
    temp.Append(looptype->GetString());
    temp.Append("/");
    temp.Append(histogramname);
    TH1D* histo = (TH1D*)file->Get(temp);
    if ( histo != 0 ) {
      histolist->Add(histo);
      histodirlist->Add(new TObjString(temp));
      histonum += 1;
    }
  }

  if ( histonum < typenum ) {
    if ( localdebug ) {
      cout << "histogram type " << type << " name " << histogramname << " not available" <<  endl;
    }
    histodirlist->Delete();
    delete histodirlist;
    histolist->Delete();
    delete histolist;
    typelist->Delete();
    delete typelist;
    return kFALSE;
  }

  // check for histogram compatibility
  if ( !this->CheckHistoCompat(histolist) ) {
    cout << "Histograms are not compatible" << endl;
    histodirlist->Delete();
    delete histodirlist;
    histolist->Delete();
    delete histolist;
    typelist->Delete();
    delete typelist;
    return kFALSE;
  }
  
  if ( localdebug ) {
    cout << "number of histograms: " << histonum << endl;
    TIter temp(histolist);
    while (TH1D* temphist = (TH1D*)temp() ) 
      cout << "histogram-name: " << temphist->GetName() << " histogram-title: " << temphist->GetTitle() << endl;
  }

  TString dirname = this->SameDirectory(histonum, histodirlist);

  if ( dirname.Contains(gInclude->StripLastDir(histogramname)) ) {
    dirname.ReplaceAll(gInclude->StripLastDir(histogramname),"");
    dirname = gInclude->StripLastDir(dirname);
    dirname = gInclude->StripLastDir(dirname);
  }
  if ( !dirname.EndsWith("/") )
    dirname.Append("/");
  dirname.Append("merged/");
  if ( !dirname.EndsWith("/") )
    dirname.Append("/");
  dirname.Append(gInclude->StripLastDir(histogramname));

  TDirectory *directory = gInclude->MkdirRecursiveOld(file,dirname);
  directory->cd();

  TString mergedname = gInclude->StripFirstDir(histogramname);
  TString mergedtitle = ((TH1D*)histolist->First())->GetTitle();
  mergedtitle.Append(" for");
  // append to name the different comma separated types
  TIter nexttype2(typelist);
  while ( TObjString *looptype = (TObjString*)nexttype2() ) {
    mergedname.Append("_");
    mergedname.Append(looptype->GetString());
    mergedtitle.Append(" ");
    mergedtitle.Append(looptype->GetString());
  }
  
  // clean types in title
  TIter nexttype3(fTypes);
  while ( TObjString *looptype = (TObjString*)nexttype3() ) {
    TString temp = looptype->GetString();
    temp.Prepend("/");
    mergedtitle.ReplaceAll(temp,"");
  }
  
  TH1D* merged = new TH1D(*((TH1D*)histolist->First()));
  merged->Reset();
  merged->SetName(mergedname);
  merged->SetTitle(mergedtitle);
  merged->SetXTitle(((TH1D*)histolist->First())->GetXaxis()->GetTitle());
  merged->SetYTitle(((TH1D*)histolist->First())->GetYaxis()->GetTitle());
  if(label){
    // set bin labels
    Int_t bins = merged->GetNbinsX();
    for ( Int_t i = 1; i <= bins; i++)
      merged->GetXaxis()->SetBinLabel(i,((TH1D*)histolist->First())->GetXaxis()->GetBinLabel(i));
    // draw vertical labels
    merged->LabelsOption("v");
  }
  merged->Sumw2();

  TIter nexthisto(histolist);

  while ( TH1D* histo = (TH1D*)nexthisto() ) {
    merged->Add(histo);
  }

  merged->Write("",kOverwrite);
//   file->Save();
//   file->ReadKeys();

  histodirlist->Delete();
  delete histodirlist;
  histolist->Delete();
  delete histolist;
  typelist->Delete();
  delete typelist;

  if ( localdebug ) {
    cout << "end of AddHistosMCStage4" << endl;
  }

  return kTRUE;

}

//_____________________________________________________________

Bool_t GHistogrammer::AddHistos2DMCStage1(TFile *file, TString type, TString period, TString histogramname, TString option) {
  //
  // merge histograms to histogram in smallest same directory + merged directory in file
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::AddHistos2DMCStage1 called" << endl << endl;

  Bool_t localdebug = kFALSE;

  option.ToUpper();
  if ( option.Contains("DEBUG") )
    localdebug = kTRUE;

  TList *histolist = new TList();
  TList *histodirlist = new TList();
  Int_t histonum = 0;

  TIter nextsubdir(fSubdirs);
  TString temp = "";
  while ( TObjString *subdir = (TObjString*)nextsubdir() ) {
    temp = "Histograms/mc/";
    temp.Append(period);
    temp.Append("/");
    temp.Append(type);
    temp.Append("/");
    temp.Append(subdir->GetString());
    temp.Append("/");
    temp.Append(histogramname);
    TH2D* histo = (TH2D*)file->Get(temp);
    if ( histo != 0 ) {
      histolist->Add(histo);
      histodirlist->Add(new TObjString(temp));
      histonum += 1;
    }
  }

  if ( histonum == 0 ) {
    if ( localdebug ) {
      cout << "histogram type " << type << " period " << period << " name " << histogramname << " not available" <<  endl;
    }
    histodirlist->Delete();
    delete histodirlist;
    histolist->Delete();
    delete histolist;
    return kFALSE;
  }

  // check for histogram compatibility
  if ( !this->CheckHistoCompat(histolist) ) {
    cout << "Histograms are not compatible" << endl;
    histodirlist->Delete();
    delete histodirlist;
    histolist->Delete();
    delete histolist;
    return kFALSE;
  }
  
  if ( localdebug ) {
    cout << "number of histograms: " << histonum << endl;
    TIter temp(histolist);
    while (TH2D* temphist = (TH2D*)temp() ) 
      cout << "histogram-name: " << temphist->GetName() << " histogram-title: " << temphist->GetTitle() << endl;
  }

  TString dirname = this->SameDirectory(histonum, histodirlist);

  if ( dirname.Contains(gInclude->StripLastDir(histogramname)) ) {
    dirname.ReplaceAll(gInclude->StripLastDir(histogramname),"");
    dirname = gInclude->StripLastDir(dirname);
    dirname = gInclude->StripLastDir(dirname);
  }
  if ( !dirname.EndsWith("/") )
    dirname.Append("/");
  dirname.Append("merged/");
  if ( !dirname.EndsWith("/") )
    dirname.Append("/");
  dirname.Append(gInclude->StripLastDir(histogramname));

  TDirectory *directory = gInclude->MkdirRecursiveOld(file,dirname);
  directory->cd();

  TString mergedname = gInclude->StripFirstDir(histogramname);
  TString mergedtitle = ((TH2D*)histolist->First())->GetTitle();

  // clean subdirectories in title
  TIter nextsubdir2(fSubdirs);
  while ( TObjString *dir = (TObjString*)nextsubdir2() ) {
    TString temp = dir->GetString();
    temp.Prepend("/");
    mergedtitle.ReplaceAll(temp,"");
  }
  
  TH2D* merged = new TH2D(*((TH2D*)histolist->First()));
  merged->Reset();
  merged->SetName(mergedname);
  merged->SetTitle(mergedtitle);
  merged->SetXTitle(((TH2D*)histolist->First())->GetXaxis()->GetTitle());
  merged->SetYTitle(((TH2D*)histolist->First())->GetYaxis()->GetTitle());
  merged->Sumw2();

  // global scale
  Double_t globalscale = GetGlobalScale(file,period,"");

  TIter nexthisto(histolist);

  while ( TH2D* histo = (TH2D*)nexthisto() ) {
    if ( (globalscale <= 0.0) || option.Contains("UNWEIGHTED") ) {
      merged->Add(histo);
    } else {
      if ( localdebug ) {
	cout << "globalscale: " << globalscale << endl;
	cout << "lumi: " << gInclude->GetLumi(file,histo->GetTitle()) << endl;
      }
      merged->Add(histo,globalscale/gInclude->GetLumi(file,histo->GetTitle()));
    }
  }

  merged->Write("",kOverwrite);
//   file->Save();
//   file->ReadKeys();

  histodirlist->Delete();
  delete histodirlist;
  histolist->Delete();
  delete histolist;

  if ( localdebug ) {
    cout << "end of AddHistos2DMCStage1" << endl;
  }

  return kTRUE;

}

//_____________________________________________________________

Bool_t GHistogrammer::AddHistos2DMCStage2(TFile *file, TString type, TString period, TString histogramname, TString option) {
  //
  // merge histograms to histogram in smallest same directory + merged directory in file
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::AddHistos2DMCStage2 called" << endl << endl;

  Bool_t localdebug = kFALSE;

  option.ToUpper();
  if ( option.Contains("DEBUG") )
    localdebug = kTRUE;

  TList *histolist = new TList();
  TList *histodirlist = new TList();
  TList *typelist = new TList();
  Int_t histonum = 0;
  Int_t typenum = 0;

  // fill typelist
  TString temptype = type;

  char first;
  TString temp = "";
  // separate entries in types
  while ( (first = temptype(0)) ) {
    // remove first
    temptype.Remove(0,1);
    // append to temp or break in case of comma
    if ( first == 44 ) {
      typelist->Add(new TObjString(temp));
      ++typenum;
      temp = "";
    } else {
      temp.Append(first);
    }
  }
  if ( temp.Length() != 0 ) {
    typelist->Add(new TObjString(temp));
    ++typenum;
  }

  // fill histo list
  TIter nexttype(typelist);
  temp = "";
  while ( TObjString *looptype = (TObjString*)nexttype() ) {
    temp = "Histograms/mc/";
    temp.Append(period);
    temp.Append("/");
    temp.Append(looptype->GetString());
    temp.Append("/merged/");
    temp.Append(histogramname);
    TH2D* histo = (TH2D*)file->Get(temp);
    if ( histo != 0 ) {
      histolist->Add(histo);
      histodirlist->Add(new TObjString(temp));
      histonum += 1;
    }
  }

  if ( histonum < typenum ) {
    if ( localdebug ) {
      cout << "histogram type " << type << " period " << period << " name " << histogramname << " not available" <<  endl;
    }
    histodirlist->Delete();
    delete histodirlist;
    histolist->Delete();
    delete histolist;
    typelist->Delete();
    delete typelist;
    return kFALSE;
  }

  // check for histogram compatibility
  if ( !this->CheckHistoCompat(histolist) ) {
    cout << "Histograms are not compatible" << endl;
    histodirlist->Delete();
    delete histodirlist;
    histolist->Delete();
    delete histolist;
    typelist->Delete();
    delete typelist;
    return kFALSE;
  }
  
  if ( localdebug ) {
    cout << "number of histograms: " << histonum << endl;
    TIter temp(histolist);
    while (TH2D* temphist = (TH2D*)temp() ) 
      cout << "histogram-name: " << temphist->GetName() << " histogram-title: " << temphist->GetTitle() << endl;
  }

  TString dirname = this->SameDirectory(histonum, histodirlist);

  if ( dirname.Contains(gInclude->StripLastDir(histogramname)) ) {
    dirname.ReplaceAll(gInclude->StripLastDir(histogramname),"");
    dirname = gInclude->StripLastDir(dirname);
    dirname = gInclude->StripLastDir(dirname);
  }
  if ( !dirname.EndsWith("/") )
    dirname.Append("/");
  dirname.Append("merged/");
  if ( !dirname.EndsWith("/") )
    dirname.Append("/");
  dirname.Append(gInclude->StripLastDir(histogramname));

  TDirectory *directory = gInclude->MkdirRecursiveOld(file,dirname);
  directory->cd();

  TString mergedname = gInclude->StripFirstDir(histogramname);
  TString mergedtitle = ((TH2D*)histolist->First())->GetTitle();
  mergedtitle.Append(" for");
  // append to name the different comma separated types
  TIter nexttype2(typelist);
  while ( TObjString *looptype = (TObjString*)nexttype2() ) {
    mergedname.Append("_");
    mergedname.Append(looptype->GetString());
    mergedtitle.Append(" ");
    mergedtitle.Append(looptype->GetString());
  }
  
  // clean types in title
  TIter nexttype3(fTypes);
  while ( TObjString *looptype = (TObjString*)nexttype3() ) {
    TString temp = looptype->GetString();
    temp.Prepend("/");
    mergedtitle.ReplaceAll(temp,"");
  }
  
  TH2D* merged = new TH2D(*((TH2D*)histolist->First()));
  merged->Reset();
  merged->SetName(mergedname);
  merged->SetTitle(mergedtitle);
  merged->SetXTitle(((TH2D*)histolist->First())->GetXaxis()->GetTitle());
  merged->SetYTitle(((TH2D*)histolist->First())->GetYaxis()->GetTitle());
  merged->Sumw2();

  TIter nexthisto(histolist);

  while ( TH2D* histo = (TH2D*)nexthisto() ) {
    merged->Add(histo);
  }

  merged->Write("",kOverwrite);
//   file->Save();
//   file->ReadKeys();

  histodirlist->Delete();
  delete histodirlist;
  histolist->Delete();
  delete histolist;
  typelist->Delete();
  delete typelist;

  if ( localdebug ) {
    cout << "end of AddHistos2DMCStage2" << endl;
  }

  return kTRUE;

}

//_____________________________________________________________

Bool_t GHistogrammer::AddHistos2DMCStage3(TFile *file, TString type, TString histogramname, TString option) {
  //
  // merge histograms to histogram in smallest same directory + merged directory in file
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::AddHistos2DMCStage3 called" << endl << endl;

  Bool_t localdebug = kFALSE;

  option.ToUpper();
  if ( option.Contains("DEBUG") )
    localdebug = kTRUE;

  TList *histolist = new TList();
  TList *histodirlist = new TList();
  vector<Double_t> lumi;
  Double_t totalLumi = 0.0;
  Int_t histonum = 0;

  // fill histo list
  TIter nextperiod(fPeriods);
  TString temp = "";
  while ( TObjString *period = (TObjString*)nextperiod() ) {
    temp = "Histograms/mc/";
    temp.Append(period->GetString());
    temp.Append("/");
    temp.Append(type);
    temp.Append("/merged/");
    temp.Append(histogramname);
    TH2D* histo = (TH2D*)file->Get(temp);
    if ( histo != 0 ) {
      histolist->Add(histo);
      histodirlist->Add(new TObjString(temp));
      histonum += 1;
      lumi.push_back(GetGlobalScale(file,period->GetString(),""));
      totalLumi += lumi[histonum-1];
    }
  }

  if ( histonum == 0 ) {
    if ( localdebug ) {
      cout << "histogram type " << type << " name " << histogramname << " not available" <<  endl;
    }
    histodirlist->Delete();
    delete histodirlist;
    histolist->Delete();
    delete histolist;
    return kFALSE;
  }

  // check for histogram compatibility
  if ( !this->CheckHistoCompat(histolist) ) {
    cout << "Histograms are not compatible" << endl;
    histodirlist->Delete();
    delete histodirlist;
    histolist->Delete();
    delete histolist;
    return kFALSE;
  }
  
  if ( localdebug ) {
    cout << "number of histograms: " << histonum << endl;
    TIter temp(histolist);
    while (TH2D* temphist = (TH2D*)temp() ) 
      cout << "histogram-name: " << temphist->GetName() << " histogram-title: " << temphist->GetTitle() << endl;
  }

  TString dirname = this->SameDirectory(histonum, histodirlist);

  if ( dirname.Contains(gInclude->StripLastDir(histogramname)) ) {
    dirname.ReplaceAll(gInclude->StripLastDir(histogramname),"");
    dirname = gInclude->StripLastDir(dirname);
    dirname = gInclude->StripLastDir(dirname);
  }
  if ( !dirname.EndsWith("/") )
    dirname.Append("/");
  dirname.Append("merged/");
  if ( !dirname.EndsWith("/") )
    dirname.Append("/");
  dirname.Append(type);
  dirname.Append("/");
  dirname.Append(gInclude->StripLastDir(histogramname));

  TDirectory *directory = gInclude->MkdirRecursiveOld(file,dirname);
  directory->cd();

  TString mergedname = gInclude->StripFirstDir(histogramname);
  TString mergedtitle = ((TH2D*)histolist->First())->GetTitle();

  mergedtitle.ReplaceAll(type,"");
  TIter nextperiod2(fPeriods);
  while ( TObjString *period = (TObjString*)nextperiod2() ) {
    mergedtitle.ReplaceAll(period->GetString(),"");
  }
  mergedtitle.ReplaceAll("/","");
  
  TH2D* merged = new TH2D(*((TH2D*)histolist->First()));
  merged->Reset();
  merged->SetName(mergedname);
  merged->SetTitle(mergedtitle);
  merged->SetXTitle(((TH2D*)histolist->First())->GetXaxis()->GetTitle());
  merged->SetYTitle(((TH2D*)histolist->First())->GetYaxis()->GetTitle());
  merged->Sumw2();

  TIter nexthisto(histolist);
  Int_t counter = 0;
  while ( TH2D* histo = (TH2D*)nexthisto() ) {
    if ( option.Contains("UNWEIGHTED") ) {
      merged->Add(histo);
    } else {
      if ( localdebug ) {
	cout << "globalscale: " << totalLumi << endl;
	cout << "lumi: " << lumi[counter] << endl;
      }
      merged->Add(histo,totalLumi/lumi[counter++]);
    }
  }

  merged->Write("",kOverwrite);
//   file->Save();
//   file->ReadKeys();

  histodirlist->Delete();
  delete histodirlist;
  histolist->Delete();
  delete histolist;

  if ( localdebug ) {
    cout << "end of AddHistos2DMCStage3" << endl;
  }

  return kTRUE;

}

//_____________________________________________________________

Bool_t GHistogrammer::AddHistos2DMCStage4(TFile *file, TString type, TString histogramname, TString option) {
  //
  // merge histograms to histogram in smallest same directory + merged directory in file
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::AddHistos2DMCStage4 called" << endl << endl;

  Bool_t localdebug = kFALSE;

  option.ToUpper();
  if ( option.Contains("DEBUG") )
    localdebug = kTRUE;

  TList *histolist = new TList();
  TList *histodirlist = new TList();
  TList *typelist = new TList();
  Int_t histonum = 0;
  Int_t typenum = 0;

  // fill typelist
  TString temptype = type;

  char first;
  TString temp = "";
  // separate entries in types
  while ( (first = temptype(0)) ) {
    // remove first
    temptype.Remove(0,1);
    // append to temp or break in case of comma
    if ( first == 44 ) {
      typelist->Add(new TObjString(temp));
      ++typenum;
      temp = "";
    } else {
      temp.Append(first);
    }
  }
  if ( temp.Length() != 0 ) {
    typelist->Add(new TObjString(temp));
    ++typenum;
  }

  // fill histo list
  TIter nexttype(typelist);
  temp = "";
  while ( TObjString *looptype = (TObjString*)nexttype() ) {
    temp = "Histograms/mc/merged/";
    temp.Append(looptype->GetString());
    temp.Append("/");
    temp.Append(histogramname);
    TH2D* histo = (TH2D*)file->Get(temp);
    if ( histo != 0 ) {
      histolist->Add(histo);
      histodirlist->Add(new TObjString(temp));
      histonum += 1;
    }
  }

  if ( histonum < typenum ) {
    if ( localdebug ) {
      cout << "histogram type " << type << " name " << histogramname << " not available" <<  endl;
    }
    histodirlist->Delete();
    delete histodirlist;
    histolist->Delete();
    delete histolist;
    typelist->Delete();
    delete typelist;
    return kFALSE;
  }

  // check for histogram compatibility
  if ( !this->CheckHistoCompat(histolist) ) {
    cout << "Histograms are not compatible" << endl;
    histodirlist->Delete();
    delete histodirlist;
    histolist->Delete();
    delete histolist;
    typelist->Delete();
    delete typelist;
    return kFALSE;
  }
  
  if ( localdebug ) {
    cout << "number of histograms: " << histonum << endl;
    TIter temp(histolist);
    while (TH2D* temphist = (TH2D*)temp() ) 
      cout << "histogram-name: " << temphist->GetName() << " histogram-title: " << temphist->GetTitle() << endl;
  }

  TString dirname = this->SameDirectory(histonum, histodirlist);

  if ( dirname.Contains(gInclude->StripLastDir(histogramname)) ) {
    dirname.ReplaceAll(gInclude->StripLastDir(histogramname),"");
    dirname = gInclude->StripLastDir(dirname);
    dirname = gInclude->StripLastDir(dirname);
  }
  if ( !dirname.EndsWith("/") )
    dirname.Append("/");
  dirname.Append("merged/");
  if ( !dirname.EndsWith("/") )
    dirname.Append("/");
  dirname.Append(gInclude->StripLastDir(histogramname));

  TDirectory *directory = gInclude->MkdirRecursiveOld(file,dirname);
  directory->cd();

  TString mergedname = gInclude->StripFirstDir(histogramname);
  TString mergedtitle = ((TH2D*)histolist->First())->GetTitle();
  mergedtitle.Append(" for");
  // append to name the different comma separated types
  TIter nexttype2(typelist);
  while ( TObjString *looptype = (TObjString*)nexttype2() ) {
    mergedname.Append("_");
    mergedname.Append(looptype->GetString());
    mergedtitle.Append(" ");
    mergedtitle.Append(looptype->GetString());
  }
  
  // clean types in title
  TIter nexttype3(fTypes);
  while ( TObjString *looptype = (TObjString*)nexttype3() ) {
    TString temp = looptype->GetString();
    temp.Prepend("/");
    mergedtitle.ReplaceAll(temp,"");
  }
  
  TH2D* merged = new TH2D(*((TH2D*)histolist->First()));
  merged->Reset();
  merged->SetName(mergedname);
  merged->SetTitle(mergedtitle);
  merged->SetXTitle(((TH2D*)histolist->First())->GetXaxis()->GetTitle());
  merged->SetYTitle(((TH2D*)histolist->First())->GetYaxis()->GetTitle());
  merged->Sumw2();

  TIter nexthisto(histolist);

  while ( TH2D* histo = (TH2D*)nexthisto() ) {
    merged->Add(histo);
  }

  merged->Write("",kOverwrite);
//   file->Save();
//   file->ReadKeys();

  histodirlist->Delete();
  delete histodirlist;
  histolist->Delete();
  delete histolist;
  typelist->Delete();
  delete typelist;

  if ( localdebug ) {
    cout << "end of AddHistos2DMCStage4" << endl;
  }

  return kTRUE;

}

//_____________________________________________________________

Bool_t GHistogrammer::InitLists() {
  //
  // init lists
  if ( gDebug==-1 ) cout << endl << "GInclude::InitLists called" << endl << endl;

  fTypes = new TList();
  fTypes->Add(new TObjString("b"));
  fTypes->Add(new TObjString("c"));
  fTypes->Add(new TObjString("lf"));
  fTypes->Add(new TObjString("jpsi"));
  fTypes->Add(new TObjString("psiprime"));
  fTypes->Add(new TObjString("upsilon"));
  fTypes->Add(new TObjString("bh"));
  fTypes->Add(new TObjString("instanton"));

  fPeriods = new TList();
  fPeriods->Add(new TObjString("95p"));
  fPeriods->Add(new TObjString("96p"));
  fPeriods->Add(new TObjString("97p"));
  fPeriods->Add(new TObjString("98e"));
  fPeriods->Add(new TObjString("99e"));
  fPeriods->Add(new TObjString("99p"));
  fPeriods->Add(new TObjString("00p"));
  fPeriods->Add(new TObjString("02p"));
  fPeriods->Add(new TObjString("03p"));
  fPeriods->Add(new TObjString("03p_7a"));
  fPeriods->Add(new TObjString("03p_8a"));
  fPeriods->Add(new TObjString("03p_9b"));
  fPeriods->Add(new TObjString("04p"));
  fPeriods->Add(new TObjString("05e"));
  fPeriods->Add(new TObjString("06e"));
  fPeriods->Add(new TObjString("06p"));
  fPeriods->Add(new TObjString("07p"));
  fPeriods->Add(new TObjString("96p-97p"));
  fPeriods->Add(new TObjString("98e-99e"));
  fPeriods->Add(new TObjString("99p-00p"));
  fPeriods->Add(new TObjString("03p-04p"));
  fPeriods->Add(new TObjString("03p-04p_ztt"));
  fPeriods->Add(new TObjString("05e-06e"));
  fPeriods->Add(new TObjString("06p-07p"));

  // always add the items which are partially included in other items after these items
  fSubdirs = new TList();
  fSubdirs->Add(new TObjString("gluspl"));
  fSubdirs->Add(new TObjString("dimuon_dirres"));
  fSubdirs->Add(new TObjString("dimuon_exgamma"));
  fSubdirs->Add(new TObjString("dimuon_exproton"));
  fSubdirs->Add(new TObjString("dir_2"));
  fSubdirs->Add(new TObjString("dir1"));
  fSubdirs->Add(new TObjString("dir2"));
  fSubdirs->Add(new TObjString("dirrap"));  
  fSubdirs->Add(new TObjString("res_2"));
  fSubdirs->Add(new TObjString("res1"));
  fSubdirs->Add(new TObjString("res2"));
  fSubdirs->Add(new TObjString("dir"));
  fSubdirs->Add(new TObjString("res"));
  fSubdirs->Add(new TObjString("exgamma_2"));
  fSubdirs->Add(new TObjString("exgamma"));
  fSubdirs->Add(new TObjString("exproton_2"));
  fSubdirs->Add(new TObjString("exproton"));
  fSubdirs->Add(new TObjString("inc"));
  fSubdirs->Add(new TObjString("jpsi1"));
  fSubdirs->Add(new TObjString("jpsi2"));
  fSubdirs->Add(new TObjString("jpsi3"));
  fSubdirs->Add(new TObjString("jpsi4"));
  fSubdirs->Add(new TObjString("jpsi5"));
  fSubdirs->Add(new TObjString("jpsi6"));
  fSubdirs->Add(new TObjString("jpsi7"));
  fSubdirs->Add(new TObjString("jpsi8"));
  fSubdirs->Add(new TObjString("jpsi9"));
  fSubdirs->Add(new TObjString("jpsia"));
  fSubdirs->Add(new TObjString("jpsib"));
  fSubdirs->Add(new TObjString("jpsic"));
  fSubdirs->Add(new TObjString("jpsid"));
  fSubdirs->Add(new TObjString("all"));
  fSubdirs->Add(new TObjString("psi2"));
  fSubdirs->Add(new TObjString("1s_dir"));
  fSubdirs->Add(new TObjString("2s_dir"));
  fSubdirs->Add(new TObjString("3s_dis"));
  fSubdirs->Add(new TObjString("elastic"));
  fSubdirs->Add(new TObjString("inelastic"));
  fSubdirs->Add(new TObjString("DIS"));
  fSubdirs->Add(new TObjString("inst1"));

  return kTRUE;
}

//_____________________________________________________________

TH1D* GHistogrammer::CopyPtRelCorrection(TString dir, TH1D *histo, Double_t weight) {
  //
  // copy PtRel correction histogram to dir, apply weight
  if ( gDebug==-1 ) cout << endl << "GHistogrammer::CopyPtRelCorrection called" << endl << endl;


  // if not already created, create directory
  if ( !fDirGeneral->FindObject(dir) )
    fDirGeneral->mkdir(dir,dir);

  fDirGeneral->cd(dir);

  TH1D *dummy = gInclude->CloneHistoWithWeight(histo,weight);

  return dummy;
}

//_____________________________________________________________

TH1D* GHistogrammer::PlusMinusErrorPerBin(TH1D* input, Bool_t plus) {
  //
  // clone input
  // add or subtract (plus = kFALSE) error from bin content per bin

  TH1D *returny = (TH1D*)input->Clone();

  for ( Int_t i = 1; i <= returny->GetNbinsX(); ++i ) {
    if ( plus ) {
      returny->SetBinContent(i,(returny->GetBinContent(i)+returny->GetBinError(i)));
    } else {
      returny->SetBinContent(i,(returny->GetBinContent(i)-returny->GetBinError(i)));
    }
  }

  return returny;

}
