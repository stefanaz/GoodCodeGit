//
// GPictureMaker.cxx
//
// $Author: kahle $
// $Date: 2005/04/08 14:17:36 $
// $Revision: 1.109 $
//

#include <GPictureMaker.h>

#ifndef GUT_GInclude
#include <GInclude.h>
#endif

#ifndef __CINT__
ClassImp(GPictureMaker)
#endif

GPictureMaker *gPictureMaker = 0;

//_____________________________________________________________
// GPictureMaker
//
// class for picture belongings
//
GPictureMaker::GPictureMaker() : TObject() {
  //
  // GPictureMaker normal constructor
  if ( gDebug ) cout << endl << "GPictureMaker::GPictureMaker normal ctor called" << endl << endl;

  // set errorignorlevel to neglect light error messages
  if ( !gDebug )
    gErrorIgnoreLevel = 2001;

  // initialize global include pointer;
  gPictureMaker = this;

  // check gutcodedir
  fGutCodeDir = gSystem->Getenv("GUTCODEDIR");
  if ( fGutCodeDir.Length() == 0 ) {
    cout << "$GUTCODEDIR not set" << endl;
    return;
  }
  if ( !fGutCodeDir.EndsWith("/") ) {
    fGutCodeDir.Append("/");
  }

  // check convert
  fConvert = gSystem->Getenv("CONVERTLOCATION");
  if ( fConvert.Length() == 0 ) {
    cout << "$CONVERTLOCATION not set, please set it to location of convert-executable" << endl;
    return;
  }
  if ( fConvert.EndsWith("/") ) {
    fConvert.Remove(fConvert.Length()-1);
  }

  // initialize canvas
  fCanvas = 0;

  // initialize booleans
  fPsFirstDirectory = kFALSE;

  // initialize labels
  fPsLabel     = new TPaveLabel(0.05,0.3,0.95,0.6,"BLANK");
  fPsTimeLabel = new TPaveLabel(0.5,0.8,0.95,0.95,"BLANK");
  fPsLogyLabel = new TPaveLabel(0.5,0.05,0.95,0.2,"LOGY");

  // initialize variables
  fInputDir        = ".";
  fDirectory       = ".";
  fMode            = "";
  fOutputFile      = "";
  fFile            = 0;
  fTime            = "";
  fHTMLTop         = 0;
  fHTML            = 0;
  fHTMLTopName     = "";
  fHTMLTopSavedDir = "";
  fScaleFactor     = 50.0;

  // initialize time
  fTime = this->GetTime();

  InitLists();

}

//_____________________________________________________________

GPictureMaker::GPictureMaker(int argc, char **argv) : TObject() {
  //
  // GPictureMaker command line constructor
  if ( gDebug ) cout << endl << "GPictureMaker::GPictureMaker command line ctor called" << endl << endl;

  // set errorignorlevel to neglect light error messages
  if ( !gDebug )
    gErrorIgnoreLevel = 2001;

  // initialize global include pointer;
  gPictureMaker = this;

  // check gutcodedir
  fGutCodeDir = gSystem->Getenv("GUTCODEDIR");
  if ( fGutCodeDir.Length() == 0 ) {
    cout << "$GUTCODEDIR not set" << endl;
    return;
  }
  if ( !fGutCodeDir.EndsWith("/") ) {
    fGutCodeDir.Append("/");
  }

  // check convert
  fConvert = gSystem->Getenv("CONVERTLOCATION");
  if ( fConvert.Length() == 0 ) {
    cout << "$CONVERTLOCATION not set, please set it to location of convert-executable" << endl;
    return;
  }
  if ( fConvert.EndsWith("/") ) {
    fConvert.Remove(fConvert.Length()-1);
  }

  // initialize global includes
  GInclude *include = new GInclude();

  // set style
  TStyle *style = include->MySetStyle();
  style->cd();

  // initialize canvas
  fCanvas = 0;

  // initialize booleans
  fPsFirstDirectory = kFALSE;

  // initialize labels
  fPsLabel     = new TPaveLabel(0.05,0.3,0.95,0.6,"BLANK");
  fPsTimeLabel = new TPaveLabel(0.5,0.8,0.95,0.95,"BLANK");
  fPsLogyLabel = new TPaveLabel(0.5,0.05,0.95,0.2,"LOGY");

  // initialize variables
  fInputDir        = ".";
  fDirectory       = ".";
  fOutputFile      = "";
  fMode            = "";
  fFile            = 0;
  fTime            = "";
  fHTMLTop         = 0;
  fHTML            = 0;
  fHTMLTopName     = "";
  fHTMLTopSavedDir = "";
  fScaleFactor     = 50.0;

  // initialize time
  fTime = this->GetTime();

  InitLists();

  this->DecodeCommandline(argc,argv);
}

//_____________________________________________________________

GPictureMaker::~GPictureMaker() {
  //
  // GPictureMaker default destructor
  if ( gDebug ) cout << endl << "GPictureMaker::~GPictureMaker dtor called" << endl << endl;

  if ( gInclude != 0 ) {
    delete gInclude;
    gInclude = 0;
  }

  if ( fPsLabel != 0 ) delete fPsLabel;
  if ( fPsTimeLabel != 0 ) delete fPsTimeLabel;
  if ( fPsLogyLabel != 0 ) delete fPsLogyLabel;

  if ( fPlotsPtRel != 0 ) {
    fPlotsPtRel->Delete();
    delete fPlotsPtRel;
  }
  if ( fPlotsImpact != 0 ) {
    fPlotsImpact->Delete();
    delete fPlotsImpact;
  }
  if ( fPlotsComparison != 0 ) {
    fPlotsComparison->Delete();
    delete fPlotsComparison;
  }
  if ( fPlots1D != 0 ) {
    fPlots1D->Delete();
    delete fPlots1D;
  }
  if ( fPlots1DMC != 0 ) {
    fPlots1DMC->Delete();
    delete fPlots1DMC;
  }
  if ( fPlots1DZoomed != 0 ) {
    fPlots1DZoomed->Delete();
    delete fPlots1DZoomed;
  }
  if ( fPlots1DMCZoomed != 0 ) {
    fPlots1DMCZoomed->Delete();
    delete fPlots1DMCZoomed;
  }
  if ( fPlots2D != 0 ) {
    fPlots2D->Delete();
    delete fPlots2D;
  }
  if ( fPlots2DMC != 0 ) {
    fPlots2DMC->Delete();
    delete fPlots2DMC;
  }
  if ( fPlots2DZoomed != 0 ) {
    fPlots2DZoomed->Delete();
    delete fPlots2DZoomed;
  }
  if ( fPlots2DMCZoomed != 0 ) {
    fPlots2DMCZoomed->Delete();
    delete fPlots2DMCZoomed;
  }
  if ( fPlotsEfficiencyBasename != 0 ) {
    fPlotsEfficiencyBasename->Delete();
    delete fPlotsEfficiencyBasename;
  }
  if ( fPlotsEfficiencyFinder != 0 ) {
    fPlotsEfficiencyFinder->Delete();
    delete fPlotsEfficiencyFinder;
  }
  if ( fPlotsEfficiencyRegion != 0 ) {
    fPlotsEfficiencyRegion->Delete();
    delete fPlotsEfficiencyRegion;
  }

}

//_____________________________________________________________

void GPictureMaker::MakePics(TFile *file, TString filename, TString directory, Int_t rows, Int_t columns, TString option) {
  //
  // wrapper function for
  // print all histograms in multi-page ps
  //
  //
  // give option LANDSCAPE or PORTRAIT
  // filename gives name of output-file
  // x gives number of columns
  // y gives number of rows
  if ( gDebug ) cout << endl << "GPictureMaker::MakePics() called" << endl << endl;

  // option
  option.ToUpper();

  // set batch to true
  Bool_t batch = gROOT->IsBatch();
  if ( !batch )
    gROOT->SetBatch(kTRUE);
  

  // reset variables for picture generation
  // check of option is enough
  fPsFileName = directory;
  if ( fPsFileName.BeginsWith(".") )
    fPsFileName = "";
  if ( (fPsFileName.Length() != 0) && (!fPsFileName.EndsWith("/")) )
    fPsFileName.Append("/");
  fPsFileName.Append(filename);

  if ( option.Contains("PORTRAIT") ) {
    fPsRows            = rows; 
    fPsColumns         = columns;
  } else if ( option.Contains("LANDSCAPE") ) {
    fPsRows            = columns; 
    fPsColumns         = rows;
  } else {
    fPsRows            = rows; 
    fPsColumns         = columns;
  }
  fPsCurrentRow      = 1;
  fPsCurrentColumn   = 1;


  // open ps file for drawing
  this->StartPsFile(file,option);

  fPsFirstInFile = kTRUE;

  // go through file and generate ps
  this->GoThroughFile(file,option);

  // close ps file for drawing
  this->EndPsFile(option);


  // restore batch level
  if ( !batch )
    gROOT->SetBatch(kFALSE);

}

//_____________________________________________________________

void GPictureMaker::FillPs(TString dirname, TH1 *histo, TString option) {
  //
  // print histogram in multi-page ps
  // 
  if ( gDebug ) cout << endl << "GPictureMaker::FillPS() called" << endl << endl;

  option.ToUpper();

  Int_t padNumber = (fPsCurrentRow-1) * fPsColumns + fPsCurrentColumn ;

  TString label = dirname;

  // write out pad if maximum is reached
  if ( (( padNumber > ( fPsRows * fPsColumns) ) || !label.Contains(fPsLabel->GetLabel()) ) 
       && !fPsFirstDirectory && !fPsFirstInFile) {
    fCanvas->SaveAs(fPsFileName.Data());
    fCanvas->Clear();
    fCanvas->Divide(fPsColumns,fPsRows);
    fPsCurrentRow    = 1;
    fPsCurrentColumn = 1;
    padNumber = (fPsCurrentRow-1) * fPsColumns + fPsCurrentColumn;
  }


  // first pad in directory
  if ( fPsFirstDirectory ) {

    fPsFirstInFile = kFALSE;

    // close old pad and write it out
    fCanvas->SaveAs(fPsFileName.Data());
    fCanvas->Clear();
    fCanvas->Divide(fPsColumns,fPsRows);
    fPsCurrentRow    = 1;
    fPsCurrentColumn = 1;
    padNumber = (fPsCurrentRow-1) * fPsColumns + fPsCurrentColumn;

    fCanvas->cd(padNumber);
    
    // TPaveLabel for time of picture generation
    TDatime time;
    TString timestring = "";
    if ( time.GetDay() < 10 ) 
      timestring.Append("0");
    timestring += time.GetDay();
    timestring.Append(".");
    if ( time.GetMonth() < 10 ) 
      timestring.Append("0");
    timestring += time.GetMonth();
    timestring.Append(".");
    timestring += time.GetYear();
    timestring.Append("  ");
    if ( time.GetHour() < 10 ) 
      timestring.Append("0");
    timestring += time.GetHour();
    timestring.Append(":");
    if ( time.GetMinute() < 10 ) 
      timestring.Append("0");
    timestring += time.GetMinute();
    timestring.Append(":");
    if ( time.GetSecond() < 10 ) 
      timestring.Append("0");
    timestring += time.GetSecond();

    // directory name
    fPsLabel->SetBorderSize(0);
    fPsLabel->SetFillColor(10);
    fPsLabel->SetLabel(dirname);
    fPsLabel->Draw();
    fPsTimeLabel->SetBorderSize(0);
    fPsTimeLabel->SetFillColor(10);
    fPsTimeLabel->SetLabel(timestring);
    fPsTimeLabel->Draw();
    if ( option.Contains("LOGPS") ) {
      fPsLogyLabel->SetBorderSize(0);
      fPsLogyLabel->SetFillColor(10);
      fPsLogyLabel->Draw();
    }

    // go one pad further
    this->PsIncreasePadNumber();
    padNumber = (fPsCurrentRow-1) * fPsColumns + fPsCurrentColumn;

    fPsFirstDirectory = kFALSE;

  }

  // go to right canvas
  fCanvas->cd(padNumber);

  // set logarythmic
  if ( option.Contains("LOGPS") )
    fCanvas->GetPad(padNumber)->SetLogy(1);
  else if ( option.Contains("PS") )
    fCanvas->GetPad(padNumber)->SetLogy(0);

  // draw histogram
  histo->Draw();

  // go one pad further
  this->PsIncreasePadNumber();

  // recalculate padnumber
  padNumber = (fPsCurrentRow-1) * fPsColumns + fPsCurrentColumn;

}
  
//_____________________________________________________________

Bool_t GPictureMaker::GoThroughFile(TFile *file, TString option) {
  //
  // go through file and perform action
  if ( gDebug ) cout << endl << "GPictureMaker::GoThroughFile() called" << endl << endl;

  // first read all directories in TString array
  // restricted to 5 levels of directories
  TString dirname = "";

  TDirectory *directory = (TDirectory*)file;
  dirname = this->GoThroughDirectory(dirname,directory,option);

  if ( fHTML != 0 ) {
    // caluclate how many directories up to go to top
    Int_t num = fHTMLTopSavedDir.CountChar(47) + 1;
    TString top = "";
    for ( Int_t i = 0; i < num; i++ ) {
      top.Append("../");
    }
    top.Append("gallery.html");
    this->HTMLEnd(fHTML,top,fTime,option);
    delete fHTML;
  }

  return kTRUE;
}
  
//_____________________________________________________________

TString GPictureMaker::GoThroughDirectory(TString dirname, TDirectory *directory, TString option) {
  //
  // go through directory and perform action
  if ( gDebug ) cout << endl << "GPictureMaker::GoThroughDirectory() called" << endl << endl;

  option.ToUpper();

  TObject *obj = 0;
  TKey    *key = 0;
  
  TIter nextkey(directory->GetListOfKeys());
  while ( (key = (TKey*)nextkey()) ) {
    obj = key->ReadObj();
    if (obj->IsA()->InheritsFrom("TDirectory")) {
      fPsFirstDirectory = kTRUE;
      directory = (TDirectory*)obj;
      dirname.Append("/");
      dirname.Append(directory->GetName());
      if ( dirname.EndsWith("/") ) dirname.Remove(dirname.Length()-1,1);
      if ( dirname.BeginsWith("/") ) dirname.Remove(0,1);
      if ( option.Contains("GALLERY"))
	this->MakeDir(dirname.Data());
      dirname = this->GoThroughDirectory(dirname,directory,option);
      dirname = gInclude->StripLastDir(dirname);
    } else if (obj->IsA()->InheritsFrom("TH1")) {
      if ( dirname.Length() == 0 ) {
	dirname = "TOP";
	this->MakeDir(dirname.Data());
      }
      if ( option.Contains("LOGPS") ) {
	option.Append(",LOGPS");
	this->FillPs(dirname.Data(), (TH1*)obj, option);
      } else if ( option.Contains("PS") ) {
	option.Append(",PS");
	this->FillPs(dirname.Data(), (TH1*)obj, option);
      } else if ( option.Contains("GALLERY") ) {
	// if directory changed, make entry to top html
	if ( fHTMLTopSavedDir != dirname ) {
	  fHTMLTopSavedDir = dirname.Data();
	  TString link = dirname.Data();
	  if ( !link.EndsWith("/") )
	    link.Append("/");
	  link.Append("gallery.html");
	  TString entry = dirname.Data();
	  entry.ReplaceAll("Histograms/","");
	  entry.ReplaceAll("/"," - ");
	  this->HTMLStreamTop(link,entry,option);
	  // if html in filling, end
	  if ( fHTML != 0 ) {
	    // caluclate how many directories up to go to top
	    Int_t num = fHTMLTopSavedDir.CountChar(47) + 1;
	    TString top = "";
	    for ( Int_t i = 0; i < num; i++ ) {
	      top.Append("../");
	    }
	    top.Append("gallery.html");
	    this->HTMLEnd(fHTML,top,fTime,option);
	    delete fHTML;
	  }
	  // start new html
	  // prepend link with fDirectory
	  TString toplink = fDirectory.Data();
	  if ( toplink.BeginsWith(".") )
	    toplink = "";
	  if ( (toplink.Length() != 0 ) && (!toplink.EndsWith("/")) )
	    toplink.Append("/");
	  toplink.Append(link.Data());
	  fHTML = new ofstream(toplink.Data());
	  this->HTMLStart(fHTML,entry,fFile->GetName(),option);
	}
	this->FillGallery(dirname.Data(), (TH1*)obj, option);
      }

    }
  }
  if ( dirname.Contains("TOP") ) {
    dirname = "";
  }
  return dirname;

}
  
//_____________________________________________________________

Bool_t GPictureMaker::StartPsFile(TFile *file, TString option) {
  //
  // create canvas and start ps file
  if ( gDebug ) cout << endl << "GPictureMaker::StartPsFile() called" << endl << endl;
  
  option.ToUpper();

  // delete old canvas
  if ( fCanvas ) {
    delete fCanvas;
    fCanvas = 0;
  }

  // canvas
  if ( !fCanvas ) {
    if ( option.Contains("PORTRAIT") )
      fCanvas = new TCanvas("canvas","canvas",600,800);
    else if ( option.Contains("LANDSCAPE") )
      fCanvas = new TCanvas("canvas","canvas",800,600);
    else
      fCanvas = new TCanvas("canvas","canvas",600,800);    
  } 

  // TPaveLabel for time of picture generation
  TDatime time;
  TString timestring = "";
  if ( time.GetDay() < 10 ) 
    timestring.Append("0");
  timestring += time.GetDay();
  timestring.Append(".");
  if ( time.GetMonth() < 10 ) 
    timestring.Append("0");
  timestring += time.GetMonth();
  timestring.Append(".");
  timestring += time.GetYear();
  timestring.Append("  ");
  if ( time.GetHour() < 10 ) 
    timestring.Append("0");
  timestring += time.GetHour();
  timestring.Append(":");
  if ( time.GetMinute() < 10 ) 
    timestring.Append("0");
  timestring += time.GetMinute();
  timestring.Append(":");
  if ( time.GetSecond() < 10 ) 
    timestring.Append("0");
  timestring += time.GetSecond();
  
  // directory name
  fPsLabel->SetBorderSize(0);
  fPsLabel->SetFillColor(10);
  fPsLabel->SetLabel(file->GetName());
  fPsLabel->Draw();
  fPsTimeLabel->SetBorderSize(0);
  fPsTimeLabel->SetFillColor(10);
  fPsTimeLabel->SetLabel(timestring);
  fPsTimeLabel->Draw();
  if ( option.Contains("LOGPS") ) {
    fPsLogyLabel->SetBorderSize(0);
    fPsLogyLabel->SetFillColor(10);
    fPsLogyLabel->Draw();
  }

  TString startfilename = fPsFileName.Data();
  startfilename.Append("[");
  fCanvas->SaveAs(startfilename.Data());

  return kTRUE;
}

//_____________________________________________________________

Bool_t GPictureMaker::EndPsFile(TString option) {
  //
  // delete canvas and end ps file
  if ( gDebug ) cout << endl << "GPictureMaker::EndPsFile() called" << endl << endl;
  
  TString endfilename = fPsFileName.Data();
  endfilename.Append("]");
  fCanvas->SaveAs(endfilename.Data());

  // delete old canvas
  if ( fCanvas ) {
    delete fCanvas;
    fCanvas = 0;
  }

  return kTRUE;
}

//_____________________________________________________________

Int_t GPictureMaker::PsIncreasePadNumber() {
  //
  // increase pad number in given borders
  if ( gDebug ) cout << endl << "GPictureMaker::PsIncreasePadNumber() called" << endl << endl;

  if ( ( (fPsCurrentColumn + 1)>fPsColumns) ) {
    fPsCurrentRow += 1;
    fPsCurrentColumn = 1;
  } else {
    fPsCurrentColumn += 1;
  }

  return ((fPsCurrentRow -1 )*fPsColumns + fPsCurrentColumn);
}

//_____________________________________________________________

void GPictureMaker::MakeGallery(TFile *file, TString directory, TString option) {
  //
  // make html gallery of all plots in file in directory
  if ( gDebug ) cout << endl << "GPictureMaker::MakeGallery() called" << endl << endl;

  // make directory absolute directory
  fGalleryDirectory.Append(directory);
  if ( fGalleryDirectory.BeginsWith(".")) {
    fGalleryDirectory = gSystem->WorkingDirectory();
    fGalleryDirectory.Append("/");
  }

  // option string
  option.ToUpper();

  option.Append(",GALLERY");

  // set batch to true
  Bool_t batch = gROOT->IsBatch();
  if ( !batch )
    gROOT->SetBatch(kTRUE);

  this->StartGallery(option);

  this->GoThroughFile(file,option);

  this->EndGallery(option);

  // restore batch level
  if ( !batch )
    gROOT->SetBatch(kFALSE);

}

//_____________________________________________________________

Bool_t GPictureMaker::MakeDir(TString directory) {
  //
  // make directory if it does not exist
  if ( gDebug ) cout << endl << "GPictureMaker::MakeDir() called" << endl << endl;

  TString dir = fGalleryDirectory;
  dir.Append("/");
  dir.Append(directory);

  gSystem->mkdir(dir.Data(),kTRUE);

  return kTRUE;

}

//_____________________________________________________________

void GPictureMaker::FillGallery(TString dirname, TH1 *histo, TString option) {
  //
  // make gif and eps of histogram
  // 
  if ( gDebug ) cout << endl << "GPictureMaker::FillGallery() called" << endl << endl;

  option.ToUpper();

  fCanvas->Clear();

  fCanvas->cd();

  fCanvas->SetLogy(0);

  // set histogram color to red
  histo->SetLineColor(2);

  // draw histogram
  histo->Draw();

  // nice histogram
  gInclude->NicePlot(fCanvas);

  TString dir = fGalleryDirectory;
  dir.Append("/");
  dir.Append(dirname);
  dir.Append("/");

  this->GenHTMLPics(fCanvas,histo->GetName(),dir.Data(),histo->GetTitle(),option);

}
  
//_____________________________________________________________

Bool_t GPictureMaker::StartGallery(TString option) {
  //
  // create canvas and start gallery
  if ( gDebug ) cout << endl << "GPictureMaker::StartGallery() called" << endl << endl;
  
  option.ToUpper();

  // delete old canvas
  if ( fCanvas ) {
    delete fCanvas;
    fCanvas = 0;
  }

  // canvas
  if ( !fCanvas ) {
    fCanvas = new TCanvas("canvas","canvas",600,400);
  } 

  // start html stream
  fHTMLTopName = fGalleryDirectory.Data();
  if ( !fHTMLTopName.EndsWith("/") )
    fHTMLTopName.Append("/");
  fHTMLTopName.Append("gallery.html");
  
  fHTMLTop = new ofstream(fHTMLTopName.Data());

  TString title = "Gallery";
  TString filename = fFile->GetName();

  this->HTMLStart(fHTMLTop,title,filename,"TOP");

  return kTRUE;
}

//_____________________________________________________________

Bool_t GPictureMaker::EndGallery(TString option) {
  //
  // delete canvas and end gallery
  if ( gDebug ) cout << endl << "GPictureMaker::EndGallery() called" << endl << endl;
  
  // delete old canvas
  if ( fCanvas ) {
    delete fCanvas;
    fCanvas = 0;
  }

  option.Append(",TOP");

  TString top = "gallery.html";

  // end top html stream
  this->HTMLEnd(fHTMLTop,top,fTime,option);
  delete fHTMLTop;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GPictureMaker::MakeSpecial(TFile *file, TString directory, TString option) {
  //
  // make special pictures
  if ( gDebug ) cout << endl << "GPictureMaker::MakeSpecial() called" << endl << endl;

  TList *entries = new TList();
  Bool_t has_entry = kFALSE;

  // do pictures for all periods
  if ( DoPicturesPeriods() ) {
    GHistogrammer grammer;
    TList *periods = grammer.GetPeriods();

    TIter nextperiod(periods);
    while ( TObjString *period = (TObjString*)nextperiod() ) {
      TString tempdir = directory;
      if ( tempdir.BeginsWith(".") ) {
	tempdir = "";
      } else if ( !tempdir.EndsWith("/") && ( tempdir.Length() != 0 ) ) {
	tempdir.Append("/");
      }
      tempdir.Append(period->GetString());

      if ( MakeSpecialPeriod(file,period->GetString(),tempdir,option) ) {
	entries->Add(new TObjString(period->GetString()));
	has_entry = kTRUE;
      }
    }
  }

  TString tempdir = directory;

  if ( tempdir.BeginsWith(".") ) {
    tempdir = "";
  } else if ( !tempdir.EndsWith("/") && ( tempdir.Length() != 0 ) ) {
    tempdir.Append("/");
  }
  tempdir.Append("complete");
  if ( MakeSpecialComplete(file,tempdir,option) ) {
    entries->Add(new TObjString("complete"));
    has_entry = kTRUE;
  }

  if ( has_entry ) {

    TString tempoption = option;
    tempoption.Append(",TOP");

    // start top html
    TString tempdir = directory;
    if ( tempdir.BeginsWith(".") ) {
      tempdir = "";
    } else if ( tempdir.EndsWith("/") && ( tempdir.Length() != 0 ) )
      tempdir.Remove(tempdir.Length()-1,1);
    // check whether tempdir exists, else generate
    gSystem->mkdir(tempdir.Data(),kTRUE);
    TString name = tempdir.Data();
    name.Append("/gallery.html");
    ofstream *top = new ofstream(name.Data());
    TString title = "Special gallery";
    TString filename = "special_gallery";
    HTMLStart(top,title,filename,tempoption);

    TIter nextentry(entries);
    while (TObjString *entry = (TObjString*)nextentry() ) {
      TString link = entry->GetString();
      link.Append("/gallery.html");
      HTMLStreamTop(top,link,entry->GetString(),tempoption);
    }

    HTMLEnd(top,"../../gallery.html",fTime,tempoption);
    delete top;  // add leading Histograms directory to input histograms
  
  }

  entries->Delete();
  delete entries;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GPictureMaker::MakeSpecialPeriod(TFile *file, TString period, TString directory, TString option) {
  //
  // make special pictures
  if ( gDebug ) cout << endl << "GPictureMaker::MakeSpecialPeriod() called" << endl << endl;

  TList *entries = new TList();
  Bool_t has_entry = kFALSE;

  TString temptopdir = directory;

  if ( temptopdir.BeginsWith(".") ) {
    temptopdir = "";
  } else if ( !temptopdir.EndsWith("/") && ( temptopdir.Length() != 0 ) ) {
    temptopdir.Append("/");
  }

  // make ptrel plots
  if ( DoPicturesPtRel() ) {
    TString tempdir = temptopdir;
    tempdir.Append("ptrel");

    if ( MakeSpecialPeriodPtRel(file,period,tempdir,option) ) {
      entries->Add(new TObjString("ptrel"));
      has_entry = kTRUE;
    }
  }

  // make impact parameter plots
  if ( DoPicturesImpact() ) {
    TString tempdir = temptopdir;
    tempdir.Append("impact");

    if ( MakeSpecialPeriodImpact(file,period,tempdir,option) ) {
      entries->Add(new TObjString("impact"));
      has_entry = kTRUE;
    }
  }

  // make data mc comparison plots using ptrel fit 1
  if ( DoPicturesPtRel_1().Length() != 0 ) {
    TString ptrelhistogramname = DoPicturesPtRel_1();
    TString tempdir = temptopdir;
    tempdir.Append("comparison_ptrel_1");
    
    TString tempoption = option;
    tempoption.Append(",PTREL");
    
    if ( MakeSpecialPeriodComparison(file,period,tempdir,ptrelhistogramname,tempoption) ) {
      entries->Add(new TObjString("comparison_ptrel_1"));
      has_entry = kTRUE;
    }
  }

  // make data mc comparison plots using ptrel fit 2
  if ( DoPicturesPtRel_2().Length() != 0 ) {
    TString ptrelhistogramname = DoPicturesPtRel_2();
    TString tempdir = temptopdir;
    tempdir.Append("comparison_ptrel_2");

    TString tempoption = option;
    tempoption.Append(",PTREL");
    
    if ( MakeSpecialPeriodComparison(file,period,tempdir,ptrelhistogramname,tempoption) ) {
      entries->Add(new TObjString("comparison_ptrel_2"));
      has_entry = kTRUE;
    }
  }
  
  // make data mc comparison plots using lumi weighting
  if ( DoPicturesLumi() ) {
    TString ptrelhistogramname = "";
    TString tempdir = temptopdir;
    tempdir.Append("comparison_lumi");

    TString tempoption = option;
    tempoption.Append(",LUMI");

    if (  MakeSpecialPeriodComparison(file,period,tempdir,ptrelhistogramname,tempoption) ) {
      entries->Add(new TObjString("comparison_lumi"));
      has_entry = kTRUE;
    }
  }
  
  // make special 1D histograms
  if ( DoPictures1D() ) {
    TString tempdir = temptopdir;
    tempdir.Append("1D");

    if (  MakeSpecialPeriod1D(file,period,tempdir,option) ) {
      entries->Add(new TObjString("1D"));
      has_entry = kTRUE;
    }
  }
  
  // make special 2D histograms
  if ( DoPictures2D() ) {
    TString tempdir = temptopdir;
    tempdir.Append("2D");

    if (  MakeSpecialPeriod2D(file,period,tempdir,option) ) {
      entries->Add(new TObjString("2D"));
      has_entry = kTRUE;
    }
  }
  
  // make efficiency histograms
  if ( DoPicturesEff() ) {
    TString tempdir = temptopdir;
    tempdir.Append("efficiencies");
    
    if (  MakeSpecialPeriodEfficiency(file,period,tempdir,option) ) {
      entries->Add(new TObjString("efficiencies"));
      has_entry = kTRUE;
    }
    
    // make efficiency histograms
    tempdir = temptopdir;
    tempdir.Append("corrections");
    
    if (  MakeSpecialPeriodCorrection(file,period,tempdir,option) ) {
      entries->Add(new TObjString("corrections"));
      has_entry = kTRUE;
    }
  }
  
  if ( has_entry ) {
    
    TString tempoption = option;
    tempoption.Append(",TOP");

    // start top html
    TString tempdir = directory;
    if ( tempdir.BeginsWith(".") ) {
      tempdir = "";
    } else if ( tempdir.EndsWith("/") && ( tempdir.Length() != 0 ) )
      tempdir.Remove(tempdir.Length()-1,1);
    // check whether tempdir exists, else generate
    gSystem->mkdir(tempdir.Data(),kTRUE);
    TString name = tempdir.Data();
    name.Append("/gallery.html");
    ofstream *top = new ofstream(name.Data());
    TString title = "Special gallery for ";
    title.Append(period);
    TString filename = "special_gallery_";
    filename.Append(period);
    HTMLStart(top,title,filename,tempoption);

    TIter nextentry(entries);
    while (TObjString *entry = (TObjString*)nextentry() ) {
      TString link = entry->GetString();
      link.Append("/gallery.html");
      TString title = "";
      if ( link.Contains("comparison") ) {
	if ( link.Contains("ptrel_2") ) {
	  title.Append("Data-MC Comparison Plots using PtRel Fit: ");
	  title.Append(DoPicturesPtRel_2());
	} else if ( link.Contains("ptrel_1") ) {
	  title.Append("Data-MC Comparison Plots using PtRel Fit: ");
	  title.Append(DoPicturesPtRel_1());
	} else if ( link.Contains("lumi") ) {
	  title.Append("Data-MC Comparison Plots using Lumi Weighting");
	}
      } else {
	if ( link.Contains("ptrel") ) {
	  title.Append("PtRel Plots");
	} else if ( link.Contains("impact") ) {
	  title.Append("Impact Parameter Plots");
	} else if ( link.Contains("1D") ) {
	  title.Append("Special one dimensionale plots");
	} else if ( link.Contains("2D") ) {
	  title.Append("Special two dimensionale plots");
	} else if ( link.Contains("efficiencies") ) {
	  title.Append("Muon efficiency plots");
	} else if ( link.Contains("corrections") ) {
	  title.Append("Muon efficiency correction factors");
	}	
      }
	
      HTMLStreamTop(top,link,title,tempoption);
    }

    HTMLEnd(top,"../gallery.html",fTime,tempoption);
    delete top;  // add leading Histograms directory to input histograms
  
  }

  entries->Delete();
  delete entries;

  return has_entry;
}

//_____________________________________________________________

Bool_t GPictureMaker::MakeSpecialPeriodEfficiency(TFile *file, TString period, TString directory, TString option) {
  //
  // make efficiency pictures
  if ( gDebug ) cout << endl << "GPictureMaker::MakeSpecialPeriodEfficiency() called" << endl << endl;

  TList *entries = new TList();
  Bool_t has_entry = kFALSE;

  TString temptopdir = directory;

  if ( temptopdir.BeginsWith(".") ) {
    temptopdir = "";
  } else if ( !temptopdir.EndsWith("/") && ( temptopdir.Length() != 0 ) ) {
    temptopdir.Append("/");
  }

  // make data efficiency plots
  TString tempdir = temptopdir;
  tempdir.Append("data");

  if ( MakeSpecialPeriodEfficiencyData(file,period,tempdir,option) ) {
    entries->Add(new TObjString("data"));
    has_entry = kTRUE;
  }

  // make mc efficiency plots
  tempdir = temptopdir;
  tempdir.Append("mc");

  if ( MakeSpecialPeriodEfficiencyMC(file,period,tempdir,option) ) {
    entries->Add(new TObjString("mc"));
    has_entry = kTRUE;
  }

  if ( has_entry ) {
    
    TString tempoption = option;
    tempoption.Append(",TOP");

    // start top html
    TString tempdir = directory;
    if ( tempdir.BeginsWith(".") ) {
      tempdir = "";
    } else if ( tempdir.EndsWith("/") && ( tempdir.Length() != 0 ) )
      tempdir.Remove(tempdir.Length()-1,1);
    // check whether tempdir exists, else generate
    gSystem->mkdir(tempdir.Data(),kTRUE);
    TString name = tempdir.Data();
    name.Append("/gallery.html");
    ofstream *top = new ofstream(name.Data());
    TString title = "Muon efficiency gallery for ";
    title.Append(period);
    TString filename = "muon_efficiency_gallery_";
    filename.Append(period);
    HTMLStart(top,title,filename,tempoption);

    TIter nextentry(entries);
    while (TObjString *entry = (TObjString*)nextentry() ) {
      TString link = entry->GetString();
      link.Append("/gallery.html");
      TString title = "";
      if ( link.Contains("data") ) {
	title.Append("Muon efficiency plots from data");
      } else if ( link.Contains("mc") ) {
	title.Append("Muon efficiency plots from MC");
      }	
	
      HTMLStreamTop(top,link,title,tempoption);
    }

    HTMLEnd(top,"../gallery.html",fTime,tempoption);
    delete top;  // add leading Histograms directory to input histograms
  
  }

  entries->Delete();
  delete entries;

  return has_entry;
}

//_____________________________________________________________

Bool_t GPictureMaker::MakeSpecialPeriodEfficiencyMC(TFile *file, TString period, TString directory, TString option) {
  //
  // make mc efficiency pictures
  if ( gDebug ) cout << endl << "GPictureMaker::MakeSpecialPeriodEfficiencyMC() called" << endl << endl;

  TList *entries = new TList();
  Bool_t has_entry = kFALSE;

  GHistogrammer grammer;
  TList *types = grammer.GetTypes();

  TString temptopdir = directory;

  if ( temptopdir.BeginsWith(".") ) {
    temptopdir = "";
  } else if ( !temptopdir.EndsWith("/") && ( temptopdir.Length() != 0 ) ) {
    temptopdir.Append("/");
  }

  // make mc efficiency plots for single type
  TIter nexttype(types);
  while (TObjString *type = (TObjString*)nexttype() ) {
    TString tempoption = option;
    option.Append(",MC");
    TString tempdir = temptopdir;
    tempdir.Append(type->GetString());
    if ( MakeSpecialPeriodEfficiencyMCType(file,period,tempdir,type->GetString(),tempoption) ) {
      entries->Add(new TObjString(type->GetString()));
      has_entry = kTRUE;
    }

  }

  // make mc efficiency plots for combination of two types
  TIter nexttype2(types);
  while (TObjString *type2 = (TObjString*)nexttype2() ) {
    TIter nexttype3(nexttype2);
    while (TObjString *type3 = (TObjString*)nexttype3() ) {

      TString tempoption = option;
      option.Append(",MC");

      TString temptype = type2->GetString();
      temptype.Append(",");
      temptype.Append(type3->GetString());

      TString tempdiradd = type2->GetString();
      tempdiradd.Append("_");
      tempdiradd.Append(type3->GetString());

      // make mc efficiency plots
      TString tempdir = temptopdir;
      tempdir.Append(tempdiradd);

      if ( MakeSpecialPeriodEfficiencyMCType(file,period,tempdir,temptype,tempoption) ) {
      entries->Add(new TObjString(tempdiradd));
      has_entry = kTRUE;
      }
    }
  }

  // make mc efficiency plots for combination of three types
  TIter nexttype4(types);
  while (TObjString *type4 = (TObjString*)nexttype4() ) {
    TIter nexttype5(nexttype4);
    while (TObjString *type5 = (TObjString*)nexttype5() ) {
      TIter nexttype6(nexttype5);
      while (TObjString *type6 = (TObjString*)nexttype6() ) {

	TString tempoption = option;
	option.Append(",MC");

	TString temptype = type4->GetString();
	temptype.Append(",");
	temptype.Append(type5->GetString());
	temptype.Append(",");
	temptype.Append(type6->GetString());

	TString tempdiradd = type4->GetString();
	tempdiradd.Append("_");
	tempdiradd.Append(type5->GetString());
	tempdiradd.Append("_");
	tempdiradd.Append(type6->GetString());

	// make mc efficiency plots
	TString tempdir = temptopdir;
	tempdir.Append(tempdiradd);
	
	if ( MakeSpecialPeriodEfficiencyMCType(file,period,tempdir,temptype,tempoption) ) {
	  entries->Add(new TObjString(tempdiradd));
	  has_entry = kTRUE;
	}
      }
    }
  }

  // make mc efficiency plots for combination of four types
  TIter nexttype7(types);
  while (TObjString *type7 = (TObjString*)nexttype7() ) {
    TIter nexttype8(nexttype7);
    while (TObjString *type8 = (TObjString*)nexttype8() ) {
      TIter nexttype9(nexttype8);
      while (TObjString *type9 = (TObjString*)nexttype9() ) {
	TIter nexttype10(nexttype9);
	while (TObjString *type10 = (TObjString*)nexttype10() ) {
	  
	  TString tempoption = option;
	  option.Append(",MC");
	  
	  TString temptype = type7->GetString();
	  temptype.Append(",");
	  temptype.Append(type8->GetString());
	  temptype.Append(",");
	  temptype.Append(type9->GetString());
	  temptype.Append(",");
	  temptype.Append(type10->GetString());
	  
	  TString tempdiradd = type7->GetString();
	  tempdiradd.Append("_");
	  tempdiradd.Append(type8->GetString());
	  tempdiradd.Append("_");
	  tempdiradd.Append(type9->GetString());
	  tempdiradd.Append("_");
	  tempdiradd.Append(type10->GetString());
	  
	  // make mc efficiency plots
	  TString tempdir = temptopdir;
	  tempdir.Append(tempdiradd);
	
	  if ( MakeSpecialPeriodEfficiencyMCType(file,period,tempdir,temptype,tempoption) ) {
	    entries->Add(new TObjString(tempdiradd));
	    has_entry = kTRUE;
	  }
	}
      }
    }
  }

  if ( has_entry ) {
    
    TString tempoption = option;
    tempoption.Append(",TOP");

    // start top html
    TString tempdir = directory;
    if ( tempdir.BeginsWith(".") ) {
      tempdir = "";
    } else if ( tempdir.EndsWith("/") && ( tempdir.Length() != 0 ) )
      tempdir.Remove(tempdir.Length()-1,1);
    // check whether tempdir exists, else generate
    gSystem->mkdir(tempdir.Data(),kTRUE);
    TString name = tempdir.Data();
    name.Append("/gallery.html");
    ofstream *top = new ofstream(name.Data());
    TString title = "Muon MC efficiency gallery for ";
    title.Append(period);
    TString filename = "muon_mc_efficiency_gallery_";
    filename.Append(period);
    HTMLStart(top,title,filename,tempoption);

    TIter nextentry(entries);
    while (TObjString *entry = (TObjString*)nextentry() ) {
      TString link = entry->GetString();
      link.Append("/gallery.html");
      TString title = "";
      if ( link.Contains("b_c_lf_jpsi") ) {
	title.Append("Muon efficiency plots from b, c, lf and jpsi MC");
      } else if ( link.Contains("b_c_lf") ) {
	title.Append("Muon efficiency plots from b, c and lf MC");
      } else if ( link.Contains("b_c_jpsi") ) {
	title.Append("Muon efficiency plots from b, c and jpsi MC");
      } else if ( link.Contains("b_lf_jpsi") ) {
	title.Append("Muon efficiency plots from b, lf and jpsi MC");
      } else if ( link.Contains("c_lf_jpsi") ) {
	title.Append("Muon efficiency plots from c, lf and jpsi MC");
      } else if ( link.Contains("b_c") ) {
	title.Append("Muon efficiency plots from b and c MC");
      } else if ( link.Contains("b_lf") ) {
	title.Append("Muon efficiency plots from b and lf MC");
      } else if ( link.Contains("b_jpsi") ) {
	title.Append("Muon efficiency plots from b and jpsi MC");
      } else if ( link.Contains("c_lf") ) {
	title.Append("Muon efficiency plots from c and lf MC");
      } else if ( link.Contains("c_jpsi") ) {
	title.Append("Muon efficiency plots from c and jpsi MC");
      } else if ( link.Contains("lf_jpsi") ) {
	title.Append("Muon efficiency plots from lf and jpsi MC");
      } else if ( link.Contains("b") ) {
	title.Append("Muon efficiency plots from b MC");
      } else if ( link.Contains("c") ) {
	title.Append("Muon efficiency plots from c MC");
      } else if ( link.Contains("lf") ) {
	title.Append("Muon efficiency plots from lf MC");
      } else if ( link.Contains("jpsi") ) {
	title.Append("Muon efficiency plots from jpsi MC");
      }	
	
      HTMLStreamTop(top,link,title,tempoption);
    }

    HTMLEnd(top,"../gallery.html",fTime,tempoption);
    delete top;  // add leading Histograms directory to input histograms
  
  }

  entries->Delete();
  delete entries;

  return has_entry;
}

//_____________________________________________________________

Bool_t GPictureMaker::MakeSpecialPeriodPtRel(TFile *file, TString period, TString directory, TString option) {
  //
  // make special ptrel pictures
  if ( gDebug ) cout << endl << "GPictureMaker::MakeSpecialPeriodPtRel() called" << endl << endl;

  TList *entries = new TList();
  Bool_t has_entry = kFALSE;

  // check whether dir exists, else generate
  gSystem->mkdir(directory,kTRUE);

  // start html file
  TString tempdir = directory;
  if ( tempdir.BeginsWith(".") ) {
    tempdir = "";
  } else if ( tempdir.EndsWith("/") && ( tempdir.Length() != 0 ) )
    tempdir.Remove(tempdir.Length()-1,1);
  // check whether tempdir exists, else generate
  gSystem->mkdir(tempdir.Data(),kTRUE);
  TString filename = tempdir.Data();
  filename.Append("/gallery.html");
  ofstream *top = new ofstream(filename);
  HTMLStart(top,"PtRel Plots","ptrel_plots",option);

  TIter nextname(fPlotsPtRel);
  while ( TObjString *name = (TObjString*)nextname() ) {
    Bool_t temp_has_entry = kFALSE;
    temp_has_entry = MakePtRelPlot(file,top,name->GetString(),directory,period,option);
    if ( DoPicturesPtRelMCOnly() ) {
      TString tempoption = option;
      tempoption.Append(",MCONLY");
      temp_has_entry = MakePtRelPlot(file,top,name->GetString(),directory,period,tempoption);
    }
    if ( !has_entry )
      has_entry = temp_has_entry;
  }

  HTMLEnd(top,"../gallery.html",fTime,option);
  delete top;  // add leading Histograms directory to input histograms
  
  entries->Delete();
  delete entries;

  return has_entry;
}

//_____________________________________________________________

Bool_t GPictureMaker::MakeSpecialPeriodImpact(TFile *file, TString period, TString directory, TString option) {
  //
  // make special impact parameter pictures
  if ( gDebug ) cout << endl << "GPictureMaker::MakeSpecialPeriodImpact() called" << endl << endl;

  TList *entries = new TList();
  Bool_t has_entry = kFALSE;

  // check whether dir exists, else generate
  gSystem->mkdir(directory,kTRUE);

  // start html file
  TString tempdir = directory;
  if ( tempdir.BeginsWith(".") ) {
    tempdir = "";
  } else if ( tempdir.EndsWith("/") && ( tempdir.Length() != 0 ) )
    tempdir.Remove(tempdir.Length()-1,1);
  // check whether tempdir exists, else generate
  gSystem->mkdir(tempdir.Data(),kTRUE);
  TString filename = tempdir.Data();
  filename.Append("/gallery.html");
  ofstream *top = new ofstream(filename);
  HTMLStart(top,"Impact Parameter Plots","impact_plots",option);

  TIter nextname(fPlotsImpact);
  while ( TObjString *name = (TObjString*)nextname() ) {
    Bool_t temp_has_entry = kFALSE;
    temp_has_entry = MakeImpactPlot(file,top,name->GetString(),directory,period,option);
    if ( DoPicturesPtRelMCOnly() ) {
      TString tempoption = option;
      tempoption.Append(",MCONLY");
      temp_has_entry = MakeImpactPlot(file,top,name->GetString(),directory,period,tempoption);
    }
    if ( !has_entry )
      has_entry = temp_has_entry;
  }

  HTMLEnd(top,"../gallery.html",fTime,option);
  delete top;  // add leading Histograms directory to input histograms
  
  entries->Delete();
  delete entries;

  return has_entry;
}

//_____________________________________________________________

Bool_t GPictureMaker::MakeSpecialPeriod1D(TFile *file, TString period, TString directory, TString option) {
  //
  // make special one dimensional pictures
  if ( gDebug ) cout << endl << "GPictureMaker::MakeSpecialPeriod1D() called" << endl << endl;

  Bool_t has_entry = kFALSE;

  GHistogrammer grammer;
  TList *types = grammer.GetTypes();

  // check whether dir exists, else generate
  gSystem->mkdir(directory,kTRUE);

  // start html file
  TString tempdir = directory;
  if ( tempdir.BeginsWith(".") ) {
    tempdir = "";
  } else if ( tempdir.EndsWith("/") && ( tempdir.Length() != 0 ) )
    tempdir.Remove(tempdir.Length()-1,1);
  // check whether tempdir exists, else generate
  gSystem->mkdir(tempdir.Data(),kTRUE);
  TString filename = tempdir.Data();
  filename.Append("/gallery.html");
  ofstream *top = new ofstream(filename);
  HTMLStart(top,"Special one dimensional plots","1D_plots",option);

  TIter nextdata(fPlots1D);
  while ( TObjString *datahist = (TObjString*)nextdata() ) {
    Bool_t temp_has_entry = kFALSE;
    TString tempoption = option;
    tempoption.Append(",DATA");
    temp_has_entry = Make1DPlot(file,top,"","",datahist->GetString(),directory,period,tempoption);
    if ( !has_entry )
      has_entry = temp_has_entry;
  }

  TIter nextdatazoomed(fPlots1DZoomed);
  while ( TObjString *datahistzoomed = (TObjString*)nextdatazoomed() ) {
    Bool_t temp_has_entry = kFALSE;
    TString tempoption = option;
    tempoption.Append(",DATA");
    temp_has_entry = Make1DPlot(file,top,"","",datahistzoomed->GetString(),directory,period,tempoption,0.33);
    if ( !has_entry )
      has_entry = temp_has_entry;
  }

  TIter nextmc(fPlots1DMC);
  while ( TObjString *mchist = (TObjString*)nextmc() ) {
    Bool_t temp_has_entry = kFALSE;
    TString tempoption = option;
    tempoption.Append(",MC");
    TIter nexttype(types);
    while ( TObjString *type = (TObjString*)nexttype() ) {
      temp_has_entry = Make1DPlot(file,top,type->GetString(),"",mchist->GetString(),directory,period,tempoption);
      TIter nexttype2(nexttype);
      while ( TObjString *type2 = (TObjString*)nexttype2() ) {
	TString merge = type->GetString();
	merge.Append("_");
	merge.Append(type2->GetString());
	temp_has_entry = Make1DPlot(file,top,"",merge,mchist->GetString(),directory,period,tempoption);
	TIter nexttype3(nexttype2);
	while ( TObjString *type3 = (TObjString*)nexttype3() ) {
	  TString merge = type->GetString();
	  merge.Append("_");
	  merge.Append(type2->GetString());
	  merge.Append("_");
	  merge.Append(type3->GetString());
	  temp_has_entry = Make1DPlot(file,top,"",merge,mchist->GetString(),directory,period,tempoption);
	}
      }
    }
    if ( !has_entry )
      has_entry = temp_has_entry;
  }

  TIter nextmczoomed(fPlots1DMCZoomed);
  while ( TObjString *mchistzoomed = (TObjString*)nextmczoomed() ) {
    Bool_t temp_has_entry = kFALSE;
    TString tempoption = option;
    tempoption.Append(",MC");
    TIter nexttype(types);
    while ( TObjString *type = (TObjString*)nexttype() ) {
      temp_has_entry = Make1DPlot(file,top,type->GetString(),"",mchistzoomed->GetString(),directory,period,tempoption,0.33);
      TIter nexttype2(nexttype);
      while ( TObjString *type2 = (TObjString*)nexttype2() ) {
	TString merge = type->GetString();
	merge.Append("_");
	merge.Append(type2->GetString());
	temp_has_entry = Make1DPlot(file,top,"",merge,mchistzoomed->GetString(),directory,period,tempoption,0.33);
	TIter nexttype3(nexttype2);
	while ( TObjString *type3 = (TObjString*)nexttype3() ) {
	  TString merge = type->GetString();
	  merge.Append("_");
	  merge.Append(type2->GetString());
	  merge.Append("_");
	  merge.Append(type3->GetString());
	  temp_has_entry = Make1DPlot(file,top,"",merge,mchistzoomed->GetString(),directory,period,tempoption,0.33);
	}
      }
    }
    if ( !has_entry )
      has_entry = temp_has_entry;
  }

  HTMLEnd(top,"../gallery.html",fTime,option);
  delete top;  // add leading Histograms directory to input histograms
  
  return has_entry;
}

//_____________________________________________________________

Bool_t GPictureMaker::MakeSpecialPeriodEfficiencyData(TFile *file, TString period, TString directory, TString option) {
  //
  // make data efficiency pictures
  if ( gDebug ) cout << endl << "GPictureMaker::MakeSpecialPeriodEfficiencyData() called" << endl << endl;

  Bool_t has_entry = kFALSE;

  // check whether dir exists, else generate
  gSystem->mkdir(directory,kTRUE);

  // start html file
  TString tempdir = directory;
  if ( tempdir.BeginsWith(".") ) {
    tempdir = "";
  } else if ( tempdir.EndsWith("/") && ( tempdir.Length() != 0 ) )
    tempdir.Remove(tempdir.Length()-1,1);
  // check whether tempdir exists, else generate
  gSystem->mkdir(tempdir.Data(),kTRUE);
  TString filename = tempdir.Data();
  filename.Append("/gallery.html");
  ofstream *top = new ofstream(filename);
  HTMLStart(top,"Muon data efficiency plots","Data_Efficiency_plots",option);

  // make data plots
  TIter nextbasename(fPlotsEfficiencyBasename);
  while ( TObjString *basename = (TObjString*)nextbasename() ) {
    TIter nextfinder(fPlotsEfficiencyFinder);
    while ( TObjString *finder = (TObjString*)nextfinder() ) {
      TIter nextregion(fPlotsEfficiencyRegion);
      while ( TObjString *region = (TObjString*)nextregion() ) {
	Bool_t temp_has_entry = kFALSE;
	temp_has_entry = MakeEfficiencyPlotData(file,top,directory,basename->GetString(),finder->GetString(),period,region->GetString(),"",option);
	if ( !has_entry )
	  has_entry = temp_has_entry;
      }
    }
  }


  HTMLEnd(top,"../gallery.html",fTime,option);
  delete top;  // add leading Histograms directory to input histograms
  
  return has_entry;
}

//_____________________________________________________________

Bool_t GPictureMaker::MakeSpecialPeriodCorrection(TFile *file, TString period, TString directory, TString option) {
  //
  // make data efficiency correction factors pictures
  if ( gDebug ) cout << endl << "GPictureMaker::MakeSpecialPeriodCorrection() called" << endl << endl;

  Bool_t has_entry = kFALSE;

  // check whether dir exists, else generate
  gSystem->mkdir(directory,kTRUE);

  // start html file
  TString tempdir = directory;
  if ( tempdir.BeginsWith(".") ) {
    tempdir = "";
  } else if ( tempdir.EndsWith("/") && ( tempdir.Length() != 0 ) )
    tempdir.Remove(tempdir.Length()-1,1);
  // check whether tempdir exists, else generate
  gSystem->mkdir(tempdir.Data(),kTRUE);
  TString filename = tempdir.Data();
  filename.Append("/gallery.html");
  ofstream *top = new ofstream(filename);
  HTMLStart(top,"Muon efficiency correction factors plots","Muon_Correction_plots",option);

  // make data plots
  TIter nextbasename(fPlotsEfficiencyBasename);
  while ( TObjString *basename = (TObjString*)nextbasename() ) {
    TIter nextfinder(fPlotsEfficiencyFinder);
    while ( TObjString *finder = (TObjString*)nextfinder() ) {
      TIter nextregion(fPlotsEfficiencyRegion);
      while ( TObjString *region = (TObjString*)nextregion() ) {
	Bool_t temp_has_entry = kFALSE;
	temp_has_entry = MakeCorrectionPlot(file,top,directory,basename->GetString(),finder->GetString(),period,region->GetString(),"jpsi",option);
	if ( !has_entry )
	  has_entry = temp_has_entry;
      }
    }
  }


  HTMLEnd(top,"../gallery.html",fTime,option);
  delete top;  // add leading Histograms directory to input histograms
  
  return has_entry;
}

//_____________________________________________________________

Bool_t GPictureMaker::MakeSpecialPeriodEfficiencyMCType(TFile *file, TString period, TString directory, TString type, TString option) {
  //
  // make mc efficiency pictures for a type
  if ( gDebug ) cout << endl << "GPictureMaker::MakeSpecialPeriodEfficiencyMCType() called" << endl << endl;

  Bool_t has_entry = kFALSE;

  // check whether dir exists, else generate
  gSystem->mkdir(directory,kTRUE);

  // start html file
  TString tempdir = directory;
  if ( tempdir.BeginsWith(".") ) {
    tempdir = "";
  } else if ( tempdir.EndsWith("/") && ( tempdir.Length() != 0 ) )
    tempdir.Remove(tempdir.Length()-1,1);
  // check whether tempdir exists, else generate
  gSystem->mkdir(tempdir.Data(),kTRUE);
  TString filename = tempdir.Data();
  filename.Append("/gallery.html");
  ofstream *top = new ofstream(filename);
  HTMLStart(top,"Muon MC efficiency plots","MC_Efficiency_plots",option);

  // make data plots
  TIter nextbasename(fPlotsEfficiencyBasename);
  while ( TObjString *basename = (TObjString*)nextbasename() ) {
    TIter nextfinder(fPlotsEfficiencyFinder);
    while ( TObjString *finder = (TObjString*)nextfinder() ) {
      TIter nextregion(fPlotsEfficiencyRegion);
      while ( TObjString *region = (TObjString*)nextregion() ) {
	Bool_t temp_has_entry = kFALSE;
	temp_has_entry = MakeEfficiencyPlotMC(file,top,directory,basename->GetString(),finder->GetString(),period,region->GetString(),type,option);
	if ( !has_entry )
	  has_entry = temp_has_entry;
      }
    }
  }

  
  HTMLEnd(top,"../gallery.html",fTime,option);
  delete top;  // add leading Histograms directory to input histograms
  
  return has_entry;
}

//_____________________________________________________________

Bool_t GPictureMaker::MakeSpecialPeriod2D(TFile *file, TString period, TString directory, TString option) {
  //
  // make special two dimensional pictures
  if ( gDebug ) cout << endl << "GPictureMaker::MakeSpecialPeriod2D() called" << endl << endl;

  Bool_t has_entry = kFALSE;

  TList *drawoptions = new TList();
  drawoptions->Add(new TObjString("COLZ"));
  drawoptions->Add(new TObjString("BOX"));
  drawoptions->Add(new TObjString("CONTZ"));
  drawoptions->Add(new TObjString("SCAT"));

  GHistogrammer grammer;
  TList *types = grammer.GetTypes();

  // check whether dir exists, else generate
  gSystem->mkdir(directory,kTRUE);

  // start html file
  TString tempdir = directory;
  if ( tempdir.BeginsWith(".") ) {
    tempdir = "";
  } else if ( tempdir.EndsWith("/") && ( tempdir.Length() != 0 ) )
    tempdir.Remove(tempdir.Length()-1,1);
  // check whether tempdir exists, else generate
  gSystem->mkdir(tempdir.Data(),kTRUE);
  TString filename = tempdir.Data();
  filename.Append("/gallery.html");
  ofstream *top = new ofstream(filename);
  HTMLStart(top,"Special two dimensional plots","2D_plots",option);

  TIter nextdrawoption(drawoptions);
  while (TObjString *drawoption = (TObjString*)nextdrawoption() ) {

    TString tempoption = option;
    tempoption.Append(",");
    tempoption.Append(drawoption->GetString());

    TIter nextdata(fPlots2D);
    while ( TObjString *datahist = (TObjString*)nextdata() ) {
      Bool_t temp_has_entry = kFALSE;
      TString tempoption2 = tempoption;
      tempoption2.Append(",DATA");
      temp_has_entry = Make2DPlot(file,top,"","",datahist->GetString(),directory,period,tempoption2);
      if ( !has_entry )
	has_entry = temp_has_entry;
    }

    TIter nextdatazoomed(fPlots2DZoomed);
    while ( TObjString *datahistzoomed = (TObjString*)nextdatazoomed() ) {
      Bool_t temp_has_entry = kFALSE;
      TString tempoption2 = tempoption;
      tempoption2.Append(",DATA");
      temp_has_entry = Make2DPlot(file,top,"","",datahistzoomed->GetString(),directory,period,tempoption2,0.33);
      if ( !has_entry )
	has_entry = temp_has_entry;
    }

    TIter nextmc(fPlots2DMC);
    while ( TObjString *mchist = (TObjString*)nextmc() ) {
      Bool_t temp_has_entry = kFALSE;
      TString tempoption2 = tempoption;
      tempoption2.Append(",MC");
      TIter nexttype(types);
      while ( TObjString *type = (TObjString*)nexttype() ) {
// 	if ( (mchist->GetString().EndsWith("B") && type->GetString().Contains("b")) ||
// 	     (mchist->GetString().EndsWith("C") && type->GetString().Contains("c")) ||
// 	     (mchist->GetString().EndsWith("LF") && type->GetString().Contains("lf")) ||
// 	     (mchist->GetString().EndsWith("BQuark") && type->GetString().Contains("b")) ||
// 	     (mchist->GetString().EndsWith("CQuark") && type->GetString().Contains("c")) ||
// 	     (mchist->GetString().EndsWith("LFQuark") && type->GetString().Contains("lf")) ) {
	  temp_has_entry = Make2DPlot(file,top,type->GetString(),"",mchist->GetString(),directory,period,tempoption2);
	  if ( !has_entry )
	    has_entry = temp_has_entry;
// 	}
	TIter nexttype2(nexttype);
	while ( TObjString *type2 = (TObjString*)nexttype2() ) {
	  TString merge = type->GetString();
	  merge.Append("_");
	  merge.Append(type2->GetString());
	  temp_has_entry = Make2DPlot(file,top,"",merge,mchist->GetString(),directory,period,tempoption2);
	  if ( !has_entry )
	    has_entry = temp_has_entry;
	  TIter nexttype3(nexttype2);
	  while ( TObjString *type3 = (TObjString*)nexttype3() ) {
	    TString merge = type->GetString();
	    merge.Append("_");
	    merge.Append(type2->GetString());
	    merge.Append("_");
	    merge.Append(type3->GetString());
	    temp_has_entry = Make2DPlot(file,top,"",merge,mchist->GetString(),directory,period,tempoption2);
	    if ( !has_entry )
	      has_entry = temp_has_entry;
	  }
	}
      }
    }

    TIter nextmczoomed(fPlots2DMCZoomed);
    while ( TObjString *mczoomedhist = (TObjString*)nextmczoomed() ) {
      Bool_t temp_has_entry = kFALSE;
      TString tempoption2 = tempoption;
      tempoption2.Append(",MC");
      TIter nexttype(types);
      while ( TObjString *type = (TObjString*)nexttype() ) {
// 	if ( (mczoomedhist->GetString().EndsWith("B") && type->GetString().Contains("b")) ||
// 	     (mczoomedhist->GetString().EndsWith("C") && type->GetString().Contains("c")) ||
// 	     (mczoomedhist->GetString().EndsWith("LF") && type->GetString().Contains("lf")) ||
// 	     (mczoomedhist->GetString().EndsWith("BQuark") && type->GetString().Contains("b")) ||
// 	     (mczoomedhist->GetString().EndsWith("CQuark") && type->GetString().Contains("c")) ||
// 	     (mczoomedhist->GetString().EndsWith("LFQuark") && type->GetString().Contains("lf")) ) {
	  temp_has_entry = Make2DPlot(file,top,type->GetString(),"",mczoomedhist->GetString(),directory,period,tempoption2,0.33,0.2);
	  if ( !has_entry )
	    has_entry = temp_has_entry;
// 	}
	TIter nexttype2(nexttype);
	while ( TObjString *type2 = (TObjString*)nexttype2() ) {
	  TString merge = type->GetString();
	  merge.Append("_");
	  merge.Append(type2->GetString());
	  temp_has_entry = Make2DPlot(file,top,"",merge,mczoomedhist->GetString(),directory,period,tempoption2,0.33,0.2);
	  if ( !has_entry )
	    has_entry = temp_has_entry;
	  TIter nexttype3(nexttype2);
	  while ( TObjString *type3 = (TObjString*)nexttype3() ) {
	    TString merge = type->GetString();
	    merge.Append("_");
	    merge.Append(type2->GetString());
	    merge.Append("_");
	    merge.Append(type3->GetString());
	    temp_has_entry = Make2DPlot(file,top,"",merge,mczoomedhist->GetString(),directory,period,tempoption2,0.33,0.2);
	    if ( !has_entry )
	      has_entry = temp_has_entry;
	  }
	}
      }
      if ( !has_entry )
	has_entry = temp_has_entry;
    }
  }

  HTMLEnd(top,"../gallery.html",fTime,option);
  delete top;  // add leading Histograms directory to input histograms
  
  return has_entry;
}

//_____________________________________________________________

Bool_t GPictureMaker::MakeSpecialPeriodComparison(TFile *file, TString period, TString directory, TString ptrelhistogramname, TString option) {
  //
  // make special comparison pictures
  if ( gDebug ) cout << endl << "GPictureMaker::MakeSpecialPeriodComparison() called" << endl << endl;

  option.ToUpper();

  TList *entries = new TList();
  Bool_t has_entry = kFALSE;

  // check whether dir exists, else generate
  gSystem->mkdir(directory,kTRUE);

  // start html file
  TString tempdir = directory;
  if ( tempdir.BeginsWith(".") ) {
    tempdir = "";
  } else if ( tempdir.EndsWith("/") && ( tempdir.Length() != 0 ) )
    tempdir.Remove(tempdir.Length()-1,1);
  // check whether tempdir exists, else generate
  gSystem->mkdir(tempdir.Data(),kTRUE);
  TString filename = tempdir.Data();
  filename.Append("/gallery.html");
  ofstream *top = new ofstream(filename);
  HTMLStart(top,"Comparison Plots using PtRel Fits","comparison_ptrel",option);
  
  TIter nextname(fPlotsComparison);
  while ( TObjString *name = (TObjString*)nextname() ) {
    Bool_t temp_has_entry = kFALSE;
    Double_t scale = 0.0;
    temp_has_entry = MakeComparisonPlot(file,top,name->GetString(),ptrelhistogramname,period,directory,option,scale);
    // use region ptrel fit if region is contained in plot name
    if ( option.Contains("PTREL") ) {
      if ( name->GetString().Contains("Forward") || name->GetString().Contains("FORWARD") ) {
	TString tempoption = option;
	tempoption.Append(",FORWARD");
	temp_has_entry = MakeComparisonPlot(file,top,name->GetString(),ptrelhistogramname,period,directory,tempoption,scale);
      } else if ( name->GetString().Contains("Barrel") || name->GetString().Contains("BARREL") ) {
	TString tempoption = option;
	tempoption.Append(",BARREL");
	temp_has_entry = MakeComparisonPlot(file,top,name->GetString(),ptrelhistogramname,period,directory,tempoption,scale);
      } else if ( name->GetString().Contains("Rear") || name->GetString().Contains("REAR") ) {
	TString tempoption = option;
	tempoption.Append(",REAR");
	temp_has_entry = MakeComparisonPlot(file,top,name->GetString(),ptrelhistogramname,period,directory,tempoption,scale);
      }
    }
    if ( !has_entry )
      has_entry = temp_has_entry;
  }

  HTMLEnd(top,"../gallery.html",fTime,option);
  delete top;  // add leading Histograms directory to input histograms
  
  entries->Delete();
  delete entries;

  return has_entry;
}

//_____________________________________________________________

Bool_t GPictureMaker::MakePtRelPlot(TFile *file, ofstream *stream, TString histogramname, TString directory, TString period, TString option) {
  //
  // make PtRel plot
  if ( gDebug ) cout << endl << "GPictureMaker::MakePtRelPlot called" << endl << endl;

  option.ToUpper();

  Bool_t debug = kFALSE;

  TH1D **histos = new TH1D *[4];

  // generation of data histogram name
  TString datahistname = "Histograms/data/merged/";
  datahistname.Append(histogramname);
  datahistname.Append("_");
  // fix for period 03p-04p_ztt
  TString tempperiod = period;
  tempperiod.ReplaceAll("_ztt","");
  datahistname.Append(tempperiod);
  if ( !option.Contains("MCONLY") ) {
    histos[0]=(TH1D*)file->Get(datahistname);
    if ( histos[0] == 0) {
      if ( debug ) {
	cout << "GPictureMaker::MakePtRelPlot problems with histos[0] named: " << datahistname << endl;
      }
      return kFALSE;
    }
  }

  // generation of b MC histogram name
  TString bhistname = "Histograms/mc/";
  bhistname.Append(period);
  bhistname.Append("/b/merged/");
  bhistname.Append(histogramname);

  histos[1]=(TH1D*)file->Get(bhistname);
  if ( histos[1] == 0 ) {
    if ( debug ) {
      cout << "GPictureMaker::MakePtRelPlot problems with histos[1] named: " << bhistname  << endl;
    }
    return kFALSE;
  }

  // generation of c MC histogram name
  TString chistname = "Histograms/mc/";
  chistname.Append(period);
  chistname.Append("/c/merged/");
  chistname.Append(histogramname);

  TH1D *chisto = (TH1D*)gFile->Get(chistname);
  if ( chisto == 0 ) {
    if ( debug ) {
      cout << "GPictureMaker::MakePtRelPlot problems with chisto named: " << chistname  << endl;
    }
    return kFALSE;
  }
  
  chistname.Append("_Corrections");
  TH1D *chisto_corr =(TH1D*)gFile->Get(chistname);
  if ( (chisto_corr != 0) && (chisto != 0) ) {
    Double_t old_int = chisto->Integral();
    chisto->Multiply(chisto_corr);
    Double_t new_int = chisto->Integral();
    chisto->Scale(old_int/new_int);
  }

  // generation of lf MC histogram name
  TString lfhistname = "Histograms/mc/";
  lfhistname.Append(period);
  lfhistname.Append("/lf/merged/");
  lfhistname.Append(histogramname);

  TH1D *lfhisto = (TH1D*)gFile->Get(lfhistname);
  if ( lfhisto == 0 ) {
    if ( debug ) {
      cout << "GPictureMaker::MakePtRelPlot problems with lfhisto named: " << lfhistname  << endl;
    }
    return kFALSE;
  }
  
  lfhistname.Append("_Corrections");
  TH1D *lfhisto_corr =(TH1D*)gFile->Get(lfhistname);
  if ( (lfhisto_corr != 0) && (lfhisto != 0) ) {
    Double_t old_int = lfhisto->Integral();
    lfhisto->Multiply(lfhisto_corr);
    Double_t new_int = lfhisto->Integral();
    lfhisto->Scale(old_int/new_int);
  }
  
  TH1D *clfhist = (TH1D*)chisto->Clone();
  clfhist->Add(lfhisto);    // ben: scale c!

  histos[2]=clfhist;
  
  TH1D *cbhisto = (TH1D*)chisto->Clone("cbhisto");
  cbhisto->Reset();
  cbhisto->Add(chisto);
  histos[3]=cbhisto;
  
  if ( option.Contains("MCONLY") ) {
    TH1D *bclfhist = (TH1D*)histos[1]->Clone();
    bclfhist->Add(chisto);
    bclfhist->Add(lfhisto);
    histos[0]=bclfhist;
  }

  GPtRelFit *fit = 0;

  if ( option.Contains("MCONLY") )
    fit = gInclude->GetFit(file,bhistname);
  else
    fit = gInclude->GetFit(file,datahistname);

  if ( fit == 0 ) {
    if ( debug ) {
      cout << "GPictureMaker::MakePtRelPlot problems with fit for: " << bhistname  << endl;
    }
    return kFALSE;
  }

  if ( option.Contains("MCONLY") ) {
    cout << "GPictureMaker::MakePtRelPlot for " << histogramname << " in MCONLY mode for period " << period << endl;
  } else {
    cout << "GPictureMaker::MakePtRelPlot for " << histogramname << " for period " << period << endl;
  }
  // calculate fraction
  Double_t fraction = fit->GetBFraction();
  Double_t fraction_error = fit->GetBFractionErr();

  // set batch to true
  Bool_t batch = gROOT->IsBatch();
  if ( !batch )
    gROOT->SetBatch(kTRUE);

  // delete old canvas
  if ( fCanvas ) {
    delete fCanvas;
    fCanvas = 0;
  }

  // canvas
  if ( !fCanvas ) {
    fCanvas = new TCanvas("canvas","canvas",640,480);
  } 

  // set error bars in x off
  gStyle->SetErrorX(0);

  fCanvas->cd();
  fCanvas->Clear();
  fCanvas->SetLogy(0);

  if (option.Contains("STATS"))
    gStyle->SetOptStat(1110);
  else
    gStyle->SetOptStat(0);

  if ( option.Contains("MCONLY") ) {
    histos[0]->SetMarkerColor(8);
    histos[0]->SetMarkerStyle(1);
    histos[0]->SetMarkerSize(0.01);
    histos[0]->SetLineColor(8);
    histos[0]->SetLineStyle(1);
    histos[0]->SetLineWidth((Short_t)0.01);
  } else {
    histos[0]->SetMarkerColor(2);
    histos[0]->SetMarkerStyle(8);
    histos[0]->SetMarkerSize(1.3);
  }
  histos[0]->SetTitleOffset(1.2);
  TString histoname = "ptrel_";
  histoname.Append(histogramname);
  histoname.Append("_");
  histoname.Append(period);
  histoname.ReplaceAll("/","_");
  histoname.ToLower();
  if ( option.Contains("MCONLY") )
    histoname.Append("_mconly");
  histos[0]->SetName(histoname);
  TString histotitle = "p_{T}^{rel} plot for ";
  histotitle.Append(histogramname);
  histotitle.Append(" in ");
  histotitle.Append(period);
  if ( option.Contains("MCONLY") ) {
    histotitle.Append(" using MC only");
  }
  histos[0]->SetTitle(histotitle);
  if ( option.Contains("MCONLY") )
    histos[0]->Draw("HIST");
  else
    histos[0]->Draw("PE");

  if (option.Contains("STATS")) {
    fCanvas->Update();
    TPaveStats *stats = (TPaveStats*)(histos[0]->GetListOfFunctions()->FindObject("stats"));
    stats->SetX1NDC(0.68);
    stats->SetY1NDC(0.88);
    stats->SetX2NDC(0.98);
    stats->SetY2NDC(0.995);
  }

  // title pave text
  fCanvas->Update();
  TPaveText *titlepave = (TPaveText*)fCanvas->FindObject("title");
  if ( titlepave->GetX2NDC() > 0.67 )
    titlepave->SetX2NDC(0.67);

  // scale histos[1] (bbbar) before adding to scaled histos[2] (c+lf)
  histos[1]->Scale(fit->GetBScale());

  histos[2]->Scale(fit->GetCLFScale());
  histos[2]->Add(histos[1],1);
  histos[2]->SetTitleOffset(1.2);
  histos[2]->SetLineColor(8);
  histos[2]->SetLineStyle(1);
  histos[2]->SetLineWidth((Short_t)3);
  histos[2]->SetStats(kFALSE);
  histos[2]->Draw("HIST,SAME");

  if (DoCLFDraw()){
    histos[3]->Scale(fit->GetCLFScale()); // ben: use c only fit?
    histos[3]->Add(histos[1],1);
    histos[3]->SetTitleOffset(1.2);
    histos[3]->SetLineColor(6);
    histos[3]->SetLineStyle(3);
    histos[3]->SetLineWidth((Short_t)3);
    histos[3]->SetStats(kFALSE);
    histos[3]->Draw("HIST,SAME");
  }
  histos[1]->SetTitle("test");
  histos[1]->SetStats(kFALSE);
  histos[1]->SetLineColor(4);
  histos[1]->SetLineStyle(2);
  histos[1]->SetLineWidth((Short_t)3);
  histos[1]->SetTitleOffset(1.2);
  histos[1]->Draw("HIST,SAME");

  // redraw data points
  
  if ( option.Contains("MCONLY") ) {
//     histos[0]->Draw("P,SAME");
  } else {
    histos[0]->Draw("PE,SAME");
  }

  TLegend *leg = 0;
  if (option.Contains("STATS"))
    leg = new TLegend(0.68,0.75,0.98,0.87);
  else
    leg = new TLegend(0.68,0.87,0.98,0.995);
  leg->SetTextSize(0.035); 
  leg->SetFillColor(10);
  leg->SetBorderSize(1); // no frame, no shadow
  TString datalegendentry = "Data ";
  datalegendentry.Append(period);
  if ( option.Contains("MCONLY") ) {
    //     leg->AddEntry(histos[0], "MC ccbar+lf+bbbar" , "P" );
  } else {
    leg->AddEntry(histos[0], datalegendentry , "P" );
  }
  if (DoCLFDraw()){
    leg->AddEntry(histos[1], "MC bbbar" , "L" );
    leg->AddEntry(histos[3], "MC bbbar+ccbar" , "L" );
    leg->AddEntry(histos[2], "MC bbbar+ccbar+lf" , "L" );
  }
  else {
    leg->AddEntry(histos[1], "MC bbbar" , "L" );
    leg->AddEntry(histos[2], "MC ccbar+lf+bbbar" , "L" );
  }
  leg->Draw("SAME");
 
  TString label = "";
  label.Append(gInclude->FormatedDouble(fraction,2,3));
  label.Append (" #pm ");
  label.Append(gInclude->FormatedDouble(fraction_error,2,3));

  TPaveText *text = 0;
  if (option.Contains("STATS"))
    text = new TPaveText(0.68,0.64,0.98,0.74,"br,NDC");
  else
    text = new TPaveText(0.68,0.77,0.98,0.86,"br,NDC");
  text->AddText("bbbar fraction:");
  text->AddText(label.Data());
  text->Draw("SAME");

  // nice histogram
  gInclude->NicePlot(fCanvas);
  gInclude->NicePlot(fCanvas);

  GenHTMLPics(stream, fCanvas,histoname,directory,histotitle,option);
  
  // set error bars in x to default
  gStyle->SetErrorX(0.5);

  // delete old canvas
  if ( fCanvas ) {
    delete fCanvas;
    fCanvas = 0;
  }

  // delete histo objects
  if ( chisto != 0 ) {
    delete chisto;
    chisto = 0;
  }
  if ( chisto_corr != 0 ) {
    delete chisto_corr;
    chisto_corr = 0;
  }
  if ( lfhisto != 0 ) {
    delete lfhisto;
    lfhisto = 0;
  }
  if ( lfhisto_corr != 0 ) {
    delete lfhisto_corr;
    lfhisto_corr = 0;
  }
  if ( cbhisto != 0 ) {
    delete cbhisto;
    cbhisto=0;
  }
  if ( clfhist != 0 ) {
    delete clfhist;
    clfhist = 0;
    histos[2] = 0;
  }

  for ( Int_t i = 0; i < 3; ++i ) {
    if ( histos[i] != 0 ) {
      delete histos[i];
      histos[i] = 0;
    }
  }

  // restore batch level
  if ( !batch )
    gROOT->SetBatch(kFALSE);

  return kTRUE;
}

//_____________________________________________________________

Bool_t GPictureMaker::MakeImpactPlot(TFile *file, ofstream *stream, TString histogramname, TString directory, TString period, TString option) {
  //
  // make impact parameter plot
  if ( gDebug ) cout << endl << "GPictureMaker::MakeImpactPlot called" << endl << endl;

  option.ToUpper();

  TH1D **histos = new TH1D *[3];

  // generation of data histogram name
  TString datahistname = "";
  if ( option.Contains("MCONLY") ) {
    datahistname = "Histograms/mc/";
    datahistname.Append(period);
    datahistname.Append("/merged/");
    datahistname.Append(histogramname);
    datahistname.Append("_b_c_lf");
  } else {
    datahistname = "Histograms/data/merged/";
    datahistname.Append(histogramname);
    datahistname.Append("_");
    // fix for period 03p-04p_ztt
    TString tempperiod = period;
    tempperiod.ReplaceAll("_ztt","");
    datahistname.Append(tempperiod);
  }

  // generation of b MC histogram name
  TString bhistname = "Histograms/mc/";
  bhistname.Append(period);
  bhistname.Append("/b/merged/");
  bhistname.Append(histogramname);

  // generation of c+lf MC histogram name
  TString clfhistname = "Histograms/mc/";
  clfhistname.Append(period);
  clfhistname.Append("/merged/");
  clfhistname.Append(histogramname);
  clfhistname.Append("_c_lf");

  histos[0]=(TH1D*)file->Get(datahistname);
  if ( histos[0] == 0) {
    return kFALSE;
  }
  
  histos[1]=(TH1D*)file->Get(bhistname);
  if ( histos[1] == 0 ) {
    return kFALSE;
  }

  histos[2]=(TH1D*)file->Get(clfhistname);
  if ( histos[2] == 0 ) {
    return kFALSE;
  }

  GImpactFit *fit = 0;

  if ( option.Contains("MCONLY") )
    fit = gInclude->GetImpactFit(file,bhistname);
  else
    fit = gInclude->GetImpactFit(file,datahistname);

  if ( fit == 0 ) {
    return kFALSE;
  }

  if ( option.Contains("MCONLY") ) {
    cout << "GPictureMaker::MakeImpactPlot for " << histogramname << " in MCONLY mode for period " << period << endl;
  } else {
    cout << "GPictureMaker::MakeImpactPlot for " << histogramname << " for period " << period << endl;
  }
  // calculate fraction
  Double_t fraction = fit->GetBFraction();
  Double_t fraction_error = fit->GetBFractionErr();

  // set batch to true
  Bool_t batch = gROOT->IsBatch();
  if ( !batch )
    gROOT->SetBatch(kTRUE);

  // delete old canvas
  if ( fCanvas ) {
    delete fCanvas;
    fCanvas = 0;
  }

  // canvas
  if ( !fCanvas ) {
    fCanvas = new TCanvas("canvas","canvas",640,480);
  } 

  // set error bars in x off
  gStyle->SetErrorX(0);

  fCanvas->cd();
  fCanvas->Clear();
  fCanvas->SetLogy(0);

  if (option.Contains("STATS"))
    gStyle->SetOptStat(1110);
  else
    gStyle->SetOptStat(0);

  if ( option.Contains("MCONLY") ) {
    histos[0]->SetMarkerColor(8);
    histos[0]->SetMarkerStyle(1);
    histos[0]->SetMarkerSize(0.01);
    histos[0]->SetLineColor(8);
    histos[0]->SetLineStyle(1);
    histos[0]->SetLineWidth((Short_t)0.01);
  } else {
    histos[0]->SetMarkerColor(2);
    histos[0]->SetMarkerStyle(8);
    histos[0]->SetMarkerSize(1.3);
  }
  histos[0]->SetTitleOffset(1.2);
  TString histoname = "impact_";
  histoname.Append(histogramname);
  histoname.Append("_");
  histoname.Append(period);
  histoname.ReplaceAll("/","_");
  histoname.ToLower();
  if ( option.Contains("MCONLY") )
    histoname.Append("_mconly");
  histos[0]->SetName(histoname);
  TString histotitle = "Impact parameter plot for ";
  histotitle.Append(histogramname);
  histotitle.Append(" in ");
  histotitle.Append(period);
  if ( option.Contains("MCONLY") ) {
    histotitle.Append(" using MC only");
  }
  histos[0]->SetTitle(histotitle);
  if ( option.Contains("MCONLY") )
    histos[0]->Draw("HIST");
  else
    histos[0]->Draw("PE");

  if (option.Contains("STATS")) {
    fCanvas->Update();
    TPaveStats *stats = (TPaveStats*)(histos[0]->GetListOfFunctions()->FindObject("stats"));
    stats->SetX1NDC(0.68);
    stats->SetY1NDC(0.88);
    stats->SetX2NDC(0.98);
    stats->SetY2NDC(0.995);
  }

  // title pave text
  fCanvas->Update();
  TPaveText *titlepave = (TPaveText*)fCanvas->FindObject("title");
  if ( titlepave->GetX2NDC() > 0.67 )
    titlepave->SetX2NDC(0.67);

  // scale histos[1] (bbbar) before adding to scaled histos[2] (c+lf)
  histos[1]->Scale(fit->GetBScale());

  histos[2]->Scale(fit->GetCLFScale());
  histos[2]->Add(histos[1],1);
  histos[2]->SetTitleOffset(1.2);
  histos[2]->SetLineColor(8);
  histos[2]->SetLineStyle(1);
  histos[2]->SetLineWidth((Short_t)3);
  histos[2]->SetStats(kFALSE);
  histos[2]->Draw("HIST,SAME");

  histos[1]->SetTitle("test");
  histos[1]->SetStats(kFALSE);
  histos[1]->SetLineColor(4);
  histos[1]->SetLineStyle(2);
  histos[1]->SetLineWidth((Short_t)3);
  histos[1]->SetTitleOffset(1.2);
  histos[1]->Draw("HIST,SAME");

  // redraw data points
  
  if ( option.Contains("MCONLY") ) {
//     histos[0]->Draw("P,SAME");
  } else {
    histos[0]->Draw("PE,SAME");
  }

  TLegend *leg = 0;
  if (option.Contains("STATS"))
    leg = new TLegend(0.68,0.75,0.98,0.87);
  else
    leg = new TLegend(0.68,0.87,0.98,0.995);
  leg->SetTextSize(0.035); 
  leg->SetFillColor(10);
  leg->SetBorderSize(1); // no frame, no shadow
  TString datalegendentry = "Data ";
  datalegendentry.Append(period);
  if ( option.Contains("MCONLY") ) {
    //     leg->AddEntry(histos[0], "MC ccbar+lf+bbbar" , "P" );
  } else {
    leg->AddEntry(histos[0], datalegendentry , "P" );
  }
  leg->AddEntry(histos[1], "MC bbbar" , "L" );
  leg->AddEntry(histos[2], "MC bbbar+ccbar+lf" , "L" );
  leg->Draw("SAME");
 
  TString label = "";
  label.Append(gInclude->FormatedDouble(fraction,2,3));
  label.Append (" #pm ");
  label.Append(gInclude->FormatedDouble(fraction_error,2,3));

  TPaveText *text = 0;
  if (option.Contains("STATS"))
    text = new TPaveText(0.68,0.64,0.98,0.74,"br,NDC");
  else
    text = new TPaveText(0.68,0.77,0.98,0.86,"br,NDC");
  text->AddText("bbbar fraction:");
  text->AddText(label.Data());
  text->Draw("SAME");

  // nice histogram
  gInclude->NicePlot(fCanvas);
  gInclude->NicePlot(fCanvas);

  GenHTMLPics(stream, fCanvas,histoname,directory,histotitle,option);
  
  // set error bars in x to default
  gStyle->SetErrorX(0.5);

  // delete old canvas
  if ( fCanvas ) {
    delete fCanvas;
    fCanvas = 0;
  }

  // restore batch level
  if ( !batch )
    gROOT->SetBatch(kFALSE);

  return kTRUE;
}

//_____________________________________________________________

Bool_t GPictureMaker::Make1DPlot(TFile *file, ofstream *stream, TString type, TString merge, TString histogramname, TString directory, TString period, TString option, Double_t zoomx) {
  //
  // make 1D plot
  if ( gDebug ) cout << endl << "GPictureMaker::Make1DPlot called" << endl << endl;

  option.ToUpper();

  TString histname = "Histograms/";
  if ( option.Contains("DATA") ) {
    histname.Append("data/");
    if ( type.Length() != 0 ) {
      histname.Append(type);
      histname.Append("/");
      histname.Append(histogramname);
    } else {
      histname.Append("merged/");
      histname.Append(histogramname);
      histname.Append("_");
      histname.Append(period);
    }
  } else if ( option.Contains("MC") ) {
    histname.Append("mc/");
    histname.Append(period);
    histname.Append("/");
    if ( type.Length() != 0 ) {
      histname.Append(type);
      histname.Append("/");
    }
    histname.Append("merged/");
    histname.Append(histogramname);
    if ( merge.Length() != 0 ) {
      histname.Append("_");
      histname.Append(merge);
    }
  }
  TH1D* histo=(TH1D*)file->Get(histname);
  if ( histo == 0) {
//     cout << "1D: problems in getting histogram: " << histname << endl;
    return kFALSE;
  }
  
  if ( option.Contains("DATA") ) {
    cout << "GPictureMaker::Make1DPlot for " << histogramname << " in DATA mode for period " << period << endl;
  } else if ( option.Contains("MC") ) {
    cout << "GPictureMaker::Make1DPlot for " << histogramname << " in MC mode for period " << period << endl;
  }

  // set batch to true
  Bool_t batch = gROOT->IsBatch();
  if ( !batch )
    gROOT->SetBatch(kTRUE);

  // delete old canvas
  if ( fCanvas ) {
    delete fCanvas;
    fCanvas = 0;
  }

  // canvas
  if ( !fCanvas ) {
    fCanvas = new TCanvas("canvas","canvas",640,480);
  } 

  // set error bars in x off
  gStyle->SetErrorX(0);

  fCanvas->cd();
  fCanvas->Clear();
  fCanvas->SetLogy(0);

  if (option.Contains("STATS"))
    gStyle->SetOptStat(1110);
  else
    gStyle->SetOptStat(0);

  TString histoname = histo->GetName();
  if ( type.Length() != 0 ) {
    histoname.Append("_");
    histoname.Append(type);
  }
  TString histotitle = histo->GetTitle(); 

  histo->SetMarkerColor(2);
  histo->SetMarkerStyle(8);
  histo->SetMarkerSize(1.3);
  if ( zoomx != 0.0 )
    histo->GetXaxis()->SetRangeUser(0.,histo->GetXaxis()->GetXmax()*zoomx);
//   histo->SetTitleOffset(1.2);
  histo->Draw("PE");

  if (option.Contains("STATS")) {
    fCanvas->Update();
    TPaveStats *stats = (TPaveStats*)(histo->GetListOfFunctions()->FindObject("stats"));
    stats->SetX1NDC(0.68);
    stats->SetY1NDC(0.88);
    stats->SetX2NDC(0.98);
    stats->SetY2NDC(0.995);
  }

  // title pave text
  fCanvas->Update();
  TPaveText *titlepave = (TPaveText*)fCanvas->FindObject("title");
  if ( titlepave->GetX2NDC() > 0.67 )
    titlepave->SetX2NDC(0.67);
  
  gInclude->NicePlot(fCanvas);
  gInclude->NicePlot(fCanvas);

  if ( zoomx != 0.0 ) {
    histoname.Append("_zoomed");
  }

  GenHTMLPics(stream, fCanvas,histoname,directory,histotitle,option);
  
  // set error bars in x to default
  gStyle->SetErrorX(0.5);

  // delete old canvas
  if ( fCanvas ) {
    delete fCanvas;
    fCanvas = 0;
  }

  // restore batch level
  if ( !batch )
    gROOT->SetBatch(kFALSE);

  return kTRUE;
}

//_____________________________________________________________

Bool_t GPictureMaker::Make2DPlot(TFile *file, ofstream *stream, TString type, TString merge, TString histogramname, TString directory, TString period, TString option, Double_t zoomx, Double_t zoomy) {
  //
  // make 2D plot
  if ( gDebug ) cout << endl << "GPictureMaker::Make2DPlot called" << endl << endl;

  option.ToUpper();

  TString histname = "Histograms/";
  if ( option.Contains("DATA") ) {
    histname.Append("data/");
    if ( type.Length() != 0 ) {
      histname.Append(type);
      histname.Append("/");
      histname.Append(histogramname);
    } else {
      histname.Append("merged/");
      histname.Append(histogramname);
      histname.Append("_");
      histname.Append(period);
    }
  } else if ( option.Contains("MC") ) {
    histname.Append("mc/");
    histname.Append(period);
    histname.Append("/");
    if ( type.Length() != 0 ) {
      histname.Append(type);
      histname.Append("/");
    }
    histname.Append("merged/");
    histname.Append(histogramname);
    if ( merge.Length() != 0 ) {
      histname.Append("_");
      histname.Append(merge);
    }
  }
  TH2D* histo=(TH2D*)file->Get(histname);
  if ( histo == 0) {
//     cout << "2D: problems in getting histogram: " << histname << endl;
    return kFALSE;
  }
  
  if ( option.Contains("DATA") ) {
    cout << "GPictureMaker::Make2DPlot for " << histogramname << " in DATA mode for period " << period << endl;
  } else if ( option.Contains("MC") ) {
    cout << "GPictureMaker::Make2DPlot for " << histogramname << " in MC mode for period " << period << endl;
  }

  // set batch to true
  Bool_t batch = gROOT->IsBatch();
  if ( !batch )
    gROOT->SetBatch(kTRUE);

  // delete old canvas
  if ( fCanvas ) {
    delete fCanvas;
    fCanvas = 0;
  }

  // canvas
  if ( !fCanvas ) {
    fCanvas = new TCanvas("canvas","canvas",640,480);
  } 

  // set error bars in x off
  gStyle->SetErrorX(0);

  fCanvas->cd();
  fCanvas->Clear();
  fCanvas->SetLogy(0);

  if (option.Contains("STATS"))
    gStyle->SetOptStat(1110);
  else
    gStyle->SetOptStat(0);

//   histo->SetMarkerColor(2);
//   histo->SetMarkerStyle(8);
//   histo->SetMarkerSize(1.3);
//   histo->SetTitleOffset(1.2);

  if ( zoomx != 0.0 )
    histo->GetXaxis()->SetRangeUser(0.,histo->GetXaxis()->GetXmax()*zoomx);
  if ( zoomy != 0.0 )
    histo->GetYaxis()->SetRangeUser(0.,histo->GetYaxis()->GetXmax()*zoomy);

  TString histoname = histo->GetName();
  if ( type.Length() != 0 ) {
    histoname.Append("_");
    histoname.Append(type);
  }
  histoname.Append("_");
  TString histotitle = histo->GetTitle(); 

  if ( option.Contains("COLZ") ) {
    histo->Draw("COLZ");
    histoname.Append("colz");
  } else if ( option.Contains("BOX") ) {
    histo->Draw("BOX");
    histoname.Append("box");
  } else if ( option.Contains("CONTZ") ) {
    histo->Draw("CONTZ");
    histoname.Append("contz");
  } else if ( option.Contains("SCAT") ) {
    histo->Draw("SCAT");
    histoname.Append("scat");
  } 

  if ( (zoomx != 0.0) || (zoomy != 0.0) ) {
    histoname.Append("_zoomed");
  }

  if (option.Contains("STATS")) {
    fCanvas->Update();
    TPaveStats *stats = (TPaveStats*)(histo->GetListOfFunctions()->FindObject("stats"));
    stats->SetX1NDC(0.68);
    stats->SetY1NDC(0.88);
    stats->SetX2NDC(0.98);
    stats->SetY2NDC(0.995);
  }

  // title pave text
  fCanvas->Update();
  TPaveText *titlepave = (TPaveText*)fCanvas->FindObject("title");
  if ( titlepave->GetX2NDC() > 0.67 )
    titlepave->SetX2NDC(0.67);
  
  gInclude->NicePlot(fCanvas);
  gInclude->NicePlot(fCanvas);

  GenHTMLPics(stream, fCanvas,histoname,directory,histotitle,option);
  
  // set error bars in x to default
  gStyle->SetErrorX(0.5);

  // delete old canvas
  if ( fCanvas ) {
    delete fCanvas;
    fCanvas = 0;
  }

  // restore batch level
  if ( !batch )
    gROOT->SetBatch(kFALSE);

  return kTRUE;
}

//_____________________________________________________________

Bool_t GPictureMaker::MakeDataMCComparisonPlot(TFile *file, TString period, TString name, TString datadir, TString histoname, TString histotitle, TString directory, TString option, Double_t addToMaximum) {
  //
  // make mc comparison plot
  if ( gDebug ) cout << endl << "GPictureMaker::MakeDataMCComparisonPlot called" << endl << endl;

  TH1D **histos = new TH1D *[4];

  // data histo
  TString dummy = "Histograms";
  if ( !datadir.BeginsWith("/") )
    dummy.Append("/");
  dummy.Append(datadir);
  if ( !name.BeginsWith("/") )
    dummy.Append("/");
  dummy.Append(name);
  histos[0]=(TH1D*)file->Get(dummy.Data());
  if ( histos[0] == 0 ) {
    return kFALSE;
  }

  // b mc histo
  dummy = "Histograms/mc";
  if ( !period.BeginsWith("/") )
    dummy.Append("/");
  dummy.Append(period);
  if ( !dummy.EndsWith("/") )
    dummy.Append("/");
  dummy.Append("b/merged");
  if ( !name.BeginsWith("/") )
    dummy.Append("/");
  dummy.Append(name);
  histos[1]=(TH1D*)file->Get(dummy.Data());
  if ( histos[1] == 0 ) {
    return kFALSE;
  }

  // c mc histo
  dummy = "Histograms/mc";
  if ( !period.BeginsWith("/") )
    dummy.Append("/");
  dummy.Append(period);
  if ( !dummy.EndsWith("/") )
    dummy.Append("/");
  dummy.Append("c/merged");
  if ( !name.BeginsWith("/") )
    dummy.Append("/");
  dummy.Append(name);
  histos[2]=(TH1D*)file->Get(dummy.Data());
  if ( histos[2] == 0 ) {
    return kFALSE;
  }

  // lf mc histo
  dummy = "Histograms/mc";
  if ( !period.BeginsWith("/") )
    dummy.Append("/");
  dummy.Append(period);
  if ( !dummy.EndsWith("/") )
    dummy.Append("/");
  dummy.Append("lf/merged");
  if ( !name.BeginsWith("/") )
    dummy.Append("/");
  dummy.Append(name);
  histos[3]=(TH1D*)file->Get(dummy.Data());
  if ( histos[3] == 0) {
    return kFALSE;
  }

  dummy = "mc";
  if ( !period.BeginsWith("/") )
    dummy.Append("/");
  dummy.Append(period);

  GPtRelFit *fit = gInclude->GetFit(file,dummy);
  if ( fit == 0 ) {
    return kFALSE;
  }

  // calculate fraction
  Double_t fraction = fit->GetBFraction();
  Double_t fraction_error = fit->GetBFractionErr();

  // set batch to true
  Bool_t batch = gROOT->IsBatch();
  if ( !batch )
    gROOT->SetBatch(kTRUE);

  // delete old canvas
  if ( fCanvas ) {
    delete fCanvas;
    fCanvas = 0;
  }

  // canvas
  if ( !fCanvas ) {
    fCanvas = new TCanvas("canvas","canvas",640,480);
  } 

  // set error bars in x off
  gStyle->SetErrorX(0);

  fCanvas->cd();
  fCanvas->Clear();
  fCanvas->SetLogy(0);

  gStyle->SetOptStat(0);

  histos[0]->SetMarkerColor(2);
  histos[0]->SetMarkerStyle(8);
  histos[0]->SetMarkerSize(1.3);
  histos[0]->SetTitleOffset(1.2);
  histos[0]->SetName("ptrel");
  histos[0]->SetTitle(histotitle.Data());
  if ( addToMaximum > 0.0 )
    histos[0]->SetMaximum(histos[0]->GetMaximum()+addToMaximum);
  histos[0]->Draw("PE");

  histos[1]->SetTitle("test");
  histos[1]->SetLineColor(4);
  histos[1]->SetLineStyle(3);
  histos[1]->SetLineWidth((Short_t)3);
  histos[1]->SetTitleOffset(1.2);
  histos[1]->Scale(fit->GetBScale());
  histos[1]->Draw("HIST,SAME");

  histos[2]->Add(histos[3],1);
  histos[2]->Scale(fit->GetCLFScale());
  histos[2]->Add(histos[1],1);
  histos[2]->SetTitleOffset(1.2);
  histos[2]->SetLineColor(3);
  histos[2]->Draw("HIST,SAME");

  TString label = "";
  label.Append(gInclude->FormatedDouble(fraction,2,3));
  label.Append (" #pm ");
  label.Append(gInclude->FormatedDouble(fraction_error,2,3));

  TPaveText *text = new TPaveText(0.64,0.78,0.94,0.86,"br,NDC");
  text->AddText("bbbar fraction:");
  text->AddText(label.Data());
  text->Draw("SAME");

  TLegend *leg = new TLegend(0.64,0.87,0.94,0.99);
  leg->SetTextSize(0.035); 
  leg->SetFillColor(10);
  leg->SetBorderSize(1); // no frame, no shadow
  leg->AddEntry(histos[0], "Data 96p" , "P" );
  leg->AddEntry(histos[1], "MC bbbar" , "L" );
  leg->AddEntry(histos[2], "MC bbbar+ccbar+lf" , "L" );
  leg->Draw("SAME");

  gInclude->NicePlot(fCanvas);
  gInclude->NicePlot(fCanvas);
 
  GenHTMLPics(fCanvas,histoname.Data(),directory,histotitle.Data(),option);
  
  // set error bars in x to default
  gStyle->SetErrorX(0.5);

  // delete old canvas
  if ( fCanvas ) {
    delete fCanvas;
    fCanvas = 0;
  }

  // restore batch level
  if ( !batch )
    gROOT->SetBatch(kFALSE);

  return kTRUE;
}

//_____________________________________________________________

Bool_t GPictureMaker::MakeComparisonPlot(TFile *file, ofstream *stream, TString histogramname, TString ptrelhistogramname, TString period, TString directory, TString option, Double_t scaleMaximum) {
  //
  // make mc comparison plot
  if ( gDebug ) cout << endl << "GPictureMaker::MakeComparisonPlot called" << endl << endl;

  option.ToUpper();
  
  Double_t statsX1NDC = 0.68;
  Double_t statsY1NDC = 0.88;
  Double_t statsX2NDC = 0.98;
  Double_t statsY2NDC = 0.995;
  Double_t legX1NDC = 0.0;
  Double_t legY1NDC = 0.0;
  Double_t legX2NDC = 0.0;
  Double_t legY2NDC = 0.0;
  if ( option.Contains("PTREL") ) {
    if (option.Contains("STATS")) {
      legX1NDC = 0.68;
      legY1NDC = 0.75;
      legX2NDC = 0.98;
      legY2NDC = 0.87;
    } else {
      legX1NDC = 0.68;
      legY1NDC = 0.87;
      legX2NDC = 0.98;
      legY2NDC = 0.995;
    }
  } else if ( option.Contains("LUMI") ) {
    if (option.Contains("STATS")) {
      legX1NDC = 0.68;
      legY1NDC = 0.67;
      legX2NDC = 0.98;
      legY2NDC = 0.87;
    } else {
      legX1NDC = 0.68;
      legY1NDC = 0.81;
      legX2NDC = 0.98;
      legY2NDC = 0.995;
    }
  }
  Double_t textX1NDC = 0.0;
  Double_t textY1NDC = 0.0;
  Double_t textX2NDC = 0.0;
  Double_t textY2NDC = 0.0;
  if (option.Contains("STATS")) {
    textX1NDC = 0.68;
    textY1NDC = 0.64;
    textX2NDC = 0.98;
    textY2NDC = 0.74;
  } else {
    textX1NDC = 0.68;
    textY1NDC = 0.77;
    textX2NDC = 0.98;
    textY2NDC = 0.86;
  }

  TH1D **histos = new TH1D *[6];

  TString datahistname = "Histograms/data/merged/";
  datahistname.Append(histogramname);
  datahistname.Append("_");
  // fix for period 03p-04p_ztt
  TString tempperiod = period;
  tempperiod.ReplaceAll("_ztt","");
  datahistname.Append(tempperiod);
  histos[0]=(TH1D*)file->Get(datahistname);
  if ( histos[0] == 0) {
//     cout << "comparison-problems in getting histogram: " << datahistname << endl;
    return kFALSE;
  }
  
  TString bhistname = "Histograms/mc/";
  bhistname.Append(period);
  bhistname.Append("/b/merged/");
  bhistname.Append(histogramname);
  histos[1]=(TH1D*)file->Get(bhistname);
  if ( histos[1] == 0 ) {
//     cout << "comparison-problems in getting histogram: " << bhistname << endl;
    return kFALSE;
  }

  TString chistname = "Histograms/mc/";
  chistname.Append(period);
  chistname.Append("/c/merged/");
  chistname.Append(histogramname);
  histos[2]=(TH1D*)file->Get(chistname);
  if ( histos[2] == 0 ) {
//     cout << "comparison-problems in getting histogram: " << chistname << endl;
    return kFALSE;
  }

  TString lfhistname = "Histograms/mc/";
  lfhistname.Append(period);
  lfhistname.Append("/lf/merged/");
  lfhistname.Append(histogramname);
  histos[3]=(TH1D*)file->Get(lfhistname);
  if ( histos[3] == 0 ) {
//     cout << "comparison-problems in getting histogram: " << lfhistname << endl;
    return kFALSE;
  }

  TString bclfhistname = "Histograms/mc/";
  bclfhistname.Append(period);
  bclfhistname.Append("/merged/");
  bclfhistname.Append(histogramname);
  bclfhistname.Append("_b_c_lf");
  histos[4]=(TH1D*)file->Get(bclfhistname);
  if ( histos[4] == 0 ) {
//     cout << "comparison-problems in getting histogram: " << bclfhistname << endl;
    return kFALSE;
  }

  TH1D *cbhisto = (TH1D*)histos[2]->Clone("cbhisto");
  cbhisto->Reset();
  cbhisto->Add(histos[2]);
  histos[5]=cbhisto;
  
  TString ptrelhistname = datahistname;
  TString tempptrelhistogramname = ptrelhistogramname;
  if ( option.Contains("FORWARD") ) {
    tempptrelhistogramname.Append("_Forward");
  } else if ( option.Contains("BARREL") ) {
    tempptrelhistogramname.Append("_Barrel");
  } else if ( option.Contains("REAR") ) {
    tempptrelhistogramname.Append("_Rear");
  }
  ptrelhistname.ReplaceAll(histogramname,tempptrelhistogramname);

  GPtRelFit *fit = gInclude->GetFit(file,ptrelhistname);
  if ( fit == 0 ) {
//     cout << "comparison-problems in getting fit for: " << ptrelhistname << endl;
    return kFALSE;
  }

  if ( option.Contains("PTREL") ) {
    cout << "GPictureMaker::MakeComparisonPlot for " << histogramname << " in PTREL mode for period " << period;
    if ( option.Contains("FORWARD") ) {
      cout << " using forward ptrel fit";
    } else if ( option.Contains("BARREL") ) {
      cout << " using barrel ptrel fit";
    } else if ( option.Contains("REAR") ) {
      cout << " using rear ptrel fit";
    }
    cout << endl;
  } else {
    cout << "GPictureMaker::MakeComparisonPlot for " << histogramname << " in LUMI mode for period " << period << endl;
  }

  // calculate fraction
  Double_t fraction = fit->GetBFraction();
  Double_t fraction_error = fit->GetBFractionErr();

  // set batch to true
  Bool_t batch = gROOT->IsBatch();
  if ( !batch )
    gROOT->SetBatch(kTRUE);

  // delete old canvas
  if ( fCanvas ) {
    delete fCanvas;
    fCanvas = 0;
  }

  // canvas
  if ( !fCanvas ) {
    fCanvas = new TCanvas("canvas","canvas",640,480);
  } 

  // set error bars in x off
  gStyle->SetErrorX(0);

  fCanvas->cd();
  fCanvas->Clear();
  fCanvas->SetLogy(0);

  if (option.Contains("STATS"))
    gStyle->SetOptStat(1110);
  else
    gStyle->SetOptStat(0);

  // prepare histograms
  TString histoname = "comparison_";
  if ( option.Contains("PTREL") )
    histoname.Append("ptrel_");
  else if ( option.Contains("LUMI") )
    histoname.Append("lumi_");
  histoname.Append(histogramname);
  if ( option.Contains("FORWARD") ) {
    histoname.Append("_forward");
  } else if ( option.Contains("BARREL") ) {
    histoname.Append("_barrel");
  } else if ( option.Contains("REAR") ) {
    histoname.Append("_rear");
  } 
  histoname.Append("_");
  histoname.Append(period);
  histoname.ReplaceAll("/","_");
  histoname.ToLower();
  histos[0]->SetName(histoname);
  TString histotitle = histogramname;
  histotitle.Append(" using ");
  if ( option.Contains("PTREL") ) {
    if ( option.Contains("FORWARD") ) {
      histotitle.Append("forward ");
    } else if ( option.Contains("BARREL") ) {
      histotitle.Append("barrel ");
    } else if ( option.Contains("REAR") ) {
      histotitle.Append("rear ");
    } 
    histotitle.Append("p_{T}^{rel} fit");
  } else if ( option.Contains("LUMI") )
    histotitle.Append("lumi");
  histotitle.Append(" in ");
  histotitle.Append(period);

  histos[0]->SetStats(kTRUE);
  histos[0]->SetMarkerColor(2);
  histos[0]->SetMarkerStyle(8);
  histos[0]->SetMarkerSize(1.3);
  histos[0]->SetTitleOffset(1.2);
  histos[0]->SetName(histoname);
  histos[0]->SetTitle(histotitle);

  if ( option.Contains("PTREL") ) {
    
    // scale histos[1] (bbbar) before adding to scaled histos[2] (c+lf)
    histos[1]->Scale(fit->GetBScale());

    histos[2]->SetStats(kFALSE);
    histos[2]->Add(histos[3],1);
    histos[2]->Scale(fit->GetCLFScale());
    histos[2]->Add(histos[1],1);
    histos[2]->SetLineStyle(1);
    histos[2]->SetLineWidth((Short_t)3);
    histos[2]->SetLineColor(8);
    
    if (DoCLFDraw()){
      histos[5]->Scale(fit->GetCLFScale());
      histos[5]->Add(histos[1],1);
      histos[5]->SetLineStyle(3);
      histos[5]->SetLineWidth((Short_t)3);
      histos[5]->SetLineColor(6);
    }

  } else if ( option.Contains("LUMI") ) {
    
    histos[4]->SetStats(kFALSE);
    histos[4]->SetLineColor(8);
    histos[4]->SetLineStyle(1);
    histos[4]->SetLineWidth((Short_t)3);
    histos[4]->SetTitleOffset(1.2);
    
    histos[3]->SetStats(kFALSE);
    histos[3]->SetLineColor(43);
    histos[3]->SetLineStyle(1);
    histos[3]->SetLineWidth((Short_t)3);
    histos[3]->SetTitleOffset(1.2);
    
    histos[2]->SetStats(kFALSE);
    histos[2]->SetLineColor(50);
    histos[2]->SetLineStyle(1);
    histos[2]->SetLineWidth((Short_t)3);
    histos[2]->SetTitleOffset(1.2);
    
  }
  
  histos[1]->SetStats(kFALSE);
  histos[1]->SetTitle("b");
  histos[1]->SetLineColor(4);
  histos[1]->SetLineStyle(1);
  histos[1]->SetLineWidth((Short_t)3);
  histos[1]->SetTitleOffset(1.2);
  
  // determine maximum of plot
  // determine histo with maximum in last 40% of bins
  Int_t startbins = (Int_t)(textX1NDC * histos[0]->GetNbinsX());
  Double_t max = histos[0]->GetMaximum();
  if ( option.Contains("PTREL") ) {
    for ( Int_t i = 0; i < 3; ++i ) {
      if ( max < histos[i]->GetMaximum() )
	max = histos[i]->GetMaximum();
    }
    if (DoCLFDraw()){
      if ( max < histos[5]->GetMaximum() )
	max = histos[5]->GetMaximum();
    }
  } else if ( option.Contains("LUMI") ) {
    for ( Int_t i = 0; i < 5; ++i ) {
      if ( max < histos[i]->GetMaximum() )
	max = histos[i]->GetMaximum();
    }
  }
  
  Double_t localmax = -9999.99;

  if ( option.Contains("PTREL") ) {
    for ( Int_t i = 0; i < 3; ++i ) {
      for ( Int_t bin = startbins; bin <= histos[i]->GetNbinsX(); ++bin){
	if ( localmax < histos[i]->GetBinContent(bin) )
	  localmax = histos[i]->GetBinContent(bin);
      }
    }
    if (DoCLFDraw()){
      for ( Int_t bin = startbins; bin <= histos[5]->GetNbinsX(); ++bin){
	if ( localmax < histos[5]->GetBinContent(bin) )
	  localmax = histos[5]->GetBinContent(bin);
      }
    }
  } else if ( option.Contains("LUMI") ) {
    for ( Int_t i = 0; i < 5; ++i ) {
      for ( Int_t bin = startbins; bin <= histos[i]->GetNbinsX(); ++bin){
	if ( localmax < histos[i]->GetBinContent(bin) )
	  localmax = histos[i]->GetBinContent(bin);
      }
    }
  }

  if ( option.Contains("PTREL") ) {
    if ( localmax > (textY1NDC*max) )
      max = 1/textY1NDC*localmax;
  } else if ( option.Contains("LUMI") ) {
    if ( localmax > (legY1NDC*max) )
      max = 1/legY1NDC*localmax;
  }

  histos[0]->SetMaximum(1.15*max);

  if ( scaleMaximum > 1.2 )
    histos[0]->SetMaximum(histos[0]->GetMaximum()*scaleMaximum);

  histos[0]->Draw("PE");

  if (option.Contains("STATS")) {
    fCanvas->Update();
    TPaveStats *stats = (TPaveStats*)(histos[0]->GetListOfFunctions()->FindObject("stats"));
    stats->SetX1NDC(statsX1NDC);
    stats->SetY1NDC(statsY1NDC);
    stats->SetX2NDC(statsX2NDC);
    stats->SetY2NDC(statsY2NDC);
  }

  // title pave text
  fCanvas->Update();
  TPaveText *titlepave = (TPaveText*)fCanvas->FindObject("title");
  if ( titlepave->GetX2NDC() > 0.67 )
    titlepave->SetX2NDC(0.67);
  
  // draw histograms
  if ( option.Contains("PTREL") ) {
    
    if (DoCLFDraw()){
      histos[5]->Draw("HIST,SAME");
    }
    
    histos[2]->Draw("HIST,SAME");    
    
  } else if ( option.Contains("LUMI") ) {
    
    histos[4]->Draw("HIST,SAME");
    
    histos[3]->Draw("HIST,SAME");
    
    histos[2]->Draw("HIST,SAME");
    
  }
  
  histos[1]->Draw("HIST,SAME");
  
  // redraw data
  histos[0]->Draw("PE,SAME");
  
  TLegend *leg = 0;
  if ( option.Contains("PTREL") ) {
    leg = new TLegend(legX1NDC,legY1NDC,legX2NDC,legY2NDC);
    leg->SetTextSize(0.035); 
    leg->SetFillColor(10);
    leg->SetBorderSize(1); // no frame, no shadow
    TString datalegendentry = "Data ";
    datalegendentry.Append(period);
    leg->AddEntry(histos[0], datalegendentry , "P" );
    if (DoCLFDraw()){
      leg->AddEntry(histos[1], "MC bbbar" , "L" );
      leg->AddEntry(histos[5], "MC bbbar+ccbar" , "L" );
      leg->AddEntry(histos[2], "MC bbbar+ccbar+lf" , "L" );
    }
    else {
      leg->AddEntry(histos[1], "MC bbbar" , "L" );
      leg->AddEntry(histos[2], "MC ccbar+lf+bbbar" , "L" );
    }
  } else if ( option.Contains("LUMI") ) {
    leg = new TLegend(legX1NDC,legY1NDC,legX2NDC,legY2NDC);
    leg->SetTextSize(0.035); 
    leg->SetFillColor(10);
    leg->SetBorderSize(1); // no frame, no shadow
    TString datalegendentry = "Data ";
    datalegendentry.Append(period);
    leg->AddEntry(histos[0], datalegendentry , "P" );
    leg->AddEntry(histos[1], "MC b" , "L" );
    leg->AddEntry(histos[2], "MC c" , "L" );
    leg->AddEntry(histos[3], "MC lf" , "L" );
    leg->AddEntry(histos[4], "MC b+c+lf" , "L" );
  }
  leg->Draw("SAME");
  
  if ( option.Contains("PTREL") ) {
    TString label = "";
    label.Append(gInclude->FormatedDouble(fraction,2,3));
    label.Append (" #pm ");
    label.Append(gInclude->FormatedDouble(fraction_error,2,3));
    
    TPaveText *text = new TPaveText(textX1NDC,textY1NDC,textX2NDC,textY2NDC,"br,NDC");
    text->AddText("bbbar fraction:");
    text->AddText(label.Data());
    text->Draw("SAME");
  }

  gInclude->NicePlot(fCanvas);
  gInclude->NicePlot(fCanvas);
 
  GenHTMLPics(stream,fCanvas,histoname,directory,histotitle,option);
  
  // set error bars in x to default
  gStyle->SetErrorX(0.5);

  // delete old canvas
  if ( fCanvas ) {
    delete fCanvas;
    fCanvas = 0;
  }

  // restore batch level
  if ( !batch )
    gROOT->SetBatch(kFALSE);

  return kTRUE;
}

//_____________________________________________________________

Bool_t GPictureMaker::MakeComparisonPlotLumi(TFile *file, TString period, TString name, TString datadir, TString histoname, TString histotitle, TString directory, TString option) {
  //
  // make mc comparison plot
  if ( gDebug ) cout << endl << "GPictureMaker::MakeDataMCComparisonPlot called" << endl << endl;

  TH1D **histos = new TH1D *[5];

  // data histo
  TString dummy = "Histograms";
  if ( !datadir.BeginsWith("/") )
    dummy.Append("/");
  dummy.Append(datadir);
  if ( !name.BeginsWith("/") )
    dummy.Append("/");
  dummy.Append(name);
  histos[0]=(TH1D*)file->Get(dummy.Data());
  if ( histos[0] == 0 ) {
    return kFALSE;
  }

  // b mc histo
  dummy = "Histograms/mc";
  if ( !period.BeginsWith("/") )
    dummy.Append("/");
  dummy.Append(period);
  if ( !dummy.EndsWith("/") )
    dummy.Append("/");
  dummy.Append("b/merged");
  if ( !name.BeginsWith("/") )
    dummy.Append("/");
  dummy.Append(name);
  histos[1]=(TH1D*)file->Get(dummy.Data());
  if ( histos[1] == 0 ) {
    return kFALSE;
  }

  // c mc histo
  dummy = "Histograms/mc";
  if ( !period.BeginsWith("/") )
    dummy.Append("/");
  dummy.Append(period);
  if ( !dummy.EndsWith("/") )
    dummy.Append("/");
  dummy.Append("c/merged");
  if ( !name.BeginsWith("/") )
    dummy.Append("/");
  dummy.Append(name);
  histos[2]=(TH1D*)file->Get(dummy.Data());
  if ( histos[2] == 0 ) {
    return kFALSE;
  }

  // lf mc histo
  dummy = "Histograms/mc";
  if ( !period.BeginsWith("/") )
    dummy.Append("/");
  dummy.Append(period);
  if ( !dummy.EndsWith("/") )
    dummy.Append("/");
  dummy.Append("lf/merged");
  if ( !name.BeginsWith("/") )
    dummy.Append("/");
  dummy.Append(name);
  histos[3]=(TH1D*)file->Get(dummy.Data());
  if ( histos[3] == 0) {
    return kFALSE;
  }

  // b+c+lf merged mc histo
  dummy = "Histograms/mc";
  if ( !period.BeginsWith("/") )
    dummy.Append("/");
  dummy.Append(period);
  if ( !dummy.EndsWith("/") )
    dummy.Append("/");
  dummy.Append("merged");
  if ( !name.BeginsWith("/") )
    dummy.Append("/");
  dummy.Append(name);
  dummy.Append("_b_c_lf");
  histos[4]=(TH1D*)file->Get(dummy.Data());
  if ( histos[4] == 0) {
    return kFALSE;
  }

  // set batch to true
  Bool_t batch = gROOT->IsBatch();
  if ( !batch )
    gROOT->SetBatch(kTRUE);

  // delete old canvas
  if ( fCanvas ) {
    delete fCanvas;
    fCanvas = 0;
  }

  // canvas
  if ( !fCanvas ) {
    fCanvas = new TCanvas("canvas","canvas",640,480);
  } 

  // set error bars in x off
  gStyle->SetErrorX(0);

  fCanvas->cd();
  fCanvas->Clear();
  fCanvas->SetLogy(0);

  gStyle->SetOptStat(0);

  // determine histo with maximum
  Double_t max = 0;
  Int_t index = -99;
  for ( Int_t i = 0; i < 5; ++i ) {
    if ( histos[i]->GetMaximum() > max ) {
      max = histos[i]->GetMaximum();
      index = i;
    }
  }


  histos[index]->SetLineColor(10);
  histos[index]->SetTitleOffset(1.2);
  histos[index]->SetName("ptrel");
  histos[index]->SetTitle(histotitle.Data());
  histos[index]->Draw("Line");

  histos[0]->SetMarkerColor(2);
  histos[0]->SetMarkerStyle(8);
  histos[0]->SetMarkerSize(1.3);
  histos[0]->SetTitleOffset(1.2);
  histos[0]->SetName("ptrel");
  histos[0]->SetTitle(histotitle.Data());
  histos[0]->Draw("PE,Same");

  histos[1]->SetLineColor(4);
  histos[1]->SetLineStyle(3);
  histos[1]->SetLineWidth((Short_t)3);
  histos[1]->SetTitleOffset(1.2);
  histos[1]->Draw("HIST,SAME");

  histos[2]->SetLineColor(5);
  histos[2]->SetLineStyle(3);
  histos[2]->SetLineWidth((Short_t)3);
  histos[2]->SetTitleOffset(1.2);
  histos[2]->Draw("HIST,SAME");

  histos[3]->SetLineColor(6);
  histos[3]->SetLineStyle(3);
  histos[3]->SetLineWidth((Short_t)3);
  histos[3]->SetTitleOffset(1.2);
  histos[3]->Draw("HIST,SAME");

  histos[4]->SetLineColor(7);
  histos[4]->SetLineStyle(3);
  histos[4]->SetLineWidth((Short_t)3);
  histos[4]->SetTitleOffset(1.2);
  histos[4]->Draw("HIST,SAME");

  TLegend *leg = new TLegend(0.78,0.81,0.94,0.99);
  leg->SetTextSize(0.035); 
  leg->SetFillColor(10);
  leg->SetBorderSize(1); // no frame, no shadow
  leg->AddEntry(histos[0], "Data 96p" , "P" );
  leg->AddEntry(histos[1], "MC b" , "L" );
  leg->AddEntry(histos[2], "MC c" , "L" );
  leg->AddEntry(histos[3], "MC lf" , "L" );
  leg->AddEntry(histos[4], "MC b+c+lf" , "L" );
  leg->Draw("SAME");

  gInclude->NicePlot(fCanvas);
  gInclude->NicePlot(fCanvas);
 
  GenHTMLPics(fCanvas,histoname.Data(),directory,histotitle.Data(),option);
  
  // set error bars in x to default
  gStyle->SetErrorX(0.5);

  // delete old canvas
  if ( fCanvas ) {
    delete fCanvas;
    fCanvas = 0;
  }

  // restore batch level
  if ( !batch )
    gROOT->SetBatch(kFALSE);

  return kTRUE;
}

//_____________________________________________________________

void GPictureMaker::HelpMessage() {
  //
  // help message for concatenating cards
  if ( gDebug ) cout << "GPictureMaker::HelpMessage() called" << endl;

  cout << "----------------------------------------------------------------------------------------------------------" << endl
       << "picturemaker.exe [options] -histogram-file [file] -output-file [file]                                     " << endl
       << "                           -input-dir [input] -dir [dir] -file1 [file1] -file2 [file2]" << endl
       << "                           -title [title] -date [date] -scale [scale] [mode]" << endl
       << "----------------------------------------------------------------------------------------------------------" << endl
       << "options:" << endl
       << "-help          : print this message" << endl
       << "--help         : print this message" << endl
       << endl
       << "-histogram-file: " << endl
       << "file           : input histogram file" << endl
       << endl
       << "-file1         : " << endl
       << "file           : input histogram file 1" << endl
       << endl
       << "-file2         : " << endl
       << "file           : input histogram file 2" << endl
       << endl
       << "-output-file: " << endl
       << "file           : output file for PS and LOGPS mode" << endl
       << endl
       << "-input-dir     : " << endl
       << "input          : input directory" << endl
       << endl
       << "-dir           : " << endl
       << "dir            : output directory" << endl
       << endl
       << "-til           : " << endl
       << "tile           : title of HTMLGallery" << endl
       << endl
       << "-date          : " << endl
       << "date           : date of HTMLGallery" << endl
       << endl
       << "-scale         : " << endl
       << "scale          : scale for small images in percent for HTMLGallery" << endl
       << endl
       << "mode:" << endl
       << "PS             : output of Histograms in multi-page ps" << endl
       << "LOGPS          : output of Histograms in multi-page ps" << endl
       << "SPECIAL        : make pictures of special projects" << endl
       << "SPECIALSTATS   : make pictures of special projects including stats on canvas" << endl
       << "GALLERY        : make picture gallery" << endl
       << "SPECIALGALLERY : make picture gallery incl. specials part" << endl
       << "COMPARE        : compare two histos.root directly from analysis.exe" << endl
       << "----------------------------------------------------------------------------------------------------------" << endl;
  
}

//_____________________________________________________________

void GPictureMaker::DecodeCommandline(int argc, char **argv) {
  //
  // decode commandline parameters and call respective fill functions
  if ( gDebug ) cout << "GPictureMaker::HelpMessage() called" << endl;

  // check if first parameter is an option
  // positions given in index of opt

  TString option = "";

  // spool parameters in string array
  TString opt[argc];

  if ( argc > 1 ) {
    for ( Int_t i = 0; i < argc; i++ ) {
      opt[i]=argv[i];
    }
  } else {
    this->HelpMessage();
    return;
  }

  // decode
  for ( Int_t i = 0; i < argc; i++ ) {
    if ( opt[i].Contains("help") ) {
      this->HelpMessage();
      return;
    } else if ( opt[i].Contains("scale") ) {
      istrstream stream(opt[++i].Data());
      stream >> fScaleFactor;
    } else if ( opt[i].Contains("title") ) {
      fTitle = opt[++i].Data();
    } else if ( opt[i].Contains("date") ) {
      fDate = opt[++i].Data();
    } else if ( opt[i].Contains("input-dir") ) {
      fInputDir = opt[++i].Data();
      // check whether directory exists, else generate
      gSystem->mkdir(fInputDir.Data(),kTRUE);
    } else if ( opt[i].Contains("dir") ) {
      fDirectory = opt[++i].Data();
      // check whether directory exists, else generate
      gSystem->mkdir(fDirectory.Data(),kTRUE);
    } else if ( opt[i].Contains("output") ) {
      fOutputFile = opt[++i].Data();
    } else if ( opt[i].Contains("histogram") ) {
      fFile = new TFile(opt[++i].Data(),"UPDATE");
      if ( !fFile->IsOpen() ) {
	fFile = 0;
	this->HelpMessage();
	return;
      }
    } else if ( opt[i].Contains("file1") ) {
      fComparisonFile1 = new TFile(opt[++i].Data(),"UPDATE");
      if ( !fComparisonFile1->IsOpen() ) {
	fComparisonFile1 = 0;
	this->HelpMessage();
	return;
      }
    } else if ( opt[i].Contains("file2") ) {
      fComparisonFile2 = new TFile(opt[++i].Data(),"UPDATE");
      if ( !fComparisonFile2->IsOpen() ) {
	fComparisonFile2 = 0;
	this->HelpMessage();
	return;
      }
    } else if ( (i == (argc-1)) ) {
      fMode = opt[i].Data();
      fMode.ToUpper();
    } 
  }

  if ( fMode.Length() == 0 ) {
    this->HelpMessage();
    return;
  }
      
  if ( fMode.Contains("LOGPS") ) {
    if ( fOutputFile.Length() == 0 ) {
      this->HelpMessage();
      return;
    } else {
      this->MakePics(fFile,fOutputFile.Data(), fDirectory.Data(), 4, 2, "LOGPS");
    }
  } else if ( fMode.Contains("PS") ) {
    if ( fOutputFile.Length() == 0 ) {
      this->HelpMessage();
      return;
    } else {
      this->MakePics(fFile,fOutputFile.Data(), fDirectory.Data(), 4, 2, "PS");
    }
  } else if ( fMode.Contains("SPECIALGALLERY") ) {
    this->MakeGallery(fFile,fDirectory,"SPECIAL");
  } else if ( fMode.Contains("COMPARE") ) {
    this->MakeTwoFileComparison(fComparisonFile1,fComparisonFile2,fDirectory,"");
  } else if ( fMode.Contains("SPECIALSTATS") ) {
    option.Append(",STATS");
    this->MakeSpecial(fFile,fDirectory,option);
  } else if ( fMode.Contains("SPECIAL") ) {
    this->MakeSpecial(fFile,fDirectory,option);
  } else if ( fMode.Contains("GALLERY") ) {
    this->MakeGallery(fFile,fDirectory,option);
  } else {
    this->HelpMessage();
    return;
  }

}

//_____________________________________________________________

Bool_t GPictureMaker::HTMLStart(ofstream *stream, TString title, TString filename, TString option) {
  //
  // start html stream
  if ( gDebug ) cout << endl << "GPictureMaker::HTMLStart() called" << endl << endl;

  option.ToUpper();

  *stream << "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">" << endl;
  *stream << "<html>" << endl;
  *stream << "<head>" << endl;
  *stream << "<title>" << title.Data() << "</title>" << endl;
  *stream << "<LINK REL=\"STYLESHEET\" TYPE=\"text/css\" HREF=\"http://www-zeus.desy.de/~gutsche/physics/css/zeus.css\">" << endl;
  *stream << "<link rel=\"shortcut icon\" href=\"http://www-zeus.desy.de/~gutsche/general/gutsoft.ico\">" << endl;
  *stream << "</head>" << endl;
  *stream << "<body bgcolor=\"#fffff0\">" << endl;
  *stream << "<table width=\"810\" align=\"left\">" << endl;
  *stream << "<tbody>" << endl;
  *stream << "<tr><td><big><big><big><big><big><big><b><font color=\"#0000aa\">" << title.Data() << "</font></b></big></big></big></big></big></big><br><br></td></tr>" << endl;
  *stream << "<tr>" << endl;
  *stream << "<td>" << endl;
  *stream << "<TABLE width=\"90%\" BORDER=\"0\" CELLPADDING=\"0\" CELLSPACING=\"0\" align=\"center\">" << endl;
  *stream << "<TR><TD width=\"160\" colspan=\"4\"><IMG SRC=\"http://www-zeus.desy.de/~gutsche/physics/pic/spacer.gif\" WIDTH=\"1\" HEIGHT=\"1\" HSPACE=\"50\" VSPACE=\"5\" ALT=\"\"></TD></TR>" << endl;
  *stream << "<TR><TD width=\"160\" colspan=\"4\" VALIGN=top ALIGN=left class=\"head1\"><DIV class=\"h3s\">" << title.Data() << "</DIV></TD></TR>" << endl;
  *stream << "<TR><TD width=\"160\" colspan=\"4\" class=\"cell1\"><IMG SRC=\"http://www-zeus.desy.de/~gutsche/physics/pic/spacer.gif\" WIDTH=\"1\" HEIGHT=\"2\" HSPACE=\"0\" ALT=\"\"></TD></TR>" << endl;
  
  if ( option.Contains("TOP") ) {
  *stream << "<TR>" << endl;
  *stream << "<TD width=\"15\" VALIGN=bottom ALIGN=right class=\"cell1\"><IMG SRC=\"http://www-zeus.desy.de/~gutsche/physics/pic/spacer.gif\" WIDTH=\"10\" HEIGHT=\"1\" ALT=\"\"></TD>" << endl;
  *stream << "<TD  VALIGN=top ALIGN=left class=\"cell1\"><P class=\"c1s\">" << filename.Data() << "</TD>" << endl;
  *stream << "<TD width=\"15\" VALIGN=bottom ALIGN=right class=\"cell1\"><IMG SRC=\"http://www-zeus.desy.de/~gutsche/physics/pic/spacer.gif\" WIDTH=\"10\" HEIGHT=\"1\" ALT=\"\"></TD>" << endl;
  *stream << "<TD  VALIGN=top ALIGN=left class=\"cell1\"><P class=\"c1s\">" << endl;
  *stream << "<ul>" << endl;
  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GPictureMaker::HTMLEnd(ofstream *stream, TString top, TString date, TString option) {
  //
  // end html stream
  if ( gDebug ) cout << endl << "GPictureMaker::HTMLEnd() called" << endl << endl;

  TString username;
  option.ToUpper();

  if ( option.Contains("TOP") ) {
    *stream << "</ul>" << endl;
    *stream << "</TD>" << endl;
    *stream << "</TR>" << endl;
  }

  if ( option.Contains("SPECIAL") ) {
    *stream << "<TR>" << endl;
    *stream << "<TD width=\"15\" VALIGN=bottom ALIGN=right class=\"cell1\"><IMG SRC=\"http://www-zeus.desy.de/~gutsche/physics/pic/spacer.gif\" WIDTH=\"10\" HEIGHT=\"1\" ALT=\"\"></TD>" << endl;
    *stream << "<TD  VALIGN=top ALIGN=left class=\"cell1\"><P class=\"c1s\">Special</TD>" << endl;
    *stream << "<TD width=\"15\" VALIGN=bottom ALIGN=right class=\"cell1\"><IMG SRC=\"http://www-zeus.desy.de/~gutsche/physics/pic/spacer.gif\" WIDTH=\"10\" HEIGHT=\"1\" ALT=\"\"></TD>" << endl;
    *stream << "<TD  VALIGN=center ALIGN=left class=\"cell1\"><P class=\"c1s\">" << endl;
    *stream << "<ul>" << endl;
    *stream << "<li><a href=\"Histograms/special/ptrel/gallery.html\">PtRel</a></li>" << endl;
    *stream << "<li><a href=\"Histograms/all.ps.gz\">PS including all Histograms</a></li>" << endl;
    *stream << "<li><a href=\"Histograms/all_log.ps.gz\">PS including all log. Histograms</a></li>" << endl;
    *stream << "</ul>" << endl;
    *stream << "</TD>" << endl;
    *stream << "</TR>" << endl;

  }


  *stream << "<TR><TD width=\"160\" colspan=\"4\" class=\"cell1\"><IMG SRC=\"http://www-zeus.desy.de/~gutsche/physics/pic/spacer.gif\" WIDTH=\"1\" HEIGHT=\"3\" HSPACE=\"0\" ALT=\"\"></TD></TR>" << endl;
  *stream << "<TR><TD width=\"160\" colspan=\"4\"><IMG SRC=\"http://www-zeus.desy.de/~gutsche/physics/pic/spacer.gif\" WIDTH=\"1\" HEIGHT=\"1\" HSPACE=\"50\" VSPACE=\"5\" ALT=\"\"></TD></TR>" << endl;
  *stream << "</TABLE>" << endl;
  *stream << "</td>" << endl;
  *stream << "</tr>" << endl;
  *stream << "<tr>" << endl;
  *stream << "<td valign=\"top\">" << endl;
  *stream << "<hr width=\"90%\" size=\"1\" noshade=\"noshade\" align=\"center\">" << endl;
  *stream << "<table width=\"90%\" cellspacing=\"0\" border=\"0\" cellpadding=\"0\" align=\"center\">" << endl;
  *stream << "<tbody>" << endl;
  *stream << "<tr>" << endl;
  *stream << "<td width=\"100%\" align=\"right\"><font size=\"1\">" << endl;
  *stream << "<a href=\"" << top.Data() << "\">TOP</a>" << endl;
  username = gSystem->Getenv("USER") ;
  if (username.Contains("kahle")) {
    *stream << "<br><script type=text/javascript src=\"http://www-zeus.desy.de/~kahle/email.js\"></script>" << endl;
    *stream << "<input TYPE=\"image\" name=\"mail_ben\" src=\"http://www-zeus.desy.de/~kahle/images/mail_small.gif\" onClick=\"noSpam('benjamin.kahle','desy','de')\"><address>Benjamin Kahle</address>" << endl;
  }
  else if (username.Contains("gutsche")) 
    *stream << "<address><a href=\"mailto:oliver.gutsche@desy.de\">Oliver Gutsche</a></address>" << endl;
  else if (username.Contains("meyer"))
    *stream << "<address><a href=\"mailto:ursula.meyer@desy.de\">Ursula Meyer</a></address>" << endl;
  else {
    *stream << "<address><a href=\"mailto:" << username << "@mail.desy.de\">" << username << "</a></address>" << endl;
  }
  *stream << date.Data() << endl;
  *stream << "</font>" << endl;
  *stream << "</td>" << endl;
  *stream << "</tr>" << endl;
  *stream << "</tbody>" << endl;
  *stream << "</table>" << endl;
  *stream << "<br>" << endl;
  *stream << "</td></tr>" << endl;
  *stream << "</tbody>" << endl;
  *stream << "</table>" << endl;
  *stream << "</body>" << endl;
  *stream << "</html>" << endl;

  return kTRUE;
}

//_____________________________________________________________

TString GPictureMaker::GetTime() {
  //
  // get time
  if ( gDebug ) cout << endl << "GPictureMaker::GetTime() called" << endl << endl;

  TString time = "\n<!-- hhmts start -->\nLast modified: ";
  TDatime timer;
  time.Append(timer.AsString());
  time.ReplaceAll("200","CEST 200");
  time.Append("\n<!-- hhmts end -->");
  
  return time;
}

//_____________________________________________________________

Bool_t GPictureMaker::HTMLStreamTop(TString link, TString entry, TString option) {
  //
  // stream line in top html
  if ( gDebug ) cout << endl << "GPictureMaker::HTMLStreamTop() called" << endl << endl;

  *fHTMLTop << "<li><a href=\"" << link.Data() << "\">" << entry.Data() << "</a></li>" << endl;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GPictureMaker::HTMLStreamTop(ofstream *stream, TString link, TString entry, TString option) {
  //
  // stream line in top html
  if ( gDebug ) cout << endl << "GPictureMaker::HTMLStreamTop() called" << endl << endl;

  *stream << "<li><a href=\"" << link.Data() << "\">" << entry.Data() << "</a></li>" << endl;

  return kTRUE;
}

//_____________________________________________________________

Bool_t GPictureMaker::HTMLStream(TString thumb, TString title, TString ps, TString eps, TString gif, TString jpg,
				 TString logps, TString logeps, TString loggif, TString logjpg, TString option) {
  //
  // stream line in html
  if ( gDebug ) cout << endl << "GPictureMaker::HTMLStream() called" << endl << endl;
  
  *fHTML << "<TR>" << endl;
  *fHTML << "<TD width=\"15\" VALIGN=bottom ALIGN=right class=\"cell1\"><IMG SRC=\"http://www-zeus.desy.de/~gutsche/physics/pic/spacer.gif\" WIDTH=\"10\" HEIGHT=\"1\" ALT=\"\"></TD>" << endl;
  *fHTML << "<TD  VALIGN=top ALIGN=left class=\"cell1\"><P class=\"c1s\"><a href=\"" << gif.Data() << "\"><img src=\"" << thumb.Data() << "\"></a></TD>" << endl;
  *fHTML << "<TD width=\"15\" VALIGN=bottom ALIGN=right class=\"cell1\"><IMG SRC=\"http://www-zeus.desy.de/~gutsche/physics/pic/spacer.gif\" WIDTH=\"10\" HEIGHT=\"1\" ALT=\"\"></TD>" << endl;
  *fHTML << "<TD  VALIGN=center ALIGN=left class=\"cell1\"><P class=\"c1s\">" << endl;
  *fHTML << title.Data() << "<br>" << endl;
  
  if ( DoPicturesPS() )
    *fHTML << "<a href=\"" << ps.Data() << "\">(PS)</a>";
  if ( DoPicturesEPS() )
    *fHTML << "<a href=\"" << eps.Data() << "\">(EPS)</a>";
  if ( DoPicturesGIF() ) 
    *fHTML << "<a href=\"" << gif.Data() << "\">(GIF)</a>";
  if ( DoPicturesJPG() ) 
    *fHTML << "<a href=\"" << jpg.Data() << "\">(JPG)</a>";
  *fHTML << "<br>" << endl;

  if ( DoPicturesPS() )
    *fHTML << "<a href=\"" << logps.Data() << "\">(log PS)</a>";
  if ( DoPicturesEPS() )
    *fHTML << "<a href=\"" << logeps.Data() << "\">(log EPS)</a>";
  if ( DoPicturesGIF() ) 
    *fHTML << "<a href=\"" << loggif.Data() << "\">(log GIF)</a>";
  if ( DoPicturesJPG() ) 
    *fHTML << "<a href=\"" << logjpg.Data() << "\">(log JPG)</a>";
  *fHTML << "<br>" << endl;
  *fHTML << "</TD>" << endl;
  *fHTML << "</TR>" << endl;


  return kTRUE;
}

//_____________________________________________________________

Bool_t GPictureMaker::HTMLStream(ofstream *stream, TString thumb, TString title, TString ps, TString eps, TString gif, TString jpg,
				 TString logps, TString logeps, TString loggif, TString logjpg, TString option) {
  //
  // stream line in html
  if ( gDebug ) cout << endl << "GPictureMaker::HTMLStream() called" << endl << endl;
  
  *stream << "<TR>" << endl;
  *stream << "<TD width=\"15\" VALIGN=bottom ALIGN=right class=\"cell1\"><IMG SRC=\"http://www-zeus.desy.de/~gutsche/physics/pic/spacer.gif\" WIDTH=\"10\" HEIGHT=\"1\" ALT=\"\"></TD>" << endl;
  *stream << "<TD  VALIGN=top ALIGN=left class=\"cell1\"><P class=\"c1s\"><a href=\"" << gif.Data() << "\"><img src=\"" << thumb.Data() << "\"></a></TD>" << endl;
  *stream << "<TD width=\"15\" VALIGN=bottom ALIGN=right class=\"cell1\"><IMG SRC=\"http://www-zeus.desy.de/~gutsche/physics/pic/spacer.gif\" WIDTH=\"10\" HEIGHT=\"1\" ALT=\"\"></TD>" << endl;
  *stream << "<TD  VALIGN=center ALIGN=left class=\"cell1\"><P class=\"c1s\">" << endl;
  *stream << title.Data() << "<br>" << endl;
  
  if ( DoPicturesPS() )
    *stream << "<a href=\"" << ps.Data() << "\">(PS)</a>";
  if ( DoPicturesEPS() )
    *stream << "<a href=\"" << eps.Data() << "\">(EPS)</a>";
  if ( DoPicturesGIF() ) 
    *stream << "<a href=\"" << gif.Data() << "\">(GIF)</a>";
  if ( DoPicturesJPG() ) 
    *stream << "<a href=\"" << jpg.Data() << "\">(JPG)</a>";
  *stream << "<br>" << endl;
  
  if ( DoPicturesPS() )
    *stream << "<a href=\"" << logps.Data() << "\">(log PS)</a>";
  if ( DoPicturesEPS() )
    *stream << "<a href=\"" << logeps.Data() << "\">(log EPS)</a>";
  if ( DoPicturesGIF() ) 
    *stream << "<a href=\"" << loggif.Data() << "\">(log GIF)</a>";
  if ( DoPicturesJPG() ) 
    *stream << "<a href=\"" << logjpg.Data() << "\">(log JPG)</a>";
  *stream << "<br>" << endl;
  
  *stream << "</TD>" << endl;
  *stream << "</TR>" << endl;
  
  return kTRUE;
}

//_____________________________________________________________

Bool_t GPictureMaker::GenHTMLPics(TCanvas* canvas, TString name, TString directory, TString title, TString option) {
  //
  // generate HTML pics and make html entry, name without extension
  if ( gDebug ) cout << endl << "GPictureMaker::GenHTMLPics() called" << endl << endl;

  TString dir = directory;
  if ( dir.BeginsWith(".") ) {
    dir = "";
  } else if ( !dir.EndsWith("/") && ( dir.Length() != 0 ) ) {
    dir.Append("/");
  }

  option.ToUpper();

  TString psname;
  TString psdir; 
  TString epsname;
  TString epsdir;
  TString gifname;
  TString gifdir;
  TString command;
  TString jpgname;
  TString jpgdir;
  TString thumbgifname;
  TString thumbgifdir;
  TString logpsname;
  TString logpsdir;
  TString logepsname;
  TString logepsdir;
  TString loggifname;
  TString loggifdir;
  TString logjpgname;
  TString logjpgdir;

  // make ps pic
  if ( (!option.Contains("NOHTML") || option.Contains("PUREPS")) && DoPicturesPS()) {
    psname = name;
    psname.Append(".ps");
    psdir = dir;
    psdir.Append(psname);
    if ( !option.Contains("NONICE") ) 
      gInclude->NicePlot(canvas);
    canvas->SaveAs(psdir.Data());
  }
  
  if ( (!option.Contains("NOHTML") || option.Contains("EPS") ) && DoPicturesEPS() ) {
    // make eps pic
    epsname = name;
    epsname.Append(".eps");
    epsdir = dir;
    epsdir.Append(epsname);
    if ( !option.Contains("NONICE") ) 
      gInclude->NicePlot(canvas);
    canvas->SaveAs(epsdir.Data());
  }

  if ( (!option.Contains("NOHTML") || option.Contains("GIF"))  && DoPicturesGIF() ) {
    // make gif pic
    if ( !option.Contains("NOCONVERT") ) {
      gifname = name;
      gifname.Append(".gif");
      gifdir = dir;
      gifdir.Append(gifname);
      command = fConvert;
      command.Append(" -density 144 ");
      command.Append(epsdir.Data());
      command.Append(" ");
      command.Append(gifdir.Data());
      gSystem->Exec(command.Data());
    } else {
      gifname = name;
      gifname.Append(".gif");
      gifdir = dir;
      gifdir.Append(gifname);
      if ( !option.Contains("NONICE") ) 
	gInclude->NicePlot(canvas);
      canvas->SaveAs(gifdir.Data());
    }
  }
  
  if ( (!option.Contains("NOHTML") || option.Contains("JPG") ) && DoPicturesJPG() ) {
    // make jpg pic
    jpgname = name;
    jpgname.Append(".jpg");
    jpgdir = dir;
    jpgdir.Append(jpgname);
    command = fConvert;
    command.Append(" -density 144 ");
    command.Append(epsdir.Data());
    command.Append(" ");
    command.Append(jpgdir.Data());
    gSystem->Exec(command.Data());
  }

  if ( !option.Contains("NOHTML") ) {
    // make thumb gif picture 
    thumbgifname = name;
    thumbgifname.Append("_thumb.gif");
    thumbgifdir = dir;
    thumbgifdir.Append(thumbgifname);
    command = fConvert;
    command.Append(" -size 240x240 ");
    command.Append(gifdir.Data());
    command.Append(" -scale 240x240 ");
    command.Append(thumbgifdir.Data());
    gSystem->Exec(command.Data());
    
    canvas->SetLogy(1);
    canvas->Update();
    
    if (DoPicturesPS()) {
      logpsname = name;
      logpsname.Append("_log.ps");
      logpsdir = dir;
      logpsdir.Append(logpsname);
      if ( !option.Contains("NONICE") ) 
	gInclude->NicePlot(canvas);
      canvas->SaveAs(logpsdir.Data());
    }
    
    if ( DoPicturesEPS() ) {
      logepsname = name;
      logepsname.Append("_log.eps");
      logepsdir = dir;
      logepsdir.Append(logepsname);
      if ( !option.Contains("NONICE") ) 
	gInclude->NicePlot(canvas);
      canvas->SaveAs(logepsdir.Data());
    }
    
    if ( DoPicturesGIF() ) {
      loggifname = name;
      loggifname.Append("_log.gif");
      loggifdir = dir;
      loggifdir.Append(loggifname);
      command = fConvert;
      command.Append(" -density 144 ");
      command.Append(logepsdir.Data());
      command.Append(" ");
      command.Append(loggifdir.Data());
      gSystem->Exec(command.Data());
    }
    
    if ( DoPicturesJPG() ) {
      logjpgname = name;
      logjpgname.Append("_log.jpg");
      logjpgdir = dir;
      logjpgdir.Append(logjpgname);
      command = fConvert;
      command.Append(" -density 144 ");
      command.Append(logepsdir.Data());
      command.Append(" ");
      command.Append(logjpgdir.Data());
      gSystem->Exec(command.Data());
    }
      
  // fill html
    this->HTMLStream(thumbgifname,
		     title,
		     psname,
		     epsname,
		     gifname,
		     jpgname,
		     logpsname,
		     logepsname,
		     loggifname,
		     logjpgname,
		     option);

    // reset canvas to linear scale
    canvas->SetLogy(0);

  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GPictureMaker::GenHTMLPics(ofstream *stream, TCanvas* canvas, TString name, TString directory, TString title, TString option) {
  //
  // generate HTML pics and make html entry, name without extension
  if ( gDebug ) cout << endl << "GPictureMaker::GenHTMLPics() called" << endl << endl;

  TString dir = directory;
  if ( dir.BeginsWith(".") ) {
    dir = "";
  } else if ( !dir.EndsWith("/") && ( dir.Length() != 0 ) ) {
    dir.Append("/");
  }

  option.ToUpper();

  TString psname;
  TString psdir; 
  TString epsname;
  TString epsdir;
  TString gifname;
  TString gifdir;
  TString command;
  TString jpgname;
  TString jpgdir;
  TString thumbgifname;
  TString thumbgifdir;
  TString logpsname;
  TString logpsdir;
  TString logepsname;
  TString logepsdir;
  TString loggifname;
  TString loggifdir;
  TString logjpgname;
  TString logjpgdir;

  // make ps pic
  if ( (!option.Contains("NOHTML") || option.Contains("PUREPS")) && DoPicturesPS() ) {
    psname = name;
    psname.Append(".ps");
    psdir = dir;
    psdir.Append(psname);
    if ( !option.Contains("NONICE") ) 
      gInclude->NicePlot(canvas);
    canvas->SaveAs(psdir.Data());
  }

  if ( (!option.Contains("NOHTML") || option.Contains("EPS")) && DoPicturesEPS() ) {
    // make eps pic
    epsname = name;
    epsname.Append(".eps");
    epsdir = dir;
    epsdir.Append(epsname);
    if ( !option.Contains("NONICE") ) 
      gInclude->NicePlot(canvas);
    canvas->SaveAs(epsdir.Data());
  }

  if ( (!option.Contains("NOHTML") || option.Contains("GIF")) && DoPicturesGIF() ) {
    // make gif pic
    if ( !option.Contains("NOCONVERT") ) {
      gifname = name;
      gifname.Append(".gif");
      gifdir = dir;
      gifdir.Append(gifname);
      command = fConvert;
      command.Append(" -density 144 ");
      command.Append(epsdir.Data());
      command.Append(" ");
      command.Append(gifdir.Data());
      gSystem->Exec(command.Data());
    } else {
      gifname = name;
      gifname.Append(".gif");
      gifdir = dir;
      gifdir.Append(gifname);
      if ( !option.Contains("NONICE") ) 
	gInclude->NicePlot(canvas);
      canvas->SaveAs(gifdir.Data());
    }
  }

  if ( (!option.Contains("NOHTML") || option.Contains("JPG")) && DoPicturesJPG() ) {
    // make jpg pic
    jpgname = name;
    jpgname.Append(".jpg");
    jpgdir = dir;
    jpgdir.Append(jpgname);
    command = fConvert;
    command.Append(" -density 144 ");
    command.Append(epsdir.Data());
    command.Append(" ");
    command.Append(jpgdir.Data());
    gSystem->Exec(command.Data());
  }

  if ( !option.Contains("NOHTML") ) {
    // make thumb gif picture 
    thumbgifname = name;
    thumbgifname.Append("_thumb.gif");
    thumbgifdir = dir;
    thumbgifdir.Append(thumbgifname);
    command = fConvert;
    command.Append(" -size 240x240 ");
    command.Append(gifdir.Data());
    command.Append(" -scale 240x240 ");
    command.Append(thumbgifdir.Data());
    gSystem->Exec(command.Data());

    // make log plots
    canvas->SetLogy(1);
    canvas->Update();

    if (DoPicturesPS()) {
      logpsname = name;
      logpsname.Append("_log.ps");
      logpsdir = dir;
      logpsdir.Append(logpsname);
      if ( !option.Contains("NONICE") ) 
	gInclude->NicePlot(canvas);
      canvas->SaveAs(logpsdir.Data());
    }

    if ( DoPicturesEPS() ) {
      logepsname = name;
      logepsname.Append("_log.eps");
      logepsdir = dir;
      logepsdir.Append(logepsname);
      if ( !option.Contains("NONICE") ) 
	gInclude->NicePlot(canvas);
      canvas->SaveAs(logepsdir.Data());
    }
    
    if ( DoPicturesGIF() ) {
      loggifname = name;
      loggifname.Append("_log.gif");
      loggifdir = dir;
      loggifdir.Append(loggifname);
      command = fConvert;
      command.Append(" -density 144 ");
      command.Append(logepsdir.Data());
      command.Append(" ");
      command.Append(loggifdir.Data());
      gSystem->Exec(command.Data());
    }
    
    if ( DoPicturesJPG() ) {
      logjpgname = name;
      logjpgname.Append("_log.jpg");
      logjpgdir = dir;
      logjpgdir.Append(logjpgname);
      command = fConvert;
      command.Append(" -density 144 ");
      command.Append(logepsdir.Data());
      command.Append(" ");
      command.Append(logjpgdir.Data());
      gSystem->Exec(command.Data());
    }
    
    // fill html
    HTMLStream(stream, thumbgifname,
		     title,
		     psname,
		     epsname,
		     gifname,
		     jpgname,
		     logpsname,
		     logepsname,
		     loggifname,
		     logjpgname,
		     option);

    // reset canvas to linear scale
    canvas->SetLogy(0);

  }

  return kTRUE;
}

//_____________________________________________________________

Bool_t GPictureMaker::MakeTwoFileComparison(TFile *file1, TFile *file2, TString directory, TString option) {
  //
  // compare two histos.root cominig directly from analysis.exe
  if ( gDebug ) cout << endl << "GPictureMaker::MakeTwoFileComparison() called" << endl << endl;

  Bool_t has_entry = kFALSE;

  TList *histograms = new TList();
  histograms->Add(new TObjString("Vertex_Control/X_uncut"));
  histograms->Add(new TObjString("Vertex_Control/Y_uncut"));
  histograms->Add(new TObjString("Vertex_Control/Z_uncut"));
  histograms->Add(new TObjString("Sinistra_Control/EE_uncut"));
  histograms->Add(new TObjString("Sinistra_Control/YEL_uncut"));
  histograms->Add(new TObjString("Sinistra_Control/SiNCand_uncut"));
  histograms->Add(new TObjString("Sinistra/YEL"));
  histograms->Add(new TObjString("Sinistra/Q2"));
  histograms->Add(new TObjString("Sinistra/Q2log"));
  histograms->Add(new TObjString("Sinistra/Xlog"));
  histograms->Add(new TObjString("Sinistra/Q2x"));
  histograms->Add(new TObjString("Sinistra/ThetaE"));
  histograms->Add(new TObjString("Sinistra/XY"));
  histograms->Add(new TObjString("Cal_Control/E_uncut"));
  histograms->Add(new TObjString("Cal_Control/E_zufo_uncut"));
  histograms->Add(new TObjString("Cal_Control/Empz_uncut"));
  histograms->Add(new TObjString("Cal_Control/Empz_zufo_uncut"));
  histograms->Add(new TObjString("Cal_Control/px_uncut"));
  histograms->Add(new TObjString("Cal_Control/px_zufo_uncut"));
  histograms->Add(new TObjString("Cal_Control/py_uncut"));
  histograms->Add(new TObjString("Cal_Control/py_zufo_uncut"));
  histograms->Add(new TObjString("Cal_Control/pz_uncut"));
  histograms->Add(new TObjString("Cal_Control/pz_zufo_uncut"));
  histograms->Add(new TObjString("Jet/n_uncut"));
  histograms->Add(new TObjString("Jet/E_uncut"));
  histograms->Add(new TObjString("Jet/Et_uncut"));
  histograms->Add(new TObjString("Jet/Eta_uncut"));
  histograms->Add(new TObjString("Jet/Mass_uncut"));
  histograms->Add(new TObjString("Jet/Phi_uncut"));
  histograms->Add(new TObjString("Jet/Pt_uncut"));
  histograms->Add(new TObjString("Jet/XGamma_uncut"));
  histograms->Add(new TObjString("Jet/XGamma_zufo_uncut"));
  histograms->Add(new TObjString("Zufo/ZUFOn_uncut"));
  histograms->Add(new TObjString("Zufo/ZUFOE_uncut"));
  histograms->Add(new TObjString("Zufo/ZUFOp_uncut"));
  histograms->Add(new TObjString("Zufo/ZUFOpt_uncut"));
  histograms->Add(new TObjString("Zufo/ZUFOpx_uncut"));
  histograms->Add(new TObjString("Zufo/ZUFOpy_uncut"));
  histograms->Add(new TObjString("Zufo/ZUFOpz_uncut"));
  histograms->Add(new TObjString("Tracks/N_uncut"));
  histograms->Add(new TObjString("Muons/Charge_uncut"));
  histograms->Add(new TObjString("Muons/Eta_uncut"));
  histograms->Add(new TObjString("Muons/MuonFinder_uncut"));
  histograms->Add(new TObjString("Muons/NMU_uncut"));
  histograms->Add(new TObjString("Muons/P_uncut"));
  histograms->Add(new TObjString("Muons/Phi_uncut"));
  histograms->Add(new TObjString("Muons/Pt_uncut"));
  histograms->Add(new TObjString("Muons/Theta_uncut"));
  histograms->Add(new TObjString("Muons/Px_uncut"));
  histograms->Add(new TObjString("Muons/Py_uncut"));
  histograms->Add(new TObjString("Muons/Pz_uncut"));
  histograms->Add(new TObjString("Muons_Control/Quality_uncut"));
  histograms->Add(new TObjString("MJMatch/PtRel"));
  histograms->Add(new TObjString("Muons/Pt"));
  histograms->Add(new TObjString("Muons/PtSpecial"));
  histograms->Add(new TObjString("Muons/PtSpecial_uncut"));
  histograms->Add(new TObjString("Muons/PtSpecialForward"));
  histograms->Add(new TObjString("Muons/PtSpecialForward_uncut"));
  histograms->Add(new TObjString("Muons/PtSpecialBarrel"));
  histograms->Add(new TObjString("Muons/PtSpecialBarrel_uncut"));
  histograms->Add(new TObjString("Muons/PtSpecialRear"));
  histograms->Add(new TObjString("Muons/PtSpecialRear_uncut"));
  histograms->Add(new TObjString("Muons/Eta"));
  histograms->Add(new TObjString("Muons/PtChosen"));
  histograms->Add(new TObjString("Muons/EtaChosen"));
  histograms->Add(new TObjString("Muons/EtaChosenLarge"));
  histograms->Add(new TObjString("Jet/Pt_Matched"));
  histograms->Add(new TObjString("Jet/Pt_Unmatched"));
  histograms->Add(new TObjString("Jet/Pt_A"));
  histograms->Add(new TObjString("Jet/Pt_B"));
  histograms->Add(new TObjString("Jet/Et_Matched"));
  histograms->Add(new TObjString("Jet/Et_Unmatched"));
  histograms->Add(new TObjString("Jet/Et_A"));
  histograms->Add(new TObjString("Jet/Et_B"));
  histograms->Add(new TObjString("Jet/Eta_Matched"));
  histograms->Add(new TObjString("Jet/Eta_Unmatched"));
  histograms->Add(new TObjString("Jet/Eta_A"));
  histograms->Add(new TObjString("Jet/Eta_B"));
  histograms->Add(new TObjString("Jet/Eta_Matched_Large"));
  histograms->Add(new TObjString("Jet/Eta_Unmatched_Large"));
  histograms->Add(new TObjString("Jet/Eta_A_Large"));
  histograms->Add(new TObjString("Jet/Eta_B_Large"));
  histograms->Add(new TObjString("Jet/Mass_Matched"));
  histograms->Add(new TObjString("Jet/Mass_Unmatched"));
  histograms->Add(new TObjString("Jet/Mass_A"));
  histograms->Add(new TObjString("Jet/Mass_B"));
  histograms->Add(new TObjString("Jet/XGamma"));
  histograms->Add(new TObjString("Jet/XGamma_zufo"));

  // start html file
  TString tempdir = directory;
  TString filename = "";
  if ( tempdir.BeginsWith(".") ) {
    tempdir = "";
    filename = tempdir.Data();
    filename.Append("gallery.html");
  } else {
    if ( tempdir.EndsWith("/") && ( tempdir.Length() != 0 ) )
      tempdir.Remove(tempdir.Length()-1,1);
    filename = tempdir.Data();
    filename.Append("/gallery.html");
  }
  ofstream *top = new ofstream(filename);
  TString title = "Comparison between ";
  title.Append(file1->GetName());
  title.Append(" and ");
  title.Append(file2->GetName());
  HTMLStart(top,title,"comparison",option);

  TIter nexthistogram(histograms);
  while ( TObjString *histogram = (TObjString*)nexthistogram() ) {
    has_entry = MakeTwoFilesComparisonPlot(file1,file2,top,histogram->GetString(),directory,option);
  }

  HTMLEnd(top,"../gallery.html",fTime,option);
  delete top;  // add leading Histograms directory to input histograms
  
  histograms->Delete();
  delete histograms;

  return has_entry;
}

//_____________________________________________________________

Bool_t GPictureMaker::MakeTwoFilesComparisonPlot(TFile *file1, TFile *file2, ofstream *stream, TString histogramname, TString directory, TString option) {
  //
  // make mc comparison plot
  if ( gDebug ) cout << endl << "GPictureMaker::MakeComparisonPlot called" << endl << endl;

  option.ToUpper();

  TString completehistogramname = "Histograms/";
  completehistogramname.Append(histogramname);

  TH1D *histo1 = (TH1D*)file1->Get(completehistogramname);
  if ( histo1 == 0) {
    cout << "GPictureMaker::MakeTowFilesComparisonPlot() problem in getting histogram: " << completehistogramname << " from file " << file1->GetName() << endl;
    return kFALSE;
  }
  
  TH1D *histo2 = (TH1D*)file2->Get(completehistogramname);
  if ( histo2 == 0) {
    cout << "GPictureMaker::MakeTowFilesComparisonPlot() problem in getting histogram: " << completehistogramname << " from file " << file1->GetName() << endl;
    return kFALSE;
  }
  
  cout << "GPictureMaker::MakeTwoFilesComparisonPlot for " << completehistogramname << " between file " << file1->GetName() << " and " << file2->GetName() << endl;

  // determine histo with maximum
  Double_t max = histo1->GetMaximum();
  if ( max < histo2->GetMaximum() )
    max = histo2->GetMaximum();

  // set batch to true
  Bool_t batch = gROOT->IsBatch();
  if ( !batch )
    gROOT->SetBatch(kTRUE);

  // delete old canvas
  if ( fCanvas ) {
    delete fCanvas;
    fCanvas = 0;
  }

  // canvas
  if ( !fCanvas ) {
    fCanvas = new TCanvas("canvas","canvas",640,480);
  } 

  // set error bars in x off
  gStyle->SetErrorX(0);

  fCanvas->cd();
  fCanvas->Clear();
  fCanvas->SetLogy(0);

  gStyle->SetOptStat(1110);

  TString histoname = "two_files_comparison_";
  histoname.Append(histogramname);
  histoname.ReplaceAll("/","_");
  histoname.ToLower();

  histo1->SetStats(kFALSE);
  histo1->SetLineStyle(1);
  histo1->SetLineWidth((Short_t)3);
  histo1->SetLineColor(2);
  histo1->SetMarkerColor(2);
  histo1->SetMarkerStyle(8);
  histo1->SetMarkerSize(1.3);
  histo1->SetTitleOffset(1.2);
  histo1->SetMaximum(1.2*max);

  histo1->Draw("HIST");

//   fCanvas->Update();
//   TPaveStats *stats = (TPaveStats*)(histo1->GetListOfFunctions()->FindObject("stats"));

  TString label1 = file1->GetName();
  label1.Append(" entries: ");
  label1 += histo1->GetEntries();
  TString label2 = file2->GetName();
  label2.Append(" entries: ");
  label2 += histo2->GetEntries();
  TPaveText *text = new TPaveText(0.68,0.88,0.98,0.995,"br,NDC");
  text->AddText(label1);
  text->AddText(label2);
  text->SetFillColor(10);
  text->SetBorderSize(1);
  text->Draw("SAME");

  // title pave text
  fCanvas->Update();
  TPaveText *titlepave = (TPaveText*)fCanvas->FindObject("title");
  if ( titlepave->GetX2NDC() > 0.67 )
    titlepave->SetX2NDC(0.67);
  
  histo2->SetStats(kFALSE);
  histo2->SetLineStyle(1);
  histo2->SetLineWidth((Short_t)3);
  histo2->SetLineColor(8);
  histo2->Draw("HIST,SAME");

  TLegend *leg = 0;
  leg = new TLegend(0.68,0.75,0.98,0.87);
  leg->SetTextSize(0.035); 
  leg->SetFillColor(10);
  leg->SetBorderSize(1); // no frame, no shadow
  leg->AddEntry(histo1,file1->GetName(), "L" );
  leg->AddEntry(histo2,file2->GetName(), "L" );
  leg->Draw("SAME");
  
  gInclude->NicePlot(fCanvas);
  gInclude->NicePlot(fCanvas);

  TString histotitle = "Comparison of ";
  histotitle.Append(histogramname);
  GenHTMLPics(stream,fCanvas,histoname,directory,histotitle,option);
  
  // set error bars in x to default
  gStyle->SetErrorX(0.5);

  // delete old canvas
  if ( fCanvas ) {
    delete fCanvas;
    fCanvas = 0;
  }

  // restore batch level
  if ( !batch )
    gROOT->SetBatch(kFALSE);

  return kTRUE;
}

//_____________________________________________________________

Bool_t GPictureMaker::MakeSpecialComplete(TFile *file, TString directory, TString option) {
  //
  // make special pictures
  if ( gDebug ) cout << endl << "GPictureMaker::MakeSpecialComplete called" << endl << endl;

  TList *entries = new TList();
  Bool_t has_entry = kFALSE;

  TString temptopdir = directory;

  if ( temptopdir.BeginsWith(".") ) {
    temptopdir = "";
  } else if ( !temptopdir.EndsWith("/") && ( temptopdir.Length() != 0 ) ) {
    temptopdir.Append("/");
  }

  // make ptrel plots
  if ( DoPicturesPtRel() ) {
    TString tempdir = temptopdir;
    tempdir.Append("ptrel");

    if ( MakeSpecialCompletePtRel(file,tempdir,option) ) {
      entries->Add(new TObjString("ptrel"));
      has_entry = kTRUE;
    }
  }

  // make impact parameter plots
  if ( DoPicturesImpact() ) {
    TString tempdir = temptopdir;
    tempdir.Append("impact");

    if ( MakeSpecialCompleteImpact(file,tempdir,option) ) {
      entries->Add(new TObjString("impact"));
      has_entry = kTRUE;
    }
  }

  // make data mc comparison plots using ptrel fit 1
  if ( DoPicturesPtRel_1().Length() != 0 ) {
    TString ptrelhistogramname = DoPicturesPtRel_1();
    TString tempdir = temptopdir;
    tempdir.Append("comparison_ptrel_1");

    TString tempoption = option;
    tempoption.Append(",PTREL");

    if ( MakeSpecialCompleteComparison(file,tempdir,ptrelhistogramname,tempoption) ) {
      entries->Add(new TObjString("comparison_ptrel_1"));
      has_entry = kTRUE;
    }
  }

  // make data mc comparison plots using ptrel fit 2
  if ( DoPicturesPtRel_2().Length() != 0 ) {
    TString ptrelhistogramname = DoPicturesPtRel_2();
    TString tempdir = temptopdir;
    tempdir.Append("comparison_ptrel_2");

    TString tempoption = option;
    tempoption.Append(",PTREL");

    if ( MakeSpecialCompleteComparison(file,tempdir,ptrelhistogramname,tempoption) ) {
      entries->Add(new TObjString("comparison_ptrel_2"));
      has_entry = kTRUE;
    }
  }

  // make data mc comparison plots using lumi weighting
  if ( DoPicturesLumi() ) {
    TString ptrelhistogramname = "";
    TString tempdir = temptopdir;
    tempdir.Append("comparison_lumi");

    TString tempoption = option;
    tempoption.Append(",LUMI");

    if (  MakeSpecialCompleteComparison(file,tempdir,ptrelhistogramname,tempoption) ) {
      entries->Add(new TObjString("comparison_lumi"));
      has_entry = kTRUE;
    }
  }
  
  // make special 1D histograms
  if ( DoPictures1D() ) {
    TString tempdir = temptopdir;
    tempdir.Append("1D");
    
    if (  MakeSpecialComplete1D(file,tempdir,option) ) {
      entries->Add(new TObjString("1D"));
      has_entry = kTRUE;
    }
  }
  
  // make special 2D histograms
  if ( DoPictures1D() ) {
    TString tempdir = temptopdir;
    tempdir.Append("2D");

    if (  MakeSpecialComplete2D(file,tempdir,option) ) {
      entries->Add(new TObjString("2D"));
      has_entry = kTRUE;
    }
  }
  
  // make efficiency histograms
  if ( DoPicturesEff() ) {
    TString tempdir = temptopdir;
    tempdir.Append("efficiencies");

    if (  MakeSpecialCompleteEfficiency(file,tempdir,option) ) {
      entries->Add(new TObjString("efficiencies"));
      has_entry = kTRUE;
    }
  
    // make efficiency histograms
    tempdir = temptopdir;
    tempdir.Append("corrections");
    
    if (  MakeSpecialCompleteCorrection(file,tempdir,option) ) {
      entries->Add(new TObjString("corrections"));
      has_entry = kTRUE;
    }
  }
  
  if ( has_entry ) {
    
    TString tempoption = option;
    tempoption.Append(",TOP");

    // start top html
    TString tempdir = directory;
    if ( tempdir.BeginsWith(".") ) {
      tempdir = "";
    } else if ( tempdir.EndsWith("/") && ( tempdir.Length() != 0 ) )
      tempdir.Remove(tempdir.Length()-1,1);
    // check whether tempdir exists, else generate
    gSystem->mkdir(tempdir.Data(),kTRUE);
    TString name = tempdir.Data();
    name.Append("/gallery.html");
    ofstream *top = new ofstream(name.Data());
    TString title = "Special complete gallery";
    TString filename = "special_gallery_complete";
    HTMLStart(top,title,filename,tempoption);

    TIter nextentry(entries);
    while (TObjString *entry = (TObjString*)nextentry() ) {
      TString link = entry->GetString();
      link.Append("/gallery.html");
      TString title = "";
      if ( link.Contains("comparison") ) {
	if ( link.Contains("ptrel_2") ) {
	  title.Append("Data-MC Comparison Plots using PtRel Fit: ");
	  title.Append(DoPicturesPtRel_2());
	} else if ( link.Contains("ptrel_1") ) {
	  title.Append("Data-MC Comparison Plots using PtRel Fit: ");
	  title.Append(DoPicturesPtRel_1());
	} else if ( link.Contains("lumi") ) {
	  title.Append("Data-MC Comparison Plots using Lumi Weighting");
	}
      } else {
	if ( link.Contains("ptrel") ) {
	  title.Append("PtRel Plots");
	} else if ( link.Contains("impact") ) {
	  title.Append("Impact Parameter Plots");
	} else if ( link.Contains("1D") ) {
	  title.Append("Special one dimensionale plots");
	} else if ( link.Contains("2D") ) {
	  title.Append("Special two dimensionale plots");
	} else if ( link.Contains("efficiencies") ) {
	  title.Append("Muon efficiency plots");
	} else if ( link.Contains("corrections") ) {
	  title.Append("Muon efficiency correction factor plots");
	}	
      }
	
      HTMLStreamTop(top,link,title,tempoption);
    }

    HTMLEnd(top,"../gallery.html",fTime,tempoption);
    delete top;  // add leading Histograms directory to input histograms
  
  }

  entries->Delete();
  delete entries;

  return has_entry;
}

//_____________________________________________________________

Bool_t GPictureMaker::MakeSpecialCompletePtRel(TFile *file, TString directory, TString option) {
  //
  // make special ptrel pictures
  if ( gDebug ) cout << endl << "GPictureMaker::MakeSpecialCompletePtRel() called" << endl << endl;

  TList *entries = new TList();
  Bool_t has_entry = kFALSE;

  // check whether dir exists, else generate
  gSystem->mkdir(directory,kTRUE);

  // start html file
  TString tempdir = directory;
  if ( tempdir.BeginsWith(".") ) {
    tempdir = "";
  } else if ( tempdir.EndsWith("/") && ( tempdir.Length() != 0 ) )
    tempdir.Remove(tempdir.Length()-1,1);
  // check whether tempdir exists, else generate
  gSystem->mkdir(tempdir.Data(),kTRUE);
  TString filename = tempdir.Data();
  filename.Append("/gallery.html");
  ofstream *top = new ofstream(filename);
  HTMLStart(top,"PtRel Plots","ptrel_plots",option);

  TIter nextname(fPlotsPtRel);
  while ( TObjString *name = (TObjString*)nextname() ) {
    Bool_t temp_has_entry = kFALSE;
    temp_has_entry = MakePtRelPlotComplete(file,top,name->GetString(),directory,option);
    if ( DoPicturesPtRelMCOnly() ) {
      TString tempoption = option;
      tempoption.Append(",MCONLY");
      temp_has_entry = MakePtRelPlotComplete(file,top,name->GetString(),directory,tempoption);
    }
    if ( !has_entry)
      has_entry = temp_has_entry;
  }

  HTMLEnd(top,"../gallery.html",fTime,option);
  delete top;  // add leading Histograms directory to input histograms
  
  entries->Delete();
  delete entries;

  return has_entry;
}

//_____________________________________________________________

Bool_t GPictureMaker::MakeSpecialCompleteImpact(TFile *file, TString directory, TString option) {
  //
  // make special impact pictures
  if ( gDebug ) cout << endl << "GPictureMaker::MakeSpecialCompleteImpact() called" << endl << endl;

  TList *entries = new TList();
  Bool_t has_entry = kFALSE;

  // check whether dir exists, else generate
  gSystem->mkdir(directory,kTRUE);

  // start html file
  TString tempdir = directory;
  if ( tempdir.BeginsWith(".") ) {
    tempdir = "";
  } else if ( tempdir.EndsWith("/") && ( tempdir.Length() != 0 ) )
    tempdir.Remove(tempdir.Length()-1,1);
  // check whether tempdir exists, else generate
  gSystem->mkdir(tempdir.Data(),kTRUE);
  TString filename = tempdir.Data();
  filename.Append("/gallery.html");
  ofstream *top = new ofstream(filename);
  HTMLStart(top,"Impact Parameter Plots","impact_plots",option);

  TIter nextname(fPlotsImpact);
  while ( TObjString *name = (TObjString*)nextname() ) {
    Bool_t temp_has_entry = kFALSE;
    temp_has_entry = MakeImpactPlotComplete(file,top,name->GetString(),directory,option);
    if ( DoPicturesPtRelMCOnly() ) {
      TString tempoption = option;
      tempoption.Append(",MCONLY");
      temp_has_entry = MakeImpactPlotComplete(file,top,name->GetString(),directory,tempoption);
    }
    if ( !has_entry)
      has_entry = temp_has_entry;
  }

  HTMLEnd(top,"../gallery.html",fTime,option);
  delete top;  // add leading Histograms directory to input histograms
  
  entries->Delete();
  delete entries;

  return has_entry;
}

//_____________________________________________________________

Bool_t GPictureMaker::MakeSpecialComplete1D(TFile *file, TString directory, TString option) {
  //
  // make special one dimensional pictures
  if ( gDebug ) cout << endl << "GPictureMaker::MakeSpecialPeriod1D() called" << endl << endl;

  Bool_t has_entry = kFALSE;

  GHistogrammer grammer;
  TList *types = grammer.GetTypes();

  // check whether dir exists, else generate
  gSystem->mkdir(directory,kTRUE);

  // start html file
  TString tempdir = directory;
  if ( tempdir.BeginsWith(".") ) {
    tempdir = "";
  } else if ( tempdir.EndsWith("/") && ( tempdir.Length() != 0 ) )
    tempdir.Remove(tempdir.Length()-1,1);
  // check whether tempdir exists, else generate
  gSystem->mkdir(tempdir.Data(),kTRUE);
  TString filename = tempdir.Data();
  filename.Append("/gallery.html");
  ofstream *top = new ofstream(filename);
  HTMLStart(top,"Special one dimensional plots","1D_plots",option);

  TIter nextdata(fPlots1D);
  while ( TObjString *datahist = (TObjString*)nextdata() ) {
    Bool_t temp_has_entry = kFALSE;
    TString tempoption = option;
    tempoption.Append(",DATA");
    temp_has_entry = Make1DPlotComplete(file,top,"","",datahist->GetString(),directory,tempoption);
    if ( !has_entry)
      has_entry = temp_has_entry;
  }

  TIter nextdatazoomed(fPlots1DZoomed);
  while ( TObjString *datahistzoomed = (TObjString*)nextdatazoomed() ) {
    Bool_t temp_has_entry = kFALSE;
    TString tempoption = option;
    tempoption.Append(",DATA");
    temp_has_entry = Make1DPlotComplete(file,top,"","",datahistzoomed->GetString(),directory,tempoption,0.33);
    if ( !has_entry)
      has_entry = temp_has_entry;
  }

  TIter nextmc(fPlots1DMC);
  while ( TObjString *mchist = (TObjString*)nextmc() ) {
    Bool_t temp_has_entry = kFALSE;
    TString tempoption = option;
    tempoption.Append(",MC");
    TIter nexttype(types);
    while ( TObjString *type = (TObjString*)nexttype() ) {
      temp_has_entry = Make1DPlotComplete(file,top,type->GetString(),"",mchist->GetString(),directory,tempoption);
      TIter nexttype2(nexttype);
      while ( TObjString *type2 = (TObjString*)nexttype2() ) {
	TString merge = type->GetString();
	merge.Append("_");
	merge.Append(type2->GetString());
	temp_has_entry = Make1DPlotComplete(file,top,"",merge,mchist->GetString(),directory,tempoption);
	TIter nexttype3(nexttype2);
	while ( TObjString *type3 = (TObjString*)nexttype3() ) {
	  TString merge = type->GetString();
	  merge.Append("_");
	  merge.Append(type2->GetString());
	  merge.Append("_");
	  merge.Append(type3->GetString());
	  temp_has_entry = Make1DPlotComplete(file,top,"",merge,mchist->GetString(),directory,tempoption);
	}
      }
    }
    if ( !has_entry)
      has_entry = temp_has_entry;
  }

  TIter nextmczoomed(fPlots1DMCZoomed);
  while ( TObjString *mchistzoomed = (TObjString*)nextmczoomed() ) {
    Bool_t temp_has_entry = kFALSE;
    TString tempoption = option;
    tempoption.Append(",MC");
    TIter nexttype(types);
    while ( TObjString *type = (TObjString*)nexttype() ) {
      temp_has_entry = Make1DPlotComplete(file,top,type->GetString(),"",mchistzoomed->GetString(),directory,tempoption,0.33);
      TIter nexttype2(nexttype);
      while ( TObjString *type2 = (TObjString*)nexttype2() ) {
	TString merge = type->GetString();
	merge.Append("_");
	merge.Append(type2->GetString());
	temp_has_entry = Make1DPlotComplete(file,top,"",merge,mchistzoomed->GetString(),directory,tempoption,0.33);
	TIter nexttype3(nexttype2);
	while ( TObjString *type3 = (TObjString*)nexttype3() ) {
	  TString merge = type->GetString();
	  merge.Append("_");
	  merge.Append(type2->GetString());
	  merge.Append("_");
	  merge.Append(type3->GetString());
	  temp_has_entry = Make1DPlotComplete(file,top,"",merge,mchistzoomed->GetString(),directory,tempoption,0.33);
	}
      }
    }
    if ( !has_entry)
      has_entry = temp_has_entry;
  }

  HTMLEnd(top,"../gallery.html",fTime,option);
  delete top;  // add leading Histograms directory to input histograms
  
  return has_entry;
}

//_____________________________________________________________

Bool_t GPictureMaker::MakeSpecialComplete2D(TFile *file, TString directory, TString option) {
  //
  // make special two dimensional pictures
  if ( gDebug ) cout << endl << "GPictureMaker::MakeSpecialComplete2D() called" << endl << endl;

  Bool_t has_entry = kFALSE;

  TList *drawoptions = new TList();
  drawoptions->Add(new TObjString("COLZ"));
  drawoptions->Add(new TObjString("BOX"));
  drawoptions->Add(new TObjString("CONTZ"));
  drawoptions->Add(new TObjString("SCAT"));

  GHistogrammer grammer;
  TList *types = grammer.GetTypes();

  // check whether dir exists, else generate
  gSystem->mkdir(directory,kTRUE);

  // start html file
  TString tempdir = directory;
  if ( tempdir.BeginsWith(".") ) {
    tempdir = "";
  } else if ( tempdir.EndsWith("/") && ( tempdir.Length() != 0 ) )
    tempdir.Remove(tempdir.Length()-1,1);
  // check whether tempdir exists, else generate
  gSystem->mkdir(tempdir.Data(),kTRUE);
  TString filename = tempdir.Data();
  filename.Append("/gallery.html");
  ofstream *top = new ofstream(filename);
  HTMLStart(top,"Special two dimensional plots","2D_plots",option);

  TIter nextdrawoption(drawoptions);
  while (TObjString *drawoption = (TObjString*)nextdrawoption() ) {

    TString tempoption = option;
    tempoption.Append(",");
    tempoption.Append(drawoption->GetString());

    TIter nextdata(fPlots2D);
    while ( TObjString *datahist = (TObjString*)nextdata() ) {
      Bool_t temp_has_entry = kFALSE;
      TString tempoption2 = tempoption;
      tempoption2.Append(",DATA");
      temp_has_entry = Make2DPlotComplete(file,top,"","",datahist->GetString(),directory,tempoption2);
      if ( !has_entry)
	has_entry = temp_has_entry;
    }

    TIter nextdatazoomed(fPlots2DZoomed);
    while ( TObjString *datahistzoomed = (TObjString*)nextdatazoomed() ) {
      Bool_t temp_has_entry = kFALSE;
      TString tempoption2 = tempoption;
      tempoption2.Append(",DATA");
      temp_has_entry = Make2DPlotComplete(file,top,"","",datahistzoomed->GetString(),directory,tempoption2,0.33);
      if ( !has_entry)
	has_entry = temp_has_entry;
    }

    TIter nextmc(fPlots2DMC);
    while ( TObjString *mchist = (TObjString*)nextmc() ) {
      Bool_t temp_has_entry = kFALSE;
      TString tempoption2 = tempoption;
      tempoption2.Append(",MC");
      TIter nexttype(types);
      while ( TObjString *type = (TObjString*)nexttype() ) {
	if ( (mchist->GetString().EndsWith("B") && type->GetString().Contains("b")) ||
	     (mchist->GetString().EndsWith("C") && type->GetString().Contains("c")) ||
	     (mchist->GetString().EndsWith("LF") && type->GetString().Contains("lf")) ||
	     (mchist->GetString().EndsWith("BQuark") && type->GetString().Contains("b")) ||
	     (mchist->GetString().EndsWith("CQuark") && type->GetString().Contains("c")) ||
	     (mchist->GetString().EndsWith("LFQuark") && type->GetString().Contains("lf")) ) {
	  temp_has_entry = Make2DPlotComplete(file,top,type->GetString(),"",mchist->GetString(),directory,tempoption2);
	  if ( !has_entry)
	    has_entry = temp_has_entry;
	}
	TIter nexttype2(nexttype);
	while ( TObjString *type2 = (TObjString*)nexttype2() ) {
	  TString merge = type->GetString();
	  merge.Append("_");
	  merge.Append(type2->GetString());
	  temp_has_entry = Make2DPlotComplete(file,top,"",merge,mchist->GetString(),directory,tempoption2);
	  if ( !has_entry)
	    has_entry = temp_has_entry;
	  TIter nexttype3(nexttype2);
	  while ( TObjString *type3 = (TObjString*)nexttype3() ) {
	    TString merge = type->GetString();
	    merge.Append("_");
	    merge.Append(type2->GetString());
	    merge.Append("_");
	    merge.Append(type3->GetString());
	    temp_has_entry = Make2DPlotComplete(file,top,"",merge,mchist->GetString(),directory,tempoption2);
	    if ( !has_entry)
	      has_entry = temp_has_entry;
	  }
	}
      }
      if ( !has_entry)
	has_entry = temp_has_entry;
    }

    TIter nextmczoomed(fPlots2DMCZoomed);
    while ( TObjString *mczoomedhist = (TObjString*)nextmczoomed() ) {
      Bool_t temp_has_entry = kFALSE;
      TString tempoption2 = tempoption;
      tempoption2.Append(",MC");
      TIter nexttype(types);
      while ( TObjString *type = (TObjString*)nexttype() ) {
	if ( (mczoomedhist->GetString().EndsWith("B") && type->GetString().Contains("b")) ||
	     (mczoomedhist->GetString().EndsWith("C") && type->GetString().Contains("c")) ||
	     (mczoomedhist->GetString().EndsWith("LF") && type->GetString().Contains("lf")) ||
	     (mczoomedhist->GetString().EndsWith("BQuark") && type->GetString().Contains("b")) ||
	     (mczoomedhist->GetString().EndsWith("CQuark") && type->GetString().Contains("c")) ||
	     (mczoomedhist->GetString().EndsWith("LFQuark") && type->GetString().Contains("lf")) ) {
	  temp_has_entry = Make2DPlotComplete(file,top,type->GetString(),"",mczoomedhist->GetString(),directory,tempoption2,0.33,0.2);
	  if ( !has_entry)
	    has_entry = temp_has_entry;
	}
	TIter nexttype2(nexttype);
	while ( TObjString *type2 = (TObjString*)nexttype2() ) {
	  TString merge = type->GetString();
	  merge.Append("_");
	  merge.Append(type2->GetString());
	  temp_has_entry = Make2DPlotComplete(file,top,"",merge,mczoomedhist->GetString(),directory,tempoption2,0.33,0.2);
	  if ( !has_entry)
	    has_entry = temp_has_entry;
	  TIter nexttype3(nexttype2);
	  while ( TObjString *type3 = (TObjString*)nexttype3() ) {
	    TString merge = type->GetString();
	    merge.Append("_");
	    merge.Append(type2->GetString());
	    merge.Append("_");
	    merge.Append(type3->GetString());
	    temp_has_entry = Make2DPlotComplete(file,top,"",merge,mczoomedhist->GetString(),directory,tempoption2,0.33,0.2);
	    if ( !has_entry)
	      has_entry = temp_has_entry;
	  }
	}
      }
      if ( !has_entry)
	has_entry = temp_has_entry;
    }
  }

  HTMLEnd(top,"../gallery.html",fTime,option);
  delete top;  // add leading Histograms directory to input histograms
  
  return has_entry;
}

//_____________________________________________________________

Bool_t GPictureMaker::MakeSpecialCompleteComparison(TFile *file, TString directory, TString ptrelhistogramname, TString option) {
  //
  // make special comparison pictures
  if ( gDebug ) cout << endl << "GPictureMaker::MakeSpecialCompleteComparison() called" << endl << endl;

  TList *entries = new TList();
  Bool_t has_entry = kFALSE;

  // check whether dir exists, else generate
  gSystem->mkdir(directory,kTRUE);

  // start html file
  TString tempdir = directory;
  if ( tempdir.BeginsWith(".") ) {
    tempdir = "";
  } else if ( tempdir.EndsWith("/") && ( tempdir.Length() != 0 ) )
    tempdir.Remove(tempdir.Length()-1,1);
  // check whether tempdir exists, else generate
  gSystem->mkdir(tempdir.Data(),kTRUE);
  TString filename = tempdir.Data();
  filename.Append("/gallery.html");
  ofstream *top = new ofstream(filename);
  HTMLStart(top,"Comparison Plots using PtRel Fits","comparison_ptrel",option);

  TIter nextname(fPlotsComparison);
  while ( TObjString *name = (TObjString*)nextname() ) {
    Bool_t temp_has_entry = kFALSE;
    Double_t scale = 0.0;
    temp_has_entry = MakeComparisonPlotComplete(file,top,name->GetString(),ptrelhistogramname,directory,option,scale);
    // use region ptrel fit if region is contained in plot name
    if ( option.Contains("PTREL") ) {
      if ( name->GetString().Contains("Forward") || name->GetString().Contains("FORWARD") ) {
	TString tempoption = option;
	tempoption.Append(",FORWARD");
	temp_has_entry = MakeComparisonPlotComplete(file,top,name->GetString(),ptrelhistogramname,directory,tempoption,scale);
      } else if ( name->GetString().Contains("Barrel") || name->GetString().Contains("BARREL") ) {
	TString tempoption = option;
	tempoption.Append(",BARREL");
	temp_has_entry = MakeComparisonPlotComplete(file,top,name->GetString(),ptrelhistogramname,directory,tempoption,scale);
      } else if ( name->GetString().Contains("Rear") || name->GetString().Contains("REAR") ) {
	TString tempoption = option;
	tempoption.Append(",REAR");
	temp_has_entry = MakeComparisonPlotComplete(file,top,name->GetString(),ptrelhistogramname,directory,tempoption,scale);
      }
    }
    if ( !has_entry )
      has_entry = temp_has_entry;
  }

  HTMLEnd(top,"../gallery.html",fTime,option);
  delete top;  // add leading Histograms directory to input histograms
  
  entries->Delete();
  delete entries;

  return has_entry;
}

//_____________________________________________________________

Bool_t GPictureMaker::MakePtRelPlotComplete(TFile *file, ofstream *stream, TString histogramname, TString directory, TString option) {
  //
  // make PtRel plot
  if ( gDebug ) cout << endl << "GPictureMaker::MakePtRelPlotComplete called" << endl << endl;

  option.ToUpper();

  TH1D **histos = new TH1D *[4];

  // generation of data histogram name
  TString datahistname = "Histograms/data/merged/";
  datahistname.Append(histogramname);
  if ( !option.Contains("MCONLY") ) {
    histos[0]=(TH1D*)file->Get(datahistname);
    if ( histos[0] == 0) {
      return kFALSE;
    }
  }

  // generation of b MC histogram name
  TString bhistname = "Histograms/mc/merged/b/";
  bhistname.Append(histogramname);

  histos[1]=(TH1D*)file->Get(bhistname);
  if ( histos[1] == 0 ) {
    return kFALSE;
  }

  // generation of c MC histogram name
  TString chistname = "Histograms/mc/merged/c/";
  chistname.Append(histogramname);
  
  TH1D *chisto = (TH1D*)gFile->Get(chistname);
  if ( chisto == 0 ) {
    return kFALSE;
  }
  
  chistname.Append("_Corrections");
  TH1D *chisto_corr =(TH1D*)gFile->Get(chistname);
  if ( (chisto_corr != 0) && (chisto != 0) ) {
    Double_t old_int = chisto->Integral();
    chisto->Multiply(chisto_corr);
    Double_t new_int = chisto->Integral();
    chisto->Scale(old_int/new_int);
  }

  // generation of lf MC histogram name
  TString lfhistname = "Histograms/mc/merged/lf/";
  lfhistname.Append(histogramname);
  
  TH1D *lfhisto = (TH1D*)gFile->Get(lfhistname);
  if ( lfhisto == 0 ) {
    return kFALSE;
  }
  
  lfhistname.Append("_Corrections");
  TH1D *lfhisto_corr =(TH1D*)gFile->Get(lfhistname);
  if ( (lfhisto_corr != 0) && (lfhisto != 0) ) {
    Double_t old_int = lfhisto->Integral();
    lfhisto->Multiply(lfhisto_corr);
    Double_t new_int = lfhisto->Integral();
    lfhisto->Scale(old_int/new_int);
  }
  
  TH1D *clfhist = (TH1D*)chisto->Clone();
  clfhist->Add(lfhisto);

  histos[2]=clfhist;
  
  TH1D *cbhisto = (TH1D*)histos[1]->Clone("cbhisto");
  cbhisto->Reset();
  cbhisto->Add(chisto);
  histos[3]=cbhisto;
  
  if ( option.Contains("MCONLY") ) {
    TH1D *bclfhist = (TH1D*)histos[1]->Clone();
    bclfhist->Add(chisto);
    bclfhist->Add(lfhisto);
    histos[0]=bclfhist;
  }

  GPtRelFit *fit = 0;

  if ( option.Contains("MCONLY") )
    fit = gInclude->GetFit(file,bhistname);
  else
    fit = gInclude->GetFit(file,datahistname);

  if ( fit == 0 ) {
    return kFALSE;
  }

  if ( option.Contains("MCONLY") ) {
    cout << "GPictureMaker::MakePtRelPlotComplete for " << histogramname << " in MCONLY mode" << endl;
  } else {
    cout << "GPictureMaker::MakePtRelPlotComplete for " << histogramname << endl;
  }
  // calculate fraction
  Double_t fraction = fit->GetBFraction();
  Double_t fraction_error = fit->GetBFractionErr();

  // set batch to true
  Bool_t batch = gROOT->IsBatch();
  if ( !batch )
    gROOT->SetBatch(kTRUE);

  // delete old canvas
  if ( fCanvas ) {
    delete fCanvas;
    fCanvas = 0;
  }

  // canvas
  if ( !fCanvas ) {
    fCanvas = new TCanvas("canvas","canvas",640,480);
  } 

  // set error bars in x off
  gStyle->SetErrorX(0);

  fCanvas->cd();
  fCanvas->Clear();
  fCanvas->SetLogy(0);

  if (option.Contains("STATS"))
    gStyle->SetOptStat(1110);
  else
    gStyle->SetOptStat(0);

  if ( option.Contains("MCONLY") ) {
    histos[0]->SetMarkerColor(8);
    histos[0]->SetMarkerStyle(1);
    histos[0]->SetMarkerSize(0.01);
    histos[0]->SetLineColor(8);
    histos[0]->SetLineStyle(1);
    histos[0]->SetLineWidth((Short_t)0.01);
  } else {
    histos[0]->SetMarkerColor(2);
    histos[0]->SetMarkerStyle(8);
    histos[0]->SetMarkerSize(1.3);
  }
  histos[0]->SetTitleOffset(1.2);
  TString histoname = "ptrel_";
  histoname.Append(histogramname);
  histoname.ReplaceAll("/","_");
  histoname.ToLower();
  if ( option.Contains("MCONLY") )
    histoname.Append("_mconly");
  histos[0]->SetName(histoname);
  TString histotitle = "p_{T}^{rel} plot for ";
  histotitle.Append(histogramname);
  if ( option.Contains("MCONLY") ) {
    histotitle.Append(" using MC only");
  }
  histos[0]->SetTitle(histotitle);
  if ( option.Contains("MCONLY") )
    histos[0]->Draw("HIST");
  else
    histos[0]->Draw("PE");

  if (option.Contains("STATS")) {
    fCanvas->Update();
    TPaveStats *stats = (TPaveStats*)(histos[0]->GetListOfFunctions()->FindObject("stats"));
    stats->SetX1NDC(0.68);
    stats->SetY1NDC(0.88);
    stats->SetX2NDC(0.98);
    stats->SetY2NDC(0.995);
  }

  // title pave text
  fCanvas->Update();
  TPaveText *titlepave = (TPaveText*)fCanvas->FindObject("title");
  if ( titlepave->GetX2NDC() > 0.67 )
    titlepave->SetX2NDC(0.67);

  // scale histos[1] (bbbar) before adding to scaled histos[2] (c+lf)
  histos[1]->Scale(fit->GetBScale());

  histos[2]->Scale(fit->GetCLFScale());
  histos[2]->Add(histos[1],1);
  histos[2]->SetTitleOffset(1.2);
  histos[2]->SetLineColor(8);
  histos[2]->SetLineStyle(1);
  histos[2]->SetLineWidth((Short_t)3);
  histos[2]->SetStats(kFALSE);
  histos[2]->Draw("HIST,SAME");

  if (DoCLFDraw()) {  
    histos[3]->Scale(fit->GetCLFScale()); // ben: use c only fit!
    histos[3]->Add(histos[1],1);
    histos[3]->SetTitleOffset(1.2);
    histos[3]->SetLineColor(6);
    histos[3]->SetLineStyle(3);
    histos[3]->SetLineWidth((Short_t)3);
    histos[3]->SetStats(kFALSE);
    histos[3]->Draw("HIST,SAME");
  }

  histos[1]->SetTitle("test");
  histos[1]->SetStats(kFALSE);
  histos[1]->SetLineColor(4);
  histos[1]->SetLineStyle(2);
  histos[1]->SetLineWidth((Short_t)3);
  histos[1]->SetTitleOffset(1.2);
  histos[1]->Draw("HIST,SAME");

  // redraw data points
  
  if ( option.Contains("MCONLY") ) {
//     histos[0]->Draw("P,SAME");
  } else {
    histos[0]->Draw("PE,SAME");
  }

  TLegend *leg = 0;
  if (option.Contains("STATS"))
    leg = new TLegend(0.68,0.75,0.98,0.87);
  else
    leg = new TLegend(0.68,0.87,0.98,0.995);
  leg->SetTextSize(0.035); 
  leg->SetFillColor(10);
  leg->SetBorderSize(1); // no frame, no shadow
  TString datalegendentry = "Data 96-00";
  if ( file->Get("Histograms/mc/03p-04p") ) {
    datalegendentry = "Data 03-04";
  }
  if ( option.Contains("MCONLY") ) {
    //     leg->AddEntry(histos[0], "MC ccbar+lf+bbbar" , "P" );
  } else {
    leg->AddEntry(histos[0], datalegendentry , "P" );
  }
  if (DoCLFDraw()){
    leg->AddEntry(histos[1], "MC bbbar" , "L" );
    leg->AddEntry(histos[3], "MC bbbar+ccbar" , "L" );
    leg->AddEntry(histos[2], "MC bbbar+ccbar+lf" , "L" );
  }
  else {
    leg->AddEntry(histos[1], "MC bbbar" , "L" );
    leg->AddEntry(histos[2], "MC ccbar+lf+bbbar" , "L" );
  }
  leg->Draw("SAME");
 
  TString label = "";
  label.Append(gInclude->FormatedDouble(fraction,2,3));
  label.Append (" #pm ");
  label.Append(gInclude->FormatedDouble(fraction_error,2,3));

  TPaveText *text = 0;
  if (option.Contains("STATS"))
    text = new TPaveText(0.68,0.64,0.98,0.74,"br,NDC");
  else
    text = new TPaveText(0.68,0.77,0.98,0.86,"br,NDC");
  text->AddText("bbbar fraction:");
  text->AddText(label.Data());
  text->Draw("SAME");

  // nice histogram
  gInclude->NicePlot(fCanvas);
  gInclude->NicePlot(fCanvas);

  GenHTMLPics(stream, fCanvas,histoname,directory,histotitle,option);
  
  // set error bars in x to default
  gStyle->SetErrorX(0.5);

  // delete old canvas
  if ( fCanvas ) {
    delete fCanvas;
    fCanvas = 0;
  }

  // delete histo objects
  if ( chisto != 0 ) {
    delete chisto;
    chisto = 0;
  }
  if ( chisto_corr != 0 ) {
    delete chisto_corr;
    chisto_corr = 0;
  }
  if ( lfhisto != 0 ) {
    delete lfhisto;
    lfhisto = 0;
  }
  if ( lfhisto_corr != 0 ) {
    delete lfhisto_corr;
    lfhisto_corr = 0;
  }
  if ( clfhist != 0 ) {
    delete clfhist;
    clfhist = 0;
    histos[2] = 0;
  }

  for ( Int_t i = 0; i < 3; ++i ) {
    if ( histos[i] != 0 ) {
      delete histos[i];
      histos[i] = 0;
    }
  }

  // restore batch level
  if ( !batch )
    gROOT->SetBatch(kFALSE);

  return kTRUE;
}

//_____________________________________________________________

Bool_t GPictureMaker::MakeImpactPlotComplete(TFile *file, ofstream *stream, TString histogramname, TString directory, TString option) {
  //
  // make impact parameter plot
  if ( gDebug ) cout << endl << "GPictureMaker::MakeImpactPlotComplete called" << endl << endl;

  option.ToUpper();

  TH1D **histos = new TH1D *[3];

  // generation of data histogram name
  TString datahistname = "";
  if ( option.Contains("MCONLY") ) {
    datahistname = "Histograms/mc/merged/merged/";
    datahistname.Append(histogramname);
    datahistname.Append("_b_c_lf");
  } else {
    datahistname = "Histograms/data/merged/";
    datahistname.Append(histogramname);
  }

  // generation of b MC histogram name
  TString bhistname = "Histograms/mc/merged/b/";
  bhistname.Append(histogramname);

  // generation of c+lf MC histogram name
  TString clfhistname = "Histograms/mc/merged/merged/";
  clfhistname.Append(histogramname);
  clfhistname.Append("_c_lf");

  histos[0]=(TH1D*)file->Get(datahistname);
  if ( histos[0] == 0) {
    return kFALSE;
  }
  
  histos[1]=(TH1D*)file->Get(bhistname);
  if ( histos[1] == 0 ) {
    return kFALSE;
  }

  histos[2]=(TH1D*)file->Get(clfhistname);
  if ( histos[2] == 0 ) {
    return kFALSE;
  }

  GImpactFit *fit = 0;

  if ( option.Contains("MCONLY") )
    fit = gInclude->GetImpactFit(file,bhistname);
  else
    fit = gInclude->GetImpactFit(file,datahistname);

  if ( fit == 0 ) {
    return kFALSE;
  }

  if ( option.Contains("MCONLY") ) {
    cout << "GPictureMaker::MakeImpactPlotComplete for " << histogramname << " in MCONLY mode" << endl;
  } else {
    cout << "GPictureMaker::MakeImpactPlotComplete for " << histogramname << endl;
  }
  // calculate fraction
  Double_t fraction = fit->GetBFraction();
  Double_t fraction_error = fit->GetBFractionErr();

  // set batch to true
  Bool_t batch = gROOT->IsBatch();
  if ( !batch )
    gROOT->SetBatch(kTRUE);

  // delete old canvas
  if ( fCanvas ) {
    delete fCanvas;
    fCanvas = 0;
  }

  // canvas
  if ( !fCanvas ) {
    fCanvas = new TCanvas("canvas","canvas",640,480);
  } 

  // set error bars in x off
  gStyle->SetErrorX(0);

  fCanvas->cd();
  fCanvas->Clear();
  fCanvas->SetLogy(0);

  if (option.Contains("STATS"))
    gStyle->SetOptStat(1110);
  else
    gStyle->SetOptStat(0);

  if ( option.Contains("MCONLY") ) {
    histos[0]->SetMarkerColor(8);
    histos[0]->SetMarkerStyle(1);
    histos[0]->SetMarkerSize(0.01);
    histos[0]->SetLineColor(8);
    histos[0]->SetLineStyle(1);
    histos[0]->SetLineWidth((Short_t)0.01);
  } else {
    histos[0]->SetMarkerColor(2);
    histos[0]->SetMarkerStyle(8);
    histos[0]->SetMarkerSize(1.3);
  }
  histos[0]->SetTitleOffset(1.2);
  TString histoname = "impact_";
  histoname.Append(histogramname);
  histoname.ReplaceAll("/","_");
  histoname.ToLower();
  if ( option.Contains("MCONLY") )
    histoname.Append("_mconly");
  histos[0]->SetName(histoname);
  TString histotitle = "impact parameter plot for ";
  histotitle.Append(histogramname);
  if ( option.Contains("MCONLY") ) {
    histotitle.Append(" using MC only");
  }
  histos[0]->SetTitle(histotitle);
  if ( option.Contains("MCONLY") )
    histos[0]->Draw("HIST");
  else
    histos[0]->Draw("PE");

  if (option.Contains("STATS")) {
    fCanvas->Update();
    TPaveStats *stats = (TPaveStats*)(histos[0]->GetListOfFunctions()->FindObject("stats"));
    stats->SetX1NDC(0.68);
    stats->SetY1NDC(0.88);
    stats->SetX2NDC(0.98);
    stats->SetY2NDC(0.995);
  }

  // title pave text
  fCanvas->Update();
  TPaveText *titlepave = (TPaveText*)fCanvas->FindObject("title");
  if ( titlepave->GetX2NDC() > 0.67 )
    titlepave->SetX2NDC(0.67);

  // scale histos[1] (bbbar) before adding to scaled histos[2] (c+lf)
  histos[1]->Scale(fit->GetBScale());

  histos[2]->Scale(fit->GetCLFScale());
  histos[2]->Add(histos[1],1);
  histos[2]->SetTitleOffset(1.2);
  histos[2]->SetLineColor(8);
  histos[2]->SetLineStyle(1);
  histos[2]->SetLineWidth((Short_t)3);
  histos[2]->SetStats(kFALSE);
  histos[2]->Draw("HIST,SAME");

  histos[1]->SetTitle("test");
  histos[1]->SetStats(kFALSE);
  histos[1]->SetLineColor(4);
  histos[1]->SetLineStyle(2);
  histos[1]->SetLineWidth((Short_t)3);
  histos[1]->SetTitleOffset(1.2);
  histos[1]->Draw("HIST,SAME");

  // redraw data points
  
  if ( option.Contains("MCONLY") ) {
//     histos[0]->Draw("P,SAME");
  } else {
    histos[0]->Draw("PE,SAME");
  }

  TLegend *leg = 0;
  if (option.Contains("STATS"))
    leg = new TLegend(0.68,0.75,0.98,0.87);
  else
    leg = new TLegend(0.68,0.87,0.98,0.995);
  leg->SetTextSize(0.035); 
  leg->SetFillColor(10);
  leg->SetBorderSize(1); // no frame, no shadow
  TString datalegendentry = "Data 96-00";
  if ( file->Get("Histograms/mc/03p-04p") ) {
    datalegendentry = "Data 03-04";
  }
  if ( option.Contains("MCONLY") ) {
    //     leg->AddEntry(histos[0], "MC ccbar+lf+bbbar" , "P" );
  } else {
    leg->AddEntry(histos[0], datalegendentry , "P" );
  }
  leg->AddEntry(histos[1], "MC bbbar" , "L" );
  leg->AddEntry(histos[2], "MC bbbar+ccbar+lf" , "L" );
  leg->Draw("SAME");
 
  TString label = "";
  label.Append(gInclude->FormatedDouble(fraction,2,3));
  label.Append (" #pm ");
  label.Append(gInclude->FormatedDouble(fraction_error,2,3));

  TPaveText *text = 0;
  if (option.Contains("STATS"))
    text = new TPaveText(0.68,0.64,0.98,0.74,"br,NDC");
  else
    text = new TPaveText(0.68,0.77,0.98,0.86,"br,NDC");
  text->AddText("bbbar fraction:");
  text->AddText(label.Data());
  text->Draw("SAME");

  // nice histogram
  gInclude->NicePlot(fCanvas);
  gInclude->NicePlot(fCanvas);

  GenHTMLPics(stream, fCanvas,histoname,directory,histotitle,option);
  
  // set error bars in x to default
  gStyle->SetErrorX(0.5);

  // delete old canvas
  if ( fCanvas ) {
    delete fCanvas;
    fCanvas = 0;
  }

  // restore batch level
  if ( !batch )
    gROOT->SetBatch(kFALSE);

  return kTRUE;
}

//_____________________________________________________________

Bool_t GPictureMaker::Make1DPlotComplete(TFile *file, ofstream *stream, TString type, TString merge, TString histogramname, TString directory, TString option, Double_t zoomx) {
  //
  // make 1D plot
  if ( gDebug ) cout << endl << "GPictureMaker::Make1DPlotComplete called" << endl << endl;

  option.ToUpper();

  TString histname = "Histograms/";
  if ( option.Contains("DATA") ) {
    histname.Append("data/merged/");
      histname.Append(histogramname);
  } else if ( option.Contains("MC") ) {
    histname.Append("mc/merged/");
    if ( type.Length() != 0 ) {
      histname.Append(type);
      histname.Append("/");
    } else {
      histname.Append("merged/");
    }
    histname.Append(histogramname);
    if ( merge.Length() != 0 ) {
      histname.Append("_");
      histname.Append(merge);
    }
  }
  TH1D* histo=(TH1D*)file->Get(histname);
  if ( histo == 0) {
//     cout << "1D: problems in getting histogram: " << histname << endl;
    return kFALSE;
  }
  
  if ( option.Contains("DATA") ) {
    cout << "GPictureMaker::Make1DPlotComplete for " << histogramname << " in DATA mode " << endl;
  } else if ( option.Contains("MC") ) {
    cout << "GPictureMaker::Make1DPlotComplete for " << histogramname << " in MC mode " << endl;
  }

  // set batch to true
  Bool_t batch = gROOT->IsBatch();
  if ( !batch )
    gROOT->SetBatch(kTRUE);

  // delete old canvas
  if ( fCanvas ) {
    delete fCanvas;
    fCanvas = 0;
  }

  // canvas
  if ( !fCanvas ) {
    fCanvas = new TCanvas("canvas","canvas",640,480);
  } 

  // set error bars in x off
  gStyle->SetErrorX(0);

  fCanvas->cd();
  fCanvas->Clear();
  fCanvas->SetLogy(0);

  if (option.Contains("STATS"))
    gStyle->SetOptStat(1110);
  else
    gStyle->SetOptStat(0);

  TString histoname = histo->GetName();
  if ( type.Length() != 0 ) {
    histoname.Append("_");
    histoname.Append(type);
  }
  TString histotitle = histo->GetTitle(); 

  histo->SetMarkerColor(2);
  histo->SetMarkerStyle(8);
  histo->SetMarkerSize(1.3);
  if ( zoomx != 0.0 )
    histo->GetXaxis()->SetRangeUser(0.,histo->GetXaxis()->GetXmax()*zoomx);
//   histo->SetTitleOffset(1.2);
  histo->Draw("PE");

  if (option.Contains("STATS")) {
    fCanvas->Update();
    TPaveStats *stats = (TPaveStats*)(histo->GetListOfFunctions()->FindObject("stats"));
    stats->SetX1NDC(0.68);
    stats->SetY1NDC(0.88);
    stats->SetX2NDC(0.98);
    stats->SetY2NDC(0.995);
  }

  // title pave text
  fCanvas->Update();
  TPaveText *titlepave = (TPaveText*)fCanvas->FindObject("title");
  if ( titlepave->GetX2NDC() > 0.67 )
    titlepave->SetX2NDC(0.67);
  
  gInclude->NicePlot(fCanvas);
  gInclude->NicePlot(fCanvas);

  if ( zoomx != 0.0 ) {
    histoname.Append("_zoomed");
  }

  GenHTMLPics(stream, fCanvas,histoname,directory,histotitle,option);
  
  // set error bars in x to default
  gStyle->SetErrorX(0.5);

  // delete old canvas
  if ( fCanvas ) {
    delete fCanvas;
    fCanvas = 0;
  }

  // restore batch level
  if ( !batch )
    gROOT->SetBatch(kFALSE);

  return kTRUE;
}

//_____________________________________________________________

Bool_t GPictureMaker::Make2DPlotComplete(TFile *file, ofstream *stream, TString type, TString merge, TString histogramname, TString directory, TString option, Double_t zoomx, Double_t zoomy) {
  //
  // make 2D plot
  if ( gDebug ) cout << endl << "GPictureMaker::Make2DPlot called" << endl << endl;

  option.ToUpper();

  TString histname = "Histograms/";
  if ( option.Contains("DATA") ) {
    histname.Append("data/merged/");
    histname.Append(histogramname);
  } else if ( option.Contains("MC") ) {
    histname.Append("mc/merged/");
    if ( type.Length() != 0 ) {
      histname.Append(type);
      histname.Append("/");
    } else {
      histname.Append("merged/");
    }
    histname.Append(histogramname);
    if ( merge.Length() != 0 ) {
      histname.Append("_");
      histname.Append(merge);
    }
  }
  TH2D* histo=(TH2D*)file->Get(histname);
  if ( histo == 0) {
//     cout << "2D: problems in getting histogram: " << histname << endl;
    return kFALSE;
  }
  
  if ( option.Contains("DATA") ) {
    cout << "GPictureMaker::Make2DPlot for " << histogramname << " in DATA mode " << endl;
  } else if ( option.Contains("MC") ) {
    cout << "GPictureMaker::Make2DPlot for " << histogramname << " in MC mode " << endl;
  }

  // set batch to true
  Bool_t batch = gROOT->IsBatch();
  if ( !batch )
    gROOT->SetBatch(kTRUE);

  // delete old canvas
  if ( fCanvas ) {
    delete fCanvas;
    fCanvas = 0;
  }

  // canvas
  if ( !fCanvas ) {
    fCanvas = new TCanvas("canvas","canvas",640,480);
  } 

  // set error bars in x off
  gStyle->SetErrorX(0);

  fCanvas->cd();
  fCanvas->Clear();
  fCanvas->SetLogy(0);

  if (option.Contains("STATS"))
    gStyle->SetOptStat(1110);
  else
    gStyle->SetOptStat(0);

//   histo->SetMarkerColor(2);
//   histo->SetMarkerStyle(8);
//   histo->SetMarkerSize(1.3);
//   histo->SetTitleOffset(1.2);

  if ( zoomx != 0.0 )
    histo->GetXaxis()->SetRangeUser(0.,histo->GetXaxis()->GetXmax()*zoomx);
  if ( zoomy != 0.0 )
    histo->GetYaxis()->SetRangeUser(0.,histo->GetYaxis()->GetXmax()*zoomy);

  TString histoname = histo->GetName();
  if ( type.Length() != 0 ) {
    histoname.Append("_");
    histoname.Append(type);
  }
  histoname.Append("_");
  TString histotitle = histo->GetTitle(); 

  if ( option.Contains("COLZ") ) {
    histo->Draw("COLZ");
    histoname.Append("colz");
  } else if ( option.Contains("BOX") ) {
    histo->Draw("BOX");
    histoname.Append("box");
  } else if ( option.Contains("CONTZ") ) {
    histo->Draw("CONTZ");
    histoname.Append("contz");
  } else if ( option.Contains("SCAT") ) {
    histo->Draw("SCAT");
    histoname.Append("scat");
  } 

  if ( (zoomx != 0.0) || (zoomy != 0.0) ) {
    histoname.Append("_zoomed");
  }

  if (option.Contains("STATS")) {
    fCanvas->Update();
    TPaveStats *stats = (TPaveStats*)(histo->GetListOfFunctions()->FindObject("stats"));
    stats->SetX1NDC(0.68);
    stats->SetY1NDC(0.88);
    stats->SetX2NDC(0.98);
    stats->SetY2NDC(0.995);
  }

  // title pave text
  fCanvas->Update();
  TPaveText *titlepave = (TPaveText*)fCanvas->FindObject("title");
  if ( titlepave->GetX2NDC() > 0.67 )
    titlepave->SetX2NDC(0.67);
  
  gInclude->NicePlot(fCanvas);
  gInclude->NicePlot(fCanvas);

  GenHTMLPics(stream, fCanvas,histoname,directory,histotitle,option);
  
  // set error bars in x to default
  gStyle->SetErrorX(0.5);

  // delete old canvas
  if ( fCanvas ) {
    delete fCanvas;
    fCanvas = 0;
  }

  // restore batch level
  if ( !batch )
    gROOT->SetBatch(kFALSE);

  return kTRUE;
}

//_____________________________________________________________

Bool_t GPictureMaker::MakeComparisonPlotComplete(TFile *file, ofstream *stream, TString histogramname, TString ptrelhistogramname, TString directory, TString option, Double_t scaleMaximum) {
  //
  // make mc comparison plot
  if ( gDebug ) cout << endl << "GPictureMaker::MakeComparisonPlotComplete called" << endl << endl;

  option.ToUpper();

  Double_t statsX1NDC = 0.68;
  Double_t statsY1NDC = 0.88;
  Double_t statsX2NDC = 0.98;
  Double_t statsY2NDC = 0.995;
  Double_t legX1NDC = 0.0;
  Double_t legY1NDC = 0.0;
  Double_t legX2NDC = 0.0;
  Double_t legY2NDC = 0.0;
  if ( option.Contains("PTREL") ) {
    if (option.Contains("STATS")) {
      legX1NDC = 0.68;
      legY1NDC = 0.75;
      legX2NDC = 0.98;
      legY2NDC = 0.87;
    } else {
      legX1NDC = 0.68;
      legY1NDC = 0.87;
      legX2NDC = 0.98;
      legY2NDC = 0.995;
    }
  } else if ( option.Contains("LUMI") ) {
    if (option.Contains("STATS")) {
      legX1NDC = 0.68;
      legY1NDC = 0.67;
      legX2NDC = 0.98;
      legY2NDC = 0.87;
    } else {
      legX1NDC = 0.68;
      legY1NDC = 0.81;
      legX2NDC = 0.98;
      legY2NDC = 0.995;
    }
  }
  Double_t textX1NDC = 0.0;
  Double_t textY1NDC = 0.0;
  Double_t textX2NDC = 0.0;
  Double_t textY2NDC = 0.0;
  if (option.Contains("STATS")) {
    textX1NDC = 0.68;
    textY1NDC = 0.64;
    textX2NDC = 0.98;
    textY2NDC = 0.74;
  } else {
    textX1NDC = 0.68;
    textY1NDC = 0.77;
    textX2NDC = 0.98;
    textY2NDC = 0.86;
  }

  TH1D **histos = new TH1D *[6];

  TString datahistname = "Histograms/data/merged/";
  datahistname.Append(histogramname);
  histos[0]=(TH1D*)file->Get(datahistname);
  if ( histos[0] == 0) {
//     cout << "comparison-problems in getting histogram: " << datahistname << endl;
    return kFALSE;
  }
  
  TString bhistname = "Histograms/mc/merged/b/";
  bhistname.Append(histogramname);
  histos[1]=(TH1D*)file->Get(bhistname);
  if ( histos[1] == 0 ) {
//     cout << "comparison-problems in getting histogram: " << bhistname << endl;
    return kFALSE;
  }

  TString chistname = "Histograms/mc/merged/c/";
  chistname.Append(histogramname);
  histos[2]=(TH1D*)file->Get(chistname);
  if ( histos[2] == 0 ) {
//     cout << "comparison-problems in getting histogram: " << chistname << endl;
    return kFALSE;
  }

  TString lfhistname = "Histograms/mc/merged/lf/";
  lfhistname.Append(histogramname);
  histos[3]=(TH1D*)file->Get(lfhistname);
  if ( histos[3] == 0 ) {
//     cout << "comparison-problems in getting histogram: " << lfhistname << endl;
    return kFALSE;
  }

  TString bclfhistname = "Histograms/mc/merged/merged/";
  bclfhistname.Append(histogramname);
  bclfhistname.Append("_b_c_lf");
  histos[4]=(TH1D*)file->Get(bclfhistname);
  if ( histos[4] == 0 ) {
//     cout << "comparison-problems in getting histogram: " << bclfhistname << endl;
    return kFALSE;
  }

  TH1D *cbhisto = (TH1D*)histos[2]->Clone("cbhisto");
  cbhisto->Reset();
  cbhisto->Add(histos[2]);
  histos[5]=cbhisto;

  TString ptrelhistname = datahistname;
  TString tempptrelhistogramname = ptrelhistogramname;
  if ( option.Contains("FORWARD") ) {
    tempptrelhistogramname.Append("_Forward");
  } else if ( option.Contains("BARREL") ) {
    tempptrelhistogramname.Append("_Barrel");
  } else if ( option.Contains("REAR") ) {
    tempptrelhistogramname.Append("_Rear");
  }
  ptrelhistname.ReplaceAll(histogramname,tempptrelhistogramname);

  GPtRelFit *fit = gInclude->GetFit(file,ptrelhistname);
  if ( fit == 0 ) {
//     cout << "comparison-problems in getting fit for: " << ptrelhistname << endl;
    return kFALSE;
  }

  if ( option.Contains("PTREL") ) {
    cout << "GPictureMaker::MakeComparisonPlotComplete for " << histogramname << " in PTREL mode";
    if ( option.Contains("FORWARD") ) {
      cout << " using forward ptrel fit";
    } else if ( option.Contains("BARREL") ) {
      cout << " using barrel ptrel fit";
    } else if ( option.Contains("REAR") ) {
      cout << " using rear ptrel fit";
    }
    cout << endl;
  } else {
    cout << "GPictureMaker::MakeComparisonPlotComplete for " << histogramname << " in LUMI mode " << endl;
  }

  // calculate fraction
  Double_t fraction = fit->GetBFraction();
  Double_t fraction_error = fit->GetBFractionErr();

  // set batch to true
  Bool_t batch = gROOT->IsBatch();
  if ( !batch )
    gROOT->SetBatch(kTRUE);

  // delete old canvas
  if ( fCanvas ) {
    delete fCanvas;
    fCanvas = 0;
  }

  // canvas
  if ( !fCanvas ) {
    fCanvas = new TCanvas("canvas","canvas",640,480);
  } 

  // set error bars in x off
  gStyle->SetErrorX(0);

  fCanvas->cd();
  fCanvas->Clear();
  fCanvas->SetLogy(0);

  if (option.Contains("STATS"))
    gStyle->SetOptStat(1110);
  else
    gStyle->SetOptStat(0);

  // prepare histograms
  TString histoname = "comparison_";
  if ( option.Contains("PTREL") )
    histoname.Append("ptrel_");
  else if ( option.Contains("LUMI") )
    histoname.Append("lumi_");
  histoname.Append(histogramname);
  if ( option.Contains("FORWARD") ) {
    histoname.Append("_forward");
  } else if ( option.Contains("BARREL") ) {
    histoname.Append("_barrel");
  } else if ( option.Contains("REAR") ) {
    histoname.Append("_rear");
  } 
  histoname.ReplaceAll("/","_");
  histoname.ToLower();
  histos[0]->SetName(histoname);
  TString histotitle = histogramname;
  histotitle.Append(" using ");
  if ( option.Contains("PTREL") ) {
    if ( option.Contains("FORWARD") ) {
      histotitle.Append("forward ");
    } else if ( option.Contains("BARREL") ) {
      histotitle.Append("barrel ");
    } else if ( option.Contains("REAR") ) {
      histotitle.Append("rear ");
    } 
    histotitle.Append("p_{T}^{rel} fit");
  } else if ( option.Contains("LUMI") )
    histotitle.Append("lumi");

  histos[0]->SetStats(kTRUE);
  histos[0]->SetMarkerColor(2);
  histos[0]->SetMarkerStyle(8);
  histos[0]->SetMarkerSize(1.3);
  histos[0]->SetTitleOffset(1.2);
  histos[0]->SetName(histoname);
  histos[0]->SetTitle(histotitle);
  if ( option.Contains("PTREL") ) {
    
    // scale histos[1] (bbbar) before adding to scaled histos[2] (c+lf)
    histos[1]->Scale(fit->GetBScale());

    histos[2]->SetStats(kFALSE);
    histos[2]->Add(histos[3],1);
    histos[2]->Scale(fit->GetCLFScale());
    histos[2]->Add(histos[1],1);
    histos[2]->SetLineStyle(1);
    histos[2]->SetLineWidth((Short_t)3);
    histos[2]->SetLineColor(8);
    
    if (DoCLFDraw()){
      histos[5]->Scale(fit->GetCLFScale());
      histos[5]->Add(histos[1],1);
      histos[5]->SetLineStyle(3);
      histos[5]->SetLineWidth((Short_t)3);
      histos[5]->SetLineColor(6);
    }
    
  } else if ( option.Contains("LUMI") ) {
    
    histos[4]->SetStats(kFALSE);
    histos[4]->SetLineColor(8);
    histos[4]->SetLineStyle(1);
    histos[4]->SetLineWidth((Short_t)3);
    histos[4]->SetTitleOffset(1.2);
    
    histos[3]->SetStats(kFALSE);
    histos[3]->SetLineColor(43);
    histos[3]->SetLineStyle(1);
    histos[3]->SetLineWidth((Short_t)3);
    histos[3]->SetTitleOffset(1.2);
    
    histos[2]->SetStats(kFALSE);
    histos[2]->SetLineColor(50);
    histos[2]->SetLineStyle(1);
    histos[2]->SetLineWidth((Short_t)3);
    histos[2]->SetTitleOffset(1.2);
    
  }
  
  histos[1]->SetStats(kFALSE);
  histos[1]->SetTitle("b");
  histos[1]->SetLineColor(4);
  histos[1]->SetLineStyle(1);
  histos[1]->SetLineWidth((Short_t)3);
  histos[1]->SetTitleOffset(1.2);
  
  // determine maximum of plot
  // determine histo with maximum in last 40% of bins
  Int_t startbins = (Int_t)(textX1NDC * histos[0]->GetNbinsX());
  Double_t max = histos[0]->GetMaximum();

  Double_t localmax = -9999.99;

  if ( option.Contains("PTREL") ) {
    for ( Int_t i = 0; i < 3; ++i ) {
      for ( Int_t bin = startbins; bin <= histos[i]->GetNbinsX(); ++bin){
	if ( localmax < histos[i]->GetBinContent(bin) )
	  localmax = histos[i]->GetBinContent(bin);
      }
      if (DoCLFDraw()){
	for ( Int_t bin = startbins; bin <= histos[5]->GetNbinsX(); ++bin){
	  if ( localmax < histos[5]->GetBinContent(bin) )
	    localmax = histos[5]->GetBinContent(bin);
	}
      }
    }
  } else if ( option.Contains("LUMI") ) {
    for ( Int_t i = 0; i < 5; ++i ) {
      for ( Int_t bin = startbins; bin <= histos[i]->GetNbinsX(); ++bin){
	if ( localmax < histos[i]->GetBinContent(bin) )
	  localmax = histos[i]->GetBinContent(bin);
      }
    }
  }

  if ( option.Contains("PTREL") ) {
    if ( localmax > (textY1NDC*max) )
      max = 1/textY1NDC*localmax;
  } else if ( option.Contains("LUMI") ) {
    if ( localmax > (legY1NDC*max) )
      max = 1/legY1NDC*localmax;
  }

  histos[0]->SetMaximum(1.15*max);

  if ( scaleMaximum > 1.2 )
    histos[0]->SetMaximum(histos[0]->GetMaximum()*scaleMaximum);

  histos[0]->Draw("PE");

  if (option.Contains("STATS")) {
    fCanvas->Update();
    TPaveStats *stats = (TPaveStats*)(histos[0]->GetListOfFunctions()->FindObject("stats"));
    stats->SetX1NDC(statsX1NDC);
    stats->SetY1NDC(statsY1NDC);
    stats->SetX2NDC(statsX2NDC);
    stats->SetY2NDC(statsY2NDC);
  }

  // title pave text
  fCanvas->Update();
  TPaveText *titlepave = (TPaveText*)fCanvas->FindObject("title");
  if ( titlepave->GetX2NDC() > 0.67 )
    titlepave->SetX2NDC(0.67);
  
  if ( option.Contains("PTREL") ) {
    
    if (DoCLFDraw()){
      histos[5]->Draw("HIST,SAME");
    }
 
    histos[2]->Draw("HIST,SAME");
    
  } else if ( option.Contains("LUMI") ) {
    
    histos[4]->Draw("HIST,SAME");
    
    histos[3]->Draw("HIST,SAME");
    
    histos[2]->Draw("HIST,SAME");
    
  }
  
  histos[1]->Draw("HIST,SAME");
  
  // redraw data
  histos[0]->Draw("PE,SAME");
  
  TLegend *leg = 0;
  if ( option.Contains("PTREL") ) {
    leg = new TLegend(legX1NDC,legY1NDC,legX2NDC,legY2NDC);
    leg->SetTextSize(0.035); 
    leg->SetFillColor(10);
    leg->SetBorderSize(1); // no frame, no shadow
    TString datalegendentry = "Data 96-00";
    if ( file->Get("Histograms/mc/03p-04p") ) {
      datalegendentry = "Data 03-04";
    }
    leg->AddEntry(histos[0], datalegendentry , "P" );
    if (DoCLFDraw()){
      leg->AddEntry(histos[1], "MC bbbar" , "L" );
      leg->AddEntry(histos[5], "MC bbbar+ccbar" , "L" );
      leg->AddEntry(histos[2], "MC bbbar+ccbar+lf" , "L" );
    }
    else {
      leg->AddEntry(histos[1], "MC bbbar" , "L" );
      leg->AddEntry(histos[2], "MC ccbar+lf+bbbar" , "L" );
    }
  } else if ( option.Contains("LUMI") ) {
    leg = new TLegend(legX1NDC,legY1NDC,legX2NDC,legY2NDC);
    leg->SetTextSize(0.035); 
    leg->SetFillColor(10);
    leg->SetBorderSize(1); // no frame, no shadow
    TString datalegendentry = "Data 96-00";
    if ( file->Get("Histograms/mc/03p-04p") ) {
      datalegendentry = "Data 03-04";
    }
    leg->AddEntry(histos[0], datalegendentry , "P" );
    leg->AddEntry(histos[1], "MC b" , "L" );
    leg->AddEntry(histos[2], "MC c" , "L" );
    leg->AddEntry(histos[3], "MC lf" , "L" );
    leg->AddEntry(histos[4], "MC b+c+lf" , "L" );
  }
  leg->Draw("SAME");
  
  if ( option.Contains("PTREL") ) {
    TString label = "";
    label.Append(gInclude->FormatedDouble(fraction,2,3));
    label.Append (" #pm ");
    label.Append(gInclude->FormatedDouble(fraction_error,2,3));
    
    TPaveText *text = new TPaveText(textX1NDC,textY1NDC,textX2NDC,textY2NDC,"br,NDC");
    text->AddText("bbbar fraction:");
    text->AddText(label.Data());
    text->Draw("SAME");
  }

  gInclude->NicePlot(fCanvas);
  gInclude->NicePlot(fCanvas);
 
  GenHTMLPics(stream,fCanvas,histoname,directory,histotitle,option);
  
  // set error bars in x to default
  gStyle->SetErrorX(0.5);

  // delete old canvas
  if ( fCanvas ) {
    delete fCanvas;
    fCanvas = 0;
  }

  // restore batch level
  if ( !batch )
    gROOT->SetBatch(kFALSE);

  return kTRUE;
}
  
//_____________________________________________________________

Bool_t GPictureMaker::MakeEfficiencyPlotData(TFile *file, ofstream *stream, TString directory, TString basename, TString finder, TString period, TString region, TString type, TString option) {
  //
  // make data efficiency plot

  TString histogram = "Histograms/data/merged/DIMuon/MV_";
  histogram.Append(finder);
  histogram.Append("_");
  histogram.Append(basename);
  if ( region.Length() > 0 ) {
    histogram.Append("_");
    histogram.Append(region);
  }
  if ( period.Length() > 0 ) {
    histogram.Append("_");
    histogram.Append(period);
  }
  TString mv_histogram = "Histograms/data/merged/DIMuon/MV_";
  mv_histogram.Append(basename);
  if ( region.Length() > 0 ) {
    mv_histogram.Append("_");
    mv_histogram.Append(region);
  }
  if ( period.Length() > 0 ) {
    mv_histogram.Append("_");
    mv_histogram.Append(period);
  }
  TH1D *histo1 = (TH1D*)file->Get(histogram);
  if ( histo1 == 0) {
//     cout << "problems in getting histogram: " << histogram << endl;
    return kFALSE;
  }

  TH1D *mv1 = (TH1D*)file->Get(mv_histogram);
  if ( mv1 == 0) {
//     cout << "problems in getting MV histogram: " << mv_histogram << endl;
    return kFALSE;
  }

  cout << "GPictureMaker::MakeEfficiencyPlotData for " << histogram << " for period " << period << endl;

//   cout << "directory: " << directory << endl;
//   cout << "histogram: " << histogram << " histo1->GetName(): " << histo1->GetName() << " histo1->GetTitle(): " << histo1->GetTitle() << endl;
//   cout << "mv_histogram: " << mv_histogram << " mv1->GetName(): " << mv1->GetName() << " mv1->GetTitle(): " << mv1->GetTitle() << endl;
//   cout << "histo1: " << histo1 << endl;
//   cout << "mv1: " << mv1 << endl;

  // set batch to true
  Bool_t batch = gROOT->IsBatch();
  if ( !batch )
    gROOT->SetBatch(kTRUE);
  
  // delete old canvas
  if ( fCanvas ) {
    delete fCanvas;
    fCanvas = 0;
  }
  
  // canvas
  if ( !fCanvas ) {
    fCanvas = new TCanvas("canvas","canvas",640,480);
  } 

  fCanvas->cd();
  fCanvas->Clear();
  fCanvas->SetLogy(0);
  
  gStyle->SetOptStat(10);
  
  TString histoname = histo1->GetName();
  TString histotitle = histo1->GetTitle();
  
  TH1D *temphist = (TH1D*)histo1->Clone();
  temphist->Clear();
  temphist->Divide(histo1,mv1,1,1,"b");
  
  temphist->SetName(histoname);
  temphist->SetTitle(histotitle);
  temphist->GetYaxis()->SetTitle("Efficiency");
  
  temphist->SetMarkerColor(2);
  temphist->SetLineColor(4);
  temphist->SetMarkerStyle(8);
  temphist->SetMarkerSize(1.3);
  temphist->Draw("P0E0");

  if (option.Contains("STATS")) {
    fCanvas->Update();
    TPaveStats *stats = (TPaveStats*)(temphist->GetListOfFunctions()->FindObject("stats"));
    stats->SetX1NDC(0.68);
    stats->SetY1NDC(0.92);
    stats->SetX2NDC(0.98);
    stats->SetY2NDC(0.995);
  }

  // title pave text
  fCanvas->Update();
  TPaveText *titlepave = (TPaveText*)fCanvas->FindObject("title");
  if ( titlepave->GetX2NDC() > 0.67 )
    titlepave->SetX2NDC(0.67);
  
  gInclude->NicePlot(fCanvas);
  gInclude->NicePlot(fCanvas);

  GenHTMLPics(stream, fCanvas,histoname,directory,histotitle,option);
  
  // set error bars in x to default
  gStyle->SetErrorX(0.5);
  
  // delete old canvas
  if ( fCanvas ) {
    delete fCanvas;
    fCanvas = 0;
  }
  
  // restore batch level
  if ( !batch )
    gROOT->SetBatch(kFALSE);

  delete temphist;
  
  return kTRUE;
}
  
//_____________________________________________________________

Bool_t GPictureMaker::MakeCorrectionPlot(TFile *file, ofstream *stream, TString directory, TString basename, TString finder, TString period, TString region, TString type, TString option) {
  //
  // make muon efficiency correction factor plot

  TString data_histogram = "Histograms/data/merged/DIMuon/MV_";
  data_histogram.Append(finder);
  data_histogram.Append("_");
  data_histogram.Append(basename);
  if ( region.Length() > 0 ) {
    data_histogram.Append("_");
    data_histogram.Append(region);
  }
  if ( period.Length() > 0 ) {
    data_histogram.Append("_");
    data_histogram.Append(period);
  }
  TString mv_data_histogram = "Histograms/data/merged/DIMuon/MV_";
  mv_data_histogram.Append(basename);
  if ( region.Length() > 0 ) {
    mv_data_histogram.Append("_");
    mv_data_histogram.Append(region);
  }
  if ( period.Length() > 0 ) {
    mv_data_histogram.Append("_");
    mv_data_histogram.Append(period);
  }
  TH1D *data_histo1 = (TH1D*)file->Get(data_histogram);
  if ( data_histo1 == 0) {
//     cout << "problems in getting histogram: " << data_histogram << endl;
    return kFALSE;
  }

  TH1D *data_mv1 = (TH1D*)file->Get(mv_data_histogram);
  if ( data_mv1 == 0) {
//     cout << "problems in getting MV data_histogram: " << mv_data_histogram << endl;
    return kFALSE;
  }

  // fill typelist
  TList  *typelist = new TList();
  if ( type.Contains(",") ) {
    TString temptype = type;

    char first;
    TString tempstring = "";
    // separate entries in types
    while ( (first = temptype(0)) ) {
      // remove first
      temptype.Remove(0,1);
      // append to temp or break in case of comma
      if ( first == 44 ) {
	typelist->Add(new TObjString(tempstring));
	tempstring = "";
      } else {
	tempstring.Append(first);
      }
    }
    if ( tempstring.Length() != 0 ) {
      typelist->Add(new TObjString(tempstring));
    }
  }

  TString mc_histogram = "";
  TString mv_mc_histogram = "";

  if ( type.Contains(",") ) {
    
    mc_histogram = "Histograms/mc/";
    mc_histogram.Append(period);
    mc_histogram.Append("/merged/DIMuon/MV_");
    mc_histogram.Append(finder);
    mc_histogram.Append("_");
    mc_histogram.Append(basename);
    if ( region.Length() > 0 ) {
      mc_histogram.Append("_");
      mc_histogram.Append(region);
    }
    TIter nexttype(typelist);
    while (TObjString *temptype = (TObjString*)nexttype() ) {
      mc_histogram.Append("_");
      mc_histogram.Append(temptype->GetString());
    }
    
    mv_mc_histogram = "Histograms/mc/";
    mv_mc_histogram.Append(period);
    mv_mc_histogram.Append("/merged/DIMuon/MV_");
    mv_mc_histogram.Append(basename);
    if ( region.Length() > 0 ) {
      mv_mc_histogram.Append("_");
      mv_mc_histogram.Append(region);
    }
    TIter nexttype2(typelist);
    while (TObjString *temptype2 = (TObjString*)nexttype2() ) {
      mv_mc_histogram.Append("_");
      mv_mc_histogram.Append(temptype2->GetString());
    }
  } else {
    mc_histogram = "Histograms/mc/";
    mc_histogram.Append(period);
    mc_histogram.Append("/");
    mc_histogram.Append(type);
    mc_histogram.Append("/merged/DIMuon/MV_");
    mc_histogram.Append(finder);
    mc_histogram.Append("_");
    mc_histogram.Append(basename);
    if ( region.Length() > 0 ) {
      mc_histogram.Append("_");
      mc_histogram.Append(region);
    }

    mv_mc_histogram = "Histograms/mc/";
    mv_mc_histogram.Append(period);
    mv_mc_histogram.Append("/");
    mv_mc_histogram.Append(type);
    mv_mc_histogram.Append("/merged/DIMuon/MV_");
    mv_mc_histogram.Append(basename);
    if ( region.Length() > 0 ) {
      mv_mc_histogram.Append("_");
      mv_mc_histogram.Append(region);
    }
  }
  
  TH1D *mc_histo2 = (TH1D*)file->Get(mc_histogram);
  if ( mc_histo2 == 0) {
//     cout << "problems in getting mc_histogram: " << mc_histogram << endl;
    return kFALSE;
  }

  TH1D *mc_mv2 = (TH1D*)file->Get(mv_mc_histogram);
  if ( mc_mv2 == 0) {
//     cout << "problems in getting MV mc_histogram: " << mv_mc_histogram << endl;
    return kFALSE;
  }

  cout << "GPictureMaker::MakeCorrectionPlot for " << data_histogram << " for period " << period << endl;

//   cout << "directory: " << directory << endl;
//   cout << "histogram: " << histogram << " histo1->GetName(): " << histo1->GetName() << " histo1->GetTitle(): " << histo1->GetTitle() << endl;
//   cout << "mv_histogram: " << mv_histogram << " mv1->GetName(): " << mv1->GetName() << " mv1->GetTitle(): " << mv1->GetTitle() << endl;
//   cout << "histo1: " << histo1 << endl;
//   cout << "mv1: " << mv1 << endl;

  // set batch to true
  Bool_t batch = gROOT->IsBatch();
  if ( !batch )
    gROOT->SetBatch(kTRUE);
  
  // delete old canvas
  if ( fCanvas ) {
    delete fCanvas;
    fCanvas = 0;
  }
  
  // canvas
  if ( !fCanvas ) {
    fCanvas = new TCanvas("canvas","canvas",640,480);
  } 

  fCanvas->cd();
  fCanvas->Clear();
  fCanvas->SetLogy(0);
  
  gStyle->SetOptStat(10);
  
  TString histoname = data_histo1->GetName();
  TString histotitle = data_histo1->GetTitle();
  histotitle.ReplaceAll("data/","");
  
  TH1D *data_temphist = (TH1D*)data_histo1->Clone();
  data_temphist->Clear();
  data_temphist->Divide(data_histo1,data_mv1,1,1,"b");
  
  TH1D *mc_temphist = (TH1D*)mc_histo2->Clone();
  mc_temphist->Clear();
  mc_temphist->Divide(mc_histo2,mc_mv2,1,1,"b");
  
  data_temphist->Divide(mc_temphist);

  data_temphist->SetName(histoname);
  data_temphist->SetTitle(histotitle);
  data_temphist->GetYaxis()->SetTitle("Correction factor");
  
  data_temphist->SetMarkerColor(2);
  data_temphist->SetLineColor(4);
  data_temphist->SetMarkerStyle(8);
  data_temphist->SetMarkerSize(1.3);
  data_temphist->SetAxisRange(0,1.5,"Y");
  data_temphist->Draw("P0E0");

  if (option.Contains("STATS")) {
    fCanvas->Update();
    TPaveStats *stats = (TPaveStats*)(data_temphist->GetListOfFunctions()->FindObject("stats"));
    stats->SetX1NDC(0.68);
    stats->SetY1NDC(0.92);
    stats->SetX2NDC(0.98);
    stats->SetY2NDC(0.995);
  }

  // title pave text
  fCanvas->Update();
  TPaveText *titlepave = (TPaveText*)fCanvas->FindObject("title");
  if ( titlepave->GetX2NDC() > 0.67 )
    titlepave->SetX2NDC(0.67);
  
  gInclude->NicePlot(fCanvas);
  gInclude->NicePlot(fCanvas);

  GenHTMLPics(stream, fCanvas,histoname,directory,histotitle,option);
  
  // set error bars in x to default
  gStyle->SetErrorX(0.5);
  
  // delete old canvas
  if ( fCanvas ) {
    delete fCanvas;
    fCanvas = 0;
  }
  
  // restore batch level
  if ( !batch )
    gROOT->SetBatch(kFALSE);

  delete data_temphist;
  delete mc_temphist;
  
  return kTRUE;
}
  
//_____________________________________________________________

Bool_t GPictureMaker::MakeEfficiencyPlotMC(TFile *file, ofstream *stream, TString directory, TString basename, TString finder, TString period, TString region, TString type, TString option) {
  //
  // make mc efficiency plot

  // fill typelist
  TList  *typelist = new TList();
  if ( type.Contains(",") ) {
    TString temptype = type;

    char first;
    TString tempstring = "";
    // separate entries in types
    while ( (first = temptype(0)) ) {
      // remove first
      temptype.Remove(0,1);
      // append to temp or break in case of comma
      if ( first == 44 ) {
	typelist->Add(new TObjString(tempstring));
	tempstring = "";
      } else {
	tempstring.Append(first);
      }
    }
    if ( tempstring.Length() != 0 ) {
      typelist->Add(new TObjString(tempstring));
    }
  }

  TString histogram = "";
  TString mv_histogram = "";

  if ( type.Contains(",") ) {
    
    histogram = "Histograms/mc/";
    histogram.Append(period);
    histogram.Append("/merged/DIMuon/MV_");
    histogram.Append(finder);
    histogram.Append("_");
    histogram.Append(basename);
    if ( region.Length() > 0 ) {
      histogram.Append("_");
      histogram.Append(region);
    }
    TIter nexttype(typelist);
    while (TObjString *temptype = (TObjString*)nexttype() ) {
      histogram.Append("_");
      histogram.Append(temptype->GetString());
    }
    
    mv_histogram = "Histograms/mc/";
    mv_histogram.Append(period);
    mv_histogram.Append("/merged/DIMuon/MV_");
    mv_histogram.Append(basename);
    if ( region.Length() > 0 ) {
      mv_histogram.Append("_");
      mv_histogram.Append(region);
    }
    TIter nexttype2(typelist);
    while (TObjString *temptype2 = (TObjString*)nexttype2() ) {
      mv_histogram.Append("_");
      mv_histogram.Append(temptype2->GetString());
    }
  } else {
    histogram = "Histograms/mc/";
    histogram.Append(period);
    histogram.Append("/");
    histogram.Append(type);
    histogram.Append("/merged/DIMuon/MV_");
    histogram.Append(finder);
    histogram.Append("_");
    histogram.Append(basename);
    if ( region.Length() > 0 ) {
      histogram.Append("_");
      histogram.Append(region);
    }

    mv_histogram = "Histograms/mc/";
    mv_histogram.Append(period);
    mv_histogram.Append("/");
    mv_histogram.Append(type);
    mv_histogram.Append("/merged/DIMuon/MV_");
    mv_histogram.Append(basename);
    if ( region.Length() > 0 ) {
      mv_histogram.Append("_");
      mv_histogram.Append(region);
    }
  }
  
  TH1D *histo2 = (TH1D*)file->Get(histogram);
  if ( histo2 == 0) {
//     cout << "problems in getting histogram: " << histogram << endl;
    return kFALSE;
  }

  TH1D *mv2 = (TH1D*)file->Get(mv_histogram);
  if ( mv2 == 0) {
//     cout << "problems in getting MV histogram: " << mv_histogram << endl;
    return kFALSE;
  }

  cout << "GPictureMaker::MakeefficiencyPlotMC for " << histogram << " for period " << period << endl;

//   cout << "directory: " << directory << endl;
//   cout << "histogram: " << histogram << " histo2->GetName(): " << histo2->GetName() << " histo2->GetTitle(): " << histo2->GetTitle() << endl;
//   cout << "mv_histogram: " << mv_histogram << " mv2->GetName(): " << mv2->GetName() << " mv2->GetTitle(): " << mv2->GetTitle() << endl;
//   cout << "histo2: " << histo2 << endl;
//   cout << "mv2: " << mv2 << endl;

  // set batch to true
  Bool_t batch = gROOT->IsBatch();
  if ( !batch )
    gROOT->SetBatch(kTRUE);
  
  // delete old canvas
  if ( fCanvas ) {
    delete fCanvas;
    fCanvas = 0;
  }
  
  // canvas
  if ( !fCanvas ) {
    fCanvas = new TCanvas("canvas","canvas",640,480);
  } 
  
  fCanvas->cd();
  fCanvas->Clear();
  fCanvas->SetLogy(0);
  
  gStyle->SetOptStat(10);
  
  TString histoname = histo2->GetName();
  TString histotitle = histo2->GetTitle();

  TH1D *temphist = (TH1D*)histo2->Clone();
  temphist->Clear();
  temphist->Divide(histo2,mv2,1,1,"b");

  temphist->SetName(histoname);
  temphist->SetTitle(histotitle);
  temphist->GetYaxis()->SetTitle("Efficiency");
  
  temphist->SetMarkerColor(2);
  temphist->SetLineColor(4);
  temphist->SetMarkerStyle(8);
  temphist->SetMarkerSize(1.3);
  temphist->Draw("P0E0");

  if (option.Contains("STATS")) {
    fCanvas->Update();
    TPaveStats *stats = (TPaveStats*)(temphist->GetListOfFunctions()->FindObject("stats"));
    stats->SetX1NDC(0.68);
    stats->SetY1NDC(0.92);
    stats->SetX2NDC(0.98);
    stats->SetY2NDC(0.995);
  }

  // title pave text
  fCanvas->Update();
  TPaveText *titlepave = (TPaveText*)fCanvas->FindObject("title");
  if ( titlepave->GetX2NDC() > 0.67 )
    titlepave->SetX2NDC(0.67);

  gInclude->NicePlot(fCanvas);
  gInclude->NicePlot(fCanvas);

  GenHTMLPics(stream, fCanvas,histoname,directory,histotitle,option);
  
  // set error bars in x to default
  gStyle->SetErrorX(0.5);
  
  // delete old canvas
  if ( fCanvas ) {
    delete fCanvas;
    fCanvas = 0;
  }

  // restore batch level
  if ( !batch )
    gROOT->SetBatch(kFALSE);

  typelist->Delete();
  delete typelist;

  delete temphist;
  
  return kTRUE;
}

//_____________________________________________________________

Bool_t GPictureMaker::MakeSpecialCompleteEfficiency(TFile *file, TString directory, TString option) {
  //
  // make efficiency pictures
  if ( gDebug ) cout << endl << "GPictureMaker::MakeSpecialCompleteEfficiency() called" << endl << endl;

  TList *entries = new TList();
  Bool_t has_entry = kFALSE;

  TString temptopdir = directory;

  if ( temptopdir.BeginsWith(".") ) {
    temptopdir = "";
  } else if ( !temptopdir.EndsWith("/") && ( temptopdir.Length() != 0 ) ) {
    temptopdir.Append("/");
  }

  // make data efficiency plots
  TString tempdir = temptopdir;
  tempdir.Append("data");

  if ( MakeSpecialCompleteEfficiencyData(file,tempdir,option) ) {
    entries->Add(new TObjString("data"));
    has_entry = kTRUE;
  }

  // make mc efficiency plots
  tempdir = temptopdir;
  tempdir.Append("mc");

  if ( MakeSpecialCompleteEfficiencyMC(file,tempdir,option) ) {
    entries->Add(new TObjString("mc"));
    has_entry = kTRUE;
  }

  if ( has_entry ) {
    
    TString tempoption = option;
    tempoption.Append(",TOP");

    // start top html
    TString tempdir = directory;
    if ( tempdir.BeginsWith(".") ) {
      tempdir = "";
    } else if ( tempdir.EndsWith("/") && ( tempdir.Length() != 0 ) )
      tempdir.Remove(tempdir.Length()-1,1);
    // check whether tempdir exists, else generate
    gSystem->mkdir(tempdir.Data(),kTRUE);
    TString name = tempdir.Data();
    name.Append("/gallery.html");
    ofstream *top = new ofstream(name.Data());
    TString title = "Muon efficiency gallery for 96-00";
    if ( file->Get("Histograms/mc/03p-04p") ) {
      title = "Muon efficiency gallery for 03-04";
    }

    TString filename = "muon_efficiency_gallery";
    HTMLStart(top,title,filename,tempoption);

    TIter nextentry(entries);
    while (TObjString *entry = (TObjString*)nextentry() ) {
      TString link = entry->GetString();
      link.Append("/gallery.html");
      TString title = "";
      if ( link.Contains("data") ) {
	title.Append("Muon efficiency plots from data");
      } else if ( link.Contains("mc") ) {
	title.Append("Muon efficiency plots from MC");
      }	
	
      HTMLStreamTop(top,link,title,tempoption);
    }

    HTMLEnd(top,"../gallery.html",fTime,tempoption);
    delete top;  // add leading Histograms directory to input histograms
  
  }

  entries->Delete();
  delete entries;

  return has_entry;
}

//_____________________________________________________________

Bool_t GPictureMaker::MakeSpecialCompleteEfficiencyMC(TFile *file, TString directory, TString option) {
  //
  // make mc efficiency pictures
  if ( gDebug ) cout << endl << "GPictureMaker::MakeSpecialCompleteEfficiencyMC() called" << endl << endl;

  TList *entries = new TList();
  Bool_t has_entry = kFALSE;

  GHistogrammer grammer;
  TList *types = grammer.GetTypes();

  TString temptopdir = directory;

  if ( temptopdir.BeginsWith(".") ) {
    temptopdir = "";
  } else if ( !temptopdir.EndsWith("/") && ( temptopdir.Length() != 0 ) ) {
    temptopdir.Append("/");
  }

  // make mc efficiency plots for single type
  TIter nexttype(types);
  while (TObjString *type = (TObjString*)nexttype() ) {
    TString tempoption = option;
    option.Append(",MC");
    TString tempdir = temptopdir;
    tempdir.Append(type->GetString());
    if ( MakeSpecialCompleteEfficiencyMCType(file,tempdir,type->GetString(),tempoption) ) {
      entries->Add(new TObjString(type->GetString()));
      has_entry = kTRUE;
    }

  }

  // make mc efficiency plots for combination of two types
  TIter nexttype2(types);
  while (TObjString *type2 = (TObjString*)nexttype2() ) {
    TIter nexttype3(nexttype2);
    while (TObjString *type3 = (TObjString*)nexttype3() ) {

      TString tempoption = option;
      option.Append(",MC");

      TString temptype = type2->GetString();
      temptype.Append(",");
      temptype.Append(type3->GetString());

      TString tempdiradd = type2->GetString();
      tempdiradd.Append("_");
      tempdiradd.Append(type3->GetString());

      // make mc efficiency plots
      TString tempdir = temptopdir;
      tempdir.Append(tempdiradd);

      if ( MakeSpecialCompleteEfficiencyMCType(file,tempdir,temptype,tempoption) ) {
      entries->Add(new TObjString(tempdiradd));
      has_entry = kTRUE;
      }
    }
  }

  // make mc efficiency plots for combination of three types
  TIter nexttype4(types);
  while (TObjString *type4 = (TObjString*)nexttype4() ) {
    TIter nexttype5(nexttype4);
    while (TObjString *type5 = (TObjString*)nexttype5() ) {
      TIter nexttype6(nexttype5);
      while (TObjString *type6 = (TObjString*)nexttype6() ) {

	TString tempoption = option;
	option.Append(",MC");

	TString temptype = type4->GetString();
	temptype.Append(",");
	temptype.Append(type5->GetString());
	temptype.Append(",");
	temptype.Append(type6->GetString());

	TString tempdiradd = type4->GetString();
	tempdiradd.Append("_");
	tempdiradd.Append(type5->GetString());
	tempdiradd.Append("_");
	tempdiradd.Append(type6->GetString());

	// make mc efficiency plots
	TString tempdir = temptopdir;
	tempdir.Append(tempdiradd);
	
	if ( MakeSpecialCompleteEfficiencyMCType(file,tempdir,temptype,tempoption) ) {
	  entries->Add(new TObjString(tempdiradd));
	  has_entry = kTRUE;
	}
      }
    }
  }

  // make mc efficiency plots for combination of four types
  TIter nexttype7(types);
  while (TObjString *type7 = (TObjString*)nexttype7() ) {
    TIter nexttype8(nexttype7);
    while (TObjString *type8 = (TObjString*)nexttype8() ) {
      TIter nexttype9(nexttype8);
      while (TObjString *type9 = (TObjString*)nexttype9() ) {
	TIter nexttype10(nexttype9);
	while (TObjString *type10 = (TObjString*)nexttype10() ) {
	
	  TString tempoption = option;
	  option.Append(",MC");

	  TString temptype = type7->GetString();
	  temptype.Append(",");
	  temptype.Append(type8->GetString());
	  temptype.Append(",");
	  temptype.Append(type9->GetString());
	  temptype.Append(",");
	  temptype.Append(type10->GetString());

	  TString tempdiradd = type7->GetString();
	  tempdiradd.Append("_");
	  tempdiradd.Append(type8->GetString());
	  tempdiradd.Append("_");
	  tempdiradd.Append(type9->GetString());
	  tempdiradd.Append("_");
	  tempdiradd.Append(type10->GetString());

	  // make mc efficiency plots
	  TString tempdir = temptopdir;
	  tempdir.Append(tempdiradd);
	
	  if ( MakeSpecialCompleteEfficiencyMCType(file,tempdir,temptype,tempoption) ) {
	    entries->Add(new TObjString(tempdiradd));
	    has_entry = kTRUE;
	  }
	}
      }
    }
  }

  if ( has_entry ) {
    
    TString tempoption = option;
    tempoption.Append(",TOP");

    // start top html
    TString tempdir = directory;
    if ( tempdir.BeginsWith(".") ) {
      tempdir = "";
    } else if ( tempdir.EndsWith("/") && ( tempdir.Length() != 0 ) )
      tempdir.Remove(tempdir.Length()-1,1);
    // check whether tempdir exists, else generate
    gSystem->mkdir(tempdir.Data(),kTRUE);
    TString name = tempdir.Data();
    name.Append("/gallery.html");
    ofstream *top = new ofstream(name.Data());
    TString title = "Muon MC efficiency gallery for 96-00";
    if ( file->Get("Histograms/mc/03p-04p") ) {
      title = "Muon efficiency gallery for 03-04";
    }
    TString filename = "muon_mc_efficiency_gallery_";
    HTMLStart(top,title,filename,tempoption);

    TIter nextentry(entries);
    while (TObjString *entry = (TObjString*)nextentry() ) {
      TString link = entry->GetString();
      link.Append("/gallery.html");
      TString title = "";
      if ( link.Contains("b_c_lf_jpsi") ) {
	title.Append("Muon efficiency plots from b, c, lf and jpsi MC");
      } else if ( link.Contains("b_c_lf") ) {
	title.Append("Muon efficiency plots from b, c and lf MC");
      } else if ( link.Contains("b_c_jpsi") ) {
	title.Append("Muon efficiency plots from b, c and jpsi MC");
      } else if ( link.Contains("b_lf_jpsi") ) {
	title.Append("Muon efficiency plots from b, lf and jpsi MC");
      } else if ( link.Contains("c_lf_jpsi") ) {
	title.Append("Muon efficiency plots from c, lf and jpsi MC");
      } else if ( link.Contains("b_c") ) {
	title.Append("Muon efficiency plots from b and c MC");
      } else if ( link.Contains("b_lf") ) {
	title.Append("Muon efficiency plots from b and lf MC");
      } else if ( link.Contains("b_jpsi") ) {
	title.Append("Muon efficiency plots from b and jpsi MC");
      } else if ( link.Contains("c_lf") ) {
	title.Append("Muon efficiency plots from c and lf MC");
      } else if ( link.Contains("c_jpsi") ) {
	title.Append("Muon efficiency plots from c and jpsi MC");
      } else if ( link.Contains("lf_jpsi") ) {
	title.Append("Muon efficiency plots from lf and jpsi MC");
      } else if ( link.Contains("b") ) {
	title.Append("Muon efficiency plots from b MC");
      } else if ( link.Contains("c") ) {
	title.Append("Muon efficiency plots from c MC");
      } else if ( link.Contains("lf") ) {
	title.Append("Muon efficiency plots from lf MC");
      } else if ( link.Contains("jpsi") ) {
	title.Append("Muon efficiency plots from jpsi MC");
      }	
      HTMLStreamTop(top,link,title,tempoption);
    }

    HTMLEnd(top,"../gallery.html",fTime,tempoption);
    delete top;  // add leading Histograms directory to input histograms
  
  }

  entries->Delete();
  delete entries;

  return has_entry;
}

//_____________________________________________________________

Bool_t GPictureMaker::MakeSpecialCompleteEfficiencyMCType(TFile *file, TString directory, TString type, TString option) {
  //
  // make mc efficiency pictures for a type
  if ( gDebug ) cout << endl << "GPictureMaker::MakeSpecialCompleteEfficiencyMCType() called" << endl << endl;

  Bool_t has_entry = kFALSE;

  // check whether dir exists, else generate
  gSystem->mkdir(directory,kTRUE);

  // start html file
  TString tempdir = directory;
  if ( tempdir.BeginsWith(".") ) {
    tempdir = "";
  } else if ( tempdir.EndsWith("/") && ( tempdir.Length() != 0 ) )
    tempdir.Remove(tempdir.Length()-1,1);
  // check whether tempdir exists, else generate
  gSystem->mkdir(tempdir.Data(),kTRUE);
  TString filename = tempdir.Data();
  filename.Append("/gallery.html");
  ofstream *top = new ofstream(filename);
  HTMLStart(top,"Muon MC efficiency plots","MC_Efficiency_plots",option);

  // make data plots
  TIter nextbasename(fPlotsEfficiencyBasename);
  while ( TObjString *basename = (TObjString*)nextbasename() ) {
    TIter nextfinder(fPlotsEfficiencyFinder);
    while ( TObjString *finder = (TObjString*)nextfinder() ) {
      TIter nextregion(fPlotsEfficiencyRegion);
      while ( TObjString *region = (TObjString*)nextregion() ) {
	Bool_t temp_has_entry = kFALSE;
	temp_has_entry = MakeEfficiencyPlotMCComplete(file,top,directory,basename->GetString(),finder->GetString(),region->GetString(),type,option);
	if ( !has_entry )
	  has_entry = temp_has_entry;
      }
    }
  }

  
  HTMLEnd(top,"../gallery.html",fTime,option);
  delete top;  // add leading Histograms directory to input histograms
  
  return has_entry;
}

//_____________________________________________________________

Bool_t GPictureMaker::MakeSpecialCompleteEfficiencyData(TFile *file, TString directory, TString option) {
  //
  // make data efficiency pictures
  if ( gDebug ) cout << endl << "GPictureMaker::MakeSpecialCompleteEfficiencyData() called" << endl << endl;

  Bool_t has_entry = kFALSE;

  // check whether dir exists, else generate
  gSystem->mkdir(directory,kTRUE);

  // start html file
  TString tempdir = directory;
  if ( tempdir.BeginsWith(".") ) {
    tempdir = "";
  } else if ( tempdir.EndsWith("/") && ( tempdir.Length() != 0 ) )
    tempdir.Remove(tempdir.Length()-1,1);
  // check whether tempdir exists, else generate
  gSystem->mkdir(tempdir.Data(),kTRUE);
  TString filename = tempdir.Data();
  filename.Append("/gallery.html");
  ofstream *top = new ofstream(filename);
  HTMLStart(top,"Muon data efficiency plots","Data_Efficiency_plots",option);

  // make data plots
  TIter nextbasename(fPlotsEfficiencyBasename);
  while ( TObjString *basename = (TObjString*)nextbasename() ) {
    TIter nextfinder(fPlotsEfficiencyFinder);
    while ( TObjString *finder = (TObjString*)nextfinder() ) {
      TIter nextregion(fPlotsEfficiencyRegion);
      while ( TObjString *region = (TObjString*)nextregion() ) {
	Bool_t temp_has_entry = kFALSE;
	temp_has_entry = MakeEfficiencyPlotDataComplete(file,top,directory,basename->GetString(),finder->GetString(),region->GetString(),"",option);
	if ( !has_entry )
	  has_entry = temp_has_entry;
      }
    }
  }


  HTMLEnd(top,"../gallery.html",fTime,option);
  delete top;  // add leading Histograms directory to input histograms
  
  return has_entry;
}

//_____________________________________________________________

Bool_t GPictureMaker::MakeSpecialCompleteCorrection(TFile *file, TString directory, TString option) {
  //
  // make data efficiency pictures
  if ( gDebug ) cout << endl << "GPictureMaker::MakeSpecialCompleteCorrection() called" << endl << endl;

  Bool_t has_entry = kFALSE;

  // check whether dir exists, else generate
  gSystem->mkdir(directory,kTRUE);

  // start html file
  TString tempdir = directory;
  if ( tempdir.BeginsWith(".") ) {
    tempdir = "";
  } else if ( tempdir.EndsWith("/") && ( tempdir.Length() != 0 ) )
    tempdir.Remove(tempdir.Length()-1,1);
  // check whether tempdir exists, else generate
  gSystem->mkdir(tempdir.Data(),kTRUE);
  TString filename = tempdir.Data();
  filename.Append("/gallery.html");
  ofstream *top = new ofstream(filename);
  HTMLStart(top,"Muon efficiency correction factor plots","Muon_Coorection_plots",option);

  // make data plots
  TIter nextbasename(fPlotsEfficiencyBasename);
  while ( TObjString *basename = (TObjString*)nextbasename() ) {
    TIter nextfinder(fPlotsEfficiencyFinder);
    while ( TObjString *finder = (TObjString*)nextfinder() ) {
      TIter nextregion(fPlotsEfficiencyRegion);
      while ( TObjString *region = (TObjString*)nextregion() ) {
	Bool_t temp_has_entry = kFALSE;
	temp_has_entry = MakeCorrectionPlotComplete(file,top,directory,basename->GetString(),finder->GetString(),region->GetString(),"jpsi",option);
	if ( !has_entry )
	  has_entry = temp_has_entry;
      }
    }
  }


  HTMLEnd(top,"../gallery.html",fTime,option);
  delete top;  // add leading Histograms directory to input histograms
  
  return has_entry;
}
  
//_____________________________________________________________

Bool_t GPictureMaker::MakeEfficiencyPlotDataComplete(TFile *file, ofstream *stream, TString directory, TString basename, TString finder, TString region, TString type, TString option) {
  //
  // make data efficiency plot
  
  TString histogram = "Histograms/data/merged/DIMuon/MV_";
  histogram.Append(finder);
  histogram.Append("_");
  histogram.Append(basename);
  if ( region.Length() > 0 ) {
    histogram.Append("_");
    histogram.Append(region);
  }
  TString mv_histogram = "Histograms/data/merged/DIMuon/MV_";
  mv_histogram.Append(basename);
  if ( region.Length() > 0 ) {
    mv_histogram.Append("_");
    mv_histogram.Append(region);
  }
  TH1D *histo3 = (TH1D*)file->Get(histogram);
  if ( histo3 == 0) {
//     cout << "problems in getting histogram: " << histogram << endl;
    return kFALSE;
  }

  TH1D *mv3 = (TH1D*)file->Get(mv_histogram);
  if ( mv3 == 0) {
//     cout << "problems in getting MV histogram: " << mv_histogram << endl;
    return kFALSE;
  }

  cout << "GPictureMaker::MakeEfficiencyPlotDataComplete for " << histogram << endl;

//   cout << "directory: " << directory << endl;
//   cout << "histogram: " << histogram << " histo3->GetName(): " << histo3->GetName() << " histo3->GetTitle(): " << histo3->GetTitle() << endl;
//   cout << "mv_histogram: " << mv_histogram << " mv3->GetName(): " << mv3->GetName() << " mv3->GetTitle(): " << mv3->GetTitle() << endl;
//   cout << "histo3: " << histo3 << endl;
//   cout << "mv3: " << mv3 << endl;

  // set batch to true
  Bool_t batch = gROOT->IsBatch();
  if ( !batch )
    gROOT->SetBatch(kTRUE);
  
  // delete old canvas
  if ( fCanvas ) {
    delete fCanvas;
    fCanvas = 0;
  }
  
  // canvas
  if ( !fCanvas ) {
    fCanvas = new TCanvas("canvas","canvas",640,480);
  } 

  fCanvas->cd();
  fCanvas->Clear();
  fCanvas->SetLogy(0);
  
  gStyle->SetOptStat(10);
  
  TString histoname = histo3->GetName();
  TString histotitle = histo3->GetTitle();
  
  TH1D *temphist = (TH1D*)histo3->Clone();
  temphist->Clear();
  temphist->Divide(histo3,mv3,1,1,"b");
  
  temphist->SetName(histoname);
  temphist->SetTitle(histotitle);
  temphist->GetYaxis()->SetTitle("Efficiency");
  
  temphist->SetMarkerColor(2);
  temphist->SetLineColor(4);
  temphist->SetMarkerStyle(8);
  temphist->SetMarkerSize(1.3);
  temphist->Draw("P0E0");

  if (option.Contains("STATS")) {
    fCanvas->Update();
    TPaveStats *stats = (TPaveStats*)(temphist->GetListOfFunctions()->FindObject("stats"));
    stats->SetX1NDC(0.68);
    stats->SetY1NDC(0.92);
    stats->SetX2NDC(0.98);
    stats->SetY2NDC(0.995);
  }

  // title pave text
  fCanvas->Update();
  TPaveText *titlepave = (TPaveText*)fCanvas->FindObject("title");
  if ( titlepave->GetX2NDC() > 0.67 )
    titlepave->SetX2NDC(0.67);
  
  gInclude->NicePlot(fCanvas);
  gInclude->NicePlot(fCanvas);

  GenHTMLPics(stream, fCanvas,histoname,directory,histotitle,option);
  
  // set error bars in x to default
  gStyle->SetErrorX(0.5);
  
  // delete old canvas
  if ( fCanvas ) {
    delete fCanvas;
    fCanvas = 0;
  }
  
  // restore batch level
  if ( !batch )
    gROOT->SetBatch(kFALSE);
  
  delete temphist;
  
  return kTRUE;
}
  
//_____________________________________________________________

Bool_t GPictureMaker::MakeCorrectionPlotComplete(TFile *file, ofstream *stream, TString directory, TString basename, TString finder, TString region, TString type, TString option) {
  //
  // make muon efficiency correction factor plots
  
  TString data_histogram = "Histograms/data/merged/DIMuon/MV_";
  data_histogram.Append(finder);
  data_histogram.Append("_");
  data_histogram.Append(basename);
  if ( region.Length() > 0 ) {
    data_histogram.Append("_");
    data_histogram.Append(region);
  }
  TString mv_data_histogram = "Histograms/data/merged/DIMuon/MV_";
  mv_data_histogram.Append(basename);
  if ( region.Length() > 0 ) {
    mv_data_histogram.Append("_");
    mv_data_histogram.Append(region);
  }
  TH1D *data_histo3 = (TH1D*)file->Get(data_histogram);
  if ( data_histo3 == 0) {
//     cout << "problems in getting data_histogram: " << data_histogram << endl;
    return kFALSE;
  }

  TH1D *data_mv3 = (TH1D*)file->Get(mv_data_histogram);
  if ( data_mv3 == 0) {
//     cout << "problems in getting MV data_histogram: " << mv_data_histogram << endl;
    return kFALSE;
  }

  // fill typelist
  TList  *typelist = new TList();
  if ( type.Contains(",") ) {
    TString temptype = type;

    char first;
    TString tempstring = "";
    // separate entries in types
    while ( (first = temptype(0)) ) {
      // remove first
      temptype.Remove(0,1);
      // append to temp or break in case of comma
      if ( first == 44 ) {
	typelist->Add(new TObjString(tempstring));
	tempstring = "";
      } else {
	tempstring.Append(first);
      }
    }
    if ( tempstring.Length() != 0 ) {
      typelist->Add(new TObjString(tempstring));
    }
  }

  TString mc_histogram = "";
  TString mv_mc_histogram = "";

  if ( type.Contains(",") ) {
    
    mc_histogram = "Histograms/mc/merged/merged/DIMuon/MV_";
    mc_histogram.Append(finder);
    mc_histogram.Append("_");
    mc_histogram.Append(basename);
    if ( region.Length() > 0 ) {
      mc_histogram.Append("_");
      mc_histogram.Append(region);
    }
    TIter nexttype(typelist);
    while (TObjString *temptype = (TObjString*)nexttype() ) {
      mc_histogram.Append("_");
      mc_histogram.Append(temptype->GetString());
    }
    
    mv_mc_histogram = "Histograms/mc/merged/merged/DIMuon/MV_";
    mv_mc_histogram.Append(basename);
    if ( region.Length() > 0 ) {
      mv_mc_histogram.Append("_");
      mv_mc_histogram.Append(region);
    }
    TIter nexttype2(typelist);
    while (TObjString *temptype2 = (TObjString*)nexttype2() ) {
      mv_mc_histogram.Append("_");
      mv_mc_histogram.Append(temptype2->GetString());
    }
  } else {
    mc_histogram = "Histograms/mc/merged/";
    mc_histogram.Append(type);
    mc_histogram.Append("/DIMuon/MV_");
    mc_histogram.Append(finder);
    mc_histogram.Append("_");
    mc_histogram.Append(basename);
    if ( region.Length() > 0 ) {
      mc_histogram.Append("_");
      mc_histogram.Append(region);
    }

    mv_mc_histogram = "Histograms/mc/merged/";
    mv_mc_histogram.Append(type);
    mv_mc_histogram.Append("/DIMuon/MV_");
    mv_mc_histogram.Append(basename);
    if ( region.Length() > 0 ) {
      mv_mc_histogram.Append("_");
      mv_mc_histogram.Append(region);
    }
  }
  
  TH1D *mc_histo4 = (TH1D*)file->Get(mc_histogram);
  if ( mc_histo4 == 0) {
//     cout << "problems in getting mc_histogram: " << mc_histogram << endl;
    return kFALSE;
  }

  TH1D *mc_mv4 = (TH1D*)file->Get(mv_mc_histogram);
  if ( mc_mv4 == 0) {
//     cout << "problems in getting MV mc_histogram: " << mv_mc_histogram << endl;
    return kFALSE;
  }

  cout << "GPictureMaker::MakeCorrectionPlotComplete for " << data_histogram << endl;

//   cout << "directory: " << directory << endl;
//   cout << "histogram: " << histogram << " histo3->GetName(): " << histo3->GetName() << " histo3->GetTitle(): " << histo3->GetTitle() << endl;
//   cout << "mv_histogram: " << mv_histogram << " mv3->GetName(): " << mv3->GetName() << " mv3->GetTitle(): " << mv3->GetTitle() << endl;
//   cout << "histo3: " << histo3 << endl;
//   cout << "mv3: " << mv3 << endl;

  // set batch to true
  Bool_t batch = gROOT->IsBatch();
  if ( !batch )
    gROOT->SetBatch(kTRUE);
  
  // delete old canvas
  if ( fCanvas ) {
    delete fCanvas;
    fCanvas = 0;
  }
  
  // canvas
  if ( !fCanvas ) {
    fCanvas = new TCanvas("canvas","canvas",640,480);
  } 

  fCanvas->cd();
  fCanvas->Clear();
  fCanvas->SetLogy(0);
  
  gStyle->SetOptStat(10);
  
  TString histoname = data_histo3->GetName();
  TString histotitle = data_histo3->GetTitle();
  histotitle.ReplaceAll("data/","");
  
  TH1D *data_temphist = (TH1D*)data_histo3->Clone();
  data_temphist->Clear();
  data_temphist->Divide(data_histo3,data_mv3,1,1,"b");

  TH1D *mc_temphist = (TH1D*)mc_histo4->Clone();
  mc_temphist->Clear();
  mc_temphist->Divide(mc_histo4,mc_mv4,1,1,"b");
  
  data_temphist->Divide(mc_temphist);

  data_temphist->SetName(histoname);
  data_temphist->SetTitle(histotitle);
  data_temphist->GetYaxis()->SetTitle("Correction factor");
  
  data_temphist->SetMarkerColor(2);
  data_temphist->SetLineColor(4);
  data_temphist->SetMarkerStyle(8);
  data_temphist->SetMarkerSize(1.3);
  data_temphist->SetAxisRange(0,1.5,"Y");
  data_temphist->Draw("P0E0");

  if (option.Contains("STATS")) {
    fCanvas->Update();
    TPaveStats *stats = (TPaveStats*)(data_temphist->GetListOfFunctions()->FindObject("stats"));
    stats->SetX1NDC(0.68);
    stats->SetY1NDC(0.92);
    stats->SetX2NDC(0.98);
    stats->SetY2NDC(0.995);
  }

  // title pave text
  fCanvas->Update();
  TPaveText *titlepave = (TPaveText*)fCanvas->FindObject("title");
  if ( titlepave->GetX2NDC() > 0.67 )
    titlepave->SetX2NDC(0.67);
  
  gInclude->NicePlot(fCanvas);
  gInclude->NicePlot(fCanvas);

  GenHTMLPics(stream, fCanvas,histoname,directory,histotitle,option);
  
  // set error bars in x to default
  gStyle->SetErrorX(0.5);
  
  // delete old canvas
  if ( fCanvas ) {
    delete fCanvas;
    fCanvas = 0;
  }
  
  // restore batch level
  if ( !batch )
    gROOT->SetBatch(kFALSE);
  
  delete data_temphist;
  delete mc_temphist;
  
  return kTRUE;
}
  
//_____________________________________________________________

Bool_t GPictureMaker::MakeEfficiencyPlotMCComplete(TFile *file, ofstream *stream, TString directory, TString basename, TString finder, TString region, TString type, TString option) {
  //
  // make mc efficiency plot

  // fill typelist
  TList  *typelist = new TList();
  if ( type.Contains(",") ) {
    TString temptype = type;

    char first;
    TString tempstring = "";
    // separate entries in types
    while ( (first = temptype(0)) ) {
      // remove first
      temptype.Remove(0,1);
      // append to temp or break in case of comma
      if ( first == 44 ) {
	typelist->Add(new TObjString(tempstring));
	tempstring = "";
      } else {
	tempstring.Append(first);
      }
    }
    if ( tempstring.Length() != 0 ) {
      typelist->Add(new TObjString(tempstring));
    }
  }

  TString histogram = "";
  TString mv_histogram = "";

  if ( type.Contains(",") ) {
    
    histogram = "Histograms/mc/merged/merged/DIMuon/MV_";
    histogram.Append(finder);
    histogram.Append("_");
    histogram.Append(basename);
    if ( region.Length() > 0 ) {
      histogram.Append("_");
      histogram.Append(region);
    }
    TIter nexttype(typelist);
    while (TObjString *temptype = (TObjString*)nexttype() ) {
      histogram.Append("_");
      histogram.Append(temptype->GetString());
    }
    
    mv_histogram = "Histograms/mc/merged/merged/DIMuon/MV_";
    mv_histogram.Append(basename);
    if ( region.Length() > 0 ) {
      mv_histogram.Append("_");
      mv_histogram.Append(region);
    }
    TIter nexttype2(typelist);
    while (TObjString *temptype2 = (TObjString*)nexttype2() ) {
      mv_histogram.Append("_");
      mv_histogram.Append(temptype2->GetString());
    }
  } else {
    histogram = "Histograms/mc/merged/";
    histogram.Append(type);
    histogram.Append("/DIMuon/MV_");
    histogram.Append(finder);
    histogram.Append("_");
    histogram.Append(basename);
    if ( region.Length() > 0 ) {
      histogram.Append("_");
      histogram.Append(region);
    }

    mv_histogram = "Histograms/mc/merged/";
    mv_histogram.Append(type);
    mv_histogram.Append("/DIMuon/MV_");
    mv_histogram.Append(basename);
    if ( region.Length() > 0 ) {
      mv_histogram.Append("_");
      mv_histogram.Append(region);
    }
  }
  
  TH1D *histo4 = (TH1D*)file->Get(histogram);
  if ( histo4 == 0) {
//     cout << "problems in getting histogram: " << histogram << endl;
    return kFALSE;
  }

  TH1D *mv4 = (TH1D*)file->Get(mv_histogram);
  if ( mv4 == 0) {
//     cout << "problems in getting MV histogram: " << mv_histogram << endl;
    return kFALSE;
  }

  cout << "GPictureMaker::MakeefficiencyPlotMCComplete for " << histogram << endl;

//   cout << "directory: " << directory << endl;
//   cout << "histogram: " << histogram << " histo4->GetName(): " << histo4->GetName() << " histo4->GetTitle(): " << histo4->GetTitle() << endl;
//   cout << "mv_histogram: " << mv_histogram << " mv4->GetName(): " << mv4->GetName() << " mv4->GetTitle(): " << mv4->GetTitle() << endl;
//   cout << "histo4: " << histo4 << endl;
//   cout << "mv4: " << mv4 << endl;
  

  // set batch to true
  Bool_t batch = gROOT->IsBatch();
  if ( !batch )
    gROOT->SetBatch(kTRUE);
  
  // delete old canvas
  if ( fCanvas ) {
    delete fCanvas;
    fCanvas = 0;
  }
  
  // canvas
  if ( !fCanvas ) {
    fCanvas = new TCanvas("canvas","canvas",640,480);
  } 
  
  fCanvas->cd();
  fCanvas->Clear();
  fCanvas->SetLogy(0);
  
  gStyle->SetOptStat(10);
  
  TString histoname = histo4->GetName();
  TString histotitle = histo4->GetTitle();

  TH1D *temphist = (TH1D*)histo4->Clone();
  temphist->Clear();
  temphist->Divide(histo4,mv4,1,1,"b");

  temphist->SetName(histoname);
  temphist->SetTitle(histotitle);
  temphist->GetYaxis()->SetTitle("Efficiency");

  temphist->SetMarkerColor(2);
  temphist->SetLineColor(4);
  temphist->SetMarkerStyle(8);
  temphist->SetMarkerSize(1.3);
  temphist->Draw("P0E0");

  if (option.Contains("STATS")) {
    fCanvas->Update();
    TPaveStats *stats = (TPaveStats*)(temphist->GetListOfFunctions()->FindObject("stats"));
    stats->SetX1NDC(0.68);
    stats->SetY1NDC(0.92);
    stats->SetX2NDC(0.98);
    stats->SetY2NDC(0.995);
  }

  // title pave text
  fCanvas->Update();
  TPaveText *titlepave = (TPaveText*)fCanvas->FindObject("title");
  if ( titlepave->GetX2NDC() > 0.67 )
    titlepave->SetX2NDC(0.67);

  gInclude->NicePlot(fCanvas);
  gInclude->NicePlot(fCanvas);

  GenHTMLPics(stream, fCanvas,histoname,directory,histotitle,option);
  
  // set error bars in x to default
  gStyle->SetErrorX(0.5);
  
  // delete old canvas
  if ( fCanvas ) {
    delete fCanvas;
    fCanvas = 0;
  }

  // restore batch level
  if ( !batch )
    gROOT->SetBatch(kFALSE);

  typelist->Delete();
  delete typelist;

  delete temphist;
  
  return kTRUE;
}
  
//_____________________________________________________________

Bool_t GPictureMaker::InitLists() {
  //
  // init lists for plot generation
  if ( gDebug ) cout << endl << "GPictureMaker::InitLists called" << endl << endl;

  fCLFDraw                = kFALSE;
  fPicturesPS             = kTRUE;
  fPicturesGIF            = kTRUE;
  fPicturesJPG            = kTRUE;
  fPicturesEPS            = kTRUE;
  fPicturesPeriods        = kTRUE;
  fPicturesPtRel          = kTRUE;
  fPicturesImpact         = kFALSE;
  fPicturesLumi           = kTRUE;
  fPicturesPtRel_1        = "MJMatch/PtRel_JetMinMu";
  fPicturesPtRel_2        = "MJMatch/PtRel_0_5_7_JetMinMu";
  fPicturesPtRelMCOnly    = kTRUE;
  fPicturesImpact_1         = "";
  fPictures1D             = kTRUE;
  fPictures2D             = kTRUE;
  fPicturesEff            = kFALSE;

  // init lists
  Bool_t comp_muon        = kTRUE;
  Bool_t comp_ptrel       = kTRUE;
  Bool_t comp_jet         = kTRUE;
  Bool_t comp_mjmatch     = kTRUE;
  Bool_t comp_cal         = kTRUE;
  Bool_t comp_tracks      = kTRUE;
  Bool_t comp_trigger     = kTRUE;
  Bool_t comp_zufo        = kTRUE;
  Bool_t comp_sinistra    = kTRUE;
  Bool_t comp_disonly     = kTRUE;
  Bool_t comp_phponly     = kTRUE;
  Bool_t ONED_dimuon      = kTRUE;
  Bool_t ONED_track       = kTRUE;
  Bool_t ONED_muon        = kTRUE;
  
  Bool_t ONEDMC_dimuon    = kTRUE;
  Bool_t ONEDMC_mc        = kTRUE;
  Bool_t ONEDMC_track     = kTRUE;
  Bool_t ONEDMC_muon      = kTRUE;
  
  Bool_t TWOD_mjmatch     = kTRUE;
  Bool_t TWODMC_cal       = kTRUE;
  Bool_t TWODMC_zufo      = kTRUE;
  Bool_t TWODMC_mc        = kTRUE;
  Bool_t TWODMC_muon      = kTRUE;
  Bool_t TWODMC_mjmatch   = kTRUE;
  
  Bool_t TWODMCzoomed_mc  = kTRUE;
  
  Bool_t EfficiencyFull   = kFALSE;
//    Reading Cards   under construction!!!
//    fPicturesGIF = gCards->GetPicturesGIF();
//    fPicturesJPG = gCards->GetPicturesJPG();
//    fPicturesEPS = gCards->GetPicturesEPS();
//    comp_disonly  = gCards->GetPicturesCompdisonly();
//    comp_phponly  = gCards->GetPicturesCompphponly();
  
//    comp_ptrel     = gCards->GetPicturesCompptrel();
//    comp_muon      = gCards->GetPicturesCompmuon();
//    comp_jet       = gCards->GetPicturesCompjet();
//    comp_mjmatch   = gCards->GetPicturesCompmjmatch();
//    comp_cal       = gCards->GetPicturesCompcal();
//    comp_tracks    = gCards->GetPicturesComptracks();
//    comp_trigger   = gCards->GetPicturesComptrigger();
//    comp_zufo      = gCards->GetPicturesCompzufo();
//    comp_sinistra  = gCards->GetPicturesCompsinistra();

//    ONED_dimuon      = gCards->GetPicturesONEDdimuon();    
//    ONED_track       = gCards->GetPicturesONEDtrack(); 
//    ONED_muon        = gCards->GetPicturesONEDmuon();  
  		     			               
//    ONEDMC_dimuon    = gCards->GetPicturesONEDMCdimuon();  
//    ONEDMC_mc        = gCards->GetPicturesONEDMCmc();      
//    ONEDMC_track     = gCards->GetPicturesONEDMCtrack();   
//    ONEDMC_muon      = gCards->GetPicturesONEDMCmuon();    
  		     			               
//    TWOD_mjmatch     = gCards->GetPicturesTWODmjmatch(); 
//    TWODMC_cal       = gCards->GetPicturesTWODMCcal();
//    TWODMC_zufo      = gCards->GetPicturesTWODMCzufo();  
//    TWODMC_mc        = gCards->GetPicturesTWODMCmc(); 
//    TWODMC_muon      = gCards->GetPicturesTWODMCmuon();   
//    TWODMC_mjmatch   = gCards->GetPicturesTWODMCmjmatch(); 
  		     			               
//    TWODMCzoomed_mc  = gCards->GetPicturesTWODMCzoomedmc();
  		     			               
//    EfficiencyFull   = gCards->GetPicturesEfficiencyFull();

  // list of ptrel plots
  fPlotsPtRel = new TList();
  fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_JetMinMu"));
  fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_JetMinMu_Forward"));
  fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_JetMinMu_Barrel"));
  fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_JetMinMu_Rear"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_Forward"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_Barrel"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_Rear"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_4_8"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_4_8_JetMinMu"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_10"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_10_JetMinMu"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_20"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_20_JetMinMu"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_3_6"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_3_6_JetMinMu"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_Forward"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_Barrel"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_Rear"));
  fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_JetMinMu"));
  fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_JetMinMu_Forward"));
  fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_JetMinMu_Barrel"));
  fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_JetMinMu_Rear"));

//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_MPMATCHMUBAC"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_MPMATCHMUBAC_JetMinMu"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_MPMATCHMUBAC_Forward"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_MPMATCHMUBAC_JetMinMu_Forward"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_MPMATCHNOTMUBAC"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_MPMATCHNOTMUBAC_JetMinMu"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_MPMATCHNOTMUBAC_Forward"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_MPMATCHNOTMUBAC_JetMinMu_Forward"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_NOTMPMATCHMUBAC"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_NOTMPMATCHMUBAC_JetMinMu"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_NOTMPMATCHMUBAC_Forward"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_NOTMPMATCHMUBAC_JetMinMu_Forward"));

//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_BREMATMUBAC"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_BREMATMUBAC_JetMinMu"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_BREMATMUBAC_Barrel"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_BREMATMUBAC_JetMinMu_Barrel"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_BREMATMUBAC_Rear"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_BREMATMUBAC_JetMinMu_Rear"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_BREMATNOTMUBAC"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_BREMATNOTMUBAC_JetMinMu"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_BREMATNOTMUBAC_Barrel"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_BREMATNOTMUBAC_JetMinMu_Barrel"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_BREMATNOTMUBAC_Rear"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_BREMATNOTMUBAC_JetMinMu_Rear"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_NOTBREMATMUBAC"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_NOTBREMATMUBAC_JetMinMu"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_NOTBREMATMUBAC_Barrel"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_NOTBREMATMUBAC_JetMinMu_Barrel"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_NOTBREMATMUBAC_Rear"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_NOTBREMATMUBAC_JetMinMu_Rear"));

  if (comp_ptrel) {
    fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_CrossMuonPt_Bin1_JetMinMu"));
    fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_CrossMuonPt_Bin2_JetMinMu"));
    fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_CrossMuonPt_Bin3_JetMinMu"));
    fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_CrossMuonPt_Bin4_JetMinMu"));
    fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_CrossMuonPt_Bin1_JetMinMu"));
    fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_CrossMuonPt_Bin2_JetMinMu"));
    fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_CrossMuonPt_Bin3_JetMinMu"));
    fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_CrossMuonPt_Bin4_JetMinMu"));
    fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_CrossMuonEta_Bin1_JetMinMu"));
    fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_CrossMuonEta_Bin2_JetMinMu"));
    fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_CrossMuonEta_Bin3_JetMinMu"));
    fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_CrossMuonEta_Bin4_JetMinMu"));
    fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_CrossMuonEta_Bin1_JetMinMu"));
    fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_CrossMuonEta_Bin2_JetMinMu"));
    fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_CrossMuonEta_Bin3_JetMinMu"));
    fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_CrossMuonEta_Bin4_JetMinMu"));

//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_CrossMuonPt_Bin1"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_CrossMuonPt_Bin2"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_CrossMuonPt_Bin3"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_CrossMuonPt_Bin4"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_CrossMuonPt_Bin1"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_CrossMuonPt_Bin2"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_CrossMuonPt_Bin3"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_CrossMuonPt_Bin4"));

//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_CrossMuonEta_Bin1"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_CrossMuonEta_Bin2"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_CrossMuonEta_Bin3"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_CrossMuonEta_Bin4"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_CrossMuonEta_Bin1"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_CrossMuonEta_Bin2"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_CrossMuonEta_Bin3"));
//   fPlotsPtRel->Add(new TObjString("MJMatch/PtRel_0_5_7_CrossMuonEta_Bin4"));
  }
  
  // list of impact plots
  fPlotsImpact = new TList();
  fPlotsImpact->Add(new TObjString("Muons/2DBeamSpotImpact"));

  // list of comparison plots
  fPlotsComparison = new TList();

  if ( comp_mjmatch ) {
    fPlotsComparison->Add(new TObjString("MJMatch/PtRel"));
    fPlotsComparison->Add(new TObjString("MJMatch/PtRel_JetMinMu"));
    fPlotsComparison->Add(new TObjString("MJMatch/PtRel_Forward"));
    fPlotsComparison->Add(new TObjString("MJMatch/PtRel_JetMinMu_Forward"));
    fPlotsComparison->Add(new TObjString("MJMatch/PtRel_Barrel"));
    fPlotsComparison->Add(new TObjString("MJMatch/PtRel_JetMinMu_Barrel"));
    fPlotsComparison->Add(new TObjString("MJMatch/PtRel_Rear"));
    fPlotsComparison->Add(new TObjString("MJMatch/PtRel_JetMinMu_Rear"));
    fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_4_8"));
    fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_4_8_JetMinMu"));
    fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_10"));
    fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_10_JetMinMu"));
    fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_20"));
    fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_20_JetMinMu"));
    fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_3_6"));
    fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_3_6_JetMinMu"));
    fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7"));
    fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_JetMinMu"));
    fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_Forward"));
    fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_JetMinMu_Forward"));
    fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_Barrel"));
    fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_JetMinMu_Barrel"));
    fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_Rear"));
    fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_JetMinMu_Rear"));

//     fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_MPMATCHMUBAC"));
//     fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_MPMATCHMUBAC_JetMinMu"));
//     fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_MPMATCHMUBAC_Forward"));
//     fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_MPMATCHMUBAC_JetMinMu_Forward"));
//     fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_MPMATCHNOTMUBAC"));
//     fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_MPMATCHNOTMUBAC_JetMinMu"));
//     fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_MPMATCHNOTMUBAC_Forward"));
//     fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_MPMATCHNOTMUBAC_JetMinMu_Forward"));
//     fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_NOTMPMATCHMUBAC"));
//     fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_NOTMPMATCHMUBAC_JetMinMu"));
//     fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_NOTMPMATCHMUBAC_Forward"));
//     fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_NOTMPMATCHMUBAC_JetMinMu_Forward"));

//     fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_BREMATMUBAC"));
//     fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_BREMATMUBAC_JetMinMu"));
//     fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_BREMATMUBAC_Barrel"));
//     fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_BREMATMUBAC_JetMinMu_Barrel"));
//     fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_BREMATMUBAC_Rear"));
//     fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_BREMATMUBAC_JetMinMu_Rear"));
//     fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_BREMATNOTMUBAC"));
//     fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_BREMATNOTMUBAC_JetMinMu"));
//     fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_BREMATNOTMUBAC_Barrel"));
//     fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_BREMATNOTMUBAC_JetMinMu_Barrel"));
//     fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_BREMATNOTMUBAC_Rear"));
//     fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_BREMATNOTMUBAC_JetMinMu_Rear"));
//     fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_NOTBREMATMUBAC"));
//     fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_NOTBREMATMUBAC_JetMinMu"));
//     fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_NOTBREMATMUBAC_Barrel"));
//     fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_NOTBREMATMUBAC_JetMinMu_Barrel"));
//     fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_NOTBREMATMUBAC_Rear"));
//     fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_NOTBREMATMUBAC_JetMinMu_Rear"));

  fPlotsComparison->Add(new TObjString("MJMatch/PtRel_CrossMuonPt_Bin1_JetMinMu"));
  fPlotsComparison->Add(new TObjString("MJMatch/PtRel_CrossMuonPt_Bin2_JetMinMu"));
  fPlotsComparison->Add(new TObjString("MJMatch/PtRel_CrossMuonPt_Bin3_JetMinMu"));
  fPlotsComparison->Add(new TObjString("MJMatch/PtRel_CrossMuonPt_Bin4_JetMinMu"));
  fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_CrossMuonPt_Bin1_JetMinMu"));
  fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_CrossMuonPt_Bin2_JetMinMu"));
  fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_CrossMuonPt_Bin3_JetMinMu"));
  fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_CrossMuonPt_Bin4_JetMinMu"));
  fPlotsComparison->Add(new TObjString("MJMatch/PtRel_CrossMuonEta_Bin1_JetMinMu"));
  fPlotsComparison->Add(new TObjString("MJMatch/PtRel_CrossMuonEta_Bin2_JetMinMu"));
  fPlotsComparison->Add(new TObjString("MJMatch/PtRel_CrossMuonEta_Bin3_JetMinMu"));
  fPlotsComparison->Add(new TObjString("MJMatch/PtRel_CrossMuonEta_Bin4_JetMinMu"));
  fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_CrossMuonEta_Bin1_JetMinMu"));
  fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_CrossMuonEta_Bin2_JetMinMu"));
  fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_CrossMuonEta_Bin3_JetMinMu"));
  fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_CrossMuonEta_Bin4_JetMinMu"));

//   fPlotsComparison->Add(new TObjString("MJMatch/PtRel_CrossMuonPt_Bin1"));
//   fPlotsComparison->Add(new TObjString("MJMatch/PtRel_CrossMuonPt_Bin2"));
//   fPlotsComparison->Add(new TObjString("MJMatch/PtRel_CrossMuonPt_Bin3"));
//   fPlotsComparison->Add(new TObjString("MJMatch/PtRel_CrossMuonPt_Bin4"));
//   fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_CrossMuonPt_Bin1"));
//   fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_CrossMuonPt_Bin2"));
//   fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_CrossMuonPt_Bin3"));
//   fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_CrossMuonPt_Bin4"));

//   fPlotsComparison->Add(new TObjString("MJMatch/PtRel_CrossMuonEta_Bin1"));
//   fPlotsComparison->Add(new TObjString("MJMatch/PtRel_CrossMuonEta_Bin2"));
//   fPlotsComparison->Add(new TObjString("MJMatch/PtRel_CrossMuonEta_Bin3"));
//   fPlotsComparison->Add(new TObjString("MJMatch/PtRel_CrossMuonEta_Bin4"));
//   fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_CrossMuonEta_Bin1"));
//   fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_CrossMuonEta_Bin2"));
//   fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_CrossMuonEta_Bin3"));
//   fPlotsComparison->Add(new TObjString("MJMatch/PtRel_0_5_7_CrossMuonEta_Bin4"));
  }
  fPlotsComparison->Add(new TObjString("MJMatch/NperEv"));

  // list of sinistra plots
  if ( comp_sinistra && !comp_phponly) {
    fPlotsComparison->Add(new TObjString("Sinistra/YEL"));
    fPlotsComparison->Add(new TObjString("Sinistra/Q2"));
    fPlotsComparison->Add(new TObjString("Sinistra/Q2log"));
    fPlotsComparison->Add(new TObjString("Sinistra/Xlog"));
    fPlotsComparison->Add(new TObjString("Sinistra/EE"));
    fPlotsComparison->Add(new TObjString("Sinistra/ThetaE"));    

  }
  
  fPlotsComparison->Add(new TObjString("Muons/PtChosen"));
  fPlotsComparison->Add(new TObjString("Muons/EtaChosen"));

  if ( comp_muon ) {
    fPlotsComparison->Add(new TObjString("Muons/SpecialFinder"));
    fPlotsComparison->Add(new TObjString("Muons/PtChosenFine2"));
    fPlotsComparison->Add(new TObjString("Muons/PtChosenFine4"));
    fPlotsComparison->Add(new TObjString("Muons/PtChosenFine8"));
    fPlotsComparison->Add(new TObjString("Muons/PtChosenFine16"));
    fPlotsComparison->Add(new TObjString("Muons/EtaChosenLarge"));
    fPlotsComparison->Add(new TObjString("Muons/NMU"));
    fPlotsComparison->Add(new TObjString("Muons/NMUForward"));
    fPlotsComparison->Add(new TObjString("Muons/NMUBarrel"));
    fPlotsComparison->Add(new TObjString("Muons/NMURear"));
    fPlotsComparison->Add(new TObjString("Muons/Prob"));
    fPlotsComparison->Add(new TObjString("Muons/ProbForward"));
    fPlotsComparison->Add(new TObjString("Muons/ProbBarrel"));
    fPlotsComparison->Add(new TObjString("Muons/ProbRear"));
    fPlotsComparison->Add(new TObjString("Muons/P"));
    fPlotsComparison->Add(new TObjString("Muons/PForward"));
    fPlotsComparison->Add(new TObjString("Muons/PBarrel"));
    fPlotsComparison->Add(new TObjString("Muons/PRear"));
    fPlotsComparison->Add(new TObjString("Muons/PtForward"));
    fPlotsComparison->Add(new TObjString("Muons/PtBarrel"));
    fPlotsComparison->Add(new TObjString("Muons/PtRear"));
    fPlotsComparison->Add(new TObjString("Muons/Px"));
    fPlotsComparison->Add(new TObjString("Muons/PxForward"));
    fPlotsComparison->Add(new TObjString("Muons/PxBarrel"));
    fPlotsComparison->Add(new TObjString("Muons/PxRear"));
    fPlotsComparison->Add(new TObjString("Muons/Py"));
    fPlotsComparison->Add(new TObjString("Muons/PyForward"));
    fPlotsComparison->Add(new TObjString("Muons/PyBarrel"));
    fPlotsComparison->Add(new TObjString("Muons/PyRear"));
    fPlotsComparison->Add(new TObjString("Muons/Pz"));
    fPlotsComparison->Add(new TObjString("Muons/PzForward"));
    fPlotsComparison->Add(new TObjString("Muons/PzBarrel"));
    fPlotsComparison->Add(new TObjString("Muons/PzRear"));
    fPlotsComparison->Add(new TObjString("Muons/Phi"));
    fPlotsComparison->Add(new TObjString("Muons/PhiForward"));
    fPlotsComparison->Add(new TObjString("Muons/PhiBarrel"));
    fPlotsComparison->Add(new TObjString("Muons/PhiRear"));
    fPlotsComparison->Add(new TObjString("Muons/Theta"));
    fPlotsComparison->Add(new TObjString("Muons/ThetaForward"));
    fPlotsComparison->Add(new TObjString("Muons/ThetaBarrel"));
    fPlotsComparison->Add(new TObjString("Muons/ThetaRear"));
    fPlotsComparison->Add(new TObjString("Muons/EtaForward"));
    fPlotsComparison->Add(new TObjString("Muons/EtaBarrel"));
    fPlotsComparison->Add(new TObjString("Muons/EtaRear"));
    fPlotsComparison->Add(new TObjString("Muons/Charge"));
    fPlotsComparison->Add(new TObjString("Muons/ChargeForward"));
    fPlotsComparison->Add(new TObjString("Muons/ChargeBarrel"));
    fPlotsComparison->Add(new TObjString("Muons/ChargeRear"));
    fPlotsComparison->Add(new TObjString("Muons/MuonFinder"));
    fPlotsComparison->Add(new TObjString("Muons/MuonFinder4"));
    fPlotsComparison->Add(new TObjString("Muons/MuonFinder5"));
    fPlotsComparison->Add(new TObjString("Muons/MuonFinder6"));
    fPlotsComparison->Add(new TObjString("Muons/2DBeamSpotImpact"));
    fPlotsComparison->Add(new TObjString("Muons/2DBeamSpotSignificance"));
    fPlotsComparison->Add(new TObjString("Muons/Quality"));
    fPlotsComparison->Add(new TObjString("Muons/QualityForward"));
    fPlotsComparison->Add(new TObjString("Muons/QualityBarrel"));
    fPlotsComparison->Add(new TObjString("Muons/QualityRear"));
    fPlotsComparison->Add(new TObjString("Muons/SpecialFinderForward"));
    fPlotsComparison->Add(new TObjString("Muons/SpecialFinderBarrel"));
    fPlotsComparison->Add(new TObjString("Muons/SpecialFinderRear"));
    fPlotsComparison->Add(new TObjString("Muons/Regions"));
    fPlotsComparison->Add(new TObjString("Muons/ChosenIso01"));
    fPlotsComparison->Add(new TObjString("Muons/ChosenIso02"));
    fPlotsComparison->Add(new TObjString("Muons/ChosenIso04"));
    fPlotsComparison->Add(new TObjString("Muons/ChosenIso05"));
    fPlotsComparison->Add(new TObjString("Muons/ChosenIso06"));
    fPlotsComparison->Add(new TObjString("Muons/ChosenIso08"));
    fPlotsComparison->Add(new TObjString("Muons/ChosenIso09"));
    fPlotsComparison->Add(new TObjString("Muons/ChosenIso03"));
    fPlotsComparison->Add(new TObjString("Muons/ChosenIso07"));
    fPlotsComparison->Add(new TObjString("Muons/ChosenIso10"));
  }

  fPlotsComparison->Add(new TObjString("Jet/Pt_Matched"));
  fPlotsComparison->Add(new TObjString("Jet/Et_Matched"));
  fPlotsComparison->Add(new TObjString("Jet/Et_Matched_breit"));
  fPlotsComparison->Add(new TObjString("Jet/Eta_Matched"));
  fPlotsComparison->Add(new TObjString("Jet/Mass_Matched"));
  if (!comp_disonly){
    fPlotsComparison->Add(new TObjString("Jet/XGamma_zufo"));
  }
  fPlotsComparison->Add(new TObjString("Jet/XGamma2"));
  fPlotsComparison->Add(new TObjString("Jet/MJet"));
  fPlotsComparison->Add(new TObjString("Jet/DPhiJet"));
  fPlotsComparison->Add(new TObjString("Jet/PtJet"));


  if ( comp_jet ) {
    if (!comp_disonly){
      fPlotsComparison->Add(new TObjString("Jet/XGamma"));
    }    
    fPlotsComparison->Add(new TObjString("Jet/Pt_Unmatched"));
    fPlotsComparison->Add(new TObjString("Jet/Pt_A"));
    fPlotsComparison->Add(new TObjString("Jet/Pt_B"));
    fPlotsComparison->Add(new TObjString("Jet/Et_Unmatched"));
    fPlotsComparison->Add(new TObjString("Jet/Et_A"));
    fPlotsComparison->Add(new TObjString("Jet/Et_B"));
    fPlotsComparison->Add(new TObjString("Jet/Et_Unmatched_breit"));
    fPlotsComparison->Add(new TObjString("Jet/Et_A_breit"));
    fPlotsComparison->Add(new TObjString("Jet/Et_B_breit"));
    fPlotsComparison->Add(new TObjString("Jet/Eta_Unmatched"));
    fPlotsComparison->Add(new TObjString("Jet/Eta_A"));
    fPlotsComparison->Add(new TObjString("Jet/Eta_B"));
    fPlotsComparison->Add(new TObjString("Jet/Eta_Matched_Large"));
    fPlotsComparison->Add(new TObjString("Jet/Eta_Unmatched_Large"));
    fPlotsComparison->Add(new TObjString("Jet/Eta_A_Large"));
    fPlotsComparison->Add(new TObjString("Jet/Eta_B_Large"));
    fPlotsComparison->Add(new TObjString("Jet/Mass_Unmatched"));
    fPlotsComparison->Add(new TObjString("Jet/Mass_A"));
    fPlotsComparison->Add(new TObjString("Jet/Mass_B"));
    fPlotsComparison->Add(new TObjString("Jet/n"));
    fPlotsComparison->Add(new TObjString("Jet/Phi_Matched"));
    fPlotsComparison->Add(new TObjString("Jet/Phi_Unmatched"));
    fPlotsComparison->Add(new TObjString("Jet/Phi_A"));
    fPlotsComparison->Add(new TObjString("Jet/Phi_B"));
  }

  fPlotsComparison->Add(new TObjString("MJMatch/PtMuOverEtJet"));

  if ( comp_mjmatch ) {
    fPlotsComparison->Add(new TObjString("MJMatch/DeltaR"));
    fPlotsComparison->Add(new TObjString("MJMatch/DeltaPhi"));
    fPlotsComparison->Add(new TObjString("MJMatch/DeltaEta"));
    fPlotsComparison->Add(new TObjString("MJMatch/DeltaTheta"));
  }

  if ( comp_cal ) {
    fPlotsComparison->Add(new TObjString("Cal/px"));
    fPlotsComparison->Add(new TObjString("Cal/py"));
    fPlotsComparison->Add(new TObjString("Cal/pz"));
    fPlotsComparison->Add(new TObjString("Cal/E"));
    fPlotsComparison->Add(new TObjString("Cal/Et"));
    fPlotsComparison->Add(new TObjString("Cal/Etex2ir"));
    fPlotsComparison->Add(new TObjString("Cal/Etex2irOrange"));
    fPlotsComparison->Add(new TObjString("Cal/Empz"));
    fPlotsComparison->Add(new TObjString("Cal/Pt"));
    if (!comp_disonly){
      fPlotsComparison->Add(new TObjString("Cal/YJB"));
    }
    fPlotsComparison->Add(new TObjString("Cal/PtOvEt"));
  }

  if ( comp_tracks ) {
    fPlotsComparison->Add(new TObjString("Tracks/N"));
    fPlotsComparison->Add(new TObjString("Tracks/NVertex"));
    fPlotsComparison->Add(new TObjString("Tracks/NTotalOvVertex"));
  }

  if ( comp_trigger ) {
    fPlotsComparison->Add(new TObjString("Trigger/FLT_AfterPrescale"));
    fPlotsComparison->Add(new TObjString("Trigger/SLT_1"));
    fPlotsComparison->Add(new TObjString("Trigger/SLT_2"));
    fPlotsComparison->Add(new TObjString("Trigger/SLT_3"));
    fPlotsComparison->Add(new TObjString("Trigger/SLT_4"));
    fPlotsComparison->Add(new TObjString("Trigger/SLT_5"));
    fPlotsComparison->Add(new TObjString("Trigger/SLT_6"));
    fPlotsComparison->Add(new TObjString("Trigger/TLT_SPP_after_prescale"));
    fPlotsComparison->Add(new TObjString("Trigger/TLT_DIS_after_prescale"));
    fPlotsComparison->Add(new TObjString("Trigger/TLT_HPP_after_prescale"));
    fPlotsComparison->Add(new TObjString("Trigger/TLT_EXO_after_prescale"));
    fPlotsComparison->Add(new TObjString("Trigger/TLT_MUO_after_prescale"));
    fPlotsComparison->Add(new TObjString("Trigger/TLT_VTX_after_prescale"));
    fPlotsComparison->Add(new TObjString("Trigger/TLT_HFM_after_prescale"));
    fPlotsComparison->Add(new TObjString("Trigger/TLT_HFL_after_prescale"));
  }

  if ( comp_zufo ) { 
    fPlotsComparison->Add(new TObjString("Zufo/n"));
    fPlotsComparison->Add(new TObjString("Zufo/px"));
    fPlotsComparison->Add(new TObjString("Zufo/py"));
    fPlotsComparison->Add(new TObjString("Zufo/pz"));
    fPlotsComparison->Add(new TObjString("Zufo/p"));
    fPlotsComparison->Add(new TObjString("Zufo/pt"));
    fPlotsComparison->Add(new TObjString("Zufo/E"));
    fPlotsComparison->Add(new TObjString("Zufo/px_had"));
    fPlotsComparison->Add(new TObjString("Zufo/py_had"));
    fPlotsComparison->Add(new TObjString("Zufo/pz_had"));
    fPlotsComparison->Add(new TObjString("Zufo/E_had"));
    fPlotsComparison->Add(new TObjString("Zufo/Empz_had"));
    fPlotsComparison->Add(new TObjString("Zufo/Pt_had"));
    if (!comp_disonly){
      fPlotsComparison->Add(new TObjString("Zufo/YJB_had"));
    }
  }

  // list of 1D plots
  fPlots1D = new TList();

  if ( ONED_dimuon ) {
    fPlots1D->Add(new TObjString("DIMuon/DIMuonMass"));
    fPlots1D->Add(new TObjString("DIMuon/DIMuonMassLow"));
    fPlots1D->Add(new TObjString("DIMuon/DIMuonMassHigh"));
    fPlots1D->Add(new TObjString("DIMuon/DIMuonMass_LikeSign"));
    fPlots1D->Add(new TObjString("DIMuon/DIMuonMassLow_LikeSign"));
    fPlots1D->Add(new TObjString("DIMuon/DIMuonMassHigh_LikeSign"));
    fPlots1D->Add(new TObjString("DIMuon/DIMuonMass_UnlikeSign"));
    fPlots1D->Add(new TObjString("DIMuon/DIMuonMassLow_UnlikeSign"));
    fPlots1D->Add(new TObjString("DIMuon/DIMuonMassHigh_UnlikeSign"));
  }

  if ( ONED_muon ) {
    fPlots1D->Add(new TObjString("Muons/PtChosenFine2"));
    fPlots1D->Add(new TObjString("Muons/PtChosenFine4"));
    fPlots1D->Add(new TObjString("Muons/PtChosenFine8"));
    fPlots1D->Add(new TObjString("Muons/PtChosenFine16"));
    fPlots1D->Add(new TObjString("Muons/EtaChosen"));
    fPlots1D->Add(new TObjString("Muons/NMU"));
    fPlots1D->Add(new TObjString("Muons/NMUForward"));
    fPlots1D->Add(new TObjString("Muons/NMUBarrel"));
    fPlots1D->Add(new TObjString("Muons/NMURear"));
    fPlots1D->Add(new TObjString("Muons/P"));
    fPlots1D->Add(new TObjString("Muons/PForward"));
    fPlots1D->Add(new TObjString("Muons/PBarrel"));
    fPlots1D->Add(new TObjString("Muons/PRear"));
    fPlots1D->Add(new TObjString("Muons/PtForward"));
    fPlots1D->Add(new TObjString("Muons/PtBarrel"));
    fPlots1D->Add(new TObjString("Muons/PtRear"));
    fPlots1D->Add(new TObjString("Muons/Px"));
    fPlots1D->Add(new TObjString("Muons/PxForward"));
    fPlots1D->Add(new TObjString("Muons/PxBarrel"));
    fPlots1D->Add(new TObjString("Muons/PxRear"));
    fPlots1D->Add(new TObjString("Muons/Py"));
    fPlots1D->Add(new TObjString("Muons/PyForward"));
    fPlots1D->Add(new TObjString("Muons/PyBarrel"));
    fPlots1D->Add(new TObjString("Muons/PyRear"));
    fPlots1D->Add(new TObjString("Muons/Pz"));
    fPlots1D->Add(new TObjString("Muons/PzForward"));
    fPlots1D->Add(new TObjString("Muons/PzBarrel"));
    fPlots1D->Add(new TObjString("Muons/PzRear"));
    fPlots1D->Add(new TObjString("Muons/Phi"));
    fPlots1D->Add(new TObjString("Muons/PhiForward"));
    fPlots1D->Add(new TObjString("Muons/PhiBarrel"));
    fPlots1D->Add(new TObjString("Muons/PhiRear"));
    fPlots1D->Add(new TObjString("Muons/Theta"));
    fPlots1D->Add(new TObjString("Muons/ThetaForward"));
    fPlots1D->Add(new TObjString("Muons/ThetaBarrel"));
    fPlots1D->Add(new TObjString("Muons/ThetaRear"));
    fPlots1D->Add(new TObjString("Muons/Eta"));
    fPlots1D->Add(new TObjString("Muons/EtaForward"));
    fPlots1D->Add(new TObjString("Muons/EtaBarrel"));
    fPlots1D->Add(new TObjString("Muons/EtaRear"));
    fPlots1D->Add(new TObjString("Muons/Charge"));
    fPlots1D->Add(new TObjString("Muons/ChargeForward"));
    fPlots1D->Add(new TObjString("Muons/ChargeBarrel"));
    fPlots1D->Add(new TObjString("Muons/ChargeRear"));
    fPlots1D->Add(new TObjString("Muons/2DBeamSpotSignificance"));
    fPlots1D->Add(new TObjString("Muons/2DBeamSpotImpact"));
    fPlots1D->Add(new TObjString("Muons/Quality"));
    fPlots1D->Add(new TObjString("Muons/QualityForward"));
    fPlots1D->Add(new TObjString("Muons/QualityBarrel"));
    fPlots1D->Add(new TObjString("Muons/QualityRear"));
    fPlots1D->Add(new TObjString("Muons/SpecialFinder"));
    fPlots1D->Add(new TObjString("Muons/SpecialFinderForward"));
    fPlots1D->Add(new TObjString("Muons/SpecialFinderBarrel"));
    fPlots1D->Add(new TObjString("Muons/SpecialFinderRear"));
  }

  if ( ONED_track ) {
    fPlots1D->Add(new TObjString("Tracks/N"));
    fPlots1D->Add(new TObjString("Tracks/N_uncut"));
    fPlots1D->Add(new TObjString("Tracks/NVertex"));
    fPlots1D->Add(new TObjString("Tracks/NVertex_uncut"));
    fPlots1D->Add(new TObjString("Tracks/NTotalOvVertex"));
    fPlots1D->Add(new TObjString("Tracks/NTotalOvVertex_uncut"));
  }

  // list of 1D MC plots
  fPlots1DMC = new TList();

  if ( ONEDMC_dimuon ) {
    fPlots1DMC->Add(new TObjString("DIMuon/DIMuonMass"));
    fPlots1DMC->Add(new TObjString("DIMuon/DIMuonMassLow"));
    fPlots1DMC->Add(new TObjString("DIMuon/DIMuonMassHigh"));
    fPlots1DMC->Add(new TObjString("DIMuon/DIMuonMass_LikeSign"));
    fPlots1DMC->Add(new TObjString("DIMuon/DIMuonMassLow_LikeSign"));
    fPlots1DMC->Add(new TObjString("DIMuon/DIMuonMassHigh_LikeSign"));
    fPlots1DMC->Add(new TObjString("DIMuon/DIMuonMass_UnlikeSign"));
    fPlots1DMC->Add(new TObjString("DIMuon/DIMuonMassLow_UnlikeSign"));
    fPlots1DMC->Add(new TObjString("DIMuon/DIMuonMassHigh_UnlikeSign"));
    fPlots1DMC->Add(new TObjString("Muons/Quality"));
    fPlots1DMC->Add(new TObjString("Muons/QualityForward"));
    fPlots1DMC->Add(new TObjString("Muons/QualityBarrel"));
    fPlots1DMC->Add(new TObjString("Muons/QualityRear"));
    fPlots1DMC->Add(new TObjString("Muons/SpecialFinder"));
    fPlots1DMC->Add(new TObjString("Muons/SpecialFinderForward"));
    fPlots1DMC->Add(new TObjString("Muons/SpecialFinderBarrel"));
    fPlots1DMC->Add(new TObjString("Muons/SpecialFinderRear"));
  }

  if ( ONEDMC_mc ) {
    fPlots1DMC->Add(new TObjString("MC/X_uncut"));
    fPlots1DMC->Add(new TObjString("MC/Y_uncut"));
    fPlots1DMC->Add(new TObjString("MC/Q2_uncut"));
    fPlots1DMC->Add(new TObjString("MC/X"));
    fPlots1DMC->Add(new TObjString("MC/Y"));
    fPlots1DMC->Add(new TObjString("MC/Q2"));
    fPlots1DMC->Add(new TObjString("MC/MuonRegionsTrue"));
    fPlots1DMC->Add(new TObjString("MC/MuonRegionsTrueNRec"));
    fPlots1DMC->Add(new TObjString("MC/MuonPtChosenFine2True"));
    fPlots1DMC->Add(new TObjString("MC/MuonPtChosenFine2TrueNRec"));
    fPlots1DMC->Add(new TObjString("MC/MuonEtaChosenTrue"));
    fPlots1DMC->Add(new TObjString("MC/MuonEtaChosenTrueNRec"));

  }

  if ( ONEDMC_track ) {
    fPlots1DMC->Add(new TObjString("Tracks/N"));
    fPlots1DMC->Add(new TObjString("Tracks/N_uncut"));
    fPlots1DMC->Add(new TObjString("Tracks/NVertex"));
    fPlots1DMC->Add(new TObjString("Tracks/NVertex_uncut"));
    fPlots1DMC->Add(new TObjString("Tracks/NTotalOvVertex"));
    fPlots1DMC->Add(new TObjString("Tracks/NTotalOvVertex_uncut"));
  }

  if ( ONEDMC_muon ) {
    fPlots1DMC->Add(new TObjString("Muons/PMCTRUE_uncut"));
    fPlots1DMC->Add(new TObjString("Muons/PXMCTRUE_uncut"));
    fPlots1DMC->Add(new TObjString("Muons/PYMCTRUE_uncut"));
    fPlots1DMC->Add(new TObjString("Muons/PZMCTRUE_uncut"));
    fPlots1DMC->Add(new TObjString("Muons/PMCTRUEpos_uncut"));
    fPlots1DMC->Add(new TObjString("Muons/PXMCTRUEpos_uncut"));
    fPlots1DMC->Add(new TObjString("Muons/PYMCTRUEpos_uncut"));
    fPlots1DMC->Add(new TObjString("Muons/PZMCTRUEpos_uncut"));
    fPlots1DMC->Add(new TObjString("Muons/PMCTRUEneg_uncut"));
    fPlots1DMC->Add(new TObjString("Muons/PXMCTRUEneg_uncut"));
    fPlots1DMC->Add(new TObjString("Muons/PYMCTRUEneg_uncut"));
    fPlots1DMC->Add(new TObjString("Muons/PZMCTRUEneg_uncut"));
    fPlots1DMC->Add(new TObjString("Muons/PMCTRUE"));
    fPlots1DMC->Add(new TObjString("Muons/PXMCTRUE"));
    fPlots1DMC->Add(new TObjString("Muons/PYMCTRUE"));
    fPlots1DMC->Add(new TObjString("Muons/PZMCTRUE"));
    fPlots1DMC->Add(new TObjString("Muons/PMCTRUEpos"));
    fPlots1DMC->Add(new TObjString("Muons/PXMCTRUEpos"));
    fPlots1DMC->Add(new TObjString("Muons/PYMCTRUEpos"));
    fPlots1DMC->Add(new TObjString("Muons/PZMCTRUEpos"));
    fPlots1DMC->Add(new TObjString("Muons/PMCTRUEneg"));
    fPlots1DMC->Add(new TObjString("Muons/PXMCTRUEneg"));
    fPlots1DMC->Add(new TObjString("Muons/PYMCTRUEneg"));
    fPlots1DMC->Add(new TObjString("Muons/PZMCTRUEneg"));
    fPlots1DMC->Add(new TObjString("Muons/PtChosenFine2"));
    fPlots1DMC->Add(new TObjString("Muons/PtChosenFine4"));
    fPlots1DMC->Add(new TObjString("Muons/PtChosenFine8"));
    fPlots1DMC->Add(new TObjString("Muons/PtChosenFine16"));
    fPlots1DMC->Add(new TObjString("Muons/EtaChosen"));
    fPlots1DMC->Add(new TObjString("Muons/NMU"));
    fPlots1DMC->Add(new TObjString("Muons/NMUForward"));
    fPlots1DMC->Add(new TObjString("Muons/NMUBarrel"));
    fPlots1DMC->Add(new TObjString("Muons/NMURear"));
    fPlots1DMC->Add(new TObjString("Muons/P"));
    fPlots1DMC->Add(new TObjString("Muons/PForward"));
    fPlots1DMC->Add(new TObjString("Muons/PBarrel"));
    fPlots1DMC->Add(new TObjString("Muons/PRear"));
    fPlots1DMC->Add(new TObjString("Muons/PtForward"));
    fPlots1DMC->Add(new TObjString("Muons/PtBarrel"));
    fPlots1DMC->Add(new TObjString("Muons/PtRear"));
    fPlots1DMC->Add(new TObjString("Muons/Px"));
    fPlots1DMC->Add(new TObjString("Muons/PxForward"));
    fPlots1DMC->Add(new TObjString("Muons/PxBarrel"));
    fPlots1DMC->Add(new TObjString("Muons/PxRear"));
    fPlots1DMC->Add(new TObjString("Muons/Py"));
    fPlots1DMC->Add(new TObjString("Muons/PyForward"));
    fPlots1DMC->Add(new TObjString("Muons/PyBarrel"));
    fPlots1DMC->Add(new TObjString("Muons/PyRear"));
    fPlots1DMC->Add(new TObjString("Muons/Pz"));
    fPlots1DMC->Add(new TObjString("Muons/PzForward"));
    fPlots1DMC->Add(new TObjString("Muons/PzBarrel"));
    fPlots1DMC->Add(new TObjString("Muons/PzRear"));
    fPlots1DMC->Add(new TObjString("Muons/Phi"));
    fPlots1DMC->Add(new TObjString("Muons/PhiForward"));
    fPlots1DMC->Add(new TObjString("Muons/PhiBarrel"));
    fPlots1DMC->Add(new TObjString("Muons/PhiRear"));
    fPlots1DMC->Add(new TObjString("Muons/Theta"));
    fPlots1DMC->Add(new TObjString("Muons/ThetaForward"));
    fPlots1DMC->Add(new TObjString("Muons/ThetaBarrel"));
    fPlots1DMC->Add(new TObjString("Muons/ThetaRear"));
    fPlots1DMC->Add(new TObjString("Muons/EtaForward"));
    fPlots1DMC->Add(new TObjString("Muons/EtaBarrel"));
    fPlots1DMC->Add(new TObjString("Muons/EtaRear"));
    fPlots1DMC->Add(new TObjString("Muons/Charge"));
    fPlots1DMC->Add(new TObjString("Muons/ChargeForward"));
    fPlots1DMC->Add(new TObjString("Muons/ChargeBarrel"));
    fPlots1DMC->Add(new TObjString("Muons/ChargeRear"));
    fPlots1DMC->Add(new TObjString("Muons/2DBeamSpotSignificance"));
    fPlots1DMC->Add(new TObjString("Muons/2DBeamSpotImpact"));
    fPlots1DMC->Add(new TObjString("Muons/2DTrueImpact"));
    fPlots1DMC->Add(new TObjString("Muons/2DMCTrueImpact"));
    fPlots1DMC->Add(new TObjString("Muons/2DMCBeamSpotImpact"));
    fPlots1DMC->Add(new TObjString("Muons/Regions"));
    fPlots1DMC->Add(new TObjString("Muons/RegionsRecNTrue"));
    fPlots1DMC->Add(new TObjString("Muons/PtChosenFine2"));
    fPlots1DMC->Add(new TObjString("Muons/PtChosenFine2RecNTrue"));
    fPlots1DMC->Add(new TObjString("Muons/EtaChosen"));
    fPlots1DMC->Add(new TObjString("Muons/EtaChosenRecNTrue"));
  }


  // list of zoomed 1D plots
  fPlots1DZoomed = new TList();

  // list of zoomed 1D MC plots
  fPlots1DMCZoomed = new TList();

  // list of 2D plots
  fPlots2D = new TList();

  if ( TWOD_mjmatch ) {
    fPlots2D->Add(new TObjString("MJMatch/2DBSImpactVsPtRel_0_5_7_JetMinMu"));
    fPlots2D->Add(new TObjString("MJMatch/2DBSImpactVsPtRel_0_5_7"));
    fPlots2D->Add(new TObjString("Sinistra/Q2x"));
    fPlots2D->Add(new TObjString("Sinistra/XY"));
  }

  // list of 2D MC plots
  fPlots2DMC = new TList();
  
  if ( TWODMC_cal ) {
    fPlots2DMC->Add(new TObjString("Cal/YJBvsYTrue_uncut"));
    fPlots2DMC->Add(new TObjString("Cal/YJBvsYTrue"));
  }

  if ( TWODMC_zufo ) {
    fPlots2DMC->Add(new TObjString("Zufo/YJBvsYTrue_uncut"));
    fPlots2DMC->Add(new TObjString("Zufo/YJBvsYTrue"));
  }

  if ( TWODMC_mc ) {
    fPlots2DMC->Add(new TObjString("MC_Control/JetPtDeltaR"));
    fPlots2DMC->Add(new TObjString("MC_Control/JetEtDeltaR"));
    fPlots2DMC->Add(new TObjString("MC_Control/JetMassDeltaR"));
    fPlots2DMC->Add(new TObjString("MC_Control/JetPtPtRelRec"));
    fPlots2DMC->Add(new TObjString("MC_Control/JetEtPtRelRec"));
    fPlots2DMC->Add(new TObjString("MC_Control/JetMassPtRelRec"));
    fPlots2DMC->Add(new TObjString("MC_Control/PtRelJetQuark"));
    fPlots2DMC->Add(new TObjString("MC_Control/PtRelJetQuark45"));
    fPlots2DMC->Add(new TObjString("MC_Control/PtRelJetQuark56"));
    fPlots2DMC->Add(new TObjString("MC_Control/PtRelJetQuark6"));

    fPlots2DMC->Add(new TObjString("MC_Control/JetPtDeltaRB"));
    fPlots2DMC->Add(new TObjString("MC_Control/JetEtDeltaRB"));
    fPlots2DMC->Add(new TObjString("MC_Control/JetMassDeltaRB"));
    fPlots2DMC->Add(new TObjString("MC_Control/JetPtPtRelRecB"));
    fPlots2DMC->Add(new TObjString("MC_Control/JetEtPtRelRecB"));
    fPlots2DMC->Add(new TObjString("MC_Control/JetMassPtRelRecB"));
    fPlots2DMC->Add(new TObjString("MC_Control/PtRelJetBQuark"));
    fPlots2DMC->Add(new TObjString("MC_Control/PtRelJetBQuark45"));
    fPlots2DMC->Add(new TObjString("MC_Control/PtRelJetBQuark56"));
    fPlots2DMC->Add(new TObjString("MC_Control/PtRelJetBQuark6"));

    fPlots2DMC->Add(new TObjString("MC_Control/JetPtDeltaRC"));
    fPlots2DMC->Add(new TObjString("MC_Control/JetEtDeltaRC"));
    fPlots2DMC->Add(new TObjString("MC_Control/JetMassDeltaRC"));
    fPlots2DMC->Add(new TObjString("MC_Control/JetPtPtRelRecC"));
    fPlots2DMC->Add(new TObjString("MC_Control/JetEtPtRelRecC"));
    fPlots2DMC->Add(new TObjString("MC_Control/JetMassPtRelRecC"));
    fPlots2DMC->Add(new TObjString("MC_Control/PtRelJetCQuark"));
    fPlots2DMC->Add(new TObjString("MC_Control/PtRelJetCQuark45"));
    fPlots2DMC->Add(new TObjString("MC_Control/PtRelJetCQuark56"));
    fPlots2DMC->Add(new TObjString("MC_Control/PtRelJetCQuark6"));

    fPlots2DMC->Add(new TObjString("MC_Control/JetPtDeltaRLF"));
    fPlots2DMC->Add(new TObjString("MC_Control/JetEtDeltaRLF"));
    fPlots2DMC->Add(new TObjString("MC_Control/JetMassDeltaRLF"));
    fPlots2DMC->Add(new TObjString("MC_Control/JetPtPtRelRecLF"));
    fPlots2DMC->Add(new TObjString("MC_Control/JetEtPtRelRecLF"));
    fPlots2DMC->Add(new TObjString("MC_Control/JetMassPtRelRecLF"));
    fPlots2DMC->Add(new TObjString("MC_Control/PtRelJetLFQuark"));
    fPlots2DMC->Add(new TObjString("MC_Control/PtRelJetLFQuark45"));
    fPlots2DMC->Add(new TObjString("MC_Control/PtRelJetLFQuark56"));
    fPlots2DMC->Add(new TObjString("MC_Control/PtRelJetLFQuark6"));
  }

  if ( TWODMC_muon ) {
    fPlots2DMC->Add(new TObjString("Muons/PvsPMCTRUE_uncut"));
    fPlots2DMC->Add(new TObjString("Muons/PXvsPYMCTRUE_uncut"));
    fPlots2DMC->Add(new TObjString("Muons/PYvsPXMCTRUE_uncut"));
    fPlots2DMC->Add(new TObjString("Muons/PZvsPZMCTRUE_uncut"));
    fPlots2DMC->Add(new TObjString("Muons/PvsPMCTRUEpos_uncut"));
    fPlots2DMC->Add(new TObjString("Muons/PXvsPYMCTRUEpos_uncut"));
    fPlots2DMC->Add(new TObjString("Muons/PYvsPXMCTRUEpos_uncut"));
    fPlots2DMC->Add(new TObjString("Muons/PZvsPZMCTRUEpos_uncut"));
    fPlots2DMC->Add(new TObjString("Muons/PvsPMCTRUEneg_uncut"));
    fPlots2DMC->Add(new TObjString("Muons/PXvsPYMCTRUEneg_uncut"));
    fPlots2DMC->Add(new TObjString("Muons/PYvsPXMCTRUEneg_uncut"));
    fPlots2DMC->Add(new TObjString("Muons/PZvsPZMCTRUEneg_uncut"));
    fPlots2DMC->Add(new TObjString("Muons/PvsPMCTRUE"));
    fPlots2DMC->Add(new TObjString("Muons/PXvsPYMCTRUE"));
    fPlots2DMC->Add(new TObjString("Muons/PYvsPXMCTRUE"));
    fPlots2DMC->Add(new TObjString("Muons/PZvsPZMCTRUE"));
    fPlots2DMC->Add(new TObjString("Muons/PvsPMCTRUEpos"));
    fPlots2DMC->Add(new TObjString("Muons/PXvsPYMCTRUEpos"));
    fPlots2DMC->Add(new TObjString("Muons/PYvsPXMCTRUEpos"));
    fPlots2DMC->Add(new TObjString("Muons/PZvsPZMCTRUEpos"));
    fPlots2DMC->Add(new TObjString("Muons/PvsPMCTRUEneg"));
    fPlots2DMC->Add(new TObjString("Muons/PXvsPYMCTRUEneg"));
    fPlots2DMC->Add(new TObjString("Muons/PYvsPXMCTRUEneg"));
    fPlots2DMC->Add(new TObjString("Muons/PZvsPZMCTRUEneg"));
    fPlots2DMC->Add(new TObjString("Muons/2DBeamSpotImpactParameterRecVsTrue"));
    fPlots2DMC->Add(new TObjString("Muons/2DTrueImpactParameterRecVsTrue"));
  }

  if ( TWODMC_mjmatch ) {
    fPlots2DMC->Add(new TObjString("MJMatch/2DBSImpactVsPtRel_0_5_7_JetMinMu"));
    fPlots2DMC->Add(new TObjString("MJMatch/2DBSImpactVsPtRel_0_5_7"));
  }

  // list of zoomed 2D plots
  fPlots2DZoomed = new TList();

  // list of zoomed 2D MC plots
  fPlots2DMCZoomed = new TList();

  if ( TWODMCzoomed_mc ) {
    fPlots2DMCZoomed->Add(new TObjString("MC_Control/JetPtDeltaR"));
    fPlots2DMCZoomed->Add(new TObjString("MC_Control/JetEtDeltaR"));
    fPlots2DMCZoomed->Add(new TObjString("MC_Control/JetMassDeltaR"));
    fPlots2DMCZoomed->Add(new TObjString("MC_Control/JetPtPtRelRec"));
    fPlots2DMCZoomed->Add(new TObjString("MC_Control/JetEtPtRelRec"));
    fPlots2DMCZoomed->Add(new TObjString("MC_Control/JetMassPtRelRec"));

    fPlots2DMCZoomed->Add(new TObjString("MC_Control/JetPtDeltaRB"));
    fPlots2DMCZoomed->Add(new TObjString("MC_Control/JetEtDeltaRB"));
    fPlots2DMCZoomed->Add(new TObjString("MC_Control/JetMassDeltaRB"));
    fPlots2DMCZoomed->Add(new TObjString("MC_Control/JetPtPtRelRecB"));
    fPlots2DMCZoomed->Add(new TObjString("MC_Control/JetEtPtRelRecB"));
    fPlots2DMCZoomed->Add(new TObjString("MC_Control/JetMassPtRelRecB"));

    fPlots2DMCZoomed->Add(new TObjString("MC_Control/JetPtDeltaRC"));
    fPlots2DMCZoomed->Add(new TObjString("MC_Control/JetEtDeltaRC"));
    fPlots2DMCZoomed->Add(new TObjString("MC_Control/JetMassDeltaRC"));
    fPlots2DMCZoomed->Add(new TObjString("MC_Control/JetPtPtRelRecC"));
    fPlots2DMCZoomed->Add(new TObjString("MC_Control/JetEtPtRelRecC"));
    fPlots2DMCZoomed->Add(new TObjString("MC_Control/JetMassPtRelRecC"));

    fPlots2DMCZoomed->Add(new TObjString("MC_Control/JetPtDeltaRLF"));
    fPlots2DMCZoomed->Add(new TObjString("MC_Control/JetEtDeltaRLF"));
    fPlots2DMCZoomed->Add(new TObjString("MC_Control/JetMassDeltaRLF"));
    fPlots2DMCZoomed->Add(new TObjString("MC_Control/JetPtPtRelRecLF"));
    fPlots2DMCZoomed->Add(new TObjString("MC_Control/JetEtPtRelRecLF"));
    fPlots2DMCZoomed->Add(new TObjString("MC_Control/JetMassPtRelRecLF"));
  }

  fPlotsEfficiencyBasename = new TList();
  fPlotsEfficiencyBasename->Add(new TObjString("MuonPt"));
  fPlotsEfficiencyBasename->Add(new TObjString("MuonEta"));
  fPlotsEfficiencyBasename->Add(new TObjString("MuonPhi"));
  if ( EfficiencyFull ) {
    fPlotsEfficiencyBasename->Add(new TObjString("MuonP"));
    fPlotsEfficiencyBasename->Add(new TObjString("MuonPz"));
  }

  // add basenames for eta and phi plots in bins of pt, p and pz
  GDIMuons dimuon(12);

  if ( EfficiencyFull ) {
    for ( Int_t i = 0; i < dimuon.GetMuonP_NBins_MV(); ++i ) {
      Double_t *array = dimuon.GetMuonP_Bins_MV();
      TString name = "MuonEtaPBins_";
      name.Append(gInclude->FormatedDouble(array[i],0,2));;
      name.Append("_");
      name.Append(gInclude->FormatedDouble(array[i+1],0,2));;
      fPlotsEfficiencyBasename->Add(new TObjString(name));
      name = "MuonPhiPBins_";
      name.Append(gInclude->FormatedDouble(array[i],0,2));;
      name.Append("_");
      name.Append(gInclude->FormatedDouble(array[i+1],0,2));;
      fPlotsEfficiencyBasename->Add(new TObjString(name));
    }
  }
    
  for ( Int_t i = 0; i < dimuon.GetMuonPt_NBins_MV(); ++i ) {
    Double_t *array = dimuon.GetMuonPt_Bins_MV();
    TString name = "MuonEtaPtBins_";
    name.Append(gInclude->FormatedDouble(array[i],0,2));;
    name.Append("_");
    name.Append(gInclude->FormatedDouble(array[i+1],0,2));;
    fPlotsEfficiencyBasename->Add(new TObjString(name));
    name = "MuonPhiPtBins_";
    name.Append(gInclude->FormatedDouble(array[i],0,2));;
    name.Append("_");
    name.Append(gInclude->FormatedDouble(array[i+1],0,2));;
    fPlotsEfficiencyBasename->Add(new TObjString(name));
  }

  if ( EfficiencyFull ) {
    for ( Int_t i = 0; i < dimuon.GetMuonPz_NBins_MV(); ++i ) {
      Double_t *array = dimuon.GetMuonPz_Bins_MV();
      TString name = "MuonEtaPzBins_";
      name.Append(gInclude->FormatedDouble(array[i],0,2));;
      name.Append("_");
      name.Append(gInclude->FormatedDouble(array[i+1],0,2));;
      fPlotsEfficiencyBasename->Add(new TObjString(name));
      name = "MuonPhiPzBins_";
      name.Append(gInclude->FormatedDouble(array[i],0,2));;
      name.Append("_");
      name.Append(gInclude->FormatedDouble(array[i+1],0,2));;
      fPlotsEfficiencyBasename->Add(new TObjString(name));
    }
  }
    

  fPlotsEfficiencyFinder = new TList();
  fPlotsEfficiencyFinder->Add(new TObjString("BREMAT"));
  fPlotsEfficiencyFinder->Add(new TObjString("MPMATCH"));
  fPlotsEfficiencyFinder->Add(new TObjString("MUBAC"));

  fPlotsEfficiencyRegion = new TList();
  fPlotsEfficiencyRegion->Add(new TObjString(""));
  fPlotsEfficiencyRegion->Add(new TObjString("Forward"));
  fPlotsEfficiencyRegion->Add(new TObjString("Barrel"));
  fPlotsEfficiencyRegion->Add(new TObjString("Rear"));

  return kTRUE;
}




