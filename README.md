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
> testOutput.contracts
{
  solexam/test1.sol:test1: {
    abi: "[{\"constant\":true,\"inputs\":[],\"name\":\"getNum\",\"outputs\":[{\"name\":\"\",\"type\":\"uint256\"}],\"payable\":false,\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[],\"payable\":false,\"stateMutability\":\"nonpayable\",\"type\":\"constructor\"}]",
    bin: "6080604052348015600f57600080fd5b50436000556077806100226000396000f3fe6080604052348015600f57600080fd5b506004361060285760003560e01c806367e0badb14602d575b600080fd5b60336045565b60408051918252519081900360200190f35b6000549056fea165627a7a7230582078e56c51dc19f67e82b3665ea0d065284247b45a9e463798d34ab629327efc9e0029"
  }
}
> var testContract = web3.eth.contract(JSON.parse(testOutput.contracts["solexam/test1.sol:test1"].abi));
undefined
> personal.unlockAccount(eth.accounts[0], "12341234");
true
> var test = testContract.new({ from: eth.accounts[0], data: "0x" + testOutput.contracts["solexam/test1.sol:test1"].bin, gas: 1000000},
  function (e, contract) {
      console.log(e, contract);
      if (typeof contract.address !== 'undefined') {
           console.log('Contract mined! address: ' + contract.address + ' transactionHash: ' + contract.transactionHash);
      }
    }
  );
INFO [05-03|12:23:26.625265] Submitted contract creation              fullhash=0x7d188b2e0740881798eddbaab1822e0fc1ed5bd6a6877d18f5698293a6bb3261 contract=0x37b601a8d2367CB5962DD3D67d6Dd9c36F0d8040
null [object Object]
undefined
>
```
where "12341234" is a password.

## TODO
1. libevmasm의 Instruction.h, Instruction.cpp에 OPCODE 추가
2. libevmasm/SemanticInformation.cpp에 OPCODE 추가
3. libsolidity/codegen/ExpressionCompiler.cpp 수정

Let's do it!
