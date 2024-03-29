// authors: S. Kwan, P. Das, I. Ojalvo


#include <vector>
#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TFrame.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH2.h"
#include "TGraph2D.h"
#include "TGraph.h"
#include "TSystem.h"
#include <TLorentzVector.h>
#include <TStyle.h>
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TEllipse.h"
#include "TPaveText.h"
#include "TLine.h"
#include "TInterpreter.h"


#ifdef __MAKECINT__
#pragma link C++ class std::vector<float>+;
#pragma link C++ class std::vector<TLorentzVector>+;
#pragma link C++ class std::vector<bool>+;
#endif

static bool comparePt(const TLorentzVector& lhs, const TLorentzVector& rhs) {
    return ( lhs.Pt() > rhs.Pt() );
}

template <typename T> 
float deltaPhi(T v1, T v2, const T c = 3.142) {
    auto r = std::fmod(v2 - v1, 2.0 * c);
    if (r < -c) {
        r += 2.0 * c;
    }
    else if (r > c) {
        r -= 2.0 * c;
    }
    return r;
}


float deltaR(float eta1, float eta2, float phi1, float phi2) {
    return sqrt(pow(eta1 - eta2, 2) + pow(deltaPhi(phi1, phi2), 2));

}

bool isLeadingDeltaRLarge(const std::vector<TLorentzVector> *v1, const std::vector<TLorentzVector> *v2, float thresholdDeltaR) {

    if ((v1->size() > 0) && (v2->size() > 0)) {

        float eta1 = v1->at(0).Eta();
        float phi1 = v1->at(0).Phi();

        float eta2 = v2->at(0).Eta();
        float phi2 = v2->at(0).Phi();

        float deltaR = sqrt(pow(eta1 - eta2, 2) + pow(deltaPhi(phi1, phi2), 2));

        printf("for eta/phi pairs %f %f and %f %f, deltaR: %f", eta1, phi1, eta2, phi2, deltaR);

        return (deltaR > thresholdDeltaR);
    }
    else {
        printf("[WARNING:] checkLeadingDeltaR: one or both of the vectors has length zero, cannot compare elements\n");
        return false;
    }



}

void DrawCardLines(){
    std::vector<TLine*> cardLines;
    float etaValues[3] = { -1.479, 0, 1.479 };

    float phiValues[19] =
        { -3.142, -2.793, -2.443, -2.094, -1.745, -1.396, -1.047, -0.698, -0.349, 0.000, 
        0.349, 0.698, 1.047, 1.396, 1.745, 2.094, 2.443, 2.793, 3.142};
    
    //eta lines
    for(int i = 0; i < 3; i++){
        TLine * line = new TLine(etaValues[i], -3.2, etaValues[i], 3.2); 
        line->SetLineColor(kRed);
        line->SetLineStyle(1);
        line->SetLineWidth(2);
        cardLines.push_back(line);
    }

    //phi lines
    for(int i = 0; i < 19; i++){
        TLine * line = new TLine(-3, phiValues[i], 3, phiValues[i]); 
        line->SetLineColor(kRed);
        line->SetLineStyle(1);
        line->SetLineWidth(2);
        cardLines.push_back(line);
    }

    for(size_t j = 0; j < cardLines.size(); j++) {
        cardLines.at(j)->Draw();
    }
}

