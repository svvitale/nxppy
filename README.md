nxppy
=====
nxppy is a *very* simple Python wrapper for interfacing with the excellent [NXP EXPLORE-NFC shield](http://uk.farnell.com/nxp-explore-nfc) for the [Raspberry Pi](http://www.raspberrypi.org/).  It takes NXP's Public Reader Library and provides a thin layer for detecting and reading the UID (unique identifier) of a Mifare RFID tag present on the reader.

This was based very heavily on NXP's card_polling example code.  The example code was only reorganized to be more conducive as an interface.  NXP still retains full copyright and ownership of the example code.  nxppy.c and the relevant Python setup files are distributed under the MIT license.

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
python setup.py build install
```

Usage
=====
Currently, the module supports one static method which returns either the UID as a string or None if no card is present:

```python
import nxppy
uid = nxppy.read_mifare()
```

Feedback
=====
I welcome your feedback and pull requests!  This project started as a necessity for my own Raspberry Pi development, but I'm hoping others will find it useful as a way to quickly bootstrap NFC-based projects.  Enjoy!
