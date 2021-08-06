#include <iostream>

using namespace std;

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

            cout << endl;
        }

        void get(int index){
            return array[index];
        }
};

