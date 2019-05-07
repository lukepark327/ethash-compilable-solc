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
