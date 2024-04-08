#pragma once

#include <string>

using namespace std;

const int MAX_REVIEW_LENGTH = 30;

struct Movie {
    string name;
    int rating;
    double releaseYear;
    string review;
    Movie* next;
    // Default constructor
 Movie() : rating(0), releaseYear(0), next(nullptr) {}

    // Parameterized constructor
 Movie(string name, int rating, double releaseYear, string review)
        : name(name), rating(rating), releaseYear(releaseYear), review(review), next(nullptr) {}

};

class MovieList {
public:
    MovieList();
    ~MovieList();

    void runMovieSystem();
    void addMovie();
    void removeMovie();
    void modifyMovie();
    void displayMovieList();
    void displayMoviesInRange();
    void searchMovie();
    void saveDataToFile();
    void loadDataFromFile();
    void sortMovies();

private:
    Movie* head;
    Movie* tail;
   
   
};
