#include <iostream>
#include <string>
#include <cstring>
#include "mlist.h"
using namespace std;
//------------------------------------------------------------------------------
//IMPORTANT: You are not allowed to remove or add any parameters to any functions.
//NOTE: There can only be at most 2 loops in this file
//------------------------------------------------------------------------------

//Constructor, construct an empty doubly linked list.
MList::MList(){
    ntop = NULL;
    nbottom = NULL;

}

//Destructor, properly clears and deallocates everything of current list.
//simply call the clear function if you have already implemented that.
MList::~MList(){
    clear();

}

//Note: RECURSION --- This function should be implemented using recursion.
//this function properly clears and deallocates everything of current list.
//there should be no loop in this function
void MList::clear(){
    if(!isEmpty()) {
        pop_top();
        clear();
    }
}

//returns a boolean true if the list is empty, false if otherwise.
bool MList::isEmpty(){
    if (ntop == NULL && nbottom == NULL) {
        return true;
    } else {
        return false;
    }

}

/*
	Add or insert a new node with d_item as its data at the top of the list.
	You need to dynamically allocate memory for the new node.
*/
void MList::push_top(Data* d_item){
    
    if (isEmpty()) {
        Node* topNode = new Node;
        topNode->nodeData = d_item;
        topNode->prev = NULL;
        topNode->next = NULL;
        ntop = topNode;
        nbottom = topNode;
    } else {
        Node* topNode = new Node;
        topNode->nodeData = d_item;
        topNode->prev = NULL;
        topNode->next = ntop;
        ntop->prev = topNode;
        ntop = topNode;
    } 
}

/*
	Add or insert a new node with d_item as its data at the bottom of the list.
	You need to dynamically allocate memory for the new node.
*/
void MList::push_bottom(Data* d_item){
    if (isEmpty()) { // if list is empty, just add it
        Node* newBottom = new Node;
        newBottom->nodeData = d_item;
        newBottom->prev = NULL;
        newBottom->next = NULL;
        nbottom = newBottom;
        ntop = newBottom;
    } else {
        Node* newBottom = new Node;
        newBottom->nodeData = d_item;
        newBottom->prev = nbottom; 
        newBottom->next = NULL;
        nbottom->next = newBottom;
        nbottom = newBottom;
    }
}

/*
	Delete or remove the top node of the list.
	Once pop, you need to properly deallocate the memory for the node (not the data).
	If your list is currently empty, you don't have to do anything.
*/
void MList::pop_top(){
    if (!isEmpty()) {
        if (ntop == nbottom) { // one item in list
            delete ntop;
            ntop = NULL;
            nbottom = NULL;
        } else { 
            ntop = ntop->next;
            delete ntop->prev;
            ntop->prev = NULL;
        }
    }
}

/*
	Delete or remove the bottom node of the list.
	Once pop, you need to properly deallocate the memory for the node (not the data).
	If your list is currently empty, you don't have to do anything.
*/
void MList::pop_bottom(){
    if (!isEmpty()) {
        if (ntop == nbottom) { // one item in list
            delete nbottom;
            ntop = NULL;
            nbottom = NULL;
        } else {
            nbottom = nbottom->prev;
            delete nbottom->next;
            nbottom->next = NULL;
        }
    }
}

/*
	Note: RECURSION --- This function should be implemented using recursion.
	Search a node in the list that has data with the same name as the parameter.
	If one is found, return the pointer to the node.
	If one is not found, return NULL.
*/
Node* MList::search(Node* start, string name){
    if (isEmpty() || start == NULL) { // check if list is empty or start is NULL, then you don't need to search
        return NULL; 
    }
    if (start->nodeData->name == name) {
            return start;
    } else {
            start = search(start->next,name);
            return start; // return start if search traces all the way back to beginning
    }
}


//Swapping node a with node b.
void MList::swapNode(Node* a, Node*b){ 

    if (a == b) { 
        return;
    } else if (a->next == b) { // a is located before b
        removeNode(a);
        insertAfter(a, b);  
    } else if (a->prev == b) { // a is located after b
        removeNode(b);
        insertAfter(b,a);
    } else { // a and b are NOT adjacent and both somewhere in middle
        Node* aa = a->prev;
        Node* bb = b->prev;
        
        removeNode(a);
        removeNode(b);
        insertAfter(a, bb);
        insertAfter(b, aa);
    }
    
}

