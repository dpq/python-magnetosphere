This project is devoted to making magnetosphere models and related physics tools easier to use when coding in Python.

Currently, it only contains IGRF, a Python extension module that allows fast calculations of the Earth's magnetic field. IGRF downloads the source code and coefficient files from the official NSSDC repository, translates the original Fortran code to C, patches it, and compiles into a Python module. This process requires f2c to be installed.

I plan to add other relevant models (such as the paraboloid model of the magnetosphere, Tsyganenko model, AP8/AE8, etc) in the near future.
I also plan to provide required C source files in the package instead of downloading them from NSSDC FTP archive during installation.

Works with Python 2.5; hasn't been tested yet with other versions.