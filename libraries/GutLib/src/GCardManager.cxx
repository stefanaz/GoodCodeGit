//
// GCardManager.cxx
//
// $Author: kahle $
// $Date: 2007/05/18 14:56:42 $
// $Revision: 1.62 $
//

#include <GCardManager.h>
#include <iostream>
#include <fstream>
#include <strstream>
#include <iomanip>

#ifndef GUT_GInclude
#include <GInclude.h>
#endif

#ifndef ROOT_TSystem
#include <TSystem.h>
#endif

using namespace std;

#ifndef __CINT__
ClassImp(GCardManager)
#endif

//_____________________________________________________________
// GCardManager
// Card Manager class
// generates card files from templates
//
//
GCardManager::GCardManager() : TObject() {
  //
  // GCardManager default constructor
  if ( gDebug ) cout << "GCardManager::GCardManager default ctor called" << endl;

  // set errorignorlevel to neglect light error messages
  if ( !gDebug )
    gErrorIgnoreLevel = 2001;

  // initialize variables
  fGutCodeDir = "";
  fTemplateDir = "";
  fAnalysisTemplateDir = "";
  fDummyFile = "";

}

//_____________________________________________________________

GCardManager::GCardManager(int argc, char **argv) : TObject() {
  //
  // GCardManager normal constructor
  if ( gDebug ) cout << "GCardManager::GCardManager normal ctor called" << endl;
  
  // set errorignorlevel to neglect light error messages
  if ( !gDebug )
    gErrorIgnoreLevel = 2001;

  // initialize variables
  fGutCodeDir = "";
  fTemplateDir = "";
  fAnalysisTemplateDir = "";
  fDummyFile = "";

  if ( CheckGutcodedir() ) {
    DecodeCommandline(argc,argv);
  }
}

//_____________________________________________________________

GCardManager::~GCardManager() {
  //
  // GCardManager default destructor
  if ( gDebug ) cout << "GCardManager::~GCardManager dtor called" << endl;

}

//_____________________________________________________________

void GCardManager::HelpMessage() {
  //
  // help message for concatenating cards
  if ( gDebug ) cout << "GCardManager::HelpMessage() called" << endl;

  cout << endl
       << "----------------------------------------------------------------------------------------" << endl
       << endl
       << "cardmaker.exe [options]" << endl
       << endl
       << "Program to concatenate cards-files from templates in $GUTCODEDIR/orange/cards/templates." << endl
       << "Analysis-template-files are used from $GUTCODEDIR/analysis/cards/templates." << endl
       << "Generated cards are stored in current directory." << endl
       << endl
       << "valid time periods for data: 95,96,97,98,99e,99p,00,03,04,05,06" << endl
       << "for selection of orange_old_data.template or orange_new_data.template" << endl
       << "and detector_95p-97p.template, detector_98e-00p.template, detector_03p-04p.template," << endl
       << "    detector_05e.template, detector_06e.template" << endl
       << endl
       << "valid time periods for mc: 95p,96p-97p,98e-99e,99p-00p,03p-04p,05e" << endl
       << "for selection of orange_old_mc.template or orange_new_mc.template" << endl
       << "and detector_95p-97p.template, detector_98e-00p.template, detector_03p-04p.template," << endl
       << "    detector_05e.template" << endl
       << endl
       << "----------------------------------------------------------------------------------------" << endl
       << endl
       << "HELP-options:" << endl
       << endl
       << "-help             : print this message" << endl
       << "--help            : print this message" << endl
       << endl
       << "ZES-Mode options" << endl
       << endl
       << "cardmaker.exe ZES [start run] [end run] [zes-selection-template-file] [timeperiod]" << endl 
       << "                  [output-cardfile-name]" << endl
       << endl
       << "ZES2-Mode options:" << endl
       << endl
       << "cardmaker.exe ZES2 [start run] [end run] [runs per cardfile]" << endl 
       << "                   [zes-selection-template-file]" << endl
       << "                   [timeperiod] [output-cardfile-basename incl. extension]" << endl
       << endl
       << "EVTAKE-Mode options:" << endl
       << endl
       << "cardmaker.exe EVTAKE [year] [particle type] [evtake lumi in nb^-1 per cardfile]" << endl 
       << "                     [output-cardfile-basename incl. extension]" << endl
       << "                     [startrun] [endrun] [timeperiod] " << endl
       << "                     year can be all years from 94 to 05" << endl
       << "                     particle type can be 'p' or 'e' and for 03 and 04 'pmvd' and 'pstt'" << endl
       << endl
       << "EVMINI-Mode options:" << endl
       << endl
       << "cardmaker.exe EVMINI [year] [particle type] [evtake lumi in nb^-1 per cardfile]" << endl 
       << "                     [output-cardfile-basename incl. extension]" << endl
       << "                     [startrun] [endrun] [timeperiod]" << endl
       << "                     year can be all years from 94 to 06" << endl
       << "                     particle type can be 'p' or 'e' and for 03 and 04 'pmvd' and 'pstt'" << endl
       << endl
       << "MC-Mode options:" << endl
       << endl
       << "cardmaker.exe MC [mc-selection-template-file] [timeperiod] [output-cardfile-name]" << endl
       << endl
       << "MC2-Mode options:" << endl
       << endl
       << "cardmaker.exe MC2 [files per cardfile] [mc-selection-template-file]" << endl 
       << "                  [timeperiod] [output-cardfile-basename incl. extension]" << endl
       << endl
       << "MCZES-Mode options" << endl
       << endl
       << "cardmaker.exe MCZES [mc-selection-template-file] [zes-selection-template-file]" << endl 
       << "                    [timeperiod] [output-cardfile-name]" << endl
       << endl
       << "MCZES2-Mode options:" << endl
       << endl
       << "cardmaker.exe MCZES2 [files per cardfile] [mc-selection-template-file]" << endl 
       << "                     [zes-selection-template-file]" << endl
       << "                     [timeperiod] [output-cardfile-basename incl. extension]" << endl
       << endl
       << "ANALYSIS-Mode options:" << endl
       << endl
       << "cardmaker.exe ANALYSIS [input-directory] [analysis-template-file] "<< endl
       << "                       [output-cardfile-name]" << endl
       << endl
       << "ANALUMI-Mode options:" << endl
       << endl
       << "cardmaker.exe ANALUMI [input-directory] [analysis-template-file] [luminosity]" << endl 
       << "                      [output-cardfile-name]" << endl
       << endl
       << "ANALUMIMC-Mode options:" << endl
       << endl
       << "cardmaker.exe ANALUMIMC [input-directory] [template-file] [luminosity]" << endl 
       << "                        [timeperiod] [output-cardfile-name]" << endl
       << endl
       << "ANALUMIMCBBBAR-Mode options:" << endl
       << endl
       << "cardmaker.exe ANALUMIMCBBBAR [input-directory] [template-file] [luminosity]" << endl 
       << "                             [timeperiod] [output-cardfile-name]" << endl
       << "ANALUMIMCCCBAR-Mode options:" << endl
       << endl
       << "cardmaker.exe ANALUMIMCCCBAR [input-directory] [template-file] [luminosity]" << endl 
       << "                             [timeperiod] [output-cardfile-name]" << endl
       << endl
       << "ANALUMIMCLF-Mode options:" << endl
       << endl
       << "cardmaker.exe ANALUMIMCLF [input-directory] [template-file] [luminosity]" << endl 
       << "                          [timeperiod] [output-cardfile-name]" << endl
       << endl
       << "ANALUMIMCJPSIHRWG-Mode options:" << endl
       << endl
       << "cardmaker.exe ANALUMIMCJPSIHRWG [input-directory] [template-file] [luminosity]" << endl 
       << "                                [timeperiod] [output-cardfile-name]" << endl
       << endl
       << "ANALUMIMCPSIPRIMEHRWG-Mode options:" << endl
       << endl
       << "cardmaker.exe ANALUMIMCPSIPRIMEHRWG [input-directory] [template-file] [luminosity]" << endl 
       << "                                    [timeperiod] [output-cardfile-name]" << endl
       << endl
       << "ANALUMIMCRAP-Mode options(use MCQ2SELECTIONCUT as lower Q2true cut):" << endl
       << endl
       << "cardmaker.exe ANALUMIMCRAP [input-directory] [template-file] [luminosity]" << endl 
       << "                           [timeperiod] [output-cardfile-name]" << endl
       << endl
       << "ANALUMIMCLFRAP-Mode options(use MCQ2SELECTIONCUT as lower Q2true cut):" << endl
       << endl
       << "cardmaker.exe ANALUMIMCLFRAP [input-directory] [template-file] [luminosity]" << endl 
       << "                             [timeperiod] [output-cardfile-name]" << endl
       << endl
       << "ANALUMIMCCCARRAP-Mode options(use MCQ2SELECTIONCUT as lower Q2true cut):" << endl
       << endl
       << "cardmaker.exe ANALUMIMCCCBARRAP [input-directory] [template-file] [luminosity]" << endl 
       << "                                [timeperiod] [output-cardfile-name]" << endl
       << endl
       << "ANALUMIMCBBARRAP-Mode options(use MCQ2SELECTIONCUT as lower Q2true cut):" << endl
       << endl
       << "cardmaker.exe ANALUMIMCBBBARRAP [input-directory] [template-file] [luminosity]" << endl 
       << "                                [timeperiod] [output-cardfile-name]" << endl
       << endl
       << "-------------------------------------------------------------------------------------------" << endl
       << endl;
  
}

//_____________________________________________________________

