
#ifndef ASSIGMENT2_CIRCULARLINKEDLISTAPARTMENT_H
#define ASSIGMENT2_CIRCULARLINKEDLISTAPARTMENT_H

#include <string>
#include "DoublyLinkedListFlat.h"

using namespace std;



class CircularLinkedListApartment {

public:

    string apartment_name;
    int max_bandwith;
    CircularLinkedListApartment *next = nullptr;
    DoublyLinkedListFlat *head_of_flats;

    void add_apartment(CircularLinkedListApartment **head , string name_of_apart, string position, int max_band);

    void add_flat(CircularLinkedListApartment **head , string name_of_apart, string index, int initial_band , string flat_id);

    CircularLinkedListApartment *remove_apartment(CircularLinkedListApartment **head , string name_of_apart);

    void make_flat_empty(CircularLinkedListApartment **head , string name_of_apart , string flat_id);

    int find_sum_of_max_bandwidth(CircularLinkedListApartment **head );

    void merge_two_apartments(CircularLinkedListApartment **head , string main_apartment , string side_apartment);

    void relocate_flats_to_same_apartments(CircularLinkedListApartment **head, string new_apartment_name, string flat_id_to_shift, string flat_id_list);

    void list_apartments(CircularLinkedListApartment **head , ofstream &file2 , int sum_of_bant);
};


#endif //ASSIGMENT2_CIRCULARLINKEDLISTAPARTMENT_H
