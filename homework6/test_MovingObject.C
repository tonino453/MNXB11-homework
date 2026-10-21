#include "MovingObject.h"
#include <iostream>

void test_MovingObject() {
  MovingObject a;
  std::cout << "default: " << a.Vx() << " " << a.Vy() << " " << a.Vz() << std::endl;

  MovingObject b(0.1, -0.2, 0.3);
  std::cout << "ctor(0.1, -0.2, 0.3): " << b.Vx() << " " << b.Vy() << " " << b.Vz() << std::endl;

  b.SetVelocity(-1.0, 2.0, -3.0);
  std::cout << "after SetVelocity(-1, 2, -3): " << b.Vx() << " " << b.Vy() << " " << b.Vz() << std::endl;

  MovingObject exA(0.30, 0.40, 0.00);
  MovingObject exB(0.30, 0.40, 0.50);
  std::cout << "A: v = " << exA.Speed() << " m/s, vxy = " << exA.HorizontalSpeed() << " m/s" << std::endl;
  std::cout << "B: v = " << exB.Speed() << " m/s, vxy = " << exB.HorizontalSpeed() << " m/s" << std::endl;

  bool okA = 0.0 <= exA.HorizontalSpeed() && exA.HorizontalSpeed() <= exA.Speed();
  bool okB = 0.0 <= exB.HorizontalSpeed() && exB.HorizontalSpeed() <= exB.Speed();
  std::cout << "A: 0 <= vxy <= v ? " << (okA ? "yes" : "no") << std::endl;
  std::cout << "B: 0 <= vxy <= v ? " << (okB ? "yes" : "no") << std::endl;
}