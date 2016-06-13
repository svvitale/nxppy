from setuptools import setup
from distutils.core import Extension
from distutils.command.build import build
import os
from subprocess import call
import multiprocessing
from glob import glob



nxppy = Extension('nxppy',
                    define_macros = [('LINUX',None),('NATIVE_C_CODE',None),('NXPBUILD_CUSTOMER_HEADER_INCLUDED',None),('NXPBUILD__PHHAL_HW_RC523',None)],
                    #compile argument '-w' is for not getting warnings because i can't do the necessary OPT="" shell command before starting setup.py
                    extra_compile_args=['-w','-O0','-lrt','-lpthread','-std=gnu99'],
                    extra_link_args=['build/linux/libNxpRdLibLinuxPN512.a','-O0','-lpthread','-lrt','-std=gnu99'],
                    sources = ['Mifare.c', 'nxppy.c']

)

class build_nxppy(build):
    def run(self):
        def compile(extra_preargs=None):
            call( './get_nxpRdLib.sh', shell=True )

            # Find where neard-explorenfc was extracted

            # Add relevant include directories
            
            nxppy.include_dirs.append('nxprdlib/NxpRdLib/intfs')
            nxppy.include_dirs.append('nxprdlib/NxpRdLib/types')
            nxppy.include_dirs.append('nxprdlib/NxpRdLib')
            nxppy.include_dirs.append('linux/intfs')
            nxppy.include_dirs.append('linux/comps/phbalReg/src/Linux')
            nxppy.include_dirs.append('linux/shared')
            nxppy.include_dirs.append('examples/NfcrdlibEx4_MIFAREClassic/intfs')
            nxppy.include_dirs.append('nxprdlib/NxpRdLib/comps/phbalReg/src/Stub')
            nxppy.include_dirs.append('linux/comps/phPlatform/src/Posix')
            nxppy.include_dirs.append('linux/comps/phOsal/src/Posix')

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
