/*
 * CharacterUtils.h
 *
 *  Created on: May 17, 2021
 *      Author: kris
 */

#ifndef CHARACTERUTILS_H_
#define CHARACTERUTILS_H_

#include <iostream>

class CharacterUtils {
	static const char allowedMIN = 0x21;
	static const char allowedMAX = 0x7e;
	static const char disallowed[] = { 0x22, 0x3c, 0x3e, 0x5c, 0x5e, 0x60, 0x7b,
			0x7c, 0x7d }; // " < > \ ^ ` { | }

public:
	CharacterUtils();
	virtual ~CharacterUtils();
	CharacterUtils(const CharacterUtils &other);
	CharacterUtils(CharacterUtils &&other);
	CharacterUtils& operator=(const CharacterUtils &other);
	CharacterUtils& operator=(CharacterUtils &&other);

};

#endif /* CHARACTERUTILS_H_ */