void GCardManager::DecodeCommandline(int argc, char **argv) {
  //
  // decode commandline parameters and call respective fill functions
  if ( gDebug ) cout << "GCardManager::HelpMessage() called" << endl;

  // check if first parameter is an option
  // positions given in index of opt

  // spool parameters in string array
  TString opt[argc];

  if ( argc > 1 ) {
    for ( Int_t i = 0; i < argc; i++ ) {
      opt[i]=argv[i];
    }
  }


  // check where options are given
  Int_t position_after_options = 1;
  for ( Int_t i = 0; i < argc; i++ ) {
    if ( opt[i].BeginsWith("-") ) {
      position_after_options = i+1;
    }
  }

  // check if options are given and then do code for options
  if ( position_after_options > 0 ) {
    for ( Int_t i = 1; i < position_after_options; i++ ) {
      opt[i].ToUpper();
      if ( opt[i].BeginsWith("HELP") ) {
	HelpMessage();
	return;
      }
    }
  }

  // check for mode 
  if ( (argc > position_after_options) && (argc > 1)) {
    opt[position_after_options].ToUpper();
    if ( opt[position_after_options].BeginsWith("MCZES2") ) {
      // check if enough parameters are given for MCZES2 (5)
      if ( argc > ( position_after_options + 5 ) ) {
	ConcatenateMCZES2(opt[position_after_options+1].Data(),
			  opt[position_after_options+2].Data(),
			  opt[position_after_options+3].Data(),
			  opt[position_after_options+4].Data(),
			  opt[position_after_options+5].Data());
      } else {
	HelpMessage();
	return;
      }
    } else if ( opt[position_after_options].BeginsWith("MCZES") ) {
      // check if enough parameters are given for MCZES (4)
      if ( argc > ( position_after_options + 4 ) ) {
	ConcatenateMCZES(opt[position_after_options+1].Data(),
			 opt[position_after_options+2].Data(),
			 opt[position_after_options+3].Data(),
			 opt[position_after_options+4].Data());
      } else {
	HelpMessage();
	return;
      }
    } else if ( opt[position_after_options].BeginsWith("ZES2") ) {
      // check if enough parameters are given for ZES2 (6)
      if ( argc > ( position_after_options + 6 ) ) {
	ConcatenateZES2(opt[position_after_options+1].Data(),
			opt[position_after_options+2].Data(),
			opt[position_after_options+3].Data(),
			opt[position_after_options+4].Data(),
			opt[position_after_options+5].Data(),
			opt[position_after_options+6].Data());
      } else {
	HelpMessage();
	return;
      }
    } else if ( opt[position_after_options].BeginsWith("ZES") ) {
      // check if enough parameters are given for ZES (5)
      if ( argc > ( position_after_options + 5 ) ) {
	ConcatenateZES(opt[position_after_options+1].Data(),
		       opt[position_after_options+2].Data(),
		       opt[position_after_options+3].Data(),
		       opt[position_after_options+4].Data(),
		       opt[position_after_options+5].Data());
      } else {
	HelpMessage();
	return;
      }
    } else if ( opt[position_after_options].BeginsWith("EVTAKE") ) {
      // check if enough parameters are given for EVTAKE (7)
      if ( argc > ( position_after_options + 7 ) ) {
	ConcatenateEVTAKE(opt[position_after_options+1].Data(),
			  opt[position_after_options+2].Data(),
			  opt[position_after_options+3].Data(),
			  opt[position_after_options+4].Data(),
			  opt[position_after_options+5].Data(),
			  opt[position_after_options+6].Data(),
			  opt[position_after_options+7].Data());
      } else {
	HelpMessage();
	return;
      }
    } else if ( opt[position_after_options].BeginsWith("EVMINI") ) {
      // check if enough parameters are given for EVMINI (7)
      if ( argc > ( position_after_options + 7 ) ) {
	ConcatenateEVMINI(opt[position_after_options+1].Data(),
			  opt[position_after_options+2].Data(),
			  opt[position_after_options+3].Data(),
			  opt[position_after_options+4].Data(),
			  opt[position_after_options+5].Data(),
			  opt[position_after_options+6].Data(),
			  opt[position_after_options+7].Data());
      } else {
	HelpMessage();
	return;
      }
    } else if ( opt[position_after_options].BeginsWith("MC2") ) {
      // check if enough parameters are given for MC2 (4)
      if ( argc > ( position_after_options + 4 ) ) {
	ConcatenateMC2(opt[position_after_options+1].Data(),
		       opt[position_after_options+2].Data(),
		       opt[position_after_options+3].Data(),
		       opt[position_after_options+4].Data());
      } else {
	HelpMessage();
      }
    } else if ( opt[position_after_options].BeginsWith("MC") ) {
      // check if enough parameters are given for MC (3)
      if ( argc > ( position_after_options + 3 ) ) {
	ConcatenateMC(opt[position_after_options+1].Data(),
		      opt[position_after_options+2].Data(),
		      opt[position_after_options+3].Data());
      } else {
	HelpMessage();
      }
    } else if ( opt[position_after_options].BeginsWith("ANALUMIMCLFREWEIGHT") ) {
      // check if enough parameters are given (5)
      if ( argc > ( position_after_options + 5 ) ) {
	TString dir = gSystem->WorkingDirectory();
	dir.Append("/");
	dir.Append(opt[position_after_options+1].Data());
	ConcatenateAnalumiMCLFREWEIGHT(dir.Data(),
				       opt[position_after_options+2].Data(),
				       opt[position_after_options+3].Data(),
				       opt[position_after_options+4].Data(),
				       opt[position_after_options+5].Data());
      }	else {
	HelpMessage();
      }
    } else if ( opt[position_after_options].BeginsWith("ANALUMIMCLFRAP") ) {
      // check if enough parameters are given for ANALUMIMCLFRAP (5)
      if ( argc > ( position_after_options + 5 ) ) {
	TString dir = gSystem->WorkingDirectory();
	dir.Append("/");
	dir.Append(opt[position_after_options+1].Data());
	ConcatenateAnalumiMCLFRAP(dir.Data(),
				  opt[position_after_options+2].Data(),
				  opt[position_after_options+3].Data(),
				  opt[position_after_options+4].Data(),
				  opt[position_after_options+5].Data());
      }	else {
	HelpMessage();
      }
    } else if ( opt[position_after_options].BeginsWith("ANALUMIMCLF") ) {
      // check if enough parameters are given for ANALUMIMC (5)
      if ( argc > ( position_after_options + 5 ) ) {
	TString dir = gSystem->WorkingDirectory();
	dir.Append("/");
	dir.Append(opt[position_after_options+1].Data());
	ConcatenateAnalumiMCLF(dir.Data(),
			       opt[position_after_options+2].Data(),
			       opt[position_after_options+3].Data(),
			       opt[position_after_options+4].Data(),
			       opt[position_after_options+5].Data());
      }	else {
	HelpMessage();
      }
    } else if ( opt[position_after_options].BeginsWith("ANALUMIMCRAP") ) {
      // check if enough parameters are given for ANALUMIMCRAP (5)
      if ( argc > ( position_after_options + 5 ) ) {
	TString dir = gSystem->WorkingDirectory();
	dir.Append("/");
	dir.Append(opt[position_after_options+1].Data());
	ConcatenateAnalumiMCRAP(dir.Data(),
				opt[position_after_options+2].Data(),
				opt[position_after_options+3].Data(),
				opt[position_after_options+4].Data(),
				opt[position_after_options+5].Data());
      }	else {
	HelpMessage();
      }
    } else if ( opt[position_after_options].BeginsWith("ANALUMIMCBBBARRAP") ) {
      // check if enough parameters are given (5)
      if ( argc > ( position_after_options + 5 ) ) {
	TString dir = gSystem->WorkingDirectory();
	dir.Append("/");
	dir.Append(opt[position_after_options+1].Data());
	ConcatenateAnalumiMCBBBARRAP(dir.Data(),
				     opt[position_after_options+2].Data(),
				     opt[position_after_options+3].Data(),
				     opt[position_after_options+4].Data(),
				     opt[position_after_options+5].Data());
      }	else {
	HelpMessage();
      }
    } else if ( opt[position_after_options].BeginsWith("ANALUMIMCBBBAR") ) {
      // check if enough parameters are given (5)
      if ( argc > ( position_after_options + 5 ) ) {
	TString dir = gSystem->WorkingDirectory();
	dir.Append("/");
	dir.Append(opt[position_after_options+1].Data());
	ConcatenateAnalumiMCBBBAR(dir.Data(),
				  opt[position_after_options+2].Data(),
				  opt[position_after_options+3].Data(),
				  opt[position_after_options+4].Data(),
				  opt[position_after_options+5].Data());
      }	else {
	HelpMessage();
      }
    } else if ( opt[position_after_options].BeginsWith("ANALUMIMCCCBARRAP") ) {
      // check if enough parameters are given (5)
      if ( argc > ( position_after_options + 5 ) ) {
	TString dir = gSystem->WorkingDirectory();
	dir.Append("/");
	dir.Append(opt[position_after_options+1].Data());
	ConcatenateAnalumiMCCCBARRAP(dir.Data(),
				     opt[position_after_options+2].Data(),
				     opt[position_after_options+3].Data(),
				     opt[position_after_options+4].Data(),
				     opt[position_after_options+5].Data());
      }	else {
	HelpMessage();
      }
    } else if ( opt[position_after_options].BeginsWith("ANALUMIMCCCBARREWEIGHT") ) {
      // check if enough parameters are given (5)
      if ( argc > ( position_after_options + 5 ) ) {
	TString dir = gSystem->WorkingDirectory();
	dir.Append("/");
	dir.Append(opt[position_after_options+1].Data());
	ConcatenateAnalumiMCCCBARREWEIGHT(dir.Data(),
				  opt[position_after_options+2].Data(),
				  opt[position_after_options+3].Data(),
				  opt[position_after_options+4].Data(),
				  opt[position_after_options+5].Data());
      }	else {
	HelpMessage();
      }
    } else if ( opt[position_after_options].BeginsWith("ANALUMIMCCCBAR") ) {
      // check if enough parameters are given (5)
      if ( argc > ( position_after_options + 5 ) ) {
	TString dir = gSystem->WorkingDirectory();
	dir.Append("/");
	dir.Append(opt[position_after_options+1].Data());
	ConcatenateAnalumiMCCCBAR(dir.Data(),
				  opt[position_after_options+2].Data(),
				  opt[position_after_options+3].Data(),
				  opt[position_after_options+4].Data(),
				  opt[position_after_options+5].Data());
      }	else {
	HelpMessage();
      }
    } else if ( opt[position_after_options].BeginsWith("ANALUMIMCJPSIHRWG") ) {
      // check if enough parameters are given for ANALUMIMC (5)
      if ( argc > ( position_after_options + 5 ) ) {
	TString dir = gSystem->WorkingDirectory();
	dir.Append("/");
	dir.Append(opt[position_after_options+1].Data());
	ConcatenateAnalumiMCJPSIHRWG(dir.Data(),
				     opt[position_after_options+2].Data(),
				     opt[position_after_options+3].Data(),
				     opt[position_after_options+4].Data(),
				     opt[position_after_options+5].Data());
      }	else {
	HelpMessage();
      }
    } else if ( opt[position_after_options].BeginsWith("ANALUMIMCPSIPRIMEHRWG") ) {
      // check if enough parameters are given for ANALUMIMC (5)
      if ( argc > ( position_after_options + 5 ) ) {
	TString dir = gSystem->WorkingDirectory();
	dir.Append("/");
	dir.Append(opt[position_after_options+1].Data());
	ConcatenateAnalumiMCPSIPRIMEHRWG(dir.Data(),
				     opt[position_after_options+2].Data(),
				     opt[position_after_options+3].Data(),
				     opt[position_after_options+4].Data(),
				     opt[position_after_options+5].Data());
      }	else {
	HelpMessage();
      }


    } else if ( opt[position_after_options].BeginsWith("ANALUMIMC") ) {
      // check if enough parameters are given for ANALUMIMC (5)
      if ( argc > ( position_after_options + 5 ) ) {
	TString dir = gSystem->WorkingDirectory();
	dir.Append("/");
	dir.Append(opt[position_after_options+1].Data());
	ConcatenateAnalumiMC(dir.Data(),
			     opt[position_after_options+2].Data(),
			     opt[position_after_options+3].Data(),
			     opt[position_after_options+4].Data(),
			     opt[position_after_options+5].Data());
      }	else {
	HelpMessage();
      }
    } else if ( opt[position_after_options].BeginsWith("ANALUMI") ) {
      // check if enough parameters are given for ANALUMI (4)
      if ( argc > ( position_after_options + 4 ) ) {
	TString dir = gSystem->WorkingDirectory();
	dir.Append("/");
	dir.Append(opt[position_after_options+1].Data());
	ConcatenateAnalumi(dir.Data(),
			   opt[position_after_options+2].Data(),
			   opt[position_after_options+3].Data(),
			   opt[position_after_options+4].Data());
      }	else {
	HelpMessage();
      }
    } else if ( opt[position_after_options].BeginsWith("ANALYSIS") ) {
      // check if enough parameters are given for ANALYSIS (3)
      if ( argc > ( position_after_options + 3 ) ) {
	TString dir = gSystem->WorkingDirectory();
	dir.Append("/");
	dir.Append(opt[position_after_options+1].Data());
	ConcatenateAnalysis(dir.Data(),
			    opt[position_after_options+2].Data(),
			    opt[position_after_options+3].Data());
      } else {
	HelpMessage();
      }
    }
  }
}

//_____________________________________________________________

void GCardManager::ConcatenateZES(TString start, TString end, TString cutfile, TString timeperiod, TString selfile) {
  //
  // concatenate card-file in ZES mode
  if ( gDebug ) cout << "GCardManager::ConcatenateZES() called" << endl;

  // output stream
  ofstream *output = new ofstream(selfile);

  StreamStart(output);
  StreamZESRun(output,start,end);
  StreamZESSelect(output,cutfile);
  StreamOrange(output,timeperiod);
  StreamMagField(output);
  StreamGeant(output);
  StreamMozart(output);
  StreamHera(output);
  StreamDetector(output,timeperiod);
  StreamReco(output);
  StreamBremat(output);
  StreamGutcard(output);
  StreamGeneral(output);

  delete output;
}

//_____________________________________________________________

void GCardManager::StreamStart(ofstream *output) {
  //
  // stream start.template to output
  if ( gDebug ) cout << "GCardManager::StreamStart() called" << endl;

  TString file = gSystem->Which(fTemplateDir.Data(),"start.template");

  if ( file.Length() > 0 ) {

    ifstream input(file.Data());
    
    TString line;

    while ( line.ReadLine(input,kFALSE) ) {
      *output << line.Data() << endl;
    }
    
    //    cout << "Successfully streamed file " << file << " to output!" << endl;
  } else {
    cout << "Problems in reading Start Template!" << endl;
  }
}

//_____________________________________________________________

void GCardManager::StreamZESRun(ofstream *output, TString start, TString end) {
  //
  // stream start.template to output
  if ( gDebug ) cout << "GCardManager::StreamZESRun() called" << endl;

  TString file = gSystem->Which(fTemplateDir.Data(),"zes_run.template");
  
  if ( file.Length() > 0 ) {
    ifstream input(file.Data());
    
    TString line;
    
    while ( line.ReadLine(input,kFALSE) ) {
      if ( line.Contains("FirstRun") ) {
	line = "ZeusIO-FirstRun ";
	line.Append(start);
      } else if ( line.Contains("LastRun") ) {
	line = "ZeusIO-LastRun ";
	line.Append(end);
      }

      *output << line.Data() << endl;;
    }
    //    cout << "Successfully streamed file " << file << " to output!" << endl;
  } else {
    cout << "Problems in reading ZES_Run Template!" << endl;
  }

}

//_____________________________________________________________

void GCardManager::StreamZESSelect(ofstream *output, TString cutfile) {
  //
  // stream start.template to output
  // don't do anything with cutfile = DUMMY
  if ( gDebug ) cout << "GCardManager::StreamZESSelect() called" << endl;

  if ( !cutfile.BeginsWith("DUMMY") ) {

    TString file = gSystem->Which(fTemplateDir.Data(),cutfile);
    
    if ( file.Length() > 0 ) {
      
      ifstream input(file.Data());
      
      TString line;
    
      while ( line.ReadLine(input,kFALSE) ) {
	*output << line.Data() << endl;
      }
      
      //      cout << "Successfully streamed file " << file << " to output!" << endl;
    } else {
      cout << "Problems in reading ZES_Selection Template!" << endl;
    }
  }

}

//_____________________________________________________________

void GCardManager::StreamOrange(ofstream *output, TString timeperiod) {
  //
  // stream start.template to output
  if ( gDebug ) cout << "GCardManager::StreamOrange() called" << endl;

  TString file = "";

  if ( timeperiod.Contains("95p")     ||
       timeperiod.Contains("96p-97p") || 
       timeperiod.Contains("98e-99e") || 
       timeperiod.Contains("99p-00p") ) {
    file = gSystem->Which(fTemplateDir.Data(),"orange_old_mc.template");
  } else if ( timeperiod.Contains("03p-04p") || 
	      timeperiod.Contains("05e") || 
	      timeperiod.Contains("06e") ) {
    file = gSystem->Which(fTemplateDir.Data(),"orange_new_mc.template");
  } else   if ( timeperiod.Contains("95") ||
		timeperiod.Contains("96") || 
		timeperiod.Contains("97") || 
		timeperiod.Contains("98") || 
		timeperiod.Contains("99") || 
		timeperiod.Contains("00") ) {
    file = gSystem->Which(fTemplateDir.Data(),"orange_old_data.template");
  } else   if ( timeperiod.Contains("03") ||
		timeperiod.Contains("04") ) {
    file = gSystem->Which(fTemplateDir.Data(),"orange_new_data.template");
  } else   if ( timeperiod.Contains("05") ) {
    file = gSystem->Which(fTemplateDir.Data(),"orange_05e_data.template");
  } else   if ( timeperiod.Contains("06") ) {
    file = gSystem->Which(fTemplateDir.Data(),"orange_06e_data.template");
  } else {
    cout << "wrong timeperiod for orange template" << endl;
  }

  if ( file.Length() > 0 ) {
    ifstream input(file.Data());
    
    TString line;
    
    while ( line.ReadLine(input,kFALSE) ) {
      *output << line.Data() << endl;;
    }
    //    cout << "Successfully streamed file " << file << " to output!" << endl;
  } else {
    cout << "Problems in reading Orange Template!" << endl;
  }


}

//_____________________________________________________________

void GCardManager::StreamBremat(ofstream *output) {
  //
  // stream start.template to output
  if ( gDebug ) cout << "GCardManager::StreamBremat() called" << endl;

  TString file = gSystem->Which(fTemplateDir.Data(),"bremat.template");

  if ( file.Length() > 0 ) {
    ifstream input(file.Data());
    
    TString line;
    
    while ( line.ReadLine(input,kFALSE) ) {
      *output << line.Data() << endl;;
    }
    //    cout << "Successfully streamed file " << file << " to output!" << endl;
  } else {
    cout << "Problems in reading Bremat Template!" << endl;
  }


}

//_____________________________________________________________

void GCardManager::StreamMCStart(ofstream *output) {
  //
  // stream start.template to output
  if ( gDebug ) cout << "GCardManager::StreamMCStart() called" << endl;

  TString file = gSystem->Which(fTemplateDir.Data(),"mc_start.template");

  if ( file.Length() > 0 ) {
    ifstream input(file.Data());
    
    TString line;
    
    while ( line.ReadLine(input,kFALSE) ) {
      *output << line.Data() << endl;;
    }
    //    cout << "Successfully streamed file " << file << " to output!" << endl;
  } else {
    cout << "Problems in reading MC Start Template!" << endl;
  }

}

//_____________________________________________________________

void GCardManager::StreamMCSelect(ofstream *output, TString mcfile) {
  //
  // stream start.template to output
  if ( gDebug ) cout << "GCardManager::StreamMCSelect() called" << endl;

  TString file = gSystem->Which(fTemplateDir.Data(),mcfile);

  if ( file.Length() > 0 ) {
    ifstream input(file.Data());
    
    TString line;
    
    while ( line.ReadLine(input,kFALSE) ) {
      *output << line.Data() << endl; 
    }
    //    cout << "Successfully streamed file " << file << " to output!" << endl;
  } else {
    cout << "Problems in reading MC Select Template!" << endl;
  }

}

//_____________________________________________________________

void GCardManager::StreamGeneral(ofstream *output) {
  //
  // stream start.template to output
  if ( gDebug ) cout << "GCardManager::StreamGeneral() called" << endl;

  TString file = gSystem->Which(fTemplateDir.Data(),"general.template");

  if ( file.Length() > 0 ) {
    ifstream input(file.Data());
    
    TString line;
    
    while ( line.ReadLine(input,kFALSE) ) {
      *output << line.Data() << endl;
    }
    //    cout << "Successfully streamed file " << file << " to output!" << endl;
  } else {
    cout << "Problems in reading General Template!" << endl;
  }
}

//_____________________________________________________________

void GCardManager::StreamGutcard(ofstream *output, Bool_t mc) {
  //
  // stream start.template to output
  if ( gDebug ) cout << "GCardManager::StreamGutcard() called" << endl;

  TString file = gSystem->Which(fTemplateDir.Data(),"gutcard.template");

  if ( file.Length() > 0 ) {
    ifstream input(file.Data());
    
    TString line;
    
    while ( line.ReadLine(input,kFALSE) ) {
      if ( mc )
	if ( line.Contains("GUTCARD-MC") )
	  line.ReplaceAll("OFF","ON");
      *output << line.Data() << endl;
    }
    //    cout << "Successfully streamed file " << file << " to output!" << endl;
  } else {
    cout << "Problems in reading Gutcard Template!" << endl;
  }
}

