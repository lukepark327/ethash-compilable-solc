contract test {
    function f(uint x) pure public {
        uint y = +x;
        y;
    }
}
// ----
// SyntaxError: (70-72): Use of unary + is disallowed.
