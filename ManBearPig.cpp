#include <cstddef>
#include <iostream>

// этот класс уже определён выше
struct Unit  
{
    explicit Unit(size_t id) 
        : id_(id) 
    {
        std::cout << __func__ << std::endl;
    }

    size_t id() const { return id_; }

// private:
    size_t id_;
};

// базовый класс для животных
struct Animal : virtual Unit
{
    // name хранит название животного
    // "bear" для медведя
    // "pig" для свиньи
    Animal(std::string const & name, size_t id) : Unit(id), name_(name) 
    {
        std::cout << __func__ << std::endl;
    }
    // ...

    std::string const& name() const { return name_; }
private:
    std::string name_;
};

// класс для человека
struct Man : virtual Unit
{
    explicit Man(size_t id) : Unit(id) 
    {
        std::cout << __func__ << std::endl;
    }
    // ...
};

// класс для медведя
struct Bear : Animal
{
    explicit Bear(size_t id) : Unit(id), Animal("bear", id)
    {
        std::cout << __func__ << std::endl;
    }
    // ...
};

// класс для свиньи
struct Pig : Animal
{
    explicit Pig(size_t id) : Unit(id), Animal("pig", id)
    {
        std::cout << __func__ << std::endl;
    }
    // ...
};

// класс для челмедведосвина
struct ManBearPig : Man, Bear, Pig
{
    ManBearPig(size_t id) : Unit(id), Man(id), Bear(id), Pig(id)
    {
        std::cout << __func__ << std::endl;
    }
    // ...
};

int main() {

    ManBearPig mbp(10);

    Unit &u = mbp;

    size_t id = u.id();

    std::cout << id << std::endl;
    return (0);
}