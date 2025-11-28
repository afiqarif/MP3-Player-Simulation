#ifndef TRACKPLAYER_H
#define TRACKPLAYER_H
#include "tracknode.h"
#include "tracklist.h"
#include "playlist.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;


/*======================================================================
 *  TrackPlayer class: The class for the player.
 *======================================================================
 */

template <typename T>
class TrackPlayer : public TrackList<T> {
    private:
        TrackNode<T> *current;
    public:
        void songSelect(TrackList<T>& tracklist);
        void displayCurrent();
        void play();
        void pause();
        void next();
        void back();
};


/*======================================================================
 *  Method to select song from the linked list of class TrackList.
 *======================================================================
 */

template <typename T>
void TrackPlayer<T>::songSelect(TrackList<T>& tracklist) {
    cout << "\n";
    cout << left << setw(7) << "Index"
         << setw(15) << "Name"
         << setw(15) << "Artist"
         << setw(4) << "Length"
         << endl;
    int searchIndex;
    while(true) {
        tracklist.displayPlaylist();
        cout << "Choose song: ";
        cin >> searchIndex;

        TrackNode<T> *nodePtr = tracklist.getHead();
        while(nodePtr != nullptr) {
            if(nodePtr->getIndex() == searchIndex) {
                break;
            }
            nodePtr = nodePtr->getNext();
        }

        if(nodePtr == nullptr) {
            cout << "Song is not found. Search again." << endl;
            continue;
        }
        break;
    }

    cout << "\n";
    current = tracklist.searchTrack(searchIndex);
}


/*=================================================
 *  Method to display the current playing song.
 *=================================================
 */

template <typename T>
void TrackPlayer<T>::displayCurrent() {
    cout << "\nCurrently playing: " << current->getTitle() << endl;
    cout << "Artist: " << current->getArtist() << endl;
    cout << "Length: ";
    current->calcHourMinuteSecond();
    cout << "\n\n";
}


/*===========================================
 *  Method to play, pause, next, and back.
 *===========================================
 */

//  Play the current song.
template <typename T>
void TrackPlayer<T>::play() {
    cout << "\nPlaying: " << current->getTitle() << endl;
}

//  Pause the current song.
template <typename T>
void TrackPlayer<T>::pause() {
    cout << "\nPaused: " << current->getTitle() << endl;
}

//  Next song.
template <typename T>
void TrackPlayer<T>::next() {
    TrackNode<T> *nodePtr = current->getNext();
    if(nodePtr == nullptr) {
        cout << "\nEnd of playlist." << endl;
    } else {
        current = nodePtr;
    }
}

//  Previous song.
template <typename T>
void TrackPlayer<T>::back() {
    TrackNode<T> *nodePtr = current->getBack();
    if(nodePtr == nullptr) {
        cout << "\nNo previous song." << endl;
    } else {
        current = nodePtr;
    }
}


#endif
