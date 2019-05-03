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

#include <libsolidity/analysis/ControlFlowGraph.h>
#include <set>

namespace dev
{
namespace solidity
{

class ControlFlowAnalyzer: private ASTConstVisitor
{
public:
	explicit ControlFlowAnalyzer(CFG const& _cfg, langutil::ErrorReporter& _errorReporter):
		m_cfg(_cfg), m_errorReporter(_errorReporter) {}

	bool analyze(ASTNode const& _astRoot);

	bool visit(FunctionDefinition const& _function) override;

private:
	/// Checks for uninitialized variable accesses in the control flow between @param _entry and @param _exit.
	void checkUninitializedAccess(CFGNode const* _entry, CFGNode const* _exit) const;
	/// Checks for unreachable code, i.e. code ending in @param _exit or @param _revert
	/// that can not be reached from @param _entry.
	void checkUnreachable(CFGNode const* _entry, CFGNode const* _exit, CFGNode const* _revert) const;

	CFG const& m_cfg;
	langutil::ErrorReporter& m_errorReporter;
};

}
}
