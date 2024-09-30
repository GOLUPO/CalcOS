# keyboard.py
from pynput import keyboard as kb

_hotkeys = {}

def add_hotkey(key, function):
    def on_press(key_pressed):
        try:
            if key_pressed.char == key:
                function()
        except AttributeError:
            if key_pressed == kb.Key.esc and key == 'esc':
                function()

    listener = kb.Listener(on_press=on_press)
    listener.start()