//_____________________________________________________________

void GCardManager::ConcatenateAnalysis(TString inputdir, TString templatefile, TString selfile) {
  //
  // concatenate card-file in Analysis mode
  if ( gDebug ) cout << "GCardManager::ConcatenateAnalysis() called" << endl;

  // output stream
  ofstream *output = new ofstream(selfile);

  StreamAnalysis(output,templatefile,inputdir);

  delete output;
}

//_____________________________________________________________

void GCardManager::ConcatenateAnalumi(TString inputdir, TString templatefile, TString lumi, TString selfile) {
  //
  // concatenate card-file in Analysis mode including LUMI
  if ( gDebug ) cout << "GCardManager::ConcatenateAnalumi() called" << endl;

  // output stream
  ofstream *output = new ofstream(selfile);

  StreamLumiAnalysis(output,templatefile,lumi,inputdir);

  delete output;
}

//_____________________________________________________________

void GCardManager::ConcatenateAnalumiMC(TString inputdir, TString templatefile, TString lumi, TString runperiod, TString selfile) {
  //
  // concatenate card-file in MC Analysis mode including LUMI
  if ( gDebug ) cout << "GCardManager::ConcatenateAnalumiMC() called" << endl;

  // output stream
  ofstream *output = new ofstream(selfile);

  StreamLumiAnalysisMC(output,templatefile,lumi,inputdir,runperiod);

  delete output;
}

//_____________________________________________________________


void GCardManager::ConcatenateAnalumiMCRAP(TString inputdir, TString templatefile, TString lumi, TString runperiod, TString selfile) {
  //
  // concatenate card-file in MC Analysis mode including LUMI
  if ( gDebug ) cout << "GCardManager::ConcatenateAnalumiMC() called" << endl;

  // output stream
  ofstream *output = new ofstream(selfile);

  StreamLumiAnalysisMCRAP(output,templatefile,lumi,inputdir,runperiod);

  delete output;
}

//_____________________________________________________________

void GCardManager::ConcatenateAnalumiMCLFRAP(TString inputdir, TString templatefile, TString lumi, TString runperiod, TString selfile) {
  //
  // concatenate card-file in light flavour MC Analysis mode including LUMI
  if ( gDebug ) cout << "GCardManager::ConcatenateAnalumiMCLFRAP() called" << endl;

  // output stream
  ofstream *output = new ofstream(selfile);

  StreamLumiAnalysisMCLFRAP(output,templatefile,lumi,inputdir,runperiod);

  delete output;
}

//_____________________________________________________________

void GCardManager::ConcatenateAnalumiMCLF(TString inputdir, TString templatefile, TString lumi, TString runperiod, TString selfile) {
  //
  // concatenate card-file in light flavour MC Analysis mode including LUMI
  if ( gDebug ) cout << "GCardManager::ConcatenateAnalumiMCLF() called" << endl;

  // output stream
  ofstream *output = new ofstream(selfile);

  StreamLumiAnalysisMCLF(output,templatefile,lumi,inputdir,runperiod);

  delete output;
}

//_____________________________________________________________

void GCardManager::ConcatenateAnalumiMCBBBAR(TString inputdir, TString templatefile, TString lumi, TString runperiod, TString selfile) {
  //
  // concatenate card-file in bbbar MC Analysis mode including LUMI
  if ( gDebug ) cout << "GCardManager::ConcatenateAnalumiMCBBBAR() called" << endl;

  // output stream
  ofstream *output = new ofstream(selfile);

  StreamLumiAnalysisMCBBBAR(output,templatefile,lumi,inputdir,runperiod);

  delete output;
}
//_____________________________________________________________

void GCardManager::ConcatenateAnalumiMCBBBARRAP(TString inputdir, TString templatefile, TString lumi, TString runperiod, TString selfile) {
  //
  // concatenate card-file in bbbar MC Analysis mode including LUMI
  if ( gDebug ) cout << "GCardManager::ConcatenateAnalumiMCBBBARRAP() called" << endl;

  // output stream
  ofstream *output = new ofstream(selfile);

  StreamLumiAnalysisMCBBBARRAP(output,templatefile,lumi,inputdir,runperiod);

  delete output;
}

//_____________________________________________________________

void GCardManager::ConcatenateAnalumiMCCCBARRAP(TString inputdir, TString templatefile, TString lumi, TString runperiod, TString selfile) {
  //
  // concatenate card-file in ccbar MC Analysis mode including LUMI
  if ( gDebug ) cout << "GCardManager::ConcatenateAnalumiMCCCBARRAP() called" << endl;

  // output stream
  ofstream *output = new ofstream(selfile);

  StreamLumiAnalysisMCCCBARRAP(output,templatefile,lumi,inputdir,runperiod);

  delete output;
}
//_____________________________________________________________

void GCardManager::ConcatenateAnalumiMCCCBARREWEIGHT(TString inputdir, TString templatefile, TString lumi, TString runperiod, TString selfile) {
  //
  // concatenate card-file in ccbar MC Analysis mode including LUMI
  if ( gDebug ) cout << "GCardManager::ConcatenateAnalumiMCCCBARREWEIGHT() called" << endl;

  // output stream
  ofstream *output = new ofstream(selfile);

  StreamLumiAnalysisMCCCBARREWEIGHT(output,templatefile,lumi,inputdir,runperiod);

  delete output;
}
//_____________________________________________________________

void GCardManager::ConcatenateAnalumiMCCCBAR(TString inputdir, TString templatefile, TString lumi, TString runperiod, TString selfile) {
  //
  // concatenate card-file in ccbar MC Analysis mode including LUMI
  if ( gDebug ) cout << "GCardManager::ConcatenateAnalumiMCCCBAR() called" << endl;

  // output stream
  ofstream *output = new ofstream(selfile);

  StreamLumiAnalysisMCCCBAR(output,templatefile,lumi,inputdir,runperiod);

  delete output;
}
//_____________________________________________________________
void GCardManager::ConcatenateAnalumiMCLFREWEIGHT(TString inputdir, TString templatefile, TString lumi, TString runperiod, TString selfile) {
  //
  // concatenate card-file in lf MC Analysis mode including LUMI
  if ( gDebug ) cout << "GCardManager::ConcatenateAnalumiMCLFREWEIGHT() called" << endl;

  // output stream
  ofstream *output = new ofstream(selfile);

  StreamLumiAnalysisMCLFREWEIGHT(output,templatefile,lumi,inputdir,runperiod);

  delete output;
}
//_____________________________________________________________


void GCardManager::ConcatenateAnalumiMCJPSIHRWG(TString inputdir, TString templatefile, TString lumi, TString runperiod, TString selfile) {
  //
  // concatenate card-file in jpsihrwg MC Analysis mode including LUMI
  if ( gDebug ) cout << "GCardManager::ConcatenateAnalumiMCJPSIHRWG() called" << endl;

  // output stream
  ofstream *output = new ofstream(selfile);

  StreamLumiAnalysisMCJPSIHRWG(output,templatefile,lumi,inputdir,runperiod);

  delete output;
}

//_____________________________________________________________


void GCardManager::ConcatenateAnalumiMCPSIPRIMEHRWG(TString inputdir, TString templatefile, TString lumi, TString runperiod, TString selfile) {
  //
  // concatenate card-file in psiprimehrwg MC Analysis mode including LUMI
  if ( gDebug ) cout << "GCardManager::ConcatenateAnalumiMCPSIPRIMEHRWG() called" << endl;

  // output stream
  ofstream *output = new ofstream(selfile);

  StreamLumiAnalysisMCPSIPRIMEHRWG(output,templatefile,lumi,inputdir,runperiod);

  delete output;
}

//_____________________________________________________________

void GCardManager::StreamAnalysis(ofstream *output, TString templatefile, TString inputdir) {
  //
  // stream analysis.templatefile to output
  if ( gDebug ) cout << "GCardManager::StreamAnalysis() called" << endl;

  TString file = gSystem->Which(fAnalysisTemplateDir,templatefile);
  
  if ( file.Length() > 0 ) {
    ifstream input(file.Data());
    TString line;
    while ( line.ReadLine(input,kFALSE) ) {
      if ( line.Contains("GENERAL-INPUTDIR") ) {
	line = "GENERAL-INPUTDIR ";
	line.Append(inputdir);
      }
      *output << line.Data() << endl;
    }
    //    cout << "Successfully streamed file " << file << " to output!" << endl;
  } else {
    cout << "Problems in reading Analysis Template!" << endl;
  }
}

//_____________________________________________________________

void GCardManager::StreamLumiAnalysis(ofstream *output, TString templatefile, TString lumi, TString inputdir) {
  //
  // stream analysis.template file to output and change LUMI
  if ( gDebug ) cout << "GCardManager::StreamLumiAnalysis() called" << endl;

  TString file = gSystem->Which(fAnalysisTemplateDir,templatefile);
  
  if ( file.Length() > 0 ) {
    ifstream input(file.Data());
    TString line;
    while ( line.ReadLine(input,kFALSE) ) {
      // switch off MC
      if ( line.Contains("GENERAL-MC") ) {
	line = "GENERAL-MC OFF";
      }
      if ( line.Contains("GENERAL-OWNMC" ) ) {
	line = "GENERAL-OWNMC OFF";
      }
      if ( line.Contains("GENERAL-OWNJETSMC" ) ) {
	line = "GENERAL-OWNJETSMC OFF";
      }
      if ( line.Contains("GENERAL-INPUTDIR") ) {
	line = "GENERAL-INPUTDIR ";
	line.Append(inputdir);
      }
      // replace lumi
      if ( line.Contains("GENERAL-LUMINOSITY") ) {
	line = "GENERAL-LUMINOSITY ";
	line.Append(lumi);
      }
      
      *output << line.Data() << endl;
    }
    //    cout << "Successfully streamed file " << file << " to output!" << endl;
  } else {
    cout << "Problems in reading Analysis Template!" << endl;
  }
}

//_____________________________________________________________

void GCardManager::StreamLumiAnalysisMC(ofstream *output, TString templatefile, TString lumi, TString inputdir, TString runperiod) {
  //
  // stream analysis.template to output and change LUMI and MC flag
  if ( gDebug ) cout << "GCardManager::StreamLumiAnalysisMC() called" << endl;

  TString file = gSystem->Which(fAnalysisTemplateDir,templatefile);
  
  if ( file.Length() ) {
    ifstream input(file.Data());
    TString line;
    while ( line.ReadLine(input,kFALSE) ) {
      if ( line.Contains("GENERAL-INPUTDIR") ) {
	line = "GENERAL-INPUTDIR ";
	line.Append(inputdir);
      }
      // replace lumi
      if ( line.Contains("GENERAL-LUMINOSITY") ) {
	line = "GENERAL-LUMINOSITY ";
	line.Append(lumi);
      }
      if ( line.Contains("GENERAL-MC") ) {
	line = "GENERAL-MC ON";
      }
      // replace MC run period
      if ( line.Contains("GENERAL-RUNPERIODMC") ) {
	line = "GENERAL-RUNPERIODMC ";
	line.Append(runperiod);
      }
      // replace lower MC Selection Q2 cut
      if ( line.Contains("GENERAL-Q2MCSELECTIONCUT") ) {
	line = "GENERAL-Q2MCSELECTIONCUT -999999.99";
      }	
      
      *output << line.Data() << endl;
    }
    //    cout << "Successfully streamed file " << file << " to output!" << endl;
  } else {
    cout << "Problems in reading Analysis Template!" << endl;
  }
}

//_____________________________________________________________
void GCardManager::StreamLumiAnalysisMCRAP(ofstream *output, TString templatefile, TString lumi, TString inputdir, TString runperiod) {
  //
  // stream analysis.template to output and change LUMI and MC flag
  if ( gDebug ) cout << "GCardManager::StreamLumiAnalysisMC() called" << endl;

  TString file = gSystem->Which(fAnalysisTemplateDir,templatefile);
  
  if ( file.Length() ) {
    ifstream input(file.Data());
    TString line;
    while ( line.ReadLine(input,kFALSE) ) {
      if ( line.Contains("GENERAL-INPUTDIR") ) {
	line = "GENERAL-INPUTDIR ";
	line.Append(inputdir);
      }
      // replace lumi
      if ( line.Contains("GENERAL-LUMINOSITY") ) {
	line = "GENERAL-LUMINOSITY ";
	line.Append(lumi);
      }
      if ( line.Contains("GENERAL-MC") ) {
	line = "GENERAL-MC ON";
      }
      // replace MC run period
      if ( line.Contains("GENERAL-RUNPERIODMC") ) {
	line = "GENERAL-RUNPERIODMC ";
	line.Append(runperiod);
      }
      // replace lower MC Selection Q2 cut
      if ( line.Contains("GENERAL-Q2MCLOWCUT") ) {
	line = "GENERAL-Q2MCLOWCUT YES";
      }	
      
      *output << line.Data() << endl;
    }
    //    cout << "Successfully streamed file " << file << " to output!" << endl;
  } else {
    cout << "Problems in reading Analysis Template!" << endl;
  }
}

//_____________________________________________________________

void GCardManager::StreamLumiAnalysisMCLFRAP(ofstream *output, TString templatefile, TString lumi, TString inputdir, TString runperiod) {
  //
  // stream analysis.template to output and change LUMI and MC flag, including setting MCLF flag to ON
  if ( gDebug ) cout << "GCardManager::StreamLumiAnalysisMCLFRAP() called" << endl;

  TString file = gSystem->Which(fAnalysisTemplateDir,templatefile);
  
  if ( file.Length() ) {
    ifstream input(file.Data());
    TString line;
    while ( line.ReadLine(input,kFALSE) ) {
      if ( line.Contains("GENERAL-INPUTDIR") ) {
	line = "GENERAL-INPUTDIR ";
	line.Append(inputdir);
      }
      // replace lumi
      if ( line.Contains("GENERAL-LUMINOSITY") ) {
	line = "GENERAL-LUMINOSITY ";
	line.Append(lumi);
      }
      // replace MC
      if ( line.Contains("GENERAL-LFMC") ) {
	line = "GENERAL-LFMC ON";
      } else if ( line.Contains("GENERAL-DOLFREWEIGHT") ) {
	line = "GENERAL-DOLFREWEIGHT OFF";
      } else if ( line.Contains("GENERAL-MC") ) {
	line = "GENERAL-MC ON";
      }
      // replace MC run period
      if ( line.Contains("GENERAL-RUNPERIODMC") ) {
	line = "GENERAL-RUNPERIODMC ";
	line.Append(runperiod);
      }
      // replace lower MC Selection Q2 cut
      if ( line.Contains("GENERAL-Q2MCLOWCUT") ) {
	line = "GENERAL-Q2MCLOWCUT YES";
      }	
      
      *output << line.Data() << endl;
    }
    //    cout << "Successfully streamed file " << file << " to output!" << endl;
  } else {
    cout << "Problems in reading Analysis Template!" << endl;
  }
}

//_____________________________________________________________

