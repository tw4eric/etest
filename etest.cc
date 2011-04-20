#ifndef DEPEND
#ifdef LINUX
#include <cstdlib>
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#else
#include <stdlib.h>
#include <iostream.h>
#endif
#endif
#include "etest.hh"

bool runTest(TestCase *f);
void reportTests();
void cleanTests();

int successCount = 0;
int failureCount = 0;

static TestNode *headTestNode = 0;

TestNode *addTest(TestFactoryBase *f) {
    TestNode *newCase = new TestNode(f, headTestNode);
    headTestNode = newCase;
    return headTestNode;
}

void reportTests() {
    cout << "Tests ended. Total count = " << (successCount + failureCount) << endl;
    cout << "SUCCESSFUL Tests         = " << (successCount) << endl;
    cout << "FAILED Tests             = " << (failureCount) << endl;
}

bool runTest(TestCase *f) {
    cout << "Running test: " << f->getGroup() << ":" << f->getScenario() << endl;
    try {
        f->body();
        return true;
    }
    catch (...) {
        cerr << "FAILED! " << f->getGroup() << ":" << f->getScenario() << endl;
        return false;
    }
}

void cleanTests() {
    delete headTestNode;
    headTestNode = 0;
}

int RUN_ALL_TESTS() {
    TestNode *h = headTestNode;
    while (h) {
        TestCase *testCase = h->testfun_->createTest();
        if (runTest(testCase)) {
            successCount++;
        }
        else
        {
            testCase->reportEvents(cout);
            failureCount++;
        }
        h = h->next_;
    }
    reportTests();
    cleanTests();
    if (failureCount > 0) {
        return 1;
    }
    return 0;
}