// ECAL region lines
void DrawRegionLines(){

    std::vector<TLine*> RegionLines;
    float etaValues[13] = { -1.479, // -1.392,
                            -1.305, // -1.218, -1.131,
                            -1.044, // -0.957, -0.87,
                            -0.783, // -0.696, -0.609, 
                            -0.522, // -0.435, -0.348,
                            -0.261, // -0.174, -0.087, 
                            0,      // 0.087, 0.174,
                            0.261,  // 0.348, 0.435,
                            0.522,  // 0.609, 0.696,
                            0.783,  // 0.87, 0.957,
                            1.044,  // 1.131, 1.218,
                            1.305,  // 1.392, 
                            1.479
    };

    float phiValues[19] =
        { -3.142, -2.793, -2.443, -2.094, -1.745, -1.396, -1.047, -0.698, -0.349, 0.000,
        0.349, 0.698, 1.047, 1.396, 1.745, 2.094, 2.443, 2.793, 3.142};

    //eta lines
    for(int i = 0; i < 13; i++){
        TLine * line = new TLine(etaValues[i], -3.2, etaValues[i], 3.2); 
        line->SetLineColor(kBlue);
        line->SetLineStyle(1);
        RegionLines.push_back(line);
    }

    //phi lines
    for(int i = 0; i < 19; i++){
        TLine * line = new TLine(-3, phiValues[i], 3, phiValues[i]); 
        line->SetLineColor(kBlue);
        line->SetLineStyle(1);
        RegionLines.push_back(line);
    }

    for(size_t j = 0; j < RegionLines.size(); j++){
        RegionLines.at(j)->Draw();
    }

}


void DrawTowerLines(){

    std::vector<TLine*> TowerLines;
    float etaValues[59] = { -3, -2.826, -2.652, -2.478, -2.304, -2.107, -2.0207, -1.93, -1.83, -1.74, -1.653, -1.566, -1.479, -1.392, -1.305, -1.218, -1.131, -1.044, -0.957, -0.87, -0.783, -0.696, -0.609, -0.522, -0.435, -0.348, -0.261, -0.174, -0.087, 0, 0.087, 0.174, 0.261, 0.348, 0.435, 0.522, 0.609, 0.696, 0.783, 0.87, 0.957, 1.044, 1.131, 1.218, 1.305, 1.392, 1.479, 1.566, 1.653, 1.74, 1.83, 1.93, 2.0207, 2.107, 2.304, 2.478, 2.652, 2.826, 3};

    float phiValues[73] =
        {-3.142, -3.054, -2.967, -2.880, -2.793, -2.705, -2.618, -2.531, -2.443, -2.356, -2.269, -2.182, -2.094, -2.007, -1.920, -1.833, -1.745, -1.658, -1.571, -1.484, -1.396, -1.309, -1.222, -1.134, -1.047, -0.960, -0.873, -0.785, -0.698, -0.611, -0.524, -0.436, -0.349, -0.262, -0.175, -0.087,
        0.000, 0.087, 0.175, 0.262, 0.349, 0.436, 0.524, 0.611, 0.698, 0.785, 0.873, 0.960, 1.047, 1.134, 1.222, 1.309, 1.396, 1.484, 1.571, 1.658, 1.745, 1.833, 1.920, 2.007, 2.094, 2.182, 2.269, 2.356, 2.443, 2.531, 2.618, 2.705, 2.793, 2.880, 2.967, 3.054, 3.142};
    
    //eta lines
    for(int i = 0; i < 59; i++){
        TLine * line = new TLine(etaValues[i], -3.2, etaValues[i], 3.2); 
        line->SetLineColor(kGray);
        line->SetLineStyle(3);
        TowerLines.push_back(line);
    }

    //phi lines
    for(int i = 0; i < 73; i++){
        TLine * line = new TLine(-3, phiValues[i], 3, phiValues[i]); 
        line->SetLineColor(kGray);
        line->SetLineStyle(3);
        TowerLines.push_back(line);
    }

    for(size_t j = 0; j < TowerLines.size(); j++){
        TowerLines.at(j)->Draw();
    }
}

/*
 * 
 */
