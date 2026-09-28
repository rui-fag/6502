#include "opcodes.hpp"
#include <bitset>
#include <cstdint>
#include <iostream>

void Opcodes::ADC_IMMEDIATE(void) {}
void Opcodes::ADC_ZEROPAGE(void) {}
void Opcodes::ADC_ZEROPAGE_X(void) {}
void Opcodes::ADC_ABSOLUTE(void) {}
void Opcodes::ADC_ABSOLUTE_X(void) {}
void Opcodes::ADC_ABSOLUTE_Y(void) {}
void Opcodes::ADC_INDIRECT_X(void) {}
void Opcodes::ADC_INDIRECT_Y(void) {}
void Opcodes::AND_IMMEDIATE(void) {}
void Opcodes::AND_ZEROPAGE(void) {}
void Opcodes::AND_ZEROPAGE_X(void) {}
void Opcodes::AND_ABSOLUTE(void) {}
void Opcodes::AND_ABSOLUTE_X(void) {}
void Opcodes::AND_ABSOLUTE_Y(void) {}
void Opcodes::AND_INDIRECT_X(void) {}
void Opcodes::AND_INDIRECT_Y(void) {}
void Opcodes::ASL_ACCUMULATOR(void) {}
void Opcodes::ASL_ZEROPAGE(void) {}
void Opcodes::ASL_ZEROPAGE_X(void) {}
void Opcodes::ASL_ABSOLUTE(void) {}
void Opcodes::ASL_ABSOLUTE_X(void) {}
void Opcodes::BCC_RELATIVE(void) {}
void Opcodes::BCS_RELATIVE(void) {}
void Opcodes::BEQ_RELATIVE(void) {}
void Opcodes::BMI_RELATIVE(void) {}
void Opcodes::BNE_RELATIVE(void) {}
void Opcodes::BPL_RELATIVE(void) {}
void Opcodes::BVC_RELATIVE(void) {}
void Opcodes::BVS_RELATIVE(void) {}
void Opcodes::BIT_ZEROPAGE(void) {}
void Opcodes::BIT_ABSOLUTE(void) {}
void Opcodes::BRK_IMPLIED(void) { std::cout << "TODO: BRK_IMPLIED" << std::endl; }
void Opcodes::CLC_IMPLIED(void)
{
	status_.clearFlag(Reg<8>::statusFlags::carry);
}

