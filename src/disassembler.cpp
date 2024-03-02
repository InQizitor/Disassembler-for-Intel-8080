#include <algorithm>
#include <ranges>
#include <functional>
#include <iterator>
#include "disassembler.hpp"

i8008_disasm::Instruction::Instruction(std::uint8_t opcode, std::uint8_t length, std::string mnemonic)
	:
	opcode(opcode),
	length(length),
	mnemonic(std::move(mnemonic))
{
}

std::uint8_t i8008_disasm::Instruction::GetOpcode() const
{
	return this->opcode;
}

std::string_view i8008_disasm::Instruction::GetMnemonic() const
{
	return this->mnemonic;
}

std::uint8_t i8008_disasm::Instruction::GetLength() const
{
	return this->length;
}

bool i8008_disasm::operator<(const Instruction & lhs, const Instruction & rhs)
{
	return lhs.GetOpcode() < rhs.GetOpcode();
}

i8008_disasm::Instruction::operator std::uint8_t() const
{
	return GetOpcode();
}

i8008_disasm::InstructionDictionary::InstructionDictionary()
	:
	//this implementation is not really efficient but it works
	instructions
	(
		{
			Instruction{0X87, 1, "ADD A"},
			Instruction{0X80, 1, "ADD B"},
			Instruction{0X81, 1, "ADD C"},
			Instruction{0X82, 1, "ADD D"},
			Instruction{0X83, 1, "ADD E"},
			Instruction{0X84, 1, "ADD H"},
			Instruction{0X85, 1, "ADD L"},
			Instruction{0X86, 1, "ADD M"},
			Instruction{0XC6, 2, "ADI "}, 
			Instruction{0X8F, 1, "ADC A"},
			Instruction{0X88, 1, "ADC B"},
			Instruction{0X89, 1, "ADC C"},
			Instruction{0X8A, 1, "ADC D"},
			Instruction{0X8B, 1, "ADC E"},
			Instruction{0X8C, 1, "ADC H"},
			Instruction{0X8D, 1, "ADC L"},
			Instruction{0X8E, 1, "ADC M"},
			Instruction{0XCE, 2, "ACI "}, 
			Instruction{0XA7, 1, "ANA A"},
			Instruction{0XA0, 1, "ANA B"},
			Instruction{0XA1, 1, "ANA C"},
			Instruction{0XA2, 1, "ANA D"},
			Instruction{0XA3, 1, "ANA E"},
			Instruction{0XA4, 1, "ANA H"},
			Instruction{0XA5, 1, "ANA L"},
			Instruction{0XA6, 1, "ANA M"},
			Instruction{0XE6, 2, "ANI "}, 
			Instruction{0XCD, 3, "CALL "}, 
			Instruction{0XCC, 3, "CZ "}, 
			Instruction{0XC4, 3, "CNZ "}, 
			Instruction{0XF4, 3, "CP "}, 
			Instruction{0XFC, 3, "CM "}, 
			Instruction{0XDC, 3, "CC "}, 
			Instruction{0XD4, 3, "CNC "}, 
			Instruction{0XEC, 3, "CPE "}, 
			Instruction{0XE4, 3, "CPO "}, 
			Instruction{0X2F, 1, "CMA"},
			Instruction{0X3F, 1, "CMC"},
			Instruction{0XBF, 1, "CMP A"},
			Instruction{0XB8, 1, "CMP B"},
			Instruction{0XB9, 1, "CMP C"},
			Instruction{0XBA, 1, "CMP D"},
			Instruction{0XBB, 1, "CMP E"},
			Instruction{0XBC, 1, "CMP H"},
			Instruction{0XBD, 1, "CMP L"},
			Instruction{0XBE, 1, "CMP M"},
			Instruction{0XFE, 2, "CPI "}, 
			Instruction{0X27, 1, "DAA"},
			Instruction{0X09, 1, "DAD B"},
			Instruction{0X19, 1, "DAD D"},
			Instruction{0X29, 1, "DAD H"},
			Instruction{0X39, 1, "DAD SP"},
			Instruction{0X3D, 1, "DCR A"},
			Instruction{0X05, 1, "DCR B"},
			Instruction{0X0D, 1, "DCR C"},
			Instruction{0X15, 1, "DCR D"},
			Instruction{0X1D, 1, "DCR E"},
			Instruction{0X25, 1, "DCR H"},
			Instruction{0X2D, 1, "DCR L"},
			Instruction{0X35, 1, "DCR M"},
			Instruction{0X0B, 1, "DCX B"},
			Instruction{0X1B, 1, "DCX D"},
			Instruction{0X2B, 1, "DCX H"},
			Instruction{0X3B, 1, "DCX SP"},
			Instruction{0XF3, 1, "DI"},
			Instruction{0XFB, 1, "EI"},
			Instruction{0X76, 1, "HLT"},
			Instruction{0XDB, 2, "IN "},
			Instruction{0X3C, 1, "INR A"},
			Instruction{0X04, 1, "INR B"},
			Instruction{0X0C, 1, "INR C"},
			Instruction{0X14, 1, "INR D"},
			Instruction{0X1C, 1, "INR E"},
			Instruction{0X24, 1, "INR H"},
			Instruction{0X2C, 1, "INR L"},
			Instruction{0X34, 1, "INR M"},
			Instruction{0X03, 1, "INX B"},
			Instruction{0X13, 1, "INX D"},
			Instruction{0X23, 1, "INX H"},
			Instruction{0X33, 1, "INX SP"},
			Instruction{0XC3, 3, "JMP "},
			Instruction{0XCA, 3, "JZ "}, 
			Instruction{0XC2, 3, "JNZ "}, 
			Instruction{0XF2, 3, "JP "}, 
			Instruction{0XFA, 3, "JM "}, 
			Instruction{0XDA, 3, "JC "}, 
			Instruction{0XD2, 3, "JNC "}, 
			Instruction{0XEA, 3, "JPE "},
			Instruction{0XE2, 3, "JPO "}, 
			Instruction{0X3A, 3, "LDA "}, 
			Instruction{0X0A, 1, "LDAX B"},
			Instruction{0X1A, 1, "LDAX D"}, 
			Instruction{0X2A, 3, "LHLD "}, 
			Instruction{0X01, 3, "LXI B, "},
			Instruction{0X21, 3, "LXI H, "},
			Instruction{0X31, 3, "LXI SP, "}, 
			Instruction{0X7F, 1, "MOV A, A"},
			Instruction{0X78, 1, "MOV A, B"},
			Instruction{0X79, 1, "MOV A, C"},
			Instruction{0X7A, 1, "MOV A, D"},
			Instruction{0X7B, 1, "MOV A, D"},
			Instruction{0X7C, 1, "MOV A, H"},
			Instruction{0X7D, 1, "MOV A, L"},
			Instruction{0X7E, 1, "MOV A, M"},
			Instruction{0X47, 1, "MOV B, A"},
			Instruction{0X40, 1, "MOV B, B"},
			Instruction{0X41, 1, "MOV B, C"},
			Instruction{0X42, 1, "MOV B, D"},
			Instruction{0X43, 1, "MOV B, E"},
			Instruction{0X44, 1, "MOV B, H"},
			Instruction{0X45, 1, "MOV B, L"},
			Instruction{0X46, 1, "MOV B, M"},
			Instruction{0X4F, 1, "MOV C, A"},
			Instruction{0X48, 1, "MOV C, D"},
			Instruction{0X49, 1, "MOV C, C"},
			Instruction{0X4A, 1, "MOV C, D"},
			Instruction{0X4B, 1, "MOV C, E"},
			Instruction{0X4C, 1, "MOV C, H"},
			Instruction{0X4D, 1, "MOV C, L"},
			Instruction{0X4E, 1, "MOV C, M"},
			Instruction{0X57, 1, "MOV D, A"},
			Instruction{0X50, 1, "MOV D, B"},
			Instruction{0X51, 1, "MOV D, C"},
			Instruction{0X52, 1, "MOV D, D"},
			Instruction{0X53, 1, "MOV D, E"},
			Instruction{0X54, 1, "MOV D, H"},
			Instruction{0X55, 1, "MOV D, L"},
			Instruction{0X56, 1, "MOV D, M"},
			Instruction{0X5F, 1, "MOV E, A"},
			Instruction{0X58, 1, "MOV E, B"},
			Instruction{0X59, 1, "MOV E, C"},
			Instruction{0X5A, 1, "MOV E, D"},
			Instruction{0X5B, 1, "MOV E, E"},
			Instruction{0X5C, 1, "MOV E, H"},
			Instruction{0X5D, 1, "MOV E, L"},
			Instruction{0X5E, 1, "MOV E, M"},
			Instruction{0X67, 1, "MOV H, A"},
			Instruction{0X60, 1, "MOV H, B"},
			Instruction{0X61, 1, "MOV H, C"},
			Instruction{0X62, 1, "MOV H, D"},
			Instruction{0X63, 1, "MOV H, E"},
			Instruction{0X64, 1, "MOV H, H"},
			Instruction{0X65, 1, "MOV H, L"},
			Instruction{0X66, 1, "MOV H, M"},
			Instruction{0X6F, 1, "MOV L, A"},
			Instruction{0X68, 1, "MOV L, B"},
			Instruction{0X69, 1, "MOV L, C"},
			Instruction{0X6A, 1, "MOV L, D"},
			Instruction{0X6B, 1, "MOV L, E"},
			Instruction{0X6C, 1, "MOV L, H"},
			Instruction{0X6D, 1, "MOV L, L"},
			Instruction{0X6E, 1, "MOV L, M"},
			Instruction{0X77, 1, "MOV M, A"},
			Instruction{0X70, 1, "MOV M, B"},
			Instruction{0X71, 1, "MOV M, C"},
			Instruction{0X72, 1, "MOV M, D"},
			Instruction{0X73, 1, "MOV M, E"},
			Instruction{0X74, 1, "MOV M, H"},
			Instruction{0X75, 1, "MOV M, L"},
			Instruction{0X3E, 2, "MVI A, "}, 
			Instruction{0X06, 2, "MVI B, "}, 
			Instruction{0X0E, 2, "MVI C, "}, 
			Instruction{0X16, 2, "MVI D, "},
			Instruction{0X1E, 2, "MVI E, "}, 
			Instruction{0X26, 2, "MVI H, "},
			Instruction{0X2E, 2, "MVI L, "},
			Instruction{0X36, 2, "MVI M, "},
			Instruction{0X00, 1, "NOP"},
			Instruction{0XB7, 1, "ORA A"},
			Instruction{0XB0, 1, "ORA B"},
			Instruction{0XB1, 1, "ORA C"},
			Instruction{0XB2, 1, "ORA D"},
			Instruction{0XB3, 1, "ORA E"},
			Instruction{0XB4, 1, "ORA H"},
			Instruction{0XB5, 1, "ORA L"},
			Instruction{0XB6, 1, "ORA M"},
			Instruction{0XF6, 2, "ORI "}, 
			Instruction{0XD3, 2, "OUT "}, 
			Instruction{0XE9, 1, "PCHL"},
			Instruction{0XC1, 1, "POP B"},
			Instruction{0XD1, 1, "POP D"},
			Instruction{0XE1, 1, "POP H"},
			Instruction{0XF1, 1, "POP PSW"},
			Instruction{0XC5, 1, "PUSH B"},
			Instruction{0XD5, 1, "PUSH D"},
			Instruction{0XE5, 1, "PUSH H"},
			Instruction{0XF5, 1, "PUSH PSW"},
			Instruction{0X17, 1, "RAL"},
			Instruction{0X1F, 1, "RAR"},
			Instruction{0X07, 1, "RLC"},
			Instruction{0X0F, 1, "RRC"},
			Instruction{0XC9, 1, "RET"},
			Instruction{0XC8, 1, "RZ"},
			Instruction{0XC0, 1, "RNZ"},
			Instruction{0XF0, 1, "RP"},
			Instruction{0XF8, 1, "RM"},
			Instruction{0XD8, 1, "RC"},
			Instruction{0XD0, 1, "RNC"},
			Instruction{0XE8, 1, "RPE"},
			Instruction{0XE0, 1, "RPO"},
			Instruction{0XC7, 1, "RST 0"},
			Instruction{0XCF, 1, "RST 1"},
			Instruction{0XD7, 1, "RST 2"},
			Instruction{0XDF, 1, "RST 3"},
			Instruction{0XE7, 1, "RST 4"},
			Instruction{0XEF, 1, "RST 5"},
			Instruction{0XF7, 1, "RST 6"},
			Instruction{0XFF, 1, "RST 7"},
			Instruction{0XF9, 1, "SPHL"},
			Instruction{0X22, 3, "SHLD "},
			Instruction{0X32, 3, "STA "}, 
			Instruction{0X02, 1, "STAX B"},
			Instruction{0X12, 1, "STAX D"},
			Instruction{0X37, 1, "STC"},
			Instruction{0X97, 1, "SUB A"},
			Instruction{0X90, 1, "SUB B"},
			Instruction{0X91, 1, "SUB C"},
			Instruction{0X92, 1, "SUB D"},
			Instruction{0X93, 1, "SUB E"},
			Instruction{0X94, 1, "SUB H"},
			Instruction{0X95, 1, "SUB L"},
			Instruction{0X96, 1, "SUB M"},
			Instruction{0XD6, 1, "SUI "}, 
			Instruction{0X9F, 1, "SBB A"},
			Instruction{0X98, 1, "SBB B"},
			Instruction{0X99, 1, "SBB C"},
			Instruction{0X9A, 1, "SBB D"},
			Instruction{0X9B, 1, "SBB E"},
			Instruction{0X9C, 1, "SBB H"},
			Instruction{0X9D, 1, "SBB L"},
			Instruction{0X9E, 1, "SBB M"},
			Instruction{0XDE, 1, "SBI "}, 
			Instruction{0XEB, 1, "XCHG"},
			Instruction{0XE3, 1, "XTHL"},
			Instruction{0XAF, 1, "XRA A"},
			Instruction{0XA8, 1, "XRA B"},
			Instruction{0XA9, 1, "XRA C"},
			Instruction{0XAA, 1, "XRA D"},
			Instruction{0XAB, 1, "XRA E"},
			Instruction{0XAC, 1, "XRA H"},
			Instruction{0XAD, 1, "XRA L"},
			Instruction{0XAE, 1, "XRA M"},
			Instruction{0XEE, 1, "XRI "}
		}
	)
{
	std::ranges::sort(instructions);
}

std::optional<std::reference_wrapper<const i8008_disasm::Instruction>> i8008_disasm::InstructionDictionary::FindInstruction(std::uint8_t opcode) const
{
	const auto found = std::ranges::lower_bound(instructions, opcode);
	if (found != std::end(instructions) and found->GetOpcode() == opcode)
	{
		return std::cref(*found);
	}
	else 
	{
		return std::nullopt;
	}
}