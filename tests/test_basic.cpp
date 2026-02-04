#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_range.hpp>
#include <trompeloeil.hpp>

#include <algorithm>
#include <string>
#include <vector>

// --- Catch2: Unit testing ---

unsigned int Factorial(unsigned int number)
{
    return number <= 1 ? number : Factorial(number - 1) * number;
}

TEST_CASE("Factorials are computed", "[factorial]")
{
    REQUIRE(Factorial(1) == 1);
    REQUIRE(Factorial(2) == 2);
    REQUIRE(Factorial(3) == 6);
    REQUIRE(Factorial(10) == 3628800);
}

// --- Trompeloeil: Mocking ---

class IDatabase {
public:
    virtual ~IDatabase() = default;
    virtual bool connect(const std::string& host) = 0;
    virtual std::string query(const std::string& sql) = 0;
};

class MockDatabase : public IDatabase {
public:
    MAKE_MOCK1(connect, bool(const std::string&), override);
    MAKE_MOCK1(query, std::string(const std::string&), override);
};

TEST_CASE("Trompeloeil mock example", "[mock]")
{
    MockDatabase db;
    REQUIRE_CALL(db, connect("localhost")).RETURN(true);
    REQUIRE_CALL(db, query("SELECT 1")).RETURN("1");

    REQUIRE(db.connect("localhost") == true);
    REQUIRE(db.query("SELECT 1") == "1");
}

// --- Catch2 Generators: Property-like testing ---

TEST_CASE("Addition is commutative", "[property]")
{
    auto a = GENERATE(range(-100, 100));
    auto b = GENERATE(range(-100, 100));
    REQUIRE(a + b == b + a);
}

TEST_CASE("String reversal is involutory", "[property]")
{
    auto str = GENERATE(as<std::string>{}, "hello", "world", "", "a", "abcdef", "12345");
    std::string reversed(str.rbegin(), str.rend());
    std::string double_reversed(reversed.rbegin(), reversed.rend());
    REQUIRE(str == double_reversed);
}

TEST_CASE("Sorting is idempotent", "[property]")
{
    auto vec = GENERATE(
        std::vector<int>{},
        std::vector<int>{1},
        std::vector<int>{3, 1, 2},
        std::vector<int>{5, 4, 3, 2, 1},
        std::vector<int>{1, 1, 1, 1}
    );
    auto sorted_once = vec;
    std::sort(sorted_once.begin(), sorted_once.end());
    auto sorted_twice = sorted_once;
    std::sort(sorted_twice.begin(), sorted_twice.end());
    REQUIRE(sorted_once == sorted_twice);
}
