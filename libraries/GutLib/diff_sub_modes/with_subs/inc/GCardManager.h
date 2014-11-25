//
// GCardManager.h
//
// $Author: kahle $
// $Date: 2007/05/18 14:57:21 $
// $Revision: 1.28 $
//

#ifndef GUT_GCardManager
#define GUT_GCardManager

#ifndef ROOT_TObject
#include <TObject.h>
#endif

#ifndef ROOT_TString
#include <TString.h>
#endif


class GCardManager : public TObject {

 private:

  TString fGutCodeDir;          // base directory
  TString fTemplateDir;         // template directory
  TString fAnalysisTemplateDir; // analysis template directory
  TString fDummyFile;           // path and name of dummy file for mc concatenation

 public:
  GCardManager();
  GCardManager(int argc, char **argv);
  virtual ~GCardManager();

  virtual void HelpMessage(); 

  virtual Bool_t CheckGutcodedir();

  virtual void DecodeCommandline(int argc, char **argv);
  
  virtual void ConcatenateZES(TString start, TString end, TString cutfile, TString timeperiod, TString selfile);
  virtual void ConcatenateZES2(TString start, TString end, TString stepsize, TString cutfile, TString timeperiod, TString selfile);
  virtual void ConcatenateEVTAKE(TString year, TString partype, TString stepsize, TString selfile, TString start, TString end, TString timeperiod);
  virtual void ConcatenateEVMINI(TString year, TString partype, TString stepsize, TString selfile, TString start, TString end, TString timeperiod);
  virtual void ConcatenateMC(TString mcfile, TString timeperiod, TString selfile);
  virtual void ConcatenateMINI(TString runs, TString timeperiod, TString selfile);
  virtual void ConcatenateMINISplit(TString run, TString firstevent, TString lastevent, TString timeperiod, TString selfile);
  virtual void ConcatenateMC2(TString filespercard, TString mcfile, TString timeperiod, TString selfile);
  virtual void ConcatenateMCZES(TString mcfile, TString cutfile, TString timeperiod, TString selfile);
  virtual void ConcatenateMCZES2(TString filespercard, TString mcfile, TString cutfile, TString timeperiod, TString selfile);

  virtual void ConcatenateAnalysis(TString inputdir, TString templatefile, TString selfile);
  virtual void ConcatenateAnalumi(TString inputdir, TString templatefile, TString lumi, TString selfile);
  virtual void ConcatenateAnalumiMCRAP(TString inputdir, TString templatefile, TString lumi, TString runperiod, TString selfile);
  virtual void ConcatenateAnalumiMC(TString inputdir, TString templatefile, TString lumi, TString runperiod, TString selfile);
  virtual void ConcatenateAnalumiMCBBBARRAP(TString inputdir, TString templatefile, TString lumi, TString runperiod, TString selfile);
  virtual void ConcatenateAnalumiMCBBBAR(TString inputdir, TString templatefile, TString lumi, TString runperiod, TString selfile);
  virtual void ConcatenateAnalumiMCCCBARRAP(TString inputdir, TString templatefile, TString lumi, TString runperiod, TString selfile);
  virtual void ConcatenateAnalumiMCCCBARREWEIGHT(TString inputdir, TString templatefile, TString lumi, TString runperiod, TString selfile);
  virtual void ConcatenateAnalumiMCCCBAR(TString inputdir, TString templatefile, TString lumi, TString runperiod, TString selfile);
  virtual void ConcatenateAnalumiMCLFRAP(TString inputdir, TString templatefile, TString lumi, TString runperiod, TString selfile);
  virtual void ConcatenateAnalumiMCLF(TString inputdir, TString templatefile, TString lumi, TString runperiod, TString selfile);
  virtual void ConcatenateAnalumiMCLFREWEIGHT(TString inputdir, TString templatefile, TString lumi, TString runperiod, TString selfile);
  virtual void ConcatenateAnalumiMCJPSIHRWG(TString inputdir, TString templatefile, TString lumi, TString runperiod, TString selfile);
  virtual void ConcatenateAnalumiMCPSIPRIMEHRWG(TString inputdir, TString templatefile, TString lumi, TString runperiod, TString selfile);

  virtual void StreamStart(ofstream *output);
  virtual void StreamZESRun(ofstream *output, TString start, TString end);
  virtual void StreamZESSelect(ofstream *output, TString cutfile);
  virtual void StreamOrange(ofstream *output, TString timeperiod);
  virtual void StreamBremat(ofstream *output);
  virtual void StreamMINI(ofstream *output, TString runs, TString timeperiod);
  virtual void StreamMINISplit(ofstream *output, TString run, TString firstevent, TString lastevent, TString timeperiod);
  virtual void StreamMCStart(ofstream *output);
  virtual void StreamMCZESStart(ofstream *output);
  virtual void StreamMCSelect(ofstream *output, TString mcfile);
  virtual void StreamGutcard(ofstream *output, Bool_t mc = kFALSE);
  virtual void StreamGeneral(ofstream *output);
  virtual void StreamAnalysis(ofstream *output, TString templatefile, TString inputdir);
  virtual void StreamLumiAnalysis(ofstream *output, TString templatefile, TString lumi, TString inputdir);
  virtual void StreamLumiAnalysisMC(ofstream *output, TString templatefile, TString lumi, TString inputdir, TString runperiod);
  virtual void StreamLumiAnalysisMCRAP(ofstream *output, TString templatefile, TString lumi, TString inputdir, TString runperiod);
  virtual void StreamLumiAnalysisMCBBBARRAP(ofstream *output, TString templatefile, TString lumi, TString inputdir, TString runperiod);
  virtual void StreamLumiAnalysisMCBBBAR(ofstream *output, TString templatefile, TString lumi, TString inputdir, TString runperiod);
  virtual void StreamLumiAnalysisMCCCBARRAP(ofstream *output, TString templatefile, TString lumi, TString inputdir, TString runperiod);
  virtual void StreamLumiAnalysisMCCCBARREWEIGHT(ofstream *output, TString templatefile, TString lumi, TString inputdir, TString runperiod);
  virtual void StreamLumiAnalysisMCCCBAR(ofstream *output, TString templatefile, TString lumi, TString inputdir, TString runperiod);
  virtual void StreamLumiAnalysisMCLFRAP(ofstream *output, TString templatefile, TString lumi, TString inputdir, TString runperiod);
  virtual void StreamLumiAnalysisMCLF(ofstream *output, TString templatefile, TString lumi, TString inputdir, TString runperiod);
  virtual void StreamLumiAnalysisMCLFREWEIGHT(ofstream *output, TString templatefile, TString lumi, TString inputdir, TString runperiod);
  virtual void StreamLumiAnalysisMCJPSIHRWG(ofstream *output, TString templatefile, TString lumi, TString inputdir, TString runperiod);
  virtual void StreamLumiAnalysisMCPSIPRIMEHRWG(ofstream *output, TString templatefile, TString lumi, TString inputdir, TString runperiod);

  virtual void StreamMagField(ofstream *output);
  virtual void StreamGeant(ofstream *output);
  virtual void StreamMozart(ofstream *output);
  virtual void StreamHera(ofstream *output);
  virtual void StreamDetector(ofstream *output, TString timeperiod);
  virtual void StreamReco(ofstream *output);

  ClassDef(GCardManager,0) // concatenate template cards
};

#endif
