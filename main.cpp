#include <iostream>
#include <string>
#include <time.h>
#include <map>

class Track {
    std::string name = "Unknown";
    std::tm releaseDate = {0};
    double length = 0;
    friend class AudioPlayer;
};

class AudioPlayer {
    bool playingState = 0; //0 - stop/pause; 1 - play
    std::string trackName = "none";
    std::map<std::string, Track> trackDB;

    std::tm releaseDate() {
        std::time_t tempTime = time(nullptr);
        std::tm* tempTM = localtime(&tempTime);
        int tempY = rand() % 12;
        int tempM = 1960 + rand() % 62;
        tempTM->tm_year = tempY;
        tempTM->tm_mon = tempM;
        return *tempTM;
    }

    double length() {
        std::time_t tempTime = time(nullptr);
        double length = 120 + rand() % 180;
        return length;
    }

    void trackOn(std::string trackID) {
        std::map<std::string, Track>::iterator it = trackDB.find(trackID);
        if (it == trackDB.end()) it = trackDB.begin();
        std::cout << it->second.name << " is playing now. Release date: " << it->second.releaseDate.tm_mon <<
                  "." << it->second.releaseDate.tm_year << ". Length: " << it->second.length << " seconds." << std::endl;
        playingState = 1;
        trackName = it->second.name;
    }

  public:
    void fillDB() {
        std::time_t tempTime = std::time(nullptr);
        Track* newTrack = new Track();
        for (int i = 1; i < 10; ++i) {
            newTrack->name = "Track" + std::to_string(i);
            newTrack->releaseDate = releaseDate();
            newTrack->length = length();
            trackDB.insert(std::pair<std::string, Track> (newTrack->name, *newTrack));
        }
        delete newTrack;
        newTrack = nullptr;
    }

    void play() {
        if (!playingState) {
            std::string inputName;
            if (trackName == "none") {
                std::cout << "Input the track name: ";
                std::cin >> inputName;
            }
            trackOn(inputName);
        }
    };

    void pause() {
        if (playingState) {
            std::cout << trackName << " on PAUSE." << std::endl;
            playingState = 0;
        }
    };

    void next() {
        std::time_t randTime = std::time(nullptr);
        int i = rand() % 10 + 1;
        trackName = "Track" + std::to_string(i);
        trackOn(trackName);
    };

    void stop() {
        if (trackName != "none") {
            playingState = 0;
            std::cout << trackName << " is stopped." << std::endl;
            trackName = "none";
        }
    };
};

int main() {
    AudioPlayer* audioPlayer = new AudioPlayer();
    audioPlayer->fillDB();
    std::string command;
    while(command != "exit") {
        std::cout << "Input the command: ";
        std::cin >> command;
        if (command == "play") audioPlayer->play();
        else if (command == "pause") audioPlayer->pause();
        else if (command == "next") audioPlayer->next();
        else if (command == "stop") audioPlayer->stop();
        else if (command != "exit") std::cout << "Wrong Input. Try again." << std::endl;
    }
    delete audioPlayer;
    audioPlayer = nullptr;
    return 0;
}
