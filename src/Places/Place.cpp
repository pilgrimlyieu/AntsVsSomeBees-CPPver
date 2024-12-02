#include "Place.h"
#include "Insect.h"

/**
 * @brief Selects a random Bee from the list of bees in the Place.
 *
 * This function returns a pointer to a randomly selected Bee from the
 * bees vector. If the bees vector is empty, it returns nullptr.
 *
 * @return Bee* Pointer to a randomly selected Bee, or nullptr if the
 * bees vector is empty.
 */
Bee *Place::randomBee() {
    if (bees.size() == 0) {
        return nullptr;
    }
    return get(bees, rand() % bees.size());
}

/**
 * @brief Constructs a new Place object with a given name and exit.
 *
 * @param name The name of the place.
 * @param exit A pointer to the exit Place object. If not null, sets this place as the entrance of
 * the exit place.
 */
Place::Place(string name, Place *exit) {
    this->name = name;
    this->exit = exit;
    if (this->exit != nullptr) {
        this->exit->entrance = this;
    }
}

/**
 * @brief Adds an insect to the place.
 *
 * This function adds the given insect to the current place by calling the
 * insect's addTo method and passing the current place as an argument.
 *
 * @param insect A pointer to the Insect object to be added to the place.
 */
void Place::addInsect(Insect *insect) {
    insect->addTo(this);
}

/**
 * @brief Removes an insect from the current place.
 *
 * This function calls the removeFrom method on the given insect,
 * passing the current place as the parameter, effectively removing
 * the insect from this place.
 *
 * @param insect A pointer to the insect to be removed.
 */
void Place::removeInsect(Insect *insect) {
    insect->removeFrom(this);
}

/**
 * @brief Overloaded << operator to add an insect to the place.
 *
 * This operator allows adding an insect to the place using the << operator.
 *
 * @param insect Pointer to the insect to be added.
 *
 * @example
 * @code
 * Place place;
 * Insect* insect = new Insect();
 * place << insect; // Adds the insect to the place
 * @endcode
 */
void Place::operator<<(Insect *insect) {
    this->addInsect(insect);
}

/**
 * @brief Overloaded >> operator to remove an insect from the place.
 *
 * This operator allows removing an insect from the place using the >> operator.
 *
 * @param insect Pointer to the insect to be removed.
 *
 * @example
 * @code
 * Place place;
 * Insect* insect = new Insect();
 * place << insect; // Adds the insect to the place
 * place >> insect; // Removes the insect from the place
 * @endcode
 */
void Place::operator>>(Insect *insect) {
    this->removeInsect(insect);
}

/**
 * @brief Converts the Place object to a string representation.
 *
 * This operator allows a Place object to be implicitly converted to a
 * std::string, returning the name of the place.
 *
 * @return A string representation of the Place object, which is the name of the place.
 */
Place::operator string() const {
    return name;
}

/**
 * @brief Destructor for the Place class.
 *
 * This destructor is responsible for cleaning up any resources
 * that the Place object may have acquired during its lifetime.
 */
Place::~Place() {}