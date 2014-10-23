//
// GAnalysisHeader.h
//
// $Author: kahle $
// $Date: 2008/06/10 08:46:47 $
// $Revision: 1.39 $
//

#ifndef GUT_GAnalysisHeader
#define GUT_GAnalysisHeader

#ifndef ROOT_TObject
#include <TObject.h>
#endif

#ifndef ROOT_TString
#include <TString.h>
#endif

class TDatime;
class GMuon;

class GAnalysisHeader : public TObject {

 private:

  Double_t fEventWeight;                 // event weight         

  Int_t    fSecondStart;                 // start second
  Int_t    fMinuteStart;                 // start minute
  Int_t    fHourStart;                   // start hour
  Int_t    fDayStart;                    // start day
  Int_t    fMonthStart;                  // start month
  Int_t    fYearStart;                   // start year

  Int_t    fSecondEnd;                   // end second
  Int_t    fMinuteEnd;                   // end minute
  Int_t    fHourEnd;                     // end hour
  Int_t    fDayEnd;                      // end day
  Int_t    fMonthEnd;                    // end month
  Int_t    fYearEnd;                     // end year

  Int_t    fSecondDiff;                  // diff second
  Int_t    fMinuteDiff;                  // diff minute
  Int_t    fHourDiff;                    // diff hour
  Int_t    fDayDiff;                     // diff day

  Int_t    fProcessedEvents;             // number of processed events

  Int_t    fPassedEvtakeCutsOnly;        // Only number of events passed evtake cuts
  Int_t    fPassedTriggerCutsOnly;       // Only number of events passed trigger cuts
  Int_t    fPassedVertexCutsOnly;        // Only number of events passed vertex cuts
  Int_t    fPassedSinistraCutsOnly;      // Only number of events passed sinistra cuts
  Int_t    fPassedCalCutsOnly;           // Only number of events passed cal cuts
  Int_t    fPassedBacCutsOnly;           // Only number of events passed bac cuts
  Int_t    fPassedZufoCutsOnly;          // Only number of events passed zufo cuts
  Int_t    fPassedJetCutsOnly;           // Only number of events passed jet cuts
  Int_t    fPassedTrackCutsOnly;         // Only number of events passed track cuts
  Int_t    fPassedMuonCutsOnly;          // Only number of events passed muon cuts
  Int_t    fPassedMJMatchCutsOnly;       // Only number of events passed muon-jet match
  Int_t    fPassedTJMatchCutsOnly;       // Only number of events passed track-jet match
  Int_t    fPassedMVDCutsOnly;           // Only number of events passed mvd vertexing
  Int_t    fPassedDIMuonCutsOnly;        // Only number of events passed dimuon
  Int_t    fPassedMCCutsOnly;            // Only number of events passed MC
  Int_t    fPassedMCSelectionCutsOnly;   // Only number of events passed MC selection
  Int_t    fPassedAllCutsOnly;           // Only number of events passed all cuts
  Int_t    fForwardMuonsOnly;            // Only number of forward muons
  Int_t    fBarrelMuonsOnly;             // Only number of barrel muons
  Int_t    fRearMuonsOnly;               // Only number of rear muons

  Int_t    fPassedEvtakeCutsCons;        // consecutive number of events passed evtake cuts
  Int_t    fPassedMCSelectionCutsCons;   // consecutive number of events passed MC selection cuts
  Int_t    fPassedTriggerCutsCons;       // consecutive number of events passed trigger cuts
  Int_t    fPassedVertexCutsCons;        // consecutive number of events passed vertex cuts
  Int_t    fPassedSinistraCutsCons;      // consecutive number of events passed sinistra cuts
  Int_t    fPassedCalCutsCons;           // consecutive number of events passed cal cuts
  Int_t    fPassedBacCutsCons;           // consecutive number of events passed bac cuts
  Int_t    fPassedZufoCutsCons;          // consecutive number of events passed zufo cuts
  Int_t    fPassedJetCutsCons;           // consecutive number of events passed jet cuts
  Int_t    fPassedTrackCutsCons;         // consecutive number of events passed track cuts
  Int_t    fPassedMuonCutsCons;          // consecutive number of events passed muon cuts
  Int_t    fPassedMJMatchCutsCons;       // consecutive number of events passed muon-jet match
  Int_t    fPassedTJMatchCutsCons;       // consecutive number of events passed track-jet match
  Int_t    fPassedMVDCutsCons;           // consecutive number of events passed mvd vertexing
  Int_t    fPassedDIMuonCutsCons;        // consecutive number of events passed dimuon
  Int_t    fPassedMCCutsCons;            // consecutive number of events passed mc
  Int_t    fPassedAllCutsCons;           // consecutive number of events passed all cuts
  Int_t    fForwardMuonsCons;            // consecutive number of forward muons
  Int_t    fBarrelMuonsCons;             // consecutive number of barrel muons
  Int_t    fRearMuonsCons;               // consecutive number of rear muons

