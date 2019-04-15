#ifndef __ASS_H__
#define __ASS_H__

#include <fstream>
#include <iomanip>
#include <map>
#include <string>
#include <vector>

using namespace std;

class ASS {
    string path;
    bool modified;
    struct ScriptInfo {
        string title; // <untitle>
        string originalScript; // <unknown>
        string originalTranslation;
        string originalEditing;
        string originalTiming;
        string synchPoint;
        string scriptUpdatedBy;
        string updateDetails;
        string scriptType; // V4.00+
        string collisions; // Normal, Reverse
        unsigned long playResY;
        unsigned long playResX;
        unsigned long playDepth;
        double timer;
        unsigned long wrapStyle; // 0-3
        ScriptInfo() {
            title = "<untitle>";
            originalScript = "<unknown>";
            scriptType = "V4.00+";
            collisions = "Normal";
            playResY = 0;
            playResX = 0;
            playDepth = 0;
            timer = 100.0;
            wrapStyle = 0;
        }
    } scriptInfo;
    struct Style {
        string name;
        string fontname;
        double fontsize;
        unsigned long primaryColor;
        unsigned long secondaryColor;
        unsigned long outlineColor;
        unsigned long backColor;
        bool bold;
        bool italic;
        bool underline;
        bool strikeout;
        double scaleX;
        double scaleY;
        unsigned long spacing;
        double angle;
        unsigned long borderStyle; // 1, 3
        unsigned long outline; // 0-4
        unsigned long shadow; // 0-4
        unsigned long alignment; // 1-9
        int marginL;
        int marginR;
        int marginV;
        unsigned long encoding; // 0: English (Western, ANSI), 1: Default, 128: Janpanese, 134: Chinese (Simplified), 136: Chinese (Traditional)
        Style() {
            fontsize = 12;
            primaryColor = 0;
            secondaryColor = 0;
            outlineColor = 0;
            backColor = 0;
            bold = false;
            italic = false;
            underline = false;
            strikeout = false;
            scaleX = 0.0;
            scaleY = 0.0;
            spacing = 0;
            angle = 0.0;
            borderStyle = 1;
            outline = 1;
            shadow = 1;
            alignment = 2;
            marginL = 0;
            marginR = 0;
            marginV = 0;
            encoding = 1;
        }
        friend ostream& operator<<(ostream& os, const Style& style) {
            os << "Style: " << style.name << "," << style.fontname << "," << style.fontsize << ",";
            os << "&" << setw(8) << setfill('0') << setiosflags(ios::uppercase) << hex << style.primaryColor << ",";
            os << "&" << setw(8) << setfill('0') << setiosflags(ios::uppercase) << hex << style.secondaryColor << ",";
            os << "&" << setw(8) << setfill('0') << setiosflags(ios::uppercase) << hex << style.outlineColor << ",";
            os << "&" << setw(8) << setfill('0') << setiosflags(ios::uppercase) << hex << style.backColor << ",";
            os << dec;
            os << (style.bold ? "-1" : "0") << ",";
            os << (style.italic ? "-1" : "0") << ",";
            os << (style.underline ? "-1" : "0") << ",";
            os << (style.strikeout ? "-1" : "0") << ",";
            os << style.scaleX << "," << style.scaleY << "," << style.spacing << "," << style.angle << ",";
            os << style.borderStyle << "," << style.outline << "," << style.shadow << "," << style.alignment << ",";
            os << style.marginL << "," << style.marginR << "," << style.marginV << "," << style.encoding;
            return os;
        }
    };
    map<string, Style*> v4PlusStyles;
    struct Effect {
        string type;
        friend ostream& operator<<(ostream& os, const Effect& effect) {
            return os;
        }
    };
    struct ScrollUp : public Effect {
        int y1;
        int y2;
        int delay;
        int fadeAwayHeight;
        ScrollUp() {
            type = "Scroll up";
            y1 = 0;
            y2 = 0;
            delay = 0;
            fadeAwayHeight = 0;
        }
        friend ostream& operator<<(ostream& os, const ScrollUp& scrollUp) {
            os << scrollUp.type << ";" << scrollUp.y1 << ";" << scrollUp.y2 << ";" << scrollUp.delay;
            if (scrollUp.fadeAwayHeight != 0) {
                os << ";" << scrollUp.fadeAwayHeight;
            }
            return os;
        }
    };
    struct Banner : public Effect {
        int delay;
        bool leftToRight;
        int fadeAwayWidth;
        Banner() {
            type = "Banner";
            delay = 0;
            leftToRight = false;
            fadeAwayWidth = 0;
        }
        friend ostream& operator<<(ostream& os, const Banner& banner) {
            os << banner.type << ";" << banner.delay;
            if (banner.leftToRight || banner.fadeAwayWidth != 0) {
                os << ";" << (banner.leftToRight? "1" : "0");
            }
            if (banner.fadeAwayWidth != 0) {
                os << ";" << banner.fadeAwayWidth;
            }
            return os;
        }
    };
    struct ScrollDown : public Effect {
        int y1;
        int y2;
        int delay;
        int fadeAwayHeight;
        ScrollDown() {
            type = "Scroll down";
            y1 = 0;
            y2 = 0;
            delay = 0;
            fadeAwayHeight = 0;
        }
        friend ostream& operator<<(ostream& os, const ScrollDown& scrollDown) {
            os << scrollDown.type << ";" << scrollDown.y1 << ";" << scrollDown.y2 << ";" << scrollDown.delay;
            if (scrollDown.fadeAwayHeight != 0) {
                os << ";" << scrollDown.fadeAwayHeight;
            }
            return os;
        }
    };
    struct Event {
        string type;
        unsigned long layer;
        unsigned long start[4];
        unsigned long end[4];
        Style* style;
        string name;
        int marginL;
        int marginR;
        int marginV;
        Effect* effect;
        string text;
        Event() {
            layer = 0;
            memset(&start, 0, sizeof(unsigned long) * 4);
            memset(&end, 0, sizeof(unsigned long) * 4);
            style = nullptr;
            marginL = 8;
            marginR = 8;
            marginV = 8;
            effect = nullptr;
        }
        friend ostream& operator<<(ostream& os, const Event& event) {
            os << event.type << ": " << event.layer << ",";
            os << setw(2) << setfill('0') << event.start[0] << ":" << setw(2) << setfill('0') << event.start[1] << ":" << setw(2) << setfill('0') << event.start[2] << "." << setw(2) << setfill('0') << event.start[3] << ",";
            os << setw(2) << setfill('0') << event.end[0] << ":" << setw(2) << setfill('0') << event.end[1] << ":" << setw(2) << setfill('0') << event.end[2] << "." << setw(2) << setfill('0') << event.end[3] << ",";
            os << event.style->name << "," << event.name << "," << event.marginL << "," << event.marginR << "," << event.marginV << "," << *event.effect << "," << event.text;
            return os;
        }
    };
    struct Dialogue : public Event {
        Dialogue() {
            type = "Dialogue";
        }
    };
    struct Comment : public Event {
        Comment() {
            type = "Comment";
        }
    };
    struct Picture : public Event {
        Picture() {
            type = "Picture";
        }
    };
    struct Sound : public Event {
        Sound() {
            type = "Sound";
        }
    };
    struct Movie : public Event {
        Movie() {
            type = "Movie";
        }
    };
    struct Command : public Event {
        Command() {
            type = "Command";
        }
    };
    vector<Event*> events;
    struct Font {
        string fontname;
    };
    vector<Font*> fonts;
    struct Graphic {
        string filename;
    };
    vector<Graphic*> graphics;
    virtual void parseFile(ifstream & file);
    virtual void dumpFile(ofstream & file);
    static void splitFormat(const string & s, vector<string> & v, const string & c);

public:
    ASS();
    explicit ASS(const string & path);
    virtual ~ASS();
    virtual void save();
    virtual void saveAs(const string & path);
};

#endif // __ASS_H__
