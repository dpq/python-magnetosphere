#!/usr/bin/python
from distutils.core import setup, Extension

cxform = Extension('magnetosphere.cxform', sources = ['cxformmodule.c',
    'cxform-manual.c', 'cxform-auto.c'])
igrf = Extension('magnetosphere.igrf', sources = ['igrf_sub.c',
    'igrfmodule.c'], libraries = ['m', 'f2c'], library_dirs = ['/usr/lib/'])
rigidity = Extension('magnetosphere.rigidity', sources = ['rigidity.c',
		'rigiditymodule.c'], libraries = ['m', 'f2c'], library_dirs = ['/usr/lib/'])

setup(name='Magnetosphere',
    version='0.11',
    description='A collection of useful libraries for Earth & Space scientists',
    author='David Parunakian',
    author_email='dp@xientific.info',
    url='http://python-magnetosphere.googlecode.com',
    ext_modules=[igrf,cxform,rigidity],
    packages=['magnetosphere'],
    data_files=[('/usr/lib/igrf',
        ['dat/dgrf1945.dat', 'dat/dgrf1950.dat', 'dat/dgrf1955.dat',
         'dat/dgrf1960.dat', 'dat/dgrf1980.dat', 'dat/dgrf2000.dat',
         'dat/dgrf1965.dat', 'dat/dgrf1970.dat', 'dat/dgrf1975.dat',
         'dat/dgrf1985.dat', 'dat/dgrf1990.dat', 'dat/dgrf1995.dat',
         'dat/igrf1910.dat', 'dat/igrf1930.dat', 'dat/igrf2010.dat',
         'dat/dgrf2005.dat', 'dat/igrf1900.dat', 'dat/igrf1905.dat',
         'dat/igrf1915.dat', 'dat/igrf1920.dat', 'dat/igrf1925.dat',
         'dat/igrf1935.dat', 'dat/igrf1940.dat', 'dat/igrf2005.dat',
         'dat/igrf2010s.dat'])])