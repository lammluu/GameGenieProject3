#include "color.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <iomanip>
#include "game.h"
#include <algorithm>
#include <chrono>
#include <regex>
#include <set>

using namespace std;
using namespace std::chrono;


void extractDataFromFile(vector<Game>& listOfAllGames){
    string line;
    ifstream File("videogames.csv");


    string title;

    bool handheld;
    string tempHandheld;

    int maxPlayers;
    string tempMaxPlayers;

    bool multiplatform;
    string tempMulti;

    bool online;
    string tempOnline;

    string genre;

    bool licensed;
    string tempLicensed;

    string publisher;

    bool sequel;
    string tempSequel;

    int reviewScore;
    string tempScore;

    float sales;
    string tempSales;

    float usedPrice;
    string tempUsedPrice;

    string releaseConsole;

    string ESRBrating;

    bool reRelease;
    string tempReRelease;

    int releaseYear;
    string tempYear;


    if(File.is_open()){
        getline(File, line);


        while(getline(File, line)) {
            istringstream stream(line);

            getline(stream, title, '%');
            getline(stream, tempHandheld, '%');
            getline(stream, tempMaxPlayers, '%');
            getline(stream, tempMulti, '%');
            getline(stream, tempOnline, '%');
            getline(stream, genre, '%');
            getline(stream, tempLicensed, '%');
            getline(stream, publisher, '%');
            getline(stream, tempSequel, '%');
            getline(stream, tempScore, '%');
            getline(stream, tempSales, '%');
            getline(stream, tempUsedPrice, '%');
            getline(stream, releaseConsole, '%');
            getline(stream, ESRBrating, '%');
            getline(stream, tempReRelease, '%');
            getline(stream, tempYear, '%');

            if(tempHandheld == "True"){
                handheld = true;
            }
            else{
                handheld = false;
            }


            maxPlayers = stoi(tempMaxPlayers);
            //  cout << tempMaxPlayers << endl;


            if(tempMulti == "True"){
                multiplatform = true;
            }
            else{
                multiplatform = false;
            }

            if(tempOnline == "True"){
                online = true;
            }
            else{
                online = false;
            }

            licensed = true;
            sequel = true;
            reviewScore = stoi(tempScore);
            //  cout << tempScore << endl;
            sales = stof(tempSales);
            usedPrice = stof(tempUsedPrice);
            reRelease = true;
            releaseYear = stoi(tempYear);

            Game toBeAdded(title, handheld, maxPlayers, multiplatform, online,
                           genre, licensed, publisher, sequel, reviewScore,
                           sales, usedPrice, releaseConsole, ESRBrating,
                           reRelease, releaseYear);


            listOfAllGames.push_back(toBeAdded);


        }



    }

}

// Radix sort
int getMax(vector<Game>& games, int n)
{

    int mx = games.at(0).reviewScore;

    for (int i = 1; i < n; i++) {

        if (games.at(i).reviewScore > mx) {
            mx = games[i].reviewScore;

        }
    }
    return mx;
}

void countSort(vector<Game>& games, int n, int exp)
{
    vector<Game> unsortedTempGames = games;
    int output[n];
    int  i, count[10] = { 0 };


    for (i = 0; i < n; i++)
        count[(games[i].reviewScore / exp) % 10]++;


    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];


    for (i = n - 1; i >= 0; i--) {
        output[count[(games[i].reviewScore / exp) % 10] - 1] = games[i].reviewScore;
        count[(games[i].reviewScore / exp) % 10]--;

    }


    for (i = 0; i < n; i++) {
        games[i].reviewScore = output[i];
        for (int j = 0; j < unsortedTempGames.size(); j++) {
            if (games[i].reviewScore == unsortedTempGames[j].reviewScore) {
                games[i] = unsortedTempGames[j];
                games[i].reviewScore = output[i];
                unsortedTempGames[j].reviewScore = -1;
                break;
            }
        }
    }
    // cout << games[i].reviewScore << endl;


}

void radixsort(vector<Game>& games, int n)
{
    // Find the maximum number to know number of digits
    int m = getMax(games, n);


    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(games, n, exp);
    
}

// Quick sort
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int partition(std::vector<Game> &arr, int low, int high) {
    int pivot = arr[high].reviewScore;
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].reviewScore < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quicksort(std::vector<Game> &arr, int low, int high) {

    if (low < high) {
        int pi = partition(arr, low, high);

        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }

}


