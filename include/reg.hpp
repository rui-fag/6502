#pragma once
#include <bitset>
#include <cstddef>

template <std::size_t nBits>
class Reg
{
	private:
		std::bitset<nBits> sReg;
		std::bitset<nBits> resetValue;
	public:
		enum class statusFlags
		{
			carry = 1 << 0,
			zero = 1 << 1,
			interruptDisable = 1 << 2,
			decimal = 1 << 3,
			bFlag = 1 << 4,
			noEffect = 1 << 5,
			overflow = 1 << 6,
			negative = 1 << 7
		};

		Reg(std::bitset<nBits> resetValue_)
			: resetValue(resetValue_),
			sReg(resetValue_)
		{}
		void reset(void)
		{
			sReg = resetValue;
		}
		std::bitset<nBits> get(void) const
		{
			return sReg;
		}
		void updateValue(std::bitset<nBits> newValue)
		{
			sReg = newValue;
		}
		void setFlag(statusFlags flag)
			requires (nBits == 8)
		{
			sReg |= std::bitset<nBits>(static_cast<unsigned long>(flag));
		}
		void clearFlag(statusFlags flag)
			requires (nBits == 8)
		{
			sReg &= ~std::bitset<nBits>(static_cast<unsigned long>(flag));
		}
		void setFlagTo(statusFlags flag, bool value)
			requires (nBits == 8)
		{
			if(value)
			{
				setFlag(flag);
			}
			else
			{
				clearFlag(flag);
			}
		}
		bool isFlagSet(statusFlags flag) const
			requires (nBits == 8)
		{
			return (sReg & std::bitset<nBits>(static_cast<unsigned long>(flag))).any();
		}
};
