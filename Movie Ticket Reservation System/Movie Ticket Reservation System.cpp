#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// Class representing a Movie
class Movie {
private:
    string title;
    vector<string> showtimes;
    vector<int> availableSeats; // Number of seats available for each showtime

public:
    // Constructor to initialize movie details
    Movie(string title, vector<string> showtimes, vector<int> availableSeats)
        : title(title), showtimes(showtimes), availableSeats(availableSeats) {}

    string getTitle() const {
        return title;
    }

    vector<string> getShowtimes() const {
        return showtimes;
    }

    int getAvailableSeats(int index) const {
        return availableSeats[index];
    }

    // Method to book tickets and reduce available seats
    void bookTickets(int index, int numTickets) {
        if (availableSeats[index] >= numTickets) {
            availableSeats[index] -= numTickets;
        }
        else {
            cout << "Not enough seats available for this showtime!" << endl;
        }
    }

    // Method to display movie details and available seats
    void displayMovieDetails() const {
        cout << "Movie: " << title << endl;
        for (size_t i = 0; i < showtimes.size(); ++i) {
            cout << "\t" << i + 1 << ". " << showtimes[i]
                << " - " << availableSeats[i] << " seats available" << endl;
        }
    }
};

// Class representing a Reservation
class Reservation {
private:
    string movieTitle;
    string showtime;
    int numTickets;

public:
    // Constructor to initialize reservation details
    Reservation(string movieTitle, string showtime, int numTickets)
        : movieTitle(movieTitle), showtime(showtime), numTickets(numTickets) {}

    // Method to display reservation details
    void displayReservation() const {
        cout << "Reserved " << numTickets << " ticket(s) for "
            << movieTitle << " at " << showtime << endl;
    }
};

// Class managing the Theater System
class TheaterSystem {
private:
    vector<Movie> movies;
    vector<Reservation> reservations;

    // Method to load movies (you can extend this to load from a file)
    void loadMoviesFromFile() {
        // For simplicity, we're hardcoding the movies here
        vector<string> showtimes1 = { "10:00 AM", "2:00 PM", "6:00 PM" };
        vector<int> seats1 = { 50, 50, 50 };
        movies.push_back(Movie("The Matrix", showtimes1, seats1));

        vector<string> showtimes2 = { "11:00 AM", "3:00 PM", "7:00 PM" };
        vector<int> seats2 = { 30, 30, 30 };
        movies.push_back(Movie("Inception", showtimes2, seats2));

        vector<string> showtimes3 = { "12:00 PM", "4:00 PM", "8:00 PM" };
        vector<int> seats3 = { 40, 40, 40 };
        movies.push_back(Movie("Interstellar", showtimes3, seats3));
    }

    // Method to display all available movies
    void displayMovies() const {
        cout << "Available Movies:" << endl;
        for (size_t i = 0; i < movies.size(); ++i) {
            movies[i].displayMovieDetails();
        }
    }

    // Method to make a reservation
    void makeReservation() {
        string movieTitle;
        int movieChoice, showtimeChoice, numTickets;
        cout << "Enter the movie number to book tickets: ";
        cin >> movieChoice;
        if (movieChoice < 1 || movieChoice > movies.size()) {
            cout << "Invalid movie choice!" << endl;
            return;
        }

        Movie& selectedMovie = movies[movieChoice - 1];
        cout << "Choose a showtime:" << endl;
        vector<string> showtimes = selectedMovie.getShowtimes();
        for (size_t i = 0; i < showtimes.size(); ++i) {
            cout << "\t" << i + 1 << ". " << showtimes[i] << endl;
        }
        cout << "Enter the showtime number: ";
        cin >> showtimeChoice;
        if (showtimeChoice < 1 || showtimeChoice > showtimes.size()) {
            cout << "Invalid showtime choice!" << endl;
            return;
        }

        cout << "Enter number of tickets: ";
        cin >> numTickets;

        int availableSeats = selectedMovie.getAvailableSeats(showtimeChoice - 1);
        if (numTickets > availableSeats) {
            cout << "Not enough seats available!" << endl;
            return;
        }

        selectedMovie.bookTickets(showtimeChoice - 1, numTickets);
        Reservation reservation(selectedMovie.getTitle(), showtimes[showtimeChoice - 1], numTickets);
        reservations.push_back(reservation);
        cout << "Reservation Successful!" << endl;
    }

    // Method to view all reservations
    void viewReservations() const {
        if (reservations.empty()) {
            cout << "No reservations found." << endl;
            return;
        }
        cout << "Your Reservations:" << endl;
        for (const auto& res : reservations) {
            res.displayReservation();
        }
    }

public:
    // Constructor to load initial movies
    TheaterSystem() {
        loadMoviesFromFile(); // Load available movies
    }

    // Method to display the menu and handle user input
    void displayMenu() {
        int choice;
        do {
            cout << "\n--- Movie Ticket Reservation System ---" << endl;
            cout << "1. Display Available Movies" << endl;
            cout << "2. Make Reservation" << endl;
            cout << "3. View Reservations" << endl;
            cout << "4. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                displayMovies();
                break;
            case 2:
                makeReservation();
                break;
            case 3:
                viewReservations();
                break;
            case 4:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 4);
    }
};

// Main function to run the movie reservation system
int main() {
    TheaterSystem theaterSystem;
    theaterSystem.displayMenu();
    return 0;
}
