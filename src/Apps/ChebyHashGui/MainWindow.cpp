#include "MainWindow.hpp"
#include "Tabs/CalculatorTab/CalculatorTab.hpp"
#include <ChebyHash/ChebyHash.hpp>
#include <FL/Fl_Choice.H>

ChebyHash::GuiApp::MainWindow::MainWindow(int w, int h, const char* title)
    : Fl_Double_Window(w, h, title)
{
    tabs = new Fl_Tabs(10, 10, 780, 580);

    calculator = new GuiApp::Tabs::CalculatorTab(10, 35, 780, 580);

    this->end();
}

