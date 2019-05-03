pragma solidity ^0.5.0;

contract testEthash {
	uint blockEthash;

	constructor () public {
		blockEthash = block.ethash;
	}
	
	function getEthash() public view returns(uint) {
		return blockEthash;
	}
}

