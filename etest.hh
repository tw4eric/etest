#ifndef _ETEST_HH_
#define _ETEST_HH_
#define _ETEST_INTERNAL_REQUIRED_
#include "etest-internal.hh"
#undef _ETEST_INTERNAL_REQUIRED_

int RUN_ALL_TESTS();

TestNode *addTest(TestFactoryBase *f);

#define TEST_NAME(group, scenario) group##_##scenario##_test
#define TEST(group, scenario) \
    class TEST_NAME(group, scenario) : public TestCase {\
        private: \
                static const char *group, *scenario; \
        public: \
                TEST_NAME(group, scenario)() {}; \
        virtual ~TEST_NAME(group, scenario)() {}; \
        virtual void body(); \
        static TestNode *testNode_; \
        virtual const char *getGroup() { return group; } \
        virtual const char *getScenario() { return scenario; } \
    }; \
const char *TEST_NAME(group, scenario)::group = #group; \
const char *TEST_NAME(group, scenario)::scenario = #scenario; \
TestNode *TEST_NAME(group, scenario)::testNode_ = addTest(new TestFactory<TEST_NAME(group, scenario)>()); \
void TEST_NAME(group, scenario)::body()

# define EXPECT_TRUE(boolExpression) if(!(boolExpression)) updateFailure(__FILE__, __LINE__)
# define ASSERT_TRUE(boolExpression) if(!(boolExpression)) updateFailure(__FILE__, __LINE__, true)

#endif // _ETEST_HH_
