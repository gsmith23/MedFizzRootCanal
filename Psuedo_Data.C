/*
 Example of using root:
 reading from root file, 
 smearing energy,
 adding file id,
 writing to root file.

 gary.smith@ed.ac.uk
 5th March 2020

 To run in compiled mode do 
 $ root Psuedo_Data.C+"(4,0.2)"
 where 4 is the output file number
 and .2 is the energy resolution
 or
 $ root
 [0] .L Psuedo_Data.C+
 [1] Psuedo_Data()
 as example of running
 in root and using the
 default arguments
*/

#include <iostream> 

#include "TFile.h"
#include "TH1.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TRandom3.h"
#include "TMath.h"

using namespace std;
using namespace TMath;

void Psuedo_Data(int fileNumber = 2, Double_t energyRes = 0.5){
  
  //-----------
  // INPUT
  
  // Declaration of leaf types
  Double_t row_wise_branch;
  
  // List of branches
  TBranch  *b_Eabs;   
  
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

  char  outName[128];
  sprintf(outName,"out_%d.root",fileNumber);

  TFile * outputFile  = new TFile(outName,"RECREATE");
  TTree * outputTree = new TTree("T","T");
  
  outputTree->Branch("eDeposited",&eDeposited,"eDeposited/D");
  outputTree->Branch("eDetected",&eDetected,"eDetected/D");
  outputTree->Branch("fileNumber",&fileNumber,"fileNumber/I");
  
  Long64_t nentries = inputTree->GetEntriesFast();
  bool     comments = true;
  
  TRandom3 * rand3 = new TRandom3(); 
  
  Double_t sigma = energyRes/(2*Sqrt(2*Log(2.)));
  
  for (Long64_t iEntry=0; iEntry<nentries;iEntry++) {
    inputTree->GetEntry(iEntry);

    if(comments){
      printf("\n entry = %lld \n",iEntry);
    }
  
    // energy resolution scales with 1/Sqrt(energy)
    eDetected = rand3->Gaus(eDeposited,sigma*Sqrt(eDeposited));

    if(comments){
      printf("\n deposited energy = %.2f MeV ",eDeposited);
      printf("\n detected  energy = %.2f MeV \n",eDeposited);
    }
  
    outputTree->Fill();
  }
  outputFile->Write();

}
