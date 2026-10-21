#include "MovingObject.h"
#include <TFile.h>
#include <TTree.h>
#include <TRandom.h>
#include <iostream>

void write() {
  TFile *file = new TFile("tree_file.root", "RECREATE");
  if (file->IsZombie()) {
    std::cout << "could not create tree_file.root" << std::endl;
    return;
  }

  TTree *tree = new TTree("tree", "velocity measurements");

  MovingObject *object = new MovingObject();
  tree->Branch("object", &object);

  gRandom->SetSeed(12345);

  const Int_t nMeasurements = 10000;
  for (Int_t i = 0; i < nMeasurements; ++i) {
    Double_t vx = gRandom->Gaus(0.0, 0.30);
    Double_t vy = gRandom->Gaus(0.0, 0.30);
    Double_t vz = gRandom->Gaus(0.0, 0.30);
    object->SetVelocity(vx, vy, vz);
    tree->Fill();
  }

  std::cout << "entries in tree: " << tree->GetEntries() << std::endl;

  tree->Write();
  file->Close(); // also deletes the tree, it belongs to the file
  delete file;
  delete object;
}