#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
using namespace std;

/*
    Average rating of movies:
    Write a program that calculates and prints the average rating of a list of movies. Each movie has
    a list of ratings from 1 to 10 (where 1 is the lowest and 10 is the highest rating). In order to
    compute the rating, you must remove 5% of the highest and lowest ratings before computing their
    average. The result must be displayed with a single decimal point.
*/

struct Movie
{
    int id;
    string title;
    vector<int> ratings;
};

void getRating(vector<Movie> &movies)
{
    cout.precision(2);
    for (Movie &m : movies)
    {
        double minQ{};
        double maxQ{};
        auto size = m.ratings.size();
        auto itMax = max_element(m.ratings.begin(), m.ratings.end());
        auto itMin = min_element(m.ratings.begin(), m.ratings.end());
        int sum = accumulate(m.ratings.begin(), m.ratings.end(), 0, [&](int acc, int val) {
            if (val == *itMax)
            {
                maxQ++;
                return acc;
            }
            if (val == *itMin)
            {
                minQ++;
                return acc;
            }
            return acc + val;
        });
        minQ = (minQ - minQ * 0.05) * *itMin;
        maxQ = (maxQ - maxQ * 0.05) * *itMax;
        double result = (static_cast<double>(sum) + static_cast<double>(minQ + maxQ)) / static_cast<double>(size);
        cout << m.title << " : " << result << " / 10.0" << endl;
    }
}

int main()
{
    std::vector<Movie> movies
            {
                    {101, "The Matrix",   {10, 9,  10, 9, 9, 8, 7, 10, 5,  9, 9, 8}},
                    {102, "Gladiator",    {10, 5,  7,  8, 9, 8, 9, 10, 10, 5, 9, 8, 10}},
                    {103, "Interstellar", {10, 10, 10, 9, 3, 8, 8, 9,  6,  4, 7, 10}},
                    {104, "Bad Boys",     {10, 10, 6,  1, 7, 8, 7, 7,  6,  4, 7, 10}},
                    {105, "Noel",         {5,  6,  5,  7, 3, 2, 2, 4,  6,  4, 7, 1}}
            };
    getRating(movies);

    return 0;
}
