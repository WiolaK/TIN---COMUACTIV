/*
 * UserInterface.hpp
 *
 *  Created on: 7 Jun 2015
 *      Author: Jan Kumor
 */

#ifndef CE_APP_SRC_USERINTERFACE_HPP_
#define CE_APP_SRC_USERINTERFACE_HPP_

#include <pthread.h>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <mutex>
#include <vector>

#include "../../proto/include/comuactiv/Command.hpp"
#include "../../proto/include/comuactiv/ComuactivServerSlot.hpp"
#include "../../proto/include/comuactiv/FlowTable.hpp"
#include "../../proto/include/comuactiv/SendFlowTableCommand.hpp"
#include "../../proto/src/utils/Printer.hpp"
#include "../../proto/src/utils/ThreadBase.hpp"

namespace std {
class mutex;
} /* namespace std */

namespace comuactiv {
namespace ce_app {

class UserInterface : public proto::utils::ThreadBase {
public:
	UserInterface(std::vector<proto::pComuactivServerSlot>& slots , std::mutex& slotsMtx, proto::flowtable::FlowTable& table) : slots_(slots), mtx_(slotsMtx), table_(table) {
		pthread_create(&tid, nullptr, &proto::utils::execute, this);
	};
	virtual ~UserInterface();

	virtual void* run() {
		proto::utils::Printer printer("UserInterface");
		while(true) {
			printer("\n\tf - send flow table update\n\tl - load flow table from file\n\te - exit");
			char c = std::cin.get();
			std::cin.get();
			switch(c) {
			case 'l':
				table_.loadTable("../flowtable.xml");
				table_.checkTable();
				break;

			case 'f':
				for( proto::pComuactivServerSlot slot : slots_) {
					std::lock_guard<std::mutex> lock(mtx_);
					slot->insertCommand(proto::pCommand(new proto::SendFlowTableCommand(table_.toString())));
				}
				break;

			case 'e':
					exit(0);
				break;
			}
		}

		return nullptr;
	}

private:
	std::vector<proto::pComuactivServerSlot>& slots_;
	std::mutex& mtx_;
	proto::flowtable::FlowTable& table_;
};

} /* namespace ce_app */
} /* namespace comuactiv */

#endif /* CE_APP_SRC_USERINTERFACE_HPP_ */
