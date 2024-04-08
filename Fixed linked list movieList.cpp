#include "movielist.h"
#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

MovieList::MovieList() : head(nullptr), tail(nullptr) {
    loadDataFromFile(); // Load data from file on object creation
}

MovieList::~MovieList() {
    while (head != nullptr) {
        Movie* temp = head;
        head = head->next;
        delete temp;
    }
}

void MovieList::runMovieSystem() {
    DWORD start = GetTickCount(); // Start measuring time
    loadDataFromFile();
    int decision = 0;
    do {
        // Display Menu Options
        cout << "Movie List" << endl;
        cout << "1. Add a movie" << endl;
        cout << "2. Remove a movie" << endl;
        cout << "3. Modify a movie" << endl;
        cout << "4. Display movie list" << endl;
        cout << "5. Display movies in a range of years" << endl;
        cout << "6. Search a movie" << endl;
        cout << "7. Exit" << endl;

        cin >> decision;
        cin.ignore(); // Clear the input buffer

        // Actions based on user input
        switch (decision) {
        case 1:
            addMovie();
            break;
        case 2:
            removeMovie();
            break;
        case 3:
            modifyMovie();
            break;
        case 4:
            displayMovieList();
            break;
        case 5:
            displayMoviesInRange();
            break;
        case 6:
            searchMovie();
            break;
        case 7:
            cout << "Exiting the program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (decision != 7); // Continue the loop until the user chooses to exit

    DWORD end = GetTickCount(); // Stop measuring time

    DWORD elapsedTime = end - start;
    cout << "Elapsed time in runMovieSystem(): " << elapsedTime << " ms" << endl;
}

void MovieList::addMovie() {
    DWORD start = GetTickCount();
    string name, review;
    int rating;
    double releaseYear;

    cout << "Enter name of movie: ";
    getline(cin, name);

    do {
        cout << "Enter rating (1 - 5): ";
        cin >> rating;
        cin.ignore(); // Clear input buffer

        if (rating < 1 || rating > 5) {
            cout << "Invalid rating. Please enter a rating between 1 and 5." << endl;
        }
    } while (rating < 1 || rating > 5);

    do {
        cout << "Enter release year: ";
        cin >> releaseYear;
        cin.ignore(); // Clear input buffer

        if (releaseYear < 1800 || releaseYear > 2100) {
            cout << "Invalid release year. Please enter a year between 1800 and 2100." << endl;
        }
    } while (releaseYear < 1800 || releaseYear > 2100);

    do {
        cout << "Enter review (up to " << MAX_REVIEW_LENGTH << " characters): ";
        getline(cin, review);

        if (review.length() > MAX_REVIEW_LENGTH) {
            cout << "Review is too long. Please enter a review with a maximum of " << MAX_REVIEW_LENGTH << " characters." << endl;
        }
    } while (review.length() > MAX_REVIEW_LENGTH);

    Movie* newMovie = new Movie(name, rating, releaseYear, review);
    if (head == nullptr) {
        head = tail = newMovie;
    }
    else {
        tail->next = newMovie;
        tail = newMovie;
    }

    saveDataToFile(); // Save updated data to file
    DWORD end = GetTickCount(); // Stop measuring time
    DWORD elapsedTime = end - start; // Calculate elapsed time
    cout << "Time taken to add movie: " << elapsedTime << " ms" << endl;

    cout << "Movie Added successfully. Big O: O(1)" << endl;
}

void MovieList::removeMovie() {
    DWORD start = GetTickCount();
    if (head == nullptr) {
        cout << "Movie list is empty." << endl;
        return;
    }

    string name;
    cout << "Enter the name of the movie you want to remove: ";
    getline(cin, name);

    Movie* current = head;
    Movie* prev = nullptr;
    bool found = false;

    while (current != nullptr) {
        if (current->name == name) {
            found = true;
            if (prev == nullptr) {
                head = current->next;
                if (head == nullptr) {
                    tail = nullptr; // Update tail if list becomes empty
                }
            }
            else {
                prev->next = current->next;
                if (current->next == nullptr) {
                    tail = prev; // Update tail if last node is removed
                }
            }
            delete current;
            cout << "Movie removed successfully." << endl;
            break;
        }
        prev = current;
        current = current->next;
    }

    if (!found) {
        cout << "Movie not found in the list." << endl;
    }

    saveDataToFile(); // Save updated data to file
    DWORD end = GetTickCount(); // Stop measuring time
    DWORD elapsedTime = end - start; // Calculate elapsed time
    cout << "Time remove movie: " << elapsedTime << " ms" << endl;

    cout << "Movie removed successfully. Big O: O(n)" << endl;
}

void MovieList::modifyMovie() {
    DWORD start = GetTickCount();
    if (head == nullptr) {
        cout << "Movie list is empty." << endl;
        return;
    }

    string name;
    cout << "Enter the name of the movie you want to modify: ";
    getline(cin, name);

    Movie* current = head;
    bool found = false;

    while (current != nullptr) {
        if (current->name == name) {
            found = true;
            cout << "Enter new rating: ";
            cin >> current->rating;
            cin.ignore(); // Clear input buffer

            do {
                cout << "Enter new release year: ";
                cin >> current->releaseYear;
                cin.ignore(); // Clear input buffer

                if (current->releaseYear < 1800 || current->releaseYear > 2100) {
                    cout << "Invalid release year. Please enter a year between 1800 and 2100." << endl;
                }
            } while (current->releaseYear < 1800 || current->releaseYear > 2100);

            cout << "Enter new review: ";
            getline(cin, current->review);

            cout << "Movie modified successfully." << endl;
            break;
        }
        current = current->next;

    }

    if (!found) {
        cout << "Movie not found in the list." << endl;
    }

    saveDataToFile(); // Save updated data to file
    DWORD end = GetTickCount(); // Stop measuring time
    DWORD elapsedTime = end - start; // Calculate elapsed time
    cout << "Time taken to modify movie: " << elapsedTime << " ms" << endl;

    cout << "Movie Modified successfully. Big O: O(n)" << endl;
}


void MovieList::displayMovieList() {
    DWORD start = GetTickCount();
    sortMovies();
    int sortedCount = 0;
    Movie* current = head;

    if (current == nullptr) {
        cout << "Movie list is empty." << endl;
        return;
    }
   
    cout << "Movie List:" << endl;

    int count = 0; // Counter to limit the number of displayed movies
    const int MAX_DISPLAY = 100; // Maximum number of movies to display
    while (current != nullptr && count < MAX_DISPLAY) {
        cout << "Name: " << current->name << endl;
        cout << "Rating: " << current->rating << endl;
        cout << "Release Year: " << current->releaseYear << endl;
        cout << "Review: " << current->review << endl << endl;
        current = current->next;
        count++;
    }

    if (count >= MAX_DISPLAY) {
        cout << "Display limit reached. There may be more movies in the list." << endl;
    }

    DWORD end = GetTickCount(); // Stop measuring time
    DWORD elapsedTime = end - start; // Calculate elapsed time
    cout << "Time taken to display list: " << elapsedTime << " ms" << endl;

    cout << "List displayed successfully. Big O: O(n log n)" << endl;
}

// Function to merge two sorted linked lists
Movie* merge(Movie* left, Movie* right) {
    // If either of the lists is empty, return the other one
    if (left == nullptr) return right;
    if (right == nullptr) return left;

    // Merge the two lists recursively
    Movie* result;
    if (left->name <= right->name) {
        result = left;
        result->next = merge(left->next, right);
    }
    else {
        result = right;
        result->next = merge(left, right->next);
    }
    return result;
}

// Function to split the linked list into two halves
void split(Movie* source, Movie** front, Movie** back) {
    if (source == nullptr || source->next == nullptr) {
        *front = source;
        *back = nullptr;
        return;
    }

    Movie* slow = source;
    Movie* fast = source->next;

    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front = source;
    *back = slow->next;
    slow->next = nullptr;
}

// Merge sort for linked list
void mergeSort(Movie** headRef) {
    Movie* head = *headRef;
    if (head == nullptr || head->next == nullptr) return;

    Movie* front;
    Movie* back;
    split(head, &front, &back);

    mergeSort(&front);
    mergeSort(&back);

    *headRef = merge(front, back);
}

void MovieList::sortMovies() {
    mergeSort(&head);
}

void MovieList::displayMoviesInRange() {
    DWORD start = GetTickCount();
    double startYear, endYear;

    cout << "Enter start year: ";
    cin >> startYear;
    cout << "Enter end year: ";
    cin >> endYear;

    Movie* current = head;
    bool found = false;

    cout << "Movies released between " << startYear << " and " << endYear << ":" << endl << endl;
    while (current != nullptr) {
        if (current->releaseYear >= startYear && current->releaseYear <= endYear) {
            found = true;
            cout << "Name: " << current->name << endl;
            cout << "Rating: " << current->rating << endl;
            cout << "Release Year: " << current->releaseYear << endl;
            cout << "Review: " << current->review << endl << endl;
        }
        current = current->next;
    }

    if (!found) {
        cout << "No movies found in the specified range." << endl;
    }
    DWORD end = GetTickCount(); // Stop measuring time
    DWORD elapsedTime = end - start; // Calculate elapsed time
    cout << "Time taken to display movies in range: " << elapsedTime << " ms" << endl;

    cout << "Movies in range displayed successfully.Big O: O(n)" << endl;
}

void MovieList::searchMovie() {
    DWORD start = GetTickCount();
    string name;

    cout << "Enter the name of the movie you want to search: ";
    getline(cin, name);

    Movie* current = head;
    bool found = false;

    while (current != nullptr) {
        if (current->name == name) {
            found = true;
            cout << "Name: " << current->name << endl;
            cout << "Rating: " << current->rating << endl;
            cout << "Release Year: " << current->releaseYear << endl;
            cout << "Review: " << current->review << endl << endl;
            break;
        }
        current = current->next;
    }

    if (!found) {
        cout << "Movie not found in the list." << endl;
    }
    DWORD end = GetTickCount(); // Stop measuring time
    DWORD elapsedTime = end - start; // Calculate elapsed time
    cout << "Time taken to search movie: " << elapsedTime << " ms" << endl;
    cout << "Movie search completed successfully. Big O: O(n)" << endl;
}

void MovieList::saveDataToFile() {
    ofstream outfile("movies.txt");

    if (!outfile.is_open()) {
        cout << "Error opening file for writing." << endl;
        return;
    }

    for (Movie* current = head; current != nullptr; current = current->next) {
        outfile << current->name << "|" << current->rating << "|" << current->releaseYear << "|" << current->review << endl;
    }

    outfile.close();
}

void MovieList::loadDataFromFile() {
    ifstream inputFile("movies.txt"); 

    if (!inputFile.is_open()) {
        cout << "Error opening file for reading." << endl;
        return;
    }

    // Clear the existing linked list
    while (head != nullptr) {
        Movie* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr; // Reset tail pointer

    string name, review;
    int rating;
    double releaseYear;

    while (getline(inputFile, name, '|')) {
        inputFile >> rating;
        inputFile.ignore();
        inputFile >> releaseYear;
        inputFile.ignore();
        getline(inputFile, review);

        Movie* newMovie = new Movie(name, rating, releaseYear, review);
        if (head == nullptr) {
            head = tail = newMovie;
        }
        else {
            tail->next = newMovie;
            tail = newMovie;
        }
    }

    inputFile.close();
}
