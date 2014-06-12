from distutils.core import setup, Extension

nxppy = Extension('nxppy',
                    sources = ['nxppy.c'],
                    include_dirs = ['NxpRdLib_PublicRelease/types', 'NxpRdLib_PublicRelease/intfs', 'NxpRdLib_PublicRelease/comps/phpalSli15693/src/Sw'],
                    extra_link_args=['NxpRdLib_PublicRelease/build/libnxprd.a']
)

setup (name = 'nxppy',
       version = '1.0',
       description = 'A python extension for interfacing with the NXP PN512 NFC Reader. Targetted specifically for Raspberry Pi and the EXPLORE-NFC module',
       ext_modules = [nxppy])
