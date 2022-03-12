from PPG.root import *
from PPG.generate_class import *

root = generate_targets()

print("---Sandbox---")

file_generator = ZtFileGenerator()
generate_result = file_generator.generate_class("ZtCore", "TestClass", True, root)
print(generate_result)
print(vars(file_generator))
