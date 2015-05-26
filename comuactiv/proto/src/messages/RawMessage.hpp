/*
 * RawMessage.hpp
 *
 *  Created on: 19 May 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_SRC_MESSAGES_RAWMESSAGE_HPP_
#define PROTO_SRC_MESSAGES_RAWMESSAGE_HPP_

#include <iostream>
#include <memory>

namespace comuactiv {
namespace proto {
namespace messages {

/**
 * \brief Zarządzanie buforem bajtów na wiadomość
 *
 * Struktura RawMessage zawiera bufor w formacie char* który może zostać wykorzystany przy obsłudze gniazd BSD.
 * Struktura odpowiada za automatyczny przydział i zwolnienie pamięci bufora.
 */
struct RawMessage {
	/**
	 * Konstruktor alokuje bufor o zadanym rozmiarze.
	 * \param length rozmiar alokowanego bufora
	 */
	RawMessage( int length ) :
		length(length) {
		//std::cout << "Creating raw message" << std::endl;
		array = new char[length];
	};

	/**
	 * W destruktorze zwalniana jest zaalokowana na bufor pamięć.
	 */
	~RawMessage() {
		//std::cout << "Deleting raw message" << std::endl;
		delete[] array;
	}

	/**
	 * Rozmiar bufora wiadomości
	 */
	const int length;
	/**
	 * Bufor wiadomości
	 */
	char* array;

};

/**
 * Sprytny wskaźnik (std::shared_ptr) na strukturę RawMessage
 */
typedef std::shared_ptr<RawMessage> pRawMessage;

} /* namespace messages */
} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_MESSAGES_RAWMESSAGE_HPP_ */
