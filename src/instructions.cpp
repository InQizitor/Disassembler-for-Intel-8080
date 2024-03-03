#include <format>
#include "instructions.hpp"

i8080_disasm::Instruction::Instruction(std::uint8_t opcode, std::uint8_t length)
	:
	opcode(opcode),
	length(length),
	mnemonic()
{
}

i8080_disasm::Instruction::Instruction(std::uint8_t opcode, std::uint8_t length, std::string mnemonic)
    :
    opcode(opcode),
    length(length),
    mnemonic(std::move(mnemonic))
{
}

i8080_disasm::Instruction::~Instruction()
{
}

std::uint8_t i8080_disasm::Instruction::GetOpcode() const
{
	return this->opcode;
}

std::string i8080_disasm::Instruction::GetMnemonic(std::optional<std::variant<std::uint8_t, std::pair<std::uint8_t, std::uint8_t>>> additionalParams) const
{
	return this->mnemonic;
}

std::uint8_t i8080_disasm::Instruction::GetLength() const
{
	return this->length;
}

void i8080_disasm::Instruction::SetMnemonic(std::string newMnemonic)
{
    this->mnemonic = std::move(newMnemonic);
}

bool i8080_disasm::operator<(const Instruction & lhs, const Instruction & rhs)
{
	return lhs.GetOpcode() < rhs.GetOpcode();
}

i8080_disasm::Instruction::operator std::uint8_t() const
{
	return GetOpcode();
}

i8080_disasm::MOV::MOV(std::uint8_t opcode)
    :
    Instruction(opcode, 1)
{
    const auto destination = RegisterNames.at(GetDestination(opcode));
    const auto source = RegisterNames.at(GetSource(opcode));
    std::string mnemonic = std::format("MOV {}, {}", destination, source);
    SetMnemonic(std::move(mnemonic));
}