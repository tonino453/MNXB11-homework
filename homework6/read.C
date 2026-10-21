#include "MovingObject.h"
#include <TFile.h>
#include <TTree.h>
#include <TH2D.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <iostream>

void read() {
  TFile *file = TFile::Open("tree_file.root", "READ");
  if (!file || file->IsZombie()) {
    std::cout << "could not open tree_file.root" << std::endl;
    return;
  }

  TTree *tree = (TTree*)file->Get("tree");
  if (!tree) {
    std::cout << "no tree named tree in tree_file.root" << std::endl;
    return;
  }

  MovingObject *object = new MovingObject();
  tree->SetBranchAddress("object", &object);

  Long64_t nEntries = tree->GetEntries();
  std::cout << "entries in tree: " << nEntries << std::endl;

  // 3.1
  TH2D *hVel = new TH2D("hVel", "Velocity components v_{y} vs v_{x};v_{x} [m/s];v_{y} [m/s]",
                        100, -1.5, 1.5, 100, -1.5, 1.5);
  for (Long64_t i = 0; i < nEntries; ++i) {
    tree->GetEntry(i);
    hVel->Fill(object->Vx(), object->Vy());
  }
  std::cout << "histogram entries: " << hVel->GetEntries() << std::endl;
  std::cout << "mean vx = " << hVel->GetMean(1) << ", std dev vx = " << hVel->GetStdDev(1) << std::endl;
  std::cout << "mean vy = " << hVel->GetMean(2) << ", std dev vy = " << hVel->GetStdDev(2) << std::endl;

  gStyle->SetStatX(0.85);
  gStyle->SetStatY(0.89);
  TCanvas *c1 = new TCanvas("c1", "velocity components", 800, 700);
  c1->SetLeftMargin(0.13);
  c1->SetRightMargin(0.15);
  hVel->Draw("COLZ");
  c1->SaveAs("velocity_components.png");
  c1->SaveAs("velocity_components.pdf");

  // 3.2
  TCanvas *c2 = new TCanvas("c2", "horizontal speed vs vz", 800, 700);
  c2->SetLeftMargin(0.13);
  tree->SetMarkerStyle(7);
  Long64_t nSelected = tree->Draw(
      "sqrt(object.fVx*object.fVx + object.fVy*object.fVy):object.fVz",
      "sqrt(object.fVx*object.fVx + object.fVy*object.fVy + object.fVz*object.fVz) > 0.50");
  std::cout << "selected with v > 0.50 m/s: " << nSelected << std::endl;

  TH1 *htemp = (TH1*)gPad->GetPrimitive("htemp");
  if (htemp) {
    htemp->SetTitle("Horizontal speed vs v_{z} for v > 0.50 m/s;v_{z} [m/s];v_{xy} [m/s]");
  }
  c2->Update();
  c2->SaveAs("vxy_vs_vz.png");
  c2->SaveAs("vxy_vs_vz.pdf");

  tree->ResetBranchAddresses();
  delete object;
}