  Int_t    fPassedTriggerCutsExcl;       // exclusive number of events passed trigger cuts
  Int_t    fPassedMCSelectionCutsExcl;   // exclusive number of events passed selection cuts
  Int_t    fPassedEvtakeCutsExcl;        // exclusive number of events passed evtake cuts
  Int_t    fPassedVertexCutsExcl;        // exclusive number of events passed vertex cuts
  Int_t    fPassedSinistraCutsExcl;      // exclusive number of events passed sinistra cuts
  Int_t    fPassedCalCutsExcl;           // exclusive number of events passed cal cuts
  Int_t    fPassedBacCutsExcl;           // exclusive number of events passed bac cuts
  Int_t    fPassedZufoCutsExcl;          // exclusive number of events passed zufo cuts
  Int_t    fPassedJetCutsExcl;           // exclusive number of events passed jet cuts
  Int_t    fPassedTrackCutsExcl;         // exclusive number of events passed track cuts
  Int_t    fPassedMuonCutsExcl;          // exclusive number of events passed muon cuts
  Int_t    fPassedMJMatchCutsExcl;       // exclusive number of events passed muon-jet match
  Int_t    fPassedTJMatchCutsExcl;       // exclusive number of events passed track-jet match
  Int_t    fPassedMVDCutsExcl;           // exclusive number of events passed mvd vertexing
  Int_t    fPassedDIMuonCutsExcl;        // exclusive number of events passed dimuon
  Int_t    fPassedMCCutsExcl;            // exclusive number of events passed MC
  Int_t    fPassedAllCutsExcl;           // exclusive number of events passed all cuts
  Int_t    fForwardMuonsExcl;            // exclusive number of forward muons
  Int_t    fBarrelMuonsExcl;             // exclusive number of barrel muons
  Int_t    fRearMuonsExcl;               // exclusive number of rear muons

  TString  fDirectory;                   // define subdirectory of data sample header is belonging to

  Double_t fLuminosity;                  // luminosity corresponding to data sample
  Double_t fLumiWeight;                  // Lumi reweighting factor for MC

  Int_t    fChosenMuons;                 // number of chosen muons
  Int_t    fEfficiencyResetMuons;        // chosen muons where efficiency had to be set to 1 because MC efficiencies for that type of event have been zero

 public:
  GAnalysisHeader();
  virtual ~GAnalysisHeader();

  inline virtual Int_t GetStartDate()    { return fYearStart * 10000 + fMonthStart * 100 + fDayStart;   }
  inline virtual Int_t GetStartTime()    { return fHourStart*10000 + fMinuteStart*100 + fSecondStart;   }
  inline virtual Int_t GetStartYear()    { return fYearStart;                                           }
  inline virtual Int_t GetStartMonth()   { return fMonthStart;                                          }
  inline virtual Int_t GetStartDay()     { return fDayStart;                                            }
  inline virtual Int_t GetStartHour()    { return fHourStart;                                           }
  inline virtual Int_t GetStartMinute()  { return fMinuteStart;                                         }
  inline virtual Int_t GetStartSecond()  { return fSecondStart;                                         }

  inline virtual Int_t GetEndDate()    { return fYearEnd * 10000 + fMonthEnd * 100 + fDayEnd;       }
  inline virtual Int_t GetEndTime()    { return fHourEnd*10000 + fMinuteEnd*100 + fSecondEnd;       }
  inline virtual Int_t GetEndYear()    { return fYearEnd;                                           }
  inline virtual Int_t GetEndMonth()   { return fMonthEnd;                                          }
  inline virtual Int_t GetEndDay()     { return fDayEnd;                                            }
  inline virtual Int_t GetEndHour()    { return fHourEnd;                                           }
  inline virtual Int_t GetEndMinute()  { return fMinuteEnd;                                         }
  inline virtual Int_t GetEndSecond()  { return fSecondEnd;                                         }

