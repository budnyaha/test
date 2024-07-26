#include <iostream>
#include "sortwindow.h"
#include "grup.h"

SortWindow::SortWindow()
:  m_VBox_Top(Gtk::Orientation::VERTICAL, 0),
   m_VBox2(Gtk::Orientation::VERTICAL, 20),
   m_HBox_DropDown(Gtk::Orientation::HORIZONTAL, 10),
   m_HBox_New(Gtk::Orientation::HORIZONTAL, 10),
   m_HBox_Preview(Gtk::Orientation::HORIZONTAL, 10),

   m_Button_New("New"),
   m_Button_Save("Save")
{
   start_dialog();
   set_title("Test Window");
   set_default_size(750, 800);
   set_resizable(false);


   set_child(m_VBox_Top);
   m_VBox_Top.append(m_VBox2);
   m_VBox2.set_expand(true);
   m_VBox2.set_margin(10);
   m_VBox2.append(m_HBox_DropDown);
   m_HBox_DropDown.set_expand(false);

   auto string_list = Gtk::StringList::create({});
   m_DropDown_Sort.set_model(string_list);

    string_list->append("Distance");
    string_list->append("Name");
    string_list->append("Time of creation");
    string_list->append("Type");

   m_HBox_DropDown.append(*Gtk::make_managed<Gtk::Label>("Select sort type:", 0));
   m_HBox_DropDown.append(m_DropDown_Sort);
   m_DropDown_Sort.property_selected().signal_changed().connect(
     sigc::mem_fun(*this, &SortWindow::on_dropdown_sort));
   m_DropDown_Sort.set_selected(0); // Top
   m_DropDown_Sort.set_expand(false);

   m_VBox2.append(m_HBox_New);
   m_HBox_New.set_expand(false);
   m_HBox_New.set_margin(10);

   m_Entry_Name.set_max_length(20);
   m_Entry_Name.set_text("Name");
   m_Entry_Name.select_region(0, m_Entry_Name.get_text_length());
   m_Entry_Name.set_expand(false);
   m_HBox_New.append(m_Entry_Name);

   m_Entry_X.set_max_length(20);
   m_Entry_X.set_text("X coordinate");
   m_Entry_X.select_region(0, m_Entry_X.get_text_length());
   m_Entry_X.set_expand(false);
   m_HBox_New.append(m_Entry_X);


   m_Entry_Y.set_max_length(20);
   m_Entry_Y.set_text("Y coordinate");
   m_Entry_Y.select_region(0, m_Entry_Y.get_text_length());
   m_Entry_Y.set_expand(false);
   m_HBox_New.append(m_Entry_Y);


   m_Entry_Type.set_max_length(20);
   m_Entry_Type.set_text("Type");
   m_Entry_Type.select_region(0, m_Entry_Type.get_text_length());
   m_Entry_Type.set_expand(false);
   m_HBox_New.append(m_Entry_Type);


   m_HBox_New.append(m_Button_New);
   set_default_widget(m_Button_New);
   m_Button_New.signal_clicked().connect(sigc::mem_fun(*this,
     &SortWindow::on_button_new));
   m_Button_New.set_margin(10);

   m_ScrolledWindow.set_child(m_TextView_Preview);

   m_ScrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
   m_ScrolledWindow.set_expand();

   m_VBox2.append(m_ScrolledWindow);

   m_VBox_Top.append(m_Button_Save);
   set_default_widget(m_Button_Save);
   m_Button_Save.signal_clicked().connect(sigc::mem_fun(*this,
       &SortWindow::on_button_sawe));
   m_Button_Save.set_margin(10);

}

SortWindow::~SortWindow()
{
}

void SortWindow::start_dialog()
{
	auto dialog = Gtk::FileDialog::create();

	  auto filters = Gio::ListStore<Gtk::FileFilter>::create();

	  auto filter_text = Gtk::FileFilter::create();
	  filter_text->set_name("Text files");
	  filter_text->add_mime_type("text/plain");
	  filters->append(filter_text);

	  auto filter_cpp = Gtk::FileFilter::create();
	  filter_cpp->set_name("C/C++ files");
	  filter_cpp->add_mime_type("text/x-c");
	  filter_cpp->add_mime_type("text/x-c++");
	  filter_cpp->add_mime_type("text/x-c-header");
	  filters->append(filter_cpp);

	  auto filter_any = Gtk::FileFilter::create();
	  filter_any->set_name("Any files");
	  filter_any->add_pattern("*");
	  filters->append(filter_any);

	  dialog->set_filters(filters);

	  dialog->open(sigc::bind(sigc::mem_fun(
	    *this, &SortWindow::on_file_dialog_finish), dialog));
}

void SortWindow::on_file_dialog_finish(const Glib::RefPtr<Gio::AsyncResult>& result,
  const Glib::RefPtr<Gtk::FileDialog>& dialog)
{
  try
  {
    auto doc = dialog->open_finish(result);

    path = doc->get_path().c_str();
    file = parsFile(path);
    text_File = grup(file, selected);
    fill_buffers();
    m_TextView_Preview.set_buffer(m_refTextBuffer1);
  }
  catch (const Gtk::DialogError& err)
  {
    std::cout << "No file selected. " << err.what() << std::endl;
  }
  catch (const Glib::Error& err)
  {
    std::cout << "Unexpected exception. " << err.what() << std::endl;
  }
}

void SortWindow::fill_buffers()
{
  m_refTextBuffer1 = Gtk::TextBuffer::create();
  m_refTextBuffer1->set_text(text_File);

}

void SortWindow::on_dropdown_sort()
{
	selected = m_DropDown_Sort.get_selected();
	text_File = grup(file, selected);
	fill_buffers();
	m_TextView_Preview.set_buffer(m_refTextBuffer1);
}

void SortWindow::on_button_new()
{
	object line;
	line.name = m_Entry_Name.get_buffer()->get_text();
	line.coord_x = std::stod(m_Entry_X.get_buffer()->get_text());
	line.coord_y = std::stod(m_Entry_Y.get_buffer()->get_text());
	line.data = time(NULL);
	line.type = m_Entry_Type.get_buffer()->get_text();
	file.push_back(line);
	text_File = grup(file, selected);
	fill_buffers();
	m_TextView_Preview.set_buffer(m_refTextBuffer1);
}

void SortWindow::on_button_sawe()
{
	save_file(text_File);
	set_visible(false);
}
