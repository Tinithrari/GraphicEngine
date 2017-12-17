#include "PlaneTest.hpp"

int main(void)
{
    TestSuite *suite = PlaneTest::suite();
    TextUi::TestRunner runner;

    runner.addTest(suite);

    runner.run();

    return runner.result().testFailuresTotal();
}