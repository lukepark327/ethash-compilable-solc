contract test {
	function fun() {
		mapping(var=>bytes32) d;
	}
}
// ----
// ParserError: (44-47): Expected elementary type name for mapping key type
