#include "CalculatorTab.hpp"
#include <ChebyHash/ChebyHash.hpp>
#include <FL/Enumerations.H>
#include <string>
#include <sstream>
#include <iomanip>

ChebyHash::GuiApp::Tabs::CalculatorTab::CalculatorTab(int x, int y, int w, int h)
    : Fl_Group(x, y, w, h, "Calculator")
{
    inputField = new Fl_Input(80, 40, 280, 30, "Text:");

    hashChoice = new Fl_Choice(80, 80, 130, 30, "Hashes:");
    hashChoice->add("ChebyHash32");
    hashChoice->add("ChebyHash64");
    hashChoice->add("ChebyHash128");
    hashChoice->value(0);

    outputField = new Fl_Output(80, 120, 280, 30, "Hash:");

    inputField->textfont(FL_SCREEN);
    outputField->textfont(FL_SCREEN);
    
    inputField->when(FL_WHEN_CHANGED);
    inputField->callback(onInputChanged, this);
    hashChoice->when(FL_WHEN_CHANGED);
    hashChoice->callback(onInputChanged, this);
}



void ChebyHash::GuiApp::Tabs::CalculatorTab::onInputChanged(Fl_Widget* widget, void* data) {
    auto* app = static_cast<CalculatorTab*>(data);
    app->handleHash();
}

void ChebyHash::GuiApp::Tabs::CalculatorTab::handleHash() {
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
            ss << std::hex << std::setfill('0')
                           << std::setw(16) << hash.high 
                           << std::setw(16) << hash.low;
            hashResult = ss.str();
            break;
        }
        default:
            hashResult = "Unknown hash";
            break;
    }

    outputField->value(hashResult.c_str());
}