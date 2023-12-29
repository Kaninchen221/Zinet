@echo off

cd Tools
python -m zinet_generator --AddressSanitizer false
cd ..