void GCardManager::StreamLumiAnalysisMCLF(ofstream *output, TString templatefile, TString lumi, TString inputdir, TString runperiod) {
  //
  // stream analysis.template to output and change LUMI and MC flag, including setting MCLF flag to ON
  if ( gDebug ) cout << "GCardManager::StreamLumiAnalysisMCLF() called" << endl;

  TString file = gSystem->Which(fAnalysisTemplateDir,templatefile);
  
  if ( file.Length() ) {
    ifstream input(file.Data());
    TString line;
    while ( line.ReadLine(input,kFALSE) ) {
      if ( line.Contains("GENERAL-INPUTDIR") ) {
	line = "GENERAL-INPUTDIR ";
	line.Append(inputdir);
      }
      // replace lumi
      if ( line.Contains("GENERAL-LUMINOSITY") ) {
	line = "GENERAL-LUMINOSITY ";
	line.Append(lumi);
      }
      // replace MC
      if ( line.Contains("GENERAL-LFMC") ) {
	line = "GENERAL-LFMC ON";
      } else if ( line.Contains("GENERAL-DOLFREWEIGHT") ) {
	line = "GENERAL-DOLFREWEIGHT OFF";
      } else if ( line.Contains("GENERAL-MC") ) {
	line = "GENERAL-MC ON";
      }
      // replace MC run period
      if ( line.Contains("GENERAL-RUNPERIODMC") ) {
	line = "GENERAL-RUNPERIODMC ";
	line.Append(runperiod);
      }
      // replace lower MC Selection Q2 cut
      if ( line.Contains("GENERAL-Q2MCLOWCUT") ) {
	line = "GENERAL-Q2MCLOWCUT NO";
      }	
      
      *output << line.Data() << endl;
    }
    //    cout << "Successfully streamed file " << file << " to output!" << endl;
  } else {
    cout << "Problems in reading Analysis Template!" << endl;
  }
}

//_____________________________________________________________

void GCardManager::StreamLumiAnalysisMCBBBAR(ofstream *output, TString templatefile, TString lumi, TString inputdir, TString runperiod) {
  //
  // stream analysis.template to output and change LUMI and MC flag, including setting MCBBBAR flag to ON
  if ( gDebug ) cout << "GCardManager::StreamLumiAnalysisMCBBBAR() called" << endl;

  TString file = gSystem->Which(fAnalysisTemplateDir,templatefile);
  
  if ( file.Length() ) {
    ifstream input(file.Data());
    TString line;
    while ( line.ReadLine(input,kFALSE) ) {
      if ( line.Contains("GENERAL-INPUTDIR") ) {
	line = "GENERAL-INPUTDIR ";
	line.Append(inputdir);
      }
      // replace lumi
      if ( line.Contains("GENERAL-LUMINOSITY") ) {
	line = "GENERAL-LUMINOSITY ";
	line.Append(lumi);
      }
      // replace MC
      // take over ownmc and ownjetsmc from template
      if ( line.Contains("GENERAL-BBBARMC") ) {
	line = "GENERAL-BBBARMC ON";
      } else if ( line.Contains("GENERAL-CCBARMC") ) {
	line = "GENERAL-CCBARMC OFF";
      } else if ( line.Contains("GENERAL-LFMC") ) {
	line = "GENERAL-LFMC OFF";
      } else if ( line.Contains("GENERAL-DOLFREWEIGHT") ) {
	line = "GENERAL-DOLFREWEIGHT OFF";
      } else if ( line.Contains("GENERAL-JPSIHRWGMC") ) {
	line = "GENERAL-JPSIHRWGMC OFF";
      } else if ( line.Contains("GENERAL-PSIPRIMEHRWGMC") ) {
	line = "GENERAL-PSIPRIMEHRWGMC OFF";
      } else if ( line.Contains("GENERAL-MC") ) {
	line = "GENERAL-MC ON";
      }
      // replace MC run period
      if ( line.Contains("GENERAL-RUNPERIODMC") ) {
	line = "GENERAL-RUNPERIODMC ";
	line.Append(runperiod);
      }
      // replace lower MC Selection Q2 cut
      if ( line.Contains("GENERAL-Q2MCLOWCUT") ) {
	line = "GENERAL-Q2MCLOWCUT NO";
      }	
      
      *output << line.Data() << endl;
    }
    //    cout << "Successfully streamed file " << file << " to output!" << endl;
  } else {
    cout << "Problems in reading Analysis Template!" << endl;
  }
}
//_____________________________________________________________

void GCardManager::StreamLumiAnalysisMCBBBARRAP(ofstream *output, TString templatefile, TString lumi, TString inputdir, TString runperiod) {
  //
  // stream analysis.template to output and change LUMI and MC flag, including setting MCBBBAR flag to ON and set Q2 true cut 
  if ( gDebug ) cout << "GCardManager::StreamLumiAnalysisMCBBBARRAP() called" << endl;
  
//    Double_t q2low;
  TString file = gSystem->Which(fAnalysisTemplateDir,templatefile);

  if ( file.Length() ) {
    ifstream input(file.Data());
    TString line;
    while ( line.ReadLine(input,kFALSE) ) {
      if ( line.Contains("GENERAL-INPUTDIR") ) {
	line = "GENERAL-INPUTDIR ";
	line.Append(inputdir);
      }
      // replace lumi
      if ( line.Contains("GENERAL-LUMINOSITY") ) {
	line = "GENERAL-LUMINOSITY ";
	line.Append(lumi);
      }
      // replace MC
      // take over ownmc and ownjetsmc from template
      if ( line.Contains("GENERAL-BBBARMC") ) {
	line = "GENERAL-BBBARMC ON";
      } else if ( line.Contains("GENERAL-CCBARMC") ) {
	line = "GENERAL-CCBARMC OFF";
      } else if ( line.Contains("GENERAL-LFMC") ) {
	line = "GENERAL-LFMC OFF";
      } else if ( line.Contains("GENERAL-DOLFREWEIGHT") ) {
	line = "GENERAL-DOLFREWEIGHT OFF";
      } else if ( line.Contains("GENERAL-JPSIHRWGMC") ) {
	line = "GENERAL-JPSIHRWGMC OFF";
      } else if ( line.Contains("GENERAL-PSIPRIMEHRWGMC") ) {
	line = "GENERAL-PSIPRIMEHRWGMC OFF";
      } else if ( line.Contains("GENERAL-MC") ) {
	line = "GENERAL-MC ON";
      }
      // replace MC run period
      if ( line.Contains("GENERAL-RUNPERIODMC") ) {
	line = "GENERAL-RUNPERIODMC ";
	line.Append(runperiod);
      }
      // replace lower MC Selection Q2 cut
      if ( line.Contains("GENERAL-Q2MCLOWCUT") ) {
	line = "GENERAL-Q2MCLOWCUT YES";
      }	
      *output << line.Data() << endl;
    }
    //    cout << "Successfully streamed file " << file << " to output!" << endl;
  } else {
    cout << "Problems in reading Analysis Template!" << endl;
  }
}

//_____________________________________________________________

void GCardManager::StreamLumiAnalysisMCCCBAR(ofstream *output, TString templatefile, TString lumi, TString inputdir, TString runperiod) {
  //
  // stream analysis.template to output and change LUMI and MC flag, including setting MCCCBAR flag to ON
  if ( gDebug ) cout << "GCardManager::StreamLumiAnalysisMCCCBAR() called" << endl;

  TString file = gSystem->Which(fAnalysisTemplateDir,templatefile);
  
  if ( file.Length() ) {
    ifstream input(file.Data());
    TString line;
    while ( line.ReadLine(input,kFALSE) ) {
      if ( line.Contains("GENERAL-INPUTDIR") ) {
	line = "GENERAL-INPUTDIR ";
	line.Append(inputdir);
      }
      // replace lumi
      if ( line.Contains("GENERAL-LUMINOSITY") ) {
	line = "GENERAL-LUMINOSITY ";
	line.Append(lumi);
      }
      // replace MC
      // take over ownmc and ownjetsmc from template
      if ( line.Contains("GENERAL-CCBARMC") ) {
	line = "GENERAL-CCBARMC ON";
      } else if ( line.Contains("GENERAL-DOCREWEIGHT") ) {
	line = "GENERAL-DOCREWEIGHT OFF";
      } else if ( line.Contains("GENERAL-DOLFREWEIGHT") ) {
	line = "GENERAL-DOLFREWEIGHT OFF";
      } else if ( line.Contains("GENERAL-BBBARMC") ) {
	line = "GENERAL-BBBARMC OFF";
      } else if ( line.Contains("GENERAL-LFMC") ) {
	line = "GENERAL-LFMC OFF";
      } else if ( line.Contains("GENERAL-JPSIHRWGMC") ) {
	line = "GENERAL-JPSIHRWGMC OFF";
      } else if ( line.Contains("GENERAL-PSIPRIMEHRWGMC") ) {
	line = "GENERAL-PSIPRIMEHRWGMC OFF";
      } else if ( line.Contains("GENERAL-MC") ) {
	line = "GENERAL-MC ON";
      }
      // replace MC run period
      if ( line.Contains("GENERAL-RUNPERIODMC") ) {
	line = "GENERAL-RUNPERIODMC ";
	line.Append(runperiod);
      }
      // replace lower MC Selection Q2 cut
      if ( line.Contains("GENERAL-Q2MCLOWCUT") ) {
	line = "GENERAL-Q2MCLOWCUT NO";
      }	
      
      *output << line.Data() << endl;
    }
    //    cout << "Successfully streamed file " << file << " to output!" << endl;
  } else {
    cout << "Problems in reading Analysis Template!" << endl;
  }
}

//_____________________________________________________________

void GCardManager::StreamLumiAnalysisMCCCBARRAP(ofstream *output, TString templatefile, TString lumi, TString inputdir, TString runperiod) {
  //
  // stream analysis.template to output and change LUMI and MC flag, including setting MCCCBAR flag to ON
  if ( gDebug ) cout << "GCardManager::StreamLumiAnalysisMCCCBARRAP() called" << endl;

  TString file = gSystem->Which(fAnalysisTemplateDir,templatefile);
  
  if ( file.Length() ) {
    ifstream input(file.Data());
    TString line;
    while ( line.ReadLine(input,kFALSE) ) {
      if ( line.Contains("GENERAL-INPUTDIR") ) {
	line = "GENERAL-INPUTDIR ";
	line.Append(inputdir);
      }
      // replace lumi
      if ( line.Contains("GENERAL-LUMINOSITY") ) {
	line = "GENERAL-LUMINOSITY ";
	line.Append(lumi);
      }
      // replace MC
      // take over ownmc and ownjetsmc from template
      if ( line.Contains("GENERAL-CCBARMC") ) {
	line = "GENERAL-CCBARMC ON";
      } else if ( line.Contains("GENERAL-DOCREWEIGHT") ) {
	line = "GENERAL-DOCREWEIGHT OFF";
      } else if ( line.Contains("GENERAL-DOLFREWEIGHT") ) {
	line = "GENERAL-DOLFREWEIGHT OFF";
      } else if ( line.Contains("GENERAL-BBBARMC") ) {
	line = "GENERAL-BBBARMC OFF";
      } else if ( line.Contains("GENERAL-LFMC") ) {
	line = "GENERAL-LFMC OFF";
      } else if ( line.Contains("GENERAL-JPSIHRWGMC") ) {
	line = "GENERAL-JPSIHRWGMC OFF";
      } else if ( line.Contains("GENERAL-PSIPRIMEHRWGMC") ) {
	line = "GENERAL-PSIPRIMEHRWGMC OFF";
      } else if ( line.Contains("GENERAL-MC") ) {
	line = "GENERAL-MC ON";
      }
      // replace MC run period
      if ( line.Contains("GENERAL-RUNPERIODMC") ) {
	line = "GENERAL-RUNPERIODMC ";
	line.Append(runperiod);
      }
      // replace lower MC Selection Q2 cut
      if ( line.Contains("GENERAL-Q2MCLOWCUT") ) {
	line = "GENERAL-Q2MCLOWCUT YES";
      }	
      
      *output << line.Data() << endl;
    }
    //    cout << "Successfully streamed file " << file << " to output!" << endl;
  } else {
    cout << "Problems in reading Analysis Template!" << endl;
  }
}

//_____________________________________________________________

void GCardManager::StreamLumiAnalysisMCCCBARREWEIGHT(ofstream *output, TString templatefile, TString lumi, TString inputdir, TString runperiod) {
  //
  // stream analysis.template to output and change LUMI and MC flag, including setting MCCCBAR flag to ON
  if ( gDebug ) cout << "GCardManager::StreamLumiAnalysisMCCCBARREWEIGHT() called" << endl;

  TString file = gSystem->Which(fAnalysisTemplateDir,templatefile);
  
  if ( file.Length() ) {
    ifstream input(file.Data());
    TString line;
    while ( line.ReadLine(input,kFALSE) ) {
      if ( line.Contains("GENERAL-INPUTDIR") ) {
	line = "GENERAL-INPUTDIR ";
	line.Append(inputdir);
      }
      // replace lumi
      if ( line.Contains("GENERAL-LUMINOSITY") ) {
	line = "GENERAL-LUMINOSITY ";
	line.Append(lumi);
      }
      // replace MC
      // take over ownmc and ownjetsmc from template
      if ( line.Contains("GENERAL-CCBARMC") ) {
	line = "GENERAL-CCBARMC ON";
      } else if ( line.Contains("GENERAL-DOCREWEIGHT") ) {
	line = "GENERAL-DOCREWEIGHT ON";
      } else if ( line.Contains("GENERAL-DOLFREWEIGHT") ) {
	line = "GENERAL-DOLFREWEIGHT OFF";
      } else if ( line.Contains("GENERAL-BBBARMC") ) {
	line = "GENERAL-BBBARMC OFF";
      } else if ( line.Contains("GENERAL-LFMC") ) {
	line = "GENERAL-LFMC OFF";
      } else if ( line.Contains("GENERAL-JPSIHRWGMC") ) {
	line = "GENERAL-JPSIHRWGMC OFF";
      } else if ( line.Contains("GENERAL-PSIPRIMEHRWGMC") ) {
	line = "GENERAL-PSIPRIMEHRWGMC OFF";
      } else if ( line.Contains("GENERAL-MC") ) {
	line = "GENERAL-MC ON";
      }
      // replace MC run period
      if ( line.Contains("GENERAL-RUNPERIODMC") ) {
	line = "GENERAL-RUNPERIODMC ";
	line.Append(runperiod);
      }
      // replace lower MC Selection Q2 cut
      if ( line.Contains("GENERAL-Q2MCLOWCUT") ) {
	line = "GENERAL-Q2MCLOWCUT YES";
      }	
      
      *output << line.Data() << endl;
    }
    //    cout << "Successfully streamed file " << file << " to output!" << endl;
  } else {
    cout << "Problems in reading Analysis Template!" << endl;
  }
}

