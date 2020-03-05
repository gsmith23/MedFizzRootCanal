/* 
   A program to plot NECR vs Randoms rate
   
   Author
   --
   gary.smith@ed.ac.uk
   05/03/2020
   
   How to run
   --
   > root
   root [0] .L Graph_NECR.C+
   root [1] Graph_NECR()
   
   output
   --
   a plot is displayed 

 */


#include "TGraph.h"
#include "necr.h"

#include <TLatex.h>

void Graph_NECR(){

  static const int nPoints = 10;
  static const int nSets   = 3;
  
  double SCR[nPoints]         = {0.0};
  double TCR[nSets][nPoints]  = {0.0};
  double RCR[nSets][nPoints]  = {0.0};
  double NECR[nSets][nPoints] = {0.0};
  
  for (int i = 0 ; i < nSets ; i++){
    
    SCR[i] = 0.3+0.1*i;
    
    for (int j = 0 ; j < nPoints ; j++){
      
      RCR[i][j] = (j+1)*(1.0-SCR[i])/nPoints;
      
      TCR[i][j] = 1.0 - SCR[i] - RCR[i][j];
      
      NECR[i][j] = calculateNECR(TCR[i][j],RCR[i][j],SCR[i]);
    }
  }
  
  TGraph * gr[nSets];
  
  for (int i = 0 ; i < nSets ; i++){
    
    gr[i] = new TGraph(nPoints,RCR[i],NECR[i]);
    gr[i]->SetTitle(";Randoms Rate ; NECR");
    gr[i]->SetLineColor(kBlue+3*i);
    
  }

  gr[0]->Draw("APC*");
  
  for (int i = 1 ; i < nSets ; i++)
    gr[i]->Draw("PC* same");

  TLatex * latex = new TLatex(); 
  latex->SetNDC();
  latex->SetTextSize(0.03);;

  char text_scat[nSets][64];
  
  latex->DrawLatex(0.6,0.85,"Scatter Rate");
  
  for (int i = 0 ; i < nSets ; i++){
    sprintf(text_scat[i],"\t %.2f",SCR[i]);
    latex->SetTextColor(kBlue+3*i);
  
    latex->DrawLatex(0.6,0.8-0.05*i,text_scat[i]);
  }

}
