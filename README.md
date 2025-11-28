# Playlist Management System (Group 38)

A C++ console-based application designed to efficiently manage music playlists and tracks using **Doubly Linked Lists**. This project simulates an MP3 player environment, allowing users to create playlists, manage songs, and simulate audio playback.

## 👥 Group Members

  * **MUHAMMAD ARIF AFIQ BIN KAMARULZAIDI** (22303865)
  * **MUHAMMAD HARITH ZIKRI BIN ZUBIR** (22303506)
  * **MUHAMMAD LUQMAN BIN RASIMI** (22303304)

-----

## 📖 Project Description

The Playlist Management System is designed to demonstrate the use of dynamic data structures in C++. It allows users to:

1.  **Manage Playlists:** Create, delete, and select specific playlists.
2.  **Manage Tracks:** Add, remove, sort, and search for songs within a playlist.
3.  **Simulate Playback:** "Play," "Pause," and skip to "Next/Previous" tracks.
4.  **Data Persistence:** All playlists and songs are saved to and loaded from `.txt` files automatically.

## 🛠 Technical Architecture

The system utilizes a modular design with **C++ Templates** and **Object-Oriented Programming**.

### Class Structure

  * **`TrackNode<T>`**: The fundamental data unit representing a song (Title, Artist, Duration). It acts as a node in the doubly linked list.
  * **`TrackList<T>`**: Manages the linked list of tracks. Handles operations like adding, removing, and sorting songs.
  * **`TrackPlayer<T>`**: Inherits from `TrackList`. Adds playback functionality (Play/Pause/Next/Back) and manages the "current" song pointer.
  * **`Playlist<T>`**: Manages a linked list of *Playlists*. It handles the creation of new playlist categories and writes the master list to `playlist_list.txt`.

### Data Storage

  * `playlist_list.txt`: Stores the index and names of all available playlists.
  * `[playlist_name].txt`: Stores the song data (Index, Title, Artist, Length) for a specific playlist.

-----

## 🚀 How to Compile and Run

This project was developed in a Linux/Unix environment (Google Colab) using `g++`. 

[Colab Notebook](https://colab.research.google.com/drive/13-SdK1clLQ4giPyyOUSeq69hwlTjFIRv?usp=sharing)

### Prerequisites

  * G++ Compiler
  * Standard C++ Libraries

### Compilation Command

Since the project relies on template classes and includes `.cpp` implementation files directly in `main.cpp`, compile using the following command:

```bash
g++ tracknode.h tracklist.h trackplayer.h playlist.h function.cpp main.cpp -o main.elf
```

### Running the Program

```bash
./main.elf
```

-----

## 🎮 User Guide (Menu Options)

Upon running the program, you will be presented with the **TRACK PLAYER V1.0** menu:

1.  **Show all song:** Displays every song from every available playlist in one master list.
2.  **Select playlist:** Load a specific playlist (e.g., "example1") to perform operations on it.
3.  **Show playlist content:** Displays songs strictly from the currently selected playlist.
4.  **Add song to playlist:** Input song details (Title, Artist, Length) to save into the current playlist.
5.  **Remove song from playlist:** Delete a song by its Index ID.
6.  **Create new playlist:** Generate a new `.txt` database for a new collection of songs.
7.  **Remove playlist:** Delete an entire playlist category.
8.  **Exit program:** Closes the application.

### Playback Controls

When you select **"Show all song"** or **"Show playlist content"**, you enter the Player Mode:

  * **1. Play:** Simulates playing the current track.
  * **2. Pause:** Simulates pausing the track.
  * **3. Next:** Move pointer to the next node in the list.
  * **4. Back:** Move pointer to the previous node in the list.
  * **5. Exit:** Return to the main menu.

-----

## 📂 File Manifest

| File | Description |
| :--- | :--- |
| `main.cpp` | The entry point of the program. Initializes objects and runs the main loop. |
| `function.cpp` | Contains the user interface logic (`handleInput`), menu display, and file reading functions. |
| `playlist.h` | Header for the Playlist manager class. |
| `trackplayer.h` | Header for the Player logic (Play/Pause controls). |
| `tracklist.h` | Header for the Doubly Linked List logic (Add/Remove nodes). |
| `tracknode.h` | Header defining the Song data structure. |
| `*.txt` | Text files used for storing persistent data (database). |

-----

## 📝 Scenarios Implemented

### Scenario 1: Creating a Playlist

  * **Actor:** Harith (User)
  * **Action:** Selects "Create new playlist", enters a name, and adds tracks.
  * **Outcome:** A new `.txt` file is generated, and the playlist is added to the master index.

### Scenario 2: Playing a Track

  * **Actor:** Arif (User)
  * **Action:** Selects a playlist, chooses a specific song index, and uses "Next/Back" controls.
  * **Outcome:** The system traverses the linked list and displays the current song's metadata.
