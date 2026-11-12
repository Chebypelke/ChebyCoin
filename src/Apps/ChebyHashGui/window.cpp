#include "window.hpp"
#include <ChebyHash/ChebyHash.hpp>
#include <FL/Fl_Choice.H>
#include <iostream>
#include <string>
#include <sstream>

ChebyHash::GuiApp::GuiApp(int w, int h, const char* title) 
    : Fl_Double_Window(w, h, title)
{
    inputField = new Fl_Input(80, 40, 280, 30, "Text:");

    hashChoice = new Fl_Choice(80, 80, 130, 30, "Hashes:");
    hashChoice->add("ChebyHash32");
    hashChoice->add("ChebyHash64");
    hashChoice->add("ChebyHash128");
    hashChoice->value(0);

    hashButton = new Fl_Button(240, 80, 120, 30, "Hash");
    outputField = new Fl_Output(80, 120, 280, 30, "Hash:");

    hashButton->callback(onButtonCB, this);

    this->end();
}

void ChebyHash::GuiApp::onButtonCB(Fl_Widget* w, void* data) {
    auto* app = static_cast<GuiApp*>(data);
    app->handleHash();
}

void ChebyHash::GuiApp::handleHash() {
    std::string text = inputField->value();
    std::stringstream ss;
    std::string hashResult;

    switch (hashChoice->value()) {
        case 0: 
            ss << std::hex << ChebyHash::ChebyHash32::hash(text);
            hashResult = ss.str();
            break;
        case 1: 
            ss << std::hex << ChebyHash::ChebyHash64::hash(text);
            hashResult = ss.str();
            break;
        case 2:
        {
            ChebyHash128::Hash128 hash = ChebyHash::ChebyHash128::hash(text);
            ss << std::hex << hash.high << hash.low;
            hashResult = ss.str();
            break;
        }
        default:
            hashResult = "Unknown hash";
            break;
    }

    outputField->value(hashResult.c_str());
}