  inline virtual Int_t GetDiffDay()     { return fDayDiff;                                            }
  inline virtual Int_t GetDiffHour()    { return fHourDiff;                                           }
  inline virtual Int_t GetDiffMinute()  { return fMinuteDiff;                                         }
  inline virtual Int_t GetDiffSecond()  { return fSecondDiff;                                         }

  inline virtual Int_t GetProcessedEvents()     { return fProcessedEvents;     }

  inline virtual Int_t GetPassedEvtakeCutsOnly()    { return fPassedEvtakeCutsOnly;    }
  inline virtual Int_t GetPassedMCSelectionCutsOnly(){ return fPassedMCSelectionCutsOnly;}
  inline virtual Int_t GetPassedTriggerCutsOnly()   { return fPassedTriggerCutsOnly;   }
  inline virtual Int_t GetPassedVertexCutsOnly()    { return fPassedVertexCutsOnly;    }
  inline virtual Int_t GetPassedSinistraCutsOnly()  { return fPassedSinistraCutsOnly;  }
  inline virtual Int_t GetPassedCalCutsOnly()       { return fPassedCalCutsOnly;       }
  inline virtual Int_t GetPassedBacCutsOnly()       { return fPassedBacCutsOnly;       }
  inline virtual Int_t GetPassedZufoCutsOnly()      { return fPassedZufoCutsOnly;      }
  inline virtual Int_t GetPassedJetCutsOnly()       { return fPassedJetCutsOnly;       }
  inline virtual Int_t GetPassedTrackCutsOnly()     { return fPassedTrackCutsOnly;     }
  inline virtual Int_t GetPassedMuonCutsOnly()      { return fPassedMuonCutsOnly;      }
  inline virtual Int_t GetPassedMJMatchCutsOnly()   { return fPassedMJMatchCutsOnly;   }
  inline virtual Int_t GetPassedTJMatchCutsOnly()   { return fPassedTJMatchCutsOnly;   }
  inline virtual Int_t GetPassedMVDCutsOnly()       { return fPassedMVDCutsOnly;       }
  inline virtual Int_t GetPassedDIMuonCutsOnly()    { return fPassedDIMuonCutsOnly;    }
  inline virtual Int_t GetPassedMCCutsOnly()        { return fPassedMCCutsOnly;        }
  inline virtual Int_t GetPassedAllCutsOnly()       { return fPassedAllCutsOnly;       }
  inline virtual Int_t GetForwardMuonsOnly()        { return fForwardMuonsOnly;        }
  inline virtual Int_t GetBarrelMuonsOnly()         { return fBarrelMuonsOnly;         }
  inline virtual Int_t GetRearMuonsOnly()           { return fRearMuonsOnly;           }

  inline virtual Int_t GetPassedEvtakeCutsCons()    { return fPassedEvtakeCutsCons;    }
  inline virtual Int_t GetPassedMCSelectionCutsCons(){ return fPassedMCSelectionCutsCons;}
  inline virtual Int_t GetPassedTriggerCutsCons()   { return fPassedTriggerCutsCons;   }
  inline virtual Int_t GetPassedVertexCutsCons()    { return fPassedVertexCutsCons;    }
  inline virtual Int_t GetPassedSinistraCutsCons()  { return fPassedSinistraCutsCons;  }
  inline virtual Int_t GetPassedCalCutsCons()       { return fPassedCalCutsCons;       }
  inline virtual Int_t GetPassedBacCutsCons()       { return fPassedBacCutsCons;       }
  inline virtual Int_t GetPassedZufoCutsCons()      { return fPassedZufoCutsCons;      }
  inline virtual Int_t GetPassedJetCutsCons()       { return fPassedJetCutsCons;       }
  inline virtual Int_t GetPassedTrackCutsCons()     { return fPassedTrackCutsCons;     }
  inline virtual Int_t GetPassedMuonCutsCons()      { return fPassedMuonCutsCons;      }
  inline virtual Int_t GetPassedMJMatchCutsCons()   { return fPassedMJMatchCutsCons;   }
  inline virtual Int_t GetPassedTJMatchCutsCons()   { return fPassedTJMatchCutsCons;   }
  inline virtual Int_t GetPassedMVDCutsCons()       { return fPassedMVDCutsCons;       }
  inline virtual Int_t GetPassedDIMuonCutsCons()    { return fPassedDIMuonCutsCons;    }
  inline virtual Int_t GetPassedMCCutsCons()        { return fPassedMCCutsCons;        }
  inline virtual Int_t GetPassedAllCutsCons()       { return fPassedAllCutsCons;       }
  inline virtual Int_t GetForwardMuonsCons()        { return fForwardMuonsCons;        }
  inline virtual Int_t GetBarrelMuonsCons()         { return fBarrelMuonsCons;         }
  inline virtual Int_t GetRearMuonsCons()           { return fRearMuonsCons;           }

