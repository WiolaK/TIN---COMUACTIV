/*
 * MessageFactory.hpp
 *
 *  Created on: 10 May 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_SRC_MESSAGEFACTORY_HPP_
#define PROTO_SRC_MESSAGEFACTORY_HPP_

#include <map>
#include <memory>

#include "Message.hpp"

namespace comuactiv {
namespace proto {
namespace messages {

/**
 * \brief Fabryka komunikatów protokołu COMUACTIV.
 * Fabryka umożliwia tworzenie zarejestrowanych w niej typów komunikatów protokołu COMUACTIV.
 * Klasa realizuje wzorzec singletonu, dostęp do funkcjonalności odbywa się przez statyczną instancję.
 */
class MessageFactory {
public:
	/**
	 * Zwraca referencję do instancji fabryki komunikatów protkołu COMUACTIV.
	 */
	static MessageFactory& getInstance();

	/**
	 * Typ reprezentujący wskaźnik na funkcję tworzącą komunikat.
	 */
	typedef std::function<pMessage(pRawMessage)> CreateFun;

	/**
	 * Rejestracja nowego typu w fabryce komunikatów.
	 * \param code - kod rejestrowanego w fabryce komunikatu będący jednocześnie jego identyfikatorem
	 * \param fun - wskaźnik na metodę tworzącą instancję konkretyzacji komunikatu
	 */
	bool registerMessage(Message::MsgCode code, CreateFun fun);

	/**
	 * Tworzenie wybranego komunikatu.
	 * \param code - identyfikator pod którym zarejestrowano dany typ w fabryce
	 * \param raw - surowa wiadomość, zwykle odczytana z gniazda
	 */
	pMessage create(Message::MsgCode code, pRawMessage raw);

private:
	// singleton pattern functions
	MessageFactory();
	virtual ~MessageFactory();
	MessageFactory(const MessageFactory&) = delete;
	MessageFactory& operator=(const MessageFactory&) = delete;
	// inicjalizacja
	void initialize();

	typedef	std::map<Message::MsgCode, CreateFun> Callbacks;

	Callbacks callbacks_;

	static bool isInitialized_;
};

} /* namespace messages */
} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_MESSAGEFACTORY_HPP_ */
