// original author I. Ojalvo

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




void plotEventDisplayPhase2ECALCrystals(const char* inFile, int iEvent){

    // Necessary to declare dictionary, else ROOT complains about reading a custom class
    gInterpreter->GenerateDictionary("vector<TLorentzVector>", "vector");
  
    gStyle->SetOptStat(0);
  
    // float half_tower_offset = 0.04365;
    float half_tower_offset = 0.0;

    TFile *f = TFile::Open(inFile, "READ");

    if (!f) { return; }

    TTree *t = (TTree*) f->Get("l1NtupleSingleProducer/dispTree");

    std::vector<TLorentzVector> *vEcalTpgs       = 0;
    std::vector<TLorentzVector> *vHcalTpgs       = 0;

    std::vector<TLorentzVector> *vOldClusters     = 0;
    // std::vector<TLorentzVector> *vOldTowers       = 0;

    std::vector<TLorentzVector> *vNewClusters       = 0;
    std::vector<TLorentzVector> *vNewTowers         = 0;

    int event = 0;

    // Create a new canvas.
    TCanvas *c1 = new TCanvas("c1","eta vs phi",200,10,700,700);
    c1->SetFillColor(0);
    c1->GetFrame()->SetFillColor(0);
    c1->GetFrame()->SetBorderSize(6);
    c1->GetFrame()->SetBorderMode(-1);

    const Int_t kUPDATE = 1000;

    t->SetBranchAddress("event",&event);

    t->SetBranchAddress("ecalTPGs",&vEcalTpgs);
    t->SetBranchAddress("hcalTPGs",&vHcalTpgs);
    t->SetBranchAddress("oldClusters",&vOldClusters);
    // t->SetBranchAddress("oldTowers",&vOldTowers);
    t->SetBranchAddress("newClusters",&vNewClusters);
    //t->SetBranchAddress("newTowers",&vNewTowers);

    TH2F *h2EcalTpgs = new TH2F("h2EcalTpgs","Event Display",(34*5), //(90*2), //64*2
                                -1.4841, 1.4841,
                                (72*5), // (144*2),
                                -3.142,3.142);
    TH2F *h2HcalTpgs = new TH2F("h2HcalTpgs","Event Display",34,
                                -1.4841, 1.4841,
                                72,
                                -3.142,3.142);
    TH2F *h2NewClusters = new TH2F("h2NewClusters","Event Display", (34*5), //(90*2),
                                    -1.4841, 1.4841,
                                    (72*5),//(144*2),
                                    -3.142,3.142); 
    TH2F *h2OldClusters = new TH2F("h2OldClusters","Event Display", (34*5), //(90*2),
                                    -1.4841, 1.4841,
                                    (72*5),//(144*2),
                                    -3.142,3.142); 
    // TH2F   *h2L1Towers    = new TH2F("h2L1Towers", "Event Display", 34,
        // 			   -1.4841, 1.4841,
        // 			   72,
        // 			   -3.142,3.142);
    

    Long64_t tentry = t->LoadTree(iEvent);
    t->GetEntry(tentry);
    std::printf("Event %i\n", event);

    // Set plot center
    float etaCenter, phiCenter;
    std::printf("[INFO:] Found %zu old clusters...", vOldClusters->size());
    if (vOldClusters->size() > 0) {
        etaCenter = vOldClusters->at(0).Eta();
        phiCenter = vOldClusters->at(0).Phi();
    }

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
            std::printf("vEcalTpgs->at(j).Pt() %f eta %f phi %f\n", cpt, ceta, cphi);
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

            if ((ceta > (etaCenter - 0.25)) && (ceta < (etaCenter + 0.25))
                && (cphi > (phiCenter - 0.25)) && (cphi < (phiCenter + 0.25))) {

                std::printf("vHcalTpgs->at(j).Pt() %f eta %f phi %f\n", cpt, ceta, cphi);
            }
        }
    }

    // Get the new emulator clusters
    float clusterMinPt = 0;
    std::printf("[INFO:] Found %zu new emulator clusters...\n",  vNewClusters->size());
    for (unsigned int j = 0; j < vNewClusters->size(); ++j) {
        if (vNewClusters->at(j).Pt() > clusterMinPt) {
            float ceta = vNewClusters->at(j).Eta();
            float cphi = vNewClusters->at(j).Phi();
            float cpt  = vNewClusters->at(j).Pt();

            h2NewClusters->Fill(ceta, cphi, cpt);

            if ((ceta > (etaCenter - 0.25)) && (ceta < (etaCenter + 0.25))
                && (cphi > (phiCenter - 0.25)) && (cphi < (phiCenter + 0.25)) ) {
                std::printf("vNewClusters->at(j).Pt() %f eta %f phi %f\n", cpt, ceta, cphi);
            }
        }
    }


    // Get the old emulator clusters
    for (unsigned int j = 0; j < vOldClusters->size(); ++j) {
        if (vOldClusters->at(j).Pt() > clusterMinPt) {
            float ceta = vOldClusters->at(j).Eta();
            float cphi = vOldClusters->at(j).Phi();
            float cpt  = vOldClusters->at(j).Pt();

            h2OldClusters->Fill(ceta, cphi, cpt);

            if ((ceta > (etaCenter - 0.25)) && (ceta < (etaCenter + 0.25))
                && (cphi > (phiCenter - 0.25)) && (cphi < (phiCenter + 0.25)) ) {
                std::printf("vOldClusters->at(j).Pt() %f eta %f phi %f\n", cpt, ceta, cphi);
            }
        }
    }

    // Plot the HCAL TPGs (first, clone to plot the border)                                                 
    TH2F* h2HcalTpgs2 = (TH2F*)h2HcalTpgs->Clone();
    h2HcalTpgs->SetFillStyle(1001);
    h2HcalTpgs->SetFillColorAlpha(kSpring+10, 0.8);
    h2HcalTpgs->SetLineColorAlpha(kSpring+10, 0.8);
    h2HcalTpgs->GetXaxis()->SetTitle("#eta");
    h2HcalTpgs->GetYaxis()->SetTitle("#phi");
    char name[30];
    sprintf(name, "Event %u", event);
    h2HcalTpgs->SetTitle(name);

    h2HcalTpgs->GetXaxis()->SetRangeUser(etaCenter - 0.5, etaCenter + 0.5);
    h2HcalTpgs->GetYaxis()->SetRangeUser(phiCenter - 0.5, phiCenter + 0.5);

    h2HcalTpgs->Draw("BOX");
    h2HcalTpgs->Draw("SAME BOX");
    h2HcalTpgs2->SetLineColor(kSpring+10);
    h2HcalTpgs2->SetLineWidth(1);
    h2HcalTpgs2->Draw("SAME BOXL");

    DrawCardLines();
    DrawRegionLines();
    DrawTowerLines();

    // Plot the ECAL crystals (TPGs)
    TH2F* h2EcalTpgs2 = (TH2F*)h2EcalTpgs->Clone();
    h2EcalTpgs->SetFillStyle(1001);
    h2EcalTpgs->SetFillColorAlpha(kPink+1, 0.8);
    h2EcalTpgs->SetLineColorAlpha(kPink+1, 0.8);
    h2EcalTpgs->Draw("SAME BOX");
    h2EcalTpgs2->SetLineColor(kPink+1);
    h2EcalTpgs2->SetLineWidth(1);
    h2EcalTpgs2->Draw("SAME BOXL");

    // Plot the new clusters: filled-in only no outlines
    TH2F* h2NewClusters2 = (TH2F*)h2NewClusters->Clone();
    h2NewClusters->SetFillStyle(1001);
    h2NewClusters->SetFillColorAlpha(kRed, 0.5);
    h2NewClusters->SetLineColorAlpha(kRed, 0.5);
    h2NewClusters->Draw("SAME BOX");
    h2NewClusters2->SetLineColor(kRed);
    h2NewClusters2->SetLineWidth(1);
    // h2NewClusters2->Draw("SAME BOXL");

    // Plot the old clusters
    TH2F* h2OldClusters2 = (TH2F*)h2OldClusters->Clone();
    h2OldClusters->SetFillStyle(1001);
    h2OldClusters->SetFillColorAlpha(kBlue, 0.8);
    h2OldClusters->SetLineColorAlpha(kBlue, 0.8);
    // h2OldClusters->Draw("SAME BOX");
    h2OldClusters2->SetLineColor(kBlue);
    h2OldClusters2->SetLineWidth(1);
    h2OldClusters2->Draw("SAME BOXL");

    float xR = 0.7;
    TLegend *l = new TLegend(xR, 0.80, xR+0.30, 1.0);
    l->SetTextSize(0.035);

    l->AddEntry(h2EcalTpgs,   "ECAL Crystals",   "F");
    l->AddEntry(h2HcalTpgs,   "HCAL Towers",     "F");
    l->AddEntry(h2NewClusters, "New Clusters", "F");
    // l->AddEntry(h2L1Towers,   "New Towers",   "F");
    l->AddEntry(h2OldClusters2, "Old Clusters", "F");
    l->Draw();

    char* saveFile = new char[100];
    sprintf(saveFile, "/eos/user/s/skkwan/phase2RCTDevel/eventsSingleAnalyzer/Event-%u.pdf",event);
    c1->SaveAs(saveFile);

    
}

