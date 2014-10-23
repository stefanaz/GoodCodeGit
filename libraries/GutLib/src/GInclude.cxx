//
// GInclude.cxx
//
// $Author: gutsche $
// $Date: 2005/02/18 12:07:42 $
// $Revision: 1.41 $
//

#include <GInclude.h>

#ifndef GUT_GPictureMaker
#include <GPictureMaker.h>
#endif

#ifndef __CINT__
ClassImp(GInclude)
#endif

  GInclude *gInclude = 0;

//_____________________________________________________________
// GInclude
//
// dummy class for general includes
//
GInclude::GInclude() : TObject() {
  //
  // GInclude normal constructor
  if ( gDebug ) cout << endl << "GInclude::GInclude normal ctor called" << endl << endl;

  // initialize global include pointer;
  gInclude = this;

}

//_____________________________________________________________

GInclude::~GInclude() {
  //
  // GInclude default destructor
  if ( gDebug ) cout << endl << "GInclude::~GInclude dtor called" << endl << endl;

}

//_____________________________________________________________

TString GInclude::FormatedInt(Int_t number, Int_t length, Int_t decimals, TString fill, Bool_t neg) {
  //
  // returns char string for length formated int, add blanks for compensation of decimals
  if ( gDebug ) cout << endl << "GInclude::FormatedInt called" << endl << endl;

  // compensate for negative numbers
  if ( number < 0 || neg) {
    length -= 1;
  }

  Bool_t hit = kFALSE;
  TString output = "";
  
  // count length of number
  TString test = "";
  test += number;
  Int_t mylength = test.Length();

  Int_t upper = (Int_t)TMath::Power(10,length-1);
  if ( number == 0 ) {
    for ( Int_t i = 0; i < length-1; i++)
      output.Append(fill);
    if ( neg )
      output.Append("-");
    output += 0;
  } else if ( TMath::Abs(number) < upper ) {
    for ( Int_t i = 0; i < (length-1); i++ ) {
      if ( !hit ) {
	if ( TMath::Abs(number) < (upper / TMath::Power(10,(length-2-i)) ) ) {
	  for ( Int_t j = 1; j < (length-i); j++ )
	    output.Append(fill);
	  output += number;
	  hit = kTRUE;
	}
      }
    }
    // compensate decimals
    if ( decimals > 0 ) {
      for ( Int_t i = 0; i < decimals; i++ )
	output.Append(" ");
    }
  } else {
    // if number has equal or more digits than length, just output number

    if ( mylength <= (length+decimals) ) {

      output += number;
      // compensation for the rest
      for ( Int_t i = 0; i < (length+decimals-mylength); i++ )
	output.Append(" ");
    } else {
      output += number;
    }
  }

  return output;

}

//_____________________________________________________________

TString GInclude::FormatedBool(Bool_t input) {
  //
  // returns char string for length formated bool
  // includes one blank at the beginnig for spacing
  if ( gDebug ) cout << endl << "GInclude::FormatedBool called" << endl << endl;

  TString output = " ";
  if ( input )
    output.Append("1");
  else
    output.Append("0");

  return output;

}

//_____________________________________________________________

TString GInclude::FormatedDouble(Double_t number, Int_t length, Int_t decimals) {
  //
  // returns char string for length formated double
  // includes one blank at the beginnig for spacing
  // seven decimals maximum
  if ( gDebug ) cout << endl << "GInclude::FormatedDouble called" << endl << endl;

  // variables
  TString output = "";

  // split number in integer and decimal part and treat separately
  Int_t intnumber = (Int_t)number;
  Double_t decnumber = TMath::Abs(number - intnumber);

  Double_t dec1 = decnumber*TMath::Power(10,decimals);

  if ( dec1 == 0 ) {

    // take care of case "-0"
    if ( (number < 0) && (intnumber == 0) )
      output.Append(FormatedInt(intnumber,length,0," ",kTRUE));
    else
      output.Append(FormatedInt(intnumber,length,0," "));
    
    output.Append(".");

    for ( Int_t i = 0; i < decimals; ++i )
      output.Append("0");

  } else {

    TString count = "";
    count += dec1;
    Int_t trailing = 0;
    for ( Int_t i = count.Length()-1; i >= 0;  i--) {
      if ( count(i) == 48 ) {
	trailing += 1;
      } else {
	break;
      }
    }

    Double_t dec2 = 0;
    Int_t dec = 0;
  
    // round for trailing digit if trailing is zero
    if ( trailing == 0 ) {
      dec2 = (decnumber*TMath::Power(10,decimals+1));
      //     if ( (((Int_t)(dec2+10))%100)>=50)
      dec = TMath::Nint(dec2);
      //     else
      //       dec = (Int_t)dec2;
      dec2 = dec/10+0.5;
      dec = (Int_t)dec2;
    } else {
      dec2 = (decnumber*TMath::Power(10,decimals+1-trailing));
      //     if ( (((Int_t)(dec2+10))%100)>50)
      dec = TMath::Nint(dec2);
      //     else
      //       dec = (Int_t)dec2;
      dec2 = dec/10+0.5;
      dec = (Int_t)dec2;
    }

    if ( (dec >= TMath::Power(10,decimals)) && (intnumber == 0) ) {
      intnumber = 1;
      dec = 0;
    }


    // take care of case "-0"
    if ( (number < 0) && (intnumber == 0) )
      output.Append(FormatedInt(intnumber,length,0," ",kTRUE));
    else
      output.Append(FormatedInt(intnumber,length,0," "));
    
    output.Append(".");

    if ( dec == 0 ) {
      output.Append(FormatedInt(0,decimals,0,"0"));
    } else 
      output.Append(FormatedInt(dec,decimals-trailing,0,"0"));

    for ( Int_t i = 0; i < trailing; ++i )
      output.Append("0");

  }

  return output;
}

//_____________________________________________________________

TString GInclude::FormatedChar(TString string, Int_t length) {
  //
  // returns char string for length formated string
  if ( gDebug ) cout << endl << "GInclude::FormatedChar called" << endl << endl;

  TString dummy = string;
  Int_t missing = length - dummy.Length();
  if ( missing > 0 ) {
    for ( Int_t i = 0; i < missing; i++ )
      dummy.Append(" ");
  }

  return dummy;
}

//_____________________________________________________________

TStyle* GInclude::MySetStyle() {
  //
  // create own TSytle for histograms
  if ( gDebug ) cout << endl << "GInclude::MySetStyle() called" << endl << endl;

  TStyle *myStyle = new TStyle("Default","Default");
  myStyle->cd();
  myStyle->SetFrameBorderMode(0);
  myStyle->SetCanvasBorderMode(0);
  myStyle->SetPadBorderMode(0);
  myStyle->SetPadColor(0);
  myStyle->SetCanvasColor(0);
  myStyle->SetTitleFillColor(0);
  myStyle->SetTitleBorderSize(1);
  myStyle->SetStatColor(0);
  myStyle->SetStatBorderSize(1);

  // no x error bars      
  // set individually
  // myStyle->SetErrorX(0);

  // set marker style
  myStyle->SetMarkerStyle(8);
  myStyle->SetMarkerSize(1.);
  myStyle->SetMarkerColor(2);

  return myStyle;
}

//_____________________________________________________________

