#!/usr/bin/python
from distutils.core import setup, Extension

igrf = Extension('pygrf', sources = ['igrf_sub.c', 'pygrfmodule.c'], libraries = ['m', 'f2c'], library_dirs = ['/usr/lib/'])

setup(name = 'pygrf',
	version = '1.0',
	description = 'IGRF v.10 Python wrapper',
	author = 'David Parunakian',
	author_email = 'dp@xientific.info',
	ext_modules = [igrf])