int makeSmallerPlotInPad(float etaMin, float etaMax, float phiMin, float phiMax,
                        TH2F* h2HcalTpgs_original, TH2F* h2EcalTpgs_original, TH2F* h2OldClusters_original, TH2F* h2NewClusters_original,
                        TH2F* h2LeadingOld_original, TH2F* h2LeadingNew_original,
                        float barOffset, float textSize) {
    gStyle->SetTextFont(42);

    TH2F* h2HcalTpgs = (TH2F*) h2HcalTpgs_original->Clone();
    TH2F* h2HcalTpgs2 = (TH2F*) h2HcalTpgs_original->Clone();
    h2HcalTpgs->GetXaxis()->SetRangeUser(etaMin, etaMax);
    h2HcalTpgs->GetYaxis()->SetRangeUser(phiMin, phiMax);

    h2HcalTpgs->Draw("BOX");
    h2HcalTpgs->Draw("SAME BOX");

    h2HcalTpgs2->SetLineColor(kSpring+10);
    h2HcalTpgs2->SetLineWidth(1);
    h2HcalTpgs2->Draw("SAME BOXL");

    DrawCardLines();
    DrawRegionLines();
    DrawTowerLines();

    // Plot the ECAL crystals (TPGs)
    TH2F* h2EcalTpgs = (TH2F*)h2EcalTpgs_original->Clone();
    TH2F* h2EcalTpgs2 = (TH2F*)h2EcalTpgs_original->Clone();
    h2EcalTpgs->Draw("SAME BOX");
    h2EcalTpgs2->SetLineColor(kPink+1);
    h2EcalTpgs2->SetLineWidth(1);
    h2EcalTpgs2->SetMarkerColor(kBlack);
    h2EcalTpgs2->SetMarkerSize(textSize * 0.5);
    h2EcalTpgs2->Draw("SAME BOXL");

    // // Plot the new clusters: filled-in only no outlines
    // TH2F* h2NewClusters = (TH2F*) h2NewClusters_original->Clone();
    // h2NewClusters->Draw("SAME BOX");
    // h2NewClusters->SetMarkerColor(kRed-5);
    // h2NewClusters->SetMarkerSize(textSize * 0.7);
    // h2NewClusters->SetBarOffset(barOffset);
    // h2NewClusters->Draw("SAME TEXT");
 
    // // Plot the old clusters
    // TH2F* h2OldClusters = (TH2F*) h2OldClusters_original->Clone();
    // h2OldClusters->Draw("SAME BOXL");
    // h2OldClusters->SetMarkerColor(kBlue-6);
    // h2OldClusters->SetMarkerSize(textSize);
    // h2OldClusters->SetBarOffset(-1 * barOffset);
    // h2OldClusters->Draw("SAME TEXT");

    // leading new cluster
    TH2F* h2LeadingNew = (TH2F*) h2LeadingNew_original->Clone();
    h2LeadingNew->Draw("SAME BOX");
    h2LeadingNew->SetMarkerColor(kRed);
    h2LeadingNew->SetMarkerSize(textSize);
    h2LeadingNew->SetBarOffset(2 * barOffset);
    h2LeadingNew->Draw("SAME TEXT");

    // leading old cluster
    TH2F* h2LeadingOld = (TH2F*) h2LeadingOld_original->Clone();
    h2LeadingOld->Draw("SAME BOX");
    h2LeadingOld->SetMarkerColor(kBlue);
    h2LeadingOld->SetMarkerSize(textSize);
    h2LeadingOld->SetBarOffset(-2 * barOffset);
    h2LeadingOld->Draw("SAME TEXT");


    return 1;
}

/*
 * Creates plots of the provided TH2Fs.
 */