TStyle* GInclude::ZEUSSetStyle() {
  //
  // create ZEUS TSytle for histograms
  if ( gDebug ) cout << endl << "GInclude::MySetStyle() called" << endl << endl;

  TStyle *zeus_pub = new TStyle("zeus_pub", "Style for ZEUS Publications");
  // stuff from "plain" style
  zeus_pub->SetFrameBorderMode(0);
  zeus_pub->SetCanvasBorderMode(0);
  zeus_pub->SetPadBorderMode(0);

  zeus_pub->SetOptStat(000000);
  zeus_pub->SetOptTitle(000000);

  zeus_pub->SetLabelSize(0.055,"x");
  zeus_pub->SetLabelSize(0.06,"y");
  zeus_pub->SetLabelOffset(0.00,"x");
  zeus_pub->SetLabelOffset(0.00,"y");
  zeus_pub->SetTitleOffset(0.04,"x");
  zeus_pub->SetTitleOffset(0.04,"y");
  zeus_pub->SetLabelFont(22,"x");
  zeus_pub->SetLabelFont(22,"y");
  zeus_pub->SetErrorX(0.0000);
  zeus_pub->SetTickLength(0.05,"x");
  zeus_pub->SetTickLength(0.05,"y");
  zeus_pub->SetLineWidth((Short_t)0.8);
  zeus_pub->SetPadTickX(1);
  zeus_pub->SetPadTickY(1);
  zeus_pub->SetPadLeftMargin(0.15);
  zeus_pub->SetPadBottomMargin(0.2);

  zeus_pub->SetPadColor(0);
  zeus_pub->SetCanvasColor(0);
  zeus_pub->SetTitleFillColor(0);
  zeus_pub->SetTitleBorderSize(1);
  zeus_pub->SetStatColor(0);
  zeus_pub->SetStatBorderSize(1);

  // no x error bars      
  zeus_pub->SetErrorX(0);

  return zeus_pub;
}

//_____________________________________________________________

void GInclude::GenClass(TString name) {
  // 
  // generate class for tree for give root file
  if ( gDebug ) cout << endl << "GInclude::GenerateClass() called" << endl << endl;

  TFile *file = new TFile(name.Data());

  TTree *tree = (TTree*)file->Get("orange");

  if(tree == NULL){
    tree = (TTree*)file->Get("h1");
  }

  tree->MakeClass();

  name.ReplaceAll(".root","");

  TString mvh;
  TString mvc;

  mvh.Append(".! mv h1.h ");
  mvh.Append(name.Data());
  mvh.Append(".h");

  mvc.Append(".! mv h1.C ");
  mvc.Append(name.Data());
  mvc.Append(".C");

  gROOT->ProcessLine(mvh.Data());
  gROOT->ProcessLine(mvc.Data());

  delete tree;
  delete file;
}

//_____________________________________________________________

TFile* GInclude::OpenFile(TString name) {
  //
  // open file in root-session
  if ( gDebug ) cout << endl << "GInclude::OpenDir() called" << endl << endl;
  TFile *file = new TFile(name.Data(),"READ");
  return file;
}

//_____________________________________________________________

void GInclude::ReadoutHeader(TFile *file) {
  //
  // read out analysis header information
  if ( gDebug ) cout << endl << "GInclude::ReadoutHeader() called" << endl << endl;

  TTree *general = (TTree*)file->Get("general");
  GAnalysisHeader *header = new GAnalysisHeader();
  general->SetBranchAddress("header",&header);

  for ( Int_t i = 0; i < general->GetEntries(); ++i ) {
    general->GetEntry(i);
    cout << endl;
    header->Header(header->GetDirectory());
    header->Footer(header->GetDirectory());
    cout << "Luminosity for " << header->GetDirectory() << ": " << header->GetLuminosity() << endl;
    cout << endl;
  }
}

//_____________________________________________________________

void GInclude::ReadoutHeaderToFile(TFile *file, TString outputfilename) {
  //
  // read out analysis header information to file
  if ( gDebug ) cout << endl << "GInclude::ReadoutHeaderToFile() called" << endl << endl;

  ofstream *stream = new ofstream(outputfilename.Data());


  TTree *general = (TTree*)file->Get("general");
  GAnalysisHeader *header = new GAnalysisHeader();
  general->SetBranchAddress("header",&header);

  for ( Int_t i = 0; i < general->GetEntries(); ++i ) {
    general->GetEntry(i);
    header->Header(stream,header->GetDirectory());
    header->Footer(stream,header->GetDirectory());
//     *stream << "Luminosity for " << header->GetDirectory() << ": " << header->GetLuminosity() << endl;
    *stream << endl;
  }
}

//_____________________________________________________________

void GInclude::ReadoutFits(TFile *file) {
  //
  // read out ptrel fit information
  if ( gDebug ) cout << endl << "GInclude::ReadoutFits() called" << endl << endl;

  TTree *fits = (TTree*)file->Get("fits");
  if ( fits != 0 ) {
    GPtRelFit *fit = new GPtRelFit();
    fits->SetBranchAddress("fit",&fit);
    
    for ( Int_t i = 0; i < fits->GetEntries(); ++i ) {
      fits->GetEntry(i);
      cout << endl;
      cout << fit->Print("");
      cout << endl;
    }
  }
  TTree *impactfits = (TTree*)file->Get("impactfits");
  if ( impactfits != 0 ) {  
    GImpactFit *impactfit = new GImpactFit();
    impactfits->SetBranchAddress("impactfit",&impactfit);
    
    for ( Int_t i = 0; i < impactfits->GetEntries(); ++i ) {
      impactfits->GetEntry(i);
      cout << endl;
      cout << impactfit->Print("");
      cout << endl;
    }
  }
}

//_____________________________________________________________

void GInclude::ReadoutFitsToFile(TFile *file, TString outputfilename) {
  //
  // read out ptrel fit information
  if ( gDebug ) cout << endl << "GInclude::ReadoutFitsToFile() called" << endl << endl;

  ofstream *stream = new ofstream(outputfilename.Data());


  TTree *fits = (TTree*)file->Get("fits");
  if ( fits != 0 ) {
    GPtRelFit *fit = new GPtRelFit();
    fits->SetBranchAddress("fit",&fit);
    
    for ( Int_t i = 0; i < fits->GetEntries(); ++i ) {
      fits->GetEntry(i);
      *stream << fit->Print("");
      *stream << endl;
    }
  }
    
  TTree *impactfits = (TTree*)file->Get("impactfits");
  if ( impactfits != 0 ) {
    GImpactFit *impactfit = new GImpactFit();
    impactfits->SetBranchAddress("impactfit",&impactfit);
    
    for ( Int_t i = 0; i < impactfits->GetEntries(); ++i ) {
      impactfits->GetEntry(i);
      *stream << impactfit->Print("");
      *stream << endl;
    }
  }
}

//_____________________________________________________________

void GInclude::InitData(TString name) {
  //
  // init data root file and open tree
  if ( gDebug ) cout << endl << "GInclude::InitData() called" << endl << endl;

  TFile *file = OpenFile(name);
  TTree *tree = InitTree(file);
  StartViewer(tree);
}

//_____________________________________________________________

TTree* GInclude::InitTree(TFile *file) {
  //
  // init tree of file
  if ( gDebug ) cout << endl << "GInclude::InitTree() called" << endl << endl;

  TTree *tree = (TTree*)file->Get("h1");

  if(tree == NULL){
    tree = (TTree*)file->Get("orange");
  }

  return tree;
}

//_____________________________________________________________

void GInclude::StartViewer(TTree *tree) {
  //
  // start tree viewer
  if ( gDebug ) cout << endl << "GInclude::StartViewer() called" << endl << endl;

  tree->StartViewer();
}

//_____________________________________________________________

TChain* GInclude::ChainFiles(TString directory) {
  //
  // chain root files 
  if ( gDebug ) cout << endl << "GInclude::ChainFiles() called" << endl << endl;

  TChain *chain = new TChain("h1");

  if( chain == 0 ){
    chain = new TChain("orange");
  }

  TString dummy = directory;
  dummy.Append("/*.root");
  chain->Add(dummy.Data(),0);
  cout << "GInclude::ChainFiles entries: " << chain->GetEntries() << endl;
  return chain;
}

//_____________________________________________________________

void GInclude::StartChainViewer(TChain *chain) {
  //
  // start chain viewer
  if ( gDebug ) cout << endl << "GInclude::StartChainViewer() called" << endl << endl;

  chain->StartViewer();
}

