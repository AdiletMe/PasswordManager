#include "Password.hpp"
#include "SaveReadFile.hpp"
#include <iostream>
#include <utility>
#include <random>
#include <memory>

SaveReadFile saveReadFile;

Password::Password() = default;

Password::~Password() = default;

Password::Password(std::string name, std::string password, std::string category){
    this->name = std::move(name);
    this->password = std::move(password);
    this->category = std::move(category);
    this->URL = "NO URL";
    this->login = "NO LOGIN";
}

Password::Password(std::string name, std::string password, std::string category, std::string URL, std::string login) {
    this->name = std::move(name);
    this->password = std::move(password);
    this->category = std::move(category);
    this->URL = std::move(URL);
    this->login = std::move(login);
}

auto Password::setName(const std::string &Name)  -> void{
    Password::name = Name;
}

auto Password::setPassword(const std::string &Password)  -> void{
    Password::password = Password;
}

auto Password::setCategory(const std::string &Category)  -> void {
    Password::category = Category;
}

auto Password::setUrl(const std::string &url)  -> void{
    URL = url;
}

auto Password::setLogin(const std::string &Login)  -> void{
    Password::login = Login;
}

auto Password::get_name() const -> std::string {
    return name;
}

auto Password::get_password() const -> std::string {
    return password;
}

auto Password::get_category() const -> std::string {
    return category;
}

auto Password::get_web() const -> std::string {
    return URL;
}

auto Password::get_login() const -> std::string {
    return login;
}

auto Password::show_password() -> void {
    std::cout << "Name: " << name
              << "\nPassword: " << password
              << "\nCategory: " << category
              << "\nURL: " << URL
              << "\nLogin: " << login;
}

auto Password::show_all_category() -> void {
    for(int i = 0; i < categories.size(); i++){
        std::cout << "[" << i << "] ";
        std::cout << categories.at(i) << "\n";
        std::cout << "---------------------------------------------------\n";
    }

}

auto Password::show_all_passwords() -> void {
    for(int i = 0; i < passwords.size(); i++){
        std::cout << "[" << i << "] ";
        passwords[i]->show_password();
        std::cout << "\n---------------------------------------------------\n";
    }
}

auto Password::search_password() -> bool  {
    std::string parameter;

    std::cout << "Enter parameter(name,password or login) : ";
    std::cin >> parameter;
    for(auto &pass : passwords){
        if( pass->name == parameter     ||
            pass->password == parameter ||
            pass->login == parameter){
                pass->show_password();
                return true;
            }
    }
    std::cout << "No such password";
    return false;
}

auto Password::add_password() -> void {
    int num;
    int generator_num;
    int category_select;

    std::cout << "Enter 1 if you want to generate password: ";
    std::cin >> generator_num;
    if(generator_num == 1) password = generate_password();

    std::cout << "Enter 1 if you to add URL and Login?";
    std::cin >> num;
    std::cout << "Enter name of password: ";
    std::cin >> name;
    if(generator_num != 1) {
        std::cout << "Enter password: ";
        std::cin >> password;
    }
    std::cout << "Select category: ";
    show_all_category();
    std::cin >> category_select;
    if(num == 1) {
        std::cout << "Enter URL: ";
        std::cin >> URL;
        std::cout << "Enter login: ";
        std::cin >> login;

        if(check_password(password)) {
            std::cout << "You already used this password before, we can't add it!";
            return;
        }

        auto new_password = std::make_shared<Password>(name, password, categories.at(category_select), URL, login);
        passwords.push_back(new_password);
        return;

    }

    if(check_password(password)) {
        std::cout << "You already used this password before, we can't add it!";
        return;
    }

    auto new_password = std::make_shared<Password>(name,password,categories.at(category_select));
    passwords.push_back(new_password);
}

