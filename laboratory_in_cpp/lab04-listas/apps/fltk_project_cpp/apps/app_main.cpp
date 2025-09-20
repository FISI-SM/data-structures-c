#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include "gui_music.hpp"

struct AppState {
    Node* head{nullptr};
    Node* current{nullptr};
    Fl_Box* label{nullptr};
};

static void refresh_label(AppState* st) {
    if (st->current) 
        st->label->copy_label(st->current->song.c_str());
    else 
        st->label->copy_label("No songs");
    Fl::redraw();
}

static void on_left(Fl_Widget*, void* data) {
    auto* st = static_cast<AppState*>(data);
    Node* prev = find_prev(st->head, st->current);
    if (prev) st->current = prev;
    refresh_label(st);
}

static void on_right(Fl_Widget*, void* data) {
    auto* st = static_cast<AppState*>(data);
    if (st->current && st->current->next) 
        st->current = st->current->next;
    refresh_label(st);
}

int main(int argc, char** argv) {
    // Lista simple en C++
    Node* head = nullptr;
    append(head, "Song 1 - Yesterday");
    append(head, "Song 2 - Imagine");
    append(head, "Song 3 - Let it Be");
    append(head, "Song 4 - Hey Jude");

    AppState st;
    st.head = head;
    st.current = head;

    // Ventana
    Fl_Window* win = new Fl_Window(520, 220, "Music Browser (FLTK, C++)");
    // Label centrado
    Fl_Box* label = new Fl_Box(20, 40, 480, 40, "");
    label->labelfont(FL_HELVETICA_BOLD);
    label->labelsize(20);
    label->align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE);
    st.label = label;
    refresh_label(&st);

    // Botones
    Fl_Button* left = new Fl_Button(80, 140, 120, 40, "Left");
    left->callback(on_left, &st);

    Fl_Button* right = new Fl_Button(320, 140, 120, 40, "Right");
    right->callback(on_right, &st);

    win->end();
    win->show(argc, argv);

    int rc = Fl::run();

    clear_list(st.head);
    return rc;
}
