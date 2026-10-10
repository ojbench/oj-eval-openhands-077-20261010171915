// CrossArray implementation without using STL
#ifndef CROSSARRAY_HPP
#define CROSSARRAY_HPP

namespace sjtu {
class CrossArray {
private:
    int **data; // pointers to each sub-array
    int *len;   // length of each sub-array
    int capacity; // maximum number of sub-arrays
    int count;    // number of inserted sub-arrays
public:
    explicit CrossArray(int lines) : capacity(lines), count(0) {
        data = new int*[capacity];
        len = new int[capacity];
        for (int i = 0; i < capacity; ++i) {
            data[i] = nullptr;
            len[i] = 0;
        }
    }

    // Copy constructor – deep copy
    CrossArray(const CrossArray &o) : capacity(o.capacity), count(o.count) {
        data = new int*[capacity];
        len = new int[capacity];
        for (int i = 0; i < capacity; ++i) {
            if (o.data[i]) {
                len[i] = o.len[i];
                data[i] = new int[len[i]];
                for (int j = 0; j < len[i]; ++j) {
                    data[i][j] = o.data[i][j];
                }
            } else {
                data[i] = nullptr;
                len[i] = 0;
            }
        }
    }
    // Copy assignment – deep copy
    CrossArray &operator=(const CrossArray &o) {
        if (this != &o) {
            // clean current resources
            for (int i = 0; i < capacity; ++i) {
                delete [] data[i];
            }
            delete [] data;
            delete [] len;
            // copy new state
            capacity = o.capacity;
            count = o.count;
            data = new int*[capacity];
            len = new int[capacity];
            for (int i = 0; i < capacity; ++i) {
                if (o.data[i]) {
                    len[i] = o.len[i];
                    data[i] = new int[len[i]];
                    for (int j = 0; j < len[i]; ++j) {
                        data[i][j] = o.data[i][j];
                    }
                } else {
                    data[i] = nullptr;
                    len[i] = 0;
                }
            }
        }
        return *this;
    }



    CrossArray &WhichGreater(CrossArray &o) {
        long long total_this = 0, total_o = 0;
        for (int i = 0; i < capacity; ++i) {
            if (data[i]) total_this += len[i];
        }
        for (int i = 0; i < o.capacity; ++i) {
            if (o.data[i]) total_o += o.len[i];
        }
        if (total_o > total_this) return o;
        return *this;
    }

    bool IsSame(const CrossArray &o) {
        // true only if both objects share the same underlying storage block
        return data == o.data;
    }

    bool InsertArrays(const int *Input, int size) {
        if (count >= capacity) return false;
        int idx = count;
        data[idx] = new int[size];
        len[idx] = size;
        for (int i = 0; i < size; ++i) {
            data[idx][i] = Input[i];
        }
        ++count;
        return true;
    }

    void AppendArrays(const int *Input, int Line, int size) {
        // Line is guaranteed to be valid and already inserted
        int oldlen = len[Line];
        int newlen = oldlen + size;
        int *newarr = new int[newlen];
        for (int i = 0; i < oldlen; ++i) newarr[i] = data[Line][i];
        for (int i = 0; i < size; ++i) newarr[oldlen + i] = Input[i];
        delete [] data[Line];
        data[Line] = newarr;
        len[Line] = newlen;
    }

    void DoubleCrossLength() {
        int newcap = capacity * 2;
        int **newdata = new int*[newcap];
        int *newlen = new int[newcap];
        for (int i = 0; i < capacity; ++i) {
            newdata[i] = data[i];
            newlen[i] = len[i];
        }
        for (int i = capacity; i < newcap; ++i) {
            newdata[i] = nullptr;
            newlen[i] = 0;
        }
        delete [] data;
        delete [] len;
        data = newdata;
        len = newlen;
        capacity = newcap;
    }

    // Non-const overload for AtArray
    int *AtArray(int i) {
        return data[i];
    }
    const int *AtArray(int i) const {
        return data[i];
    }

    int &At(int i, int j) {
        return data[i][j];
    }

    ~CrossArray() {
        for (int i = 0; i < capacity; ++i) {
            delete [] data[i];
        }
        delete [] data;
        delete [] len;
    }
};
} // namespace sjtu

#endif // CROSSARRAY_HPP