//_____________________________________________________________

TH1D* GInclude::ReadAscii(TString filename, TString histoname, TString histotitle, 
			  TString xaxistitle, TString yaxistitle, 
			  Int_t bins, Double_t lower_border, Double_t upper_border) {
  //
  // read ascii file which numbers are in first column
  if ( gDebug ) cout << endl << "GInclude::ReadAscii() called" << endl << endl;

  ifstream stream(filename);

  TString line = "";

  TH1D *histo = new TH1D(histoname,histotitle, bins, lower_border, upper_border);

  while (line.ReadLine(stream)) {
    istrstream istream(line.Data());
    Double_t input;
    istream >> input;
    histo->Fill(input);
      
  }
  histo->SetFillColor(2);
  histo->SetXTitle(xaxistitle);
  histo->SetYTitle(yaxistitle);
  histo->Draw("bar");

  return histo;
}

//_____________________________________________________________

TDirectory* GInclude::MkdirRecursive(TDirectory *initial, TString directory) {
  //
  // makes recursive directory in initial directory
  if ( gDebug ) cout << endl << "GInclude::MkdirRecursive() called" << endl << endl;

  // count number of slashes
  TString dirstring = directory;
  if ( dirstring.EndsWith("/") )
    dirstring.Remove(dirstring.Length()-1);
  Int_t dirnum = dirstring.CountChar(47) + 1;
    
  // fill string array for bins
  TObjArray dirarray;
  char first = 0;
  TString dummy = "";

  for ( Int_t i = 0; i < dirnum; i++) {
    while ( (first = dirstring(0)) ) {
      // remove first
      dirstring.Remove(0,1);
      // sort to arrays or break in case of slash
      if ( first == 47 )
	break;
      else
	dummy.Append(first);
    }
    dirarray.Add(new TObjString(dummy));
    dummy = "";
  }

  // make directory from input
  TDirectory *direct = initial;
  TDirectory *direct2 = 0;
  for ( Int_t i = 0; i < dirarray.GetEntries(); i++ ) {
    direct2 = direct->mkdir(((TObjString*)dirarray[i])->GetName(),((TObjString*)dirarray[i])->GetName());
    if ( direct2 == 0 ) {
      direct = (TDirectory*)(direct->FindKey(((TObjString*)dirarray[i])->GetName()))->ReadObj();
    } else {
      direct = direct2;
    }
  }

  dirarray.Delete();

  return direct;
}

//_____________________________________________________________

TDirectory* GInclude::MkdirRecursiveOld(TDirectory *initial, TString directory) {
  //
  // makes recursive directory in initial directory old fashion
  if ( gDebug ) cout << endl << "GInclude::MkdirRecursiveOld() called" << endl << endl;

  // count number of slashes
  TString dirstring = directory;
  if ( dirstring.EndsWith("/") )
    dirstring.Remove(dirstring.Length()-1);
  Int_t dirnum = dirstring.CountChar(47) + 1;
    
  // fill string array for bins
  TObjArray dirarray;
  char first = 0;
  TString dummy = "";

  for ( Int_t i = 0; i < dirnum; i++) {
    while ( (first = dirstring(0)) ) {
      // remove first
      dirstring.Remove(0,1);
      // sort to arrays or break in case of slash
      if ( first == 47 )
	break;
      else
	dummy.Append(first);
    }
    dirarray.Add(new TObjString(dummy));
    dummy = "";
  }

  // make directory from input
  TDirectory *direct = initial;
  TDirectory *direct2 = 0;
  for ( Int_t i = 0; i < dirarray.GetEntries(); i++ ) {
    direct2 = direct->mkdir(((TObjString*)dirarray[i])->GetName(),((TObjString*)dirarray[i])->GetName());
    if ( direct2 == 0 ) {
      direct = (TDirectory*)direct->Get(((TObjString*)dirarray[i])->GetName());
    } else {
      direct = direct2;
    }
  }

  dirarray.Delete();

  return direct;
}

//_____________________________________________________________

TKey* GInclude::FindKeyAnyRecursive(TDirectory *initial, TString object) {
  //
  // find key of object recursively in initial directory
  if ( gDebug ) cout << endl << "GInclude::FindKeyAnyRecursive() called" << endl << endl;

  // count number of slashes
  TString dirstring = object;
  if ( dirstring.EndsWith("/") )
    dirstring.Remove(dirstring.Length()-1);
  if ( dirstring.BeginsWith("/") )
    dirstring.Remove(0);
  Int_t dirnum = dirstring.CountChar(47)+1;

  // fill string array for bins
  TObjArray dirarray;
  char first = 0;
  TString dummy = "";

  for ( Int_t i = 0; i < dirnum; i++) {
    while ( (first = dirstring(0)) ) {
      // remove first
      dirstring.Remove(0,1);
      // sort to arrays or break in case of slash
      if ( first == 47 )
	break;
      else
	dummy.Append(first);
    }
    dirarray.Add(new TObjString(dummy));
    dummy = "";
  }

  // make directory from input
  TDirectory *direct = initial;
  TKey *temp = 0;
  for ( Int_t i = 0; i < (dirarray.GetEntries()-1); i++ ) {
    temp = direct->FindKey(((TObjString*)dirarray[i])->GetName());
    if ( temp != 0 ) {
      direct = (TDirectory*)temp->ReadObj();
    } else {
      return 0;
    }
  }

  temp = direct->FindKey(((TObjString*)dirarray[(dirarray.GetEntries()-1)])->GetName());

  dirarray.Delete();

  return temp;
}

//_____________________________________________________________

TString GInclude::StripFromFirstSpace(TString dir) {
  //
  // strip everything from first space
  if ( gDebug ) cout << endl << "GInclude::StripFromFirstSpace() called" << endl << endl;

  char first = 0;
  TString output = "";

  while ( (first = dir(0)) ) {
    // remove first
    dir.Remove(0,1);
    // break in case of slash
    if ( first == 32 )
      break;
    output.Append(first);
  }

  return output;

}

//_____________________________________________________________

TString GInclude::StripLastDir(TString dir) {
  //
  // strip last dir from string
  if ( gDebug ) cout << endl << "GInclude::StripLastDir() called" << endl << endl;

  char last = 0;

  while ( (last = dir(dir.Length()-1)) ) {
    // remove last
    dir.Remove(dir.Length()-1,1);
    // break in case of slash
    if ( last == 47 )
      break;
  }

  return dir;

}

//_____________________________________________________________

TString GInclude::StripFirstDir(TString dir) {
  //
  // strip first dir from string
  if ( gDebug ) cout << endl << "GInclude::StripFirstDir() called" << endl << endl;

  char first = 0;

  while ( (first = dir(0)) ) {
    // remove last
    dir.Remove(0,1);
    // break in case of slash
    if ( first == 47 )
      break;
  }

  return dir;

}

//_____________________________________________________________

TString GInclude::GetExtension(TString file) {
  //
  // get file extension
  if ( gDebug ) cout << endl << "GInclude::GetExtension() called" << endl << endl;

  TString ext = "";

  char last = 0;

  while ( (last = file(file.Length()-1)) ) {
    // remove last
    file.Remove(file.Length()-1,1);
    ext.Prepend(last);
    // break in case of slash
    if ( last == 46 )
      break;
  }

  return ext;

}

//_____________________________________________________________

