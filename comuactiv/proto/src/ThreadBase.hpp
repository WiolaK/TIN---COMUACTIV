/*
 * ThreadBase.hpp
 *
 *  Created on: 5 May 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_THREADBASE_HPP_
#define PROTO_THREADBASE_HPP_

#include <pthread.h>

namespace comuactiv {
namespace proto {

class ThreadBase {
public:
	virtual ~ThreadBase() {}; // body for optimization issues
    virtual void* run() = 0;

protected:
    pthread_t tid;

    friend void* execute(void* arg) {
        return static_cast<ThreadBase*>(arg)->run();
    };
};

void* execute(void* arg);

} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_THREADBASE_HPP_ */
