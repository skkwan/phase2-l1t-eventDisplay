#include "TROOT.h"

void runEventDisplay() {
									
  gROOT->ProcessLine(".L plotEventDisplayPhaseIIecalCrystals.C++");
  gROOT->ProcessLine(".x plotEventDisplayPhaseIIecalCrystals.C(0)");


}
