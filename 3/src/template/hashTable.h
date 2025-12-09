#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <functional>
#include <memory>
#include <stdexcept>
#include <cstddef>
#include <iterator>
#include <string>
#include <list>
#include <vector>
#include <type_traits>

/// Реализация хеш-таблицы, перемешанной сцеплением.
/// Использует std::hash по умолчанию для хеширования ключей.
template<typename T, typename Key = T, typename Hasher = std::hash<Key>, typename KeyEqual = std::equal_to<Key>>
class HashTable {
private:
    size_t bucket_count_;
    size_t size_;
    std::unique_ptr<std::list<T>[]> buckets_;
    Hasher hasher_;
    KeyEqual keyEqual_;

    template<typename K>
    size_t bucket_index(const K& key) const {
        return hasher_(key) % bucket_count_;
    }

public:
    // Named requirements: Container typedefs
    using value_type = T;
    using key_type = Key;
    using hasher = Hasher;
    using key_equal = KeyEqual;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;

    explicit HashTable(size_t bucket_count = 101) : bucket_count_(bucket_count), size_(0), buckets_(std::make_unique<std::list<T>[]>(bucket_count_)) {}

    ~HashTable() = default;

    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;

    HashTable(HashTable&& other) noexcept 
        : bucket_count_(other.bucket_count_), size_(other.size_), 
          buckets_(std::move(other.buckets_)), hasher_(std::move(other.hasher_)),
          keyEqual_(std::move(other.keyEqual_)) {
        other.bucket_count_ = 0;
        other.size_ = 0;
    }

    HashTable& operator=(HashTable&& other) noexcept {
        if (this != &other) {
            bucket_count_ = other.bucket_count_;
            size_ = other.size_;
            buckets_ = std::move(other.buckets_);
            hasher_ = std::move(other.hasher_);
            keyEqual_ = std::move(other.keyEqual_);
            other.bucket_count_ = 0;
            other.size_ = 0;
        }
        return *this;
    }

    /**
     * @brief Вставка элемента в таблицу с проверкой дубликатов
     * @param value Значение для вставки
     * @param key Ключ для определения бакета и проверки дубликатов
     * @param keyExtractor Функция извлечения ключа из значения
     * @return true, если вставка успешна, false если элемент с таким ключом уже существует
     */
    template<typename K>
    bool insert(const T& value, const K& key, const std::function<Key(const T&)>& keyExtractor) {
        size_t idx = bucket_index(key);
        auto& bucket = buckets_[idx];

        for (const auto& item : bucket) {
            if (keyEqual_(keyExtractor(item), key)) {
                return false; 
            }
        }

        bucket.push_front(value);
        ++size_;
        return true;
    }

    /**
     * @brief Вставка элемента в таблицу с проверкой дубликатов через keyExtractor (move-семантика)
     * @param value Значение для вставки
     * @param key Ключ для определения бакета и проверки дубликатов
     * @param keyExtractor Функция извлечения ключа из значения
     * @return true, если вставка успешна, false если элемент с таким ключом уже существует
     */
    template<typename K>
    bool insert(T&& value, const K& key, const std::function<Key(const T&)>& keyExtractor) {
        size_t idx = bucket_index(key);
        auto& bucket = buckets_[idx];
 
        for (const auto& item : bucket) {
            if (keyEqual_(keyExtractor(item), key)) {
                return false;
            }
        }
        
        bucket.push_front(std::move(value));
        ++size_;
        return true;
    }

    /**
     * @brief Поиск элемента по ключу
     * @param key Ключ для поиска
     * @param keyExtractor Функция извлечения ключа из значения
     * @return Указатель на найденный элемент или nullptr
     */
    template<typename K>
    T* find(const K& key, const std::function<Key(const T&)>& keyExtractor) {
        size_t idx = bucket_index(key);
        auto& bucket = buckets_[idx];

        for (auto& item : bucket) {
            if (keyEqual_(keyExtractor(item), key)) {
                return &item;
            }
        }

        return nullptr;
    }

    /**
     * @brief Удаление элемента по ключу
     * @param key Ключ для удаления
     * @param keyExtractor Функция извлечения ключа из значения
     * @return true, если элемент был найден и удален
     */
    template<typename K>
    bool erase(const K& key, const std::function<Key(const T&)>& keyExtractor) {
        size_t idx = bucket_index(key);
        auto& bucket = buckets_[idx];

        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (keyEqual_(keyExtractor(*it), key)) {
                bucket.erase(it);
                --size_;
                return true;
            }
        }

