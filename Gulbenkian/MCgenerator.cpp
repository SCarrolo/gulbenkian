//Monte Carlo Event Generator
#include<iostream>
#include <cmath>
//root includes
#include "TGraph.h"
#include "TApplication.h"
#include "TPad.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TGraphErrors.h"
#include "TAxis.h"
#include "TF1.h"
#include "TRandom3.h"

using namespace std;

//distances in cm
//angles in radians
//


double norm(double xp, double yp);
double radiatorIndex(double xp, double yp, double nafRadius, double sio2Radius); //gives coordinates and radius, returns the index of that region
pair<double,double> GenerateImpactPos(double dRadius);
double Generate_angle(double indexp);
vector<double> CircleSampling(double thetac, double dheight ,double xp, double yp, int nsamples);
bool Belong_to_detector(double xp, double yp, double dInnerSide,double dOutterRadius);

int main (void)
{

  //detector characteristics
  double dRadius = 1336.4e-1;
  double dheight = 45.8;
  //radiator characteristics
  double sideTile = 11.4;
  double nafd = 3*0.5*sideTile; //the NaF in the middle is a square, the rest is assumed to be a circle
  double sio2Radius = nafd + 4*sideTile;
  // cout << "Percentage of area occupied by NaF : " <<  pow((2*nafd),2)/(pow(sio2Radius,2)*M_PI) *100 <<endl;



  TRandom3 MCrand(90192); //random number generator
  cout << MCrand.Rndm() << endl;


  pair<double,double> firstPart = GenerateImpactPos(dRadius);
  double auxx = firstPart.first;
  double auxy = firstPart.second;

  if(norm(auxx,auxy) <= dRadius)
    cout << auxx << " " << auxy << endl;
  double indexp = radiatorIndex(auxx,auxy,nafd,sio2Radius);


  cout << "index = " <<indexp << endl;
  double thetac = Generate_angle(indexp);

  // TF1*funcindex = new TF1("funcindex", "acos(1/(x*[0]))",0,1);
  // funcindex->SetParameter(0,indexp);
  // TApplication * MyRootApp;
  // MyRootApp = new TApplication("", NULL, NULL);
  // MyRootApp->SetReturnFromRun(true);
  // TCanvas *c1 = new TCanvas("c1","",1280,720);
  // gPad->Clear();
  // funcindex->Draw();
  // c1->Update();
  // gPad->WaitPrimitive("ggg");
}

bool Belong_to_detector(double xp, double yp, double dInnerRadius,double dOutterRadius)
{

}



vector<double> CircleSampling(double thetac, double dheight ,double xp, double yp, int nsamples)
{
    double Rad = dheight*tan(thetac/2);
    double
}


double Generate_angle(double indexp)
{
  TRandom3 random(90192);
  TF1*funcindex = new TF1("funcindex", "acos(1/(x*[0]))",0,1); //thetac = arcos(1/beta*n)
  funcindex->SetParameter(0,indexp);
  double velocity = random.Rndm()*(1-(1/indexp))+(1/indexp); //dá uma velocidade aleatoria entre a abcissa na origem e 1
  // cout <<"theta de cherenkov: " << funcindex->Eval(auxvelocity) << endl;
  double thetac = funcindex->Eval(velocity);
  return thetac;
}


double norm(double xp, double yp)
{
  return sqrt(pow(xp,2) + pow(yp,2));
}


double radiatorIndex(double xp, double yp, double nafd, double sio2Radius)
{
  //radiator characteristics (reffraction index)
  double nNaf = 1.334;
  double nSio2 = 1.05;
  if(fabs(xp) <= nafd && fabs(yp) <= nafd )
  {
    return nNaf;
  }else if(norm(xp,yp)<= sio2Radius){
    return nSio2;
  }else{
    return 0.0f;
  }
}



pair<double,double> GenerateImpactPos(double dRadius)
{
  TRandom3 rand(90192); //random number generator
  pair<double,double> ipos;
  double auxR = rand.Rndm()*dRadius;
  double auxtheta = rand.Rndm()*2*M_PI;
  ipos.first = auxR*cos(auxtheta);
  ipos.second = auxR*sin(auxtheta);
  return ipos;
}
