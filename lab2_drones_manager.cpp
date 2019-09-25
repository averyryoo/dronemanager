#include "lab2_drones_manager.hpp"



DronesManager::DronesManager() {
	first = NULL;
	last = NULL;
	size = 0;
}

DronesManager::~DronesManager() {
	DroneRecord* currNode = first;
	while (currNode) {
		DroneRecord* prev = currNode;
		currNode = currNode->next;
		delete prev;
		prev = NULL;
	}
}

bool operator==(const DronesManager::DroneRecord& lhs, const DronesManager::DroneRecord& rhs) {
	if (lhs.droneID != rhs.droneID) return false;
	if (lhs.range != rhs.range) return false;
	if (lhs.yearBought != rhs.yearBought) return false;
	if (lhs.droneType != rhs.droneType) return false;
	if (lhs.manufacturer != rhs.manufacturer) return false;
	if (lhs.description != rhs.description) return false;
	if (lhs.batteryType != rhs.batteryType) return false;
	return true;
}

unsigned int DronesManager::get_size() const {
	return size;
}

bool DronesManager::empty() const {
	if (first == NULL)
		return true;
	return false;
}

DronesManager::DroneRecord DronesManager::select(unsigned int index) const {
	if (size == 0) return DroneRecord(0);
	if (size <= index) return *last;


	DroneRecord* currNode = first;
	if (index == 0) return *currNode;
	for (int i = 0; i < index + 1; ++i) {
		currNode = currNode->next;
	}

	return *currNode;

}

unsigned int DronesManager::search(DroneRecord value) const {
	if (size == 0)
		return 0;
	DroneRecord* current = first;
	int count = 0;
	while (current != NULL) {
		if (value == *current)
			return count;
		++count;
		current = current->next;
	}
	return count;
}

void DronesManager::print() const {
	DroneRecord* current = first;
	while (current != NULL) {
		cout << current->droneID << endl;
		current = current->next;
	}
}

bool DronesManager::insert(DroneRecord value, unsigned int index) {
	return false;
}

bool DronesManager::insert_front(DroneRecord value) {
	if (first != NULL) {
		DroneRecord* current = first;
		first = new DroneRecord(value);
		first->next = current;
		first->prev = NULL;
		++size;
		return true;
	}
	else{
		first = new DroneRecord(value);
		first->next = NULL;
		first->prev = NULL;
		last = first;
		last->next = NULL;
		last->prev = NULL;
		++size;
		return true;
	}
	
	return false;
}

bool DronesManager::insert_back(DroneRecord value) {
	if (last != NULL) {
		DroneRecord* current = last;
		last = new DroneRecord(value);
		current->next = last;
		last->next = NULL;
		last->prev = current;
		++size;
		return true;
	}
	
	else {
		first = new DroneRecord(value);
		first->next = NULL;
		first->prev = NULL;
		last = first;
		last->next = NULL;
		last->prev = NULL;
		++size;
		return true;
	}
	return false;
}

bool DronesManager::remove(unsigned int index) {
	if( index < 1 || index > size)return false; // returns false if index is invalid
	
	//case 1: remove at the front
	else if( index == 1 ) remove_front();
	
	//case 2: remove at the end
	else if( index == size - 1) remove_back();
	
	
	
	//case 4: if list has zero elements
	else if (size == 0) return false;
	
	//case 5: if list has only one element
	else if (size == 1){
		first = NULL;
		last = NULL;
		size = 0;
	}
	
	//case 3: general case
	else {
		DroneRecord* node = first;
		for(int i = 1; i< index; i++){
			node = node->next; //move first pointer to the node
			node-> next -> prev = node -> prev; //change the next node
			node-> prev -> next = node -> next; //change the prev node
		}
	}
	
	return true;
}

bool DronesManager::remove_front() {
	if (size ==0) return false;
	else if (size == 1){
		first = NULL;
		last = NULL;
		size--;
		return true;
	}

	else{
		DroneRecord* temp = first;
		first = first->next; //shifts pointer to the node after the old head
		first-> prev = NULL; //changes the prev pointer of the new head to be NULL
		delete temp;
		size--;    
		return true;
	}
}

bool DronesManager::remove_back() {
	if (size == 0) return false;
	else if (size == 1){
		first = NULL;
		last = NULL;
		size--;
		return true;
	}

	else{
		DroneRecord* temp = last;
		last = last->prev; // shifts pointer to the node before the old head
		last-> next = NULL; //changes the next pointer of the new tail to be NULL
		delete temp;
		size--;
		return true;
	}
}

bool DronesManager::replace(unsigned int index, DroneRecord value) {
	DroneRecord *currDrone = first;
	DroneRecord *replace = new DroneRecord(value);
	replace -> next = NULL;
	replace -> prev = NULL;
	
	//case 1: invalid index
	if(index < 0 || index >= size) return false;
	
	//case 2: replace the head
	else if( index == 0){
		replace -> next = first-> next;
		replace -> prev = NULL; 
		first-> next -> prev = replace;
		first = replace; //changing first pointer to new replaced drone 
	}
	
	//case 3: replace the tail
	else if( index == size - 1){
		replace -> prev = last -> prev;
		replace -> next = NULL;
		last->prev->next = replace;
		last = replace; //changing last pointer to new replaced drone
	}
	//case 4: general case
	else{
		for(int i = 0; i < index; i++){
			currDrone = currDrone->next;
		}
		replace -> next = currDrone -> next;
		replace -> prev = currDrone -> prev;
		currDrone -> next -> prev = replace;
		currDrone -> prev->next = replace;
			
	}
	return true; 
}

bool DronesManager::reverse_list() {
	//loop to reverse the doubly linked list
	DroneRecord* currentNode = first;
	int reverseCounter = 0;
	
	while( currentNode ){
		
		//case 1: moving the head element to the tail
		if(reverseCounter == 0) {
			last = currentNode;
		}
		//case 2: moving the tail element to the head
		else if( reverseCounter == size - 1){
			first = currentNode;
		}
		DroneRecord *temp = currentNode -> prev;
		currentNode->prev = currentNode->next;
		currentNode->next = temp;		
		currentNode = currentNode->prev; //move the currentNode
		reverseCounter++;
	}
	
	return true;
}
