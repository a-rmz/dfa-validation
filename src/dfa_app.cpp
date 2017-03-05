
#include "define_window.h"
#include <gtkmm/application.h>

/**
  * Entry point for the app
  */
int main (int argc, char *argv[]) {
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

  DefineWindow define_window;

  //Shows the window and returns when it is closed.
  return app->run(define_window);
}