void GInclude::NicePlot(TPad *pad) {
  //
  // nice plot
  if ( gDebug ) cout << endl << "GInclude::NicePlot() called" << endl << endl;

  TH1 *histo = (TH1*)pad->FindObject(GetFirstHistoFromPad(pad));
  pad->SetBottomMargin(0.11);
  histo->GetXaxis()->SetTitleOffset(1.1);
  
  Double_t max = histo->GetMaximum();
  Double_t min = histo->GetMinimum();

  // maximum takes precedence over minimum
  Bool_t precedence = kTRUE;

  // check precedence
  // differentiate between 0<x<1 and x>1
  if (max > 1.) {
    if ( min < -1. ) {
      if ( max > TMath::Abs(min) ) {
	precedence = kTRUE;
      } else {
	precedence = kFALSE; 
      }
    } else if ( min == 0 ) {
      precedence = kTRUE;
    } else {
      precedence = kFALSE;
    }
  } else if ( max == 0 ) {
    if ( min < -1. ) {
      precedence = kFALSE; 
    } else if ( min == 0 ) {
      precedence = kTRUE;
    } else {
      precedence = kFALSE;
    }
  } else {
    if ( min < -1. ) {
      precedence = kTRUE;
    } else if ( min == 0 ) {
      precedence = kTRUE;
    } else {
      precedence = kFALSE;
    }
  }

  if ( precedence ) {
    if ( max > 1000. ) {
      pad->SetLeftMargin(0.13);
      histo->GetYaxis()->SetTitleOffset(1.6);
    } else if ( max > 100. ) {
      pad->SetLeftMargin(0.12);
      histo->GetYaxis()->SetTitleOffset(1.3);
    } else if ( max > 0.5 ) {
      pad->SetLeftMargin(0.1);
      histo->GetYaxis()->SetTitleOffset(1.);
    } else if ( max > 0.5 ) {
      pad->SetLeftMargin(0.12);
      histo->GetYaxis()->SetTitleOffset(1.2);
    } else if ( max > 0.05 ) {
      pad->SetLeftMargin(0.13);
      histo->GetYaxis()->SetTitleOffset(1.5);
    } else {
      pad->SetLeftMargin(0.14);
      histo->GetYaxis()->SetTitleOffset(1.6);
    } 
  } else {
    if ( min < -1000. ) {
      pad->SetLeftMargin(0.13);
      histo->GetYaxis()->SetTitleOffset(1.6);
    } else if ( min < -100. ) {
      pad->SetLeftMargin(0.12);
      histo->GetYaxis()->SetTitleOffset(1.3);
    } else if ( min < -0.5 ) {
      pad->SetLeftMargin(0.1);
      histo->GetYaxis()->SetTitleOffset(1.);
    } else if ( min < -0.05 ) {
      pad->SetLeftMargin(0.12);
      histo->GetYaxis()->SetTitleOffset(1.3);
    } else if ( min < -0.05 ) {
      pad->SetLeftMargin(0.14);
      histo->GetYaxis()->SetTitleOffset(1.6);
    } else {
      pad->SetLeftMargin(0.15);
      histo->GetYaxis()->SetTitleOffset(1.8);
    }
  }

  pad->Update();
}

//_____________________________________________________________

void GInclude::NicePlotDraw(TPad* pad) {
  //
  // draw niced plot
  if ( gDebug ) cout << endl << "GInclude::NicePlotDraw() called" << endl << endl;

  NicePlot(pad);
  pad->Draw();

}

//_____________________________________________________________

void GInclude::FastNice() {
  //
  // draw niced plot
  if ( gDebug ) cout << endl << "GInclude::NicePlotDraw() called" << endl << endl;

  TPad *pad = (TPad*)gROOT->FindObject("c1");

  NicePlot(pad);
  pad->Draw();

}

//_____________________________________________________________

void GInclude::FastPics() {
  //
  // make fast pics
  if ( gDebug ) cout << endl << "GInclude::NicePlotDraw() called" << endl << endl;

  TPad *pad = (TPad*)gROOT->FindObject("c1");

  GPictureMaker maker;
  maker.GenHTMLPics((TCanvas*)pad,GetFirstHistoFromPad(pad),".","","NOHTML,EPS,GIF");

}

//_____________________________________________________________

Double_t GInclude::GetLumi(TFile *file, TString histotitle) {
  //
  // get addedd lumi for given histogram
  if ( gDebug ) cout << endl << "GInclude::GetLumi called" << endl << endl;

  Double_t lumi = 0;

  TTree *general = (TTree*)file->Get("general");
  GAnalysisHeader *header = new GAnalysisHeader();
  general->SetBranchAddress("header",&header);

  // decide for subdirs mode (if header->GetDirectory() should contain dir, then it will
  // return lumi added for dir, dir_2, dir1, etc.
  // so if StripFromFirstSpace(histotitle) ends with an subdir, than take only this lumi, 
  // otherwise, add lumi values
  Bool_t exclusive = kFALSE;
  TString request = StripFromFirstSpace(histotitle);
  GHistogrammer grammer;
  TList *subdirs = grammer.GetSubdirs();
  TIter nextsubdir(subdirs);
  while (TObjString *subdir = (TObjString*)nextsubdir() ) {
    if ( request.EndsWith(subdir->GetString()) ) {
      exclusive = kTRUE;
    }
  }


  for ( Int_t i = 0; i < general->GetEntries(); ++i) {
    general->GetEntry(i);
    if ( exclusive ) { 
      if ( header->GetDirectory() == request)
	lumi = header->GetLuminosity();
    } else {
      if ( (header->GetDirectory()).Contains(StripFromFirstSpace(histotitle)))
	lumi += header->GetLuminosity();
    }
  }

  return lumi;
}

//_____________________________________________________________

void GInclude::SetLumi(TFile *file, TString histotitle,Double_t reweightfactor) {
    //
  // set lumi for given histogram
  if ( gDebug ) cout << endl << "GInclude::SetLumi called" << endl << endl;
  Double_t lumi = 0;

  TTree *general = (TTree*)file->Get("general");
  GAnalysisHeader *header = new GAnalysisHeader();
  general->SetBranchAddress("header",&header);
  TObjArray headers;
 for ( Int_t i = 0; i < general->GetEntries(); ++i) {
    general->GetEntry(i);

    if ( (header->GetDirectory()).Contains(StripFromFirstSpace(histotitle))){
      lumi = header->GetLumiWeight();
      if ( gDebug )cout << "old lumi " << header->GetLuminosity()<< endl;
       header->SetLumiWeight(reweightfactor);

       if ( gDebug ) cout << "new lumi weight " << header->GetLumiWeight()<< endl;
       }
    headers.Add(header->Clone());
     if ( gDebug )  cout << "new lumi from weight " << header->GetLumiWeight()<< endl;
   }
    


  GAnalysisHeader *newheader = new GAnalysisHeader();
  general->Delete("all");
  general = new TTree("general","general");
  general->Branch("header","GAnalysisHeader",&newheader);
 for ( Int_t i = 0; i < headers.GetEntries(); ++i) {
    newheader = (GAnalysisHeader*)headers.At(i);
    general->Fill();
 }
     
    
  

  general->Write("",kOverwrite);
   
}

//_____________________________________________________________

