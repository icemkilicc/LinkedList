
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "CircularLinkedListApartment.h"

using namespace std;


void CircularLinkedListApartment::add_apartment(CircularLinkedListApartment **head , string name_of_apart, string position, int max_band) {

    vector<string> poss;

    istringstream ss(position);
    string token;

    while(getline(ss, token, '_')) {

        poss.push_back(token);
    }

    CircularLinkedListApartment *newApart = new CircularLinkedListApartment;
    newApart->head_of_flats = nullptr;
    CircularLinkedListApartment *last = *head;
    newApart->apartment_name = name_of_apart;
    newApart->max_bandwith = max_band;

    if(position == "head"){
        *head = newApart;
    }
    else if (poss[0] == "before"){
        if(last->apartment_name == poss[1]){
            newApart->next = last;
            *head = newApart;
        }
        else {
            while (last->next->apartment_name != poss[1]) {
                last = last->next;
            }
            newApart->next = last->next;
            last->next = newApart;
        }
    }
    else if (poss[0] == "after"){
        while (last->apartment_name != poss[1]) {
            last = last->next;
        }
        if(last->next != nullptr){
            newApart->next = last->next;
        }
        last->next = newApart;
    }

}

void CircularLinkedListApartment::add_flat(CircularLinkedListApartment **head, string name_of_apart, string index , int initial_band , string flat_id) {

    int num;  stringstream ss;
    ss << index; ss >> num;

    DoublyLinkedListFlat *newFlat = new DoublyLinkedListFlat;
    newFlat->index = index;
    newFlat->flat_id = flat_id;
    newFlat->is_empty = "0";

    CircularLinkedListApartment *last = *head;

    while (last->apartment_name != name_of_apart ){
        last = last->next;
    }

    DoublyLinkedListFlat *check =last->head_of_flats;
    int total = 0;

    while (check != nullptr ){
        total += check->initial_bandwith;
        check = check->next_flat;
    }

    if(total + initial_band < last->max_bandwith){
        newFlat->initial_bandwith = initial_band;
    }else{
        newFlat->initial_bandwith = last->max_bandwith -total;
    }


    if (last->head_of_flats == NULL){

        last->head_of_flats = newFlat;
        newFlat->next_flat = nullptr;
        newFlat->prev_node = nullptr;

    }
    else{
        DoublyLinkedListFlat *searchFlat = last->head_of_flats;

        for (int i = 0; i < num-1; ++i) {
            searchFlat = searchFlat->next_flat;
        }
        if(num == 0){
            searchFlat->prev_node = newFlat;
            newFlat->next_flat = searchFlat;
            last->head_of_flats = newFlat;
        }

        else{
            newFlat->next_flat = searchFlat->next_flat;
            searchFlat->next_flat = newFlat;
            newFlat->prev_node = searchFlat;
            if(newFlat->next_flat != NULL) {
                newFlat->next_flat->prev_node = newFlat;
            }
        }

    }


}

CircularLinkedListApartment *CircularLinkedListApartment::remove_apartment(CircularLinkedListApartment **head, string name_of_apart) {

    CircularLinkedListApartment *last = *head;
    CircularLinkedListApartment *prev;

    if(last->next == nullptr){
        free(head);
        return NULL;
    }

    while (last->apartment_name != name_of_apart ){
        prev = last;
        last = last->next;
    }

    DoublyLinkedListFlat *searchFlat = last->head_of_flats;
    DoublyLinkedListFlat *freeFlat;

    while (searchFlat != nullptr){

        freeFlat = searchFlat;
        searchFlat = searchFlat->next_flat;
        free(freeFlat);

    }

    if (last == *head){
        *head = last->next;
        free(last);
        return *head;
    }

    prev->next = last->next;

    free(last);

    return *head;

}

void CircularLinkedListApartment::make_flat_empty(CircularLinkedListApartment **head, string name_of_apart, string flat_id) {

    CircularLinkedListApartment *last = *head;

    while (last->apartment_name != name_of_apart ){
        last = last->next;
    }

    DoublyLinkedListFlat *search = last->head_of_flats;

    while(search->flat_id != flat_id){
        search = search->next_flat;
    }

    search->is_empty = "1";
    search->initial_bandwith = 0;

}

int CircularLinkedListApartment::find_sum_of_max_bandwidth(CircularLinkedListApartment **head) {

    CircularLinkedListApartment *last = *head;
    int total = 0;

    if(last == nullptr){
        return 0;
    }
    else{
        while( last != nullptr){

            total += last->max_bandwith;
            last = last->next;

        }
        return total;
    }

}

