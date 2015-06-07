/*
 * BlockingQueue.cpp
 *
 *  Created on: 7 Jun 2015
 *      Author: Jan Kumor
 */

#include "BlockingQueue.hpp"

#include <mutex>
#include <string>

namespace comuactiv {
namespace proto {
class Command;
} /* namespace proto */
} /* namespace comuactiv */

namespace comuactiv {
namespace proto {

BlockingQueue::BlockingQueue() {
}

pCommand BlockingQueue::pop() {
	std::unique_lock<std::mutex> lock(mtx_);
	while(commands_.empty()) {
		wait_.wait(lock);
	}
	pCommand result;
	result = commands_.front();
	commands_.pop();
	return result;

}

void BlockingQueue::push(pCommand command) {
	{
		std::lock_guard<std::mutex> lock(mtx_);
		commands_.push(command);
	}
	wait_.notify_all();
}

} /* namespace proto */
} /* namespace comuactiv */
