#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class Book
{
    std::string title;
    std::string author;
    int year;
    bool isAvaliable;

public:
    Book()
    {
        title = "No title";
        author = "No author";
        year = 0;
        isAvaliable = true;
    }
    
    Book(const std::string& title, const std::string& author, int year, bool isAvailable)
        : title(title), author(author), year(year), isAvaliable(isAvailable)
    {
    }

    std::string getTitle() {
        return title;
    }

    std::string getAuthor() {
        return author;
    }

    int getYear() {
        return year;
    }

    bool getIsAvaliable() {
        return isAvaliable;
    }

    void setTitle(std::string s_title) {
        title = s_title;
    }

    void setAuthor(std::string s_author) {
        author = s_author;
    }

    void setYear(int s_year) {
        year = s_year;
    }

    void setIsAvaliable(bool s_isAvaliable) {
        isAvaliable = s_isAvaliable;
    }
};

void readReadBooksFromFile(const std::vector<Book>& books, const std::string& path)
{
    std::ifstream fin;
    fin.open(path);

    if (!fin.is_open())
    {
        std::cout << "Ошибка открытия файла!" << std::endl;
    }
    else
    {
        std::cout << "Содержание открытого файла:\n" << std::endl;
        std::string str;

        while (!fin.eof())
        {
            str = "";
            std::getline(fin, str);
            std::cout << str << std::endl;
        }
    }

    fin.close();
}

void saveBooksToFile(const std::vector<Book>& books, const std::string& path) {
    std::ofstream fout(path);
    if (not fout.is_open()) {
        std::cout << "Ошибка открытия файла!\n";
        return;
    }

    fout << books.size() << "\n";

    for (Book book : books) {
        fout << book.getTitle() << "\n";
        fout << book.getAuthor() << "\n";
        fout << book.getYear() << "\n";
        fout << book.getIsAvaliable() << "\n";
    }

    std::cout << "Книги сохранены в файл " << path << std::endl;
}

void printBook(Book& book) {
    std::cout << "Название книги: " << book.getTitle() << std::endl;
    std::cout << "Автор книги: " << book.getAuthor() << std::endl;
    std::cout << "Год издания книги: " << book.getYear() << std::endl;
    if (book.getIsAvaliable()) {
        std::cout << "Книга доступна\n";
    }
    else {
        std::cout << "Книга недоступна\n";
    }
}

void printAllBooks(const std::vector<Book>& books) {
    for (Book book : books) {
        printBook(book);
    }
}

void findBooksByTitle(const std::vector<Book>& books) {
    std::string title;
    int foundBooks = 0;

    std::cout << "Введите название книги для поиска: ";

    std::getline(std::cin, title);

    for (Book book : books) {
        if (book.getTitle() == title) {
            foundBooks++;
            std::cout << "Найденная книга " << foundBooks << ":\n" << std::endl;
            printBook(book);
        }
    }
    if (foundBooks == 0) {
        std::cout << "Не найдено книг с названием: " << title << std::endl;
    }
}

void findBookByAuthor(const std::vector<Book>& books) {
    std::string author;
    int foundBooks = 0;

    std::cout << "Введите автора книги для поиска: ";

    std::getline(std::cin, author);

    for (Book book : books) {
        if (book.getAuthor() == author) {
            foundBooks++;
            std::cout << "Найденная книга " << foundBooks << ":\n" << std::endl;
            printBook(book);
        }
    }
    if (foundBooks == 0) {
        std::cout << "Не найдено книг автора: " << author << std::endl;
    }
}

void findBooksByYear(const std::vector<Book>& books) {
    int year;
    int foundBooks = 0;

    std::cout << "Введите год издания книги для поиска: ";

    std::cin >> year;

    for (Book book : books) {
        if (book.getYear() == year) {
            foundBooks++;
            std::cout << "Найденная книга " << foundBooks << ":\n" << std::endl;
            printBook(book);
        }
    }
    if (foundBooks == 0) {
        std::cout << "Не найдено книг с годом издания: " << year << std::endl;
    }
}

Book createNewBook() {
    Book book;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string line;
    int num;
    bool flag = true;

    std::cout << "Введите название книги: ";
    std::getline(std::cin, line);
    book.setTitle(line);

    std::cout << "Введите автора книги: ";
    std::getline(std::cin, line);
    book.setAuthor(line);

    std::cout << "Введите год издания книги: ";
    std::cin >> num;
    book.setYear(num);

    std::cout << "Книга доступна (0 если НЕТ, любое число если ДА): ";
    std::cin >> num;
    if (num == 0) {
        flag = false;
    }
    book.setIsAvaliable(flag);

    return book;
}

void addNewBook(std::vector<Book>& books) {
    books.push_back(createNewBook());
}

void changeBook(std::vector<Book>& books) {
    int pos;

    std::cout << "Введите номер книги для замены: ";
    std::cin >> pos;

    std::cout << "Введите данные новой книги." << std::endl;

    books[pos - 1] = createNewBook();
}

void removeBook(std::vector<Book>& books) {
    int pos;

    std::cout << "Введите номер книги для удаления: ";
    std::cin >> pos;

    auto iter = books.cbegin();
    books.erase(iter + pos - 1);
}

void printMenu()
{
    std::cout << "\nМеню библиотеки\n\n" <<
        "1. Загрузить книги из файла\n" <<
        "2. Сохранить книги в файл\n" <<
        "3. Вывести список всех книг на экран\n" <<
        "4. Найти книгу по названию\n" <<
        "5. Найти книгу по автору\n" <<
        "6. Найти книгу по году\n" <<
        "7. Добавить новую книгу\n" <<
        "8. Заменить книгу\n" <<
        "9. Удалить книгу\n" <<
        "0. Закрыть программу" << std::endl;
}

int main()
{
    setlocale(LC_CTYPE, "rus");

    std::vector<Book> books;

    int pointMenu = -1;

    while (pointMenu != 0) {

        printMenu();

        std::cout << "\nВведите пункт меню: ";
        std::cin >> pointMenu;

        switch (pointMenu)
        {
        case 1:
            readReadBooksFromFile(books, "books.txt");
            return;
        case 2:
            saveBooksToFile(books, "books.txt");
            return;
        case 3:
            printAllBooks(books);
            break;
        case 4:
            findBooksByTitle(books);
            return;
        case 5:
            findBookByAuthor(books);
            return;
        case 6:
            findBooksByYear(books);
            return;
        case 7:
            addNewBook(books);
            break;
        case 8:
            changeBook(books);
            return;
        case 9:
            removeBook(books);
            return;
        case 0:
            std::cout << "\nЗавершение работы программы" << std::endl;
            break;
        default:
            std::cout << "\nВы ввели неправильный номер пункта меню! Повторите ввод.\n" << std::endl;
            break;
        }
    }
}
