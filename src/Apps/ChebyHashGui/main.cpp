#include "window.hpp"

int main(int argc, char **argv)
{
    ChebyHash::GuiApp* win = new ChebyHash::GuiApp(400, 300, "ChebyHash - GUI App");
    win->show();
    return Fl::run();
}