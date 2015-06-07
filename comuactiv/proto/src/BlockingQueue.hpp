/*
 * BlockingQueue.hpp
 *
 *  Created on: 7 Jun 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_SRC_BLOCKINGQUEUE_HPP_
#define PROTO_SRC_BLOCKINGQUEUE_HPP_

#include <mutex>
#include <condition_variable>
#include <queue>

#include "../include/comuactiv/Command.hpp"

namespace comuactiv {
namespace proto {

class BlockingQueue {
private:
	std::queue<pCommand> commands_;
	std::mutex mtx_;
	std::condition_variable wait_;

public:
	/**
	 *
	 */
	BlockingQueue();
	BlockingQueue(const BlockingQueue&) = delete;
	BlockingQueue& operator=(const BlockingQueue&) {
		return *this;
	}
	/**
	 * Pop an element from Queue, if queue is empty it blocks till someone push something into
	 */
	pCommand pop();
	/**
	 * Add an element to Queue
	 * \param message element to add
	 */
	void push(pCommand command);
};

} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_BLOCKINGQUEUE_HPP_ */
