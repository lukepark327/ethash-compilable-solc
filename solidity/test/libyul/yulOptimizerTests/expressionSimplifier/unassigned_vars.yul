// Unassigned variables are assumed to be zero.
{
	let c
	let d
	let y := add(d, add(c, 7))
}
// ====
// step: expressionSimplifier
// ----
// {
//     let c
//     let d
//     let y := 7
// }
