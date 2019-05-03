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
 * Optimisation stage that replaces variables by their most recently assigned expressions.
 */

#pragma once

#include <libyul/optimiser/DataFlowAnalyzer.h>

namespace yul
{

/**
 * Optimisation stage that replaces variables by their most recently assigned expressions,
 * but only if the expression is movable and one of the following holds:
 *  - the variable is referenced exactly once
 *  - the value is extremely cheap ("cost" of zero like ``caller()``)
 *  - the variable is referenced at most 5 times and the value is rather cheap
 *    ("cost" of at most 1 like a constant up to 0xff)
 *
 * Prerequisite: Disambiguator, ForLoopInitRewriter.
 */
class Rematerialiser: public DataFlowAnalyzer
{
public:
	static void run(
		Dialect const& _dialect,
		Block& _ast,
		std::set<YulString> _varsToAlwaysRematerialize = {}
	);
	static void run(
		Dialect const& _dialect,
		FunctionDefinition& _function,
		std::set<YulString> _varsToAlwaysRematerialize = {}
	);

protected:
	Rematerialiser(
		Dialect const& _dialect,
		Block& _ast,
		std::set<YulString> _varsToAlwaysRematerialize = {}
	);
	Rematerialiser(
		Dialect const& _dialect,
		FunctionDefinition& _function,
		std::set<YulString> _varsToAlwaysRematerialize = {}
	);

	using ASTModifier::visit;
	void visit(Expression& _e) override;

	std::map<YulString, size_t> m_referenceCounts;
	std::set<YulString> m_varsToAlwaysRematerialize;
};

}
