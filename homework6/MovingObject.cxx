#include "MovingObject.h"

ClassImp(MovingObject);

MovingObject::MovingObject() : fVx(0.0), fVy(0.0), fVz(0.0) {}

MovingObject::MovingObject(Double_t vx, Double_t vy, Double_t vz)
    : fVx(vx), fVy(vy), fVz(vz) {}

MovingObject::~MovingObject() {}

Double_t MovingObject::Vx() const { return fVx; }
Double_t MovingObject::Vy() const { return fVy; }
Double_t MovingObject::Vz() const { return fVz; }

// placeholder until part 2
Double_t MovingObject::Speed() const { return 0.0; }
Double_t MovingObject::HorizontalSpeed() const { return 0.0; }

void MovingObject::SetVelocity(Double_t vx, Double_t vy, Double_t vz) {
  fVx = vx;
  fVy = vy;
  fVz = vz;
}