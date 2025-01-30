#ifndef JSON_H
#define JSON_H

#include <WString.h>
#include <vector>
#include <map>
#include <utility> // for std::pair
#include <initializer_list>

struct Json {
    enum struct Type {
        null,
        boolean,
        number,
        string,
        array,
        object
    };

    Type type;
    union {
        bool boolean;
        double number;
        String *string;
        std::vector<Json> *array;
        std::map<String, Json> *object;
    } value;

    static Json null;

    // Constructors
    Json(); // Default constructor
    Json(bool b); // Boolean constructor
    Json(double d); // Number constructor
    Json(const String &s); // String constructor
    Json(std::initializer_list<Json> list); // Array constructor
    Json(std::initializer_list<std::pair<const String, Json>> list); // Object constructor
    Json(const Json &other); // Copy constructor
    Json &operator=(const Json &other); // Assignment operator
    ~Json(); // Destructor

    // Type conversion operators
    explicit operator bool() const;
    explicit operator double() const;
    explicit operator String() const;

    // Array access
    Json &operator[](int index);
    std::size_t length() const;
    void push(const Json &item);

    // Object access
    Json &operator[](const String &key);
};

#endif // JSON_H