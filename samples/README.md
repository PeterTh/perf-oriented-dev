This is a small set of simple C benchmarks designed to look at various performance aspects.

Basic build instructions (from this directory):

```bash
mkdir build
cd build
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release
ninja
```

Keep in mind that microbenchmarking is a very specific scenario and *will* fail to account for the impact that embedding the respective algorithms in larger programs might have on various performance aspects. 