pragma experimental ABIEncoderV2;
contract C {
    struct S { uint a; T[] sub; }
    struct T { uint[] x; }
    function f() public returns (uint, S memory) {
    }
}
// ----
// Warning: (0-33): Experimental features are turned on. Do not use experimental features on live deployments.
// Warning: (112-164): Function state mutability can be restricted to pure
