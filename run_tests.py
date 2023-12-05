from platform import system as osname
import Build.CToolKit as ct
from shutil import rmtree
from os import makedirs

STARTER = 'doTheWorld/doTheWorldMain.h'

use_valgrind = True 

if osname() == 'Windows':
    use_valgrind = False
rmtree('tests/target',ignore_errors=True)

makedirs('tests/target',exist_ok=True)

test = ct.FolderTestPreset(
    folder='tests/main_test',
    side_effect_folder='tests/target',
    use_valgrind=use_valgrind
    )

test.generate_ouptut(reconstruct=False)
test.start_test()

ct.include_code_in_markdown('README.md',save_file=True)
rmtree('tests/target',ignore_errors=True)
