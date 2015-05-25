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
namespace utils {

extern "C" {
void* execute(void* arg);
};

/**
 * \brief Interfejs dla klas zadaniowych działających w oddzielnych wątkach.
 */
class ThreadBase {
public:
	virtual ~ThreadBase() {}; // body for optimization issues
	/**
	 * Metoda wywoływana przez execute po uruchomieniu wątku.
	 */
	virtual void* run() = 0;

protected:
	/**
	 * Identyfikator wątku
	 */
	pthread_t tid;

	/**
	 * Metoda execute uruchamiająca klasę zadaniową.
	 */
	friend void* execute(void* arg);
};


extern "C" {
inline void* execute(void* arg) {
	return static_cast<ThreadBase*>(arg)->run();
};
};

} /* namespace utils */
} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_THREADBASE_HPP_ */
