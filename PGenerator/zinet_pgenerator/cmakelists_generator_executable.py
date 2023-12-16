from zinet_pgenerator.safe_dict import SafeDict
from zinet_pgenerator.cmakelists_generator_target import CMakeListsGeneratorTarget
from pathlib import Path
import numpy

class CMakeListsGeneratorExecutable(CMakeListsGeneratorTarget):
    def __init__(self) -> None:
        super().__init__()
        self.templatePath = Path(".").absolute() / "zinet_pgenerator/templates/CMakeListsExecutableTemplate.txt"
        pass