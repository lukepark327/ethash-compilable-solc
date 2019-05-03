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
 * @date 2014
 * Container of the (implicit and explicit) global objects.
 */

#pragma once

#include <libsolidity/ast/ASTForward.h>
#include <boost/noncopyable.hpp>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace dev
{
namespace solidity
{

class Type; // forward

/**
 * Container for all global objects which look like AST nodes, but are not part of the AST
 * that is currently being compiled.
 * @note must not be destroyed or moved during compilation as its objects can be referenced from
 * other objects.
 */
class GlobalContext: private boost::noncopyable
{
public:
	GlobalContext();
	void setCurrentContract(ContractDefinition const& _contract);
	MagicVariableDeclaration const* currentThis() const;
	MagicVariableDeclaration const* currentSuper() const;

	/// @returns a vector of all implicit global declarations excluding "this".
	std::vector<Declaration const*> declarations() const;

private:
	std::vector<std::shared_ptr<MagicVariableDeclaration const>> m_magicVariables;
	ContractDefinition const* m_currentContract = nullptr;
	std::map<ContractDefinition const*, std::shared_ptr<MagicVariableDeclaration const>> mutable m_thisPointer;
	std::map<ContractDefinition const*, std::shared_ptr<MagicVariableDeclaration const>> mutable m_superPointer;
};

}
}
