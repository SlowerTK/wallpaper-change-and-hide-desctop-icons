import keyboard
import subprocess

def toggle_desktop_icons():
    subprocess.run(r"iconHider.exe -hax")

def on_hotkey_pressed(hotkey_name):
    if hotkey_name == 'win+f12':
        subprocess.call("pythonw.exe \"wall.py\"")
    elif hotkey_name == 'win+shift+f12':
        subprocess.call(["pythonw.exe", "wall.py", "-a"])
    elif hotkey_name == 'win+alt+f12':
        subprocess.call(["pythonw.exe", "wall.py", "-l"])
    elif hotkey_name == 'win+f11':
        toggle_desktop_icons()

keyboard.add_hotkey('win+f12', on_hotkey_pressed, args=('win+f12',))
keyboard.add_hotkey('win+shift+f12', on_hotkey_pressed, args=('win+shift+f12',))
keyboard.add_hotkey('win+alt+f12', on_hotkey_pressed, args=('win+alt+f12',))
keyboard.add_hotkey('win+f1', on_hotkey_pressed, args=('win+f1',))
keyboard.wait()