Bool_t GInclude::AddFit(TFile *file, TString name, Double_t bscale, Double_t bscaleerr, Double_t clfscale, Double_t clfscaleerr, Double_t bfraction, Double_t bfractionerr, Double_t chi2, Int_t bins, Int_t parameter) {
  //
  // loop over all ptrel fits in file
  // check if fit with given name already exist, if yes, change values, if not, add fit
  if ( gDebug ) cout << endl << "GInclude::AddfitToHeader called" << endl << endl;

  TTree *general = (TTree*)file->Get("fits");
  if ( !general ) {
    file->cd();
    general = new TTree("fits","fits");
  }
  if ( !general->GetBranch("fit") ) {
    GPtRelFit *newfit = new GPtRelFit(name, bscale, bscaleerr, clfscale, clfscaleerr, bfraction, bfractionerr, chi2, bins, parameter);
    general->Branch("fit","GPtRelFit",&newfit);
    general->Fill();
  } else {
    TObjArray fits;
    GPtRelFit *fit = new GPtRelFit();
    general->SetBranchAddress("fit",&fit);
    for ( Int_t i = 0; i < general->GetEntries(); ++i) {
      general->GetEntry(i);
      fits.Add(fit->Clone());
    }
    Bool_t exists = kFALSE;
    for ( Int_t i = 0; i < fits.GetEntries(); ++i ) {
      if ( !(((GPtRelFit*)fits.At(i))->GetName()).CompareTo(name) ) {
	((GPtRelFit*)fits.At(i))->SetBScale(bscale);
	((GPtRelFit*)fits.At(i))->SetBScaleErr(bscaleerr);
	((GPtRelFit*)fits.At(i))->SetCLFScale(clfscale);
	((GPtRelFit*)fits.At(i))->SetCLFScaleErr(clfscaleerr);
	((GPtRelFit*)fits.At(i))->SetBFraction(bfraction);
	((GPtRelFit*)fits.At(i))->SetBFractionErr(bfractionerr);
	((GPtRelFit*)fits.At(i))->SetChi2(chi2);
	((GPtRelFit*)fits.At(i))->SetBins(bins);
	((GPtRelFit*)fits.At(i))->SetParameter(parameter);
	exists = kTRUE;
      }
    }

    if ( !exists ) {
      fits.Add(new GPtRelFit(name, bscale, bscaleerr, clfscale, clfscaleerr, bfraction, bfractionerr, chi2, bins, parameter));
    }

    GPtRelFit *newfit = new GPtRelFit();
    general->Delete("all");
    general = new TTree("fits","fits");
    general->Branch("fit","GPtRelFit",&newfit);
    for ( Int_t i = 0; i < fits.GetEntries(); ++i ) {
      newfit = ((GPtRelFit*)fits.At(i));
      general->Fill();
    }
  }

  general->Write("",kOverwrite);

  return kTRUE;
}

//_____________________________________________________________

Bool_t GInclude::AddImpactFit(TFile *file, TString name, Double_t bscale, Double_t bscaleerr, Double_t clfscale, Double_t clfscaleerr, Double_t bfraction, Double_t bfractionerr, Double_t chi2, Int_t bins, Int_t parameter) {
  //
  // loop over all impact parameter fits in file
  // check if fit with given name already exist, if yes, change values, if not, add fit
  if ( gDebug ) cout << endl << "GInclude::AddfitToHeader called" << endl << endl;

  TTree *general = (TTree*)file->Get("impactfits");
  if ( !general ) {
    file->cd();
    general = new TTree("impactfits","impactfits");
  }
  if ( !general->GetBranch("impactfit") ) {
    GImpactFit *newimpactfit = new GImpactFit(name, bscale, bscaleerr, clfscale, clfscaleerr, bfraction, bfractionerr, chi2, bins, parameter);
    general->Branch("impactfit","GImpactFit",&newimpactfit);
    general->Fill();
  } else {
    TObjArray impactfits;
    GImpactFit *impactfit = new GImpactFit();
    general->SetBranchAddress("impactfit",&impactfit);
    for ( Int_t i = 0; i < general->GetEntries(); ++i) {
      general->GetEntry(i);
      impactfits.Add(impactfit->Clone());
    }
    Bool_t exists = kFALSE;
    for ( Int_t i = 0; i < impactfits.GetEntries(); ++i ) {
      if ( !(((GImpactFit*)impactfits.At(i))->GetName()).CompareTo(name) ) {
	((GImpactFit*)impactfits.At(i))->SetBScale(bscale);
	((GImpactFit*)impactfits.At(i))->SetBScaleErr(bscaleerr);
	((GImpactFit*)impactfits.At(i))->SetCLFScale(clfscale);
	((GImpactFit*)impactfits.At(i))->SetCLFScaleErr(clfscaleerr);
	((GImpactFit*)impactfits.At(i))->SetBFraction(bfraction);
	((GImpactFit*)impactfits.At(i))->SetBFractionErr(bfractionerr);
	((GImpactFit*)impactfits.At(i))->SetChi2(chi2);
	((GImpactFit*)impactfits.At(i))->SetBins(bins);
	((GImpactFit*)impactfits.At(i))->SetParameter(parameter);
	exists = kTRUE;
      }
    }

    if ( !exists ) {
      impactfits.Add(new GImpactFit(name, bscale, bscaleerr, clfscale, clfscaleerr, bfraction, bfractionerr, chi2, bins, parameter));
    }

    GImpactFit *newimpactfit = new GImpactFit();
    general->Delete("all");
    general = new TTree("impactfits","impactfits");
    general->Branch("impactfit","GImpactFit",&newimpactfit);
    for ( Int_t i = 0; i < impactfits.GetEntries(); ++i ) {
      newimpactfit = ((GImpactFit*)impactfits.At(i));
      general->Fill();
    }
  }

  general->Write("",kOverwrite);

  return kTRUE;
}

//_____________________________________________________________

Int_t GInclude::GetNHeaders(TFile *file) {
  //
  // get number of headers
  if ( gDebug ) cout << endl << "GInclude::GetNHeaders called" << endl << endl;

  TTree *general = (TTree*)file->Get("general");
  return (Int_t)general->GetEntries();
}

//_____________________________________________________________

GAnalysisHeader* GInclude::GetHeader(TFile *file, Int_t index) {
  //
  // get header with index 
  if ( gDebug ) cout << endl << "GInclude::GetHeader called" << endl << endl;

  TTree *general = (TTree*)file->Get("general");
  GAnalysisHeader *header = new GAnalysisHeader();
  general->SetBranchAddress("header",&header);
  general->GetEntry(index);
  return header;
}

//_____________________________________________________________

GPtRelFit* GInclude::GetFit(TFile *file, TString name) {
  //
  // get fit with name
  if ( gDebug ) cout << endl << "GInclude::GetFit called" << endl << endl;

  TTree *general = (TTree*)file->Get("fits");
  if ( general != 0 ) {
    GPtRelFit *fit = new GPtRelFit();
    general->SetBranchAddress("fit",&fit);
    for ( Int_t i = 0; i < general->GetEntries(); ++i ) {
      general->GetEntry(i);
      if ( !(fit->GetName().CompareTo(name)) )
	return fit;
    }
  }

  GPtRelFit *zero = new GPtRelFit(name,0.,0.,0.,0.,0.,0.,0.,0,0);


  return zero;

}

//_____________________________________________________________

GImpactFit* GInclude::GetImpactFit(TFile *file, TString name) {
  //
  // get impact parameter fit with name
  if ( gDebug ) cout << endl << "GInclude::GetImpactFit called" << endl << endl;

  TTree *general = (TTree*)file->Get("impactfits");
  if ( general != 0 ) {
  GImpactFit *impactfit = new GImpactFit();
  general->SetBranchAddress("impactfit",&impactfit);
  for ( Int_t i = 0; i < general->GetEntries(); ++i ) {
    general->GetEntry(i);
    if ( !(impactfit->GetName().CompareTo(name)) )
      return impactfit;
  }
  }

  GImpactFit *zero = new GImpactFit(name,0.,0.,0.,0.,0.,0.,0.,0,0);

  return zero;

}

//_____________________________________________________________

TString GInclude::GetFirstHistoFromCanvas(TCanvas *canvas) {
  //
  // get name of first histogram from canvas
  if ( gDebug ) cout << endl << "GInclude::GetFirstHistoFromCanvas called" << endl << endl;

  TIter iter(canvas->GetListOfPrimitives());
  
  TObject *obj;
  
  while ( (obj = iter()) ) {
    if ( obj->IsA()->InheritsFrom("TH1") ) {
      TH1 *histo = (TH1*)obj;
      return histo->GetName();
    }
  }
  return "";
}

//_____________________________________________________________