//_____________________________________________________________
void GCardManager::StreamLumiAnalysisMCLFREWEIGHT(ofstream *output, TString templatefile, TString lumi, TString inputdir, TString runperiod) {
  //
  // stream analysis.template to output and change LUMI and MC flag, including setting MCLF flag to ON
  if ( gDebug ) cout << "GCardManager::StreamLumiAnalysisMCLFREWEIGHT() called" << endl;

  TString file = gSystem->Which(fAnalysisTemplateDir,templatefile);
  
  if ( file.Length() ) {
    ifstream input(file.Data());
    TString line;
    while ( line.ReadLine(input,kFALSE) ) {
      if ( line.Contains("GENERAL-INPUTDIR") ) {
	line = "GENERAL-INPUTDIR ";
	line.Append(inputdir);
      }
      // replace lumi
      if ( line.Contains("GENERAL-LUMINOSITY") ) {
	line = "GENERAL-LUMINOSITY ";
	line.Append(lumi);
      }
      // replace MC
      // take over ownmc and ownjetsmc from template
      if ( line.Contains("GENERAL-CCBARMC") ) {
	line = "GENERAL-CCBARMC OFF";
      } else if ( line.Contains("GENERAL-DOCREWEIGHT") ) {
	line = "GENERAL-DOCREWEIGHT OFF";
      } else if ( line.Contains("GENERAL-DOLFREWEIGHT") ) {
	line = "GENERAL-DOLFREWEIGHT ON";
      } else if ( line.Contains("GENERAL-BBBARMC") ) {
	line = "GENERAL-BBBARMC OFF";
      } else if ( line.Contains("GENERAL-LFMC") ) {
	line = "GENERAL-LFMC ON";
      } else if ( line.Contains("GENERAL-JPSIHRWGMC") ) {
	line = "GENERAL-JPSIHRWGMC OFF";
      } else if ( line.Contains("GENERAL-PSIPRIMEHRWGMC") ) {
	line = "GENERAL-PSIPRIMEHRWGMC OFF";
      } else if ( line.Contains("GENERAL-MC") ) {
	line = "GENERAL-MC ON";
      }
      // replace MC run period
      if ( line.Contains("GENERAL-RUNPERIODMC") ) {
	line = "GENERAL-RUNPERIODMC ";
	line.Append(runperiod);
      }
      // replace lower MC Selection Q2 cut
      if ( line.Contains("GENERAL-Q2MCLOWCUT") ) {
	line = "GENERAL-Q2MCLOWCUT YES";
      }	
      
      *output << line.Data() << endl;
    }
    //    cout << "Successfully streamed file " << file << " to output!" << endl;
  } else {
    cout << "Problems in reading Analysis Template!" << endl;
  }
}

//_____________________________________________________________

void GCardManager::StreamLumiAnalysisMCJPSIHRWG(ofstream *output, TString templatefile, TString lumi, TString inputdir, TString runperiod) {
  //
  // stream analysis.template to output and change LUMI and MC flag, including setting MCJPSIHRWG flag to ON
  if ( gDebug ) cout << "GCardManager::StreamLumiAnalysisMCJPSIHRWG() called" << endl;

  TString file = gSystem->Which(fAnalysisTemplateDir,templatefile);
  
  if ( file.Length() ) {
    ifstream input(file.Data());
    TString line;
    while ( line.ReadLine(input,kFALSE) ) {
      if ( line.Contains("GENERAL-INPUTDIR") ) {
	line = "GENERAL-INPUTDIR ";
	line.Append(inputdir);
      }
      // replace lumi
      if ( line.Contains("GENERAL-LUMINOSITY") ) {
	line = "GENERAL-LUMINOSITY ";
	line.Append(lumi);
      }
      // replace MC
      // take over ownmc and ownjetsmc from template
      if ( line.Contains("GENERAL-JPSIHRWGMC") ) {
	line = "GENERAL-JPSIHRWGMC ON";
      } else if ( line.Contains("GENERAL-BBBARMC") ) {
	line = "GENERAL-BBBARMC OFF";
      } else if ( line.Contains("GENERAL-CCBARMC") ) {
	line = "GENERAL-CCBARMC OFF";
      } else if ( line.Contains("GENERAL-LFMC") ) {
	line = "GENERAL-LFMC OFF";
      } else if ( line.Contains("GENERAL-MC") ) {
	line = "GENERAL-MC ON";
      }
      // replace MC run period
      if ( line.Contains("GENERAL-RUNPERIODMC") ) {
	line = "GENERAL-RUNPERIODMC ";
	line.Append(runperiod);
      }
      // replace lower MC Selection Q2 cut
      if ( line.Contains("GENERAL-Q2MCSELECTIONCUT") ) {
	line = "GENERAL-Q2MCSELECTIONCUT -999999.99";
      }	
      
      *output << line.Data() << endl;
    }
    //    cout << "Successfully streamed file " << file << " to output!" << endl;
  } else {
    cout << "Problems in reading Analysis Template!" << endl;
  }
}

//_____________________________________________________________

void GCardManager::StreamLumiAnalysisMCPSIPRIMEHRWG(ofstream *output, TString templatefile, TString lumi, TString inputdir, TString runperiod) {
  //
  // stream analysis.template to output and change LUMI and MC flag, including setting MCPSIPRIMEHRWG flag to ON
  if ( gDebug ) cout << "GCardManager::StreamLumiAnalysisMCPSIPRIMEHRWG() called" << endl;

  TString file = gSystem->Which(fAnalysisTemplateDir,templatefile);
  
  if ( file.Length() ) {
    ifstream input(file.Data());
    TString line;
    while ( line.ReadLine(input,kFALSE) ) {
      if ( line.Contains("GENERAL-INPUTDIR") ) {
	line = "GENERAL-INPUTDIR ";
	line.Append(inputdir);
      }
      // replace lumi
      if ( line.Contains("GENERAL-LUMINOSITY") ) {
	line = "GENERAL-LUMINOSITY ";
	line.Append(lumi);
      }
      // replace MC
      // take over ownmc and ownjetsmc from template
      if ( line.Contains("GENERAL-PSIPRIMEHRWGMC") ) {
	line = "GENERAL-PSIPRIMEHRWGMC ON";
      } else if ( line.Contains("GENERAL-BBBARMC") ) {
	line = "GENERAL-BBBARMC OFF";
      } else if ( line.Contains("GENERAL-CCBARMC") ) {
	line = "GENERAL-CCBARMC OFF";
      } else if ( line.Contains("GENERAL-LFMC") ) {
	line = "GENERAL-LFMC OFF";
      } else if ( line.Contains("GENERAL-MC") ) {
	line = "GENERAL-MC ON";
      }
      // replace MC run period
      if ( line.Contains("GENERAL-RUNPERIODMC") ) {
	line = "GENERAL-RUNPERIODMC ";
	line.Append(runperiod);
      }
      // replace lower MC Selection Q2 cut
      if ( line.Contains("GENERAL-Q2MCSELECTIONCUT") ) {
	line = "GENERAL-Q2MCSELECTIONCUT -999999.99";
      }	
      
      *output << line.Data() << endl;
    }
    //    cout << "Successfully streamed file " << file << " to output!" << endl;
  } else {
    cout << "Problems in reading Analysis Template!" << endl;
  }
}


//_____________________________________________________________

void GCardManager::ConcatenateMC(TString mcfile, TString timeperiod, TString selfile) {
  //
  // concatenate card-file in ZES mode
  if ( gDebug ) cout << "GCardManager::ConcatenateMC() called" << endl;

  // output stream
  ofstream *output = new ofstream(selfile);

  StreamStart(output);
  StreamMCStart(output);
  StreamMCSelect(output,mcfile);
  StreamOrange(output,timeperiod);
  StreamMagField(output);
  StreamGeant(output);
  StreamMozart(output);
  StreamHera(output);
  StreamDetector(output,timeperiod);
  StreamReco(output);
  StreamBremat(output);
  StreamGutcard(output,kTRUE);
  StreamGeneral(output);

  delete output;
}

//_____________________________________________________________

void GCardManager::ConcatenateMC2(TString filespercard, TString mcfile, TString timeperiod, TString selfile) {
  //
  // concatenate card-file in MC mode with multiple output files
  if ( gDebug ) cout << "GCardManager::ConcatenateMC() called" << endl;

  // decode char string for number of files per card
  Int_t filesperfile = 0;
  istrstream input2(filespercard);
  input2 >> filesperfile;

  Bool_t emptyfile = kFALSE;



  // scan through input file
  TString file2 = gSystem->Which(fTemplateDir.Data(),mcfile);

  ofstream *dummy = new ofstream(fDummyFile.Data());
  emptyfile = kTRUE;
  
  if ( file2.Length() > 0 ) {

    ifstream input(file2.Data());
    TString line = "";
    TString save = "";
    TString current = "";

    Int_t outputfile = 1;
    Int_t file     = 0;
    Int_t currentnumber = 0;
    Int_t lastdot = 0;

    while ( line.ReadLine(input,kFALSE) ) {

//        if ( !line.BeginsWith("C") ) {
      if ( line.BeginsWith("ZEUSIO-INFI",TString::kIgnoreCase) ) {
	// current number of included mc file
	if ( currentnumber == 0 ) {
	  // identify which mc file number for this currentnumber
	  save = line;
	  lastdot = save.Last(46);
	  save.Remove(lastdot,save.Length()-lastdot);
	  lastdot = save.Last(46);
	  save.Remove(0,lastdot);
	  save.Append(".");

	  // increase file in output counter
	  file += 1;
      
	  // increase currentnumber
	  currentnumber += 1;
	}

	if ( file < filesperfile ) {
	  if ( line.Contains(save.Data()) ) {
	    // stream line to dummy output
	    *dummy << line.Data() << endl;
	    emptyfile = kFALSE;
	  } else {
	    file += 1;

	    // identify which mc file number for this currentnumber
	    save = line;
	    lastdot = save.Last(46);
	    save.Remove(lastdot,save.Length()-lastdot);
	    lastdot = save.Last(46);
	    save.Remove(0,lastdot);
	    save.Append(".");

	    // stream line to dummy file
	    *dummy << line.Data() << endl;
	    emptyfile = kFALSE;
	  }    
	} else {
	  if ( line.Contains(save.Data()) ) {
	    // stream line to dummy output
	    *dummy << line.Data() << endl;
	    emptyfile = kFALSE;
	  } else {	  // generate output file name
	    TString dummyname = selfile;
	    dummyname.ReplaceAll(".cards","");
	    if ( outputfile < 10 ) {
	      dummyname.Append("_000");
	      dummyname += outputfile;
	      dummyname.Append(".cards");
	    } else if ( outputfile < 100 ) {
	      dummyname.Append("_00");
	      dummyname += outputfile;
	      dummyname.Append(".cards");
	    } else if ( outputfile < 1000 ) {
	      dummyname.Append("_0");
	      dummyname += outputfile;
	      dummyname.Append(".cards");
	    } else {
	      dummyname += outputfile;
	      dummyname.Append(".cards");
	    }
	    // call generation of file
	    ConcatenateMC(fDummyFile.Data(),timeperiod,dummyname.Data());

	    // remove dummy file and generate again
	    delete dummy;
	    TString deletestring = fDummyFile.Data();
	    deletestring.Prepend("rm ");
	    gSystem->Exec(deletestring.Data());
	    dummy = new ofstream(fDummyFile.Data());
	    emptyfile = kTRUE;
	    outputfile += 1;

	    // identify which mc file number for this currentnumber
	    save = line;
	    lastdot = save.Last(46);
	    save.Remove(lastdot,save.Length()-lastdot);
	    lastdot = save.Last(46);
	    save.Remove(0,lastdot);
	    save.Append(".");

	    // stream line to dummy file
	    *dummy << line.Data() << endl;
	    emptyfile = kFALSE;

	    // set file
	    file = 1;
	  }
	}
      }
    }
    // write out last dummy file
    if ( !emptyfile ) {
      TString dummyname = selfile;
      dummyname.ReplaceAll(".cards","");
      if ( outputfile < 10 ) {
	dummyname.Append("_000");
	dummyname += outputfile;
	dummyname.Append(".cards");
      } else if ( outputfile < 100 ) {
	dummyname.Append("_00");
	dummyname += outputfile;
	dummyname.Append(".cards");
      } else if ( outputfile < 1000 ) {
	dummyname.Append("_0");
	dummyname += outputfile;
	dummyname.Append(".cards");
      } else {
	dummyname += outputfile;
	dummyname.Append(".cards");
      }
      ConcatenateMC(fDummyFile.Data(),timeperiod,dummyname.Data());
    }
    
    TString deletestring = fDummyFile.Data();
    deletestring.Prepend("rm ");
    gSystem->Exec(deletestring.Data());
  } else {
    cout << "Problems in reading MC Select Template!" << endl;
  }

  delete dummy;
}

//_____________________________________________________________

//_____________________________________________________________

void GCardManager::ConcatenateMCZES2(TString filespercard, TString mcfile, TString cutfile, TString timeperiod, TString selfile) {
  //
  // concatenate card-file in ZES mode with multiple output files
  if ( gDebug ) cout << "GCardManager::ConcatenateMC() called" << endl;

  // decode char string for number of files per card
  Int_t filesperfile = 0;
  istrstream input2(filespercard);
  input2 >> filesperfile;

  Bool_t emptyfile = kFALSE;

  // scan through input file
  TString file2 = gSystem->Which(fTemplateDir.Data(),mcfile);

  ofstream *dummy = new ofstream(fDummyFile.Data());
  emptyfile = kTRUE;

  if ( file2.Length() > 0 ) {

    ifstream input(file2.Data());
    TString line = "";
    TString save = "";
    TString current = "";

    Int_t outputfile = 1;
    Int_t file     = 0;
    Int_t currentnumber = 0;

    while ( line.ReadLine(input,kFALSE) ) {

      if ( !line.BeginsWith("C") ) {

	// current number of included mc file
	if ( currentnumber == 0 ) {
	  // identify which mc file number for this currentnumber
	  save = line;
	  save.Remove(save.Length()-3,3);
	  save.Remove(0,save.Length()-4);
      
	  // increase file in output counter
	  file += 1;
      
	  // increase currentnumber
	  currentnumber += 1;
	}

	if ( file < filesperfile ) {
	  if ( line.Contains(save.Data()) ) {
	    // stream line to dummy output
	    *dummy << line.Data() << endl;
	    emptyfile = kFALSE;
	  } else {
	    file += 1;

	    // identify which mc file number for this currentnumber
	    save = line;
	    save.Remove(save.Length()-3,3);
	    save.Remove(0,save.Length()-4);

	    // stream line to dummy file
	    *dummy << line.Data() << endl;
	    emptyfile = kFALSE;
	  }    
	} else {
	  if ( line.Contains(save.Data()) ) {
	    // stream line to dummy output
	    *dummy << line.Data() << endl;
	    emptyfile = kFALSE;
	  } else {	  // generate output file name
	    TString dummyname = selfile;
	    dummyname.ReplaceAll(".cards","");
	    if ( outputfile < 10 ) {
	      dummyname.Append("_000");
	      dummyname += outputfile;
	      dummyname.Append(".cards");
	    } else if ( outputfile < 100 ) {
	      dummyname.Append("_00");
	      dummyname += outputfile;
	      dummyname.Append(".cards");
	    } else if ( outputfile < 1000 ) {
	      dummyname.Append("_0");
	      dummyname += outputfile;
	      dummyname.Append(".cards");
	    } else {
	      dummyname += outputfile;
	      dummyname.Append(".cards");
	    }
	    // call generation of file
	    ConcatenateMCZES(fDummyFile.Data(),cutfile,timeperiod,dummyname.Data());

	    // remove dummy file and generate again
	    delete dummy;
	    TString deletestring = fDummyFile.Data();
	    deletestring.Prepend("rm ");
	    gSystem->Exec(deletestring.Data());
	    dummy = new ofstream(fDummyFile.Data());
	    emptyfile = kTRUE;
	    outputfile += 1;

	    // identify which mc file number for this currentnumber
	    save = line;
	    save.Remove(save.Length()-3,3);
	    save.Remove(0,save.Length()-4);
	    
	    // stream line to dummy file
	    *dummy << line.Data() << endl;
	    emptyfile = kFALSE;

	    // set file
	    file = 1;
	  }
	}
      }
    }
    // write out last dummy file
    if ( !emptyfile ) {
      TString dummyname = selfile;
      dummyname.ReplaceAll(".cards","");
      if ( outputfile < 10 ) {
	dummyname.Append("_000");
	dummyname += outputfile;
	dummyname.Append(".cards");
      } else if ( outputfile < 100 ) {
	dummyname.Append("_00");
	dummyname += outputfile;
	dummyname.Append(".cards");
      } else if ( outputfile < 1000 ) {
	dummyname.Append("_0");
	dummyname += outputfile;
	dummyname.Append(".cards");
      } else {
	dummyname += outputfile;
	dummyname.Append(".cards");
      }
      ConcatenateMCZES(fDummyFile.Data(),cutfile,timeperiod,dummyname.Data());
    }
    
    TString deletestring = fDummyFile.Data();
    deletestring.Prepend("rm ");
    gSystem->Exec(deletestring.Data());
  } else {
    cout << "Problems in reading MC Select Template!" << endl;
  }


}

