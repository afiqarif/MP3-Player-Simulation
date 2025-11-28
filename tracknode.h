#ifndef TRACKNODE_H
#define TRACKNODE_H
using namespace std;
#include <iostream>
#include <iomanip>

using namespace std;


/*=============================================================================
 *  TrackNode class: Act as the 'container' for nodes in the linked list.
 *=============================================================================
 */

template <typename T>
class TrackNode {
    private:
        int index;
        T title;
        T artist;
        int length;
        TrackNode<T> *next;
        TrackNode<T> *back;
    public:
        void setNext(TrackNode<T>* nodePtr);
        void setNext(nullptr_t nullp);
        void setBack(TrackNode<T>* nodePtr);
        void setBack(nullptr_t nullp);
        void setTrack(int index, T title, T artist, int length);
        void calcHourMinuteSecond();
        int getIndex() const;
        T getTitle() const;
        T getArtist() const;
        int getLength() const;
        TrackNode<T> *getNext();
        TrackNode<T> *getBack();
};


/*=======================================================
 *  List of accessor and mutator functions of TrackNode.
 *=======================================================
 */

//  Set next node pointer.
template <typename T>
void TrackNode<T>::setNext(TrackNode<T>* nodePtr) {
    next = nodePtr;
}

//  Overloading function to set next node pointer to nullptr.
template <typename T>
void TrackNode<T>::setNext(std::nullptr_t nullp) {
    next = nullp;
}

//  Set back node pointer.
template <typename T>
void TrackNode<T>::setBack(TrackNode<T>* nodePtr) {
    back = nodePtr;
}

//  Overloading function to set back node pointer to nullptr.
template <typename T>
void TrackNode<T>::setBack(std::nullptr_t nullp) {
    back = nullp;
}

//  Set track information.
template <typename T>
void TrackNode<T>::setTrack(int index, T title, T artist, int length) {
    this->index = index;
    this->title = title;
    this->artist = artist;
    this->length = length;
}

//  Get the index.
template <typename T>
int TrackNode<T>::getIndex() const {
    return index;
}

//  Get the title.
template <typename T>
T TrackNode<T>::getTitle() const {
    return title;
}

//  Get the artist.
template <typename T>
T TrackNode<T>::getArtist() const {
    return artist;
}

//  Get the length.
template <typename T>
int TrackNode<T>::getLength() const {
    return length;
}

//  Get the next node pointer.
template <typename T>
TrackNode<T>* TrackNode<T>::getNext() {
    return next;
}

//  Get the back node pointer.
template <typename T>
TrackNode<T>* TrackNode<T>::getBack() {
    return back;
}

/*=============================================================================
 *  Function to convert the length (in second) into hour:minute:second format.
 *=============================================================================
 */

template <typename T>
void TrackNode<T>::calcHourMinuteSecond() {
    int hour = length / 3600;
    int minute = (length / 60) - (hour * 60);
    int second = length - (hour * 3600) - (minute * 60);
    if(minute >= 60) {
        cout << hour << ":"
             << right << setw(2) << setfill('0')
             << minute << ":" << setw(2) << second << setfill(' ') << endl;
    } else {
        cout << right << setw(2) << setfill('0')
             << minute << ":" << setw(2) << second << setfill(' ') << endl;
    }
}

#endif
