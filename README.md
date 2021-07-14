# phase2-l1t-eventDisplay

## Setup
This repo runs independently of CMSSW; it only requires a ROOT v5 (see below on how to set that up on lxplus).

## Each time you change the input n-tuple
1. Refer to instructions in https://github.com/skkwan/phase2-l1Calo-analyzer on making the input n-tuples.
2. Copy the input n-tuples to this working area.


## Each time you run
1. Edit `plotEventDisplayPhaseIIecalCrystals.C` to point to the correct input `.root` n-tuple.

2. Source a cvmfs environment that has ROOT v5:
   ```
   source setup.sh   
   ```

3. Then call the wrapper which calls the main plotting script:
   ```
   root -l -b -q runEventDisplay.C
   ```

4. Output `.png` and `.pdf` event displays are written automatically to my EOS directory. Rename the outputs to avoid writing over them.
