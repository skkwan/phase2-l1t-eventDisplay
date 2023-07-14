#include "TROOT.h"

void runDisplay() {


  gROOT->ProcessLine(".L plotEventDisplayPhase2ECALCrystals.C++");


  gROOT->ProcessLine(".x plotEventDisplayPhase2ECALCrystals.C(\"singleAnalyzer_10_events_noRawiso.root\", 0)");


}