auto Password::generate_password() -> std::string {
    int num;
    int length;
    std::string characters;
    std::string uppercase_letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string lowercase_letters = "abcdefghijklmnopqrstuvwxyz";
    std::string special_characters = "!@#$%^&*()-_=+{}[]<>?/|\\";

    std::cout << "Enter number of characters: ";
    std::cin >> length;

    // Add uppercase letters to the character pool if requested
    std::cout << "Enter 1 if you want to use uppercase in password: ";
    std::cin >> num;
    if(num == 1) characters += uppercase_letters;

    // Add lowercase letters to the character pool if requested
    std::cout << "Enter 1 if you want to use lowercase in password: ";
    std::cin >> num;
    if (num == 1) characters += lowercase_letters;

    // Add special characters to the character pool if requested
    std::cout << "Enter 1 if you want to use special characters in password: ";
    std::cin >> num;
    if (num == 1) characters += special_characters;


    // Use a random device to generate random numbers for character selection
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, characters.size() - 1);

    // Add random characters to the password until it reaches the desired length
    for (int i = 0; i < length; i++)
        password += characters[dis(gen)];

    return password;
}

auto Password::check_password(const std::string& pass) -> bool{
    return std::ranges::any_of(passwords, [&](const auto& password1) {
        return password == pass;
    });

}

auto Password::start() -> void{
    int num;

    std::cout << "What do you want to do?\n";
    std::cout << "0. Select ready file\n";
    std::cout << "1. Create new file\n";
    std::cout << "Any number. Leave\n";
    std::cin >> num;

    switch (num) {
        case 0:
            saveReadFile.ready_files();
            saveReadFile.read_from_encrypt_file(passwords);
            saveReadFile.read_from_category_file(categories);
            menu();
            break;
        case 1:
            saveReadFile.create_file();
            //ready_passwords();
            menu();
            break;
        default:
            exit(1);
    }
}

auto Password::menu() -> void {
    while (true) {
        std::cout << "\nShow menu? ";
        std::cout << "\n[Any number] -> Yes";
        std::cout << "\n[-1]         -> No, exit";
        int num = 0;

        std::cin >> num;
        if(num == -1) exit(1);

        std::cout << "What do you want?\n";
        std::cout << "[0] -> Add password\n";
        std::cout << "[1] -> Search password\n";
        std::cout << "[2] -> Sort passwords\n";
        std::cout << "[3] -> Edit password\n";
        std::cout << "[4] -> Delete password\n";
        std::cout << "[5] -> Add category\n";
        std::cout << "[6] -> Delete category\n";
        std::cout << "[7] -> Show all passwords\n";
        std::cout << "[8] -> Show all category\n";
        std::cout << "[9] -> Save and Exit\n";
        std::cin >> num;


        switch (num) {
            case 0:
                add_password(); break;
            case 1:
                search_password(); break;
            case 2:
                sort_passwords(); break;
            case 3:
                edit_password(); break;
            case 4:
                delete_password(); break;
            case 5:
                add_category(); break;
            case 6:
                delete_category(); break;
            case 7:
                show_all_passwords(); break;
            case 8:
                show_all_category(); break;
            case 9:
                saveReadFile.write_to_encrypt_file(passwords);
                saveReadFile.write_to_category_file(categories);
                exit(1);
            default:
                std::cout << "Incorrect number";
        }
    }
}

auto Password::edit_password() -> void {
    int pass_select;
    int cat_select;
    int num;
    std::string parameter;

    std::cout << "Select password: ";
    show_all_passwords();
    std::cin >> pass_select;
    std::cout << "What do you want to change?\n";
    std::cout << "[0] -> Name\n";
    std::cout << "[1] -> Password\n";
    std::cout << "[2] -> Category\n";
    std::cout << "[3] -> URL and Login\n";
    std::cin >> num;

    switch (num) {
        case 0:
            std::cout << "Enter name: ";
            std::cin >> parameter;
            passwords.at(pass_select)->setName(parameter);
            break;
        case 1:
            std::cout << "Enter password: ";
            std::cin >> parameter;

            if(!check_password(parameter)) {
                std::cout << "You already used this password before, we can't add it!";
                return;
            }
            passwords.at(pass_select)->setPassword(parameter);
            break;
        case 2:
            std::cout << "Select Category: \n";
            show_all_category();
            std::cin >> cat_select;
            passwords.at(pass_select)->setCategory(categories.at(cat_select));
            break;
        case 3:
            std::cout << "Enter URL: ";
            std::cin >> parameter;
            passwords.at(pass_select)->setUrl(parameter);
            std::cout << "Enter Login: ";
            std::cin >> parameter;
            passwords.at(pass_select)->setLogin(parameter);
            break;
        default:
            std::cout << "Incorrect number";
            return;
    }

}

