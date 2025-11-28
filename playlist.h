#ifndef PLAYLIST_H
#define PLAYLIST_H
#include "tracknode.h"
#include "tracklist.h"
#include "trackplayer.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;


/*=======================================================================
 *  Playlist class: The class for linked list that store playlists.
 *=======================================================================
 */

template <typename T>
class Playlist {
    private:
        struct TrackPlaylist {
            T listName;
            int index;
            TrackPlaylist *next;
            TrackPlaylist *back;
        };
        TrackPlaylist *head;
        TrackPlaylist *tail;
    public:
        Playlist();
        ~Playlist();
        void playlistSelect(T& selectedPlaylist, bool& checkSelected);
        T searchPlaylist(int index);
        void createPlaylist(T listName, int index);
        void removePlaylist(int index);
        void editPlaylist(TrackList<T>& tracklist);
        void allTrackPlaylist(TrackList<T>& tracklist);
        void writePlaylist(TrackList<T>& tracklist);
        ostream& operator<<(ostream& cout);
};


/*================================================
 *  Constructor and destructor of class Playlist.
 *================================================
 */

template <typename T>
Playlist<T>::Playlist() {
    head = nullptr;
    tail = nullptr;
}

template <typename T>
Playlist<T>::~Playlist() {
    TrackPlaylist *nodePtr = head;
    TrackPlaylist *nextNode;
    while(nodePtr != nullptr) {
        nextNode = nodePtr->next;
        delete nodePtr;
        nodePtr = nextNode;
    }
}


/*======================================================================
 *  Method to select playlist from the linked list of class Playlist.
 *======================================================================
 */

template <typename T>
void Playlist<T>::playlistSelect(T& selectedPlaylist, bool& checkSelected) {
    int index;
    cout << "Choose playlist index: ";
    cin >> index;
    selectedPlaylist = this->searchPlaylist(index);
    if(checkSelected == false)
        checkSelected = true;
    cout << "\n\n";
}


/*================================================================================
 *  Method to search playlist in the linked list of class Playlist by index.
 *================================================================================
 */

template <typename T>
T Playlist<T>::searchPlaylist(int index) {
    TrackPlaylist *nodePtr = head;
    while(nodePtr != nullptr) {
        if(nodePtr->index == index) {
            return nodePtr->listName;
        } else if(nodePtr == tail && nodePtr->index == index) {
            return nodePtr->listName;
        }
        nodePtr = nodePtr->next;
    }

    if(nodePtr == nullptr) {
        cout << "Playlist is not found. Search again." << endl;
        cout << "Index: ";
        cin >> index;
        return searchPlaylist(index);
    }

    return nodePtr->listName;
}


/*=======================================================================================================
 *  Method to add or create new playlist to the linked list of class Playlist in sorted order by index.
 *=======================================================================================================
 */

template <typename T>
void Playlist<T>::createPlaylist(T listName, int index) {
    TrackPlaylist* nodePtr;
    TrackPlaylist* newNode = new TrackPlaylist;
    newNode->listName = listName;
    newNode->index = index;
    newNode->next = nullptr;
    newNode->back = nullptr;

    if(!head) {
        head = newNode;
        tail = newNode;
    } else {
        nodePtr = head;
        while(nodePtr != nullptr && nodePtr->index < index) {
            nodePtr = nodePtr->next;
            if(nodePtr != nullptr && nodePtr->index == index) {
                cout << "Index taken." << endl;
                return;
            }
        }

        if(nodePtr == head) {
            head = newNode;
            newNode->next = nodePtr;
            nodePtr->back = newNode;
        } else if(nodePtr == nullptr) {
            nodePtr = tail;
            tail = newNode;
            nodePtr->next = newNode;
            newNode->back = nodePtr;
        } else {
            nodePtr->next->back = newNode;
            newNode->next = nodePtr->next;
            nodePtr->next = newNode;
            newNode->back = nodePtr;
        }
    }
}


