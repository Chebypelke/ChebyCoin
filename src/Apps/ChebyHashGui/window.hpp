#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Choice.H>

namespace ChebyHash 
{
    class GuiApp : public Fl_Double_Window 
    {
    public:
        GuiApp(int w, int h, const char* title);
    private: 
        Fl_Input* inputField;
        Fl_Button* hashButton;
        Fl_Output* outputField;
        Fl_Choice* hashChoice;

        static void onButtonCB(Fl_Widget* w, void* data);
        void handleHash();
    };
}
