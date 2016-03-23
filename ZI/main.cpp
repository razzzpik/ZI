#define _CRT_SECURE_NO_WARNINGS
#include "Main_Header.h"

int main(int argc, char* argv[]) {

	//HMODULE DLL = LoadLibrary(_T("cryptopp.dll"));
	//
	// Key and IV setup
	//AES encryption uses a secret key of a variable length (128-bit, 196-bit or 256-
	//bit). This key is secretly exchanged between two parties before communication
	//begins. DEFAULT_KEYLENGTH= 16 bytes
	std::string key = "dick";
	std::string iv = "aaaaaaaaaaaaaaaa";
	char* InputName = "Input.txt";
	char* EncryptedName = "Encrypted.txt";
	char* decryptedName = "Decrypted.txt";
	string InputText;
	std::string CipherText;
	std::string DecryptedText;
	string encoded;

	std::ifstream TextFile1("Input.txt");             //открываю файл
	while (!TextFile1.eof())                         //пока не конец файла..
	{
		if (TextFile1.eof()) break;              //если конец закончить считывание
		TextFile1 >> InputText;                         //или пока не закончится файл,
	}                                            //записывать его содержимое в s1
	TextFile1.close();                               //закрываю файл                          

	std::cout << InputText << std::endl;

	CryptoPP::AES::Encryption aesEncryption((byte *)key.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, (byte *)iv.c_str());

	CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink(CipherText));
	stfEncryptor.Put(reinterpret_cast<const unsigned char*>(InputText.c_str()), InputText.length() + 1);
	stfEncryptor.MessageEnd();
		
	std::cout << "cipher text plain: " << CipherText << std::endl;
	std::cout << std::endl;

	std::ofstream TextFile2("Encryted.txt");            
	TextFile2 << CipherText;                        
	TextFile2.close();                      

	//std::cout << "cipher text In HEX FORM:: ";
	/*for (int i = 0; i < CipherText.size(); i++) {

		std::cout << "0x" << std::hex << (0xFF & static_cast<byte>(CipherText[i])) << " ";
	}*/
	//std::cout << std::endl;
	//std::cout << std::endl;
	///*********************************\
	//\*********************************/

	//// Pretty print
	encoded.clear();
	StringSource(CipherText, true,
		new HexEncoder(
			new StringSink(encoded)
			) // HexEncoder
		); // StringSource
	//std::cout << "cipher text In HEX FORM (Modified):: " << encoded << std::endl;
	//std::cout << std::endl;
	//std::cout << std::endl;
	char *name2;
	name2 = (char*)malloc(encoded.length() + 1); // don't forget to free!!!!
	//											 //s2 = Database_row_count; // I forget if the string class can implicitly be converted to char*
	//											 //s2[0] = '1';
	strcpy(name2, encoded.c_str());

	const char* hex_str = name2;

	std::string result_string;
	unsigned int ch;
	for (; std::sscanf(hex_str, "%2x", &ch) == 1; hex_str += 2)
		result_string += ch;
	//std::cout << "HEX FORM to cipher text :: ";
	//std::cout << result_string << '\n';
	//std::cout << std::endl;
	//std::cout << std::endl;
	///*********************************\
	//\*********************************/


	CryptoPP::AES::Decryption aesDecryption((byte *)key.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, (byte *)iv.c_str());

	CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink(DecryptedText));
	stfDecryptor.Put(reinterpret_cast<const unsigned char*>(result_string.c_str()), result_string.size());
	stfDecryptor.MessageEnd();
	std::cout << DecryptedText << std::endl;

	std::ofstream TextFile3("Decryted.txt");
	TextFile3 << DecryptedText;
	TextFile3.close();

	system("pause");

	return 0;
}