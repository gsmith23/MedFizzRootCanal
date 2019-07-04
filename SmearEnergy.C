/*
 Example of using root
 reading from root file, 
 smearing energy
 writing to root file.

 gary.smith@ed.ac.uk
 4th July 2019

 To run in compiled mode do 
 $ root SmearEnergy.C+"(.2)"
 where .2 is the energy resolution
 or
 $ root
 [0] .L SmearEnergy.C+
 [1] SmearEnergy(0.15)
*/

#include "TFile.h"
#include "TString.h"
#include "TH1.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TRandom3.h"
#include "TMath.h"

#include <iostream> 

using namespace std;
using namespace TMath;

void SmearEnergy(Double_t energyRes = 0.10){
  
  //-----------
  // INPUT
  // Declaration of leaf types
  Double_t        row_wise_branch;
  
  // List of branches
  TBranch        *b_Eabs;   
  
  // New variable with better name
  Double_t eDeposited;
  
  TFile *inputFile  = new TFile("B3b.root","read");
  TTree *inputTree;
  inputFile->GetObject("E-deposited",inputTree);
  
  // mape row_wise_branch into new variable
  inputTree->SetBranchAddress("row_wise_branch",&eDeposited, &b_Eabs);
  
  //-----------
  /// OUTPUT
  Double_t eDetected;

  TFile *outputFile  = new TFile("B3bout.root","RECREATE");
  TTree *outputTree = new TTree("SmearedEnergy","SmearedEnergy");

  outputTree->Branch("eDeposited",&eDeposited,"eDeposited/D");
  outputTree->Branch("eDetected",&eDetected,"eDetected/D");
  
  TH1D * h1 = new TH1D("h1",
		       "Total Energy Deposited;Energy (keV);Counts",
		       100,0.,0.75);
  TH1D * h2 = new TH1D("h2",
		       "Total Energy Deposited (smeared);Energy (keV);Counts",
		       100,0.,0.75);
  
  Long64_t nentries = inputTree->GetEntriesFast();
  
  Bool_t comments = kFALSE;
  
  TRandom3 * rand3 = new TRandom3(); 
  

  Double_t sigma     = energyRes/(2*Sqrt(2*Log(2.)));
  
  for (Long64_t iEntry=0; iEntry<nentries;iEntry++) {
    inputTree->GetEntry(iEntry);

    if(comments){
      cout << endl;
      cout << " entry      = " << iEntry     << endl;
    }
  
    h1->Fill(eDeposited);
    
    // energy resolution scales with 1/Sqrt(energy)
    eDetected = rand3->Gaus(eDeposited,sigma*Sqrt(eDeposited));
    
    h2->Fill(eDetected);
    
    if(comments){
      cout << endl;
      cout << " eDeposited = " << eDeposited << endl;
      cout << " eDetected  = " << eDetected  << endl;
    }
  
    outputTree->Fill();
  }

  h2->SetLineColor(kRed);
  h2->Draw("same");

  h1->SetLineColor(kBlue);
  h1->Draw("same");
  
  outputFile->Write();

}
