#pragma once

// g++ -g3 -ggdb -O0 -DDEBUG -I/usr/include/cryptopp Driver.cpp -o Driver.exe -lcryptopp -lpthread
// g++ -g -O2 -DNDEBUG -I/usr/include/cryptopp Driver.cpp -o Driver.exe -lcryptopp -lpthread
#include <cstdio>
#include <iostream>
#include <fstream>
#include "..\..\CryptoPP\osrng.h"
using CryptoPP::AutoSeededRandomPool;

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
