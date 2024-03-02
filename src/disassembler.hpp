#ifndef DISASSEMBLER_HPP
#define DISASSEMBLER_HPP

#include <cstdint>
#include <string>
#include <string_view>
#include <vector>
#include <optional>
#include <utility>
#include <format>
#include <sstream>
#include <iomanip>


namespace i8008_disasm
{
	class Instruction final
	{
	private:
		std::uint8_t opcode, length;
		std::string mnemonic;

	public:
		Instruction(std::uint8_t opcode, std::uint8_t length, std::string mnemonic);
		std::uint8_t GetOpcode() const;
		std::string_view GetMnemonic() const;
		std::uint8_t GetLength() const;

		operator std::uint8_t() const;
	};

	bool operator<(const Instruction& lhs, const Instruction& rhs);

	class InstructionDictionary final
	{
	private:
		std::vector<Instruction> instructions;

	public:
		InstructionDictionary();
		std::optional<std::reference_wrapper<const Instruction>> FindInstruction(std::uint8_t opcode) const;
	};

	template<typename Range>
	std::vector<std::string> Disassemble(const Range& binaryProgram)
	{
		static InstructionDictionary instDict;
		std::vector<std::string> disassembledProgram;

		for (auto i = std::begin(binaryProgram); i != std::end(binaryProgram);)
		{
			std::stringstream line;
			auto foundInstruction = instDict.FindInstruction(*i);
			if (foundInstruction)
			{
				const Instruction& inst = *foundInstruction;
				line << inst.GetMnemonic();
				
				switch (inst.GetLength())
				{
				case 2:
					{
						std::uint16_t data = *(i + 1);
						line << std::hex << data;
					}
					break;
				
				case 3:
					{
						std::uint8_t lower, upper;
						lower = *(i + 1);
						upper = *(i + 2);
						std::uint16_t address = (upper << 8) | lower;
						line << std::hex << address;
					}
					break;
				}
				i += inst.GetLength();
				
			}
			else
			{
				line << "DB " << std::hex << static_cast<std::uint16_t>(*i);
				++i;
			}
			disassembledProgram.push_back(line.str());
		}

		return disassembledProgram;
	}
}

#endif