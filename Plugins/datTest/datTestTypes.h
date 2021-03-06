#ifndef TESTTYPES
#define TESTTYPES 1
#include "../../Main/Entity.h"

//Just two basic derived types to serve testing purposes
class Flower : public Entity
{
public:
    using Entity::Entity;
    void update(unsigned int resolution) override {if (resolution) {}} //Required, but not in use

    //The following three things are for const testing
    void otherThingy();
    int thingy = 0;
    int thingy2 = 10;
};

class Dog : public Entity
{
public:
    using Entity::Entity;
    void update(unsigned int resolution) override {if (resolution) {}} //Required, but not in use
    void bark() const;
};

#endif
