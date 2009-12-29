#!/usr/bin/python
from distutils.core import setup, Extension

cxform = Extension('cxform', sources = ['cxformmodule.c', 'cxform-manual.c', 'cxform-auto.c'])

setup (name = 'cxform',
	version = '1.0',
	description = 'NASA CXFORM 0.71 wrapper',
	author = 'David Parunakian',
	author_email = 'dp@xientific.info',
	ext_modules = [cxform])
