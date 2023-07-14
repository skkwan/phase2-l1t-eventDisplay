
void runDisplay() {


  gROOT->ProcessLine(".L plotEventDisplayPhase2ECALCrystals.C++");


  gROOT->ProcessLine(".x plotEventDisplayPhase2ECALCrystals.C(\"singleAnalyzer-test.root\", 0)");


}

