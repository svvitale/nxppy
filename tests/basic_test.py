import unittest
from tests.either_or import either_or

class nxppyTests(unittest.TestCase):
    """Basic tests for the NXP Read Library python wrapper."""

    def test_import(self):
        """Test that it can be imported"""
        import nxppy

    @either_or('detect')
    def test_detect_mifare_present(self):
        """Test that we can read the UID from a present Mifare card.
        
        Either this test or the "absent" test below will pass, but never both.
        """
        import nxppy
        reader = nxppy.Mifare()
        self.assertIsInstance(reader, nxppy.Mifare)
        self.assertIsInstance(reader.select(), str, "Card UID is not a string")

    @either_or('detect')
    def test_detect_mifare_absent(self):
        """Test that an absent card results in a None response.
        
        Either this test or the "present" test above will pass, but never both.
        """
        import nxppy
        reader = nxppy.Mifare()
        self.assertIsInstance(reader, nxppy.Mifare)
        self.assertIsNone(reader.select(), "Card UID is not None")
