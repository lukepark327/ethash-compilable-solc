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

## Compile with details
```bash
solc -o ./solexam --bin --ast --asm solexam/test1.sol
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
where "12341234" is a password. Then,
```bash
> miner.start()
INFO [05-03|12:25:13.345253] Transaction pool price threshold updated price=18000000000
INFO [05-03|12:25:13.345792] Starting mining operation
null
> INFO [05-03|12:25:13.347485] will Finalize the block
INFO [05-03|12:25:13.34761] Commit new mining work                   number=73 txs=2 uncles=0 elapsed=1.767ms
INFO [05-03|12:25:13.348424] will Seal the block
hash is : 0xd281350627c61a527fdbcfe187b9da9a6e444b7af5dde1bd8d334115ba33b9c3INFO [05-03|12:25:28.3505] Successfully sealed new block            number=73 hash=a800f4…0401c3
INFO [05-03|12:25:28.354655] 🔨 mined potential block                  number=73 hash=a800f4…0401c3
INFO [05-03|12:25:28.354838] will Finalize the block
INFO [05-03|12:25:28.354906] Commit new mining work                   number=74 txs=0 uncles=0 elapsed=201.095µs
INFO [05-03|12:25:28.354969] will Seal the block
null [object Object]
Contract mined! address: 0x37b601a8d2367cb5962dd3d67d6dd9c36f0d8040 transactionHash: 0x7d188b2e0740881798eddbaab1822e0fc1ed5bd6a6877d18f5698293a6bb3261
hash is : 0xa800f471d518abb50a1c8821c1eaf298eae4df88436366ccd274e4870d0401c3INFO [05-03|12:25:43.355571] Successfully sealed new block            number=74 hash=52d6c0…3e0ed9
```
Now you can find Contract's address and deploying transaction's hash.

## TODO
1. libevmasm의 Instruction.h, Instruction.cpp에 OPCODE 추가
2. libevmasm/SemanticInformation.cpp에 OPCODE 추가
3. libsolidity/codegen/ExpressionCompiler.cpp 수정

Let's do it!
