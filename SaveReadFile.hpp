#ifndef PASSWORDMANAGER_SAVEREADFILE_HPP
#define PASSWORDMANAGER_SAVEREADFILE_HPP

#include<iostream>
#include <filesystem>
#include "Password.hpp"

/**
 * \class SaveReadFile
 * \brief A class that provides functionality for saving and reading encrypted password information and categories to/from files.
 * The SaveReadFile class encapsulates the operations related to saving and reading encrypted password information and categories
 * to/from files. It provides methods to write encrypted password information and categories to files, as well as methods to read
 * encrypted password information and categories from files and populate data structures accordingly.
 * The class utilizes the Encryption class for encryption and decryption operations. It also relies on the filesystem library
 * for file-related operations such as searching for files in directories and obtaining file paths.
 */
class SaveReadFile {
public:
    /**
     * \brief Writes encrypted password information to a file.
     * This function takes a vector of shared pointers to Password objects and writes their encrypted information
     * to a file. The file path is obtained using the search_encrypt_file() function. If the file fails to open,
     * an error message is displayed and the function returns.
     * The function retrieves the current timestamp and writes the hours, minutes, and seconds to the file, each
     * preceded by a specific identifier and encrypted using the "DDDD" encryption key.
     * Then, for each password in the vector, the function encrypts the name, password, category, website, and login
     * using the Encryption::encrypt() function. The encrypted values are written to the file, separated by '|' characters,
     * in the order: name, password, category, website, and login.
     * Finally, the file is closed, and a message indicating the successful writing of the encrypted password information
     * is displayed.
     * @param passwords A vector of shared pointers to Password objects.
     */
    auto write_to_encrypt_file(const std::vector<std::shared_ptr<Password>>& passwords) const -> void;
    /**
     * \brief Writes encrypted password categories to a file.
     * This function takes a vector of category strings and writes their encrypted versions to a file.
     * The file path is obtained using the search_category_file() function. If the file fails to open,
     * an error message is displayed and the function returns.
     * For each category in the vector, the function encrypts the category using the Encryption::encrypt() function.
     * The encrypted category strings are written to the file, separated by '|' characters.
     * Finally, the file is closed, and a message indicating the successful writing of the encrypted password categories
     * is displayed.
     * @param category A vector of category strings.
     */
    auto write_to_category_file(const std::vector<std::string>& category) const -> void;
    /**
     * \brief Destructor of the class
     */
    ~SaveReadFile();
    /**
     * \brief Reads encrypted password information from a file and populates the vector of shared pointers to Password objects.
     * This function reads the encrypted password information from a file. The file path is obtained using the search_encrypt_file()
     * function. If the file fails to open, an error message is displayed and the function returns.
     * The function iterates over each line in the file. If the line count is between 0 and 2 (inclusive), it extracts the relevant
     * substrings from the line to construct the timestamp.
     * For lines with an index greater than 2, the function creates a stringstream from the line and uses getline() with the '|' delimiter
     * to extract the encrypted name, password, category, website, and login. It then decrypts these encrypted values using the Encryption::decrypt()
     * function and creates a new shared pointer to a Password object with the decrypted information. This Password object is added to the
     * vector of passwords.
     * Finally, the file is closed.
     * @param passwords A vector of shared pointers to Password objects, to be populated with decrypted password information.
     */
    auto read_from_encrypt_file(std::vector<std::shared_ptr<Password>>& passwords) const -> void;
    /**
     * \brief Reads encrypted password categories from a file.
     * This function reads encrypted password categories from a file and populates
     * a vector with the decrypted versions of the categories.
     * The function takes a reference to a vector of category strings as a parameter.
     * The file path is obtained from the cat_file member variable.
     * The function attempts to open the file for reading. If the file fails to open,
     * an error message is displayed, and the function returns.
     * The function reads each line from the file and separates the categories using the '|' character.
     * Each encrypted category string is decrypted using the Encryption::decrypt() function
     * and then added to the vector of categories.
     * Finally, the file is closed, and the function completes successfully.
     * \param categories A reference to a vector of category strings.
     */
    auto read_from_category_file(std::vector<std::string>& category) const -> void;
    /**
     * \brief Creates new password and category files.
     * This function prompts the user to enter names for the password and category files.
     * It then creates the corresponding files by combining the entered names with predetermined prefixes and extensions.
     * The full paths of the password and category files are stored in the pass_file and cat_file member variables, respectively.
     * The function attempts to open the password and category files for writing.
     * If both files are successfully opened, they are immediately closed, indicating that the files were created successfully.
     * If either file fails to open, an error message is displayed.
     */
    auto create_file() -> void;
    /**
     * \brief Show files for reading.
     * This function displays a list of available files in the "cmake-build-debug/Passwords" directory.
     * It then prompts the user to enter the names of the passwords and categories files they want to read,
     * without including the "PASSWORDS.", "CATEGORIES.", and ".txt" prefixes and extensions.
     * The function sets the full paths of the passwords and categories files by combining the user-entered names
     * with the appropriate prefixes and extensions. These paths are stored in the 'pass_file' and 'cat_file' member variables, respectively.
     */
    auto ready_files() -> void;

private:
    /**
    * \brief Retrieves the folder path for storing files.
    * This function returns the folder path where files are stored.
    * The folder path is set as "Passwords".
    * If the folder does not exist, the function creates it using the std::filesystem::create_directory() function.
    * \return The folder path as a string.
    */
    static auto get_folder() -> std::string;

    std::string pass_file; /*!< Stores path of the file with passwords */
    std::string cat_file; /*!< Stores path of the file with categories */
};

#endif