/*
	This function PERMANENTLY deletes a node from the list given a pointer to that node.
	You can assume that the node exists in the list - no need to search for the node.
*/
void MList::deleteNode(Node* a){
    removeNode(a); // isolate a then delete it
    delete a; 

}

/*
	Unlike the delete function above, this function does NOT permanently delete the node.
	What you need to do at the last step is to set the node's prev and next pointers to NULL.
	Again, you can assume that the node exists in the list - no need to search for the node.
	Note: this function will be useful
        when we want to insert the given node later at another position after you remove it from the list.
*/
void MList::removeNode(Node* a){
    if(a->prev != NULL && a->next != NULL) { //somewhere in the middle
       a->prev->next = a->next; //node before a has next point to node after a
       a->next->prev = a->prev; //node after a has pointer to node before a
       a->next = NULL;
       a->prev = NULL;
   } else if (a->prev != NULL && a->next == NULL) { //if a is last
       nbottom = nbottom->prev;
       a->prev->next = NULL;
       a->prev = NULL;
   } else if (a->prev == NULL && a->next != NULL) {//if a is first
       ntop = ntop->next;
       a->next->prev = NULL;
       a->next = NULL;
   } else { //if only thing in list
       ntop = NULL;
       nbottom = NULL;
   }
}

/*
	Insert node a after node b.
	Note: b can be NULL, Q: what does that mean?
    otherwise, you can assume that b exists in the list.
*/
void MList::insertAfter(Node *a, Node* b){
    if (isEmpty()) { // if list is empty, just add a to thr front
        ntop = a;
        nbottom = a;
        a->prev = NULL;
        a->next = NULL;
    } else if (b == NULL) { // if b is at the front
        a->next = ntop;
        ntop->prev = a;
        a->prev = NULL;
        ntop = a;
    } else if (b->next == NULL) { // if b is at the end
        b->next = a;
        a->prev = b;
        a->next = NULL;
        nbottom = a;
    } else { // if b is somethere in middle
        a->next = b->next;
        b->next->prev = a; //what is after b points to a
        b->next = a;
        a->prev = b;
    }
}


/*
	Note: RECURSION --- This function should be implemented using recursion.
	Implement a SELECTION SORT algorithm using recursion.
	The function takes in a start node.
	Things to keep in mind:
		1). sort should NOT be run if the list is empty.
		2). if mode = true, sort by name in alphabetical order
			(i.e., A-Za-z) based on ASCII number if mode = true
        3). if mode = false, sort by size in ascending order (low->high)
	You can search any online resources available to you (i.e. search 'selection sort')
	to understand the basic idea behind the selection sort algorithm.
    Note: 
        1). there can only be at most one loop in this function
        2). this function is private
            see sortByNameSelection and sortBySizeSelection for the calls to this function
*/
void MList::sortSelection(Node* start, bool mode){
    if (!isEmpty() && start != NULL) {
        Node* temp = start;
        Node* min = start;
        
        while (temp != NULL) {
            if (mode) { // sort alphabetically
                if (min->nodeData->name > temp->nodeData->name) {
                    min = temp;
                }
                temp = temp->next;
                
            } else { // sort by size, in ascending order
                if (min->nodeData->size > temp->nodeData->size) {
                    min = temp;
                }
                temp = temp->next;
            }
            
        }        
        swapNode(min, start);
        sortSelection(min->next, mode);
    } 

}


/*
	Note: RECURSION --- This function should be implemented using recursion.
	Implement an INSERTION SORT algorithm using recursion.
	The function takes in a start node.
	Things to keep in mind:
		1). sort should NOT be run if the list is empty.
		2). we are trying to sort by name in alphabetical order
			(i.e., A-Za-z) based on ASCII number.
	You can search any online resources available to you (i.e. search 'insertion sort')
	to understand the basic idea behind the insertion sort algorithm.
	The gif from the wikipedia page of this algorithm is the easiest to understand in my opinion
	Link: https://en.wikipedia.org/wiki/Insertion_sort
    Note: 
        1). there can only be at most one loop in this function
        2). this function is private, see sortByNameInsertion for the call to this function
*/
void MList::sortInsertion(Node* start){
    if (!isEmpty() && start != NULL && ntop != nbottom) {
        if (start == ntop) {
            sortInsertion(start->next);
            
        } else if (start->prev->nodeData->name < start->nodeData->name) {
            sortInsertion(start->next);
            
        } else {
            Node* previous =  start->prev;
            Node* after = start->next;
            Node* swap;
            while (previous != NULL) {
                if (previous->nodeData->name < start->nodeData->name) { // compare start to previous
                    swap = previous;
                    break; 
                }
                // move previous backwards
                previous = previous->prev;
            }

            removeNode(start);
            insertAfter(start, swap); // place start after previous if it's less than previous's value 

            if (start != nbottom) {
                sortInsertion(after); // sort using next item in list (after start)
            }
        }
    }

     
}


