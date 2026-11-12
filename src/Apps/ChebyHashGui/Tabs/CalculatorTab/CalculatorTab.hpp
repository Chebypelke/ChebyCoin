#pragma once 

#include <FL/Fl_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>

namespace ChebyHash::GuiApp::Tabs
{
    class CalculatorTab : public Fl_Group
    {
        public:
            CalculatorTab(int x, int y, int w, int h);
        private: 
            Fl_Input* inputField;
            Fl_Output* outputField;
            Fl_Choice* hashChoice;

            static void onInputChanged(Fl_Widget* widget, void* data);
            void handleHash();
    };
}