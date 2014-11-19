nxppy
=====
nxppy is a *very* simple Python wrapper for interfacing with the excellent [NXP EXPLORE-NFC shield](http://uk.farnell.com/nxp-explore-nfc) for the [Raspberry Pi](http://www.raspberrypi.org/).  It takes NXP's Public Reader Library and provides a thin layer for detecting a Mifare RFID tag, reading its UID (unique identifier), and reading/writing data from/to the user area.

This was based very heavily on NXP's card_polling example code.  The example code was only reorganized to be more conducive as an interface.  NXP still retains full copyright and ownership of the example code.  All files outside of the NXP directory are distributed under the MIT license.

Compatibility
=====
Tested with both Python 2.7 (as installed on Raspberry Pi) and with a manually compiled version of Python 3.4.

Requirements
=====
You'll need to run these commands and install these packages to build nxppy:

```
sudo apt-get install python2.7-dev
sudo apt-get install cmake
```

Installation
=====
nxppy is available from pypi.  Simply run:

```
pip install nxppy
```

Source
=====
To install from source, use distutils:

```
sudo apt-get install python-setuptools
python setup.py build install
```

Usage
=====
Currently, the module supports only Mifare cards:

```python
import nxppy

mifare = nxppy.Mifare()

uid = mifare.select() # Select the first available tag and return the UID
block10bytes = mifare.read_block(10) # Read 16 bytes starting from block 10 (each block is 4 bytes, so technically this reads blocks 10-13)
mifare.write_block(10, b'abcd') # Write a single block of 4 bytes
```

Feedback
=====
I welcome your feedback and pull requests!  This project started as a necessity for my own Raspberry Pi development, but I'm hoping others will find it useful as a way to quickly bootstrap NFC-based projects.  Enjoy!
