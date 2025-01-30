#include "json.h"
#include <utility> // for std::pair

// Static member initialization
Json Json::null = Json();

// Default constructor
Json::Json() : type(Type::null) {
    value.string = nullptr; // Initialize union to null
}

// Boolean constructor
Json::Json(bool b) : type(Type::boolean) {
    value.boolean = b;
}

// Number constructor
Json::Json(double d) : type(Type::number) {
    value.number = d;
}

// String constructor
Json::Json(const String &s) : type(Type::string) {
    value.string = new String(s); // Allocate new String
}

// Array constructor
Json::Json(std::initializer_list<Json> list) : type(Type::array) {
    value.array = new std::vector<Json>(list); // Allocate new vector
}

// Object constructor
Json::Json(std::initializer_list<std::pair<const String, Json>> list) : type(Type::object) {
    value.object = new std::map<String, Json>(list); // Allocate new map
}

// Copy constructor
Json::Json(const Json &other) : type(other.type) {
    switch (type) {
        case Type::boolean:
            value.boolean = other.value.boolean;
            break;
        case Type::number:
            value.number = other.value.number;
            break;
        case Type::string:
            value.string = new String(*other.value.string); // Deep copy String
            break;
        case Type::array:
            value.array = new std::vector<Json>(*other.value.array); // Deep copy vector
            break;
        case Type::object:
            value.object = new std::map<String, Json>(*other.value.object); // Deep copy map
            break;
        case Type::null:
        default:
            value.string = nullptr; // Initialize union to null
            break;
    }
}

// Assignment operator
Json &Json::operator=(const Json &other) {
    if (this != &other) { // Check for self-assignment
        // Clean up existing resources
        switch (type) {
            case Type::string:
                delete value.string;
                break;
            case Type::array:
                delete value.array;
                break;
            case Type::object:
                delete value.object;
                break;
            default:
                break;
        }

        // Copy data from other
        type = other.type;
        switch (type) {
            case Type::boolean:
                value.boolean = other.value.boolean;
                break;
            case Type::number:
                value.number = other.value.number;
                break;
            case Type::string:
                value.string = new String(*other.value.string); // Deep copy String
                break;
            case Type::array:
                value.array = new std::vector<Json>(*other.value.array); // Deep copy vector
                break;
            case Type::object:
                value.object = new std::map<String, Json>(*other.value.object); // Deep copy map
                break;
            case Type::null:
            default:
                value.string = nullptr; // Initialize union to null
                break;
        }
    }
    return *this;
}

// Destructor
Json::~Json() {
    switch (type) {
        case Type::string:
            delete value.string; // Free String
            break;
        case Type::array:
            delete value.array; // Free vector
            break;
        case Type::object:
            delete value.object; // Free map
            break;
        default:
            break;
    }
}

// Type conversion operators
Json::operator bool() const {
    if (type == Type::boolean) {
        return value.boolean;
    }
    return false; // Default for non-boolean types
}

Json::operator double() const {
    if (type == Type::number) {
        return value.number;
    }
    return 0.0; // Default for non-number types
}

Json::operator String() const {
    if (type == Type::string) {
        return *value.string;
    }
    return String(); // Default for non-string types
}

// Array access
Json &Json::operator[](int index) {
    if (type == Type::array && value.array != nullptr) {
        return (*value.array)[index];
    }
    return Json::null; // Return null Json for invalid access
}

std::size_t Json::length() const {
    if (type == Type::array && value.array != nullptr) {
        return value.array->size();
    }
    return 0; // Default for non-array types
}

void Json::push(const Json &item) {
    if (type == Type::array && value.array != nullptr) {
        value.array->push_back(item);
    }
}

// Object access
Json &Json::operator[](const String &key) {
    if (type == Type::object && value.object != nullptr) {
        return (*value.object)[key];
    }
    return Json::null; // Return null Json for invalid access
}