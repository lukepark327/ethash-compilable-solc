/*
    This file is part of solidity.

    solidity is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    solidity is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with solidity.  If not, see <http://www.gnu.org/licenses/>.
*/
/**
 * @author Christian <c@ethdev.com>
 * @date 2015
 * Parses and analyses the doc strings.
 * Stores the parsing results in the AST annotations and reports errors.
 */

#pragma once

#include <libsolidity/ast/ASTVisitor.h>

namespace langutil
{
class ErrorReporter;
}

namespace dev
{
namespace solidity
{

/**
 * Parses and analyses the doc strings.
 * Stores the parsing results in the AST annotations and reports errors.
 */
class DocStringAnalyser: private ASTConstVisitor
{
public:
	DocStringAnalyser(langutil::ErrorReporter& _errorReporter): m_errorReporter(_errorReporter) {}
	bool analyseDocStrings(SourceUnit const& _sourceUnit);

private:
	bool visit(ContractDefinition const& _contract) override;
	bool visit(FunctionDefinition const& _function) override;
	bool visit(ModifierDefinition const& _modifier) override;
	bool visit(EventDefinition const& _event) override;

	void checkParameters(
		CallableDeclaration const& _callable,
		DocumentedAnnotation& _annotation
	);

	void handleConstructor(
		CallableDeclaration const& _callable,
		Documented const& _node,
		DocumentedAnnotation& _annotation
	);

	void handleCallable(
		CallableDeclaration const& _callable,
		Documented const& _node,
		DocumentedAnnotation& _annotation
	);

	void parseDocStrings(
		Documented const& _node,
		DocumentedAnnotation& _annotation,
		std::set<std::string> const& _validTags,
		std::string const& _nodeName
	);

	void appendError(std::string const& _description);

	bool m_errorOccured = false;
	langutil::ErrorReporter& m_errorReporter;
};

}
}
