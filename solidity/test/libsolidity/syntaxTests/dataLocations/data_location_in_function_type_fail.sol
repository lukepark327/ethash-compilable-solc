library L {
    struct Nested { uint y; }
    function b(function(Nested calldata) external returns (uint)[] storage) external pure {}
    function d(function(Nested storage) external returns (uint)[] storage) external pure {}
}

// ----
// TypeError: (66-81): Data location must be "memory" for parameter in function, but "calldata" was given.
// TypeError: (159-173): Data location must be "memory" for parameter in function, but "storage" was given.
