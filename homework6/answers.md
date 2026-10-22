# Homework 6 - ROOT

Tonino Cosentino (GitHub: tonino453)

## Files

- `MovingObject.h`, `MovingObject.cxx` - the class
- `test_MovingObject.C` - test macro for task 4 and 5
- `write.C` - writing macro (the PDF says `write.cxx` once but runs `.x write.C`, so I used `write.C`)
- `read.C` - reading macro
- `tree_file.root` - generated data
- `velocity_components.png/.pdf` - plot for task 7
- `vxy_vs_vz.png/.pdf` - scatter plot from 3.2

## Commands (ROOT 6.28/10, course container on COSMOS)

Session 1:
```
root -l
.L MovingObject.cxx+
.x test_MovingObject.C
.x write.C
.q
```

Session 2:
```
root -l
.L MovingObject.cxx+
.x read.C
.q
```

## Header guard / #pragma once

Both make sure the header is only included once, otherwise the class is defined two times and the compiler gives an error. The header guard is normal C++ and works everywhere, but the macro name must be unique. `#pragma once` is shorter and needs no name, but it is not in the C++ standard (most compilers support it). I used the header guard.

## Task 1

In a `struct` everything is `public` by default, in a `class` everything is `private` by default.

## Task 2

With `TObject` and `ClassDef` ROOT knows how to save and read the class, so it can be written to a TFile and used as an object branch in a TTree.

## Task 3

`.L MovingObject.cxx+` compiles without errors:
```
Info in <TUnixSystem::ACLiC>: creating shared library .../homework6/./MovingObject_cxx.so
```

## Task 4

Output of `test_MovingObject.C`:
```
default: 0 0 0
ctor(0.1, -0.2, 0.3): 0.1 -0.2 0.3
after SetVelocity(-1, 2, -3): -1 2 -3
```

## Task 5

- A (0.30, 0.40, 0.00): v = 0.5 m/s, vxy = 0.5 m/s
- B (0.30, 0.40, 0.50): v = 0.707107 m/s, vxy = 0.5 m/s

vz is not in the formula for vxy, so vxy stays the same. v has vz^2 inside, so it gets bigger. Because vz^2 >= 0 it is always 0 <= vxy <= v (test macro prints "yes" for A and B).

## Task 6

Seed 12345, 10000 measurements, vx, vy, vz each from `gRandom->Gaus(0.0, 0.30)` (mean 0 m/s, sigma 0.30 m/s).

`write.C` prints `entries in tree: 10000`. In a new session `t->GetEntries()` also gives 10000, and `t->Print()` shows the branch `object` with `fVx`, `fVy`, `fVz`.

## Task 7

Output of `read.C`:
```
entries in tree: 10000
histogram entries: 10000
mean vx = 0.00138713, std dev vx = 0.300353
mean vy = -0.000696261, std dev vy = 0.301842
```

`velocity_components.png` shows a round Gaussian spot at (0, 0). It is round because vx and vy have the same sigma. Mean around 0 and std dev around 0.30 fit the generation. The colour is the number of measurements per bin.

## 3.2 Scatter plot

```
tree->Draw("sqrt(object.fVx*object.fVx + object.fVy*object.fVy):object.fVz",
           "sqrt(object.fVx*object.fVx + object.fVy*object.fVy + object.fVz*object.fVz) > 0.50");
```

4242 of 10000 measurements are selected.

In `vxy_vs_vz.png` there is an empty half circle with radius 0.5 m/s. Because v^2 = vxy^2 + vz^2, all points inside it have v < 0.5 and are cut. Only the upper half is there because vxy is never negative.