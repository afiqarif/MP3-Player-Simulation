#include "tracknode.h"
#include "tracklist.h"
#include "trackplayer.h"
#include "playlist.h"
#include "function.cpp"
#include <iostream>
#include <fstream>

int main() {
    TrackPlayer<string> player;     //  Instantiate a player object.
    TrackList<string> tracklist;    //  Instantiate a song list linked list.
    Playlist<string> playlist;      //  Instantiate a playlist list linked list.
    readPlaylistList(playlist);     //  Read the playlist list file

    while(true) {
        bool exitFlag = false;   //  Flag that determine the exit condition.
        handleInput(player, tracklist, playlist, exitFlag); //  Handle all process.

        //  Exit condition.
        if(exitFlag) {
            cout << "Program closed." << endl;
            break;
        }
    }

    return 0;
}
