pragma solidity ^0.5.1;

contract test1 {

    uint blocknumber;

    constructor () public {
        blocknumber = block.number;
    }

    function getNum() public view returns(uint) {
        return blocknumber;
    }

}
