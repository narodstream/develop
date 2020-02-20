#!/usr/bin/env python3

import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk, Gdk, GdkPixbuf

class MainWindow(Gtk.Window):
    def __init__(self):
        Gtk.Window.__init__(self, title="Grid Example")
        pb = GdkPixbuf.Pixbuf.new_from_file_at_size('img/img001.png', 100, 100)
        img = Gtk.Image()
        img.set_from_pixbuf(pb)
        self.button = Gtk.Button(label="Click here!")
        self.button.set_image(img)
        self.button.set_image_position(Gtk.PositionType.TOP)
        self.button.set_always_show_image (True)
        self.button.set_margin_left(25)
        self.button.set_margin_top(25)
        self.button.connect("clicked",self.button_clicked)
        self.add(self.button)
    def button_clicked(self, widget):
        print("button clicked!")

win = MainWindow()
win.connect("delete-event", Gtk.main_quit)
win.show_all()
Gtk.main()

