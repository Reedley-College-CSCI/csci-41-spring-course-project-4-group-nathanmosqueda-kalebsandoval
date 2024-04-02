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
    void displayMoviesInRange();
    void searchMovie();
    void saveDataToFile();
    void loadDataFromFile();

private:
    Movie* head;
    Movie* tail;
   

    
  
};
