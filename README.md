# dsu.h

`dsu.h` aims to be a Dynamic Software Updating (DSU) solution contained within a single library.

Other DSU frameworks we are aware of require custom kernels or compilers, and also usually source code modifications. Many DSU solutions also cannot support patches to data or data formats.

`dsu.h` provides a DSU solution self-contained within a single library. No custom kernels required. No custom compilers required. Just link the library, supply the required metadata via an API, and build.

## ⚠️Warning

`dsu.h` is currently experimental and under active development. Nothing may work. Anything could change at any time.
