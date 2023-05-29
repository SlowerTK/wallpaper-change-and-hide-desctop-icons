import glob
import sys
import ctypes
import os

SPI_SETDESKWALLPAPER = 20
STYLE = 0
UIPARAM = 0

path = ".currentfile"

if len(sys.argv) > 1 and sys.argv[1] == '-a':
    image_path = glob.glob(r"C:\path-to-you\wallpaper-folder\*") #win+shift+f12
elif len(sys.argv) > 1 and sys.argv[1] == '-l':
    image_path = glob.glob(r"C:\path-to-you\wallpaper-folder\*") #win+alt+f12
else:
    image_path = glob.glob(r"C:\Windows\Web\Wallpaper\ThemeA\*.jpg") #win+f12


if os.path.isfile(path):
    with open(path, "r") as currentFile:
        current = int(currentFile.readline())
        currentFile.close()
else:
    with open(path, "w") as currentFile:
        currentFile.write("0")
        currentFile.close()


if current + 1 >= len(image_path):
    current = 0
else:
    current = current + 1

ctypes.windll.user32.SystemParametersInfoW(SPI_SETDESKWALLPAPER, STYLE, image_path[current], UIPARAM)

currentFile = open(path, "w")
currentFile.write(str(current) + "\n")
currentFile.close()
