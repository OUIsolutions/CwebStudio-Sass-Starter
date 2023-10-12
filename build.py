
from shutil import rmtree,copytree

rmtree("src/data",ignore_errors=True)
copytree("data","src/data")
