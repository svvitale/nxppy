nxppy
=====
nxppy is a *very* simple Python wrapper for interfacing with the excellent [NXP EXPLORE-NFC shield](http://uk.farnell.com/nxp-explore-nfc) for the [Raspberry Pi](http://www.raspberrypi.org/).  It takes NXP's Reader Library and provides a thin layer for detecting a Mifare RFID tag, reading its UID (unique identifier), and reading/writing data from/to the user area.

This was based very heavily on NXP's card_polling example code.  The example code was only reorganized to be more conducive as an interface.  NXP still retains full copyright and ownership of the example code.  All files in this repository are distributed under the MIT license.

Compatibility
=====
Tested with both Python 2.7 (as installed on Raspberry Pi) and with a manually compiled version of Python 3.4.

Requirements
=====
The NXP-EXPLORE card relies on SPI being enabled.  Please enable SPI using raspi-config prior to installing nxppy.

Installation
=====
nxppy is available from pypi.  First, install pip if you don't have it already:

```
wget https://bootstrap.pypa.io/get-pip.py
sudo python get-pip.py
```

Then simply run:

```
sudo pip install nxppy
```

Installation will take some time as it automatically pulls down the NXP NFC Reader Library from souce.

Source
=====
To install from source, use distutils:

```
git clone https://github.com/svvitale/nxppy
cd nxppy
sudo apt-get install python-setuptools
sudo python setup.py build install

```

Usage
=====
Currently, the module supports only Mifare cards:

```python
import nxppy

mifare = nxppy.Mifare()

# Select the first available tag and return the UID
uid = mifare.select()

# Read 16 bytes starting from block 10 
# (each block is 4 bytes, so technically this reads blocks 10-13)
block10bytes = mifare.read_block(10)

# Write a single block of 4 bytes
mifare.write_block(10, b'abcd')
```

Polling example, equivalent to NXP's card_polling example:

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

Feedback
=====
I welcome your feedback and pull requests!  This project started as a necessity for my own Raspberry Pi development, but I'm hoping others will find it useful as a way to quickly bootstrap NFC-based projects.  Enjoy!