//_____________________________________________________________

void GCardManager::ConcatenateMCZES(TString mcfile, TString cutfile, TString timeperiod, TString selfile) {
  //
  // concatenate card-file in ZES mode
  if ( gDebug ) cout << "GCardManager::ConcatenateMC() called" << endl;

  // output stream
  ofstream *output = new ofstream(selfile);

  StreamStart(output);
  StreamMCStart(output);
  StreamMCZESStart(output);
  StreamZESSelect(output,cutfile);
  StreamMCSelect(output,mcfile);
  StreamOrange(output,timeperiod);
  StreamMagField(output);
  StreamGeant(output);
  StreamMozart(output);
  StreamHera(output);
  StreamDetector(output,timeperiod);
  StreamReco(output);
  StreamBremat(output);
  StreamGutcard(output,kTRUE);
  StreamGeneral(output);

  delete output;
}

//_____________________________________________________________

void GCardManager::ConcatenateZES2(TString start, TString end, TString stepsize, TString cutfile, TString timeperiod, TString selfile) {
  //
  // concatenate card-file in ZES mode
  if ( gDebug ) cout << "GCardManager::ConcatenateZES2() called" << endl;

  Int_t startnumber = 0;
  Int_t endnumber   = 0;
  Int_t stepnumber  = 0;

  istrstream startstream(start);
  startstream >> startnumber;
  istrstream endstream(end);
  endstream >> endnumber;
  istrstream stepstream(stepsize);
  stepstream >> stepnumber;

  Int_t loopend = (Int_t)((endnumber-startnumber)/stepnumber);

  for ( Int_t i = 0; i < loopend; i++ ) {

    Int_t st = startnumber + i * stepnumber;
    Int_t ed = startnumber + (i+1) * stepnumber -1;

    TString dummy(selfile);
    dummy.ReplaceAll(".cards","");
    dummy.Append("_");
    dummy += st;
    dummy.Append("_");
    dummy += ed;
    dummy.Append(".cards");
    TString dummy2("");
    dummy2 += st;
    TString dummy3("");
    dummy3 += ed;
    ConcatenateZES(dummy2.Data(),dummy3.Data(),cutfile,timeperiod,dummy.Data());
  }

  // last file
  Int_t st = startnumber + loopend * stepnumber;
  Int_t ed = endnumber;

  TString dummy(selfile);
  dummy.ReplaceAll(".cards","");
  dummy.Append("_");
  dummy += st;
  dummy.Append("_");
  dummy += ed;
  dummy.Append(".cards");
  TString dummy2;
  dummy2 += st;
  TString dummy3;
  dummy3 += ed;
  ConcatenateZES(dummy2.Data(),dummy3.Data(),cutfile,timeperiod,dummy.Data());
  
  return;

}

//_____________________________________________________________

void GCardManager::ConcatenateEVTAKE(TString year, TString partype, TString stepsize, TString selfile, TString start, TString end, TString timeperiod) {
  // start
  // concatenate card-file EVTAKE-event wise, in ZES mode
  if ( gDebug ) cout << "GCardManager::ConcatenateEVTAKE() called" << endl;

  // generate string with run ranges as specified by input parameters (year, particle type and batch size (stepsize) in nbarn^-1
 
  if ( !fGutCodeDir.EndsWith("/"))
    fGutCodeDir.Append("/");

  TString current_file = "";
  TString line = "";
  TString runrange = "";
  TString ppartype = "";

  Int_t year2 = atoi(year);

  istrstream parttstream(partype);
  parttstream >> ppartype;

  if(year2 == 94 && ( ppartype == "p" || partype == "e") ) {
    current_file.Append(fGutCodeDir);
    current_file.Append("programs/cardmaker/validruns/validruns_94ep.txt");
  }
  else if(year2 == 95 && ppartype == "p") {
    current_file.Append(fGutCodeDir);
    current_file.Append("programs/cardmaker/validruns/validruns_95.txt");
    cout<<"******* WARNING! -> 95 data contains SHIFTED VERTEX runs!! see http://www-zeus.desy.de/physics/lumi/lumi95/lumi.html"<<endl;
  }
  else if(year2 == 96 && ppartype == "p"){
    current_file.Append(fGutCodeDir);
    current_file.Append("programs/cardmaker/validruns/validruns_96.txt");
  }
  else if(year2 == 97 && ppartype == "p"){
    current_file.Append(fGutCodeDir);
    current_file.Append("programs/cardmaker/validruns/validruns_97.txt");
  }
  else if(year2 == 98 && ppartype == "e"){
    current_file.Append(fGutCodeDir);
    current_file.Append("programs/cardmaker/validruns/validruns_98e.txt");
  }
  else if(year2 == 99 && ppartype == "e"){
    current_file.Append(fGutCodeDir);
    current_file.Append("programs/cardmaker/validruns/validruns_99e.txt");
  }
  else if(year2 == 99 && ppartype == "p"){
    current_file.Append(fGutCodeDir);
    current_file.Append("programs/cardmaker/validruns/validruns_99.txt");
  }
  else if(year2 == 00 && ppartype == "p"){
    current_file.Append(fGutCodeDir);
    current_file.Append("programs/cardmaker/validruns/validruns_00.txt");
    cout<<"******* WARNING! -> 00 data contains SHIFTED VERTEX runs!! see http://www-zeus.desy.de/physics/lumi/lumi00/lumi.html "<<current_file<<endl;
  }
  else if(year2 == 03 && ppartype == "p"){
    current_file.Append(fGutCodeDir);
    current_file.Append("programs/cardmaker/validruns/validruns_03.txt");
  }
  else if(year2 == 03 && ppartype == "pmvd"){
    current_file.Append(fGutCodeDir);
    current_file.Append("programs/cardmaker/validruns/validruns_03mvd.txt");
  }
  else if(year2 == 03 && ppartype == "pstt"){
    current_file.Append(fGutCodeDir);
    current_file.Append("programs/cardmaker/validruns/validruns_03stt.txt");
  }
  else if(year2 == 04 && ppartype == "p"){
    current_file.Append(fGutCodeDir);
    current_file.Append("programs/cardmaker/validruns/validruns_04.txt");
  }
  else if(year2 == 04 && ppartype == "pmvd"){
    current_file.Append(fGutCodeDir);
    current_file.Append("programs/cardmaker/validruns/validruns_04mvd.txt");
  }
  else if(year2 == 04 && ppartype == "pstt"){
    current_file.Append(fGutCodeDir);
    current_file.Append("programs/cardmaker/validruns/validruns_04stt.txt");
  }
  else if(year2 == 05 && ppartype == "e"){
    current_file.Append(fGutCodeDir);
    current_file.Append("programs/cardmaker/validruns/validruns_05.txt");
  }
  else if(year2 == 06 && ppartype == "e"){
    current_file.Append(fGutCodeDir);
    current_file.Append("programs/cardmaker/validruns/validruns_06.txt");
  }

  else {
    cout<<"\n *** You mistyped the year / partype / size in lumi request (GCardManager::ConcatenateEVTAKE)"<<endl;
    cout<<" *** Usage example: ...(\"00\",\"p\",\"600\"), for 2000 e+, 600 nbarn^-1 per batch-job."<<endl<<endl;
    //    break;
  }

  ifstream stream(current_file);

  Float_t  lumi, lumi_sum_job, lumi_total, lumi_sum_job_old;
  Int_t    runnr, nr_of_events;
  Int_t    total_nr_of_events, firstrun, lastrun;

  Float_t  batch_size_ideal;
  Int_t    batch_nr;
  Int_t    batch_nr_of_events;
  Int_t    batch_nr_of_events_old;
  Int_t    startrun, endrun;
  Int_t    batchsize[2000];
  Float_t runlist_int[4][2000];
  Bool_t   verbose, compact;

  TString  steerer, runlist;

  for(Int_t wa=0; wa<2000; wa++){
    runlist_int[0][wa]=0.;
    runlist_int[1][wa]=0.;
    runlist_int[2][wa]=0.;
    runlist_int[3][wa]=0.;
  }
 
  long     nlines = 0;
 
  firstrun               = 0;
  lastrun                = 0;
  batch_nr               = 0;
  total_nr_of_events     = 0;
  batch_nr_of_events     = 0;
  batch_nr_of_events_old = 0;
  lumi_sum_job           = 0.0;
  lumi_sum_job_old       = 0.0;
  lumi_total             = 0.0;    
  verbose                = true;
  compact                = false;
  steerer                ="";
  // WARNING: set startrun to !=0 only if you want to start counting events from this run. Problematic still 030814
  startrun               = 0; 
  endrun                 = 0;
  //  endrun                 = 37208; 
  //  startrun               = 36089; 
  //startrun               = 33501-1; //33496 was last run
  //batch_size_ideal       = 600. / 1.6 ; // should take ~ 8h scaled cpu time (M job) - modify if orange changes! changed 030630 (div 1.6)
  //batch_size_ideal       = 600.; // enlarged again as I use the L queue anyway ...
 
  // give values to startrun and endrun:
  istrstream stream2(start);
  stream2 >> startrun;

  istrstream stream3(end);
  stream3 >> endrun;
  // give value to batch_size_ideal:
  istrstream stream4(stepsize);
  stream4 >> batch_size_ideal;
  
  while ( line.ReadLine(stream) ) {
    lastrun = runnr;
    istrstream stream5(line.Data());
    stream5 >> runnr;
    stream5 >> lumi;
    stream5 >> nr_of_events;

    if( runnr<startrun ) {
      continue;
    }
    else if( (runnr>=endrun) && endrun != 0 ){
      break;
    }
    if(firstrun==0)     firstrun=runnr;

    batch_nr_of_events_old = batch_nr_of_events;
    lumi_sum_job_old       = lumi_sum_job;
    total_nr_of_events    += nr_of_events;
    batch_nr_of_events    += nr_of_events;
    lumi_sum_job          += lumi;
    lumi_total            += lumi;
  
    if ((Int_t)lumi_sum_job/(Int_t)batch_size_ideal - (Int_t)lumi_sum_job_old/(Int_t)batch_size_ideal > 0) {
      if( lastrun<=startrun ) continue;
      batch_nr += 1;
      if(batch_nr>=2000){
	cout<<"ERROR in ConcatenateEVTAKE - too large number of jobs - increase array 'batchsize[2000]' to avoid break here"<<endl;
	break;
      }
      runrange="";
      runrange.Append("    ");
      runrange += firstrun;
      runrange.Append(" ");
      runrange += lastrun;
      runlist.Append(runrange);
      //      runlist.Append("\n");
      runlist_int[0][batch_nr-1]=(Float_t)firstrun;
      runlist_int[1][batch_nr-1]=(Float_t)lastrun;
      runlist_int[2][batch_nr-1]=batch_nr_of_events_old;
      runlist_int[3][batch_nr-1]=lumi_sum_job_old;

      firstrun = runnr;
      batch_nr_of_events -= batch_nr_of_events_old;
      batchsize[batch_nr-1] = batch_nr_of_events_old;
      lumi_sum_job = lumi;
      if(gDebug ) {
	cout<<endl<<"last job had lumi= "<<lumi_sum_job_old<<" total lumi so far: "<<lumi_total-lumi<<" firstrun "<<firstrun<<" lastrun "<<lastrun<<endl;
	cout<<endl<<"# of events in this batch: "<<batch_nr_of_events_old<<" total: "<<total_nr_of_events-nr_of_events<<endl;
	cout<<endl<<"click......... -> next M job (#"<<batch_nr <<"):"<<endl<<endl;
      }
    }

    nlines++;
  }

  // **************************************************************
  // *** output last job begin... 030806
  // **************************************************************
  lastrun = runnr;
  runrange="";
  runrange.Append("    ");
  runrange += firstrun;
  runrange.Append(" ");
  runrange += lastrun;
  runlist.Append(runrange);
  runlist_int[0][batch_nr]=(Float_t)firstrun;
  runlist_int[1][batch_nr]=(Float_t)lastrun;
  runlist_int[2][batch_nr]=batch_nr_of_events; // moved batch_nr_of_events_old -> batch_nr_of_events - 040310
  runlist_int[3][batch_nr]=lumi_sum_job;

  // **************************************************************
  // *** output last job end  ... 030806
  // **************************************************************
  if( gDebug ){
    cout<<"\n\t****   # of runs             : "<<nlines<<endl;
    cout<<"\t****   total lumi [nbarn^-1] : "<<lumi_total<<endl;
    cout<<"\t****   total # of events     : "<<total_nr_of_events<<" \n\t****   estimated # of M jobs : "<<batch_nr+1<<endl;
    cout<<endl<<"The list of runs for "<<current_file<<" is: "<<endl<<runlist<<endl;
    cout<<"************runlist_int_array:*************"<<endl;
    for(Int_t was=0; was<=batch_nr; was++){
      cout<<"    "<<runlist_int[0][was]<<" "<<runlist_int[1][was]<<" #ev: "<<runlist_int[2][was]<<" lumi: "<<runlist_int[3][was]<<"  batch_nr: "<<was+1<<endl;
    }
    cout<<"*******************************************"<<endl;
  }

  // use generated integerarray runlist_int of run ranges: (TString runlist unused so far!)

//   Int_t startnumber = 0;
//   Int_t endnumber   = 0;
//   Int_t stepnumber  = 0;

  //   Int_t loopend = (Int_t)((endnumber-startnumber)/stepnumber);

  for ( Int_t i = 0; runlist_int[0][i]; i++ ) {
    Int_t st = (Int_t) runlist_int[0][i];
    Int_t ed = (Int_t) runlist_int[1][i];

    if( gDebug )cout<<"Start run:"<<st<<" End run: "<<ed<<endl;

    TString dummy(selfile);
    dummy.ReplaceAll(".cards","");
    dummy.Append("_");
    dummy += st;
    dummy.Append("_");
    dummy += ed;
    dummy.Append(".cards");
    TString dummy2("");
    dummy2 += st;
    TString dummy3("");
    dummy3 += ed;
    this->ConcatenateZES(dummy2.Data(),dummy3.Data(),"DUMMY",timeperiod,dummy.Data());
  }
  for(Int_t was=0; was<=batch_nr; was++){
    cout<<"    " <<setw(8)<<runlist_int[0][was]<<" "<<setw(8)<<runlist_int[1][was]<<" #ev: "<<setw(8)<<setprecision(8)<<runlist_int[2][was]<<" lumi: "<<setw(8)<<setprecision(5)<<runlist_int[3][was]<<"  batch_nr: "<<setw(3)<<setprecision(8)<<was+1<<endl;
  }
  cout << "    " << "total number of events: " << total_nr_of_events << endl;
  cout << "    " << "total lumi: " << lumi_total << endl;
  return;

}

//_____________________________________________________________

