#include "CQTest.h"

TEST(Sample, "TestUe")
{
	ASSERT_THAT(IsTrue(true));
};

TEST_CLASS(SampleClassTest, "TestUe")
{
	bool bSetupCalled = false;

	BEFORE_EACH()
	{
		bSetupCalled = true;
	}

	AFTER_EACH()
	{
		ASSERT_THAT(IsTrue(bSetupCalled));
	}

	TEST_METHOD(TestCallsSetup)
	{
		ASSERT_THAT(IsTrue(bSetupCalled));
	}
};
