# phase2-l1t-eventDisplay

## Setup
This repo runs independently of CMSSW; it only requires ROOT (works for ROOT 6.24/08 at least).

```
git clone git@github.com:skkwan/phase2-l1t-eventDisplay.git
root -l -b -q runDisplay.C
```

## Usage
1. First make a ROOT file where for each event, there are branches containing vectors of TLorentzVectors representing the objects you want to plot (e.g. ECAL TPGs, HCAL TPGs, clusters).
   * Now we can produce such an n-tuple with both old/new emulator clusters using `L1CaloEGammaSingleAnalyzer.cc` in the `L1CaloPhase2Analyzer` repository (for me: `/afs/cern.ch/work/s/skkwan/private/phase2RCTDev/CMSSW_11_1_7/src/L1Trigger/L1CaloPhase2Analyzer/plugins`).
   * Also change the output path if necessary.
2. In `runEventDisplays.py`, point to that input ROOT file, and specify what events to run (e.g. to process the first 3 events in a ROOT file with 10 events, loop over i = 0, 1, 2). 
3. Run:
   ```
   python runEventDisplays.py
   ```
