#include "QuaternionTest.hpp"

int main(void)
{
    TestSuite *suite = QuaternionTest::suite();
    TextUi::TestRunner runner;

    runner.addTest(suite);

    runner.run();

    return runner.result().testFailuresTotal();
}