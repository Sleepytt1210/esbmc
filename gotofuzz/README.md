## Building GotoFuzz

- GotoFuzz builds as an extention to ESBMC. First, the ESBMC dependencies need to be installed. The instruction can be found [here](**https://github.com/esbmc/esbmc/blob/master/BUILDING.md**). Next, several flags need to be set when building:
    - set clang as complier: `-DCMAKE_C_COMPILER=$PWD/../../clang11/bin/clang -DCMAKE_CXX_COMPILER=$PWD/../../clang11/bin/clang++`
    - enable "fuzz" sanitizer mode: `-DCMAKE_BUILD_TYPE=Sanitizer -DSANITIZER_TYPE=FUZZ`
    - collect coverage information: `-DENABLE_COVERAGE=Off`
- Here is a building command examaple, which can be varied due to demmand
```sh
cmake .. -GNinja -DCMAKE_C_COMPILER=$PWD/../../clang11/bin/clang -DCMAKE_CXX_COMPILER=$PWD/../../clang11/bin/clang++ -DBUILD_TESTING=Off -DENABLE_REGRESSION=Off  -DClang_DIR=$PWD/../../clang11 -DLLVM_DIR=$PWD/../../clang11 -DBUILD_STATIC=Off -DZ3_DIR=$PWD/../../z3 -DBoolector_DIR=$PWD/../../boolector-release -DCMAKE_INSTALL_PREFIX:PATH=$PWD/../../release -DCMAKE_BUILD_TYPE=Sanitizer -DSANITIZER_TYPE=FUZZ -DENABLE_COVERAGE=On
```

## Running GotoFuzz

- To run GotoFuzz, add `--gotofuzz` option to the verification command. Smaller files with more complex language features will give better results. 
- In general, there are two options relative to GotoFuzz:
  - `goto-fuzz-maxtime`
  - `goto-fuzz`
- example command:
```sh
./esbmc <filename> -unwind 1 --gotofuzz 120 [--timeout 60]
```