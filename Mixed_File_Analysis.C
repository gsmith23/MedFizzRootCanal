/*
  Read from two root files:
  for analysing the first with a 
  fraction of events from the second 
  file - ie event mixing
  
  gary.smith@ed.ac.uk
  5th March 2020

  How to run:
  $ root
  [0] .L Mixed_File_Analysis.C+
  [1] .L Mixed_File_Analysis("out_1.root","out_1.root",0.1)
  where the first two args are filenames
  and the third is the proportion of events
  for which to add data from the second file 
  ie fraction of multiples

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

void Mixed_File_Analysis(string inFileName    = "out_1.root",
			 string multiFileName = "out_2.root",
			 double multiFrac     = 0.1){
  
  // input file containing trues 
  // (and possibly scattered, random events)
  TFile *inFile = new TFile(inFileName.c_str(),"read");
  TTree *inTree;

  // just adding one variable as example
  Double_t       eDet_in;
  TBranch        *b_eDet_in; 

  inFile->GetObject("T",inTree);
  inTree->SetBranchAddress("eDetected", &eDet_in, &b_eDet_in);
  
  // second input file with which to add multiples 
  TFile *multiFile = new TFile(multiFileName.c_str(),"read");
  TTree *multiTree; 

  // just adding one variable as example
  Double_t       eDet_multi;
  TBranch        *b_eDet_multi; 
  
  multiFile->GetObject("T",multiTree);
  
  // note that the variable name in the file "eDetected" is remapped to
  // distinguish it from the variable from the other tree
  multiTree->SetBranchAddress("eDetected", &eDet_multi, &b_eDet_multi);
  
  int nent_in = inTree->GetEntriesFast();
  int nent_multi = multiTree->GetEntriesFast();
  int nentries = TMath::Min(nent_in,nent_multi);

  TRandom3 * rand3 = new TRandom3(0); 

  double eDiff;
  double randNum;
  
  for (int iEntry=0; iEntry<nentries;iEntry++) {
    
    inTree->GetEntry(iEntry);
    multiTree->GetEntry(iEntry);
    
    // double between 0 and 1
    randNum = rand3->Uniform(0,1);
    //printf("\n randNum = %f  \n",randNum);
    
    //-----------
    // apply some algorithm 
    
    // apply a fixed fraction of 
    // events from multiples file
    // choosing which events randomly 
    if( randNum < multiFrac ){
    
      eDiff = 511. - eDet_multi;
      
      if( eDiff > 0.3  ){
	printf("\n eDiff,mu = %.2f MeV   ",eDiff);
	printf("\n (aka n photons = 3) \n");
      }
    }
    else{
      
      eDiff = 511. - eDet_in;

      if( eDiff > 0.3  ) {
	printf("\n eDiff,in = %.2f MeV   ",eDiff);
	printf("\n (aka n photons = 2) \n");
      }
    }

  }
}
