#pragma once

// g++ -g3 -ggdb -O0 -DDEBUG -I/usr/include/cryptopp Driver.cpp -o Driver.exe -lcryptopp -lpthread
// g++ -g -O2 -DNDEBUG -I/usr/include/cryptopp Driver.cpp -o Driver.exe -lcryptopp -lpthread
#include <cstdio>
#include <iostream>
#include <fstream>
#include <iomanip>

#include <string>
using std::string;

#include <cstdlib>
using std::exit;

#include "..\..\CryptoPP\cryptlib.h"
using CryptoPP::Exception;

#include "..\..\CryptoPP\hex.h"
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;

#include "..\..\CryptoPP\filters.h"
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::StreamTransformationFilter;

#include "..\..\CryptoPP\modes.h"
using CryptoPP::CBC_Mode;

#include "..\..\CryptoPP\secblock.h"
using CryptoPP::SecByteBlock;
#include "..\..\CryptoPP\aes.h"

bool IntoAlphabet(char k, string Alphabet) {
	bool yes = false;
	if (Alphabet.size() == 0) {
		return false;
	}
	for (int i = 0; i < Alphabet.size(); i++) {
		if (k == Alphabet[i]) {
			return true;
		}
		else yes = true;
	}
	if (yes) return false;
}

void MakeAnalysis(string input, string FileName) {
	string Alphabet;
	char k;
	int count = 0;
	std::ofstream TextFile4(FileName);
	for (int i = 0; i < input.size(); i++) {
		k = input[i];
		if (IntoAlphabet(k, Alphabet) == false || Alphabet.size() == 0) {
			for (int j = i; j < input.size(); j++) {
				if (input[j] == k) {
					count++;
				}
			}
			Alphabet.push_back(k);
			TextFile4 << "0x" << std::hex << (0xFF & static_cast<byte>(k)) << ": " << std::fixed << std::setprecision(2) << (float)count/input.size()*100 << "%" << std::endl;
			count = 0;
		}
	}
	TextFile4.close();
}


