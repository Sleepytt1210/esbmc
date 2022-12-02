# GotoFuzz Build Guide

This is a short guide on how to build the GotoFuzz. 

## Building GotoFuzz

GotoFuzz is built along with esbmc. Therefore, the environment and dependencies for building ESBMC should be first set up, where the guide can be found [here](**https://github.com/esbmc/esbmc/blob/master/BUILDING.md**). 

Next, several flags need to be set when building:
  - set clang/clang++ as the complier/linker: `-DCMAKE_C_COMPILER=$PWD/../../clang11/bin/clang`, `-DCMAKE_CXX_COMPILER=$PWD/../../clang11/bin/clang++`
  - enable "fuzz" sanitizer mode: `-DCMAKE_BUILD_TYPE=Sanitizer`, `-DSANITIZER_TYPE=FUZZ`
  - collect coverage information: `-DENABLE_COVERAGE=On`

Here is a building command examaple
```sh
cmake .. -GNinja -DCMAKE_C_COMPILER=$PWD/../../clang11/bin/clang -DCMAKE_CXX_COMPILER=$PWD/../../clang11/bin/clang++ -DBUILD_TESTING=Off -DENABLE_REGRESSION=Off  -DClang_DIR=$PWD/../../clang11 -DLLVM_DIR=$PWD/../../clang11 -DBUILD_STATIC=Off -DZ3_DIR=$PWD/../../z3 -DBoolector_DIR=$PWD/../../boolector-release -DCMAKE_INSTALL_PREFIX:PATH=$PWD/../../release -DCMAKE_BUILD_TYPE=Sanitizer -DSANITIZER_TYPE=FUZZ -DENABLE_COVERAGE=On
```

## Running GotoFuzz

GotoFuzz works as an extension to ESBMC. To run GotoFuzz, simply enable `--goto-fuzz` option. 

In general, there are two options relative to GotoFuzz:
- `goto-fuzz`: enable GotoFuzz
- `goto-fuzz-maxtime`: run GotoFuzz for $t$ seconds (default is 180 and minimum is 30)

Here is a running command examaple
```sh
./esbmc <filename> -unwind 1 --goto-fuzz --goto-fuzz-maxtime 120 --timeout 60
```
- `--goto-fuzz-maxtime` limits the maximum total time of GotoFuzz, while `--timeout` limits the execution time for each round of fuzzing/verification. GotoFuzz will terminate when reaching either of these limits, yet this will not affect the collection of coverage data.

In principle, any C program accepted by ESBMC can be used as input to GotoFuzz. Using Csmith to generate test cases would be a good place to start. By experience,  larger test cases should be avoided as they can easily consume lots of memory and have a low "coverage improvement to running time" ratio. 