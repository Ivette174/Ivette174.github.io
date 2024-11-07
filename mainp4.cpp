
#include<iostream>
#include<fstream>
#include<string>
#include<cctype>
#include<vector>
#include <ctime>

//------------------------------
// Ivette Pizarro

using namespace std;


class StringVector {

private:
    vector<string> stringv;
    vector<string> word;
    int uniquew = 0;

public:

    int BinarySearch (const string& word, int smallest, int biggest){
        if (smallest > biggest){
            return -1;
        }

        int middle = (smallest + biggest)/2;

            if (stringv[middle]==word) {
                return middle;
            }
            else if (stringv[middle]>word){
                return BinarySearch(word, smallest, middle -1);
            }
            else{
                return BinarySearch(word, middle + 1, biggest);
            }

    }

    int BinarySearch(const string& word){
            return BinarySearch(word, 0, stringv.size()-1);
        }


    int AddSorted(const string& word, int smallest, int biggest) {
        if (smallest > biggest) {
            stringv.insert(stringv.begin() + smallest, word);
            uniquew++;
            return smallest;
        }

        int middle = (smallest + biggest) / 2;

        if (stringv[middle] == word) {
            return middle;
        } else if (stringv[middle] > word) {
            return AddSorted(word, smallest, middle - 1);
        } else {
            return AddSorted(word, middle + 1, biggest);
        }
    }

    int AddSorted(const string& word){

        return AddSorted(word, 0, stringv.size()-1);
    }




    int LinearSearch(const string& word){
        for (size_t i = 0; i < stringv.size(); i++){
            if (stringv[i]==word){
                return i;
            }
        }
        return -1;
    }

    //BinarySeach(string word){

    //}

    void AddUnsorted(const string& word){
        if (LinearSearch (word) == -1) {
            stringv.push_back(word);
            uniquew++;
        }

    }

    int getuniquewnum() const {
        return uniquew;
    }

};

bool read_txt(const string &ifilename, StringVector& list, int& totalw) {
    ifstream inputFile(ifilename);

    if (!inputFile) {
        cout << "Error with opening input file. \n";
        return false;
    }

    string word;
    while (inputFile >> word) {
        totalw++;
        for (char &w: word) {

            w = tolower(w);
        }
        string Punct;
        for (char w: word) {
            if (!ispunct(w)) {
                Punct += w;
            }

        }
        if (!Punct.empty()) {
            list.AddSorted(Punct);
        }

    }
    inputFile.close();
    return true;

}
    void level_calc(const vector<string>& filenames){

    clock_t startt = clock();
    for (const auto& filename:filenames){
        StringVector wordList;
        int totalw = 0;

        if (!read_txt(filename, wordList, totalw)){
            cout << "Error reading file: " << filename << endl;
            continue;
        }

        clock_t endt = clock();
        double runt = static_cast<double>(endt - startt) / CLOCKS_PER_SEC;
        //wordList.Print();//_Node(filename);
        cout << endl << "Input file name: " << filename << endl;
        cout << "# of total words: " << totalw << endl;
        cout << "# of unique words: " << wordList.getuniquewnum() << endl;
        cout << "Execution time: " << runt << "secs\n";
        cout << "_________________________________\n";



    }
}


int main(int argc, char* argv[]){

    StringVector Vector;



    vector<string> books = {
            "CallWild.txt",
            "JekyllHyde.txt",
            "SleepyHolow.txt"
    };
    level_calc(books);


   return 0;
}