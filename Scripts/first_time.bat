@echo off

pip install -r requirements.txt

cd PGenerator
python zinet_pgenerator/setup.py build
python zinet_pgenerator/setup.py install
cd ..

cd PReflector
python zinet_preflector/setup.py build
python zinet_preflector/setup.py install
cd ..