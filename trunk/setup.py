#!/usr/bin/python
from distutils.core import setup, Extension

cxform = Extension('magnetosphere.cxform', sources = ['cxformmodule.c',
	'cxform-manual.c', 'cxform-auto.c'])
igrf = Extension('magnetosphere.igrf', sources = ['igrf_sub.c',
	'igrfmodule.c'], libraries = ['m', 'f2c'], library_dirs = ['/usr/lib/'])

setup(name='Magnetosphere',
	version='0.1',
	description='A collection of useful libraries for Earth & Space scientists',
	author='David Parunakian',
	author_email='dp@xientific.info',
	url='http://python-magnetosphere.googlecode.com',
	ext_modules=[igrf,cxform],
	packages=['magnetosphere'])
