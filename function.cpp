#include "tracknode.h"
#include "tracklist.h"
#include "trackplayer.h"
#include "playlist.h"
#include <iostream>
#include <fstream>

using namespace std;


/*====================================================================================
 *  Function to initially read the playlist's list file into the Playlist linked list.
 *====================================================================================
 */

template <typename T>
void readPlaylistList(Playlist<T>& playlist) {
    fstream library;
    library.open("playlist_list.txt", ios::in);
    if(!library) {
        cout << "Failed to open file." << endl;
        return;
    } else {
        T listName;
        int index;
        char tempComma;
        while(library >> index) {
            library.get(tempComma);
            getline(library, listName);
            playlist.createPlaylist(listName, index);
        }
    }
    library.close();
}


/*===========================================================================================
 *  Function to initially read the selected playlist file into the TrackList linked list
 *===========================================================================================
 */

template <typename T>
void readPlaylistSong(TrackList<T>& tracklist, T selectedPlaylist) {
    fstream library;
    selectedPlaylist = selectedPlaylist + ".txt";
    library.open(selectedPlaylist, ios::in);
    if(!library) {
        cout << "Failed to open file." << endl;
        return;
    } else {
        library.seekg(0, ios::end);
        if(library.tellg() == 0) {
            cout << "No songs in playlist." << endl;
            library.close();
            return;
        }
        library.seekg(0, ios::beg);
        T title, artist;
        int index, length;
        char tempComma;
        while(library >> index) {
            library.get(tempComma);
            getline(library, title, ',');
            getline(library, artist, ',');
            library >> length;
            tracklist.addTrack(index, title, artist, length);
        }
    }
    library.close();
}


/*======================================================================
 *  Function to display the player for the currently playing song.
 *======================================================================
 */

template <typename T>
bool showPlayer(TrackPlayer<T>& player) {
    int choice;
    player.displayCurrent();
    cout << "\n1. Play\n"
        << "2. Pause\n"
        << "3. Next\n"
        << "4. Back\n"
        << "5. Exit\n";
    cout << "Choice: ";
    cin >> choice;
    if(choice == 1) {
        player.play();
        return false;
    } else if(choice == 2) {
        player.pause();
        return false;
    } else if(choice == 3) {
        player.next();
        return false;
    } else if(choice == 4) {
        player.back();
        return false;
    } else {
        cout << "\n\n";
        return true;
    }
}


/*=================================================
 *  Function that handle all input from users.
 *=================================================
 */

template <typename T>
void handleInput(TrackPlayer<T>& player,TrackList<T>& tracklist, Playlist<T>& playlist, bool& exitFlag) {
    cout << "TRACK PLAYER V1.0" << endl;
    cout << "1. Show all song\n"
         << "2. Select playlist\n"
         << "3. Show playlist content\n"
         << "4. Add song to playlist\n"
         << "5. Remove song from playlist\n"
         << "6. Create new playlist\n"
         << "7. Remove playlist\n"
         << "8. Exit program\n";

    int choice;
    static T selectedPlaylist;
    static bool checkSelected = false;

    if(checkSelected == false) {
        cout << "\nSelected playlist: none selected. (Please select a playlist first)" << endl;
    } else {
        cout << "\nSelected playlist: " << selectedPlaylist << "\n\n";
    }

    cout << "Choice: ";
    cin >> choice;
    cout << "\n";

    try {
        if(choice == 1) {
            playlist.allTrackPlaylist(tracklist);
            player.songSelect(tracklist);
            while(true) {
                bool quit = showPlayer(player);
                if(quit)
                    break;
            }
        } else if(choice == 2) {
            playlist << cout;
            playlist.playlistSelect(selectedPlaylist, checkSelected);
            tracklist.clearList();
            readPlaylistSong(tracklist, selectedPlaylist);
        } else if(choice == 3) {
            player.songSelect(tracklist);
            while(true) {
                bool quit = showPlayer(player);
                if(quit)
                    break;
            }
        } else if(choice == 4) {
            if(checkSelected == false) {
                cout << "No playlist selected. Select a playlist first." << endl;
                return;
            }
            tracklist.displayPlaylist();
            playlist.editPlaylist(tracklist);
            tracklist.writePlaylistSong(tracklist, selectedPlaylist);
        }  else if(choice == 5) {
            int searchIndex;
            if(checkSelected == false) {
                cout << "No playlist selected. Select a playlist first." << endl;
                return;
            }
            tracklist.displayPlaylist();
            cout << "\nSearch index: ";
            cin >> searchIndex;
            tracklist.removeTrack(searchIndex);
            cout << "\n\nTrack deleted\n\n";
            playlist.writePlaylist(tracklist);
            tracklist.writePlaylistSong(tracklist, selectedPlaylist);
        } else if(choice == 6) {
            T listName;
            int index;
            playlist << cout;
            cout << "Playlist name: ";
            cin.ignore();
            getline(cin, listName);
            cout << "Playlist index: ";
            cin >> index;
            playlist.createPlaylist(listName, index);
            playlist.writePlaylist(tracklist);
            tracklist.writePlaylistSong(tracklist, listName);
        } else if(choice == 7) {
            int index;
            playlist << cout;
            cout << "Playlist index: ";
            cin >> index;
            if(selectedPlaylist == playlist.searchPlaylist(index))
                checkSelected = false;
            playlist.removePlaylist(index);
            cout << "\n\nPlaylist deleted\n\n";
            playlist.writePlaylist(tracklist);
        } else if(choice == 8) {
            exitFlag = true;
        } else {
            throw "Invalid choice. Please try again.";
        }
    } catch(const char* error) {
        cout << error <<"\n\n";
    }
}
