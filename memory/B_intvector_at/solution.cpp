#include <iostream>
#include <stdexcept>

class IntVector {
private:
  int *data = nullptr;
  size_t size = 0;
  size_t capacity = 0;

  void expand_storage();
  void reallocate(size_t new_capacity);

public:
  IntVector() : data(nullptr), size(0), capacity(0) {}
  IntVector(size_t n) : data(new int[n]()), size(n), capacity(n) {};

  ~IntVector() { delete[] data; }

  IntVector(const IntVector &) = delete;
  IntVector &operator=(const IntVector &) = delete;

  IntVector(IntVector &&other) noexcept
      : data(other.data), size(other.size), capacity(other.capacity) {
    other.data = nullptr;
    other.size = 0, other.capacity = 0;
    // data(std::exchange(other.data, nullptr)), size(std::exchange(other.size,
    // 0))
  };
  IntVector &operator=(IntVector &&other) noexcept {
    if (this != &other) {
      delete[] data;
      data = other.data;
      size = other.size;
      capacity = other.capacity;

      other.data = nullptr;
      other.size = 0;
      other.capacity = 0;
    }
    return *this;
  };

  int &operator[](size_t i) { return data[i]; }

  const int &operator[](size_t i) const { return data[i]; }

  int &at(size_t i) {
    if (i >= size) {
      throw std::out_of_range("index out of bounds");
    }
    return data[i];
  }
  const int &at(size_t i) const {
    if (i >= size) {
      throw std::out_of_range("index out of bounds");
    }
    return data[i];
  }

  void push_back(int value) {
    if (size >= capacity) {
      expand_storage();
    }
    data[size++] = value;
  }

  void expand_storage() {
    size_t new_capacity = (capacity == 0) ? 2 : (capacity * 2);
    reallocate(new_capacity);
  }

  reallocate(size_t new_capacity) {
    if (new_capacity < size) {
      new_capacity = size;
    }
    int *new_data = new int[new_capacity];
    for (size_t i = 0; i < size; ++i) {
      new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
    capacity = new_capacity;
  }
  void reserve(size_t new_capacity) {
    if (new_capacity > capacity) {
      reallocate(new_capacity);
    }
  }

  void shrink_to_fit() {
    if (capacity > size) {
      // IntVector v(size);
      // std::swap(v, data);
      reallocate(size);
    }
  }

  void clear() { size = 0; }

  int *begin() { return data; }
  int *end() { return data + size; }
  const int *begin() const { return data; }
  const int *end() const { return data + size; }

  bool empty() const { return size == 0; }

  size_t get_capacity() const { return capacity; }
};

int main() {
  IntVector vector(5);

  try {
    vector.at(1) = 25;

    std::cout << "Element at index 1 modified to: " << vector.at(1)
              << std::endl;

    std::cout << "Attempting to access index 10: ";
    std::cout << vector.at(10) << std::endl;
  } catch (const std::out_of_range &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  IntVector v2(std::move(vector));
  std::cout << "v2[1] = " << v2[1] << std::endl;

  return 0;
}
