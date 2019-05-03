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
 * Compiler that transforms Yul Objects to EVM bytecode objects.
 */

#pragma once

namespace yul
{
struct Object;
class AbstractAssembly;
struct EVMDialect;

class EVMObjectCompiler
{
public:
	static void compile(Object& _object, AbstractAssembly& _assembly, EVMDialect& _dialect, bool _evm15, bool _optimize);
private:
	EVMObjectCompiler(AbstractAssembly& _assembly, EVMDialect& _dialect, bool _evm15):
		m_assembly(_assembly), m_dialect(_dialect), m_evm15(_evm15)
	{}

	void run(Object& _object, bool _optimize);

	AbstractAssembly& m_assembly;
	EVMDialect& m_dialect;
	bool m_evm15 = false;
};

}