auto Password::sort_passwords() -> void {
    std::cout << "How do you want to sort?\n";
    std::cout << "[0]          -> By Category\n";
    std::cout << "[Any number] -> By name\n";
    int num = 0;
    std::cin >> num;
    if(num == 1){
        auto compare_names = [](
                const std::shared_ptr<Password>& name1,
                const std::shared_ptr<Password>& name2) {
            return name1->get_name() < name2->get_name();
        };
        std::sort(passwords.begin(),passwords.end(),compare_names);
        return;
    }

    auto compare_category = [](
            const std::shared_ptr<Password>& category1,
            const std::shared_ptr<Password>& category2){

        return category1->get_category() < category2->get_category();
    };
    std::sort(passwords.begin(),passwords.end(),compare_category);

}

auto Password::delete_password() -> void {
    std::string finish;
    int num = 0;
    while(true) {
        show_all_passwords();
        std::cout << "Select password or enter -1 to exit:\n";
        std::cin >> num;
        if(num == -1) return;

        std::cout << "You sure you want to delete password: \n";
        passwords.at(num)->show_password();
        std::cout << "\n[1]          -> Yes\n";
        std::cout << "[Any number] -> No\n";
        std:: cin >> num;
        if(num == 1) passwords.erase(passwords.begin() + num);
    }
}

auto Password::add_category() -> void {
    std::string category_name;
    std::cout << "Write name of category: ";
    std::cin >> category_name;
    categories.push_back(category_name);
}

auto Password::delete_category() -> void {
    std::cout << "Select category: ";
    int num;
    show_all_category();
    std::cin >> num;
    std::string category_to_remove = categories[num];

    passwords.erase(std::remove_if(passwords.begin(), passwords.end(),
                                   [&category_to_remove](const std::shared_ptr<Password>& p) {
                                       return p->category == category_to_remove;
                                   }), passwords.end());
    categories.erase(categories.begin() + num);
}

auto Password::ready_passwords() -> void{
    std::string category0 = "category0";
    std::string category1 = "category1";
    std::string category2 = "category2";

    categories.push_back(category0);
    categories.push_back(category1);
    categories.push_back(category2);

    auto password0 = std::make_shared<Password>("Name0","Password0",categories.at(0));
    auto password1 = std::make_shared<Password>("Name1","Password1",categories.at(0));
    auto password2 = std::make_shared<Password>("Name2","Password2",categories.at(0));
    auto password3 = std::make_shared<Password>("Name3","Password3",categories.at(1));
    auto password4 = std::make_shared<Password>("Name4","Password4",categories.at(1));
    auto password5 = std::make_shared<Password>("Name5","Password5",categories.at(1),"URL5","Login5");
    auto password6 = std::make_shared<Password>("Name6","Password6",categories.at(2),"URL6","Login6");
    auto password7 = std::make_shared<Password>("Name7","Password7",categories.at(2),"URL7","Login7");
    auto password8 = std::make_shared<Password>("Name8","Password8",categories.at(2),"URL8","Login8");
    auto password9 = std::make_shared<Password>("Name9","Password9",categories.at(2),"URL9","Login9");

    passwords.push_back(password1);
    passwords.push_back(password9);
    passwords.push_back(password0);
    passwords.push_back(password5);
    passwords.push_back(password2);
    passwords.push_back(password4);
    passwords.push_back(password3);
    passwords.push_back(password8);
    passwords.push_back(password6);
    passwords.push_back(password7);
}