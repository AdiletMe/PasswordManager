#include <iostream>
#include "Encryption.hpp"

Encryption::~Encryption() = default;

auto Encryption::encrypt(const std::string &data) -> std::string {
        std::string encryptedText;
        for (char c: data) {
            encryptedText += c + 1; // Shift each character by 1 position
        }
        return encryptedText;
}

auto Encryption::decrypt(const std::string &data) -> std::string {
        std::string decryptedText;
        for (char c: data) {
            decryptedText += c - 1; // Shift each character back by 1 position
        }
        return decryptedText;
}
