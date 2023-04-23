//
// Created by DELL ALIENWARE on 11/04/2023.
//

#ifndef PROJECT3_GAME_H
#define PROJECT3_GAME_H

#endif //PROJECT3_GAME_H
#pragma once

#include <string>
using namespace std;

struct Game{
    string title;
    bool handheld;
    int maxPlayers;
    bool multiplatform;
    bool online;
    string genre;
    bool licensed;
    string publisher;
    bool sequel;
    int reviewScore;
    float sales;
    float usedPrice;
    string releaseConsole;
    string ESRBrating;
    bool reRelease;
    int releaseYear;



    Game(string _title, bool _handheld, int _maxPlayers, bool _multiplatform, bool _online, string _genre, bool _licensed
    , string _publisher, bool _sequel, int _reviewScore, float _sales, float _usedPrice, string _releaseConsole, string _ESRBrating,
    bool _reRelease, int _releaseYear){
        title = _title;
         handheld = _handheld;
         maxPlayers = _maxPlayers;
         multiplatform = _multiplatform;
         online = _online;
         genre = _genre;
         licensed = _licensed;
         publisher = _publisher;
         sequel = _sequel;
         reviewScore = _reviewScore;
         sales = _sales;
         usedPrice = _usedPrice;
        releaseConsole = _releaseConsole;
        ESRBrating = _ESRBrating;
        reRelease = _reRelease;
        releaseYear = _releaseYear;

    }

    string returnTitle(){
        return title;
    }

    float returnSales(){
        return sales;
    }

    int returnRatings(){
        return reviewScore;
    }

    string returnConsole(){
        return releaseConsole;
    }

    int returnYear(){
        return releaseYear;
    }

    string returnGenre(){
        return genre;
    }

    int returnMaxPlayers(){
        return maxPlayers;
    }

    string returnPublisher(){
        return publisher;
    }


};


