# -*- mode: python -*-

from PyInstaller.config import CONF
from os import getcwd
from os.path import dirname
from sys import argv
block_cipher = None

# Put exe in the same directory as accents.spec
CONF['distpath'] = dirname(getcwd() + '/' + argv[1])

a = Analysis(['accents.py'],
             binaries=[],
             datas=[],
             hiddenimports=[],
             hookspath=[],
             runtime_hooks=[],
             excludes=[],
             win_no_prefer_redirects=False,
             win_private_assemblies=False,
             cipher=block_cipher,
             noarchive=False)
pyz = PYZ(a.pure, a.zipped_data,
             cipher=block_cipher)
exe = EXE(pyz,
          a.scripts,
          a.binaries,
          a.zipfiles,
          a.datas,
          [],
          name='accents',
          debug=False,
          bootloader_ignore_signals=False,
          strip=False,
          upx=True,
          runtime_tmpdir=None,
          console=True )
