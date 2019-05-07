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
