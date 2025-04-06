#include "../std.h"
#include "../shell.h"

template <typename T>
Dictionary<T>::Dictionary() {
    capacity = 100;
    size = 0;
    data = (Entry<T>*)malloc(capacity * sizeof(Entry<T>));
}

template <typename T>
Dictionary<T>::~Dictionary() {
    free(data);
}

template <typename T>
void Dictionary<T>::resize() {
    capacity *= 2;
    Entry<T>* newData = (Entry<T>*)malloc(capacity * sizeof(Entry<T>)); 

    for (int i = 0; i < size; i++) {
        newData[i] = data[i];
    }

    free(data);
    data = newData;
}

template <typename T>
void Dictionary<T>::add(const String& key, const T& value) {
    if (size == capacity) {
        resize();
    }

    data[size].key = key;
    data[size].value = value;
    size++;
}

template <typename T>
T* Dictionary<T>::find(const String& key) {
    for (int i = 0; i < size; i++) {
        if (data[i].key == key) {
            return &data[i].value;
        }
    }
    return nullptr;
}


template class Dictionary<command>;
