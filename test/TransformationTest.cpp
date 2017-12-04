#include "TransformationTest.hpp"

int main(void)
{
    TestSuite *suite = TransformationTest::suite();
    TextUi::TestRunner runner;

    runner.addTest(suite);

    runner.run();

    return runner.result().testFailuresTotal();
}