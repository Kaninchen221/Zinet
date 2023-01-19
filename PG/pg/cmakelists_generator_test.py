from pg.safe_dict import SafeDict
from pg.cmakelists_generator_target import CMakeListsGeneratorTarget
from pathlib import Path
import numpy

class CMakeListsGeneratorTest(CMakeListsGeneratorTarget):
    
    def __init__(self) -> None:
        super().__init__()
        self.templatePath = Path(".").absolute() / "pg/templates/CMakeListsTestTemplate.txt"