int makePlots(float etaMin, float etaMax, float phiMin, float phiMax,
              float oldEtaCenter, float oldPhiCenter,
              float newEtaCenter, float newPhiCenter,
              TH2F* h2HcalTpgs, TH2F* h2EcalTpgs, TH2F* h2OldClusters, TH2F* h2NewClusters,
              TH2F* h2LeadingOld, TH2F* h2LeadingNew,
              int event, const char* saveFile) {
    // Create a new canvas.
    TCanvas *c1 = new TCanvas("c1","eta vs phi",4000,5000);
    
    c1->SetFillColor(0);
    c1->GetFrame()->SetFillColor(0);
    c1->GetFrame()->SetBorderSize(6);
    c1->GetFrame()->SetBorderMode(-1);

    char name[100];


    TPad *pad1 = new TPad("pad1","This is pad1",0.05,0.8,1,1);
    TPad *pad2 = new TPad("pad2","This is pad2",0.05,0,1,0.8);
    // TPad *pad3 = new TPad("pad2","This is pad2",0.05,0.02,0.95,0.33);


    pad1->Draw();
    pad2->Draw();
    // pad3->Draw();

    pad1->cd();

    float xR = 0;
    TLegend *l = new TLegend(0.00, 0.1, 0.95, 0.9);
    l->SetTextSize(0.12);

    l->AddEntry(h2EcalTpgs,   "ECAL crystal hits (inputs to clustering)",   "F");
    l->AddEntry(h2HcalTpgs,   "HCAL tower hits",     "F");
    TLegendEntry *ent1 = l->AddEntry(h2LeadingNew, "Leading cluster and pT (GeV) of new FW-based emulator", "F"); 
    ent1->SetTextColor(kRed);
    // TLegendEntry *ent2 = l->AddEntry(h2NewClusters, "Sub-leading clusters in new emulator, pT (GeV)", "F");
    // ent2->SetTextColor(kRed-3);
    // l->AddEntry(h2L1Towers,   "New Towers",   "F");
    TLegendEntry *ent3 = l->AddEntry(h2LeadingOld, "Leading cluster and pT (GeV) of previous emulator", "F");
    ent3->SetTextColor(kBlue);
    l->Draw();
    c1->Update();

    pad2->cd();

    float barOffset = 2.5;
    sprintf(name, "Event %u", event);
    h2HcalTpgs->SetTitle(name);
    float quadrantSize = 0.4;
    makeSmallerPlotInPad(oldEtaCenter-quadrantSize, oldEtaCenter+quadrantSize, oldPhiCenter-quadrantSize, oldPhiCenter+quadrantSize,
                        h2HcalTpgs, h2EcalTpgs, h2OldClusters, h2NewClusters,
                        h2LeadingOld, h2LeadingNew, barOffset, 2.4);
    c1->Update();



   

    // c1->Update();
    c1->SaveAs(saveFile);    
    delete c1;

    return 1;
}