        return false;
    }

    size_t size() const noexcept { return size_; }
    bool empty() const noexcept { return size_ == 0; }

    /**
     * @brief Очистка таблицы
     */
    void clear() noexcept {
        for (size_t i = 0; i < bucket_count_; ++i) {
            buckets_[i].clear();
        }
        size_ = 0;
    }

    // Forward iterator
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference =    T&;

        iterator() : table_(nullptr), bucket_idx_(0), list_it_() {}

        iterator(HashTable* table, size_t bucket_idx, typename std::list<T>::iterator list_it)
            : table_(table), bucket_idx_(bucket_idx), list_it_(list_it) {}

        reference operator*() const { return *list_it_; }
        pointer operator->() const { return &*list_it_; }

        iterator& operator++() {
            ++list_it_;
            if (list_it_ == table_->buckets_[bucket_idx_].end()) {
                advance_to_next_nonempty(++bucket_idx_);
            }
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            ++*this;
            return tmp;
        }

        bool operator==(const iterator& other) const {
            return table_ == other.table_ && bucket_idx_ == other.bucket_idx_ && list_it_ == other.list_it_;
        }
        
        bool operator!=(const iterator& other) const { return !(*this == other); }

    private:
        HashTable* table_;
        size_t bucket_idx_;
        typename std::list<T>::iterator list_it_;

        void advance_to_next_nonempty(size_t start) {
            if (!table_ || table_->bucket_count_ == 0) { 
                bucket_idx_ = 0;
                return; 
            }

            for (size_t i = start; i < table_->bucket_count_; ++i) {
                if (!table_->buckets_[i].empty()) {
                    bucket_idx_ = i;
                    list_it_ = table_->buckets_[i].begin();
                    return;
                }
            }

            bucket_idx_ = table_->bucket_count_ > 0 ? table_->bucket_count_ - 1 : 0;
            list_it_ = table_->bucket_count_ > 0 ? table_->buckets_[bucket_idx_].end() : typename std::list<T>::iterator();
        }

        friend class HashTable;
    };

    // Const forward iterator
    class const_iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        const_iterator() : table_(nullptr), bucket_idx_(0), list_it_() {}

        const_iterator(const HashTable* table, size_t bucket_idx, typename std::list<T>::const_iterator list_it)
            : table_(table), bucket_idx_(bucket_idx), list_it_(list_it) {}

        reference operator*() const { return *list_it_; }
        pointer operator->() const { return &*list_it_; }

        const_iterator& operator++() {
            ++list_it_;
            if (list_it_ == table_->buckets_[bucket_idx_].end()) {
                advance_to_next_nonempty(++bucket_idx_);
            }
            return *this;
        }

        const_iterator operator++(int) {
            const_iterator tmp = *this;
            ++*this;
            return tmp;
        }

        bool operator==(const const_iterator& other) const {
            return table_ == other.table_ && bucket_idx_ == other.bucket_idx_ && list_it_ == other.list_it_;
        }
        bool operator!=(const const_iterator& other) const { return !(*this == other); }

    private:
        const HashTable* table_;
        size_t bucket_idx_;
        typename std::list<T>::const_iterator list_it_;

        void advance_to_next_nonempty(size_t start) {
            if (!table_ || table_->bucket_count_ == 0) { 
                bucket_idx_ = 0;
                return; 
            }
            for (size_t i = start; i < table_->bucket_count_; ++i) {
                if (!table_->buckets_[i].empty()) {
                    bucket_idx_ = i;
                    list_it_ = table_->buckets_[i].begin();
                    return;
                }
            }
            // Достигли конца - устанавливаем end итератор
            bucket_idx_ = table_->bucket_count_ > 0 ? table_->bucket_count_ - 1 : 0;
            list_it_ = table_->bucket_count_ > 0 ? table_->buckets_[bucket_idx_].end() : typename std::list<T>::const_iterator();
        }

        friend class HashTable;
    };

    // Проверка корректности итераторов как ForwardIterator
    static_assert(std::forward_iterator<iterator>);
    static_assert(std::forward_iterator<const_iterator>);

    iterator begin() noexcept {
        if (bucket_count_ == 0) {
            return end();
        }

        for (size_t i = 0; i < bucket_count_; ++i) {
            if (!buckets_[i].empty()) {
                return iterator(this, i, buckets_[i].begin());
            }
        }

        return end();
    }

    iterator end() noexcept {
        if (bucket_count_ == 0) {
            return iterator(this, 0, typename std::list<T>::iterator());
        }

        return iterator(this, bucket_count_ - 1, buckets_[bucket_count_ - 1].end());
    }

    const_iterator begin() const noexcept {
        if (bucket_count_ == 0) {
            return end();
        }

        for (size_t i = 0; i < bucket_count_; ++i) {
            if (!buckets_[i].empty()) {
                return const_iterator(this, i, buckets_[i].begin());
            }
        }

        return end();
    }

    const_iterator end() const noexcept {
        if (bucket_count_ == 0) {
            return const_iterator(this, 0, typename std::list<T>::const_iterator());
        }
        
        return const_iterator(this, bucket_count_ - 1, buckets_[bucket_count_ - 1].end());
    }

    const_iterator cbegin() const noexcept { return begin(); }
    const_iterator cend() const noexcept { return end(); }
};

#endif

