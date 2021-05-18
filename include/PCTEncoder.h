/*
 * PCTEncoder.h
 *
 *  Created on: May 17, 2021
 *      Author: kris
 */

#ifndef PCTENCODER_H_
#define PCTENCODER_H_

#include <sstream>

class PCTEncoder: std::basic_stringstream {
public:
	PCTEncoder();
	virtual ~PCTEncoder();
	PCTEncoder(const PCTEncoder &other);
	PCTEncoder(PCTEncoder &&other);
	PCTEncoder& operator=(const PCTEncoder &other);
	PCTEncoder& operator=(PCTEncoder &&other);

	void encode(const char);
};

#endif /* PCTENCODER_H_ */