void plotEventDisplayPhase2ECALCrystals(const char* inFile, int iEvent){

    // Necessary to declare dictionary, else ROOT complains about reading a custom class
    //gInterpreter->GenerateDictionary("std::vector<TLorentzVector>", "vector");
    //gInterpreter->GenerateDictionary("std::vector<float>", "vector");
    //gInterpreter->GenerateDictionary("std::vector<bool>", "vector");

  
    gStyle->SetOptStat(0);
  
    // float half_tower_offset = 0.04365;
    float half_tower_offset = 0.0;

    TFile *f = TFile::Open(inFile, "READ");

    if (!f) { return; }

    TTree *t = (TTree*) f->Get("l1NtupleSingleProducer/dispTree");

    std::vector<TLorentzVector> *vEcalTpgs       = 0;
    std::vector<TLorentzVector> *vHcalTpgs       = 0;

    std::vector<TLorentzVector> *vOldClusters     = 0;
    std::vector<TLorentzVector> *vOldTowers       = 0;


    std::vector<TLorentzVector> *vNewClusters       = 0;
    std::vector<TLorentzVector> *vNewTowers         = 0;


    int event = 0;

    const Int_t kUPDATE = 1000;

    t->SetBranchAddress("event",&event);
    t->SetBranchAddress("ecalTPGs",&vEcalTpgs);
    t->SetBranchAddress("hcalTPGs",&vHcalTpgs);
    t->SetBranchAddress("oldClusters",&vOldClusters);


    t->SetBranchAddress("oldTowers",&vOldTowers);
    t->SetBranchAddress("newClusters",&vNewClusters);
    t->SetBranchAddress("newTowers",&vNewTowers);


    TH2F *h2EcalTpgs = new TH2F("h2EcalTpgs","Event Display",(34*5), //(90*2), //64*2
                                -1.4841, 1.4841,
                                (72*5), // (144*2),
                                -3.142,3.142);
    TH2F *h2HcalTpgs = new TH2F("h2HcalTpgs","Event Display",34,
                                -1.4841, 1.4841,
                                72,
                                -3.142,3.142);
    TH2F *h2OldClusters = new TH2F("h2OldClusters","Event Display", (34*5), //(90*2),
                                    -1.4841, 1.4841,
                                    (72*5),//(144*2),
                                    -3.142,3.142); 
    TH2F *h2LeadingOld = new TH2F("h2LeadingOld","Event Display", (34*5), //(90*2),
                                    -1.4841, 1.4841,
                                    (72*5),//(144*2),
                                    -3.142,3.142);   

    TH2F *h2NewClusters = new TH2F("h2NewClusters","Event Display", (34*5), //(90*2),
                                    -1.4841, 1.4841,
                                    (72*5),//(144*2),
                                    -3.142,3.142);                             


    TH2F *h2LeadingNew =  new TH2F("h2LeadingNew","Event Display", (34*5), //(90*2),
                                    -1.4841, 1.4841,
                                    (72*5),//(144*2),
                                    -3.142,3.142);                     
    // TH2F   *h2L1Towers    = new TH2F("h2L1Towers", "Event Display", 34,
        // 			   -1.4841, 1.4841,
        // 			   72,
        // 			   -3.142,3.142);

    // Set style
    h2HcalTpgs->SetFillStyle(1001);
    h2HcalTpgs->SetFillColorAlpha(kSpring+10, 0.8);
    h2HcalTpgs->SetLineColorAlpha(kSpring+10, 0.8);
    h2HcalTpgs->GetXaxis()->SetTitle("#eta");
    h2HcalTpgs->GetYaxis()->SetTitle("#phi");

    h2EcalTpgs->SetFillStyle(1001);
    h2EcalTpgs->SetFillColorAlpha(kPink+1, 0.8);
    h2EcalTpgs->SetLineColorAlpha(kBlack, 0.8);

    h2NewClusters->SetFillStyle(1001);
    h2NewClusters->SetFillColorAlpha(kRed-3, 0.6);
    h2NewClusters->SetLineColorAlpha(kRed-3, 0.6);

    h2OldClusters->SetLineColor(kBlue-6);
    h2OldClusters->SetLineWidth(1);

    // leading clusters should stand out
    h2LeadingOld->SetLineColor(kBlue);
    h2LeadingOld->SetLineWidth(3);

    // leading clusters should stand out
    h2LeadingNew->SetFillStyle(1001);
    h2LeadingNew->SetFillColorAlpha(kRed, 1.0);



    Long64_t tentry = t->LoadTree(iEvent);
    t->GetEntry(tentry);
    std::printf("Event %i\n", event);

    // Get ECAL TPGs
    double ecalMinPt = 0;
    if (ecalMinPt > 0){
        std::printf("[INFO:] plotEventDisplayPhaseIIecalCrystals.C: do not show ECAL TPGs with energy under %f GeV", ecalMinPt);
    }

    for (unsigned int j = 0; j < vEcalTpgs->size(); ++j) {
        if (vEcalTpgs->at(j).Pt() > ecalMinPt) {
            float ceta = vEcalTpgs->at(j).Eta();
            float cphi = vEcalTpgs->at(j).Phi();
            float cpt  = vEcalTpgs->at(j).Pt();

            h2EcalTpgs->Fill(ceta, cphi, cpt);
            // std::printf("vEcalTpgs->at(j).Pt() %f eta %f phi %f\n", cpt, ceta, cphi);
        }
    }

    // Get HCAL TPGs
    double hcalMinPt = 0;
    if (hcalMinPt > 0){
        std::printf("[INFO:] plotEventDisplayPhaseIIecalCrystals.C: do not show HCAL TPGs with energy under %f GeV", hcalMinPt);
    }


    for (UInt_t j = 0; j < vHcalTpgs->size(); ++j) {
        if(vHcalTpgs->at(j).Pt() > hcalMinPt) {
            float ceta = vHcalTpgs->at(j).Eta();
            float cphi = vHcalTpgs->at(j).Phi();
            float cpt  = vHcalTpgs->at(j).Pt();

            h2HcalTpgs->Fill(ceta, cphi, cpt);

        }
    }

    // Get the new emulator clusters
    float clusterMinPt = 0;
    float newLeadingClusterEta = 0;
    float newLeadingClusterPhi = 0;
    float newLeadingClusterPt = 0;

    std::printf("[INFO:] Found %zu new emulator clusters...\n",  vNewClusters->size());

    for (unsigned int j = 0; j < vNewClusters->size(); ++j) {  // only save non-leading clusters

        float ceta = vNewClusters->at(j).Eta();
        float cphi = vNewClusters->at(j).Phi();
        float cpt  = vNewClusters->at(j).Pt();

        h2NewClusters->Fill(ceta, cphi, cpt);
        

        std::printf("vNewClusters->at(%i).Pt() %f eta %f phi %f\n", j, cpt, ceta, cphi);
    }


    // Save the leading new cluster
    if (vNewClusters->size() > 0) {
        newLeadingClusterEta = vNewClusters->at(0).Eta();
        newLeadingClusterPhi = vNewClusters->at(0).Phi();
        newLeadingClusterPt = vNewClusters->at(0).Pt();
        h2LeadingNew->Fill(newLeadingClusterEta, newLeadingClusterPhi, newLeadingClusterPt);
    }

    // Get the old emulator clusters
    float oldLeadingClusterEta = 0;
    float oldLeadingClusterPhi = 0;
    float oldLeadingClusterPt = 0;
    for (unsigned int j = 0; j < vOldClusters->size(); ++j) {
       if (deltaR(vOldClusters->at(0).Eta(), vOldClusters->at(j).Eta(), vOldClusters->at(0).Phi(), vOldClusters->at(j).Phi()) 
            < 0.04)  {

            float ceta = vOldClusters->at(j).Eta();
            float cphi = vOldClusters->at(j).Phi();
            float cpt  = vOldClusters->at(j).Pt();

            h2OldClusters->Fill(ceta, cphi, cpt);

            std::printf("vOldClusters->at(%i).Pt() %f eta %f phi %f\n", j, cpt, ceta, cphi);
            }
    }
    

    // Save the leading new cluster
    if (vOldClusters->size() > 0) {
        oldLeadingClusterEta = vOldClusters->at(0).Eta();
        oldLeadingClusterPhi = vOldClusters->at(0).Phi();
        oldLeadingClusterPt = vOldClusters->at(0).Pt();
        h2LeadingOld->Fill(oldLeadingClusterEta, oldLeadingClusterPhi, oldLeadingClusterPt);
    }

    /*
     * Do plots that show both clusters (dynamically adjusting the scope if they are far apart).
     */
    float etaCenter, phiCenter, etaMin, etaMax, phiMin, phiMax;
    char name[100];
    char* saveFile = new char[300];

    etaCenter = oldLeadingClusterEta;
    phiCenter = oldLeadingClusterPhi;
    
    etaMin = etaCenter - 0.25;
    etaMax = etaCenter + 0.25;
    phiMin = phiCenter - 0.25;
    phiMax = phiCenter + 0.25;

    printf("[INFO:] Centering plot on leading cluster in old emulator at %f, %f.....", etaCenter, phiCenter);

    
    sprintf(name, "Event %u", event);
    h2HcalTpgs->SetTitle(name);
    sprintf(saveFile, "event-%u.pdf",event);

    
    makePlots(etaMin, etaMax, phiMin, phiMax, oldLeadingClusterEta, oldLeadingClusterPhi, newLeadingClusterEta, newLeadingClusterPhi, h2HcalTpgs, h2EcalTpgs, h2OldClusters, h2NewClusters, h2LeadingOld, h2LeadingNew, event, saveFile);



    
}

