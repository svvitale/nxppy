nxppy
=====
nxppy is a *very* simple Python wrapper for interfacing with the excellent PN512-based [NXP EXPLORE-NFC shield](https://www.newark.com/nxp/explore-nfc-ww/nfc-add-on-board-raspberry-pi/dp/45X6356) for the [Raspberry Pi](http://www.raspberrypi.org/).  It takes NXP's NFC Reader Library and provides a thin layer for detecting a Mifare (Ultralight, NTAG210, NTAG213, NTAG216, etc) NFC tag, reading its UID (unique identifier), and reading/writing data from/to the user area.

License
=====
All files in this repository are distributed under the MIT license.

####External components

NXP now releases the NFC Reader Libary as a Debian package for easy installation on a Raspberry Pi.  Start by downloading the DEB file from here:

https://www.nxp.com/products/:PNEV512R?&tab=Design_Tools_Tab

or here:

https://www.nxp.com/products/:NFC-READER-LIBRARY?tab=In-Depth_Tab

Once downloaded, you can install the library by running:

```
sudo apt-get update
sudo apt-get install build-essential cmake python3-dev python2.7-dev
sudo dpkg -i NFC-Reader-Library-4.010-2.deb
```

Installation will take some time as it builds the NXP NFC Reader Library from source.

Compatibility
=====
Tested with both Python 2.7 and 3.4 as installed on Raspian Jessie.

Requirements
=====
The EXPLORE-NFC card relies on SPI being enabled. Please enable SPI using raspi-config prior to installing nxppy.

Installation
=====

nxppy is available from PyPI.  To install, simply run:

```
pip install nxppy
```

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

**Authentication example:**

This example uses the address layout of a NTAG216 card. Please refer to the specific card manual for the address layout.<br />
NTAG cards remain authenticated until removed from field or an error occurs. Reauthenticate to gain access again.

NTAG216 configuration page layout:

| Address  | Byte 0 | Byte 1 |    Byte 2    | Byte 3 |
| -------- | ------- | ----- | ------------ | ------ |
|   0xE3   | Mirror  | RFUI  | Mirror_Page  | AUTH0  |
|   0xE4   | Access  | RFUI  |    RFUI      | RFUI   |
|   0xE5   |  PWD    |  PWD  |     PWD      |  PWD   |

Relevant parts:<br />
**0xE3 Byte3** Defines the address from which the password verification is required<br />
**0xE4 Byte0 Bit7** Defines access protection: 0 for write protection (read only), 1 for read and write protection<br />
**0xE5** All 4 bytes are used to store the password

Values not mentioned here are the cards default values and not altered by this script.


```python
import nxppy

#initilize and select tag
mifare = nxppy.Mifare()
uid = mifare.select()


#Enable protection
####################

#write password 1234
mifare.write_block(0xE5, '1234')

#password protection starting at address D1
mifare.write_block(0xE3, b'\x04\x00\x00\xD1')

#enable readprotection (default is write protection only)
mifare.write_block(0xE4, b'\x80\x05\x00\x00')


#authenticate
####################
mifare.pwd_auth('1234')
#read and write from/to protected address space


#disable protection
####################

#reset password
mifare.write_block(0xE5, b'\xFF\xFF\xFF\xFF')

#set protection addr beyond address space
mifare.write_block(0xE3, b'\x04\x00\x00\xE7')

#reset readprotection 
mifare.write_block(0xE4, b'\x00\x05\x00\x00')

```


Common Issues
=====
**I encounter `fatal error: Python.h: No such file or directory` during install.**

>The Python development package is required for nxppy install.  If you're using Raspbian, you can install this package using `sudo apt-get install python<xx>-dev` where "&lt;xx&gt;" is either "2.7" or "3" depending on which version of Python you're using.

**I encounter `error: [Errno 13] Permission denied: '/usr/local/lib/python2.7/dist-packages/nxppy.so'` during install.**

>Looks like you're trying to install nxppy into the global python site-packages directory.  There are [many](https://realpython.com/blog/python/python-virtual-environments-a-primer/) [many](https://www.davidfischer.name/2010/04/why-you-should-be-using-pip-and-virtualenv/) [many](https://www.dabapps.com/blog/introduction-to-pip-and-virtualenv-python/) blog posts out there about why it's best to develop Python applications using a virtualenv.  If you *really* want to install nxppy into the global package store, you can install with `sudo pip install nxppy`.  It's **not** recommended.

Feedback
=====
I welcome your feedback and pull requests!  This project started as a necessity for my own Raspberry Pi development, but I'm hoping others will find it useful as a way to quickly bootstrap NFC-based projects.  Thanks to NXP for the excellent support over the years.  Enjoy!
