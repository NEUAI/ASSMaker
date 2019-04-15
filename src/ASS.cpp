#include <ASS.h>

void ASS::parseFile(ifstream& file) {
    string line;
    vector<string> fields;
    vector<string> values;
    enum Section { NONE, SCRIPT_INFO, V4PLUS_STYLES, EVENTS, FONTS, GRAPHICS } section = NONE;
    while (getline(file, line)) {
        if (line.length() == 0 || line[0] == ';' || (line[0] == '!' && line[1] == ':')) {}
        else if (line[0] == '[') {
            if (line == "[Script Info]") {
                section = SCRIPT_INFO;
            }
            else if (line == "[v4+ Styles]") {
                section = V4PLUS_STYLES;
            }
            else if (line == "[Events]") {
                section = EVENTS;
            }
            else if (line == "[Fonts]") {
                section = FONTS;
            }
            else if (line == "[Graphics]") {
                section = GRAPHICS;
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
                else if (line.find("Script Updated By: ") == 0) {
                    scriptInfo.scriptUpdatedBy = line.substr(19);
                }
                else if (line.find("Update Details: ") == 0) {
                    scriptInfo.updateDetails = line.substr(16);
                }
                else if (line.find("Script Type: ") == 0) {
                    scriptInfo.scriptType = line.substr(13);
                }
                else if (line.find("Collisions: ") == 0) {
                    scriptInfo.collisions = line.substr(12);
                }
                else if (line.find("PlayResY: ") == 0) {
                    scriptInfo.playResY = stoul(line.substr(10));
                }
                else if (line.find("PlayResX: ") == 0) {
                    scriptInfo.playResX = stoul(line.substr(10));
                }
                else if (line.find("PlayDepth: ") == 0) {
                    scriptInfo.playDepth = stoul(line.substr(11));
                }
                else if (line.find("Timer: ") == 0) {
                    scriptInfo.timer = stod(line.substr(7));
                }
                else if (line.find("WrapStyle: ") == 0) {
                    scriptInfo.wrapStyle = stoul(line.substr(11));
                }
                else {
                    // error
                }
            }
            else if (section == V4PLUS_STYLES) {
                if (line.find("Format: ") == 0) {
                    splitFormat(line.substr(8), fields, ", ");
                }
                else if (line.find("Style: ") == 0) {
                    splitFormat(line.substr(7), values, ",");
                    auto style = new Style();
                    for (int i = 0; i < fields.size(); i++) {
                        if (fields[i] == "Name") {
                            style->name = values[i];
                        }
                        else if (fields[i] == "Fontname") {
                            style->fontname = values[i];
                        }
                        else if (fields[i] == "Fontsize") {
                            style->fontsize = stod(values[i]);
                        }
                        else if (fields[i] == "PrimaryColour") {
                            if (values[i][0] == '&') {
                                style->primaryColor = stoul(values[i].substr(1), nullptr, 16);
                            }
                            else {
                                style->primaryColor = stoul(values[i]);
                            }
                        }
                        else if (fields[i] == "SecondaryColour") {
                            if (values[i][0] == '&') {
                                style->secondaryColor = stoul(values[i].substr(1), nullptr, 16);
                            }
                            else {
                                style->secondaryColor = stoul(values[i]);
                            }
                        }
                        else if (fields[i] == "OutlineColor") {
                            if (values[i][0] == '&') {
                                style->outlineColor = stoul(values[i].substr(1), nullptr, 16);
                            }
                            else {
                                style->outlineColor = stoul(values[i]);
                            }
                        }
                        else if (fields[i] == "BackColour") {
                            if (values[i][0] == '&') {
                                style->backColor = stoul(values[i].substr(1), nullptr, 16);
                            }
                            else {
                                style->backColor = stoul(values[i]);
                            }
                        }
                        else if (fields[i] == "Bold") {
                            style->bold = (values[i] == "0");
                        }
                        else if (fields[i] == "Italic") {
                            style->italic = (values[i] == "0");
                        }
                        else if (fields[i] == "Underline") {
                            style->underline = (values[i] == "0");
                        }
                        else if (fields[i] == "Strikeout") {
                            style->strikeout = (values[i] == "0");
                        }
                        else if (fields[i] == "ScaleX") {
                            style->scaleX = stod(values[i]);
                        }
                        else if (fields[i] == "ScaleY") {
                            style->scaleY = stod(values[i]);
                        }
                        else if (fields[i] == "Spacing") {
                            style->spacing = stoul(values[i]);
                        }
                        else if (fields[i] == "Angle") {
                            style->angle = stod(values[i]);
                        }
                        else if (fields[i] == "BorderStyle") {
                            style->borderStyle = stoul(values[i]);
                        }
                        else if (fields[i] == "Outline") {
                            style->outline = stoul(values[i]);
                        }
                        else if (fields[i] == "Shadow") {
                            style->shadow = stoul(values[i]);
                        }
                        else if (fields[i] == "Alignment") {
                            style->alignment = stoul(values[i]);
                        }
                        else if (fields[i] == "MarginL") {
                            style->marginL = stoi(values[i]);
                        }
                        else if (fields[i] == "MarginR") {
                            style->marginR = stoi(values[i]);
                        }
                        else if (fields[i] == "MarginV") {
                            style->marginV = stoi(values[i]);
                        }
                        else if (fields[i] == "Encoding") {
                            style->encoding = stoul(values[i]);
                        }
                        else {
                            // error
                        }
                    }
                    v4PlusStyles[style->name] = style;
                    values.clear();
                }
                else {
                    // error
                }
            }
            else if (section == EVENTS) {
                if (line.find("Format: ") == 0) {
                    fields.clear();
                    splitFormat(line.substr(8), fields, ", ");
                }
                else if (line.find("Dialogue: ") == 0) {
                    splitFormat(line.substr(10), values, ",");
                    auto dialogue = new Dialogue();
                    for (int i = 0; i < fields.size(); i++) {
                        if (fields[i] == "Layer") {
                            dialogue->layer = stoul(values[i]);
                        }
                        else if (fields[i] == "Start") {
                            size_t tag1 = values[i].find(':');
                            size_t tag2 = values[i].substr(tag1 + 1).find(':') + tag1 + 1;
                            size_t tag3 = values[i].find('.');
                            dialogue->start[0] = stoul(values[i].substr(0, tag1));
                            dialogue->start[1] = stoul(values[i].substr(tag1 + 1, tag2));
                            dialogue->start[2] = stoul(values[i].substr(tag2 + 1, tag3));
                            dialogue->start[3] = stoul(values[i].substr(tag3 + 1));
                        }
                        else if (fields[i] == "End") {
                            size_t tag1 = values[i].find(':');
                            size_t tag2 = values[i].substr(tag1 + 1).find(':') + tag1 + 1;
                            size_t tag3 = values[i].find('.');
                            dialogue->end[0] = stoul(values[i].substr(0, tag1));
                            dialogue->end[1] = stoul(values[i].substr(tag1 + 1, tag2));
                            dialogue->end[2] = stoul(values[i].substr(tag2 + 1, tag3));
                            dialogue->end[3] = stoul(values[i].substr(tag3 + 1));
                        }
                        else if (fields[i] == "Style") {
                            dialogue->style = v4PlusStyles[values[i]];
                        }
                        else if (fields[i] == "Name") {
                            dialogue->name = values[i];
                        }
                        else if (fields[i] == "MarginL") {
                            dialogue->marginL = stoi(values[i]);
                        }
                        else if (fields[i] == "MarginR") {
                            dialogue->marginR = stoi(values[i]);
                        }
                        else if (fields[i] == "MarginV") {
                            dialogue->marginV = stoi(values[i]);
                        }
                        else if (fields[i] == "Effect") {
                            if (values[i].length() == 0) {
                                dialogue->effect = nullptr;
                            }
                            else {
                                // @todo
                            }
                        }
                        else if (fields[i] == "Text") {
                            dialogue->text = values[i];
                        }
                        else {
                            // error
                        }
                    }
                    events.push_back(dialogue);
                    values.clear();
                }
                else if (line.find("Comment: ") == 0) {
                    splitFormat(line.substr(9), values, ",");
                    // @todo
                    values.clear();
                }
                else if (line.find("Picture: ") == 0) {
                    splitFormat(line.substr(9), values, ",");
                    // @todo
                    values.clear();
                }
                else if (line.find("Sound: ") == 0) {
                    splitFormat(line.substr(7), values, ",");
                    // @todo
                    values.clear();
                }
                else if (line.find("Movie: ") == 0) {
                    splitFormat(line.substr(7), values, ",");
                    // @todo
                    values.clear();
                }
                else if (line.find("Command: ") == 0) {
                    splitFormat(line.substr(9), values, ",");
                    // @todo
                    values.clear();
                }
                else {
                    // error
                }
            }
        }
    }
}

