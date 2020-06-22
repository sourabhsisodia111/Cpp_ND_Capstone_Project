#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <vector>

template<typename T>
class Array1D {
private:
    std::vector<T> data;
    unsigned int nsize;

public:
    Array1D() { nsize = 0; }
    explicit Array1D(const unsigned int &x) : nsize(x) {
        data.resize(nsize);
        zero();
    }

    ~Array1D() {
        data.clear();
        data.shrink_to_fit();
    }

    int get_size() { return nsize; }
    void set_size(const unsigned int &x) {
        nsize = x;
        data.resize(nsize);
    }

    void zero() {
        std::fill(data.begin(), data.end(), 0);
    }

    void add_element(T x) {
        data.push_back(x);
        nsize++;
    }

    T sum() {
        return std::accumulate(data.begin(), data.end(), 0);
    }

    virtual void print() {
        for (int i = 0; i < nsize; i++) {
            std::cout << data[i] << " ";
        }
    }

    virtual void reset() {
        data.clear();
        data.shrink_to_fit();
        nsize = 0;
    }

    /* Array indexing operator */
    T &operator()(unsigned int x) {
        if (x >= nsize) {
            throw std::logic_error("OOB access");
        }
        return data[x];
    }

    /* Set each matrix elements equal to the same number */
    T &operator=(T number) {
        std::fill(data.begin(), data.end(), number);
    }
};

template<typename T>
class Array2D : public Array1D<T> {
private:
    std::vector<T> data;
    unsigned int sizeX, sizeY, nsize;
public:
    Array2D() {};
    Array2D(const unsigned int &x, const unsigned int &y)
            : sizeX(x), sizeY(y) {
        nsize = sizeX * sizeY;
        data.resize(nsize);
    }
    ~Array2D() {
        data.clear();
        data.shrink_to_fit();
    }

    int get_ncol() { return sizeX; }
    int get_nrow() { return sizeY; }
    void set_size(const unsigned int &x, const unsigned int &y) {
        sizeX = x;
        sizeY = y;
        nsize = sizeX * sizeY;
        data.resize(nsize);
    }
    void print() {
        for (int i = 0; i < sizeY; i++) {
            for (int j = 0; j < sizeX; j++) {
                std::cout << data[sizeX * i + j] << " ";
            }
            std::cout << "\n";
        }
    }
    void reset() {
        data.clear();
        data.shrink_to_fit();
        sizeX = 0;
        sizeY = 0;
        nsize = 0;
    }

    /* Array indexing operator */
    T &operator()(unsigned int x, unsigned int y) {
        if (x >= sizeX || y >= sizeY) {
            throw std::logic_error("OOB access");
        }
        return data[sizeX * y + x];
    }
};

#endif //ARRAY_H
