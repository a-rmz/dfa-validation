
#include "dfa_app.h"
#include <gtkmm/application.h>

int main (int argc, char *argv[]) {
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

  DFA_app dfa_app;

  //Shows the window and returns when it is closed.
  return app->run(dfa_app);
}