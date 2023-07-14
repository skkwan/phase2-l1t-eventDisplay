# phase2-l1t-eventDisplay

## Setup and usage
This repo runs independently of CMSSW. This can be cloned outside of the CMSSW area where we are running the emulator and analyzers.

To generate the file to display, first we need to run the `L1CaloEGammaSingleAnalyzer.cc` in the `L1CaloPhase2Analyzer` repository, and copy the resulting `.root` file which has a folder `l1NtupleSingleProducer` with a TTree `dispTree` in it. The `dispTree` tree has a `std::vector<TLorentzVector>` of the objects (clusters, towers) that we want to visualize. Copy this file into the event display repository or somewhere else and run:

```
git clone git@github.com:skkwan/phase2-l1t-eventDisplay.git
# Assuming that the file is at singleAnalyzer-test.root in the same directory:
bash makeDisplays.sh
```
And this should make a `.pdf`.