TString GInclude::GetFirstHistoFromPad(TPad *pad) {
  //
  // get name of first histogram from pad
  if ( gDebug ) cout << endl << "GInclude::GetFirstHistoFromPad called" << endl << endl;

  TIter iter(pad->GetListOfPrimitives());
  
  TObject *obj;
  
  while ( (obj = iter()) ) {
    if ( obj->IsA()->InheritsFrom("TH1") ) {
      TH1 *histo = (TH1*)obj;
      return histo->GetName();
    }
  }
  return "";
}

//_____________________________________________________________

TObject* GInclude::GetFromFile(TFile *file, TString name) {
  //
  // try to get object with abolute path from memory, afterwards from file
  if ( gDebug ) cout << endl << "GInclude::GetFromFile called" << endl << endl;

  TObject *obj = gROOT->Get(name.Data());
  if ( obj == 0 )
    obj = file->Get(name.Data());

  return obj;

}

//_____________________________________________________________

Bool_t GInclude::CopyFits(TFile *source, TFile *destination) {
  //
  // copy fits from source file to destination file
  if ( gDebug ) cout << endl << "GInclude::CopyFits called" << endl << endl;

  TTree *input = (TTree*)source->Get("fits");
  GPtRelFit *oldfit = new GPtRelFit();
  input->SetBranchAddress("fit",&oldfit);
  for ( Int_t i = 0; i < input->GetEntries(); ++i) {
    input->GetEntry(i);
    AddFit(destination,oldfit->GetName(),oldfit->GetBScale(),oldfit->GetBScaleErr(),oldfit->GetCLFScale(),oldfit->GetCLFScaleErr(),oldfit->GetBFraction(),oldfit->GetBFractionErr(),oldfit->GetChi2(),oldfit->GetBins(),oldfit->GetParameter());
  }
  TTree *impactinput = (TTree*)source->Get("impactfits");
  GImpactFit *oldimpactfit = new GImpactFit();
  impactinput->SetBranchAddress("impactfit",&oldimpactfit);
  for ( Int_t i = 0; i < impactinput->GetEntries(); ++i) {
    impactinput->GetEntry(i);
    AddImpactFit(destination,oldimpactfit->GetName(),oldimpactfit->GetBScale(),oldimpactfit->GetBScaleErr(),oldimpactfit->GetCLFScale(),oldimpactfit->GetCLFScaleErr(),oldimpactfit->GetBFraction(),oldimpactfit->GetBFractionErr(),oldfit->GetChi2(),oldfit->GetBins(),oldfit->GetParameter());
  }
  return kTRUE;
}

//_____________________________________________________________

Bool_t GInclude::DumpHisto(TH1D* histo, TString filename) {
  //
  // dump histogram data points including errors in ascii-file in current directory
  //
  // 1. line: name of histogram
  // 2. line: title of histogram
  // 3. line: number of bins [nbins]
  // 4. line: bin borders    [nbins+1]
  // 5. line: bin contents   [nbins]
  // 6. line: bin errors     [nbins]
  //
  if ( gDebug ) cout << endl << "GInclude::DumpHisto called" << endl << endl;

  ofstream output(filename.Data());

  TString name = histo->GetName();
  if ( name.Length() == 0 )
    name = "dump";
  TString title = histo->GetTitle();
  if ( title.Length() == 0 )
    title = "dumped histo";
  TString xtitle = histo->GetXaxis()->GetTitle();
  if ( xtitle.Length() == 0 )
    xtitle = "dumped histo";
  TString ytitle = histo->GetYaxis()->GetTitle();
  if ( ytitle.Length() == 0 )
    ytitle = "dumped histo";


  output << name << endl;
  output << title << endl;
  output << xtitle << endl;
  output << ytitle << endl;

  output << histo->GetNbinsX() << endl;

  TString bins = "";
  TString data = "";
  TString error = "";

  for ( Int_t i = 1; i <= histo->GetNbinsX(); ++i ) {
    bins += histo->GetBinLowEdge(i);
    bins.Append(" ");
    data += histo->GetBinContent(i);
    data.Append(" ");
    error += histo->GetBinError(i);
    error.Append(" ");
  }

  // add last bin low edge
  bins += histo->GetBinLowEdge(histo->GetNbinsX()+1);
  bins.Append(" ");

  output << bins << endl;
  output << data << endl;
  output << error << endl;


  return kTRUE;
}
//_____________________________________________________________

Bool_t GInclude::DumpHisto(TH2D* histo, TString filename) {
  //
  // dump histogram data points including errors in ascii-file in current directory
  //
  // 1. line: name of histogram
  // 2. line: title of histogram
  // 3. line: number of bins [nbins]
  // 3. line: number of xbins [nbins]
  // 3. line: number of ybins [nbins]
  // 4. line: bin x center    [nbins+1]
  // 4. line: bin y center    [nbins+1]
  // 5. line: bin contents   [nbins]
  // 6. line: bin errors     [nbins]
  //
  if ( gDebug ) cout << endl << "GInclude::DumpHisto called" << endl << endl;

  ofstream output(filename.Data());

  TString name = histo->GetName();
  if ( name.Length() == 0 )
    name = "dump";
  TString title = histo->GetTitle();
  if ( title.Length() == 0 )
    title = "dumped histo";
  TString xtitle = histo->GetXaxis()->GetTitle();
  if ( xtitle.Length() == 0 )
    xtitle = "dumped histo";
  TString ytitle = histo->GetYaxis()->GetTitle();
  if ( ytitle.Length() == 0 )
    ytitle = "dumped histo";

  output << name << endl;
  output << title << endl;
  output << xtitle << endl;
  output << ytitle << endl;

  output << histo->GetNbinsX() << endl;
  output << histo->GetNbinsY() << endl;

  Double_t binX = 0;
  Double_t binY = 0;
  Double_t data = 0;
  Double_t error = 0;

  for ( Int_t i = 1; i <= histo->GetNbinsX(); ++i ) {
    for ( Int_t j = 1; j <= histo->GetNbinsY(); ++j ) {
      binX = histo->GetXaxis()->GetBinCenter(i);
      binY = histo->GetYaxis()->GetBinCenter(j);
      data = histo->GetBinContent(i,j);
      error= histo->GetBinError(i,j);
      
      output << binX << "  "  << binY << "  "  << data << "  "  << error  << endl;
    }
  }



  return kTRUE;
}



//_____________________________________________________________

TH1D* GInclude::ReadinHisto(TString filename) {
  //
  // read in histogram data points including errors from ascii-file in current directory
  //
  // 1. line: name of histogram
  // 2. line: title of histogram
  // 3. line: number of bins [nbins]
  // 4. line: bin borders    [nbins+1]
  // 5. line: bin contents   [nbins]
  // 6. line: bin errors     [nbins]
  //
  if ( gDebug ) cout << endl << "GInclude::ReadinHisto called" << endl << endl;

  TH1D *dummy = 0;

  if ( gSystem->Which(gSystem->pwd(),filename) ) {

    ifstream input(filename.Data());

    TString name = "";
    TString title = "";
    TString xtitle = "";
    TString ytitle = "";
    TString nbinline = "";
    TString binsline = "";
    TString dataline = "";
    TString errorline = "";

  // read in lines
    name.ReadLine(input);
    title.ReadLine(input);
    xtitle.ReadLine(input);
    ytitle.ReadLine(input);
    nbinline.ReadLine(input);
    binsline.ReadLine(input);
    dataline.ReadLine(input);
    errorline.ReadLine(input);

    istrstream nbinstream(nbinline.Data());
    istrstream binstream(binsline.Data());
    istrstream datastream(dataline.Data());
    istrstream errorstream(errorline.Data());

  // get number of bins
    Int_t nbins = 0;
    nbinstream >> nbins;

  // make arrays
    Double_t bins[nbins+1];
    Double_t data[nbins];
    Double_t error[nbins];

    // get array contents
    for ( Int_t i = 0; i < nbins; ++i ) {
      binstream >> bins[i];
      datastream >> data[i];
      errorstream >> error[i];
    }
    // last bin
    binstream >> bins[nbins];

    // create histogram
    dummy = new TH1D(name,title,nbins,bins);
    if ( !xtitle.Contains("dumped histo") ) {
      dummy->SetXTitle(xtitle);
    }
    if ( !ytitle.Contains("dumped histo") ) {
      dummy->SetYTitle(ytitle);
    }

    // fill bin contents
    for ( Int_t i = 1; i <= nbins; ++i ) {
      dummy->SetBinContent(i,data[i-1]);
      dummy->SetBinError(i,error[i-1]);
    }
  }
  
  return dummy;
}

