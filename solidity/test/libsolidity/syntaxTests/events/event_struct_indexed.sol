contract c {
    struct S { uint a ; }
    event E(S indexed);
}
// ----
// TypeError: (51-60): This type is only supported in the new experimental ABI encoder. Use "pragma experimental ABIEncoderV2;" to enable the feature.
