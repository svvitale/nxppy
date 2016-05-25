from setuptools import setup
from distutils.core import Extension
from distutils.command.build import build
import os
from subprocess import call
import multiprocessing
from glob import glob
nxppy = Extension('nxppy',
                     #('DEBUG',None),
                            define_macros = [('LINUX',None),('NATIVE_C_CODE',None),('NXPBUILD_CUSTOMER_HEADER_INCLUDED',None),('NXPBUILD__PHHAL_HW_RC523',None)],
                            extra_compile_args=['-lpthread','-lrt','-std=gnu99'],
                            
                            sources = ['Mifare.c','nxppy.c'],
                            include_dirs = ['nxprdlib/NxpRdLib/intfs','nxprdlib/NxpRdLib/types','nxprdlib/NxpRdLib','linux/intfs','linux/comps/phbalReg/src/Linux','linux/shared','examples/NfcrdlibEx4_MIFAREClassic/intfs','nxprdlib/NxpRdLib/comps/phbalReg/src/Stub','linux/comps/phPlatform/src/Posix','linux/comps/phOsal/src/Posix'],
                            extra_link_args=['build/linux/libNxpRdLibLinuxPN512.a','-lpthread','-lrt','-std=gnu99']
                     )


short_description = 'A python extension for interfacing with the NXP PN512 NFC Reader. Targeted specifically for Raspberry Pi and the EXPLORE-NFC module'

setup(name='nxppy',
      version='1.3.2',
      author = 'Scott Vitale',
       author_email = 'svvitale@gmail.com',
       url = 'http://github.com/svvitale/nxppy',
       test_suite = 'nose.collector',
       setup_requires=['nose>=1.0'],\
                        ext_modules = [nxppy])


