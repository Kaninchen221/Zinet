@echo off

pip install -r Tools\requirements.txt

python -m pip install -e Tools\generator
python -m pip install -e Tools\reflector