/*=============================================================================
 *  Method to remove or delete playlist from the linked list of class Playlist.
 *=============================================================================
 *
 */

template <typename T>
void Playlist<T>::removePlaylist(int index) {
    TrackPlaylist *nodePtr = head;
    while(nodePtr != nullptr) {
        if(nodePtr == head && nodePtr->index == index) {
            head = head->next;
            delete nodePtr;
            return;
        } else if(nodePtr == tail && nodePtr->index == index) {
            tail = tail->back;
            tail->next = nullptr;
            delete nodePtr;
            return;
        } else if(nodePtr->index == index && (nodePtr != head && nodePtr != tail)) {
            nodePtr->back->next = nodePtr->next;
            nodePtr->next->back = nodePtr->back;
            delete nodePtr;
            return;
        }
        nodePtr = nodePtr->next;
    }
}


/*===========================================================================================
 *  Method to edit song into a selected playlist the linked list of class TrackList.
 *===========================================================================================
 */

template <typename T>
void Playlist<T>::editPlaylist(TrackList<T>& tracklist) {
    T title, artist;
    int index, length;
    bool continueFlag = false;
    TrackNode<T> *nodePtr = tracklist.getHead();
    bool emptyList = false;
    if(nodePtr == nullptr)
        emptyList = true;

    while(true) {
        if(emptyList == true) {
            cout << "No song in playlist." << endl;
            cout << "Index: ";
            cin >> index;
            break;
        } else if(nodePtr == nullptr && emptyList == false)
            break;

        cout << "Index: ";
        cin >> index;
        emptyList = false;

        while(nodePtr != nullptr) {
            if(nodePtr->getIndex() == index) {
                cout << "Index taken. Enter again." << endl;
                continueFlag = true;
                break;
            }
            nodePtr = nodePtr->getNext();
        }
        if(continueFlag == true) {
            nodePtr = tracklist.getHead();
            continueFlag = false;
        }

        if(nodePtr == nullptr)
            break;
    }

    cin.ignore();
    cout << "Title: ";
    getline(cin, title) ;
    cout << "Artist: ";
    getline(cin, artist);
    cout << "Length: ";
    cin >> length;
    tracklist.addTrackSort(index, title, artist, length);
}

/*=================================================
 *  Method to show all track in all playlist.
 *=================================================
 */

template <typename T>
void Playlist<T>::allTrackPlaylist(TrackList<T>& tracklist) {
    TrackPlaylist *nodePtr = head;
    if(tracklist.getHead() != nullptr)
        tracklist.clearList();
    int allIndex = 0;
    while(nodePtr != nullptr) {
        tracklist.showAllTrack(nodePtr->listName, allIndex);
        nodePtr = nodePtr->next;
    }
}


/*=============================================================================
 *  Method to write the linked list of class Playlist into a text file.
 *=============================================================================
 */

template <typename T>
void Playlist<T>::writePlaylist(TrackList<T>& tracklist) {
    fstream library;
    library.open("playlist_list.txt", ios::out);
    TrackPlaylist *nodePtr = head;
    while(nodePtr != nullptr) {
        library << nodePtr->index << "," << nodePtr->listName << endl;
        nodePtr = nodePtr->next;
    }
    library.close();
}


/*===============================================================================
 *  Overloaded operator function to display the linked list of class Playlist.
 *===============================================================================
 */

template <typename T>
ostream& Playlist<T>::operator<<(ostream& cout) {
    TrackPlaylist *nodePtr = head;
    cout << left << setw(7) << "Index" << setw(15) << "Playlist Name" << endl;
    while(nodePtr != nullptr) {
        cout << left << setw(7) << nodePtr->index
             << setw(15) << nodePtr->listName
             << endl;
        nodePtr = nodePtr->next;
    }
    cout << "\n\n";
    return cout;
}

#endif