// Bucket sort
void bucketSort(vector<Game>& arr) {
    int n = arr.size();
    if (n <= 0) {
        return;
    }


    vector<vector<Game>> buckets(n);


    for (int i = 0; i < n; i++) {
        int bucketIndex = n * (arr[i].reviewScore * 0.01);
        buckets[bucketIndex].push_back(arr[i]);
    }


    for (int i = 0; i < n; i++) {
        std::sort(buckets[i].begin(), buckets[i].end(), [](const Game& a, const Game& b) {
            return a.reviewScore < b.reviewScore;
        });
    }


    int index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < buckets[i].size(); j++) {
            arr[index++] = buckets[i][j];
        }
    }
}


int main() {
    //  std::cout << "Hello, World!" << std::endl;
    regex top10Games = regex("top\\S+10\\S+games|top\\s+10\\s+games|top10 games|top 10games");
    regex top100Games = regex("top\\S+100\\S+games|top\\s+100\\s+games|100 games|top 100games");
    regex thisGame = regex("S+this\\S+game|s+this\\s+game|this game|this game|thisgame");
    regex aboutGame = regex("S+about\\S+game|s+about\\s+game|about game|about game|aboutgame");
    regex infoGame = regex("S+info\\S+game|s+info\\s+game|info game|info game|infogame");
    regex showGame = regex("S+show\\S+game|s+show\\s+game|show game|showgame");
    regex genre = regex("genre");

    // Extract data from CSV file
    vector<Game> allGamesList;
    extractDataFromFile(allGamesList);

    /*
    string selection1;
    string selection2;

    cout << "GameGenie: Your Personal Gaming Resources (with sorting)" << endl;
    cout << "-------------What sorting algorithm do you wish to use? Input 1, 2, or 3-------------" << endl;
    cout << "     1. Radix          2. Quick          3. Bucket          " << endl;
    getline(cin, selection1);
    cout << "GameGenie: What questions do you have today?" << endl;
    bool programRun = true;
    while (programRun) {
        cout << "User: ";
        getline(cin, selection2);
        transform(selection2.begin(), selection2.end(), selection2.begin(), ::tolower);


        if (selection1 == "1") {
            if (regex_search(selection2, top10Games)) {
// RADIX SORT FUNCTION
                vector<Game> sortedList = allGamesList;

                radixsort(sortedList, sortedList.size());
                cout << "GameGenie: Sure, here are the top 10 games based on metric scores" << endl;
                int n = 1;
                for (int i = sortedList.size() - 1; i > sortedList.size() - 11; --i) {
                    cout << n << ". " << sortedList[i].returnTitle() << ": " << sortedList[i].returnRatings() << endl;
                    ++n;
                }
            } else if (regex_search(selection2, top100Games)) {

                vector<Game> sortedList = allGamesList;
                radixsort(sortedList, sortedList.size());
                cout << "GameGenie: Sure, here are the top 100 games based on metric scores" << endl;
                int n = 1;
                for (int i = sortedList.size() - 1; i > sortedList.size() - 101; --i) {
                    cout << n << ". " << sortedList[i].returnTitle() << ": " << sortedList[i].returnRatings() << endl;
                    ++n;
                }
            } else if (regex_search(selection2, thisGame) | regex_search(selection2, infoGame) |
                       regex_search(selection2, aboutGame)
                       | regex_search(selection2, showGame)) {
                vector<Game> sortedList = allGamesList;
                radixsort(sortedList, sortedList.size());
                cout << "GameGenie: Sure, what game title do you need to look up?" << endl;
                bool correct = false;
                bool found = false;
                while (!correct) {
                    cout << "User: ";
                    string lookUp;
                    getline(cin, lookUp);
                    for (auto a: sortedList) {
                        if (lookUp == a.returnTitle()) {
                            cout << "GameGenie: Here is the game you requested" << endl;
                            cout << "Title: " << a.returnTitle() << endl;
                            cout << "Genre: " << a.returnGenre() << endl;
                            cout << "Year: " << a.returnYear() << endl;
                            cout << "Publisher: " << a.returnPublisher() << endl;
                            cout << "Release Console: " << a.returnConsole() << endl;
                            cout << "Sales: " << a.returnSales() << endl;
                            cout << "Metric Score: " << a.returnRatings() << endl;
                            correct = true;
                            found = true;
                            break;
                        }


                    }
                    if (found == false) {
                        cout << "Sorry, I can't find that game, try again?" << endl;
                        correct = false;
                    }
                }
            }

            else if(regex_search(selection2, genre)){
                vector<Game> sortedList = allGamesList;
                radixsort(sortedList, sortedList.size());
                cout << "GameGenie: Sure, what game genre do you need to look up?" << endl;
                bool correct = false;
                bool found = false;
                bool message = true;
                while (!correct) {
                    cout << "User: ";
                    string lookUp;
                    getline(cin, lookUp);
                    int n = 0;
                    for (auto a: sortedList) {
                        if (lookUp == a.returnGenre()) {
                            if(message){
                                cout << "GameGenie: Here is the list of games with genre " << lookUp << " you requested" << endl;
                                message = false;
                            }
                            ++n;
                            cout << n << ". " << a.returnTitle() << endl;

                            correct = true;
                            found = true;

                        }


                    }
                    if (found == false) {
                        cout << "Sorry, I can't find that genre, try again?" << endl;
                        correct = false;
                    }
                }
            }

            else {
                cout << "GameGenie: Sorry, I don't understand your question. Here are some questions you can ask me: "
                     << endl;
                cout << "1. Show me the top 10 games" << endl;
                cout << "2. Show me the top 100 games" << endl;
                cout << "3. Tell me about this game (ex. Super Mario Bros.)" << endl;
                cout << "4. Show me games with this genre (ex. Action)" << endl;
                continue;
            }


        } else if (selection1 == "2") {
            if (regex_search(selection2, top10Games)) {
// QUICK SORT FUNCTION
                vector<Game> sortedList = allGamesList;
                auto start = high_resolution_clock::now();
                quicksort(sortedList, 0, sortedList.size() - 1);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);
                cout << "GameGenie: The time taken by Quick Sort is: "
                     << duration.count() << " microseconds" << endl;
                cout << "GameGenie: Sure, here are the top 10 games based on metric scores" << endl;
                int n = 1;
                for (int i = sortedList.size() - 1; i > sortedList.size() - 11; --i) {
                    cout << n << ". " << sortedList[i].returnTitle() << ": " << sortedList[i].returnRatings() << endl;
                    ++n;
                }
            } else if (regex_search(selection2, top100Games)) {

                vector<Game> sortedList = allGamesList;
                auto start = high_resolution_clock::now();
                quicksort(sortedList, 0, sortedList.size() - 1);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);
                cout << "GameGenie: The time taken by Quick Sort is: "
                     << duration.count() << " microseconds" << endl;
                cout << "GameGenie: Sure, here are the top 10 games based on metric scores" << endl;
                int n = 1;
                for (int i = sortedList.size() - 1; i > sortedList.size() - 101; --i) {
                    cout << n << ". " << sortedList[i].returnTitle() << ": " << sortedList[i].returnRatings() << endl;
                    ++n;
                }
            } else if (regex_search(selection2, thisGame) | regex_search(selection2, infoGame) |
                       regex_search(selection2, aboutGame)
                       | regex_search(selection2, showGame)) {
                vector<Game> sortedList = allGamesList;
                auto start = high_resolution_clock::now();
                quicksort(sortedList, 0, sortedList.size() - 1);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);
                cout << "GameGenie: The time taken by Quick Sort is: "
                     << duration.count() << " microseconds" << endl;
                cout << "GameGenie: Sure, what game title do you need to look up?" << endl;

                bool correct = false;
                bool found = false;
                while (!correct) {
                    cout << "User: ";
                    string lookUp;
                    getline(cin, lookUp);
                    for (auto a: sortedList) {
                        if (lookUp == a.returnTitle()) {
                            cout << "GameGenie: Here is the game you requested" << endl;
                            cout << "Title: " << a.returnTitle() << endl;
                            cout << "Genre: " << a.returnGenre() << endl;
                            cout << "Year: " << a.returnYear() << endl;
                            cout << "Publisher: " << a.returnPublisher() << endl;
                            cout << "Release Console: " << a.returnConsole() << endl;
                            cout << "Sales: " << a.returnSales() << endl;
                            cout << "Metric Score: " << a.returnRatings() << endl;
                            correct = true;
                            found = true;
                            break;
                        }


                    }
                    if (found == false) {
                        cout << "Sorry, I can't find that game, try again?" << endl;
                        correct = false;
                    }
                }
            }


            else if(regex_search(selection2, genre)){
                vector<Game> sortedList = allGamesList;
                auto start = high_resolution_clock::now();
                quicksort(sortedList, 0, sortedList.size() - 1);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);
                cout << "GameGenie: The time taken by Quick Sort is: "
                     << duration.count() << " microseconds" << endl;
                cout << "GameGenie: Sure, what game genre do you need to look up?" << endl;
                bool correct = false;
                bool found = false;
                bool message = true;
                while (!correct) {
                    cout << "User: ";
                    string lookUp;
                    getline(cin, lookUp);
                    int n = 0;
                    for (auto a: sortedList) {
                        if (lookUp == a.returnGenre()) {
                            if(message){
                                cout << "GameGenie: Here is the list of games with genre " << lookUp << " you requested" << endl;
                                message = false;
                            }
                            ++n;
                            cout << n << ". " << a.returnTitle() << endl;

                            correct = true;
                            found = true;

                        }


                    }
                    if (found == false) {
                        cout << "Sorry, I can't find that genre, try again?" << endl;
                        correct = false;
                    }
                }
            }



            else {
                cout << "GameGenie: Sorry, I don't understand your question. Here are some questions you can ask me: "
                     << endl;
                cout << "1. Show me the top 10 games" << endl;
                cout << "2. Show me the top 100 games" << endl;
                cout << "3. Tell me about this game (ex. Super Mario Bros.)" << endl;
                continue;
            }

        } else if (selection1 == "3") {
            if (regex_search(selection2, top10Games)) {
// QUICK SORT FUNCTION
                vector<Game> sortedList = allGamesList;
                auto start = high_resolution_clock::now();
                bucketSort(sortedList);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);
                cout << "GameGenie: The time taken by Bucket Sort is: "
                     << duration.count() << " microseconds" << endl;
                cout << "GameGenie: Sure, here are the top 10 games based on metric scores" << endl;
                int n = 1;
                for (int i = sortedList.size() - 1; i > sortedList.size() - 11; --i) {
                    cout << n << ". " << sortedList[i].returnTitle() << ": " << sortedList[i].returnRatings() << endl;
                    ++n;
                }
            } else if (regex_search(selection2, top100Games)) {

                vector<Game> sortedList = allGamesList;
                auto start = high_resolution_clock::now();
                bucketSort(sortedList);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);
                cout << "GameGenie: The time taken by Bucket Sort is: "
                     << duration.count() << " microseconds" << endl;
                cout << "GameGenie: Sure, here are the top 100 games based on metric scores" << endl;
                int n = 1;
                for (int i = sortedList.size() - 1; i > sortedList.size() - 101; --i) {
                    cout << n << ". " << sortedList[i].returnTitle() << ": " << sortedList[i].returnRatings() << endl;
                    ++n;
                }
            } else if (regex_search(selection2, thisGame) | regex_search(selection2, infoGame) |
                       regex_search(selection2, aboutGame)
                       | regex_search(selection2, showGame)) {
                vector<Game> sortedList = allGamesList;
                auto start = high_resolution_clock::now();
                bucketSort(sortedList);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);
                cout << "GameGenie: The time taken by Bucket Sort is: "
                     << duration.count() << " microseconds" << endl;
                cout << "GameGenie: Sure, what game title do you need to look up?" << endl;

                bool correct = false;
                bool found = false;
                while (!correct) {
                    cout << "User: ";
                    string lookUp;
                    getline(cin, lookUp);
                    for (auto a: sortedList) {
                        if (lookUp == a.returnTitle()) {
                            cout << "GameGenie: Here is the game you requested" << endl;
                            cout << "Title: " << a.returnTitle() << endl;
                            cout << "Genre: " << a.returnGenre() << endl;
                            cout << "Year: " << a.returnYear() << endl;
                            cout << "Publisher: " << a.returnPublisher() << endl;
                            cout << "Release Console: " << a.returnConsole() << endl;
                            cout << "Sales: " << a.returnSales() << endl;
                            cout << "Metric Score: " << a.returnRatings() << endl;
                            correct = true;
                            found = true;
                            break;
                        }


                    }
                    if (found == false) {
                        cout << "Sorry, I can't find that game, try again?" << endl;
                        correct = false;
                    }
                }
            }

            else if(regex_search(selection2, genre)){
                vector<Game> sortedList = allGamesList;
                auto start = high_resolution_clock::now();
                bucketSort(sortedList);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);
                cout << "GameGenie: The time taken by Bucket Sort is: "
                     << duration.count() << " microseconds" << endl;
                cout << "GameGenie: Sure, what game genre do you need to look up?" << endl;
                bool correct = false;
                bool found = false;
                bool message = true;
                while (!correct) {
                    cout << "User: ";
                    string lookUp;
                    getline(cin, lookUp);
                    int n = 0;
                    for (auto a: sortedList) {
                        if (lookUp == a.returnGenre()) {
                            if(message){
                                cout << "GameGenie: Here is the list of games with genre " << lookUp << " you requested" << endl;
                                message = false;
                            }
                            ++n;
                            cout << n << ". " << a.returnTitle() << endl;

                            correct = true;
                            found = true;

                        }


                    }
                    if (found == false) {
                        cout << "Sorry, I can't find that genre, try again?" << endl;
                        correct = false;
                    }
                }
            }



            else {
                cout << "GameGenie: Sorry, I don't understand your question. Here are some questions you can ask me: "
                     << endl;
                cout << "1. Show me the top 10 games" << endl;
                cout << "2. Show me the top 100 games" << endl;
                cout << "3. Tell me about this game (ex. Super Mario Bros.)" << endl;
                continue;
            }

        }


        cout << endl;
        cout << "GameGenie: Anything else I can help you with?" << endl;


    }

    int a = 3; */

    cout << dye::red("GameGenie: Your Personal Gaming Resources (with sorting)") << endl << endl;

    // Continuous loop throughout the program: set program to false on exit
    bool programRun = true;
    while (programRun)
    {
        cout << dye::blue("GameGenie: What can I help you with today?") << endl;

        // Display options menu
        cout << dye::green("1. Rankings") << endl;
        cout << dye::green("2. Search Game") << endl;
        cout << dye::green("3: Exit") << endl;

        // Input option
        int option;
        string tempOption;
        getline(cin, tempOption);
        option = stoi(tempOption);

        if (option == 1) // Rank top X games
        {
            // Input number of ranks to be displayed
            int numRanks;
            cout << dye::blue("GameGenie: How many to be displayed?") << endl;
            string tempRank;
            getline(cin, tempRank);
            numRanks = stoi(tempRank);

            // Keep within bounds
            if (numRanks <= 1)
            {
                numRanks = 2;
            }
            else if (numRanks > allGamesList.size())
            {
                numRanks = allGamesList.size();
            }

            string answer;
            while (true)
            {
                // Display in ascending or descending order
                cout << dye::blue("GameGenie: Start from bottom (b) or top (t)?") << endl;
                getline(cin, answer);

                if (answer == "b" || answer == "t")
                {
                    break;
                }
                else
                {
                    // Invalid option, not "b" or "t"
                    cout << dye::blue("GameGenie: Invalid option! Try again?") << endl;
                }
            }

            // Initialize unsorted lists
            vector<Game> sortedList1, sortedList2, sortedList3;
            sortedList1 = sortedList2 = sortedList3 = allGamesList;

            // Perform Radix Sort
            auto start1 = high_resolution_clock::now();
            radixsort(sortedList1, sortedList1.size());
            auto stop1 = high_resolution_clock::now();
            auto duration1 = duration_cast<microseconds>(stop1 - start1);

            // Perform Quicksort
            auto start2 = high_resolution_clock::now();
            quicksort(sortedList2, 0, sortedList2.size() - 1);
            auto stop2 = high_resolution_clock::now();
            auto duration2 = duration_cast<microseconds>(stop2 - start2);
                    
            // Perform bucket sort
            auto start3 = high_resolution_clock::now();
            bucketSort(sortedList3);
            auto stop3 = high_resolution_clock::now();
            auto duration3 = duration_cast<microseconds>(stop3 - start3);

            if (answer == "t")
            {
                // Display results in descending order by metric score (highest ranked first)
                cout << dye::blue("GameGenie: Here are the top ") << dye::blue(numRanks) << dye::blue(" games based on metric scores") << endl;
                int n = 1;
                for (int i = sortedList1.size() - 1; i > ((int) sortedList1.size()) - numRanks - 1; --i) {
                    cout << dye::purple(n) << dye::purple(". ") << dye::purple(sortedList1[i].returnTitle()) << dye::purple(": ") << dye::light_yellow(sortedList1[i].returnRatings()) << endl;
                    ++n;
                }
            }
            else
            {
                // Display reuslts in ascending order by metric score (lowest first)
                cout << dye::blue("GameGenie: Here are the bottom ") << dye::blue(numRanks) << dye::blue(" games based on metric scores") << endl;
                int n = 1;
                for (int i = 0; i < numRanks; ++i) {
                    cout << dye::purple(n) << dye::purple(". ") << dye::purple(sortedList1[i].returnTitle()) << dye::purple(": ") << dye::light_yellow(sortedList1[i].returnRatings()) << endl;
                    ++n;
                }
            }

            // Display the times for each sorting algorithm
            cout << endl;
            cout << dye::blue("GameGenie: Time taken by sorting:") << endl;
            cout << dye::purple("Radix Sort: ") << dye::light_yellow(duration1.count() / 1000.0) << dye::light_yellow(" ms") << endl;
            cout << dye::purple("Quick Sort: ") << dye::light_yellow(duration2.count() / 1000.0) << dye::light_yellow(" ms") << endl;
            cout << dye::purple("Bucket Sort: ") << dye::light_yellow(duration3.count() / 1000.0) << dye::light_yellow(" ms") << endl << endl;
                
        }
        else if (option == 2) // Lookup game
        {
            int choice;
            while (true)
            {
                // Display search menu options
                cout << dye::blue("GameGenie: Search game by") << endl;
                cout << dye::green("1. Title") << endl;
                cout << dye::green("2. Genre") << endl;
                cout << dye::green("3. Year") << endl;
                cout << dye::green("4. Publisher") << endl;
                cout << dye::green("5. Release Console") << endl;
                cout << dye::green("6. Exit") << endl;
                
                // Take in input for menu option
                string tempChoice;
                getline(cin, tempChoice);
                choice = stoi(tempChoice);

                // Check if valid choice
                if (choice < 1 || choice > 6)
                {
                    cout << dye::blue("GameGenie: Invalid option! Try again?") << endl;
                }
                else if (choice == 6) // Exit
                {
                    break;
                }
                else
                {
                    string line;

                    vector<Game> matches;
                    if (choice == 1) // Search by title
                    {
                        cout << dye::blue("GameGenie: Input title") << endl;
                        getline(cin, line);

                        // Loop through each game and find matches
                        for (int i = 0; i < allGamesList.size(); i++)
                        {
                            // Find current title and convert to upper to avoid case issues
                            string currTitle = allGamesList[i].returnTitle();
                            transform(currTitle.begin(), currTitle.end(), currTitle.begin(), ::toupper);
                            transform(line.begin(), line.end(), line.begin(), ::toupper);

                            // Check if there is a match
                            if (currTitle.find(line) != string::npos)
                            {
                                matches.push_back(allGamesList[i]);
                            }
                        }
                    }
                    else if (choice == 2) // Search by genre
                    {
                        cout << dye::blue("GameGenie: Input genre") << endl;
                        getline(cin, line);

                        // Loop through each game and find matches
                        for (int i = 0; i < allGamesList.size(); i++)
                        {
                            // Find current genre and convert to upper to avoid case issues
                            string currGenre = allGamesList[i].returnGenre();
                            transform(currGenre.begin(), currGenre.end(), currGenre.begin(), ::toupper);
                            transform(line.begin(), line.end(), line.begin(), ::toupper);

                            // Check if there is a match
                            if (currGenre.find(line) != string::npos)
                            {
                                matches.push_back(allGamesList[i]);
                            }
                        }
                    }
                    else if (choice == 3) // Search by year published (2004-2008 only in dataset)
                    {
                        cout << dye::blue("GameGenie: Input year published") << endl;
                        getline(cin, line);

                        // Loop through each game and find matches
                        for (int i = 0; i < allGamesList.size(); i++)
                        {
                            // Find current year
                            int currYear = allGamesList[i].returnYear();
                            int inputYear = stoi(line);       

                            // Check if there is a match
                            if (currYear == inputYear)
                            {
                                matches.push_back(allGamesList[i]);
                            }
                            
                        }

                    }
                    else if (choice == 4) // Search by game publisher
                    {
                        cout << dye::blue("GameGenie: Input publisher") << endl;
                        getline(cin, line);

                        // Loop through each game and find matches
                        for (int i = 0; i < allGamesList.size(); i++)
                        {
                            // Find current publisher and convert to upper to avoid case issues
                            string currPublisher = allGamesList[i].returnPublisher();
                            transform(currPublisher.begin(), currPublisher.end(), currPublisher.begin(), ::toupper);
                            transform(line.begin(), line.end(), line.begin(), ::toupper);

                            // Check if there is a match
                            if (currPublisher.find(line) != string::npos)
                            {
                                matches.push_back(allGamesList[i]);
                            }
                        }
                    }
                    else if (choice == 5) // Search by console released
                    {
                        cout << dye::blue("GameGenie: Input console") << endl;
                        getline(cin, line);

                        // Loop through each game and find matches
                        for (int i = 0; i < allGamesList.size(); i++)
                        {
                            // Find current console and convert to upper to avoid case issues
                            string currConsole = allGamesList[i].returnConsole();
                            transform(currConsole.begin(), currConsole.end(), currConsole.begin(), ::toupper);
                            transform(line.begin(), line.end(), line.begin(), ::toupper);

                            // Check if there is a match
                            if (currConsole.find(line) != string::npos)
                            {
                                matches.push_back(allGamesList[i]);
                            }
                        }
                    }


                    if (matches.size() == 0) // No matches found / vector is empty
                    {
                        cout << dye::blue("GameGenie: No matches found!") << endl;
                    }
                    else
                    {
                        // Initialize unsorted lists
                        vector<Game> sortedList1, sortedList2, sortedList3;
                        sortedList1 = sortedList2 = sortedList3 = matches;
                        
                        // Perform Radix Sort
                        auto start1 = high_resolution_clock::now();
                        radixsort(sortedList1, sortedList1.size());
                        auto stop1 = high_resolution_clock::now();
                        auto duration1 = duration_cast<microseconds>(stop1 - start1);

                        // Perform Quicksort
                        auto start2 = high_resolution_clock::now();
                        quicksort(sortedList2, 0, sortedList2.size() - 1);
                        auto stop2 = high_resolution_clock::now();
                        auto duration2 = duration_cast<microseconds>(stop2 - start2);
                                
                        // Perform bucket sort
                        auto start3 = high_resolution_clock::now();
                        bucketSort(sortedList3);
                        auto stop3 = high_resolution_clock::now();
                        auto duration3 = duration_cast<microseconds>(stop3 - start3);


                        // Print out the data for each matching game
                        cout << dye::blue("GameGenie: Here are all matching games:") << endl;
                        for (int i = matches.size() - 1; i >= 0; --i)
                        {
                            cout << dye::purple(matches.size() - i) << dye::purple(") ") << dye::light_yellow(sortedList1[i].returnTitle()) << endl;
                            cout << "\t" << dye::purple("Genre: ") << dye::light_yellow(sortedList1[i].returnGenre()) << endl;
                            cout << "\t" << dye::purple("Year: ") << dye::light_yellow(sortedList1[i].returnYear()) << endl;
                            cout << "\t" << dye::purple("Publisher: ") << dye::light_yellow(sortedList1[i].returnPublisher()) << endl;
                            cout << "\t" << dye::purple("Release Console: ") << dye::light_yellow(sortedList1[i].returnConsole()) << endl;
                            cout << "\t" << dye::purple("Sales: ") << dye::light_yellow(sortedList1[i].returnSales()) << endl;
                            cout << "\t" << dye::purple("Metric Score: ") << dye::light_yellow(sortedList1[i].returnRatings()) << endl << endl;
                        }


                        // Display the times for each sorting algorithm
                        cout << dye::blue("GameGenie: Time taken by sorting:") << endl;
                        cout << dye::purple("Radix Sort: ") << dye::light_yellow(duration1.count() / 1000.0) << dye::light_yellow(" ms") << endl;
                        cout << dye::purple("Quick Sort: ") << dye::light_yellow(duration2.count() / 1000.0) << dye::light_yellow(" ms") << endl;
                        cout << dye::purple("Bucket Sort: ") << dye::light_yellow(duration3.count() / 1000.0) << dye::light_yellow(" ms") << endl << endl;
                    }
                }
            }
        }
        else if (option == 3) // Exit
        {
            cout << dye::blue("GameGenie: Thank you for using GameGenie! :)") << endl;
            programRun = false;
        }
        else
        {
            cout << dye::blue("GameGenie: Sorry, invalid option! Try again?") << endl << endl;
        }
    }

    return 0;
}