  inline virtual Int_t GetPassedEvtakeCutsExcl()    { return fPassedEvtakeCutsExcl;    }
  inline virtual Int_t GetPassedMCSelectionCutsExcl(){ return fPassedMCSelectionCutsExcl;}
  inline virtual Int_t GetPassedTriggerCutsExcl()   { return fPassedTriggerCutsExcl;   }
  inline virtual Int_t GetPassedVertexCutsExcl()    { return fPassedVertexCutsExcl;    }
  inline virtual Int_t GetPassedSinistraCutsExcl()  { return fPassedSinistraCutsExcl;  }
  inline virtual Int_t GetPassedCalCutsExcl()       { return fPassedCalCutsExcl;       }
  inline virtual Int_t GetPassedBacCutsExcl()       { return fPassedBacCutsExcl;       }
  inline virtual Int_t GetPassedZufoCutsExcl()      { return fPassedZufoCutsExcl;      }
  inline virtual Int_t GetPassedJetCutsExcl()       { return fPassedJetCutsExcl;       }
  inline virtual Int_t GetPassedTrackCutsExcl()     { return fPassedTrackCutsExcl;     }
  inline virtual Int_t GetPassedMuonCutsExcl()      { return fPassedMuonCutsExcl;      }
  inline virtual Int_t GetPassedMJMatchCutsExcl()   { return fPassedMJMatchCutsExcl;   }
  inline virtual Int_t GetPassedTJMatchCutsExcl()   { return fPassedTJMatchCutsExcl;   }
  inline virtual Int_t GetPassedMVDCutsExcl()       { return fPassedMVDCutsExcl;       }
  inline virtual Int_t GetPassedDIMuonCutsExcl()    { return fPassedDIMuonCutsExcl;    }
  inline virtual Int_t GetPassedMCCutsExcl()        { return fPassedMCCutsExcl;        }
  inline virtual Int_t GetPassedAllCutsExcl()       { return fPassedAllCutsExcl;       }
  inline virtual Int_t GetForwardMuonsExcl()        { return fForwardMuonsExcl;        }
  inline virtual Int_t GetBarrelMuonsExcl()         { return fBarrelMuonsExcl;         }
  inline virtual Int_t GetRearMuonsExcl()           { return fRearMuonsExcl;           }

  virtual Bool_t GetAllCuts();
  virtual TString PrintAllCuts(Bool_t formated = kTRUE);

  virtual void Increase();

  virtual void SetStart();
  virtual void SetEnd();

  virtual TString ReturnHeader(TString title);
  virtual TString ReturnFooter(TString title);

  virtual TString ReturnSevenDigits(Int_t counter);
  virtual TString ReturnTitle(TString title);
  virtual TString ReturnLine(TString category, Int_t only, Int_t consecutive, Int_t exclusive);
  
  virtual void Header(TString title);
  virtual void Header(ofstream *stream, TString title);
  virtual void Footer(TString title);
  virtual void Footer(ofstream *stream, TString title);

  virtual Bool_t CheckWeight();

  inline virtual Double_t GetWeight() { return fEventWeight; }
  virtual Double_t GetWeight(GMuon* muon);

  inline virtual void SetDirectory(TString input) { fDirectory = input;       }
  inline virtual TString GetDirectory()           { return fDirectory;        }

  inline virtual void SetLuminosity(Double_t input)      { fLuminosity = input;  }  
  inline virtual void SetLumiWeight(Double_t input)      { fLumiWeight = input;  }
  inline virtual void IncreaseLuminosity(Double_t input) { fLuminosity += input; }
  inline virtual void DecreaseLuminosity(Double_t input) { fLuminosity -= input; }
  inline virtual Double_t GetLuminosity()                { return fLuminosity*fLumiWeight;   }
  inline virtual Double_t GetLumiWeight()                { return fLumiWeight;   }

  inline virtual void IncreaseChosenMuons()          { fChosenMuons += 1;          }
  inline virtual void IncreaseEfficiencyResetMuons() { fEfficiencyResetMuons += 1; }

  ClassDef(GAnalysisHeader,12) // Analysis Header
};

R__EXTERN GAnalysisHeader *gHeader;

#endif
