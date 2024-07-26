#include <gtkmm/application.h>
#include "sortwindow.h"

int main(int argc, char *argv[])
{
  auto app = Gtk::Application::create("window");

  //Shows the window and returns when it is closed.
  return app->make_window_and_run<SortWindow>(argc, argv);
}
