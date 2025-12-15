#include <catch2/catch_all.hpp>
#include "../template/hashTable.h"
#include <string>

struct Item {
    std::string key;
    int value;
};

static std::function<std::string(const Item&)> itemKey() {
    return [](const Item& item) { return item.key; };
}

TEST_CASE("HashTable: insert, find, erase, clear", "[hashtable]") {
    HashTable<Item, std::string> table(5);
    auto keyExtractor = itemKey();

    REQUIRE(table.empty());
    REQUIRE(table.insert(Item{"a", 1}, "a", keyExtractor));
    REQUIRE_FALSE(table.insert(Item{"a", 2}, "a", keyExtractor));
    REQUIRE(table.size() == 1);

    auto* found = table.find("a", keyExtractor);
    REQUIRE(found != nullptr);
    REQUIRE(found->value == 1);

    REQUIRE(table.erase("a", keyExtractor));
    REQUIRE_FALSE(table.erase("a", keyExtractor));
    REQUIRE(table.empty());

    table.insert(Item{"b", 2}, "b", keyExtractor);
    table.insert(Item{"c", 3}, "c", keyExtractor);
    REQUIRE(table.size() == 2);
    table.clear();
    REQUIRE(table.size() == 0);
    REQUIRE(table.begin() == table.end());
}

TEST_CASE("HashTable: emplace and iterators", "[hashtable]") {
    HashTable<Item, std::string> table(3);
    auto keyExtractor = itemKey();

    REQUIRE(table.emplace("x", keyExtractor, Item{"x", 10}));
    REQUIRE_FALSE(table.emplace("x", keyExtractor, Item{"x", 11}));
    REQUIRE(table.size() == 1);

    auto it = table.begin();
    REQUIRE(it != table.end());
    REQUIRE(it->value == 10);

    const auto& constTable = table;
    auto cit = constTable.cbegin();
    REQUIRE(cit != constTable.cend());
    REQUIRE(cit->value == 10);
}

TEST_CASE("HashTable: extract returns and removes element", "[hashtable]") {
    HashTable<Item, std::string> table(4);
    auto keyExtractor = itemKey();

    table.insert(Item{"k1", 5}, "k1", keyExtractor);
    table.insert(Item{"k2", 6}, "k2", keyExtractor);

    auto extracted = table.extract("k1", keyExtractor);
    REQUIRE(extracted.has_value());
    REQUIRE(extracted->key == "k1");
    REQUIRE(table.size() == 1);
    REQUIRE(table.find("k1", keyExtractor) == nullptr);

    auto missing = table.extract("missing", keyExtractor);
    REQUIRE_FALSE(missing.has_value());
}

TEST_CASE("HashTable: swap exchanges state", "[hashtable]") {
    HashTable<Item, std::string> first(3);
    HashTable<Item, std::string> second(3);
    auto keyExtractor = itemKey();

    first.insert(Item{"a", 1}, "a", keyExtractor);
    first.insert(Item{"b", 2}, "b", keyExtractor);
    second.insert(Item{"c", 3}, "c", keyExtractor);

    first.swap(second);

    REQUIRE(first.size() == 1);
    REQUIRE(second.size() == 2);
    REQUIRE(first.find("c", keyExtractor) != nullptr);
    REQUIRE(second.find("a", keyExtractor) != nullptr);
}

TEST_CASE("HashTable: merge moves unique nodes", "[hashtable]") {
    HashTable<Item, std::string> lhs(5);
    HashTable<Item, std::string> rhs(5);
    auto keyExtractor = itemKey();

    lhs.insert(Item{"a", 1}, "a", keyExtractor);
    lhs.insert(Item{"b", 2}, "b", keyExtractor);

    rhs.insert(Item{"b", 20}, "b", keyExtractor);
    rhs.insert(Item{"c", 30}, "c", keyExtractor);

    lhs.merge(rhs, keyExtractor);

    REQUIRE(lhs.size() == 3);
    REQUIRE(rhs.size() == 1);
    REQUIRE(lhs.find("c", keyExtractor) != nullptr);
    REQUIRE(rhs.find("b", keyExtractor) != nullptr);
}

TEST_CASE("HashTable: merge self is no-op", "[hashtable]") {
    HashTable<Item, std::string> table(3);
    auto keyExtractor = itemKey();
    table.insert(Item{"a", 1}, "a", keyExtractor);
    table.merge(table, keyExtractor);
    REQUIRE(table.size() == 1);
    REQUIRE(table.find("a", keyExtractor) != nullptr);
}

TEST_CASE("HashTable: move constructor and assignment", "[hashtable]") {
    HashTable<Item, std::string> source(3);
    auto keyExtractor = itemKey();
    source.insert(Item{"a", 1}, "a", keyExtractor);

    HashTable<Item, std::string> moved(std::move(source));
    REQUIRE(moved.size() == 1);
    REQUIRE(moved.find("a", keyExtractor) != nullptr);

    HashTable<Item, std::string> target(3);
    target = std::move(moved);
    REQUIRE(target.size() == 1);
    REQUIRE(target.find("a", keyExtractor) != nullptr);
}

TEST_CASE("HashTable: iterators on moved-from (bucket_count == 0)", "[hashtable]") {
    HashTable<Item, std::string> original(2);
    auto keyExtractor = itemKey();
    original.insert(Item{"a", 1}, "a", keyExtractor);

    HashTable<Item, std::string> moved(std::move(original));

    auto beginIt = original.begin();
    auto endIt = original.end();
    REQUIRE(beginIt == endIt);

    const auto& constRef = original;
    auto cbeginIt = constRef.begin();
    auto cendIt = constRef.end();
    REQUIRE(cbeginIt == cendIt);
}

