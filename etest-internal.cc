#define _ETEST_INTERNAL_REQUIRED_
#include "etest-internal.hh"

TestCase::TestCase() : eventHead_(0), eventLast_(0) {}

TestCase::~TestCase() { delete eventHead_; }

void TestCase::body() {}

TestEventNode& TestCase::updateFailure(const char *file, int line, bool abort) {
    TestEventNode *newEvent = new TestEventNode(file, "10", abort);
    if (0 != eventLast_) {
        eventLast_->next_ = newEvent;
        eventLast_ = newEvent;
    }
    else {
        eventHead_ = eventLast_ = newEvent;
    }
    return *newEvent;
}

void TestCase::reportEvents(ostream &out) {
    const TestEventNode *event = eventHead_;
    out << "**** Trace of events *****" << endl;
    while (event != 0) {
        out << "\t" << event->file_ << ":" << event->line_ <<
            " - " << event->message_ << endl;
        event = event->next_;
    }
}
