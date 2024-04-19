#include <fstream>
#include <filesystem>
#include "SaveReadFile.hpp"
#include "Encryption.hpp"

SaveReadFile::~SaveReadFile() = default;

auto SaveReadFile::write_to_encrypt_file(const std::vector<std::shared_ptr<Password>> &passwords) const -> void {
    std::ofstream file(pass_file);
    if (!file) {
        std::cout << "Failed to open source file for writing." << std::endl;
        return;
    }

    std::time_t currentTime = std::time(nullptr);
    std::tm* timestamp = std::localtime(&currentTime);

    file << "hh" << timestamp->tm_hour << Encryption::encrypt("DDDD") << std::endl;
    file << "mm" << timestamp->tm_min << Encryption::encrypt("DDDD") << std::endl;
    file << "ss" << timestamp->tm_sec << Encryption::encrypt("DDDD") << std::endl;

    for (const auto& password : passwords) {
        std::string encryptedName = Encryption::encrypt(password->get_name());
        std::string encryptedPassword = Encryption::encrypt(password->get_password());
        std::string encryptedCategory = Encryption::encrypt(password->get_category());
        std::string encryptedWebsite = Encryption::encrypt(password->get_web());
        std::string encryptedLogin = Encryption::encrypt(password->get_login());

        file << encryptedName << "|" << encryptedPassword << "|" << encryptedCategory << "|" << encryptedWebsite << "|" << encryptedLogin << std::endl;
    }

    file.close();
    std::cout << "Encrypted password information written to file." << std::endl;
}

auto SaveReadFile::write_to_category_file(const std::vector<std::string>& category_list) const -> void{
    std::ofstream file(cat_file);
    if (!file) {
        std::cout << "Failed to open source file for writing." << std::endl;
        return;
    }

    for (const auto& category : category_list){
        std::string encryptedCategory = Encryption::encrypt(category);

        file << encryptedCategory << "|";
    }
    file.close();
    std::cout << "Encrypted password category written to file." << std::endl;
}

auto SaveReadFile::read_from_encrypt_file(std::vector<std::shared_ptr<Password>> &passwords) const -> void {
    std::ifstream file(pass_file);
    if (!file) {
        std::cout << "Failed to open source file for reading." << std::endl;
        exit(1);
    }

    std::string line;
    std::string timestamp;
    int lineCount = 0;
    while (std::getline(file, line)) {
        if (lineCount >= 0 && lineCount <= 2) {
            timestamp += line.substr(2, 2);
        } else {
            std::stringstream encryptedInfo(line);
            std::string encryptedName, encryptedPassword, encryptedCategory, encryptedWebsite, encryptedLogin;

            if (std::getline(encryptedInfo, encryptedName, '|') &&
                std::getline(encryptedInfo, encryptedPassword, '|') &&
                std::getline(encryptedInfo, encryptedCategory, '|') &&
                std::getline(encryptedInfo, encryptedWebsite, '|') &&
                std::getline(encryptedInfo, encryptedLogin)) {

                auto password = std::make_shared<Password>(
                        Encryption::decrypt(encryptedName),
                        Encryption::decrypt(encryptedPassword),
                        Encryption::decrypt(encryptedCategory),
                        Encryption::decrypt(encryptedWebsite),
                        Encryption::decrypt(encryptedLogin)
                );

                passwords.push_back(password);
            }
        }

        lineCount++;
    }

    file.close();

}

auto SaveReadFile::read_from_category_file(std::vector<std::string>& categories) const -> void{
    std::ifstream file(cat_file);
    if (!file) {
        std::cout << "Failed to open source file for reading." << std::endl;
        exit(1);
    }

    std::string line;

    while (std::getline(file, line, '|')) {
        categories.push_back(Encryption::decrypt(line));
    }

    file.close();

}

auto SaveReadFile::create_file() -> void{
    std::string passwords_file_name;
    std::string category_file_name;
    std::cout << "Write name of the passwords file: \n";
    std::cin >> passwords_file_name;
    std::cout << "Write name of the category file: \n";
    std::cin >> category_file_name;

    pass_file = get_folder() + "/" + "PASSWORDS." + passwords_file_name + ".txt";
    cat_file  = get_folder() + "/" + "CATEGORIES." + category_file_name + ".txt";

    std::ofstream passwords_file(pass_file);
    std::ofstream category_file(cat_file);

    if (passwords_file.is_open() && category_file.is_open()) {
        passwords_file.close();
        category_file.close();
        std::cout << "Files created successfully." << std::endl;
    } else {
        std::cout << "Error opening the files." << std::endl;
    }
}

auto SaveReadFile::get_folder() -> std::string{
    std::string folder_path = "Passwords";
    std::filesystem::create_directory(folder_path);
    return folder_path;
}

auto SaveReadFile::ready_files() -> void {
    std::string pass_file_name;
    std::string cat_file_name;
    std::filesystem::path path = std::filesystem::current_path();
    path = path.parent_path();
    path.append("cmake-build-debug\\Passwords");

    auto dir = std::filesystem::recursive_directory_iterator(path);
    for( const auto& file : dir) {
        if (file.is_regular_file())
            std::cout << file.path().filename() << "\n";
    }
    std::cout << "Write name of the passwords file you want read\n(WITHOUT PASSWORDS,CATEGORIES AND .TXT):";
    std::cin >> pass_file_name;
    pass_file = get_folder() + "/" + "PASSWORDS." + pass_file_name + ".txt";

    std::cout << "Write name of the categories file you want to read\n(WITHOUT PASSWORDS,CATEGORIES AND .TXT):";
    std::cin >> cat_file_name;
    cat_file = get_folder() + "/" + "CATEGORIES." + cat_file_name + ".txt";
}