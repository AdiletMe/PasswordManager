#ifndef PASSWORDMANAGER_ENCRYPTION_HPP
#define PASSWORDMANAGER_ENCRYPTION_HPP

#include <iostream>

/**
 * \class Encryption
 * \brief A class that provides encryption and decryption functionality using a simple shift cipher algorithm.
 * The Encryption class encapsulates the operations related to encrypting and decrypting strings using a simple shift cipher algorithm.
 * It provides static member functions for encrypting and decrypting strings.
 * The class assumes a simple shift cipher algorithm where each character in the input string is shifted by one position for encryption,
 * and shifted back by one position for decryption. The encryption and decryption operations are performed character by character.
 */
class Encryption {

public:
    /**
     * \brief Encrypts a given string using a simple shift cipher algorithm.
     * This static member function of the Encryption class encrypts a given string using a simple shift cipher algorithm.
     * Each character in the input string is shifted by one position, resulting in a simple substitution encryption.
     * The function iterates over each character in the input string and applies the shift operation. The shifted characters
     * are concatenated to form the encrypted text.
     * @param data The string to be encrypted.
     * @return std::string The encrypted text.
     */
    static auto encrypt(const std::string& data) -> std::string;
    /**
     * \brief Decrypts a given string that has been encrypted using a simple shift cipher algorithm.
     * This static member function of the Encryption class decrypts a given string that has been encrypted using a simple shift cipher algorithm.
     * Each character in the input string is shifted back by one position, effectively reversing the encryption process.
     * The function iterates over each character in the input string and applies the reverse shift operation. The shifted characters
     * are concatenated to form the decrypted text.
     * @param data The string to be decrypted.
     * @return std::string The decrypted text.
     */
    static auto decrypt(const std::string& data) -> std::string;

    ~Encryption();
};

#endif
