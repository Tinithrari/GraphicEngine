#include "Object3DTest.hpp"

int main(void)
{
    TestSuite *suite = Object3DTest::suite();
    TextUi::TestRunner runner;

    runner.addTest(suite);

    runner.run();

    return runner.result().testFailuresTotal();
}