//_____________________________________________________________

void GInclude::CopyEfficiencyPlots(TFile *input, TString outputname) {
  //
  // copy efficiency plots from input histos-file to file with outputname
  if ( gDebug ) cout << endl << "GInclude::CopyEfficiencyPlots called" << endl << endl;

  TFile *output = new TFile(outputname,"RECREATE");

  TDirectory *efficiencies = output->mkdir("Efficiencies","Efficiencies");
  TDirectory *data = efficiencies->mkdir("Data","Data");
  TDirectory *mc = efficiencies->mkdir("MC","MC");

  Int_t MPMATCHNBins = 3;
  Double_t MPMATCHBins[MPMATCHNBins+1];
  MPMATCHBins[0]  = 1.50;
  MPMATCHBins[1]  = 2.00;
  MPMATCHBins[2]  = 2.50;
  MPMATCHBins[3]  = 5.00;

  Int_t BREMATNBins = 3;
  Double_t BREMATBins[BREMATNBins+1];
  BREMATBins[0]  = 1.50;
  BREMATBins[1]  = 2.00;
  BREMATBins[2]  = 2.50;
  BREMATBins[3]  = 5.00;

  Int_t MUBACNBins = 6;
  Double_t MUBACBins[MUBACNBins+1];
  MUBACBins[0]  = 1.50;
  MUBACBins[1]  = 1.75;
  MUBACBins[2]  = 2.00;
  MUBACBins[3]  = 2.25;
  MUBACBins[4]  = 2.50;
  MUBACBins[5]  = 3.50;
  MUBACBins[6]  = 5.00;

  TH1D* finder = 0;
  TH1D* mv = 0;

// copy data histograms for BREMAT
  for ( Int_t i = 0; i < BREMATNBins; ++i ) {
    TString finder_name = "Histograms/data/merged/DIMuon/MV_BREMAT_MuonEtaPtBins_";
    finder_name.Append(gInclude->FormatedDouble(BREMATBins[i],0,2));
    finder_name.Append("_");
    finder_name.Append(gInclude->FormatedDouble(BREMATBins[i+1],0,2));
    cout << "finder_name: " << finder_name << endl;
    TString mv_name = "Histograms/data/merged/DIMuon/MV_MuonEtaPtBins_";
    mv_name.Append(gInclude->FormatedDouble(BREMATBins[i],0,2));
    mv_name.Append("_");
    mv_name.Append(gInclude->FormatedDouble(BREMATBins[i+1],0,2));
    cout << "mv_name: " << mv_name << endl;
    finder = (TH1D*)input->Get(finder_name);
    mv = (TH1D*)input->Get(mv_name);
    finder->Divide(mv);
    data->cd();
    finder->Clone();
    output->Write("",TFile::kOverwrite);
  }

  // copy data histograms for MPMATCH
  for ( Int_t i = 0; i < MPMATCHNBins; ++i ) {
    TString finder_name = "Histograms/data/merged/DIMuon/MV_MPMATCH_MuonEtaPtBins_";
    finder_name.Append(gInclude->FormatedDouble(MPMATCHBins[i],0,2));
    finder_name.Append("_");
    finder_name.Append(gInclude->FormatedDouble(MPMATCHBins[i+1],0,2));
    cout << "finder_name: " << finder_name << endl;
    TString mv_name = "Histograms/data/merged/DIMuon/MV_MuonEtaPtBins_";
    mv_name.Append(gInclude->FormatedDouble(MPMATCHBins[i],0,2));
    mv_name.Append("_");
    mv_name.Append(gInclude->FormatedDouble(MPMATCHBins[i+1],0,2));
    cout << "mv_name: " << mv_name << endl;
    finder = (TH1D*)input->Get(finder_name);
    mv = (TH1D*)input->Get(mv_name);
    finder->Divide(mv);
    data->cd();
    finder->Clone();
    output->Write("",TFile::kOverwrite);
  }

  // copy data histograms for MUBAC
  for ( Int_t i = 0; i < MUBACNBins; ++i ) {
    TString finder_name = "Histograms/data/merged/DIMuon/MV_MUBAC_MuonEtaPtBins_";
    finder_name.Append(gInclude->FormatedDouble(MUBACBins[i],0,2));
    finder_name.Append("_");
    finder_name.Append(gInclude->FormatedDouble(MUBACBins[i+1],0,2));
    cout << "finder_name: " << finder_name << endl;
    TString mv_name = "Histograms/data/merged/DIMuon/MV_MuonEtaPtBins_";
    mv_name.Append(gInclude->FormatedDouble(MUBACBins[i],0,2));
    mv_name.Append("_");
    mv_name.Append(gInclude->FormatedDouble(MUBACBins[i+1],0,2));
    cout << "mv_name: " << mv_name << endl;
    finder = (TH1D*)input->Get(finder_name);
    mv = (TH1D*)input->Get(mv_name);
    finder->Divide(mv);
    data->cd();
    finder->Clone();
    output->Write("",TFile::kOverwrite);
  }

  // copy data histograms for BREMAT
  for ( Int_t i = 0; i < BREMATNBins; ++i ) {
    TString finder_name = "Histograms/mc/merged/jpsi/DIMuon/MV_BREMAT_MuonEtaPtBins_";
    finder_name.Append(gInclude->FormatedDouble(BREMATBins[i],0,2));
    finder_name.Append("_");
    finder_name.Append(gInclude->FormatedDouble(BREMATBins[i+1],0,2));
    cout << "finder_name: " << finder_name << endl;
    TString mv_name = "Histograms/mc/merged/jpsi/DIMuon/MV_MuonEtaPtBins_";
    mv_name.Append(gInclude->FormatedDouble(BREMATBins[i],0,2));
    mv_name.Append("_");
    mv_name.Append(gInclude->FormatedDouble(BREMATBins[i+1],0,2));
    cout << "mv_name: " << mv_name << endl;
    finder = (TH1D*)input->Get(finder_name);
    mv = (TH1D*)input->Get(mv_name);
    finder->Divide(mv);
    mc->cd();
    finder->Clone();
    output->Write("",TFile::kOverwrite);
  }

  // copy data histograms for MPMATCH
  for ( Int_t i = 0; i < MPMATCHNBins; ++i ) {
    TString finder_name = "Histograms/mc/merged/jpsi/DIMuon/MV_MPMATCH_MuonEtaPtBins_";
    finder_name.Append(gInclude->FormatedDouble(MPMATCHBins[i],0,2));
    finder_name.Append("_");
    finder_name.Append(gInclude->FormatedDouble(MPMATCHBins[i+1],0,2));
    cout << "finder_name: " << finder_name << endl;
    TString mv_name = "Histograms/mc/merged/jpsi/DIMuon/MV_MuonEtaPtBins_";
    mv_name.Append(gInclude->FormatedDouble(MPMATCHBins[i],0,2));
    mv_name.Append("_");
    mv_name.Append(gInclude->FormatedDouble(MPMATCHBins[i+1],0,2));
    cout << "mv_name: " << mv_name << endl;
    finder = (TH1D*)input->Get(finder_name);
    mv = (TH1D*)input->Get(mv_name);
    finder->Divide(mv);
    mc->cd();
    finder->Clone();
    output->Write("",TFile::kOverwrite);
  }

  // copy data histograms for MUBAC
  for ( Int_t i = 0; i < MUBACNBins; ++i ) {
    TString finder_name = "Histograms/mc/merged/jpsi/DIMuon/MV_MUBAC_MuonEtaPtBins_";
    finder_name.Append(gInclude->FormatedDouble(MUBACBins[i],0,2));
    finder_name.Append("_");
    finder_name.Append(gInclude->FormatedDouble(MUBACBins[i+1],0,2));
    cout << "finder_name: " << finder_name << endl;
    TString mv_name = "Histograms/mc/merged/jpsi/DIMuon/MV_MuonEtaPtBins_";
    mv_name.Append(gInclude->FormatedDouble(MUBACBins[i],0,2));
    mv_name.Append("_");
    mv_name.Append(gInclude->FormatedDouble(MUBACBins[i+1],0,2));
    cout << "mv_name: " << mv_name << endl;
    finder = (TH1D*)input->Get(finder_name);
    mv = (TH1D*)input->Get(mv_name);
    finder->Divide(mv);
    mc->cd();
    finder->Clone();
    output->Write("",TFile::kOverwrite);
  }

}

