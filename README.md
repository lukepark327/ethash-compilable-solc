# sol_breakdown
make my own solidity

## Clone the Repository
```bash
git clone --recursive https://github.com/ethereum/solidity.git
cd solidity
```

## Install Dependencies
```bash
./scripts/install_deps.sh
```

## Command-Line Build
```bash
./scripts/build.sh
```
or
```bash
mkdir build
cd build
cmake .. && make
```

## TODO
1. libevmasm의 Instruction.h, Instruction.cpp에 OPCODE 추가
2. libevmasm/SemanticInformation.cpp에 OPCODE 추가
3. libsolidity/codegen/ExpressionCompiler.cpp 수정

Let's do it!
