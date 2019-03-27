#include <ASS.h>

ASS::ASS() {
    modified = false;
}

ASS::ASS(const string &path) {
    this->path = path;
    modified = false;
}

ASS::~ASS() {

}

void ASS::open(const string &path) {
    if (this->path == path) {
        break;
    } else if (modified) {
        // save current file
    }
}