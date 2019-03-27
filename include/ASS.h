#ifndef __ASS_H__
#define __ASS_H__

#include <string>

using namespace std;

class ASS {
    string path;
    bool modified;
    
public:
    ASS();
    explicit ASS(const string &path);
    virtual ~ASS();
    virtual void open(const string &path);
    virtual void save();
    virtual void saveAs(const string &path);
};

#endif // __ASS_H__