void Opcodes::CLD_IMPLIED(void) {}
void Opcodes::CLI_IMPLIED(void)
{
	status_.clearFlag(Reg<8>::statusFlags::interruptDisable);
}
void Opcodes::CLV_IMPLIED(void) {}
void Opcodes::CMP_IMMEDIATE(void) {}
void Opcodes::CMP_ZEROPAGE(void) {}
void Opcodes::CMP_ZEROPAGE_X(void) {}
void Opcodes::CMP_ABSOLUTE(void) {}
void Opcodes::CMP_ABSOLUTE_X(void) {}
void Opcodes::CMP_ABSOLUTE_Y(void) {}
void Opcodes::CMP_INDIRECT_X(void) {}
void Opcodes::CMP_INDIRECT_Y(void) {}
void Opcodes::CPX_IMMEDIATE(void) {}
void Opcodes::CPX_ZEROPAGE(void) {}
void Opcodes::CPX_ABSOLUTE(void) {}
void Opcodes::CPY_IMMEDIATE(void) {}
void Opcodes::CPY_ZEROPAGE(void) {}
void Opcodes::CPY_ABSOLUTE(void) {}
void Opcodes::DEC_ZEROPAGE(void) {}
void Opcodes::DEC_ZEROPAGE_X(void) {}
void Opcodes::DEC_ABSOLUTE(void) {}
void Opcodes::DEC_ABSOLUTE_X(void) {}
void Opcodes::DEX_IMPLIED(void) {}
void Opcodes::DEY_IMPLIED(void) {}
void Opcodes::EOR_IMMEDIATE(void) {}
void Opcodes::EOR_ZEROPAGE(void) {}
void Opcodes::EOR_ZEROPAGE_X(void) {}
void Opcodes::EOR_ABSOLUTE(void) {}
void Opcodes::EOR_ABSOLUTE_X(void) {}
void Opcodes::EOR_ABSOLUTE_Y(void) {}
void Opcodes::EOR_INDIRECT_X(void) {}
void Opcodes::EOR_INDIRECT_Y(void) {}
void Opcodes::INC_ZEROPAGE(void) {}
void Opcodes::INC_ZEROPAGE_X(void) {}
void Opcodes::INC_ABSOLUTE(void) {}
void Opcodes::INC_ABSOLUTE_X(void) {}
void Opcodes::INX_IMPLIED(void) {}
void Opcodes::INY_IMPLIED(void) {}
void Opcodes::JMP_ABSOLUTE(void) {}
void Opcodes::JMP_INDIRECT(void) {}
void Opcodes::JSR_ABSOLUTE(void) {}
void Opcodes::LDA_IMMEDIATE(void)
{
	uint8_t operand = decodedValue_;
	acc_.updateValue(std::bitset<8>(operand));
	status_.setFlagTo(Reg<8>::statusFlags::zero, operand == 0);
	status_.setFlagTo(Reg<8>::statusFlags::negative, operand > 0x80);
}
void Opcodes::LDA_ZEROPAGE(void) {}
void Opcodes::LDA_ZEROPAGE_X(void) {}
void Opcodes::LDA_ABSOLUTE(void) {}
void Opcodes::LDA_ABSOLUTE_X(void) {}
void Opcodes::LDA_ABSOLUTE_Y(void) {}
void Opcodes::LDA_INDIRECT_X(void) {}
void Opcodes::LDA_INDIRECT_Y(void) {}
void Opcodes::LDX_IMMEDIATE(void) {}
void Opcodes::LDX_ZEROPAGE(void) {}
void Opcodes::LDX_ZEROPAGE_Y(void) {}
void Opcodes::LDX_ABSOLUTE(void) {}
void Opcodes::LDX_ABSOLUTE_Y(void) {}
void Opcodes::LDY_IMMEDIATE(void) {}
void Opcodes::LDY_ZEROPAGE(void) {}
void Opcodes::LDY_ZEROPAGE_X(void) {}
void Opcodes::LDY_ABSOLUTE(void) {}
void Opcodes::LDY_ABSOLUTE_X(void) {}
void Opcodes::LSR_ACCUMULATOR(void) {}
void Opcodes::LSR_ZEROPAGE(void) {}
void Opcodes::LSR_ZEROPAGE_X(void) {}
void Opcodes::LSR_ABSOLUTE(void) {}
void Opcodes::LSR_ABSOLUTE_X(void) {}
void Opcodes::NOP_IMPLIED(void) {}
void Opcodes::ORA_IMMEDIATE(void) {}
void Opcodes::ORA_ZEROPAGE(void) {}
void Opcodes::ORA_ZEROPAGE_X(void) {}
void Opcodes::ORA_ABSOLUTE(void) {}
void Opcodes::ORA_ABSOLUTE_X(void) {}
void Opcodes::ORA_ABSOLUTE_Y(void) {}
void Opcodes::ORA_INDIRECT_X(void) {}
void Opcodes::ORA_INDIRECT_Y(void) {}
void Opcodes::PHA_IMPLIED(void) {}
void Opcodes::PHP_IMPLIED(void) {}
void Opcodes::PLA_IMPLIED(void) {}
void Opcodes::PLP_IMPLIED(void) {}
void Opcodes::ROL_ACCUMULATOR(void) {}
void Opcodes::ROL_ZEROPAGE(void) {}
void Opcodes::ROL_ZEROPAGE_X(void) {}
void Opcodes::ROL_ABSOLUTE(void) {}
void Opcodes::ROL_ABSOLUTE_X(void) {}
void Opcodes::ROR_ACCUMULATOR(void) {}
void Opcodes::ROR_ZEROPAGE(void) {}
void Opcodes::ROR_ZEROPAGE_X(void) {}
void Opcodes::ROR_ABSOLUTE(void) {}
void Opcodes::ROR_ABSOLUTE_X(void) {}
void Opcodes::RTI_IMPLIED(void) {}
void Opcodes::RTS_IMPLIED(void) {}
void Opcodes::SBC_IMMEDIATE(void) {}
void Opcodes::SBC_ZEROPAGE(void) {}
void Opcodes::SBC_ZEROPAGE_X(void) {}
void Opcodes::SBC_ABSOLUTE(void) {}
void Opcodes::SBC_ABSOLUTE_X(void) {}
void Opcodes::SBC_ABSOLUTE_Y(void) {}
void Opcodes::SBC_INDIRECT_X(void) {}
void Opcodes::SBC_INDIRECT_Y(void) {}
void Opcodes::SEC_IMPLIED(void) {}
void Opcodes::SED_IMPLIED(void) {}
void Opcodes::SEI_IMPLIED(void)
{
	status_.setFlag(Reg<8>::statusFlags::interruptDisable);
}
void Opcodes::STA_ZEROPAGE(void) {}
void Opcodes::STA_ZEROPAGE_X(void) {}
void Opcodes::STA_ABSOLUTE(void) {}
void Opcodes::STA_ABSOLUTE_X(void) {}
void Opcodes::STA_ABSOLUTE_Y(void) {}
void Opcodes::STA_INDIRECT_X(void) {}
void Opcodes::STA_INDIRECT_Y(void) {}
void Opcodes::STX_ZEROPAGE(void) {}
void Opcodes::STX_ZEROPAGE_Y(void) {}
void Opcodes::STX_ABSOLUTE(void) {}
void Opcodes::STY_ZEROPAGE(void) {}
void Opcodes::STY_ZEROPAGE_X(void) {}
void Opcodes::STY_ABSOLUTE(void) {}
void Opcodes::TAX_IMPLIED(void) {}
void Opcodes::TAY_IMPLIED(void) {}
void Opcodes::TSX_IMPLIED(void) {}
void Opcodes::TXA_IMPLIED(void) {}
void Opcodes::TXS_IMPLIED(void) {}
void Opcodes::TYA_IMPLIED(void) {}
