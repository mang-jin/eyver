#include <stdio.h>
#include <gtk/gtk.h>

static gboolean on_key_pressed(GtkEventController *controller, guint keyval,
                              guint keycode, GdkModifierType state, gpointer user_data)
{
        GtkApplication *app = GTK_APPLICATION(user_data);

        if ((state & GDK_CONTROL_MASK) &&
            (state & GDK_ALT_MASK) &&
            keyval == GDK_KEY_Return) {
                g_application_quit(G_APPLICATION(app));
                return TRUE;
        }

        return FALSE;
}

typedef struct {
        const char* msg;
        const char* font;
} UserData;

int sec = 0;
int min = 0;

static gboolean update_label(gpointer user_data) {
        GtkLabel* label = (GtkLabel*)user_data;

        sec++;
        if (sec > 59) { sec=0; min++; }

        gchar buf[256];
        snprintf(buf,sizeof(buf),"%02d:%02d",min,sec);

        gtk_label_set_text(label,buf);
        return TRUE;
}

static void activate(GtkApplication* app, gpointer user_data) {
        GtkWidget* window;
        GtkWidget* label;

        UserData* ud = (UserData*)user_data;

        window = gtk_application_window_new(app);
        gtk_window_set_title(GTK_WINDOW(window),"eyver");
        gtk_window_set_default_size(GTK_WINDOW(window),400,200);

        GtkWidget* center = gtk_center_box_new();
        GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
        gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
        gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
        gtk_widget_add_css_class(center,"box");


        label = gtk_label_new(ud->msg);
        gtk_widget_add_css_class(label,"text");
        gtk_widget_add_css_class(label,"title");
        gtk_box_append(GTK_BOX(box),label);

        GtkWidget* l2 = gtk_label_new("00:00");
        gtk_widget_add_css_class(l2,"text");
        gtk_widget_add_css_class(l2,"subtitle");
        gtk_box_append(GTK_BOX(box),l2);

        gtk_center_box_set_center_widget(GTK_CENTER_BOX(center), box);
        gtk_window_set_child(GTK_WINDOW(window), center);

        char buf[1024];
        snprintf(buf,sizeof(buf),
                 ".text { font-family: \"%s\"; color: #cfcfcf; }\n"
                 ".title { font-size: 64px; }\n"
                 ".subtitle { font-size: 32px; }\n"
                 ".box { background-color: #181818 }\n",
                 ud->font);


        GtkCssProvider* provider = gtk_css_provider_new();
        gtk_css_provider_load_from_string(provider,buf);

        gtk_style_context_add_provider_for_display(
                                                   gdk_display_get_default(),
                                                   GTK_STYLE_PROVIDER(provider),
                                                   GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
                                                   );
        g_object_unref(provider);

        GtkEventController *key_controller = gtk_event_controller_key_new();
        g_signal_connect(key_controller, "key-pressed", G_CALLBACK(on_key_pressed), app);
        gtk_widget_add_controller(window, key_controller);

        g_timeout_add(1000, update_label, l2);

        gtk_window_fullscreen(GTK_WINDOW(window));
        gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
        GtkApplication* app;
        int status;

        UserData user_data = {0};
        user_data.font="Iosevka Heavy";

        if (argc < 2) {
                printf("Usage:\n");
                printf("    eyver <message> <font>\n");
                printf("    The font defaults to \"Iosevka Heavy\"\n");
                return 0;
        }
        if (argc > 2) user_data.font=argv[2];
        user_data.msg=argv[1];
        
        app = gtk_application_new("eyver.mangjin",G_APPLICATION_DEFAULT_FLAGS);
        g_signal_connect(app,"activate",G_CALLBACK(activate),&user_data);

        status = g_application_run(G_APPLICATION(app), 0, NULL);
        g_object_unref(app);

        return status;
}
