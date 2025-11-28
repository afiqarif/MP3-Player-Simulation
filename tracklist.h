#ifndef TRACKLIST_H
#define TRACKLIST_H
#include "tracknode.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;


/*==================================================================
 *  TrackList class: The class for linked list that store tracks.
 *==================================================================
 */

template <typename T>
class TrackList {
    private:
        TrackNode<T> *head;
        TrackNode<T> *tail;
    public:
        TrackList();
        ~TrackList();
        void clearList();
        void addTrack(int newIndex, T newTitle, T newArtist, int newLength);
        void addTrackSort(int newIndex, T newTitle, T newArtist, int newLength);
        TrackNode<T> *searchTrack(int searchIndex);
        void removeTrack(int index);
        void displayPlaylist();
        void showAllTrack(T listName, int& allIndex);
        TrackNode<T> *getHead() const;
        TrackNode<T> *getTail() const;
        void writePlaylistSong(TrackList<T>& tracklist, T selectedPlaylist);
};


/*==================================================
 *  Constructor and destructo of class TrackList.
 *==================================================
 */

template <typename T>
TrackList<T>::TrackList() {
    head = nullptr;
    tail = nullptr;
}

template <typename T>
TrackList<T>::~TrackList() {
    clearList();
}


/*=======================================================
 *  Method to clear the linked list of class TrackList.
 *=======================================================
 */

template <typename T>
void TrackList<T>::clearList() {
    TrackNode<T> *nodePtr = head;
    TrackNode<T> *nextNode;
    while(nodePtr != nullptr) {
        nextNode = nodePtr->getNext();
        delete nodePtr;
        nodePtr = nextNode;
    }
    head = nullptr;
    tail = nullptr;
}


/*=================================================================
 *  Method to add track to the linked list of class TrackList.
 *=================================================================
 */

template <typename T>
void TrackList<T>::addTrack(int newIndex, T newTitle, T newArtist, int newLength) {
    TrackNode<T> *nodePtr;
    TrackNode<T> *newNode = new TrackNode<T>;
    newNode->setTrack(newIndex, newTitle, newArtist, newLength);
    newNode->setNext(nullptr);
    newNode->setBack(nullptr);

    if(!head) {
        head = newNode;
        tail = newNode;
    } else {
        nodePtr = tail;
        tail = newNode;
        nodePtr->setNext(newNode);
        newNode->setBack(nodePtr);
    }
}


/*===========================================================================================
 *  Method to add track to the linked list of class TrackList in sorted order by index.
 *===========================================================================================
 */

template <typename T>
void TrackList<T>::addTrackSort(int newIndex, T newTitle, T newArtist, int newLength) {
    TrackNode<T> *nodePtr;
    TrackNode<T> *newNode = new TrackNode<T>;
    newNode->setTrack(newIndex, newTitle, newArtist, newLength);
    newNode->setNext(nullptr);
    newNode->setBack(nullptr);

    if(!head) {
        head = newNode;
        tail = newNode;
    } else {
        nodePtr = head;
        while(nodePtr != nullptr && nodePtr->getIndex() < newIndex ){
            nodePtr = nodePtr->getNext();
        }

        if(nodePtr == head) {
            head = newNode;
            newNode->setNext(nodePtr);
            nodePtr->setBack(newNode);
        } else if(nodePtr == nullptr) {
            nodePtr = tail;
            tail = newNode;
            nodePtr->setNext(newNode);
            newNode->setBack(nodePtr);
        } else {
            TrackNode<T> *temp;
            newNode->setNext(nodePtr->getNext());
            temp = nodePtr->getNext();
            temp->setBack(newNode);
            nodePtr->setNext(newNode);
            newNode->setBack(nodePtr);
        }
    }
}


/*=============================================================================
 *  Method to search track in the linked list of class TrackList by index.
 *=============================================================================
 */

template <typename T>
TrackNode<T>* TrackList<T>::searchTrack(int searchIndex) {
    TrackNode<T> *nodePtr = head;
    while(nodePtr != nullptr) {
        if(nodePtr->getIndex() == searchIndex) {
            return nodePtr;
        }
        nodePtr = nodePtr->getNext();
    }

    return nodePtr;
}


/*======================================================================
 *  Method to remove track from the linked list of class TrackList.
 *======================================================================
 */

template <typename T>
void TrackList<T>::removeTrack(int index) {
    TrackNode<T> *nodePtr = head;
    TrackNode<T> *nextNode;
    while(nodePtr != nullptr) {
        if(nodePtr != head && nodePtr != tail && nodePtr->getIndex() == index) {
            TrackNode<T> *temp;
            temp = nodePtr->getNext();
            temp->setBack(nodePtr->getBack());
            temp = nodePtr->getBack();
            temp->setNext(nodePtr->getNext());
            delete nodePtr;
            return;
        } else if(nodePtr == tail && nodePtr->getIndex() == index) {
            tail = tail->getBack();
            tail->setNext(nullptr);
            delete nodePtr;
            return;
        } else if(nodePtr == head && nodePtr->getIndex() == index) {
            head = head->getNext();
            head->setBack(nullptr);
            delete nodePtr;
            return;
        }

        nodePtr = nodePtr->getNext();
    }
}


/*====================================================================================
 *  Method to display the linked list of class TrackList.
 *====================================================================================
 */

template <typename T>
void TrackList<T>::displayPlaylist() {
    TrackNode<T> *nodePtr = head;
    while(nodePtr != nullptr) {
        cout << left << setw(7) << nodePtr->getIndex()
             << setw(15) << nodePtr->getTitle()
             << setw(15) << nodePtr->getArtist();
             nodePtr->calcHourMinuteSecond();
        nodePtr = nodePtr->getNext();
    }
    cout << "\n\n";
}

/*=================================================
 *  Method to display all track from a text file.
 *=================================================
 */

template <typename T>
void TrackList<T>::showAllTrack(T listName, int& allIndex) {
    TrackNode<T> *nodePtr = head;
    fstream library;
    library.open(listName + ".txt", ios::in);

    if(!library) {
        cout << "Failed to open file." << endl;
        return;
    } else {
        T title, artist;
        int index, length;
        char tempComma;
        while(library >> index) {
            library.get(tempComma);
            getline(library, title, ',');
            getline(library, artist, ',');
            library >> length;
            addTrack(allIndex, title, artist, length);
            allIndex++;
        }
    }
    library.close();
}


/*=============================================================================
 *  Method to write the linked list of class TrackList into a text file.
 *=============================================================================
 */

template <typename T>
void TrackList<T>::writePlaylistSong(TrackList<T>& tracklist, T selectedPlaylist) {
    fstream library;
    selectedPlaylist = selectedPlaylist + ".txt";
    library.open(selectedPlaylist, ios::out);
    TrackNode<T> *nodePtr = tracklist.getHead();
    while(nodePtr != nullptr) {
        library << nodePtr->getIndex() << ","
                << nodePtr->getTitle() << ","
                << nodePtr->getArtist() << ","
                << nodePtr->getLength() << endl;
        nodePtr = nodePtr->getNext();
    }
    library.close();
}


/*========================================================
 *  Accessor and mutator functions of class TrackList.
 *========================================================
 */

template <typename T>
TrackNode<T>* TrackList<T>::getHead() const {
    return head;
}

template <typename T>
TrackNode<T>* TrackList<T>::getTail() const {
    return tail;
}

#endif
