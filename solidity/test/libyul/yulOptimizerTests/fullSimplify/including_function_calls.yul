{
    function f() -> a {}
    let b := add(7, sub(f(), 7))
    mstore(b, 0)
}
// ----
// fullSimplify
// {
//     function f() -> a
//     {
//     }
//     mstore(f(), 0)
// }
