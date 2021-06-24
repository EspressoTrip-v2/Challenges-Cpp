#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <any>


using namespace std;
/*
    Select algorithm:
    Write a function that, given a range of values and a projection function,
    transforms each value into a new one and returns a new range with the
    selected values. For instance, if you have a type book that has an id,
    title, and author, and have a range of such book values, it should be
    possible for the function to select only the title of the books.
*/
struct book
{
    int id;
    std::string title;
    std::string author;
};

template< typename In, typename Func >
vector<any> select(vector<In> &v, Func &&function)
{
    vector<any> result;
    for_each(v.begin(), v.end(), [&](In el) { result.push_back(function(el)); });
    return result;
}
int main()
{
    vector<book> books{
            {101, "The C++ Programming Language",        "Bjarne Stroustrup"},
            {203, "Effective Modern C++",                "Scott Meyers"},
            {404, "The Modern C++ Programming Cookbook", "Marius Bancila"}};

    auto results = select(books, [](book const &b) { return b.title; });
    for (auto &i:results)
        cout << any_cast<string>(i) << endl;
    return 0;
}
