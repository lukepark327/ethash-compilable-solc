pragma experimental ABIEncoderV2;

contract C {
    struct T { mapping(uint => uint) a; }
    struct S { T[][2] b; }
    function f(S memory) public {}
}
// ----
// Warning: (0-33): Experimental features are turned on. Do not use experimental features on live deployments.
// TypeError: (132-140): Internal or recursive type is not allowed for public or external functions.
