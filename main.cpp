#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "CircularLinkedListApartment.h"

using namespace std;

int main(int argc, char** argv) {

    string input = argv[1];
    string output = argv[2];


    std::string line;
    std::vector<std::string> tokens;

    CircularLinkedListApartment function;
    CircularLinkedListApartment *head = nullptr;

    ifstream infile;
    infile.open(input.c_str());

    vector<string> list;

    ofstream file2;
    file2.open(output.c_str());



    if(infile.is_open()){
        string x;

        while (getline(infile, line))
        {
            istringstream iss(line);
            string word;
            while(getline(iss, word, '\t')) {
                list.push_back(word);
            }
            if(list[0] == "add_apartment"){
                int band1; stringstream  ss; ss << list[3]; ss >> band1; ss.clear();

                function.add_apartment(&head,list[1],list[2],band1);
            }
            else if (list[0] == "add_flat"){
                int band2; stringstream  ss; ss << list[3]; ss >> band2; ss.clear();

                function.add_flat(&head ,list[1],list[2],band2 , list[4]);
            }
            else if (list[0] == "remove_apartment"){
                function.remove_apartment(&head ,list[1]);
            }
            else if (list[0] == "make_flat_empty"){
                function.make_flat_empty(&head ,list[1],list[2]);
            }
            else if (list[0] == "find_sum_of_max_bandwidths"){
                function.find_sum_of_max_bandwidth(&head);
                int sum = function.find_sum_of_max_bandwidth(&head);
                file2 << "sum of bandwith: " <<sum << endl << endl;
            }
            else if (list[0] == "merge_two_apartments"){
                function.merge_two_apartments(&head , list[1], list[2]);
            }
            else if (list[0] == "relocate_flats_to_same_apartment"){
                function.relocate_flats_to_same_apartments(&head,list[1],list[2],list[3]);
            }
            else if (list[0] == "list_apartments"){
                int sum = function.find_sum_of_max_bandwidth(&head);
                function.list_apartments(&head ,file2,sum);
            }

            list.clear();
        }

        infile.close();
    }

    else{
        cout << "The file is not found";
    }
    infile.close();
    file2.close();


    return 0;
}
