#include <gtk/gtk.h>
#include <stdlib.h>
#include "gui_music.h"

// Lista global simple
static Node *head = NULL;
static Node *current = NULL;

// Widgets globales
static GtkWidget *label_song = NULL;

// Callbacks
static void on_left_clicked(GtkButton *button, gpointer user_data) {
    (void)button; (void)user_data;
    Node *prev = find_prev(head, current);
    if (prev) {
        current = prev;
        gtk_label_set_text(GTK_LABEL(label_song), current->song);
    }
}

static void on_right_clicked(GtkButton *button, gpointer user_data) {
    (void)button; (void)user_data;
    if (current && current->next) {
        current = current->next;
        gtk_label_set_text(GTK_LABEL(label_song), current->song);
    }
}

static void activate(GtkApplication *app, gpointer user_data) {
    (void)user_data;

    // Ventana
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Music Browser (GTK)");
    gtk_window_set_default_size(GTK_WINDOW(window), 420, 160);
    gtk_container_set_border_width(GTK_CONTAINER(window), 8);

    // Caja vertical
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Label de la canción actual
    label_song = gtk_label_new(current ? current->song : "No songs");
    gtk_box_pack_start(GTK_BOX(vbox), label_song, TRUE, TRUE, 4);

    // Caja horizontal para botones
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);
    gtk_box_pack_end(GTK_BOX(vbox), hbox, TRUE, TRUE, 4);

    GtkWidget *btn_left = gtk_button_new_with_label("Left");
    GtkWidget *btn_right = gtk_button_new_with_label("Right");

    g_signal_connect(btn_left,  "clicked", G_CALLBACK(on_left_clicked), NULL);
    g_signal_connect(btn_right, "clicked", G_CALLBACK(on_right_clicked), NULL);

    gtk_box_pack_start(GTK_BOX(hbox), btn_left, TRUE, TRUE, 4);
    gtk_box_pack_start(GTK_BOX(hbox), btn_right, TRUE, TRUE, 4);

    gtk_widget_show_all(window);
}

int main(int argc, char *argv[]) {
    // Construcción de la lista simple
    append(&head, "Song 1 - Yesterday");
    append(&head, "Song 2 - Imagine");
    append(&head, "Song 3 - Let it Be");
    append(&head, "Song 4 - Hey Jude");
    current = head;

    GtkApplication *app = gtk_application_new("org.example.musicgtk", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    // Liberar lista
    Node *t = head;
    while (t) {
        Node *nx = t->next;
        free(t->song);
        free(t);
        t = nx;
    }
    return status;
}
