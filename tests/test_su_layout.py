import io
import struct
import unittest

from tools.validate_su_layout import (
    SECTOR_RAW,
    SYNC,
    read_mode2_form1_sector,
    read_user_bytes,
)


def make_sector(payload: bytes, form2: bool = False) -> bytes:
    if len(payload) != 2048:
        raise ValueError("payload must be 2048 bytes")
    raw = bytearray(SECTOR_RAW)
    raw[:12] = SYNC
    raw[12:15] = b"\x00\x02\x00"
    raw[15] = 2
    submode = 0x20 if form2 else 0x00
    raw[16:20] = bytes((1, 0, submode, 0))
    raw[20:24] = raw[16:20]
    raw[24:2072] = payload
    return bytes(raw)


class Mode2Tests(unittest.TestCase):
    def test_read_form1_sector(self):
        payload = bytes((i & 0xFF) for i in range(2048))
        f = io.BytesIO(make_sector(payload))
        self.assertEqual(read_mode2_form1_sector(f, 0), payload)

    def test_reject_form2(self):
        payload = bytes(2048)
        f = io.BytesIO(make_sector(payload, form2=True))
        with self.assertRaises(ValueError):
            read_mode2_form1_sector(f, 0)

    def test_cross_sector_read(self):
        a = bytes([0x11]) * 2048
        b = bytes([0x22]) * 2048
        f = io.BytesIO(make_sector(a) + make_sector(b))
        got = read_user_bytes(f, 0, 2040, 32)
        self.assertEqual(got[:8], bytes([0x11]) * 8)
        self.assertEqual(got[8:], bytes([0x22]) * 24)

    def test_resource_tail_sector_mapping(self):
        # 0x39000 bytes / 0x800 bytes per Form-1 user sector = 0x72.
        self.assertEqual(0x39000 // 0x800, 0x72)


if __name__ == "__main__":
    unittest.main()