void GCardManager::ConcatenateEVMINI(TString year, TString partype, TString stepsize, TString selfile, TString start, TString end, TString timeperiod) {
  // start
  // concatenate card-file EVMINI-event wise, in ZES mode
  if ( gDebug ) cout << "GCardManager::ConcatenateEVMINI() called" << endl;

  // generate string with run ranges as specified by input parameters (year, particle type and batch size (stepsize) in nbarn^-1
 
  if ( !fGutCodeDir.EndsWith("/"))
    fGutCodeDir.Append("/");

  TString current_file = "";
  TString line = "";
  TString runrange = "";
  TString ppartype = "";

  Int_t year2 = atoi(year);

  istrstream parttstream(partype);
  parttstream >> ppartype;

  if(year2 == 94 && ( ppartype == "p" || partype == "e") ) {
    current_file.Append(fGutCodeDir);
    current_file.Append("programs/cardmaker/validruns/validruns_94ep.txt");
  }
  else if(year2 == 95 && ppartype == "p") {
    current_file.Append(fGutCodeDir);
    current_file.Append("programs/cardmaker/validruns/validruns_95.txt");
    cout<<"******* WARNING! -> 95 data contains SHIFTED VERTEX runs!! see http://www-zeus.desy.de/physics/lumi/lumi95/lumi.html"<<endl;
  }
  else if(year2 == 96 && ppartype == "p"){
    current_file.Append(fGutCodeDir);
    current_file.Append("programs/cardmaker/validruns/validruns_96.txt");
  }
  else if(year2 == 97 && ppartype == "p"){
    current_file.Append(fGutCodeDir);
    current_file.Append("programs/cardmaker/validruns/validruns_97.txt");
  }
  else if(year2 == 98 && ppartype == "e"){
    current_file.Append(fGutCodeDir);
    current_file.Append("programs/cardmaker/validruns/validruns_98e.txt");
  }
  else if(year2 == 99 && ppartype == "e"){
    current_file.Append(fGutCodeDir);
    current_file.Append("programs/cardmaker/validruns/validruns_99e.txt");
  }
  else if(year2 == 99 && ppartype == "p"){
    current_file.Append(fGutCodeDir);
    current_file.Append("programs/cardmaker/validruns/validruns_99.txt");
  }
  else if(year2 == 00 && ppartype == "p"){
    current_file.Append(fGutCodeDir);
    current_file.Append("programs/cardmaker/validruns/validruns_00.txt");
    cout<<"******* WARNING! -> 00 data contains SHIFTED VERTEX runs!! see http://www-zeus.desy.de/physics/lumi/lumi00/lumi.html "<<current_file<<endl;
  }
  else if(year2 == 03 && ppartype == "p"){
    current_file.Append(fGutCodeDir);
    current_file.Append("programs/cardmaker/validruns/validruns_03.txt");
  }
  else if(year2 == 03 && ppartype == "pmvd"){
    current_file.Append(fGutCodeDir);
    current_file.Append("programs/cardmaker/validruns/validruns_03mvd.txt");
  }
  else if(year2 == 03 && ppartype == "pstt"){
    current_file.Append(fGutCodeDir);
    current_file.Append("programs/cardmaker/validruns/validruns_03stt.txt");
  }
  else if(year2 == 04 && ppartype == "p"){
    current_file.Append(fGutCodeDir);
    current_file.Append("programs/cardmaker/validruns/validruns_04.txt");
  }
  else if(year2 == 04 && ppartype == "pmvd"){
    current_file.Append(fGutCodeDir);
    current_file.Append("programs/cardmaker/validruns/validruns_04mvd.txt");
  }
  else if(year2 == 04 && ppartype == "pstt"){
    current_file.Append(fGutCodeDir);
    current_file.Append("programs/cardmaker/validruns/validruns_04stt.txt");
  }
  else if(year2 == 05 && ppartype == "e"){
    current_file.Append(fGutCodeDir);
    current_file.Append("programs/cardmaker/validruns/validruns_05.txt");
  }
  else if(year2 == 06 && ppartype == "e"){
    current_file.Append(fGutCodeDir);
    current_file.Append("programs/cardmaker/validruns/validruns_06.txt");
  }

  else {
    cout<<"\n *** You mistyped the year / partype / size in lumi request (GCardManager::ConcatenateEVMINI)"<<endl;
    cout<<" *** Usage example: ...(\"00\",\"p\",\"600\"), for 2000 e+, 600 nbarn^-1 per batch-job."<<endl<<endl;
    //    break;
  }

  cout << current_file << endl;

  ifstream stream(current_file);

  Float_t  lumi_sum_job, lumi_total, lumi_sum_job_old;
  //  Int_t    runnr;
  //, nr_of_events;
  Int_t    total_nr_of_events, firstrun, lastrun;

  Float_t  batch_size_ideal;
  Int_t    batch_nr;
  Int_t    batch_nr_of_events;
  Int_t    batch_nr_of_events_old;
  Int_t    startrun, endrun;
  Int_t    batchsize[2000];
  Float_t  runlist_int[5][2000];
  TString  runlist_string[2000];
  Int_t    split;
  Bool_t   verbose, compact;
  Int_t    runnr_list[10000];
  Float_t  lumi_list[10000];
  Int_t    nr_of_events_list[10000];

  TString  steerer, runlist;

  for(Int_t wa=0; wa<2000; wa++){
    runlist_int[0][wa]=0.;
    runlist_int[1][wa]=0.;
    runlist_int[2][wa]=0.;
    runlist_int[3][wa]=0.;
    runlist_int[4][wa]=1.;
  }

  for(Int_t entry=0; entry<10000; entry++){
    runnr_list[entry]=0;
    lumi_list[entry]=0.;
    nr_of_events_list[entry]=0;
  } 
  
  long     nlines = 0;
 
  firstrun               = 0;
  lastrun                = 0;
  batch_nr               = 0;
  total_nr_of_events     = 0;
  batch_nr_of_events     = 0;
  batch_nr_of_events_old = 0;
  lumi_sum_job           = 0.0;
  lumi_sum_job_old       = 0.0;
  lumi_total             = 0.0;    
  split                  = 1;
  verbose                = true;
  compact                = false;
  steerer                ="";
  // WARNING: set startrun to !=0 only if you want to start counting events from this run. Problematic still 030814
  startrun               = 0; 
  endrun                 = 0;
  //  endrun                 = 37208; 
  //  startrun               = 36089; 
  //startrun               = 33501-1; //33496 was last run
  //batch_size_ideal       = 600. / 1.6 ; // should take ~ 8h scaled cpu time (M job) - modify if orange changes! changed 030630 (div 1.6)
  //batch_size_ideal       = 600.; // enlarged again as I use the L queue anyway ...
 
  // give values to startrun and endrun:
  istrstream stream2(start);
  stream2 >> startrun;

  istrstream stream3(end);
  stream3 >> endrun;
  // give value to batch_size_ideal:
  istrstream stream4(stepsize);
  stream4 >> batch_size_ideal;
  
  TString pass_runnr = "";

  Bool_t breaker = kFALSE;

  Int_t entry=0;
  while ( line.ReadLine(stream) && entry<10000) {
    entry++;
    //    lastrun = runnr;
    istrstream stream5(line.Data());
    stream5 >> runnr_list[entry];
    stream5 >> lumi_list[entry];
    stream5 >> nr_of_events_list[entry];

    if( (runnr_list[entry]>=endrun) && endrun != 0 ){
      breaker = kTRUE;
      cout << " breaker set!" << endl;
      break;
    }
  }

//   for(Int_t entry=0; entry<10000; entry++){
//     if (runnr_list[entry] > 0 )
//     cout << "entry " << entry << "  runnr " <<runnr_list[entry] << " lumi " << lumi_list[entry] << " evts " << nr_of_events_list[entry] << endl;
//   } 

  Int_t pos=0;
  while ( runnr_list[pos+1] ) {
    pos++;
    if (runnr_list[pos]<startrun) continue;
    if(firstrun==0)     firstrun=runnr_list[pos];
    
    //    batch_nr_of_events_old = batch_nr_of_events;
    //    lumi_sum_job_old       = lumi_sum_job;
    total_nr_of_events    += nr_of_events_list[pos];
    batch_nr_of_events    += nr_of_events_list[pos];
    lumi_sum_job          += lumi_list[pos];
    lumi_total            += lumi_list[pos];
    pass_runnr += runnr_list[pos];
    pass_runnr.Append(",");
    nlines++;

    //    cout << "runnr " << runnr_list[pos] << " lumi_sum " << lumi_sum_job << endl; 
    if ((lumi_sum_job < batch_size_ideal && lumi_sum_job + lumi_list[pos+1] > batch_size_ideal) || lumi_sum_job >= batch_size_ideal || runnr_list[pos+1] == 0) { //maximum lumi per job or end of list reached
      //      cout << " runnr_list[pos]" << runnr_list[pos] << " startrun " << startrun << endl;
      if( runnr_list[pos]<startrun ) continue;
      //      cout << " close batch!" << endl;
      if(batch_nr>=2000){
	cout<<"ERROR in ConcatenateEVMINI - too large number of jobs - increase array 'batchsize[2000]' to avoid break here"<<endl;
	break;
      }
      runrange="";
      runrange.Append("    ");
      runrange += firstrun;
      runrange.Append(" ");
      runrange += runnr_list[pos];
      runlist.Append(runrange);
      //      runlist.Append("\n");
      runlist_int[0][batch_nr]=(Float_t)firstrun;
      runlist_int[1][batch_nr]=(Float_t)runnr_list[pos];
      runlist_int[2][batch_nr]=batch_nr_of_events;
      runlist_int[3][batch_nr]=lumi_sum_job;
      if ( pass_runnr.EndsWith(",") )
	pass_runnr.Remove(pass_runnr.Length()-1,1);
      runlist_string[batch_nr]=pass_runnr;
      pass_runnr = "";
      batchsize[batch_nr] = batch_nr_of_events;

      // initialise for next batch
      firstrun = runnr_list[pos+1];
      batch_nr_of_events = 0;;
      lumi_sum_job = 0;
      batch_nr += 1;
      if(gDebug ) {
	//	cout<<endl<<"last job had lumi= "<<lumi_sum_job_old<<" total lumi so far: "<<lumi_total-lumi<<" firstrun "<<firstrun<<" lastrun "<<lastrun<<endl;
	//	cout<<endl<<"# of events in this batch: "<<batch_nr_of_events_old<<" total: "<<total_nr_of_events-nr_of_events<<endl;
	//	cout<<endl<<"click......... -> next M job (#"<<batch_nr <<"):"<<endl<<endl;
      }
    }
  }
  batch_nr--;

  // **************************************************************
  // *** output last job begin... 030806
  // **************************************************************
//   if ( breaker ) 
//     pass_runnr += runnr;
//   lastrun = runnr;
//   runrange="";
//   runrange.Append("    ");
//   runrange += firstrun;
//   runrange.Append(" ");
//   runrange += lastrun;
//   runlist.Append(runrange);
//   runlist_int[0][batch_nr]=(Float_t)firstrun;
//   runlist_int[1][batch_nr]=(Float_t)lastrun;
//   runlist_int[2][batch_nr]=batch_nr_of_events; // moved batch_nr_of_events_old -> batch_nr_of_events - 040310
//   runlist_int[3][batch_nr]=lumi_sum_job;
//   if ( pass_runnr.EndsWith(",") )
//     pass_runnr.Remove(pass_runnr.Length()-1,1);
//   runlist_string[batch_nr]=pass_runnr;
//   pass_runnr = "";

  // **************************************************************
  // *** output last job end  ... 030806
  // **************************************************************
  if( gDebug ){
    cout<<"\n\t****   # of runs             : "<<nlines<<endl;
    cout<<"\t****   total lumi [nbarn^-1] : "<<lumi_total<<endl;
    cout<<"\t****   total # of events     : "<<total_nr_of_events<<" \n\t****   estimated # of M jobs : "<<batch_nr+1<<endl;
    cout<<endl<<"The list of runs for "<<current_file<<" is: "<<endl<<runlist<<endl;
    cout<<"************runlist_int_array:*************"<<endl;
    for(Int_t was=0; was<=batch_nr; was++){
      cout<<"    "<<runlist_int[0][was]<<" "<<runlist_int[1][was]<<" #ev: "<<runlist_int[2][was]<<" lumi: "<<runlist_int[3][was]<<"  batch_nr: "<<was+1<<endl;
    }
    cout<<"*******************************************"<<endl;
  }
  
  // use generated integerarray runlist_int of run ranges: (TString runlist unused so far!)
  
  //   Int_t startnumber = 0;
  //   Int_t endnumber   = 0;
  //   Int_t stepnumber  = 0;
  
  //   Int_t loopend = (Int_t)((endnumber-startnumber)/stepnumber);

  for ( Int_t i = 0; runlist_int[0][i]; i++ ) {
    Int_t st = (Int_t) runlist_int[0][i];
    Int_t ed = (Int_t) runlist_int[1][i];

    if( gDebug )cout<<"Start run:"<<st<<" End run: "<<ed<<endl;

    // check if run has to be splitted
    split=1;
    if (st==ed){
      if (runlist_int[3][i] > batch_size_ideal) { //use 1. times ideal size as threshold to split the run
	split=(Int_t)((runlist_int[2][i]+99999)/100000); // split into chunks of 100.000 events. Should fit into a 1GB ntp file using v2007a for 05 data
	runlist_int[4][i]=split;
      }
    }
    
    TString dummy(selfile);
    dummy.ReplaceAll(".cards","");
    dummy.Append("_");
    dummy += st;
    dummy.Append("_");
    dummy += ed;
    TString dummy1("");
    dummy1=dummy;
    TString dummy2("");
    dummy2 += st;
    TString dummy3("");
    dummy3 += ed;
    TString spart;
    if (split>1) {
      cout << "Split run " << st << " (Lumi=" <<runlist_int[3][i] << ", events=" <<runlist_int[2][i] << ") into " << split << " jobs!" << endl;
      Int_t firstevent, lastevent;
      firstevent=0;
      lastevent=0;
      for (Int_t part=1;part<=split;part++){
	TString sfirstevent="";
	TString slastevent="";
	lastevent+=100000;
	if (lastevent>(Int_t)runlist_int[2][i]) // set the limit for the last batch 
	  lastevent=(Int_t)runlist_int[2][i];
	if ((Int_t)runlist_int[2][i]-lastevent<10000 && part<split){ //if only 10000 evts are left add them to the last batch
	  lastevent=(Int_t)runlist_int[2][i];
	  split-=1;
	  runlist_int[4][i]-=1;
	}
	slastevent+=lastevent;
	sfirstevent+=firstevent;
	cout << "Part " << part << " is from event " <<  firstevent << " to " << lastevent << " of " << runlist_int[2][i] << " events!" << endl;
	if (split<=9) {
	  spart = "0";
	}
	spart += part;
	dummy=dummy1;
	dummy.Append("_");
	dummy += spart;
	dummy.Append(".cards");
	this->ConcatenateMINISplit(runlist_string[i],sfirstevent,slastevent,timeperiod,dummy.Data());
	firstevent=lastevent+1;
      }
    }
    else {
      spart = "01";
      dummy.Append("_");
      dummy += spart;
      dummy.Append(".cards");
      this->ConcatenateMINI(runlist_string[i],timeperiod,dummy.Data());
    }
  }
  for(Int_t was=0; was<=batch_nr; was++){
    cout<<"    " <<setw(8)<<runlist_int[0][was]<<" "<<setw(8)<<runlist_int[1][was]<<" #ev: "<<setw(8)<<setprecision(8)<<runlist_int[2][was]<<" lumi: "<<setw(8)<<setprecision(5)<<runlist_int[3][was]<<"  batch_nr: "<<setw(3)<<setprecision(8)<<was+1<< " Parts: "<<setw(3)<<setprecision(8)<<runlist_int[4][was]<<endl;
  }
  cout << "    " << "total number of events: " << total_nr_of_events << endl;
  cout << "    " << "total lumi: " << lumi_total << endl;
  return;

}

