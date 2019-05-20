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
 * @author Alex Beregszaszi
 * @date 2016
 * Framework for executing LLL contracts and testing them via RPC.
 */

#pragma once

#include <functional>

#include "../ExecutionFramework.h"

#include <liblll/Compiler.h>

using namespace dev::test;

namespace dev
{
namespace lll
{

namespace test
{

class LLLExecutionFramework: public ExecutionFramework
{

public:
	LLLExecutionFramework();

	virtual bytes const& compileAndRunWithoutCheck(
		std::string const& _sourceCode,
		u256 const& _value = 0,
		std::string const& _contractName = "",
		bytes const& _arguments = bytes(),
		std::map<std::string, Address> const& _libraryAddresses = std::map<std::string, Address>()
	) override
	{
		BOOST_REQUIRE(_contractName.empty());
		BOOST_REQUIRE(_libraryAddresses.empty());

		std::vector<std::string> errors;
		bytes bytecode = lll::compileLLL(_sourceCode, dev::test::Options::get().evmVersion(), m_optimize, &errors);
		if (!errors.empty())
		{
			for (auto const& error: errors)
				std::cerr << error << std::endl;
			BOOST_ERROR("Compiling contract failed");
		}
		sendMessage(bytecode + _arguments, true, _value);
		return m_output;
	}
};

}
}
} // end namespaces
