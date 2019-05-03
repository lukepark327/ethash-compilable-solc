# Magic Keywords
```class MagicType``` in line #1327 in ```libsolidity/ast/Types.h``` is special type for magic variables;
* block, msg, tx, type(…)

## Compiler
It has switch-case syntax in line #1347 in ```libsolidity/codegen/ExpressionCompiler.cpp```.

But what is ```codegen```? Is it a library for creating test codes? 🤔...

# Anyway,
we need to modify these files;

## OPCODEs
```libevmasm/Instruction.h```   
```libevmasm/SemanticInformation.cpp```   
```libevmasm/Instruction.cpp```   

## Keywords
```libsolidity/ast/Types.cpp```   
```libsolidity/codegen/ExpressionCompiler.cpp``` which converts keyword -> OPCODE.   

# If
you change the above files, you have to change the following codes for build;
```test/tools/yulInterpreter/EVMInstructionInterpreter.cpp```   
```test/tools/yulInterpreter/Interpreter.h```'s ```struct InterpreterState```   

# Let's Build!
```bash
$ ./scripts/build.sh
```
