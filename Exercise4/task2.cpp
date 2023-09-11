#include <gtkmm.h>

class Window : public Gtk::Window {
public:
  Gtk::Box box;
  Gtk::Entry firstName;
  Gtk::Entry lastName;
  Gtk::Button button;
  Gtk::Label label;
  Gtk::Label firstNameLabel;
  Gtk::Label lastNameLabel;

  Window() : box(Gtk::Orientation::ORIENTATION_VERTICAL) {
    button.set_label("Combine names");
    box.pack_start(firstNameLabel);
    firstNameLabel.set_text("Enter first name");
    box.pack_start(firstName); // Add the widget firstName to box
    box.pack_start(lastNameLabel);
    lastNameLabel.set_text("Enter last name");
    box.pack_start(lastName); // Add the widget lastName to box

    box.pack_start(button); // Add the widget button to box
    button.set_sensitive(FALSE);
    box.pack_start(label); // Add the widget label to box

    add(box);   // Add vbox to window
    show_all(); // Show all widgets

    button.signal_clicked().connect([this]() {
      label.set_text(firstName.get_text() + " " + lastName.get_text());
    });

    firstName.signal_changed().connect([this]() {
      bool firstnameIsInputted = firstName.get_text_length() != 0 && firstName.get_text() != " ";
      bool lastnameIsInputted = lastName.get_text_length() && lastName.get_text() != " ";
      if (firstnameIsInputted && lastnameIsInputted) {
        button.set_sensitive(true);
      } else {
        button.set_sensitive(false);
      }
    });

    lastName.signal_changed().connect([this]() {
      bool firstnameIsInputted = firstName.get_text_length() != 0 && firstName.get_text() != " ";
      bool lastnameIsInputted = lastName.get_text_length() && lastName.get_text() != " ";
      if (firstnameIsInputted && lastnameIsInputted) {
        button.set_sensitive(true);
      } else {
        button.set_sensitive(false);
      }
    });
  }
};

int main() {
  auto app = Gtk::Application::create();
  Window window;
  window.set_title("Øving 4");
  return app->run(window);
}
