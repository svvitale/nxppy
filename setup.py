from setuptools import setup
from distutils.core import Extension
from distutils.command.build import build
import os
from subprocess import call
import multiprocessing
from glob import glob



nxppy = Extension('nxppy',
                    define_macros = [('LINUX',None),('NATIVE_C_CODE',None),('NXPBUILD_CUSTOMER_HEADER_INCLUDED',None),('NXPBUILD__PHHAL_HW_RC523',None)],
                    extra_compile_args=['-O0',
                                        '-std=gnu99',
                                        '-isystemnxprdlib/NxpRdLib/intfs',
                                        '-isystemnxprdlib/NxpRdLib/types',
                                        '-isystemnxprdlib/NxpRdLib',
                                        '-isystemlinux/intfs',
                                        '-isystemlinux/comps/phbalReg/src/Linux',
                                        '-isystemlinux/shared',
                                        '-isystemexamples/NfcrdlibEx4_MIFAREClassic/intfs',
                                        '-isystemnxprdlib/NxpRdLib/comps/phbalReg/src/Stub',
                                        '-isystemlinux/comps/phPlatform/src/Posix',
                                        '-isystemlinux/comps/phOsal/src/Posix'
                    ],
                    extra_link_args=['build/linux/libNxpRdLibLinuxPN512.a','-lpthread','-lrt'],
                    sources = ['Mifare.c', 'nxppy.c']
                 
)

class build_nxppy(build):
    def run(self):
        def compile(extra_preargs=None):
            call( './get_nxpRdLib.sh', shell=True )


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
       version = '1.3.2',
       description = short_description, 
       long_description = long_description,
       author = 'Scott Vitale',
       author_email = 'svvitale@gmail.com',
       url = 'http://github.com/svvitale/nxppy',
       test_suite = 'nose.collector',
       setup_requires=['nose>=1.0'],
       ext_modules = [nxppy],
       cmdclass = {'build': build_nxppy})
