// runEventDisplay.C

// Before running:
// Make sure to do setup.sh AND change the input ROOT and output .png/pdf which are
// hard-coded in the macro, AND change the eta/phi plot range.

#include "TROOT.h"

void runEventDisplay() {
  
  gROOT->ProcessLine(".L plotEventDisplayPhaseIIecalCrystals.C++");
  
  gROOT->ProcessLine(".x plotEventDisplayPhaseIIecalCrystals.C(0)");


}
