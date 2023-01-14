#!/usr/bin/python
import os
from rgb565_converter.converter import convert_png_to_rgb565

SCRIPT_PATH = os.path.abspath(os.path.dirname(__file__))
ICON_SRC_DIR = os.path.join(SCRIPT_PATH, "../icons/")
ICON_DIR = os.path.join(SCRIPT_PATH, "../main/icons/")

class Object(object):
    pass

def current_dir() -> str:
    return os.path.dirname(os.path.realpath(__file__))

def get_icons() -> list[str]:
    return [os.path.realpath(os.path.join(ICON_SRC_DIR, icon)) for icon in os.listdir(ICON_SRC_DIR) if icon.endswith(".png")]

def main():
    icons = get_icons()
    for icon in icons:
        icon_name = os.path.basename(icon).rsplit(".", 1)[0]
        print(f"Converting \"{icon_name}\"")

        """
        args = {
            "input_file": icon,
            "output_file": os.path.abspath(os.path.join(ICON_DIR, icon_name + ".cpp"))
        }
        """
        # args.output_file ...
        args = Object()
        args.input_file = icon
        args.output_file = os.path.abspath(os.path.join(ICON_DIR, icon_name + ".cpp"))
        
        convert_png_to_rgb565(args)

if __name__ == "__main__":
    main()
