float betaToGamma(float beta){
  
  float betaSq = beta*beta;

  return 1./TMath::Sqrt(1-betaSq);
}

float thresholdKE(float n){
  
  float beta = 1./n;
  float mass = 511.;
  float gamm = betaToGamma(beta);

  return mass * ( gamm - 1 ) ;
}

float threshTotE(float n){
  
  float beta = 1./n;
  float mass = 511.;
  float gamm = betaToGamma(beta);
    
  return mass*gamm; 
}

void Cherenkov(float n = 1.33){
  
  cout << endl;
  cout << " refractive index  = " << n                  << endl ; 
  cout << " Energy threshold  = " << threshTotE(n) << endl ; 
  cout << " Kinetic threshold = " << thresholdKE(n) << endl ; 
  
  return;
}
