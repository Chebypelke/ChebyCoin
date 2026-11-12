#pragma once

#include "Tabs/CalculatorTab/CalculatorTab.hpp"
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Tabs.H>

namespace ChebyHash::GuiApp
{
    class MainWindow : public Fl_Double_Window 
    {
    public:
        Fl_Tabs* tabs;
        Tabs::CalculatorTab* calculator;

        MainWindow(int w, int h, const char* title);
    };
}
