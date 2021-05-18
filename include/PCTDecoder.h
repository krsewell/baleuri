/*
 * PCTDecoder.h
 *
 *  Created on: May 17, 2021
 *      Author: kris
 */

#ifndef PCTDECODER_H_
#define PCTDECODER_H_

#include <sstream>

class PCTDecoder: public std::basic_stringstream {
public:
	PCTDecoder();
	virtual ~PCTDecoder();
	PCTDecoder(const PCTDecoder &other);
	PCTDecoder(PCTDecoder &&other);
	PCTDecoder& operator=(const PCTDecoder &other);
	PCTDecoder& operator=(PCTDecoder &&other);

	void decode(const std::string&);
	friend ostream& operator<<(ostream &output, PCTDecoder &decoder);
	friend istream& operator>>(istream &input, PCTDecoder &decoder);
};

#endif /* PCTDECODER_H_ */
