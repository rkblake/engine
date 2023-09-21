#pragma once

#include <string>

class Resource {
public:
    Resource() {}
    ~Resource() {}

    bool operator==(Resource &other) { return uid == other.uid; }

private:
    unsigned int uid;
    static unsigned int counter;
    std::string path;
    // void *data;
};
