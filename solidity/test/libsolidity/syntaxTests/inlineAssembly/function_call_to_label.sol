contract C {
  function f() public pure {
    assembly {
      l:

      l()
    }
  }
}
// ----
// SyntaxError: (63-64): The use of labels is disallowed. Please use "if", "switch", "for" or function calls instead.
// SyntaxError: (63-64): Jump instructions and labels are low-level EVM features that can lead to incorrect stack access. Because of that they are discouraged. Please consider using "switch", "if" or "for" statements instead.
// TypeError: (73-74): Attempt to call label instead of function.