//_____________________________________________________________

void GCardManager::StreamMagField(ofstream *output) {
  //
  // stream magfield.template to output
  if ( gDebug ) cout << "GCardManager::StreamMagField() called" << endl;

  TString file = gSystem->Which(fTemplateDir.Data(),"magfield.template");

  if ( file.Length() > 0 ) {
    ifstream input(file.Data());
    
    TString line;
    
    while ( line.ReadLine(input,kFALSE) ) {
      *output << line.Data() << endl;
    }
    //    cout << "Successfully streamed file " << file << " to output!" << endl;
  } else {
    cout << "Problems in reading MagField Template!" << endl;
  }
}

//_____________________________________________________________

void GCardManager::StreamGeant(ofstream *output) {
  //
  // stream geant.template to output
  if ( gDebug ) cout << "GCardManager::StreamGeant() called" << endl;

  TString file = gSystem->Which(fTemplateDir.Data(),"geant.template");

  if ( file.Length() > 0 ) {
    ifstream input(file.Data());
    
    TString line;
    
    while ( line.ReadLine(input,kFALSE) ) {
      *output << line.Data() << endl;
    }
    //    cout << "Successfully streamed file " << file << " to output!" << endl;
  } else {
    cout << "Problems in reading Geant Template!" << endl;
  }
}

//_____________________________________________________________

void GCardManager::StreamMozart(ofstream *output) {
  //
  // stream mozart.template to output
  if ( gDebug ) cout << "GCardManager::StreamMozart() called" << endl;

  TString file = gSystem->Which(fTemplateDir.Data(),"mozart.template");

  if ( file.Length() > 0 ) {
    ifstream input(file.Data());
    
    TString line;
    
    while ( line.ReadLine(input,kFALSE) ) {
      *output << line.Data() << endl;
    }
    //    cout << "Successfully streamed file " << file << " to output!" << endl;
  } else {
    cout << "Problems in reading Mozart Template!" << endl;
  }
}

//_____________________________________________________________

void GCardManager::StreamHera(ofstream *output) {
  //
  // stream hera.template to output
  if ( gDebug ) cout << "GCardManager::StreamHera() called" << endl;

  TString file = gSystem->Which(fTemplateDir.Data(),"hera.template");

  if ( file.Length() > 0 ) {
    ifstream input(file.Data());
    
    TString line;
    
    while ( line.ReadLine(input,kFALSE) ) {
      *output << line.Data() << endl;
    }
    //    cout << "Successfully streamed file " << file << " to output!" << endl;
  } else {
    cout << "Problems in reading Hera Template!" << endl;
  }
}

//_____________________________________________________________

void GCardManager::StreamDetector(ofstream *output, TString timeperiod) {
  //
  // stream detector.template to output
  if ( gDebug ) cout << "GCardManager::StreamDetector() called" << endl;

  TString file = "";

  if ( timeperiod.Contains("95") ||
       timeperiod.Contains("96") ||
       timeperiod.Contains("97") ||
       timeperiod.Contains("95p") ||
       timeperiod.Contains("96p-97p") ) {
    file = gSystem->Which(fTemplateDir.Data(),"detector_95p-97p.template");
  } else if ( timeperiod.Contains("98") ||
	      timeperiod.Contains("99") ||
	      timeperiod.Contains("00") ||
	      timeperiod.Contains("98e-99e")     ||
	      timeperiod.Contains("99p-00p") ) {
    file = gSystem->Which(fTemplateDir.Data(),"detector_98e-00p.template");
  } else if ( timeperiod.Contains("03") ||
	      timeperiod.Contains("04") ||
	      timeperiod.Contains("03p-04p")) {
    file = gSystem->Which(fTemplateDir.Data(),"detector_03p-04p.template");
  } else if ( timeperiod.Contains("05")) {
    file = gSystem->Which(fTemplateDir.Data(),"detector_05e.template");
  } else if ( timeperiod.Contains("06")) {
    file = gSystem->Which(fTemplateDir.Data(),"detector_06e.template");
  } else {
    cout << "wrong timeperiod for detector template" << endl;
  }
  

  if ( file.Length() > 0 ) {
    ifstream input(file.Data());
    
    TString line;
    
    while ( line.ReadLine(input,kFALSE) ) {
      *output << line.Data() << endl;
    }
    //    cout << "Successfully streamed file " << file << " to output!" << endl;
  } else {
    cout << "Problems in reading Detector Template!" << endl;
  }
}

//_____________________________________________________________

void GCardManager::StreamReco(ofstream *output) {
  //
  // stream reco.template to output
  if ( gDebug ) cout << "GCardManager::StreamReco() called" << endl;

  TString file = gSystem->Which(fTemplateDir.Data(),"reco.template");

  if ( file.Length() > 0 ) {
    ifstream input(file.Data());
    
    TString line;
    
    while ( line.ReadLine(input,kFALSE) ) {
      *output << line.Data() << endl;
    }
    //    cout << "Successfully streamed file " << file << " to output!" << endl;
  } else {
    cout << "Problems in reading Reco Template!" << endl;
  }
}

//_____________________________________________________________

void GCardManager::StreamMCZESStart(ofstream *output) {
  //
  // stream mc_zes_start.template to output
  if ( gDebug ) cout << "GCardManager::StreamMCZESStart() called" << endl;

  TString file = gSystem->Which(fTemplateDir.Data(),"mc_zes_start.template");

  if ( file.Length() > 0 ) {
    ifstream input(file.Data());
    
    TString line;
    
    while ( line.ReadLine(input,kFALSE) ) {
      *output << line.Data() << endl;
    }
    //    cout << "Successfully streamed file " << file << " to output!" << endl;
  } else {
    cout << "Problems in reading MC ZES Start Template!" << endl;
  }
}
//_____________________________________________________________

Bool_t GCardManager::CheckGutcodedir() {
  //
  // Checks if environment variable GUTCODEDIR is set
  if ( gDebug ) cout << "GCardManager::CheckGutCodedir() called" << endl;
  
  fGutCodeDir = gSystem->Getenv("GUTCODEDIR");
  if(fGutCodeDir.Length() == 0) {
    cout << "Environment variable GUTCODEDIR is not set!" << endl
	 << "Please set it before using the cardmanager." << endl;
    return kFALSE;;
  } else {
    fTemplateDir = fGutCodeDir.Data();
    fTemplateDir.Append("/orange/cards/templates/");
    fAnalysisTemplateDir = fGutCodeDir.Data();
    fAnalysisTemplateDir.Append("/analysis/cards/templates/");
    fDummyFile = fTemplateDir;
    fDummyFile.Append("dummy.txt");
    return kTRUE;
  }
}

//_____________________________________________________________

void GCardManager::ConcatenateMINI(TString runs, TString timeperiod, TString selfile) {
  //
  // concatenate card-file in MINI-DST mode
  if ( gDebug ) cout << "GCardManager::ConcatenateMINI() called" << endl;

  // output stream
  ofstream *output = new ofstream(selfile);

  StreamStart(output);
  StreamMINI(output,runs,timeperiod);
  StreamOrange(output,timeperiod);
  StreamMagField(output);
  StreamGeant(output);
  StreamMozart(output);
  StreamHera(output);
  StreamDetector(output,timeperiod);
  StreamReco(output);
  StreamBremat(output);
  StreamGutcard(output);
  StreamGeneral(output);

  delete output;
}
//_____________________________________________________________

void GCardManager::ConcatenateMINISplit(TString run, TString firstevent, TString lastevent, TString timeperiod, TString selfile) {
  //
  // concatenate card-file in MINI-DST mode
  if ( gDebug ) cout << "GCardManager::ConcatenateMINISplit() called" << endl;

  // output stream
  ofstream *output = new ofstream(selfile);

  StreamStart(output);
  StreamMINISplit(output,run,firstevent,lastevent,timeperiod);
  StreamOrange(output,timeperiod);
  StreamMagField(output);
  StreamGeant(output);
  StreamMozart(output);
  StreamHera(output);
  StreamDetector(output,timeperiod);
  StreamReco(output);
  StreamBremat(output);
  StreamGutcard(output);
  StreamGeneral(output);

  delete output;
}

//_____________________________________________________________

void GCardManager::StreamMINI(ofstream *output, TString runs, TString timeperiod) {
  //
  // stream run_mini.template to output
  // add all minidst files in runs string separated by comma
  if ( gDebug ) cout << "GCardManager::StreamZESSelect() called" << endl;

  if ( timeperiod.Contains("95p") || 
       timeperiod.Contains("96p-97p") || 
       timeperiod.Contains("98e-99e") || 
       timeperiod.Contains("99p-00p") || 
       timeperiod.Contains("03p-04p") ) {
    cout << "GCardManager::StreamMINI: You selected a MC time-period, please select a data time period" << endl;
    return;
  } else if ( timeperiod.Contains("95") || 
	      timeperiod.Contains("96") || 
	      timeperiod.Contains("97") || 
	      timeperiod.Contains("98") || 
	      timeperiod.Contains("99e") || 
	      timeperiod.Contains("99p") || 
	      timeperiod.Contains("00") || 
	      timeperiod.Contains("03") || 
	      timeperiod.Contains("04") ||
	      timeperiod.Contains("05") ||
	      timeperiod.Contains("06") ) {
  } else {
    cout << "GCardManager::StreamMINI: You selected a not-valid time-period, please select a valid time period" << endl;
  }

  // clean timeperiod to have only two digits
  TString temptimeperiod = timeperiod;
  if ( !timeperiod.Contains("05RP") && !timeperiod.Contains("99")) {    
    if ( temptimeperiod.Length() > 2 ) {
      if ( temptimeperiod.Length() != 5 ) {
	cout << "GCardManager::StreamMINI: You selected a not-valid time-period, please select a valid time period" << endl;
	return;
      } else {
	temptimeperiod.Remove(temptimeperiod.Length()-3,3);
      }
    }
  }

  // correct for 03 to 03po
  if ( temptimeperiod.Contains("03") ) {
    temptimeperiod.ReplaceAll("03","03po");
  }

  // put comma-separated list of runs into list
  TString tempruns = runs;
  TList *runlist =  new TList();
  char first;
  TString temp = "";
  while ( (first = tempruns(0)) ) {
    // remove first
    tempruns.Remove(0,1);
    // append to temp or break in case of comma
    if ( first == 44 ) {
      runlist->Add(new TObjString(temp));
      temp = "";
    } else {
      temp.Append(first);
    }
  }

  // put last entry in comma-separated list in runs-list, if not empty
  if ( temp.Length() != 0 )
    runlist->Add(new TObjString(temp));
    
  // correct for 03po
  if ( temptimeperiod.BeginsWith("03") )
    temptimeperiod = "03po";

  TString file = gSystem->Which(fTemplateDir.Data(),"mini_run.template");
    
  if ( file.Length() > 0 ) {
    
    ifstream input(file.Data());
    
    TString line;
    
    while ( line.ReadLine(input,kFALSE) ) {
      *output << line.Data() << endl;
    }

    TIter nextrun(runlist);
    TString temp = "";
    while ( TObjString *run = (TObjString*)nextrun() ) {
      temp = "ZEUSIO-INFI /zeus/data/mini";
      temp.Append(temptimeperiod);
      temp.Append("/r0");
      temp.Append(run->GetString());
      temp.Append(".z");
      *output << temp.Data() << endl;
    }
    
    //    cout << "Successfully streamed file " << file << " to output!" << endl;
  } else {
    cout << "Problems in reading RUN_MINI Template!" << endl;
  }

  runlist->Delete();
  delete runlist;

}

//_____________________________________________________________

void GCardManager::StreamMINISplit(ofstream *output, TString run, TString firstevent, TString lastevent, TString timeperiod) {
  //
  // stream run_mini.template to output
  // add minidst file in run starting from startevent to endevent
  if ( gDebug ) cout << "GCardManager::StreamMiniSplit() called" << endl;

  if ( timeperiod.Contains("95p") || 
       timeperiod.Contains("96p-97p") || 
       timeperiod.Contains("98e-99e") || 
       timeperiod.Contains("99p-00p") || 
       timeperiod.Contains("03p-04p") ) {
    cout << "GCardManager::StreamMINI: You selected a MC time-period, please select a data time period" << endl;
    return;
  } else if ( timeperiod.Contains("95") || 
	      timeperiod.Contains("96") || 
	      timeperiod.Contains("97") || 
	      timeperiod.Contains("98") || 
	      timeperiod.Contains("99e") || 
	      timeperiod.Contains("99p") || 
	      timeperiod.Contains("00") || 
	      timeperiod.Contains("03") || 
	      timeperiod.Contains("04") ||
	      timeperiod.Contains("05") ||
	      timeperiod.Contains("06") ) {
  } else {
    cout << "GCardManager::StreamMINI: You selected a not-valid time-period, please select a valid time period" << endl;
  }

  // clean timeperiod to have only two digits
  TString temptimeperiod = timeperiod;
  if ( !timeperiod.Contains("05RP") && !timeperiod.Contains("99")) {    
    if ( temptimeperiod.Length() > 2 ) {
      if ( temptimeperiod.Length() != 5 ) {
	cout << "GCardManager::StreamMINISplit: You selected a not-valid time-period, please select a valid time period" << endl;
	return;
      } else {
	temptimeperiod.Remove(temptimeperiod.Length()-3,3);
      }
    }
  }

  // correct for 03 to 03po
  if ( temptimeperiod.Contains("03") ) {
    temptimeperiod.ReplaceAll("03","03po");
  }

  // put comma-separated list of runs into list
  // should be removed, because we have only one run here
  TString tempruns = run;
  TList *runlist =  new TList();
  char first;
  TString temp = "";
  while ( (first = tempruns(0)) ) {
    // remove first
    tempruns.Remove(0,1);
    // append to temp or break in case of comma
    if ( first == 44 ) {
      runlist->Add(new TObjString(temp));
      temp = "";
    } else {
      temp.Append(first);
    }
  }

  // put last entry in comma-separated list in runs-list, if not empty
  if ( temp.Length() != 0 )
    runlist->Add(new TObjString(temp));
    
  // correct for 03po
  if ( temptimeperiod.BeginsWith("03") )
    temptimeperiod = "03po";

  TString file = gSystem->Which(fTemplateDir.Data(),"mini_run.template");
    
  if ( file.Length() > 0 ) {
    
    ifstream input(file.Data());
    
    TString line;
    
    while ( line.ReadLine(input,kFALSE) ) {
      *output << line.Data() << endl;
    }

    TIter nextrun(runlist);
    TString temp = "";
    TString temp2 = "";
    while ( TObjString *run = (TObjString*)nextrun() ) {
      temp = "ZEUSIO-INFI /zeus/data/mini";
      temp.Append(temptimeperiod);
      temp.Append("/r0");
      temp.Append(run->GetString());
      temp.Append(".z");
      *output << temp.Data() << endl;
      temp2 = "ZEUSIO-EVTR ";
      temp2.Append(run->GetString());
      temp2.Append(" ");
      temp2.Append(firstevent);
      temp2.Append(" ");
      temp2.Append(lastevent);
      *output << temp2.Data() << endl;
    }
    //    ZEUSIO-EVTR RUN EVT_MIN EVT_MAX
    //    cout << "Successfully streamed file " << file << " to output!" << endl;
  } else {
    cout << "Problems in reading RUN_MINI Template!" << endl;
  }

  runlist->Delete();
  delete runlist;

}
