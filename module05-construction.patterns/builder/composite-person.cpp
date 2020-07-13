#include <iostream>
#include "PersonBuilder.h"
#include "PersonJobBuilder.h"
#include "PersonAddressBuilder.h"
#include "Person.h"

int main() {
    Person p = Person::create()
            .lives().at("123 London Road")
            .with_postcode("SW1 1GB")
            .in("London")
            .works().at("PragmaSoft")
            .as_a("Consultant")
            .earning(10e6);
    std::cout << p << std::endl ;
    return 0;
}
