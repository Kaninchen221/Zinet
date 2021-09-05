import os
import sys
from pathlib import Path

def pause():
    programPause = input("Press the <ENTER> key to continue...")

def get_all_files(directory, extension):
    pathlist = Path(directory).rglob('*.' + extension)
    pathlist_as_string_list = []
    for path in pathlist:
        realpath = os.path.realpath(path)
        pathlist_as_string_list.append(str(realpath))
    return pathlist_as_string_list


def list_string_to_cmake_path_list(pathlist):
    pathlist_string = "\"\n\t\""
    pathlist_string = pathlist_string.join(pathlist)
    pathlist_string = pathlist_string.replace("\\", "/")
    pathlist_string = "\"" + pathlist_string + "\""
    return pathlist_string


class SafeDict(dict):
    def __missing__(self, key):
        return '{' + key + '}'