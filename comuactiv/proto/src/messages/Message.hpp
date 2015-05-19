/*
 * Message.hpp
 *
 *  Created on: 4 May 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_SRC_MESSAGES_MESSAGE_HPP_
#define PROTO_SRC_MESSAGES_MESSAGE_HPP_

#include <cstdint>
#include <cstring>
#include <iostream>
#include <memory>
#include <string>

#include "RawMessage.hpp"

namespace comuactiv {
namespace proto {
namespace messages {

/**
 * Base class for COMUACTIVE protocol messages
 */
class Message {
public:
	enum MsgCode : uint32_t {
		ASSOCIATION_SETUP = 0x00,
				ASSOCIATION_SETUP_RESPONSE,
				ASSOCIATION_TEARDOWN,
				CONFIGURATION,
				CONFIGURATION_RESPONSE,
				QUERY,
				QUERY_RESPONSE,
				FLOW_TABLE_ENTRY_UPDATE,
				EVENT_NOTIFICATION,
				PACKET_REDIRECT,
				HEARTBEAT
	};

	Message() {
		memcpy(header_.prefix_, "COMUACTIV15\0", 12);
		header_.code_ = 0x00;
		header_.length_ = getLength();
		header_.id_ = counter_++;
	}



	virtual ~Message();

	/**
	 * Tworzy "surową" wiadomość protkołu COMUACTIV w postaci tablicy bajtów.
	 * \return sprytny wskaźnik na utworzoną strukturę RawMessage
	 */
	pRawMessage getRaw();

	/**
	 * Oblicza i zwraca długość wiadomości w bajtach.
	 * \return dłgość wiadomości w bajtach
	 */
	uint32_t getLength() const {
		if(!validLength_) {
			header_.length_ = sizeof(header_) + data_.size() + 1; //+1 is for ending NUL character
			validLength_ = true;
		}
		return header_.length_;
	}

	/**
	 * Pozwala na wypełnienie pola danych wiadomości dowolnym łańcuchem znaków.
	 * \param data - łańcuch znaków, który ma zostać zapisany w polu danych wiadomości
	 */
	void setData(std::string data) {
		data_ = data;
		validLength_ = false;
	}

protected:
	Message(MsgCode code);

	/**
	 * Nagłówek wiadomości protokołu COMUACTIV.
	 */
	struct MessageHeader {
		/**
		 * COMUACTIV message prefix, should be set to COMUACTIV15\0
		 */
		uint8_t prefix_[12]; // Always set to "COMUACTIV15\0"
		uint32_t code_;
		mutable uint32_t length_;
		uint32_t id_;
	} header_;
	std::string data_;

	mutable	bool validLength_;

private:
	static uint32_t counter_;
};

typedef std::shared_ptr<Message> pMessage;

} /* namespace messages */
} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_MESSAGES_MESSAGE_HPP_ */