//_____________________________________________________________

TH1D* GInclude::CloneHistoWithWeight(TH1D *histo, Double_t weight) {
  //
  // clone histogram with weight giving the ration of applied correction
  // 1:   full correction
  // 0.5: half correction (if correction is 0.9, half correction applied is 0.95)

  TH1D *clone = (TH1D*)histo->Clone();

  for ( Int_t i = 1; i <= clone->GetNbinsX(); ++i ) {
    Double_t content = clone->GetBinContent(i);
    if ( content < 1 ) {
      content = (1-(1-content)*weight);
    } else {
      content = ((content-1)*weight)+1;
    }
    clone->SetBinContent(i,content);
  }
  return clone;
}

//_____________________________________________________________

Bool_t GInclude::CopyPtRelCorrections(TFile *input, TFile *output, Double_t charm_weight, Double_t lf_weight) {
  // 
  // copy PtRel_Correction-Histograms to histogram file in all charm and lf subdirectories
  // weight gives ratio of applied correction (1: full correction, 0.5: half of the correction)

  if ( !output->IsWritable() ) {
    cout << "output file: " << output->GetName() << " is not writeable!" << endl;
    return kFALSE;
  }

  GHistogrammer histogrammer;

  TList *charm_histos = new TList();
  TList *lf_histos = new TList();

  TDirectory *input_dir = (TDirectory*)input->Get("PtRel_Corrections");
  if ( input_dir == 0 ) {
    cout << "Could not find PtRel_Corrections directory in input file: " << input->GetName() << endl;
    return kFALSE;
  }

  input_dir->cd();

  TKey *key = 0;
  TObject *obj = 0;
  TIter nextkey(input_dir->GetListOfKeys());
  while ( (key = (TKey*)nextkey()) ) {
    obj = key->ReadObj();
    if (obj->IsA()->InheritsFrom("TH1D")) {
      charm_histos->Add(CloneHistoWithWeight((TH1D*)obj,charm_weight));
      lf_histos->Add(CloneHistoWithWeight((TH1D*)obj,lf_weight));
    }
  }

  TObjString *period = 0;
  TObjString *type = 0;
  TObjString *subdir = 0;
  TH1D *histo = 0;
  TH1D *new_histo = 0;

  // copy to subdirs in types in  periods
  TIter nextperiod(histogrammer.GetPeriods());
  while ( (period = (TObjString*)nextperiod()) ) {
    TIter nexttype(histogrammer.GetTypes());
    while ( (type = (TObjString*)nexttype()) ) {
      TIter nextsubdir(histogrammer.GetSubdirs());
      TString temp = "";
      while ( (subdir = (TObjString*)nextsubdir()) ) {
	temp = "Histograms/mc/";
	temp.Append(period->GetString());
	temp.Append("/");
	temp.Append(type->GetString());
	temp.Append("/");
	temp.Append(subdir->GetString());
	temp.Append("/MJMatch");
	TDirectory *dir = (TDirectory*)output->Get(temp);
	if ( dir != 0 ) {
	  cout << "dir: " << temp << endl;
	  dir->cd();
	  if ( type->GetString().Contains("c") ) {
	    TIter nexthisto(charm_histos);
	    while ( (histo = (TH1D*)nexthisto()) ) {
	      new_histo = (TH1D*)histo->Clone();
	      new_histo->Write("",kOverwrite);
	      cout << "histogram: " << new_histo->GetName() << endl;
	      output->Save();
	      output->ReadKeys();
	    }
	  } else if ( type->GetString().Contains("lf") ) {
	    TIter nexthisto(lf_histos);
	    while ( (histo = (TH1D*)nexthisto()) ) {
	      new_histo = (TH1D*)histo->Clone();
	      cout << "histogram: " << new_histo->GetName() << endl;
	      new_histo->Write("",kOverwrite);
	      output->Save();
	      output->ReadKeys();
	    }
	  } 
	}
      }
    }
  }

  // copy to merged subdirs in types in periods
  TIter nextperiod2(histogrammer.GetPeriods());
  while ( (period = (TObjString*)nextperiod2()) ) {
    TIter nexttype(histogrammer.GetTypes());
    while ( (type = (TObjString*)nexttype()) ) {
      TString temp = "";
      temp = "Histograms/mc/";
      temp.Append(period->GetString());
      temp.Append("/");
      temp.Append(type->GetString());
      temp.Append("/merged/MJMatch");
      TDirectory *dir = (TDirectory*)output->Get(temp);
      if ( dir != 0 ) {
	cout << "dir: " << temp << endl;
	dir->cd();
	if ( type->GetString().Contains("c") ) {
	  TIter nexthisto(charm_histos);
	  while ( (histo = (TH1D*)nexthisto()) ) {
	    new_histo = (TH1D*)histo->Clone();
	    cout << "histogram: " << new_histo->GetName() << endl;
	    new_histo->Write("",kOverwrite);
	    output->Save();
	    output->ReadKeys();
	  }
	} else if ( type->GetString().Contains("lf") ) {
	  TIter nexthisto(lf_histos);
	  while ( (histo = (TH1D*)nexthisto()) ) {
	    new_histo = (TH1D*)histo->Clone();
	    cout << "histogram: " << new_histo->GetName() << endl;
	    new_histo->Write("",kOverwrite);
	    output->Save();
	    output->ReadKeys();
	  } 
	}
      }
    }
  }

  // copy to types in merged dir
  TIter nexttype(histogrammer.GetTypes());
  while ( (type = (TObjString*)nexttype()) ) {
    TString temp = "";
    temp = "Histograms/mc/merged/";
    temp.Append(type->GetString());
    temp.Append("/MJMatch");
    TDirectory *dir = (TDirectory*)output->Get(temp);
    if ( dir != 0 ) {
      cout << "dir: " << temp << endl;
      dir->cd();
      if ( type->GetString().Contains("c") ) {
	TIter nexthisto(charm_histos);
	while ( (histo = (TH1D*)nexthisto()) ) {
	  new_histo = (TH1D*)histo->Clone();
	  cout << "histogram: " << new_histo->GetName() << endl;
	  new_histo->Write("",kOverwrite);
	  output->Save();
	  output->ReadKeys();
	}
      } else if ( type->GetString().Contains("lf") ) {
	TIter nexthisto(lf_histos);
	while ( (histo = (TH1D*)nexthisto()) ) {
	  new_histo = (TH1D*)histo->Clone();
	  cout << "histogram: " << new_histo->GetName() << endl;
	  new_histo->Write("",kOverwrite);
	  output->Save();
	  output->ReadKeys();
	}
      }
    }
  }

  return kTRUE;
}
