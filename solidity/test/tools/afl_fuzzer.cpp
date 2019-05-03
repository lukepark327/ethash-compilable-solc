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
 * Executable for use with AFL <http://lcamtuf.coredump.cx/afl>.
 */

#include <test/tools/fuzzer_common.h>

#include <libdevcore/CommonIO.h>

#include <boost/program_options.hpp>

#include <string>
#include <iostream>

using namespace std;
using namespace dev;

namespace po = boost::program_options;

int main(int argc, char** argv)
{
	po::options_description options(
		R"(solfuzzer, fuzz-testing binary for use with AFL.
Usage: solfuzzer [Options] < input
Reads a single source from stdin, compiles it and signals a failure for internal errors.

Allowed options)",
		po::options_description::m_default_line_length,
		po::options_description::m_default_line_length - 23);
	options.add_options()
		("help", "Show this help screen.")
		("quiet", "Only output errors.")
		(
			"standard-json",
			"Test via the standard-json interface, i.e. "
			"input is expected to be JSON-encoded instead of "
			"plain source file."
		)
		(
			"const-opt",
			"Run the constant optimizer instead of compiling. "
			"Expects a binary string of up to 32 bytes on stdin."
		)
		(
			"input-file",
			po::value<string>(),
			"input file"
		)(
			"input-files",
			po::value<std::vector<string>>()->multitoken(),
			"input files"
		)
		(
			"without-optimizer",
			"Run without optimizations. Cannot be used together with standard-json."
		);

	// All positional options should be interpreted as input files
	po::positional_options_description filesPositions;
	filesPositions.add("input-file", 1);
	bool quiet = false;

	po::variables_map arguments;
	try
	{
		po::command_line_parser cmdLineParser(argc, argv);
		cmdLineParser.options(options).positional(filesPositions);
		po::store(cmdLineParser.run(), arguments);
	}
	catch (po::error const& _exception)
	{
		cerr << _exception.what() << endl;
		return 1;
	}

	if (arguments.count("quiet"))
		quiet = true;

	if (arguments.count("help"))
	{
		cout << options;
		return 0;
	}

	vector<string> inputs;
	if (arguments.count("input-file"))
		inputs.push_back(arguments["input-file"].as<string>());
	else if (arguments.count("input-files"))
		inputs = arguments["input-files"].as<vector<string>>();
	else
		inputs.push_back("");

	bool optimize = !arguments.count("without-optimizer");
	int retResult = 0;

	for (string const& inputFile: inputs)
	{
		string input;
		if (inputFile.size() == 0)
			input = readStandardInput();
		else
			input = readFileAsString(inputFile);

		try
		{
			if (arguments.count("const-opt"))
				FuzzerUtil::testConstantOptimizer(input, quiet);
			else if (arguments.count("standard-json"))
				FuzzerUtil::testStandardCompiler(input, quiet);
			else
				FuzzerUtil::testCompiler(input, optimize, quiet);
		}
		catch (...)
		{
			retResult = 1;

			if (inputFile.size() == 0)
				throw;

			cerr << "Fuzzer "
				<< (optimize ? "" : "(without optimizer) ")
				<< "failed on "
				<< inputFile;
		}
	}

	return retResult;
}
