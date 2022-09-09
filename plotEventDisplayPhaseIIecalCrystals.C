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
#include "TBenchmark.h"
#include "TRandom.h"
#include "TSystem.h"
#include <TLorentzVector.h>
#include <TStyle.h>
#include "TLegend.h"
#include "TEllipse.h"
//#include "TPaveText.h"
#include "TLine.h"
#include <sstream>
#include <algorithm>
#include "Math/VectorUtil_Cint.h"


#ifdef __MAKECINT__
#pragma link C++ class vector<float>+;
#endif

#ifdef __MAKECINT__
#pragma link C++ class vector<TLorentzVector>+;
#endif


void DrawCardLines(){
  std::vector<TLine*> cardLines;
  // float etaValues[17] = { -3, -2.107, -1.74, -1.392, -1.044, -0.696, -0.348, 0,
  //   0.348, 0.696, 1.044, 1.392, 1.74, 2.107, 3 };//0.3508
  // float phiValues[18] =
  // {-2.965, -2.617, -2.268, -1.919, -1.570, -1.221, -0.872, -0.523, -0.174, 
  //     0.174, 0.523, 0.872, 1.221, 1.570, 1.919, 2.268, 2.617, 2.965};

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

  for(size_t j = 0; j < cardLines.size(); j++){
    cardLines.at(j)->Draw();
  }
}


/*
 * Draw ECAL region lines.
 */
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

/*
 * Draw tower lines.
 */
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


