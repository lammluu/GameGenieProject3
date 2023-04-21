#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <iomanip>
#include "game.h"
#include <algorithm>
#include <chrono>
#include <regex>


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

// RADIX SORT

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

// A function to do counting sort of arr[] according to
// the digit represented by exp.
void countSort(vector<Game>& games, int n, int exp)
{
    vector<Game> unsortedTempGames = games;
    int output[n]; // output array
    int  i, count[10] = { 0 };

    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        count[(games[i].reviewScore / exp) % 10]++;

    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (i = n - 1; i >= 0; i--) {
        output[count[(games[i].reviewScore / exp) % 10] - 1] = games[i].reviewScore;
        count[(games[i].reviewScore / exp) % 10]--;

    }

    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
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

// The main function to that sorts arr[] of size n using
// Radix Sort
void radixsort(vector<Game>& games, int n)
{
    auto start = high_resolution_clock::now();
    // Find the maximum number to know number of digits
    int m = getMax(games, n);

    // Do counting sort for every digit. Note that instead
    // of passing digit number, exp is passed. exp is 10^i
    // where i is current digit number
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(games, n, exp);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "GameGenie: The time taken by Radix Sort is: "
         << duration.count() << " microseconds" << endl;
}




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








void bucketSort(vector<Game>& arr) {
    int n = arr.size();
    if (n <= 0) {
        return;
    }

    // Create n empty buckets
    vector<vector<Game>> buckets(n);

    // Place Game objects in different buckets based on their reviewScore
    for (int i = 0; i < n; i++) {
        int bucketIndex = n * (arr[i].reviewScore * 0.01);
        buckets[bucketIndex].push_back(arr[i]);
    }

    // Sort individual buckets
    for (int i = 0; i < n; i++) {
        std::sort(buckets[i].begin(), buckets[i].end(), [](const Game& a, const Game& b) {
            return a.reviewScore < b.reviewScore;
        });
    }

    // Concatenate all sorted buckets into the original array
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
    vector<Game> allGamesList;

    extractDataFromFile(allGamesList);

    string selection1;
    string selection2;

    cout << "GameGenie: Your Personal Gaming Resources (with sorting)" << endl;
    cout << "-------------What sorting algorithm do you wish to use? Input 1, 2, or 3-------------" << endl;
    cout << "     1. Radix          2. Quick          3. Bucket          " << endl;
    getline(cin, selection1);
    cout << "GameGenie: What questions do you have today?" << endl;
    bool programRun = true;
    while(programRun) {
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
            }

            else if(regex_search(selection2, top100Games)){

                vector<Game> sortedList = allGamesList;
                radixsort(sortedList, sortedList.size());
                cout << "GameGenie: Sure, here are the top 100 games based on metric scores" << endl;
                int n = 1;
                for (int i = sortedList.size() - 1; i > sortedList.size() - 101; --i) {
                    cout << n << ". " << sortedList[i].returnTitle() << ": " << sortedList[i].returnRatings() << endl;
                    ++n;
                }
            }

            else{
                cout << "GameGenie: Sorry, I don't understand your question. Here are some questions you can ask me: " << endl;
                cout <<       "1. Show me the top 10 games" << endl;
                cout <<       "2. Show me the top 100 games" << endl;
                cout << "3. Tell me about this game (ex. Super Mario Bros.)" << endl;
                continue;
            }



        }

        else if(selection1 == "2"){
            if (regex_search(selection2, top10Games)) {
// QUICK SORT FUNCTION
                vector<Game> sortedList = allGamesList;
                auto start = high_resolution_clock::now();
                quicksort(sortedList, 0, sortedList.size()-1);
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
            }
            else if(regex_search(selection2, top100Games)){

                vector<Game> sortedList = allGamesList;
                auto start = high_resolution_clock::now();
                quicksort(sortedList, 0, sortedList.size()-1);
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
            }

        }
        else if(selection1 == "3"){
            if (regex_search(selection2, top10Games)) {
// QUICK SORT FUNCTION
                vector<Game> sortedList = allGamesList;
                auto start = high_resolution_clock::now();
                bucketSort(sortedList);
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
            }
            else if(regex_search(selection2, top100Games)){

                vector<Game> sortedList = allGamesList;
                auto start = high_resolution_clock::now();
                bucketSort(sortedList);
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
            }

        }


        cout << endl;
        cout << "GameGenie: Anything else I can help you with?" << endl;


    }




    //  cout << "SORTED: " << endl;

/*
    for(Game A : allGamesList){
        cout << A.returnTitle() << endl;
        cout << A.returnRatings() << endl;
    }
    */


    return 0;
}

