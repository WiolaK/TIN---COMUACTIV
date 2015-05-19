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

namespace comuactiv {
namespace proto {
namespace messages {

/**
 * RawMessage structure handles memory management for socket writing purposes
 */
struct RawMessage {
	RawMessage( int length ) :
		length(length) {
		std::cout << "Creating raw message" << std::endl;
		array = new char[length];
	};
	~RawMessage() {
		std::cout << "Deleting raw message" << std::endl;
		delete[] array;
	}

	const int length;
	char* array;


};

typedef std::shared_ptr<RawMessage> pRawMessage;

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
		memcpy(header_.prefix_, "COMUACTIV15", 12);
		header_.code_ = 0x00;
		header_.length_ = getLength();
		header_.id_ = counter_++;
	}

	Message(MsgCode code) {
		data_ = std::string("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Praesent ullamcorper ex augue, ut venenatis lorem auctor sit amet. Ut non magna quis libero suscipit scelerisque non in diam. Cras finibus mi lectus, id posuere lacus accumsan sit amet. Nulla luctus facilisis felis, vel faucibus nunc fringilla quis. Integer vehicula, mauris vitae tempus tempus, felis lacus fringilla sapien, ut convallis arcu tortor et mauris. Curabitur vehicula rhoncus sem. Quisque molestie massa ut dui lobortis, eget varius enim placerat. Donec urna lacus, mattis vitae lorem nec, scelerisque efficitur felis. Etiam porttitor ac sem quis feugiat. Etiam in odio leo. Vivamus eget enim finibus, rhoncus turpis id, posuere sapien. Suspendisse nec rhoncus est. Morbi ornare orci quis dignissim sodales. Vestibulum semper tortor eu magna porta porttitor. Nullam commodo odio et lorem placerat porttitor. Sed consectetur finibus quam, eu laoreet ligula. Mauris aliquet nibh vel tortor consectetur, vitae gravida leo tincidunt. Nunc bibendum mauris nisl, quis rhoncus urna fringilla in. Vestibulum suscipit nisl in efficitur commodo. Maecenas bibendum lacus felis, et rutrum enim laoreet non. Fusce laoreet et augue aliquet sodales. Donec at molestie felis, id accumsan eros. Morbi efficitur nisi felis, vel rhoncus tortor pellentesque et. Aliquam dignissim luctus hendrerit. Aenean eleifend diam arcu, ac scelerisque nunc ultrices sit amet. Duis vel commodo massa, a sodales sem. Vivamus dapibus condimentum lectus sed hendrerit. Curabitur posuere risus commodo orci accumsan efficitur. Sed suscipit, nisl eu malesuada dignissim, felis nisl euismod enim, quis efficitur turpis diam pellentesque eros. Mauris libero nisl, tincidunt quis congue id, interdum eget dui. Etiam facilisis, lacus ut ullamcorper imperdiet, magna eros accumsan sapien, id lobortis neque eros at est. Nulla tincidunt tortor quis ornare ultricies. Morbi posuere risus in dolor dictum, sed ultrices metus ullamcorper. Pellentesque interdum eu sapien ac accumsan. Aliquam sodales volutpat diam sed finibus. Suspendisse sit amet tellus maximus, lacinia elit non, accumsan lacus. Nam convallis feugiat condimentum. Nam at lorem tristique, accumsan ante quis, ornare purus. Nullam sed nisi nunc. Fusce at mattis nunc. In sagittis maximus nisl, a consectetur purus tristique rutrum. Mauris ultrices venenatis mollis. Donec tristique tellus ac lacinia mollis. Nam vitae sagittis nisl, et laoreet odio. Curabitur sem metus, commodo et lorem ac, sagittis sodales nulla. Nullam nec enim congue, feugiat nunc ut, facilisis diam. Mauris dapibus, orci a sodales volutpat, massa massa elementum nunc, non malesuada sapien nisi varius sem. Cras aliquam vel nisl nec interdum. Praesent vulputate nulla vitae tempus efficitur. Mauris nulla turpis, volutpat eget dui vitae, ultricies rutrum risus. Sed a ultrices dui.");
		memcpy(header_.prefix_, "COMUACTIV15", 12);
		header_.code_ = code;
		header_.length_ = getLength();
		header_.id_ = counter_++;;
	}

	virtual ~Message();

	pRawMessage getRaw() {
		std::cout << "Get raw message: " << std::endl;
		pRawMessage raw = pRawMessage(new RawMessage(getLength()));
		std::cout << "Raw length: " << raw->length;

		memcpy(raw->array, &header_, sizeof(header_));

		if(data_.size() > 0 ) {
			memcpy(raw->array+sizeof(header_), data_.c_str(), data_.size());
		}

		return raw;
	}

	void writeMessage( uint8_t* buffer ) {
		memcpy(buffer, &header_, sizeof(header_));
		memcpy(buffer+sizeof(header_), data_.c_str(), data_.size());
	}

	void readMessage( uint8_t* buffer ) {

		int codeOffset = sizeof(header_.prefix_);
		int lengthOffset = sizeof(header_.code_) + codeOffset;
		int idOffset = sizeof(header_.length_) + lengthOffset;
		int dataOffset = sizeof(header_.id_) + idOffset;

		memcpy(&header_.prefix_, buffer, sizeof(header_.prefix_));
		memcpy(&header_.code_, buffer+codeOffset, sizeof(header_.code_));
		std::cout << "Code:\t" << header_.code_ << std::endl;
		memcpy(&header_.length_, buffer+lengthOffset, sizeof(header_.length_));
		std::cout << "Length:\t" << header_.length_ << std::endl;
		memcpy(&header_.id_, buffer+idOffset, sizeof(header_.id_));
		std::cout << "Id:\t" << header_.id_<< std::endl;

		int dataLength = header_.length_- sizeof(header_);
		if( dataLength  > 0 ) {
			char* dataBuffer = new char[dataLength];
			memcpy(dataBuffer, buffer+dataOffset, dataLength);
			data_.assign(dataBuffer, dataLength);
		}
		std::cout << "Data:\t" << data_ << std::endl;

	}

	uint32_t getLength() const {
		std::cout<<"getLength" << std::endl;
		return sizeof(header_) + data_.size();
	}

	void setData(std::string data) {
		data_ = data;
		header_.length_ = getLength();
	}

protected:
	struct MessageHeader {
		uint8_t prefix_[12]; // Always COMUACTIV15
		uint32_t code_;
		uint32_t length_;
		uint32_t id_;
	} header_;
	std::string data_;

private:
	static uint32_t counter_;
};

typedef std::shared_ptr<Message> pMessage;

} /* namespace messages */
} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_MESSAGES_MESSAGE_HPP_ */