void CircularLinkedListApartment::merge_two_apartments(CircularLinkedListApartment **head, string main_apartment, string side_apartment) {

    CircularLinkedListApartment *main;
    CircularLinkedListApartment *side;
    CircularLinkedListApartment *side_prev = nullptr;
    CircularLinkedListApartment *last = *head;
    CircularLinkedListApartment *check = *head;

    while (last->next != nullptr ){
        if(last->apartment_name == main_apartment){
            main = last;
        }
        if(last->next->apartment_name == side_apartment){
            side_prev =last;
            side = last->next;
        }
        last = last->next;
    }

    if(last->apartment_name == main_apartment){
        main = last;
    }
    if(check->apartment_name == side_apartment){
        side = check;
    }

    DoublyLinkedListFlat *main_flat = main->head_of_flats;

    if (main_flat != nullptr) {
        while (main_flat->next_flat != nullptr) {
            main_flat = main_flat->next_flat;
        }

        DoublyLinkedListFlat *side_flat = side->head_of_flats;

        main_flat->next_flat = side_flat;
        if (side_flat != nullptr) {
            side_flat->prev_node = main_flat;
        }
    }
    else{
        main->head_of_flats = side->head_of_flats;
    }

    int total = main->max_bandwith+ side->max_bandwith;


    main->max_bandwith = total;

    if(side_prev != nullptr){
        side_prev->next = side->next;
    }
    else{
        *head = check->next;
    }

    free(side);


}

void CircularLinkedListApartment::relocate_flats_to_same_apartments(CircularLinkedListApartment **head, string new_apartment_name, string flat_id_to_shift, string flat_id_list) {

    CircularLinkedListApartment *main_apartment = *head;

    while (main_apartment->apartment_name != new_apartment_name ){
        main_apartment = main_apartment->next;
    }

    DoublyLinkedListFlat *shifted_flat = main_apartment->head_of_flats;

    while(shifted_flat->flat_id != flat_id_to_shift ){
        shifted_flat = shifted_flat->next_flat;
    }


    flat_id_list = flat_id_list.substr(1,flat_id_list.length()-2);

    vector<string> list;
    stringstream ss(flat_id_list);
    while(ss.good()) {
        string flats;
        getline(ss, flats, ',');
        list.push_back(flats);
    }


    reverse(list.begin(), list.end());

    for(string flat : list){

        CircularLinkedListApartment *searchApart = *head;
        DoublyLinkedListFlat *searchFlat = searchApart->head_of_flats;

        while(searchFlat->flat_id != flat){

            if(searchFlat->next_flat == nullptr){
                searchApart = searchApart->next;
                searchFlat = searchApart->head_of_flats;
            }
            else{
                searchFlat = searchFlat->next_flat;
            }

        }

        int total_search_apart = searchApart->max_bandwith- searchFlat->initial_bandwith;
        int total_main_apart = main_apartment->max_bandwith+ searchFlat->initial_bandwith;


        searchApart->max_bandwith = total_search_apart;


        main_apartment->max_bandwith = total_main_apart;

        if(searchFlat->prev_node != nullptr){
            searchFlat->prev_node->next_flat = searchFlat->next_flat;
        }
        else{
            if(searchFlat->next_flat != nullptr){
                searchApart->head_of_flats = searchFlat->next_flat;
            }
            else{
                searchApart->head_of_flats = nullptr;
            }

        }


        if(shifted_flat->prev_node == nullptr){

            shifted_flat->prev_node = searchFlat;
            main_apartment->head_of_flats = searchFlat;
            searchFlat->next_flat = shifted_flat;
            searchFlat->prev_node = nullptr;

        }
        else{
            shifted_flat->prev_node->next_flat = searchFlat;
            searchFlat->prev_node = shifted_flat->prev_node;
            shifted_flat->prev_node =searchFlat;
        }

        shifted_flat = searchFlat;

    }



}

void CircularLinkedListApartment::list_apartments(CircularLinkedListApartment **head , ofstream &file2, int sum_of_bant) {

    CircularLinkedListApartment *main_apartment = *head;
    DoublyLinkedListFlat *main_flat;
    if(main_apartment != nullptr){
        main_flat = main_apartment->head_of_flats;
    }


    while (main_apartment != nullptr ){

        file2 << main_apartment->apartment_name << "(" << main_apartment->max_bandwith << ")";

        while(main_flat != nullptr){
            file2 << "\t" << "Flat" << main_flat->flat_id << "(" << main_flat->initial_bandwith << ")";
            main_flat = main_flat->next_flat;
        }

        file2 << endl;
        if(main_apartment->next != nullptr){
            main_apartment = main_apartment->next;
            main_flat = main_apartment->head_of_flats;
        }
        else{
            break;
        }

    }
    if(*head == nullptr){
        file2 << "there is no apartment" << endl;
    }
    file2 << endl;

}








