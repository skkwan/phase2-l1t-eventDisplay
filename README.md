# phase2-l1t-eventDisplay

## Setup
This repo runs independently of CMSSW; it only requires a ROOT v5 (see below on how to set that up on lxplus).

## Each time you change the input ROOT file
1. Currently this event display only works for ROOT files that contain exactly one event. To select one GEN-SIM-RAW-DIGI event (with a specific
   run/lumi/event), use the code in `pickEvent/` in the https://github.com/skkwan/phase2-l1Calo-analyzer repository.
2. Refer to instructions in https://github.com/skkwan/phase2-l1Calo-analyzer on running the emulator on the GEN-SIM-RAW-DIGI event:
   Specifically, you want `test-l1tEventDisplayGenerator.py` or `test-l1t-cmssw-EventDisplayGenerator.py` because
   you want the output file to have the collections (not just the efficiencyTree n-tuple).
3. This should produce a file called `L1EventDisplay.root` (or something similar). Copy that to this `eventDisplay` repository so we don't
   accidentally overwrite it.

## Each time you run
1. Edit `plotEventDisplayPhaseIIecalCrystals.C` to point to the correct input `.root`, and edit `eta2` and `phi2` to 
   center the output plot on the cluster that we want to look at.

2. On `lxplus` (if we are writing the output figures to `/eos/` we need to be on lxplus not uwlogin.cern.ch),
   source a cvmfs environment that has ROOT v5:
   ```
   source setup.sh   
   ```

3. Then run this (`runEventDisplay.C` calls the main plotting script):
   ```
   root -l -b -q runEventDisplay.C
   ```

4. Output `.png` and `.pdf` event displays are written automatically to my EOS directory. Rename the outputs to avoid writing over them.


## Common errors

* `././plotEventDisplayPhaseIIecalCrystals.C:23:10: fatal error: 'Math/VectorUtil_Cint.h' file not found`
   Solution: Make sure you do `source setup.sh`.

* `cannot open image file "/eos/user/...`
   Solution: This needs to run on lxplus not uwlogin.cern.ch.