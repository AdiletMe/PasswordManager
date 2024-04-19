#ifndef PASSWORDMANAGER_PASSWORD_HPP
#define PASSWORDMANAGER_PASSWORD_HPP

#include <string>
#include <vector>
#include <memory>
#include <iostream>

class Password {
public:
    /**
     * \brief Create new Password class.
     *
     * Class with empty constructor used for class main to start menu function.
     */
    Password();
    /**
     * \brief Create new Password class.
     *
     * Create new Password class without  URL and login.
     *
     * @param name The password's name.
     * @param password password.
     * @param category The password's category.
     */
    /**
     * \brief Destructor of the class.
     */
    ~Password();

    Password(std::string name, std::string password, std::string category);
    /**
     * \brief Create new Password class.
     *
     * Create new Password class with all functional requirement parameters.
     *
     * @param name.
     * @param password.
     * @param category.
     * @param URL.
     * @param login.
     */
    Password(std::string name, std::string password, std::string category, std::string URL, std::string login);
   /**
    * \brief Presents a menu to the user and performs actions based on their selection.
    * Reads from files, creates a new file, or exits the program.
    */
    auto start() -> void;
    /**
     * \brief Displays a menu to the user and performs actions based on their selection.
     * Allows the user to add, search, edit, delete passwords, add or delete categories,
     * show all passwords or categories, and save and exit the program.
     * The function runs in a loop until the user chooses to exit.
     */
    auto menu() -> void;

    auto setName(const std::string &Name) -> void;
    auto setPassword(const std::string &Password) -> void;
    auto setCategory(const std::string &Category) -> void;
    auto setUrl(const std::string &url) -> void;
    auto setLogin(const std::string &Login) -> void;

    [[nodiscard]] auto get_name() const -> std::string;
    [[nodiscard]] auto get_password() const -> std::string;
    [[nodiscard]] auto get_category() const -> std::string;
    [[nodiscard]] auto get_web() const -> std::string;
    [[nodiscard]] auto get_login() const -> std::string;
private:
    /**
     * \brief Show all information of password.
     *
     * Use std::cout to output to CLI all password's fields.
     */
    auto show_password() -> void;
    /**
     * \brief Show all category.
     *
     * Use for loop and std::cout to output all category stored in vector <categories>.
     */
    auto show_all_category() -> void;
    /**
     * \brief Show all passwords.
     *
     * Use for loop and std::cout to output all passwords stored in vector <categories>.
     */
    auto show_all_passwords() -> void;
    /**
     * \brief search password vector <passwords>.
     *
     * Allow to user input parameter (name,password or login) and search in vector one of the parameter.
     * \return True if parameter was found, and False otherwise.
     */
    auto search_password() -> bool;
    /**
     * \brief add password to vector <passwords>.
     *
     * Firstly user need to select does (s)he want to generate password or enter it.
     * Second user need to select does s(he) want to enter URL and login.
     * After entering password function check_password() checks is password repeating or not.
     * At the end include new Password to vector <passwords>.
     */
    auto add_password() -> void;
    /**
     * \brief generate password.
     * Create 4 strings.
     * 1. 'characters' fill characters which user select.
     * 2. 'uppercase_letters' include all latin uppercase letters.
     * 3. 'lowercase_letters' include all latin lowercase letters.
     * 4. 'special_characters' include some special characters.
     *
     * User need to length of password, then select does he want to include
     * uppercase or lowercase or special characters.
     * After that via randomizer password select random characters from 'character' variable.
     *
     * @return ready password
     */
    auto generate_password() -> std::string;
    /**
     * \brief check is password repeating in vector <passwords>
     *
     * @param pass password which is being checked
     *
     * use ranges::any_of to check is password repeated
     * @return true if password is repeated, false if not
     */
    auto check_password(const std::string& pass) -> bool;
    /**
     * \brief Allow to edit password
     * User select password and parameter (s)he want to change,
     * Then entering new parameter using setter.
     */
    auto edit_password() -> void;
    /**
     * \brief sort vector <passwords>.
     * User select how (s)he want sort passwords.
     * If input number is 0 vector will sorted by category, otherwise by name.
     * Sorting is done by comparing name or category.
     */
    auto sort_passwords() -> void;
    /**
     * \brief delete password from vector <passwords>.
     *
     * User select which password (s)he wants to delete, then confirm deleting.
     */
    auto delete_password() -> void;
    /**
     * \brief add category to vector <categories>.
     * User enter name of new category and include it to vector <categories>.
     */
    auto add_category() -> void;
    /**
     * \brief delete category and all passwords according to this category.
     * User select number of category (s)he wants to delete.
     * After that via erase and remove if deletes category and all passwords according to this category,
     * from vectors <categories> and <passwords>.
     */
    auto delete_category() -> void;
    /**
     * \brief already created passwords and included it to vectors
     * 10 passwords and 3 category.
     * Use this function in menu.
     */
    auto ready_passwords() -> void;

    std::string name;     /*!< Stores the password name as string */
    std::string password; /*!< Stores password as string */
    std::string category; /*!< Stores the password category as string */
    std::string URL;      /*!< Stores the password URL as string */
    std::string login;    /*!< Stores the password login as string */

    std::vector<std::string> categories; /*!< Stores all categories*/
    std::vector<std::shared_ptr<Password>> passwords; /*!< Stores all passwords */


};
#endif