void ASS::dumpFile(ofstream & file) {
    file << "[Script Info]" << endl;
    file << "; This is an ASS script made by ASSMaker." << endl;
    file << "Title: " << scriptInfo.title << endl;
    file << "Original Script: " << scriptInfo.originalScript << endl;
    if (scriptInfo.originalTranslation.length() != 0) {
        file << "Original Translation: " << scriptInfo.originalTranslation << endl;
    }
    if (scriptInfo.originalEditing.length() != 0) {
        file << "Original Editing: " << scriptInfo.originalEditing << endl;
    }
    if (scriptInfo.originalTiming.length() != 0) {
        file << "Original Timing: " << scriptInfo.originalTiming << endl;
    }
    if (scriptInfo.synchPoint.length() != 0) {
        file << "Synch Point: " << scriptInfo.synchPoint << endl;
    }
    if (scriptInfo.scriptUpdatedBy.length() != 0) {
        file << "Script Updated By: " << scriptInfo.scriptUpdatedBy << endl;
    }
    file << "Update Details: " << scriptInfo.updateDetails << endl;
    file << "Script Tyle: " << scriptInfo.scriptType << endl;
    file << "Collisions: " << scriptInfo.collisions << endl;
    file << "PlayResY: " << scriptInfo.playResY << endl;
    file << "PlayResX: " << scriptInfo.playResX << endl;
    file << "PlayDepth: " << scriptInfo.playDepth << endl;
    file << "Timer: " << fixed << setprecision(4) << scriptInfo.timer << endl;
    file << "WrapStyle: " << scriptInfo.wrapStyle << endl;
    file << endl;
    file << "[v4+ Styles]" << endl;
    file << "Format: Name, Fontname, Fontsize, PrimaryColour, SecondaryColour, OutlineColor, BackColour, Bold, Italic, Underline, StrikeOut, ScaleX, ScaleY, Spacing, Angle, BorderStyle, Outline, Shadow, Alignment, MarginL, MarginR, MarginV, Encoding" << endl;
    for (auto& style : v4PlusStyles) {
        file << *style.second << endl;
    }
    file << endl;
    file << "[Events]" << endl;
    file << "Format: Layer, Start, End, Style, Name, MarginL, MarginR, MarginV, Effect, Text" << endl;
    for (auto& event : events) {
        file << *event << endl;
    }
}

void ASS::splitFormat(const string & s, vector<string> & v, const string & c) {
    string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while (string::npos != pos2) {
        v.push_back(s.substr(pos1, pos2 - pos1));
        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if (pos1 != s.length()) {
        v.push_back(s.substr(pos1));
    }
}

ASS::ASS() {
    modified = false;
}

ASS::ASS(const string & path) {
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
        delete style.second;
    }
}

void ASS::save() {
    saveAs(path);
}

void ASS::saveAs(const string & path) {
    ofstream file(path);
    if (file && file.is_open()) {
        dumpFile(file);
        file.close();
    }
}
