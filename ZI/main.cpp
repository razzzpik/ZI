#define _CRT_SECURE_NO_WARNINGS
#include "Main_Header.h"

int main(int argc, char* argv[]) {

	//HMODULE DLL = LoadLibrary(_T("cryptopp.dll"));
	//
	// Key and IV setup
	//AES encryption uses a secret key of a variable length (128-bit, 196-bit or 256-
	//bit). This key is secretly exchanged between two parties before communication
	//begins. DEFAULT_KEYLENGTH= 16 bytes

	std::string key = "current key";
	std::string iv = "aaaaaaaaaaaaaaaa";
	string Text;
	string InputText;
	std::string CipherText;
	std::string DecryptedText;
	string encoded;
	string MainAnalysisFile = "MainAnalysisFile.txt";
	string SecondAnalysisFile = "SecondAnalysisFile.txt";

	std::ifstream TextFile1("Input.txt");
	while (!TextFile1.eof())                        
	{
		TextFile1 >> Text;                        
		InputText += Text + " ";
	}                                           
	TextFile1.close();  

	std::cout << InputText << std::endl;

	InputText.pop_back();
	MakeAnalysis(InputText, MainAnalysisFile);

	CryptoPP::AES::Encryption aesEncryption((byte *)key.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, (byte *)iv.c_str());

	CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink(CipherText));
	stfEncryptor.Put(reinterpret_cast<const unsigned char*>(InputText.c_str()), InputText.length() + 1);
	stfEncryptor.MessageEnd();
		
	std::cout << "cipher text plain: " << CipherText << std::endl;
	std::cout << std::endl;

	std::ofstream TextFile2("Encrypted.txt");            
	TextFile2 << CipherText;                        
	TextFile2.close();    

	MakeAnalysis(CipherText, SecondAnalysisFile);

	encoded.clear();
	StringSource(CipherText, true,
		new HexEncoder(
			new StringSink(encoded)
			)
		);
	char *name2;
	name2 = (char*)malloc(encoded.length() + 1);
	//											 
	//											
	strcpy(name2, encoded.c_str());

	const char* hex_str = name2;

	std::string result_string;
	unsigned int ch;
	for (; std::sscanf(hex_str, "%2x", &ch) == 1; hex_str += 2)
		result_string += ch;

	delete name2;

	CryptoPP::AES::Decryption aesDecryption((byte *)key.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, (byte *)iv.c_str());

	CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink(DecryptedText));
	stfDecryptor.Put(reinterpret_cast<const unsigned char*>(result_string.c_str()), result_string.size());
	stfDecryptor.MessageEnd();
	
	std::cout << DecryptedText << std::endl;
	
	if (!DecryptedText.empty()) {
		DecryptedText.erase(DecryptedText.length() - 2, 2);
	}

	std::ofstream TextFile3("Decrypted.txt");
	TextFile3 << DecryptedText;
	TextFile3.close();

	system("pause");

	return 0;
}