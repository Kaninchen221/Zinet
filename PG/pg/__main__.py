from pathlib import Path
import sys
sys.path.append(".")

from pg.project_generator import ProjectGenerator

if __name__ == '__main__':
    projectGenerator = ProjectGenerator()
    projectPath = Path(".").absolute().parent
    print(f"Project absolute path: {projectPath}")
    projectGenerator.generate_project(projectPath)