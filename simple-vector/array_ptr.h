// вставьте сюда ваш код для класса ArrayPtr
// внесите в него изменения, 
// которые позволят реализовать move-семантику
#pragma once

#include <algorithm>

template <typename Type>
class ArrayPtr {
public:
    ArrayPtr() = default;

 // Создаём массив из size элементов типа Type.
    explicit ArrayPtr(size_t size) {
        if (size == 0) return;
        raw_ptr_ = new Type[size];
    }

    explicit ArrayPtr(Type* raw_ptr) noexcept : raw_ptr_(raw_ptr) {}

    ArrayPtr(const ArrayPtr&) = delete;

    ~ArrayPtr() {
        delete[] raw_ptr_;
        raw_ptr_ = nullptr;
    }

    ArrayPtr& operator=(const ArrayPtr&) = delete;
 // Отпускаем владение массивом в памяти и возвращаем значение адреса массива
    [[nodiscard]] Type* Release() noexcept {
        auto temp = raw_ptr_;
        raw_ptr_ = nullptr;
        return temp;
    }

    Type& operator[](size_t index) noexcept {
        return *(raw_ptr_ + index);
    }

    const Type& operator[](size_t index) const noexcept {
        return *(raw_ptr_ + index);
    }

    explicit operator bool() const {
        return raw_ptr_ != nullptr;
    }

    Type* Get() const noexcept {
        return raw_ptr_;
    }

    // Обмениваем значения указателя на массив с объектом other
    void swap(ArrayPtr& other) noexcept {
        std::swap(raw_ptr_, other.raw_ptr_);
    }

private:
    Type* raw_ptr_ = nullptr;
};
