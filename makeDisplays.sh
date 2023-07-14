# setup.sh: get ROOT 5.34/24 (needs ROOT 5)

source /cvmfs/sft.cern.ch/lcg/views/LCG_71/x86_64-slc6-gcc48-opt/setup.sh 

cat > runDisplay.cpp << EOF
#include "TROOT.h"

void runDisplay() {

  gROOT->ProcessLine(".L plotEventDisplayPhase2ECALCrystals.cpp");

  gROOT->ProcessLine(".x plotEventDisplayPhase2ECALCrystals.cpp("singleAnalyzer_10_events_noRawiso.root", 0)");


}

EOF

root -l -b -q runDisplay.cpp