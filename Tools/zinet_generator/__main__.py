from pathlib import Path
import argparse
from zinet_generator.project_generator import ProjectGenerator


if __name__ == '__main__':

    parser = argparse.ArgumentParser(description='PG')
    parser.add_argument('--AddressSanitizer', type=str, help='true or false', default='false')
    cmdArgs = parser.parse_args()
    
    print("Arguments:")
    print(cmdArgs)

    projectGenerator = ProjectGenerator()
    projectPath = Path(".").absolute().parent
    print(f"Project absolute path: {projectPath}")
    projectGenerator.generate_project(projectPath, cmdArgs)