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

 Movie(string name, int rating, double releaseYear, string review)
        : name(name), rating(rating), releaseYear(releaseYear), review(review), next(nullptr) {}

    Movie(string name, int rating, double releaseYear, string review);
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
    void mergeSortAsc(int, int);
    void mergeAsc(int, int, int);
    void mergeSortWrapperAsc();
    void displayMoviesInRange();
    void searchMovie();
    void saveDataToFile();
    void loadDataFromFile();

private:
    Movie* head;
    Movie* tail;
   

    
  
};
