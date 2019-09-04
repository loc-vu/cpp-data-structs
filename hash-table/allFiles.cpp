#include<iostream> 
using namespace std;

template<typename K, typename V>
class HashNode {
public:
	K key;
	V val;
	HashNode<K, V>* next;

	HashNode(K key, V val);

};

template <typename K, typename V>
class HashTable
{
public:
	HashTable(int s); // Constructor 

  ~HashTable();

	// inserts a key into hash table 
	void insertItem(K key, V val);
  void insertItem(HashNode<K,V>* node);

	// deletes a key from hash table 
	void deleteItem(K key);

	void displayHash();

private: 
  int capacity; // No. of buckets 
  int size;

	// Pointer to an array containing buckets 
	HashNode<K, V>** table;

	// hash function to map values to key 
	int hashFunction(K key);

  void expandCapacity();

};



template<typename K, typename V>
HashNode<K,V>::HashNode(K k, V v):key(k), val(v), next() {}


template <typename K, typename V>
HashTable<K,V>::HashTable(int cap)
{
	this->capacity = cap;
  this->size = 0;
	this->table = new HashNode<K, V>*[this->capacity];

	for (int i = 0; i < size; i++) {
		this->table[i] = NULL;
	}
}

template <typename K, typename V>
HashTable<K,V>::~HashTable() {
  for(int i = 0; i < this->capacity; i++) {
    HashNode<K,V>* cur = table[i];

    while(cur != NULL) {
      HashNode<K,V>* prev = cur;
      cur = cur->next;
      delete prev;

    }

    delete table[i];

  }

  delete [] table;
}

template <typename K, typename V>
void HashTable<K,V>::insertItem(K key, V val)
{
  //expandCapacity();
	int index = hashFunction(key);
	
	HashNode<K,V>* prev = NULL;
	HashNode<K,V>* curr = this->table[index];

	while (curr != NULL && curr->key != key) {
		prev = curr;
		curr = curr->next;
	}

	if (curr == NULL) {
		curr = new HashNode<K,V>(key, val);

		if (prev == NULL) {
			this->table[index] = curr;
		}
		else {
			prev->next = curr;
		}

    this->size += 1;
	}
	else {
		curr->val = val;
	}

}

template <typename K, typename V>
void HashTable<K,V>::insertItem(HashNode<K,V>* node) {
  insertItem(node->key, node->val);


}


//TODO: NOT WORKING - SEG. Fault
/*
template <typename K, typename V>
void HashTable<K,V>::expandCapacity() {
  double loadFactor = this->size / (double)this->capacity;
  if(loadFactor < .75) {
    return;
  }

  int oldcap = this->capacity;
  this->capacity = oldcap * 2;

  HashTable<K,V>* newTable = new HashTable<K,V>(capacity);

  for(int i = 0; i < oldcap; i++){

    HashNode<K,V>* prev = NULL;
    HashNode<K,V>* cur = this->table[i];

    while(cur != NULL) {
      newTable->insertItem(cur);
      prev = cur;
      cur = cur->next;
      delete prev;

    }

    delete table[i];

  }

  delete table;
  this = newTable;

}

*/

template <typename K, typename V>
void HashTable<K,V>::deleteItem(K key)
{
	// get the hash index of key 
	int index = hashFunction(key);

	HashNode<K,V>* prev = NULL;
	HashNode<K,V>* curr = this->table[index];

	while (curr != NULL && curr->key != key) {
		prev = curr;
		curr = curr->next;
	}

//TODO: INCORRECT
	if (prev != NULL && curr != NULL) {
		prev->next = curr->next;
		delete curr;
	}
	else if(prev == NULL && curr != NULL){
		this->table[index] = curr->next;
	}

}

template <typename K, typename V>
int HashTable<K,V>::hashFunction(K key) {
	return (key % this->capacity);
}

// function to display hash this->table 
template <typename K, typename V>
void HashTable<K,V>::displayHash() {
	for (int i = 0; i < this->capacity; i++) {
		cout << i;
		HashNode<K,V>* cur = this->table[i];

		while (cur != NULL) {
			cout << "---> (" << cur->key << " , " << cur->val << ")";
			cur = cur->next;
		}
		cout << endl;
	}

  cout << this->size;
}

int main()
{
	// array that contains keys to be mapped 
	int n = 100;

	// insert the keys into the hash table 
	HashTable<int, int> h(2); 

  for (int i = 0; i < n; i++)
		h.insertItem(i, i);


	h.displayHash();

	return 0;
}
