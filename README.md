# sol_breakdown
make my own solidity

## Clone the Repository
```bash
$ git clone --recursive https://github.com/ethereum/solidity.git
$ cd solidity
```

## Install Dependencies
```bash
$ ./scripts/install_deps.sh
```

## Command-Line Build
```bash
$ ./scripts/build.sh
```
or
```bash
$ mkdir build
$ cd build
$ cmake .. && make
```

# How to Use

## Compile
```bash
$ echo "var testOutput=`solc --optimize --combined-json abi,bin,interface solexam/test1.sol`" > solexam/test.js
```
which ```solexam/test1.sol``` is a file for testing.

```bash
$ cat solexam/test.js
var testOutput={"contracts":{"solexam/test1.sol:test1":{"abi":"[{\"constant\":true,\"inputs\":[],\"name\":\"getNum\",\"outputs\":[{\"name\":\"\",\"type\":\"uint256\"}],\"payable\":false,\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[],\"payable\":false,\"stateMutability\":\"nonpayable\",\"type\":\"constructor\"}]","bin":"6080604052348015600f57600080fd5b50436000556077806100226000396000f3fe6080604052348015600f57600080fd5b506004361060285760003560e01c806367e0badb14602d575b600080fd5b60336045565b60408051918252519081900360200190f35b6000549056fea165627a7a7230582078e56c51dc19f67e82b3665ea0d065284247b45a9e463798d34ab629327efc9e0029"}},"version":"0.5.9-develop.2019.5.2+commit.0fcb3e85.Darwin.appleclang"}
```

## Run on EVM
in geth console,
```bash
> loadScript("/Users/luke/Desktop/solidity/solexam/test.js")
true
> testOutput
{
  contracts: {
    solexam/test1.sol:test1: {
      abi: "[{\"constant\":true,\"inputs\":[],\"name\":\"getNum\",\"outputs\":[{\"name\":\"\",\"type\":\"uint256\"}],\"payable\":false,\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[],\"payable\":false,\"stateMutability\":\"nonpayable\",\"type\":\"constructor\"}]",
      bin: "6080604052348015600f57600080fd5b50436000556077806100226000396000f3fe6080604052348015600f57600080fd5b506004361060285760003560e01c806367e0badb14602d575b600080fd5b60336045565b60408051918252519081900360200190f35b6000549056fea165627a7a7230582078e56c51dc19f67e82b3665ea0d065284247b45a9e463798d34ab629327efc9e0029"
    }
  },
  version: "0.5.9-develop.2019.5.2+commit.0fcb3e85.Darwin.appleclang"
}
```

## TODO
1. libevmasm의 Instruction.h, Instruction.cpp에 OPCODE 추가
2. libevmasm/SemanticInformation.cpp에 OPCODE 추가
3. libsolidity/codegen/ExpressionCompiler.cpp 수정

Let's do it!
