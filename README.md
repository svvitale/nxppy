nxppy
=====
nxppy is a *very* simple Python wrapper for interfacing with the excellent [NXP EXPLORE-NFC shield](http://uk.farnell.com/nxp-explore-nfc) for the [Raspberry Pi](http://www.raspberrypi.org/).  It takes NXP's NFC Reader Library and provides a thin layer for detecting a Mifare NFC tag, reading its UID (unique identifier), and reading/writing data from/to the user area.

License
=====
All files in this repository are distributed under the MIT license.

####External components
This work was based very heavily on NXP's MifareClassic example code. The example code was only reorganized to be more conducive as an interface. NXP still retains full copyright and ownership of the example code and the NFC Reader Library. The license conditions that need to be accepted in order to use this project in conjunction with the NFC Reader Library can be found in the document [NXP_NFC_Reader_Library_licencefile.pdf](https://github.com/Schoberm/nxppy/blob/master/NXP_NFC_Reader_Library_licencefile.pdf)

Compatibility
=====
Tested with both Python 2.7 and 3.4 as installed on Raspian Jessie.

Requirements
=====
The EXPLORE-NFC card relies on SPI being enabled. Please enable SPI using raspi-config prior to installing nxppy.

Installation
=====

nxppy is available from PyPI.  To install, first install the dependencies, e.g. on Raspian (replace `python3-dev` with `python2.7-dev` if you are using Python 2)

```
sudo apt-get update
sudo apt-get install build-essential cmake python3-dev unzip wget
```

then simply run:

```
pip install nxppy
```

Installation will take some time as it automatically pulls down the NXP NFC Reader Library from souce.

Usage
=====
Currently, the module supports ISO14443-3A/4A cards only:

```python
import nxppy

mifare = nxppy.Mifare()

# Select the first available tag and return the UID
uid = mifare.select()

# Read a single block of 4 bytes from block 10 
block10_bytes = mifare.read_block(10)

# Write a single block of 4 bytes
mifare.write_block(10, 'abcd')

# Read the entire user data area (this relies on byte 2 of the capability container being set to the correct tag size)
user_data = mifare.read()
```

Example polling for tags:

```python
import nxppy
import time

mifare = nxppy.Mifare()

# Print card UIDs as they are detected
while True:
    try:
        uid = mifare.select()
        print(uid)
    except nxppy.SelectError:
        # SelectError is raised if no card is in the field.
        pass

    time.sleep(1)
```

NDEF records can be read as bytes, and then passed through [ndeflib](https://github.com/nfcpy/ndeflib) for parsing

```python
import nxppy
import ndef

# Instantiate reader
mifare = nxppy.Mifare()

# Select tag
uid = mifare.select()

# Read NDEF data
ndef_data = mifare.read_ndef()

# Parse NDEF data
ndef_records = list(ndef.message_decoder(ndef_data))
```

Common Issues
=====
**I encounter `fatal error: Python.h: No such file or directory` during install.**

>The Python development package is required for nxppy install.  If you're using Raspbian, you can install this package using `sudo apt-get install python<xx>-dev` where "&lt;xx&gt;" is either "2.7" or "3" depending on which version of Python you're using.

**I encounter `error: nxp/build/linux/libNxpRdLibLinuxPN512.a: No such file or directory` during install.**

>Do you also see `cmake: command not found` further up in the error output?  If so, you're missing cmake.  If you're using Raspbian, you can install cmake using `sudo apt-get install cmake`.

**I encounter `error: [Errno 13] Permission denied: '/usr/local/lib/python2.7/dist-packages/nxppy.so'` during install.**

>Looks like you're trying to install nxppy into the global python site-packages directory.  There are [many](https://realpython.com/blog/python/python-virtual-environments-a-primer/) [many](https://www.davidfischer.name/2010/04/why-you-should-be-using-pip-and-virtualenv/) [many](https://www.dabapps.com/blog/introduction-to-pip-and-virtualenv-python/) blog posts out there about why it's best to develop Python applications using a virtualenv.  If you *really* want to install nxppy into the global package store, you can install with `sudo pip install nxppy`.  It's **not** recommended.

Feedback
=====
I welcome your feedback and pull requests!  This project started as a necessity for my own Raspberry Pi development, but I'm hoping others will find it useful as a way to quickly bootstrap NFC-based projects.  Enjoy!
