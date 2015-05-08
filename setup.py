from setuptools import setup
from distutils.core import Extension
from distutils.command.build import build
import os
from subprocess import call
import multiprocessing
from glob import glob

class build_nxppy(build):
    def run(self):
        def compile():
            call( './get_nxpRdLib.sh', shell=True )

        self.execute(compile, [], 'compiling NxpRdLib')

        # Run the rest of the build
        build.run(self)

nxprdlib_dir = glob('neard-explorenfc-*/nxprdlib')[0]

nxppy = Extension('nxppy',
                    sources = ['Mifare.c', 'nxppy.c'],
                    include_dirs = [nxprdlib_dir + '/types', 
                                    nxprdlib_dir + '/intfs'],
                    extra_compile_args=['-O1'],
                    extra_link_args=[nxprdlib_dir + '/libnxprdlib.a', '-lwiringPi']
)

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
