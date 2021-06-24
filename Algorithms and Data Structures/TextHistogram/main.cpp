#include <iostream>
#include <string>
#include <numeric>
#include <algorithm>
#include <iomanip>
#include <unordered_map>
using namespace std;
/*
   Text histogram:
   Write a program that, given a text, determines and prints
   a histogram with the frequency of each letter of the alphabet.
   The frequency is the percentage of the number of appearances
   of each letter from the total count of letters. The program
   should count only the appearances of letters and ignore digits,
   signs, and other possible characters. The frequency must be
   determined based on the count of letters and not the text size.
 */
void histogram(string_view &&s)
{
    unordered_map<char, double> logChar;
    int count = accumulate(s.begin(), s.end(), 0, [&](int acc, char item) {
        return isalpha(item) ? acc + 1 : acc + 0;
    });
    for_each(s.begin(), s.end(), [&](char item) {
        if (isalpha(item))
        {
            if (!logChar.count(static_cast<char>(tolower(item))))
            {
                logChar[static_cast<char>(tolower(item))] = 1.0;
                return;
            }
            logChar[static_cast<char>(tolower(item))]++;
        }
    });

    cout << right << "Letter " << setw(10) << "Percent" << endl;
    cout << setfill('-') << setw(18) << " " << endl;
    for_each(logChar.begin(), logChar.end(), [&count](pair<char, double> item) {

        double per{item.second / count * 100};
        cout.precision(2);
        cout << setfill(' ') << right << setw(3) << item.first << setw(11) << per << " %" << endl;
    });
    cout << setfill('-') << setw(18) << " " << endl;
}
int main()
{
    histogram(

            R"(When it comes to learning new English phrases, some of the most
                    interesting are English idioms. Idioms can be some of the most difficult parts of the
                    English language to learn and understand. Often students go online to find a long list of idioms
                    to try and study their meaning. While this can be useful, it does come with some big disadvantages.
                    Simply looking at a long list of idioms can be quite daunting to someone who is just starting to learn English.
                    In addition, many times these long lists don't include the definition of the idiom.
                    This tool, however, allows anyone looking at the random idioms and to also see the definition at
                    the same time. This makes this generator quite useful for those studying English as a second
                    language to learn the many different idioms that are part of the English language.
                    This allows English learning to confirm the idioms they already know while learning new ones when using this tool.)"
    );

    return 0;
}
