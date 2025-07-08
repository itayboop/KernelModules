
**compile:**
```bash
mkdir -p build
cd build
cmake .. -G Ninja
ninja
```

**run:**
```bash
./bin/MyShell
```

**Run gtest:**
```bash
./bin/<gtest_path> --gtest_filter=<test_suite_name>.<test_name>
```
**example:**
```bash
./bin/mytest --gtest_filter=SimpleTest.TestAddition
```

