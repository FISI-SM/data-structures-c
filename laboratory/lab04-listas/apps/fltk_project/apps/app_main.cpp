#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <cstdio>
#include <cstdlib>   // <-- necesario para free()
#include "gui_music.h"

struct AppState {
    Node* head;
    Node* current;
    Fl_Box* label;
};

static void refresh_label(AppState* st) {
    if (st->current) st->label->copy_label(st->current->song);
    else st->label->copy_label("No songs");
    Fl::redraw();
}

static void on_left(Fl_Widget* w, void* data) {
    (void)w;
    AppState* st = (AppState*)data;
    Node* prev = find_prev(st->head, st->current);
    if (prev) st->current = prev;
    refresh_label(st);
}

static void on_right(Fl_Widget* w, void* data) {
    (void)w;
    AppState* st = (AppState*)data;
    if (st->current && st->current->next) {
        st->current = st->current->next;
    }
    refresh_label(st);
}

int main(int argc, char** argv) {
    // Construir lista simple
    Node* head = NULL;
    append(&head, "Song 1 - Yesterday");
    append(&head, "Song 2 - Imagine");
    append(&head, "Song 3 - Let it Be");
    append(&head, "Song 4 - Hey Jude");

    AppState st;
    st.head = head;
    st.current = head;

    // Ventana
    Fl_Window* win = new Fl_Window(520, 220, "Music Browser (FLTK)");
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

    // Liberar lista
    Node* t = st.head;
    while (t) {
        Node* nx = t->next;
        free(t->song);
        free(t);
        t = nx;
    }

    return rc;
}
