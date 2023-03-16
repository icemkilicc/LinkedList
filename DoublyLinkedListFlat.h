
#ifndef ASSIGMENT2_DOUBLYLINKEDLISTFLAT_H
#define ASSIGMENT2_DOUBLYLINKEDLISTFLAT_H

#include <string>

using namespace std;

class DoublyLinkedListFlat {

public:

    int initial_bandwith;
    string flat_id;
    string index;
    string is_empty;

    DoublyLinkedListFlat *next_flat = nullptr;
    DoublyLinkedListFlat *prev_node = nullptr;


};


#endif //ASSIGMENT2_DOUBLYLINKEDLISTFLAT_H
