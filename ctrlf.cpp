#include <iostream>
#include <string>
#include <stdint.h>

using namespace std;


namespace utils{
    int hash(uint32_t value, int attempt, int capacity){
            uint32_t x = ((value % capacity) + attempt) % capacity;
            return x;
        }

    uint32_t calculate_key(string kmmer, int kmmer_size){
        uint32_t key = 0;
        for (int i = 0; i < kmmer_size; i++){
            int ascii_value = int(kmmer[i]);
            key = 128 * key + ascii_value;
        }
        return key;
    }

    bool check_equal(string str, string text, int skip_letters, int position){
        for (int i = skip_letters; i < str.length(); i++){
            if (str[i] != text[i + position])
                return false;
        }
        return true;          
    }

}

template<typename V>
class DynamicArray{
    private:
        V* array;
        unsigned int len;
        unsigned int next_index; 

    public:
        DynamicArray(int size){
            len = size;
            array = new V[len];
            next_index = 0;
        }

        void append(V value){
            if (next_index >= len) {
                expand();
            }

            array[next_index] = value;
            next_index += 1;
        }

        void expand() {
            V *temp = new V[len*2];
            for (int i = 0; i < len; i++){
                temp[i] = array[i];
            }

            delete array;
            array = temp;
            len = len * 2;
        }

        void show(){
            for (int i = 0; i < next_index; i++){
                cout << array[i] << ", ";
            }
        }

        V get(int index){
            return array[index];
        }

        int size(){
            return next_index;
        }
};

template<typename K, typename V>
struct HashNode{
    DynamicArray<V> * value;
    K key;

    HashNode(K init_key){
        value = new DynamicArray<V>(1);
        key = init_key;
    }
};

template<typename K, typename V>
class HashMap{
    private:
        unsigned int size;
        unsigned int capacity;
        HashNode<K,V> ** Table;

        void expand(){
            int new_capacity = capacity*2 + 1;
            HashNode<K,V> ** temp = new HashNode<K,V>*[new_capacity];
            for (int i = 0; i < new_capacity; i++){
                temp[i] = nullptr;
            }

            for (int i = 0; i < capacity; i++){
                HashNode<K,V> * node = Table[i];
                
                if(node == nullptr){
                    continue;
                }
                
                int attempt = 0;
                unsigned int index = utils::hash(node->key, attempt, new_capacity);
                while (temp[index] != nullptr){
                    attempt++;
                    index = utils::hash(node->key, attempt, new_capacity);
                }

                temp[index] = node;
            }
            
            delete Table;
            Table = temp;
            capacity = new_capacity;
        }

    public:
        HashMap(unsigned int init_capacity){
            capacity = init_capacity;
            size = 0;
            Table = new HashNode<K,V>*[capacity];
            
            for (int i = 0; i < capacity; i++){
                Table[i] = nullptr;
            }          
        }

        void push(K key, V value){
            // Verifying Load Factor
            if(float(size)/float(capacity) >= 0.5){
                expand();
            }

            unsigned int attempt = 0;
            unsigned int index = utils::hash(key, attempt, capacity);
            while(Table[index] != nullptr && Table[index]->key != key){
                attempt++;
                index = utils::hash(key, attempt, capacity);
            }

            if(Table[index] == nullptr){
                size++;

                HashNode<K,V> * node = new HashNode<K,V>(key);
                Table[index] = node;
                node->value->append(value);
            }            
            else if(Table[index]->key == key){
                Table[index]->value->append(value);
            }
        }

        DynamicArray<V>* get(K key){
            int attempt = 0;
            int index = utils::hash(key, attempt, capacity);
            while(Table[index] != nullptr){
                if (attempt > capacity){
                    return new DynamicArray<V>(1);
                }
                
                if (Table[index]->key == key){
                    return Table[index]->value;
                }
                
                attempt++;
                index = utils::hash(key, attempt, capacity);
            }

            return new DynamicArray<V>(1);
        }

        int len(){
            return size;
        }

        int cap(){
            return capacity;
        }

        int highest_consecutive(){
            int highest = 0;
            int count = 0;
            for (int i = 0; i < capacity; i++){
                if (Table[i] != nullptr){
                    count += 1;
                    if (count > highest)
                        highest = count;
                }
                else{
                    count = 0;
                }
            }

            return highest;
        }

        void print(){
            for (int i = 0; i < capacity; i++){
                if (Table[i] != nullptr){
                    cout << "key = " << Table[i]->key 
                     <<"  value = ";
                    Table[i]->value->show();
                    cout << endl;
                }
            }
        }
    
};


int main() {
    int kmmer_size;
    int init_capacity;

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> kmmer_size >> init_capacity;

    int line_count;
    string foo;

    cin >> foo >> line_count;

    string text = "";
    cin.ignore();
    for (int i = 0; i < line_count; i++) {
        string new_line;
        getline(cin, new_line);
        text += new_line;
        text += "\n";
    }

    HashMap<uint32_t, int> * map = new HashMap<uint32_t, int>(init_capacity);
    for (int i = 0; i <= text.length() - kmmer_size ; i++) {
        string kmmer = text.substr(i, kmmer_size);

        uint32_t key = utils::calculate_key(kmmer, kmmer_size);
        map->push(key, i);
    }

    int consults_count = 0;
    cin >> foo >> consults_count;
    cin.ignore();
    for (int i = 0; i < consults_count; i++){
        string word;
        getline(cin, word);

        string kmmer = word.substr(0, kmmer_size);

        DynamicArray<int> * possible_locations = map->get(utils::calculate_key(kmmer, kmmer_size));
        cout << i << ": ";
        bool first = true;
        for (int j = 0; j < possible_locations->size(); j++) {
            int current_location = possible_locations->get(j);
            if (utils::check_equal(word, text, kmmer_size, current_location)) {
                if (!first){
                    cout << " ";
                }
                else{
                    first = false;
                }
                cout << current_location;
            }
        }
        cout << endl;
    }

    cout << map->len() << " ";
    cout << map->cap() << " ";
    cout << map->highest_consecutive() << endl;    
}
