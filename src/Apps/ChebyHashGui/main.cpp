#include "MainWindow.hpp"

int main(int argc, char **argv)
{
    ChebyHash::GuiApp::MainWindow* win = new ChebyHash::GuiApp::MainWindow(400, 300, "ChebyHash - GUI App");
    win->show();
    return Fl::run();
}