void plotEventDisplayPhaseIIecalCrystals(int iEvent){
  
  gStyle->SetOptStat(0);
  
  // float half_tower_offset = 0.04365;
  float half_tower_offset = 0.0;

  //TFile *f = TFile::Open("L1EventDisplay_1_62_6189.root", "READ");
  // TFile *f = TFile::Open("L1EventDisplay_1_89_8878.root", "READ"); 
  // TFile *f = TFile::Open("L1EventDisplay_1_23_2119.root", "READ");

  // TFile *f = TFile::Open("L1EventDisplay-cmssw-1_62_6189.root", "READ");
  //TFile *f = TFile::Open("L1EventDisplay-cmssw-1_59_5839.root", "READ");
  // TFile *f = TFile::Open("L1EventDisplay-cmssw-1_89_8878.root", "READ"); 
  // TFile *f = TFile::Open("L1EventDisplay_1_62_6189_newBrems.root", "READ");


  // TFile *f = TFile::Open("L1EventDisplay_1_32_3102.root", "READ");
  // TFile *f = TFile::Open("L1EventDisplay-cmssw-1_32_3102.root", "READ");
  // TFile *f = TFile::Open("L1EventDisplay_1_32_3102_fixed_currentEmulator.root", "READ");

  // TFile *f = TFile::Open("L1EventDisplay_1_32_3111.root", "READ");
  TFile *f = TFile::Open("L1EventDisplay_1_32_3108.root", "READ");   

  // Declare the center of the plot
  float etaCenter = 0.27;
  float phiCenter = -1.7889;

  if (!f) { return; }

  TTree *t = (TTree*) f->Get("l1NtupleProducer/efficiencyTree");

  std::vector<TLorentzVector> *vEcalTpgs       = 0;
  std::vector<TLorentzVector> *vHcalTpgs       = 0;
  std::vector<TLorentzVector> *vClusters       = 0;
  std::vector<TLorentzVector> *vTowers         = 0;

  int event =0;

  // Create a new canvas.
  TCanvas *c1 = new TCanvas("c1","eta vs phi",200,10,700,700);
  c1->SetFillColor(0);
  c1->GetFrame()->SetFillColor(0);
  c1->GetFrame()->SetBorderSize(6);
  c1->GetFrame()->SetBorderMode(-1);

  const Int_t kUPDATE = 1000;

  TBranch *bEvent            = 0;      
  TBranch *bEcalTpgs         = 0;
  TBranch *bHcalTpgs         = 0;
  TBranch *bClusters = 0;
  TBranch *bTowers   = 0;

  t->SetBranchAddress("event",&event,&bEvent);

  t->SetBranchAddress("ecalTPGs",&vEcalTpgs,&bEcalTpgs);
  t->SetBranchAddress("hcalTPGs",&vHcalTpgs,&bHcalTpgs);
  t->SetBranchAddress("ecalClusters",&vClusters,&bClusters);
  t->SetBranchAddress("caloTowers",&vTowers,&bTowers);

  // Create one histograms
  TH1F   *h                = new TH1F("h","This is the eta distribution",100,-4,4);
  TH2F   *h2;//               = new TH2F("h2","Event 2988846758",68,-3.117,3.117,72,-3.142,3.142);
  //  TH2F   *h2EcalTpgs       = new TH2F("h2L1EcalCrystals","h2 title",(136*2),-3.117,3.117,(144*2),-3.142,3.142);
  TH2F   *h2EcalTpgs       = new TH2F("h2L1EcalCrystals","Event Display",(34*5), //(90*2), //64*2
				      -1.4841, 1.4841,
				      (72*5), // (144*2),
				      -3.142,3.142);
  TH2F   *h2HcalTpgs       = new TH2F("h2HcalTpgs","Event Display",34,
				      -1.4841, 1.4841,
				      72,
				      -3.142,3.142);
  TH2F   *h2L1Clusters  = new TH2F("h2L1EcalCrystals","Event Display", (34*5), //(90*2),
				   -1.4841, 1.4841,
				   (72*5),//(144*2),
				   -3.142,3.142); 
  TH2F   *h2L1Towers    = new TH2F("h2L1Towers", "Event Display", 34,
				   -1.4841, 1.4841,
				   72,
				   -3.142,3.142);
  TH2F   *h2L1EcalCrystals;//  = new TH2F("h2L1EcalCrystals","h2 title",(136*2),-3.117,3.117,(144*2),-3.142,3.142);
  
  h->SetFillColor(48);

  int i = iEvent;
  Long64_t tentry = t->LoadTree(i);
  std::cout<<"i "<<i<< " tentry "<< tentry << std::endl;
  bEvent->GetEntry(tentry);
  bEcalTpgs->GetEntry(tentry);
  bHcalTpgs->GetEntry(tentry);
  bClusters->GetEntry(tentry);
  bTowers->GetEntry(tentry);

  //get the event number
  char* name = new char[30];
  sprintf(name,"Event %u",event);
  std::cout<<event<<std::endl;
  std::cout<<name<<std::endl;

  h2 = new TH2F("h2",name,68,-3.117,3.117,72,-3.142,3.142);

  delete name;
  int k = 0;


  double ecalMinPt = 0.5;   // in GeV
  std::cout << "[INFO:] plotEventDisplayPhaseIIecalCrystals.C: do not show ECAL TPGs with energy under "
	    << ecalMinPt << " GeV..." << std::endl;

  for (UInt_t j = 0; j < vEcalTpgs->size(); ++j) {
    double eta = vEcalTpgs->at(j).Eta();
    double phi = vEcalTpgs->at(j).Phi();
    double pt  = vEcalTpgs->at(j).Pt();
    if(pt >= ecalMinPt) {
      h2EcalTpgs->Fill(eta, phi, pt);
      
      std::cout<<"vEcalTpgs->at(j).Pt() "<<vEcalTpgs->at(j).Pt()
             <<" eta "<<vEcalTpgs->at(j).Eta()
             <<" phi "<<vEcalTpgs->at(j).Phi()<<std::endl;
      
      
      std::ostringstream strs;
      strs << pt;
      /*
	std::string text = strs.str();
	eta += 0.01;
	phi += 0.01;
	TPaveText *tempText = new TPaveText( eta, phi, eta+0.1, phi+0.1 );
	tempText->AddText(text.c_str());
	tempText->SetFillColor(0);
	tempText->SetLineColor(0);
	tempText->SetShadowColor(0);
	tempText->SetTextColor(kBlue);
	ecalTpgText.push_back(tempText);
      */
    }
    
  }

  // const static float half_crystal_size = 0.00873;


  // double hcalMinPt = 1.5;
  double hcalMinPt = 0;
  std::cout << "[INFO:] plotEventDisplayPhaseIIecalCrystals.C: do not show HCAL TPGs with energy under "
	    << hcalMinPt << " GeV" << std::endl;
  std::cout << "[INFO:] plotEventDisplayPhaseIIecalCrystals.C: adding half-tower-size eta offset "
	    << half_tower_offset << " to HCAL TPGs" << std::endl;
  for (UInt_t j = 0; j < vHcalTpgs->size(); ++j) {
    if(vHcalTpgs->at(j).Pt()>hcalMinPt) {
      // h2HcalTpgs->Fill(vHcalTpgs->at(j).Eta(), vHcalTpgs->at(j).Phi(), vHcalTpgs->at(j).Pt());
      
      // For visual clarity, add offset in eta
      h2HcalTpgs->Fill(vHcalTpgs->at(j).Eta() + half_tower_offset,
		       vHcalTpgs->at(j).Phi(), vHcalTpgs->at(j).Pt());
    }
    // if(vHcalTpgs->at(j).Pt()>hcalMinPt){
    //   std::cout<<"vHcalTpgs->at(j).Pt() "<<vHcalTpgs->at(j).Pt()
    // 	       <<" eta "<<vHcalTpgs->at(j).Eta()
    // 	       <<" phi "<<vHcalTpgs->at(j).Phi()<<std::endl;
    // }
    
    float ceta = vHcalTpgs->at(j).Eta();                                                                                                                                                   
    float cphi = vHcalTpgs->at(j).Phi();                                                                                                                                                   
    float cpt  = vHcalTpgs->at(j).Pt();
    if ((ceta > (etaCenter - 0.25)) && (ceta < (etaCenter + 0.25))
        && (cphi > (phiCenter - 0.25)) && (cphi < (phiCenter + 0.25))
	&& (cpt > hcalMinPt)) {

      std::cout<<"vHcalTpgs->at(j).Pt() "<< vHcalTpgs->at(j).Pt()
               <<" eta "<<vHcalTpgs->at(j).Eta()
               <<" phi "<<vHcalTpgs->at(j).Phi()<<std::endl;
    }

  }

  // Get the clusters
  for (UInt_t j = 0; j < vClusters->size(); ++j) {
    float ceta = vClusters->at(j).Eta();
    float cphi = vClusters->at(j).Phi();
    float cpt  = vClusters->at(j).Pt();
    
    h2L1Clusters->Fill(vClusters->at(j).Eta(), vClusters->at(j).Phi(), vClusters->at(j).Pt());


    if ((ceta > (etaCenter - 0.25)) && (ceta < (etaCenter + 0.25))
        && (cphi > (phiCenter - 0.25)) && (cphi < (phiCenter + 0.25)) ) {
      // if ((ceta > (-0.9135 -0.45)) && (ceta < (-0.9135 + 0.45)) 
      // && (cphi > (1.87623-0.45)) && (cphi < (1.87623 + 0.45))) {
      // if ((ceta > (-1.05)) && (ceta < (-0.780))
      // 	&& (cphi > (1.75)) && (cphi < (2.1))) {
	std::cout<<"vClusters->at(j).Pt() "<< vClusters->at(j).Pt()              
		 <<" eta "<<vClusters->at(j).Eta()                           
		 <<" phi "<<vClusters->at(j).Phi()<<std::endl;   
    }
  }
  
  // Get the towers
  for (UInt_t j = 0; j < vTowers->size(); ++j) {
    h2L1Towers->Fill(vTowers->at(j).Eta(), vTowers->at(j).Phi(), vTowers->at(j).Pt());
    float ceta = vTowers->at(j).Eta();
    float cphi = vTowers->at(j).Phi();
    float cpt  = vTowers->at(j).Pt();

    if ((ceta > (etaCenter - 0.25)) && (ceta < (etaCenter + 0.25))
     	&& (cphi > (phiCenter - 0.25)) && (cphi < (phiCenter + 0.25))) {
      
      std::cout<<"vTowers->at(j).Pt() "<< vTowers->at(j).Pt()
	       <<" eta "<<vTowers->at(j).Eta()
	       <<" phi "<<vTowers->at(j).Phi()<<std::endl;
    }
  }
  
  
  h2 = (TH2F*)h2EcalTpgs->Clone();
  h2->GetXaxis()->SetAxisColor(17);
  h2->GetYaxis()->SetAxisColor(17);
  h2->Draw();
  

  DrawCardLines();
  DrawRegionLines();
  DrawTowerLines();

  // Plot the HCAL TPGs (first, clone to plot the border)                                                 
  TH2F* h2HcalTpgs2 = (TH2F*)h2HcalTpgs->Clone();
  h2HcalTpgs->SetFillStyle(1001);
  h2HcalTpgs->SetFillColorAlpha(kCyan-10, 0.9);
  h2HcalTpgs->Draw("SAME BOX");
  h2HcalTpgs2->SetLineColor(kBlack);
  h2HcalTpgs2->SetLineWidth(1);
  h2HcalTpgs2->Draw("SAME BOXL");

  // Plot the towers                                                                                       
  TH2F* h2L1Towers2 = (TH2F*)h2L1Towers->Clone();
  h2L1Towers->SetFillStyle(3144);
  h2L1Towers->SetFillColorAlpha(kPink+1, 0.90);
  h2L1Towers->Draw("SAME BOX");
  h2L1Towers2->SetLineColor(kPink+1);
  h2L1Towers2->SetLineWidth(1);
  h2L1Towers2->Draw("SAME BOXL");

  // Plot the ECAL crystals (TPGs)
  TH2F* h2EcalTpgs2 = (TH2F*)h2EcalTpgs->Clone(); 
  h2EcalTpgs->SetFillStyle(1001);
  h2EcalTpgs->SetFillColorAlpha(kCyan-4, 1.0);
  h2EcalTpgs->Draw("SAME BOX");
  h2EcalTpgs2->SetLineColor(kBlack);
  h2EcalTpgs2->SetLineWidth(1);
  h2EcalTpgs2->Draw("SAME BOXL");

  // Plot the clusters
  TH2F* h2L1Clusters2 = (TH2F*)h2L1Clusters->Clone();
  h2L1Clusters->SetFillStyle(3144);
  h2L1Clusters->SetFillColorAlpha(kOrange+10, 0.75);
  h2L1Clusters->Draw("SAME BOX");

  h2L1Clusters2->SetLineColor(kOrange+10);
  h2L1Clusters2->SetLineWidth(1);
  h2L1Clusters2->Draw("SAME BOXL");

  float xR=0.70;
  TLegend *l = new TLegend(xR,0.80,xR+0.30,1.0);
  l->SetTextSize(0.035);

  l->AddEntry(h2EcalTpgs,   "ECAL Crystals",   "F");
  l->AddEntry(h2HcalTpgs,   "HCAL Towers",     "F");
  l->AddEntry(h2L1Clusters, "Clusters out", "F");
  l->AddEntry(h2L1Towers,   "Towers out",   "F");
  l->Draw();
  h2->GetXaxis()->SetTitle("#eta");
  h2->GetYaxis()->SetTitle("#phi");

  h2EcalTpgs->GetXaxis()->SetTitle("#eta"); 
  h2EcalTpgs->GetYaxis()->SetTitle("#phi");    
  
  /*
  for (UInt_t j = 0; j < ecalTpgText.size(); ++j) {
    //ecalTpgText.at(j)->Draw();
    ecalTpgText.at(j)->SetFillColorAlpha(kWhite, 0.01);
    ecalTpgText.at(j)->SetLineColorAlpha(kWhite, 0.001);
    }
  */
  
  // this gives you the value taking into account the zoom
  Double_t xmin = c1->GetUxmin(); 
  Double_t xmax = c1->GetUxmax();
  Double_t ymin = c1->GetUymin(); 
  Double_t ymax = c1->GetUymax();

  // and this gives you the "real" value of the axis (no zoom)
  Double_t xminLimit = h2->GetXaxis()->GetXmin();  
  Double_t xmaxLimit = h2->GetXaxis()->GetXmax();
  Double_t yminLimit = h2->GetMinimum();
  Double_t ymaxLimit = h2->GetMaximum();


  DrawCardLines();
  DrawRegionLines();
  DrawTowerLines();


  // float eta2 = -1.23093;
  // float phi2 = -1.66679;

  // 1_62_6189
  // float eta2= 1.248;
  // float phi2= 1.388;

  // 1_32_3102 
  //float eta2 = 0.77697;
  // float phi2 = 2.34747;

  // 1_89_8878
  // float eta2 = 1.143;
  // float phi2 = 2.417;

  // 1_59_5839
  //float eta2 = 0.428;
  //float phi2 = 2.801;
  
  //  float eta2 = 0.026;
  //float phi2 = 1.387;

  h2->GetXaxis()->SetRangeUser(etaCenter - 0.25, etaCenter + 0.25);
  h2->GetYaxis()->SetRangeUser(phiCenter - 0.25, phiCenter + 0.25);
  
  char* saveFile = new char[100];
  //  sprintf(saveFile,"/eos/user/s/skkwan/phase2RCTDevel/events/Event-%u-old_emulator.png",event);
  
  
  sprintf(saveFile,"/eos/user/s/skkwan/phase2RCTDevel/events/Event-%u-current_emulator.png",event);
  c1->SaveAs(saveFile);

  // sprintf(saveFile,"/eos/user/s/skkwan/phase2RCTDevel/events/Event-%u-old_emulator.pdf",event);
  sprintf(saveFile,"/eos/user/s/skkwan/phase2RCTDevel/events/Event-%u-current_emulator.pdf",event);
  c1->SaveAs(saveFile);



}