/*
	Note: RECURSION --- This function should be implemented using recursion.
	Traverse and print our list from node n to the top.
	we will seperate each node printed by the passed-in delimiter.
	If a node you encounter is a folder type, do

		cout<<....name.....<<delim;

	If a node you encounter is a file type, do

		cout<<....name.....<<"("<<..size..<<")"<<delim;

	Note: please do NOT include <<endl; (aka newline)
	Example output (assume that the delimiter is a single space):
    
		folder1 file1(0) folder2 file2(0)

    There should be no loop in this function
	See printBtT function for the call to this function.
    This function is private
*/
void MList::traverseToTop(Node* n, string delim){
    if (!isEmpty()) { // only traverse if list isn't empty
        if (n->nodeData->isFolder == false) { // if node is file type
            cout << n->nodeData->name << "(" << n->nodeData->size << ")" << delim;
        } else { // if node is folder type
            cout << n->nodeData->name << delim;
        }

        if (n->prev != NULL) { // recursion factor (traverse at previous node)
            traverseToTop(n->prev, delim);
        }
    } 
}

/*
	Note: RECURSION --- This function should be implemented using recursion.
	Traverse and print our list from node n to the bottom.
	we will seperate each node printed by the passed-in delimiter.
	If a node you encounter is a folder type, do

		cout<<....name.....<<delim;

	If a node you encounter is a file type, do

		cout<<....name.....<<"("<<..size..<<")"<<delim;

	Note: please do NOT include <<endl; (aka newline)
	Example output (assume that the delimiter is a single space):
    
		folder1 file1(0) folder2 file2(0)

    There should be no loop in this function
	See printTtB function for the call to this function.
    This function is private
*/
void MList::traverseToBottom(Node* n,string delim){ 
    if (!isEmpty()) { // only traverse if list isn't empty
        if (n->nodeData->isFolder == false) { // if node is file type
            cout << n->nodeData->name << "(" << n->nodeData->size << ")" << delim;
        } else { // if node is folder type
            cout << n->nodeData->name << delim;
        }

        if (n->next != NULL) { // recursion factor (traverse at next node)
            traverseToBottom(n->next, delim);
        }
    }
    
}

//------------------------------------------------------------------------------
//FUNCTIONS BELOW ARE COMPLETE, PLEASE DON'T CHANGE ANYTHING HERE
//------------------------------------------------------------------------------

//getting the pointer to the top node.
Node* MList::top(){
	return ntop;
}

//getting the pointer to the bottom node.
Node* MList::bottom(){
	return nbottom;
}

//call traverseToBottom to print all item in the list from bottom node to top node
//the list of items is separated by a given delimiter
void MList::printBtT(string delim){
	//create a temp pointer to hold bottom
	Node* tmp = nbottom;
	traverseToTop(tmp,delim);
}

//call traverseToBottom to print all item in the list from top node to bottom node
//the list of items is separated by a given delimiter
void MList::printTtB(string delim){
	Node* tmp = ntop;
	traverseToBottom(tmp,delim);
}

//call sortSelection function, mode = true = sort by name
//public member
void MList::sortByNameSelection(){
    bool mode = true;
    Node *tmp = ntop;
    sortSelection(tmp,mode);
}

//call sortSelection function, mode = false = sort by size
//public member
void MList::sortBySizeSelection(){
    bool mode = false;
    Node *tmp = ntop;
    sortSelection(tmp,mode);
}

//call sortInsertion function
//public member
void MList::sortByNameInsertion(){
    Node *tmp = ntop;
    sortInsertion(tmp);
}
