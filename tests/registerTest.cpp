#include <gtest/gtest.h>
#include "reg.hpp"
#include <bitset>
#include <memory>

class RegisterTest : public ::testing::Test
{
	static constexpr size_t nBits = 8;
	public:
		static constexpr auto _resetValue = 0xFF;
		std::shared_ptr<Reg<nBits>>stackPointer;

		void SetUp() override
		{
			std::bitset<nBits> resetValue{_resetValue};
			stackPointer = std::make_shared<Reg<nBits>>(resetValue);
		}
};

TEST_F(RegisterTest, initalValueEqReset)
{
	auto batata = stackPointer->get();
	EXPECT_EQ(batata, _resetValue);
}
