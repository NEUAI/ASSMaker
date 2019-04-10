#ifndef __ASS_H__
#define __ASS_H__

#include <fstream>
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
		unsigned int playResY;
		unsigned int playResX;
		unsigned int playDepth;
		double timer;
		unsigned int wrapStyle; // 0-3
		ScriptInfo() {
			title = "<untitle>";
			originalScript = "<unknown>";
			scriptType = "V4.00+";
			collisions = "Normal";
			playResY = 1080;
			playResX = 1920;
			playDepth = 0;
			timer = 100.0;
			wrapStyle = 0;
		}
	} scriptInfo;
	struct Style {
		string name;
		string fontname;
		unsigned int primaryColor[4];
		unsigned int secondaryColor[4];
		unsigned int outlineColor[4];
		unsigned int backColor[4];
		bool bold;
		bool italic;
		bool underline;
		bool strikeout;
		double scaleX;
		double scaleY;
		unsigned int spacing;
		double angle;
		unsigned int borderStyle; // 1, 3
		unsigned int outline; // 0-4
		unsigned int shadow; // 0-4
		unsigned int alignment; // 1-9
		int marginL;
		int marginR;
		int marginV;
		unsigned int encoding; // 0: English (Western, ANSI), 1: Default, 128: Janpanese, 134: Chinese (Simplified), 136: Chinese (Traditional)
		Style() {
			memset(&primaryColor, 0, sizeof(unsigned int) * 4);
			memset(&secondaryColor, 0, sizeof(unsigned int) * 4);
			memset(&outlineColor, 0, sizeof(unsigned int) * 4);
			memset(&backColor, 0, sizeof(unsigned int) * 4);
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
			marginL = 8;
			marginR = 8;
			marginV = 8;
			encoding = 1;
		}
	};
	vector<Style*> v4PlusStyles;
	struct Effect {
		string type;
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
	};
	struct Event {
		string type;
		unsigned int layer;
		unsigned int start[4];
		unsigned int end[4];
		Style* style;
		string name;
		int marginL;
		int marginR;
		int marginV;
		Effect* effect;
		string text;
		Event() {
			layer = 0;
			memset(&start, 0, sizeof(unsigned int) * 4);
			memset(&end, 0, sizeof(unsigned int) * 4);
			style = nullptr;
			marginL = 8;
			marginR = 8;
			marginV = 8;
			effect = nullptr;
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
	virtual void parseFile(ifstream& file);
    
public:
    ASS();
    explicit ASS(const string &path);
    virtual ~ASS();
    // virtual void save();
    // virtual void saveAs(const string &path);
};

#endif // __ASS_H__
