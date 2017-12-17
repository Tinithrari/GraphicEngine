#include "FrustumTest.hpp"

int main(void)
{
    TestSuite *suite = FrustumTest::suite();
    TextUi::TestRunner runner;

    runner.addTest(suite);

    runner.run();

    return runner.result().testFailuresTotal();
}
