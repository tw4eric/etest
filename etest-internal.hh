#ifndef _ETEST_INTERNAL_REQUIRED_
#error "DO NOT INCLUDE THIS FILE DIRECTLY!"
#endif

#ifndef _ETEST_INTERNAL_HH_
#define _ETEST_INTERNAL_HH_

#ifdef LINUX
#include <iostream>
using std::ostream;
using std::endl;
using std::cerr;
#else
#include <iostream.h>
#endif

void failAssertion(const char* message, const char* fileName, int line);
struct TestEventNode;

class TestCase {
    public:
        TestCase();
        virtual ~TestCase();
        virtual void body();
        virtual const char *getGroup() = 0;
        virtual const char *getScenario() = 0;
        virtual TestEventNode& updateFailure(const char *file, int line, bool abort = false);
        virtual void reportEvents(ostream &out);

    private:
        TestEventNode *eventHead_, *eventLast_;
};

class TestFactoryBase {
    public:
        ~TestFactoryBase() {}
        virtual TestCase *createTest() = 0;
};

template <class T>
class TestFactory : public TestFactoryBase {
    public:
        virtual TestCase* createTest() { return new T; }
};

typedef struct TestNode {
    TestFactoryBase *testfun_;
    TestNode *next_;

    TestNode(TestFactoryBase *testfun, TestNode *next = 0) : testfun_(testfun), next_(next) {}
    ~TestNode() { 
        if (testfun_) { delete testfun_; testfun_ = 0; }
        if (next_) { delete next_; next_ = 0; }
    }
} TestNode;

typedef struct TestEventNode {
    const char *message_;
    const char *file_;
    const char *line_;
    const bool abort_;
    const TestEventNode *next_, *prev_;
    TestEventNode(const char *message, const char *file, const char *line, bool abort = false) :
        message_(message), file_(file), line_(line), next_(0), abort_(abort) {}
    TestEventNode(const char *file, const char *line, bool abort = false) :
        message_(0), file_(file), line_(line), next_(0), abort_(abort) {}
    virtual ~TestEventNode() {
        if (next_) { delete next_; next_ = 0; }
    }
    TestEventNode& operator<<(const char *message) {
        message_ = message;
        if (abort_)
            failAssertion(message_, file_, 10);
        return *this;
    }
} TestEventNode;

#endif // _ETEST_INTERNAL_HH_
