#include <iostream>
#include <filesystem>
#include <fstream>

using namespace std;
namespace fs = filesystem;

int main()
{
    uintmax_t size{};

    ofstream file_out{"text-books.txt", ios::app};
    if (!file_out) exit(1);
    // iterator settings
    auto iterator = fs::recursive_directory_iterator(
            "B:\\Textbooks",
            std::filesystem::directory_options::follow_directory_symlink
    );
    int books{};
    for (auto &p: iterator)
    {
        size += p.file_size();
        string temp = p.path().string();
        string file;
        for (auto i{temp.rbegin()}; i != temp.rend(); i++)
        {
            if (*i == '\\')
            {
                break;
            }
            file = *i + file;
        }
        books++;
        file_out << books << " : " << file << ", Size: " << p.file_size() / 1000 << " KB" << endl;

    }

    file_out << "\n" << "Total books in directory: " << books << endl;
    file_out.close();
    cout << "\nTotal size: " << size << " bytes." << endl;
    return 0;
}
