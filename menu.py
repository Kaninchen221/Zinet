from consolemenu import ConsoleMenu, SelectionMenu
from consolemenu.items import MenuItem, FunctionItem

import subprocess

from pathlib import Path

class Menu:
       
        __menuItems = []
        __menu = ConsoleMenu("Zinet Utilities", "")

        def run_script(self, script_file_name):
                scriptFilePath = str(Path('.').absolute()) + "/Scripts/" + script_file_name
                process = subprocess.run(scriptFilePath, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True, universal_newlines=True)

                outputFileName = "output_" + script_file_name + ".temp";
                outputFilePath = str(Path('.')) + "/Scripts/outputs/" + outputFileName
                with open(outputFilePath, 'w') as file:
                        if process.stdout is not None: file.write(process.stdout)
                        if process.stderr is not None: file.write(process.stderr)
                        file.write("Return code: " + str(process.returncode))

                if process.returncode != 0:
                       if process.stdout is not None: raise Exception(str(process.stdout))
                       if process.stderr is not None: raise Exception(str(process.stderr))

        
        def main_menu(self):
                self.__menuItems = [
                        FunctionItem("Generate Project Files", self.run_script, ["generate_project_files.bat"]),
                        FunctionItem("Conan Install", self.run_script, ["conan_install.py"]),
                        FunctionItem("Build Project", self.run_script, ["build.py"]),
                        FunctionItem("Compile Project", self.run_script, ["compile.bat"]),
                        FunctionItem("Run Automatic Tests", self.run_script, ["run_automatic_tests.py"]),
                        FunctionItem("Run All Tests", self.run_script, ["run_all_tests.py"]),
                        FunctionItem("Clear Build Folder", self.run_script, ["build_clear.bat"])
                ]

                for item in self.__menuItems:
                        self.__menu.append_item(item)

                self.__menu.show()

                #menu.join()


if __name__ == "__main__":
    menu = Menu()
    menu.main_menu()