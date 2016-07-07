from setuptools import setup
from distutils.core import Extension
from distutils.command.build import build
import os
import sys
from subprocess import call
import multiprocessing
from glob import glob


nxppy = Extension('nxppy',
                    define_macros = [('LINUX',None),('NATIVE_C_CODE',None),('NXPBUILD_CUSTOMER_HEADER_INCLUDED',None),('NXPBUILD__PHHAL_HW_RC523',None)],
                    extra_compile_args=['-O0',
                                        '-std=gnu99',
                                        '-isystemnxp/nxprdlib/NxpRdLib/intfs',
                                        '-isystemnxp/nxprdlib/NxpRdLib/types',
                                        '-isystemnxp/nxprdlib/NxpRdLib',
                                        '-isystemnxp/linux/intfs',
                                        '-isystemnxp/linux/comps/phbalReg/src/Linux',
                                        '-isystemnxp/linux/shared',
                                        '-isystemnxp/examples/NfcrdlibEx4_MIFAREClassic/intfs',
                                        '-isystemnxp/nxprdlib/NxpRdLib/comps/phbalReg/src/Stub',
                                        '-isystemnxp/linux/comps/phPlatform/src/Posix',
                                        '-isystemnxp/linux/comps/phOsal/src/Posix'
                    ],
                    extra_link_args=['nxp/build/linux/libNxpRdLibLinuxPN512.a','-lpthread','-lrt'],
                    sources = ['Mifare.c', 'nxppy.c']
                 
)

class build_nxppy(build):
    def run(self):
        def compile(extra_preargs=None):
            if sys.version_info >= (3, 0):
                python_lib = 'python3-dev'
            elif sys.version_info >= (2, 7):
                python_lib = 'python2.7-dev'
            else:
                raise ValueError("Python version not supported")

            call('./get_nxpRdLib.sh all ' + python_lib, shell=True)

        self.execute(compile, [], 'compiling NxpRdLib')

        # Run the rest of the build
        build.run(self)

short_description = 'A python extension for interfacing with the NXP PN512 NFC Reader. Targeted specifically for Raspberry Pi and the EXPLORE-NFC module'

try:
    import pypandoc
    long_description = pypandoc.convert('README.md', 'rst')
except:
    long_description = short_description

setup (name = 'nxppy',
       version = '1.4.3',
       description = short_description, 
       long_description = long_description,
       author = 'Scott Vitale',
       author_email = 'svvitale@gmail.com',
       url = 'http://github.com/svvitale/nxppy',
       test_suite = 'nose.collector',
       setup_requires=['nose>=1.0'],
       ext_modules = [nxppy],
       cmdclass = {'build': build_nxppy})
