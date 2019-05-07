# Overview
The implementation of additional solidity instruction(s). Let me show you `ETHASH` as an example. `ETHASH` is an OPCODE which verifies Ethereum's header. It returns true if header is valid, else returns false.
* block.ethash(uint256,bytes32,uint256) returns (bool)

Ethereum Virtual Machine (EVM) and solidity compiler have to be changed. Refer [geth-breakdown](https://github.com/twodude/geth-breakdown) for modified EVM.

## Table

| Opcode | Name | Description | Extra Info | Gas |
| --- | --- | --- | --- | --- |
...
| `0x3e` | RETURNDATACOPY | Copies data from the return data buffer to memory | [EIP 211](https://github.com/ethereum/EIPs/blob/master/EIPS/eip-211.md) | 3 |
| `0x3f` | Unused | - |
| `0x40` | BLOCKHASH | Get the hash of one of the 256 most recent complete blocks | - | 20 |
| `0x41` | COINBASE | Get the block's beneficiary address | - | 2 |
| `0x42` | TIMESTAMP | Get the block's timestamp | - | 2 |
| `0x43` | NUMBER | Get the block's number | - | 2 |
| `0x44` | DIFFICULTY | Get the block's difficulty | - | 2 |
| `0x45` | GASLIMIT | Get the block's gas limit | - | 2 |
| `0x46` | ETHASH | Show the above definition | - | 2 |
| `0x47` - `0x4f` | Unused | - |
| `0x50` | POP | Remove word from stack | - | 2 |
...

We get a new OPCODE `0x46` as ETHASH. You can use ETHASH with a new solidity instruction; `block.ethash(...)`.

## Test
Decode a bytecode which contains my own OPCODE;
Original solidity code is
```bash
$ cat solexam/testEthash.sol
pragma solidity ^0.5.0;

contract testEthash {
	bool blockEthash;

	constructor () public {
		blockEthash = block.ethash(3, "0x12", 6); // blockNumber, Truncated blockHash, nonce
	}

	function getEthash() public view returns(bool) {
		return blockEthash;
	}
}
```
The bytecode of the above code
```
6080604052348015600f57600080fd5b5060067f30783132000000000000000000000000000000000000000000000000000000006003466000805491151560ff19909216919091179055607c806100576000396000f3fe6080604052348015600f57600080fd5b506004361060285760003560e01c806303c6f5b314602d575b600080fd5b60336047565b604080519115158252519081900360200190f35b60005460ff169056fea165627a7a7230582030f87231d1014e4e74a81076801d7b0543a29ffbb290623fb5ac687bb2baea7f0029
```
decodes to
```

[0] DUP1
[2] PUSH1 0x40
[3] MSTORE
[4] CALLVALUE
[5] DUP1
[6] ISZERO
[8] PUSH1 0x0f
[9] JUMPI
[11] PUSH1 0x00
[12] DUP1
[13] REVERT
[14] JUMPDEST
[15] POP
[17] PUSH1 0x06
[50] PUSH32 0x3078313200000000000000000000000000000000000000000000000000000000
[52] PUSH1 0x03
[53] '46'(Unknown Opcode)
[55] PUSH1 0x00
[56] DUP1
[57] SLOAD
```
See [53]. As you know, `0x46` is our new OPCODE. Also you can see [17], [50], [52]. Those are reverse order of parameters; 3, "0x12", and 6.

Refer [Bytecode to Opcode Disassembler by Etherscan](https://etherscan.io/opcode-tool).

# Install

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
If you finish building solc successfully, It may install ```/usr/local/bin/solc``` too. Now you can use solidity compiler in any directory. Just call ```solc```.

# How to Use

## Compile
```bash
$ echo "var testOutput=`build/solc/solc --combined-json abi,bin,interface solexam/testEthash.sol`" > solexam/testEthash.js
```
which ```solexam/testEthash.sol``` is a file for testing. You can add `--optimize` flag for optimization.

```bash
$ cat solexam/testEthash.js
var testOutput={"contracts":{"solexam/testEthash.sol:testEthash":{"abi":"[{\"constant\":true,\"inputs\":[],\"name\":\"getEthash\",\"outputs\":[{\"name\":\"\",\"type\":\"bool\"}],\"payable\":false,\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[],\"payable\":false,\"stateMutability\":\"nonpayable\",\"type\":\"constructor\"}]","bin":"6080604052348015600f57600080fd5b5060067f30783132000000000000000000000000000000000000000000000000000000006003466000806101000a81548160ff021916908315150217905550608f8061005c6000396000f3fe6080604052348015600f57600080fd5b506004361060285760003560e01c806303c6f5b314602d575b600080fd5b6033604d565b604051808215151515815260200191505060405180910390f35b60008060009054906101000a900460ff1690509056fea165627a7a72305820843ff4b78ea01dc4651a5bbe25a9c1c382fc50689719c0edcc25913df3bbc7390029"}},"version":"0.5.9-develop.2019.5.7+commit.0fcb3e85.mod.Darwin.appleclang"}
```

## Compile with details (optional)
```bash
$ build/solc/solc -o ./solexam --bin --ast --asm solexam/testEthash.sol
```

# Run

## Run geth
```bash
$ build/bin/geth --datadir ./mydata/ --networkid 950327 --port 32222 --rpc --rpcport 8222 --nodiscover console
```

## Deploy Contract
in geth console,
```bash
> loadScript("/Users/luke/Desktop/solidity/solexam/testEthash.js")
true
> testOutput
{
  contracts: {
    solexam/testEthash.sol:testEthash: {
      abi: "[{\"constant\":true,\"inputs\":[],\"name\":\"getEthash\",\"outputs\":[{\"name\":\"\",\"type\":\"bool\"}],\"payable\":false,\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[],\"payable\":false,\"stateMutability\":\"nonpayable\",\"type\":\"constructor\"}]",
      bin: "6080604052348015600f57600080fd5b5060067f30783132000000000000000000000000000000000000000000000000000000006003466000806101000a81548160ff021916908315150217905550608f8061005c6000396000f3fe6080604052348015600f57600080fd5b506004361060285760003560e01c806303c6f5b314602d575b600080fd5b6033604d565b604051808215151515815260200191505060405180910390f35b60008060009054906101000a900460ff1690509056fea165627a7a72305820843ff4b78ea01dc4651a5bbe25a9c1c382fc50689719c0edcc25913df3bbc7390029"
    }
  },
  version: "0.5.9-develop.2019.5.7+commit.0fcb3e85.mod.Darwin.appleclang"
}
```
You can check contract bytecodes;
```bash
> testOutput.contracts
{
  solexam/testEthash.sol:testEthash: {
    abi: "[{\"constant\":true,\"inputs\":[],\"name\":\"getEthash\",\"outputs\":[{\"name\":\"\",\"type\":\"bool\"}],\"payable\":false,\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[],\"payable\":false,\"stateMutability\":\"nonpayable\",\"type\":\"constructor\"}]",
    bin: "6080604052348015600f57600080fd5b5060067f30783132000000000000000000000000000000000000000000000000000000006003466000806101000a81548160ff021916908315150217905550608f8061005c6000396000f3fe6080604052348015600f57600080fd5b506004361060285760003560e01c806303c6f5b314602d575b600080fd5b6033604d565b604051808215151515815260200191505060405180910390f35b60008060009054906101000a900460ff1690509056fea165627a7a72305820843ff4b78ea01dc4651a5bbe25a9c1c382fc50689719c0edcc25913df3bbc7390029"
  }
}
```

<!--
수정요망
-->

Deploy by user whose index number is zero.

```bash
> var testContract = web3.eth.contract(JSON.parse(testOutput.contracts["solexam/testEthash.sol:testEthash"].abi));
undefined
> personal.unlockAccount(eth.accounts[0], "12341234");
true
> var test = testContract.new({ from: eth.accounts[0], data: "0x" + testOutput.contracts["solexam/testEthash.sol:testEthash"].bin, gas: 2000000},
  function (e, contract) {
      console.log(e, contract);
      if (typeof contract.address !== 'undefined') {
           console.log('Contract mined! address: ' + contract.address + ' transactionHash: ' + contract.transactionHash);
      }
    }
  );
INFO [05-07|16:06:46.995917] Submitted contract creation              fullhash=0x046c9b19579e6b8dc3fdaf1b257630d4c6ed2f55b161be76fbf51f7f1368402d contract=0x0e8f5FD6e49420F0Bef4A635C5142829F659ee19
null [object Object]
undefined
```
where "12341234" is a password.

## Start mining
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


Now you can find Contract's address and deploying transaction's hash. Then,
```bash
> eth.getTransaction("0x7d188b2e0740881798eddbaab1822e0fc1ed5bd6a6877d18f5698293a6bb3261");
{
  blockHash: "0xa800f471d518abb50a1c8821c1eaf298eae4df88436366ccd274e4870d0401c3",
  blockNumber: 73,
  from: "0x6282ad5f86c03726722ec397844d2f87ced3af89",
  gas: 1000000,
  gasPrice: 18000000000,
  hash: "0x7d188b2e0740881798eddbaab1822e0fc1ed5bd6a6877d18f5698293a6bb3261",
  input: "0x6080604052348015600f57600080fd5b50436000556077806100226000396000f3fe6080604052348015600f57600080fd5b506004361060285760003560e01c806367e0badb14602d575b600080fd5b60336045565b60408051918252519081900360200190f35b6000549056fea165627a7a7230582078e56c51dc19f67e82b3665ea0d065284247b45a9e463798d34ab629327efc9e0029",
  nonce: 1,
  r: "0x2df91d2ba580d1a2a06548bbc903a6a019fda8b8a80c1b70a6165cd0e50a81f2",
  s: "0x50b88eec2941c1e58df22b2679d314eb196e67ffad79cf0135e2fff11681d008",
  to: null,
  transactionIndex: 1,
  v: "0x1d0091",
  value: 0
}
> eth.getBlock(73);
{
  difficulty: 131072,
  extraData: "0xd88301080c846765746887676f312e392e378664617277696e",
  gasLimit: 2254977,
  gasUsed: 127644,
  hash: "0xa800f471d518abb50a1c8821c1eaf298eae4df88436366ccd274e4870d0401c3",
  logsBloom: "0x00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
  miner: "0x6282ad5f86c03726722ec397844d2f87ced3af89",
  mixHash: "0x0000000000000000000000000000000000000000000000000000000000000000",
  nonce: "0x000000000000000a",
  number: 73,
  parentHash: "0xd281350627c61a527fdbcfe187b9da9a6e444b7af5dde1bd8d334115ba33b9c3",
  receiptsRoot: "0xfdf2c387a4464b91e27e557d281380be0d5728aefb3179cbcabf98fe427a2866",
  sha3Uncles: "0x1dcc4de8dec75d7aab85b567b6ccd41ad312451b948a7413f0a142fd40d49347",
  size: 896,
  stateRoot: "0x7a26497ef7e24611fa31fa5ceb17ac8cc83e30c309a67113fe625fee76c42076",
  timestamp: 1556853913,
  totalDifficulty: 9568276,
  transactions: ["0xcaca504190cfeae3817e4dd53633331ef962c638b30f75af5931c334977f2ec9", "0x7d188b2e0740881798eddbaab1822e0fc1ed5bd6a6877d18f5698293a6bb3261"],
  transactionsRoot: "0x0c12bb63b35e604c87454a5bcf2f747b528a2b1cbfcc60c65d3b4f618b944e33",
  uncles: []
}
```

## Call the Contract Function
```bash
> web3.sha3("getNum()")
"0x67e0badbd9d54f8777f844af5013859ed16b3097520a135023bf50d6a299c144"
```
So the function selector for the getNum() function is 0x67e0badb.

```bash
> eth.sendTransaction({from:eth.accounts[0], to:"0x37b601a8d2367cb5962dd3d67d6dd9c36f0d8040", value:0, data:"0x67e0badb0000000000000000000000000000000000000000000000000000000000000000"})
INFO [05-03|12:59:32.177669] Submitted transaction                    fullhash=0xecb0cafd549f32240fbde05f0d0c06247993d3049c248895a55ab9396b7db557 recipient=0x37b601a8d2367CB5962DD3D67d6Dd9c36F0d8040
"0xecb0cafd549f32240fbde05f0d0c06247993d3049c248895a55ab9396b7db557"
```
* from: account of the caller. 
* to: contract address 
* value: since the purpose of this call is not to transfer money, this value is 0.
* data: describes the function to call and what parameters to use.
  * The first four bytes are the function selector. This is to call the getNum() function so 0x67e0badb.
  * Since the set function has no parameter,
    * The word length is 32 bytes.
    * The value set here is 0x0000 because there is no set value. Actually, I think that I show you a wrong example... Anyway,
    
```bash
> eth.getStorageAt("0x37b601a8d2367cb5962dd3d67d6dd9c36f0d8040",0);
"0x0000000000000000000000000000000000000000000000000000000000000049"
```
because of 0x49==73.

# Trouble Shootings

## Fail to Deploy

If error occurs, you might see the message below;
```bash
Error: The contract code couldn't be stored, please check your gas amount. undefined
```
You need to allocate more gas.

# References
[1] https://ethereum.stackexchange.com/questions/15435/how-to-compile-solidity-contracts-with-geth-v1-6   
[2] https://blog.csdn.net/weixin_40401264/article/details/78136346   
[3] https://javaexpert.tistory.com/946   
