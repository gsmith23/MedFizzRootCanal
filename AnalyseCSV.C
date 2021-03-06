/*

 Examples using root:
 reading from CSV file, 
 writing to root file,
 reading from a TTree,
 and plotting a TGraph.

 gary.smith@ed.ac.uk
 3rd July 2019

 To run do (e.g.)
 $ root AnalyseCSV.C

*/

#include "TFile.h"
#include "TString.h"
#include "TH1.h"
#include "TTree.h"
#include "TCanvas.h"

void CSVToRoot(Int_t cSize = 500){
  
  TFile *outFile = new TFile("Sensitivity.root","RECREATE");
  
  TTree *T = new TTree("Sensitivity","Sensitivity");
  Long64_t nlines;
  TString lineFormat = "Length/F:Sensitivity/F";
  nlines = T->ReadFile("Sensitivity.csv",lineFormat,',');
  
  printf(" Sensitivity at %lld lengths \n",nlines);
  
  TCanvas * c1 =  new TCanvas("c1","c1",0,0,cSize,cSize);

  // Draw straight from TTree
  T->Draw("Sensitivity:Length","","L*");

  T->Write();

  outFile->Close();
}

void PlotTGraphFromRootData(Int_t cSize = 500){
  
  // Declaration of leaf types
  Float_t         Length;
  Float_t         Sensitivity;
  
  // List of branches
  TBranch        *b_Length;   
  TBranch        *b_Sensitivity;  
  
  TFile *file  = new TFile("Sensitivity.root");
  TTree *tree;
  file->GetObject("Sensitivity",tree);
  
  tree->SetBranchAddress("Length", &Length, &b_Length);
  tree->SetBranchAddress("Sensitivity", &Sensitivity, &b_Sensitivity);

  Long64_t nentries = tree->GetEntriesFast();
  
  Float_t LengthArray[nentries], SensitivityArray[nentries];
  
  Bool_t comments = kTRUE;

  for (Long64_t iEntry=0; iEntry<nentries;iEntry++) {
    tree->GetEntry(iEntry);
  
    if(comments){
      cout << endl;
      cout << " entry       = " << iEntry      << endl;
      cout << " Sensitivity = " << Sensitivity << endl;
      cout << " Length      = " << Length      << endl;
    }
    
    LengthArray[iEntry]      = Length;
    SensitivityArray[iEntry] = Sensitivity;
    
  }

  TCanvas * c2 =  new TCanvas("c2","c2",cSize,0,cSize,cSize);
  TGraph * gr = new TGraph(nentries,LengthArray,SensitivityArray);
  gr->SetName("TGraph");
  gr->SetTitle("TGraph from root file;Length (m);Sensitivity (%)");
  
  // Draw TGraph
  gr->Draw("APC*");
  
}

void AnalyseCSV(){

  CSVToRoot();
  PlotTGraphFromRootData();
  
}
