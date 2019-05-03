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

#pragma once

#include <libsolidity/ast/ASTEnums.h>
#include <libsolidity/ast/ASTForward.h>
#include <libsolidity/ast/ASTVisitor.h>

#include <map>
#include <memory>

namespace langutil
{
class ErrorReporter;
struct SourceLocation;
}

namespace dev
{
namespace solidity
{

class ViewPureChecker: private ASTConstVisitor
{
public:
	ViewPureChecker(std::vector<std::shared_ptr<ASTNode>> const& _ast, langutil::ErrorReporter& _errorReporter):
		m_ast(_ast), m_errorReporter(_errorReporter) {}

	bool check();

private:
	struct MutabilityAndLocation
	{
		StateMutability mutability;
		langutil::SourceLocation location;
	};

	bool visit(FunctionDefinition const& _funDef) override;
	void endVisit(FunctionDefinition const& _funDef) override;
	bool visit(ModifierDefinition const& _modifierDef) override;
	void endVisit(ModifierDefinition const& _modifierDef) override;
	void endVisit(Identifier const& _identifier) override;
	bool visit(MemberAccess const& _memberAccess) override;
	void endVisit(MemberAccess const& _memberAccess) override;
	void endVisit(IndexAccess const& _indexAccess) override;
	void endVisit(ModifierInvocation const& _modifier) override;
	void endVisit(FunctionCall const& _functionCall) override;
	void endVisit(InlineAssembly const& _inlineAssembly) override;

	/// Called when an element of mutability @a _mutability is encountered.
	/// Creates appropriate warnings and errors and sets @a m_currentBestMutability.
	void reportMutability(
		StateMutability _mutability,
		langutil::SourceLocation const& _location,
		boost::optional<langutil::SourceLocation> const& _nestedLocation = {}
	);

	std::vector<std::shared_ptr<ASTNode>> const& m_ast;
	langutil::ErrorReporter& m_errorReporter;

	bool m_errors = false;
	MutabilityAndLocation m_bestMutabilityAndLocation = MutabilityAndLocation{StateMutability::Payable, langutil::SourceLocation()};
	FunctionDefinition const* m_currentFunction = nullptr;
	std::map<ModifierDefinition const*, MutabilityAndLocation> m_inferredMutability;
};

}
}
