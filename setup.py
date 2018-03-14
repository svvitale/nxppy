from __future__ import print_function
from setuptools import setup
from distutils.core import Extension
from distutils.command.build_ext import build_ext
import sys
import os

nxprdlib_include_path = '/usr/local/src/nxprdlib'
nxprdlib_link_path = '/usr/local/lib/nxprdlib'

nxppy = Extension('nxppy',
                  define_macros=[('LINUX', None),
                                 ('NATIVE_C_CODE', None),
                                 ('NXPBUILD_CUSTOMER_HEADER_INCLUDED', None),
                                 ('NXPBUILD__PHHAL_HW_RC523', None)],
                  extra_compile_args=['-O0',
                                      '-std=gnu99',
                                      '-isystem{}/nxprdlib/NxpRdLib/intfs'.format(nxprdlib_include_path),
                                      '-isystem{}/nxprdlib/NxpRdLib/types'.format(nxprdlib_include_path),
                                      '-isystem{}/nxprdlib/NxpRdLib/comps/phbalReg/src/LinuxUserSpi'.format(nxprdlib_include_path),
                                      '-isystem{}/linux/shared'.format(nxprdlib_include_path),
                                      '-isystem{}/examples/NfcrdlibEx4_MIFAREClassic/intfs'.format(nxprdlib_include_path),
                                      '-isystem{}/nxprdlib/NxpRdLib/comps/phbalReg/src/Stub'.format(nxprdlib_include_path),
                                      '-isystem{}/linux/comps/phPlatform/src/Posix'.format(nxprdlib_include_path),
                                      '-isystem{}/linux/comps/phOsal/src/Posix'.format(nxprdlib_include_path),
                                      '-isystem{}/linux/intfs'.format(nxprdlib_include_path)
                                      ],
                  extra_link_args=['{}/libNxpRdLibLinuxPN512.a'.format(nxprdlib_link_path), '-lpthread', '-lrt'],
                  sources=['Mifare.c', 'nxppy.c']

                  )


# noinspection PyShadowingBuiltins
class BuildNxppy(build_ext):
    def run(self):
        if not os.path.isdir(nxprdlib_include_path) or not os.path.isdir(nxprdlib_link_path):
            print('\nNXP Reader library not found.  Install it using `sudo apt-get install nxprdlib`\n')
            sys.exit(1)

        # Run the rest of the build
        build_ext.run(self)


short_description = 'A python extension for interfacing with the NXP PN512 NFC Reader. Targeted specifically for ' \
                    'Raspberry Pi and the EXPLORE-NFC module'

# noinspection PyBroadException
try:
    # noinspection PyPackageRequirements
    import pypandoc

    long_description = pypandoc.convert('README.md', 'rst')
except:
    long_description = short_description

setup(name='nxppy',
      version='1.6.0',
      description=short_description,
      long_description=long_description,
      author='Scott Vitale',
      author_email='svvitale@gmail.com',
      url='http://github.com/svvitale/nxppy',
      ext_modules=[nxppy],
      cmdclass={'build_ext': BuildNxppy})
