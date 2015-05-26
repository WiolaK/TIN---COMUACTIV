/*
 * AssociationSetupMsg.hpp
 *
 *  Created on: 10 May 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_SRC_MESSAGES_ASSOCIATIONSETUPMSG_HPP_
#define PROTO_SRC_MESSAGES_ASSOCIATIONSETUPMSG_HPP_

#include <memory>
#include <string>

#include "Message.hpp"
#include "RawMessage.hpp"

namespace comuactiv {
namespace proto {
namespace messages {


/**
 * \brief klasa reprezentująca komunikat AssociationSetup protokołu COMUACTIV
 */
class AssociationSetupMsg: public Message {
public:
	const static MsgCode defaultCode = ASSOCIATION_SETUP;

	/**
	 * \brief konstruktor komunikatu AssociationSetup sparametryzowany numerami porŧów.
	 * Tworzy komunikat i ustawia jego parametry ( porty dla kanałów Medium i Low) na zadane wartości.
	 * \param mediumPort - łańcuch znaków zawierający numer portu na którym otwarto kanał Medium
	 * \param lowPort - łańcuch znaków zawierający numer portu na którym otwarto kanał Medium
	 */
	AssociationSetupMsg(std::string lowPort);

	AssociationSetupMsg(pRawMessage raw);

	virtual ~AssociationSetupMsg();

	static pMessage create(pRawMessage raw) {
		return std::shared_ptr<AssociationSetupMsg>( new AssociationSetupMsg(raw) );
	}

	const std::string& getLowPort() {
		return lowPort_;
	}

private:
	std::string lowPort_;
};

typedef std::shared_ptr<AssociationSetupMsg> pAssociationSetupMsg;

} /* namespace messages */
} /* namespace proto */
} /* namespace comuactiv */



#endif /* PROTO_SRC_MESSAGES_ASSOCIATIONSETUPMSG_HPP_ */
