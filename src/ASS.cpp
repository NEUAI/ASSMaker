#include <ASS.h>

void ASS::parseFile(ifstream& file) {
	string line;
	enum Section { NONE, SCRIPT_INFO, V4PLUS_STYLES, EVENTS, FONTS, GRAPHICS } section = NONE;
	while (getline(file, line)) {
		if (line.length() == 0 || line[0] == ';' || (line[0] == '!' && line[1] == ':')) {}
		else if (line[0] == '[') {
			if (line == "[Script Info]") {
				section = SCRIPT_INFO;
			}
			else if (line == "[v4+ Styles]") {
				section == V4PLUS_STYLES;
			}
			else if (line == "[Events]") {
				section == EVENTS;
			}
			else if (line == "[Fonts]") {
				section == FONTS;
			}
			else if (line == "[Graphics]") {
				section == GRAPHICS;
			}
			else {
				// error
			}
		}
		else {
			if (section == SCRIPT_INFO) {
				if (line.find("Title: ") == 0) {
					scriptInfo.title = line.substr(7);
				}
				else if (line.find("Original Script: ") == 0) {
					scriptInfo.originalScript = line.substr(17);
				}
				else if (line.find("Original Translation: ") == 0) {
					scriptInfo.originalTranslation = line.substr(22);
				}
				else if (line.find("Original Editing: ") == 0) {
					scriptInfo.originalEditing = line.substr(18);
				}
				else if (line.find("Original Timing: ") == 0) {
					scriptInfo.originalTiming = line.substr(17);
				}
				else if (line.find("Synch Point: ") == 0) {
					scriptInfo.synchPoint = line.substr(13);
				}
				// @todo
			}
		}
	}
}

ASS::ASS() {
    modified = false;
}

ASS::ASS(const string &path) {
    this->path = path;
    modified = false;
	ifstream file(path);
	if (file && file.is_open()) {
		parseFile(file);
		file.close();
	}
}

ASS::~ASS() {
	for each (auto graphic in graphics) {
		delete graphic;
	}
	for each (auto font in fonts) {
		delete font;
	}
	for each (auto event in events) {
		delete event->effect;
		delete event;
	}
	for each (auto style in v4PlusStyles) {
		delete style;
	}
}
