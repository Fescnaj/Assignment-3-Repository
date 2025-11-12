//Programmer: Feliciano Escalante Najera (2941390)


#include <iostream>
#include <string>
#include <limits>

using namespace std;

//Node Structure for every song.
struct Song {
    string title;
    Song* next;
    Song* prev;

    Song(const string& t) : title(t), next(nullptr), prev(nullptr) {}
};

//The class gets declared as a circular double linked list. 
class MusicPlaylist {
private:
    Song* head;
    Song* current;

public:
    MusicPlaylist() : head(nullptr), current(nullptr) {}

    //Function to add a song to the end of the playlist. 
    void addSong(const string& title) {
        Song* newSong = new Song(title);
        if (!head) {
            head = newSong;
            head->next = head;
            head->prev = head;
            current = head;
        } else {
            Song* tail = head->prev;
            tail->next = newSong;
            newSong->prev = tail;
            newSong->next = head;
            head->prev = newSong;
        }
        cout << "Added: " << title << "." << endl;
    }

    //Displays all the songs in the playlist.
    void displayPlaylist() const {
        if (!head) {
            cout << endl;
            cout << "Playlist is empty. " << endl;
            return;
        }
        Song* temp = head;
        cout << endl;
        cout << "Playlist: " << endl;
        do {
            cout << " - " << temp->title << endl;
            temp = temp->next;
        } while (temp != head);
    }

    //This plays the current song.
    void playCurrent() const {
        if (!current) {
            cout << endl;
            cout << "No song to play. " << endl;
            return;
        }
        cout << endl;
        cout << "Now playing: " << current-> title << endl;
    }

    //This moves to the next song.
    void nextSong() {
        if (current) {
            current = current->next;
            playCurrent();
        }
    }

    //This goes to the previous song.
    void prevSong() {
        if (current) {
            current = current->prev;
            playCurrent();
        }
    }

    //Destructor to free up memory/storage.
    ~MusicPlaylist() {
        if (!head) return;
        Song* temp = head;
        do {
            Song* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        } while (temp != head);
        head = nullptr;
        current = nullptr;
    }
};

//Prevents infinite loops and deals with invalid user input.
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    MusicPlaylist playlist;
    int choice;
    string title;


//Prints out all menu options.
    do {
        cout << endl;
        cout << "Music Playlist Menu: " << endl;
        cout << endl;
        cout << "1. Add Song. " << endl;
        cout << "2. Display Playlist. " << endl;
        cout << "3. Play Current Song. " << endl;
        cout << "4. Next Song. " << endl;
        cout << "5. Previous Song. " << endl;
        cout << "0. Exit. " << endl;
        cout << endl;
        cout << "Enter choice: ";

//Validates user input.
        if (!(cin >> choice)) {
            cout << endl;
            cout << "Invalid input. Please enter a number (0-5)." << endl;
            clearInputBuffer();
            continue;
        }

        clearInputBuffer();

//Deals with the input from the user per prompt. 
        switch (choice) {
            case 1:
                cout << "Enter song title: ";
                getline(cin, title);
                playlist.addSong(title);
                break;
            case 2:
                playlist.displayPlaylist();
                break;
            case 3:
                playlist.playCurrent();
                break;
            case 4:
                playlist.nextSong();
                break;
            case 5:
                playlist.prevSong();
                break;
            case 0:
                cout << "Exiting. " << endl;
                break;
            default:
                cout << "Invalid input. " << endl;
        }
        //Keeps it running until inputted option to quit.
    } while (choice != 0);

    return 0;
}
