#ifndef INSTRUCTIONS_HPP
#define INSTRUCTIONS_HPP

#include <cstdint>
#include <string>
#include <array>
#include <concepts>
#include <variant>

namespace i8080_disasm
{
    enum Register
    {
        A = 0b111,
        B = 0b000,
        C = 0b001,
        D = 0b010,
        E = 0b011,
        H = 0b100,
        L = 0b101,
        M = 0b110
    };

    const std::array<char, 8> RegisterNames
    {
        'B', 'C', 'D', 'E', 'H', 'L', 'M', 'A'
    };

    class Instruction
	{
	private:
		std::uint8_t opcode, length;
		std::string mnemonic;

	public:
		Instruction(std::uint8_t opcode, std::uint8_t length);
        Instruction(std::uint8_t opcode, std::uint8_t length, std::string mnemonic);
        virtual ~Instruction();

		std::uint8_t GetOpcode() const;
		virtual std::string GetMnemonic(std::optional<std::variant<std::uint8_t, std::pair<std::uint8_t, std::uint8_t>>> additionalParams) const;
		std::uint8_t GetLength() const;

        void SetMnemonic(std::string newMnemonic);

		operator std::uint8_t() const;
	};

    class MOV final : public Instruction
    {
    public:
        explicit MOV(std::uint8_t opcode);
    };

	bool operator<(const Instruction& lhs, const Instruction& rhs);

    std::integral auto GetDestination(std::integral auto opcode)
    {
        return (opcode & 0b111000) >> 3;
    }

    std::integral auto GetSource(std::integral auto opcode)
    {
        return opcode & 0b111;
    }
}

#endif //INSTRUCTIONS_HPP