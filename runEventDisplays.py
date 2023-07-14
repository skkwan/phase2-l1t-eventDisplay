import os

def main():
    """
    Call a ROOT macro to make event displays from a ROOT file containing a TTree with the objects to
    display stored as vectors of TLorentzVectors.
    """

    inFile = "singleAnalyzer_10_events_noRawiso.root"

    for eventIndex in range(1):
        cmd = "root -l -b -q 'plotEventDisplayPhase2ECALCrystals.cpp(\"{}\", {})'".format(inFile, eventIndex)
        print(cmd)
        os.system(cmd)

if __name__ == "__main__":
    main()
    