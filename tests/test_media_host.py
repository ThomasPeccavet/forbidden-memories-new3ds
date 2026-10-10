"""Exercise production XA, STR, MDEC/DMA, disc and NDSP adapter without a ROM."""
import os
from pathlib import Path
import shlex
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class MediaHostTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cc = shlex.split(os.environ.get("CC", "cc"))
        if not cc or not shutil.which(cc[0]):
            raise unittest.SkipTest("Host C compiler required")
        cls.temp = tempfile.TemporaryDirectory()
        cls.binary = Path(cls.temp.name) / "media"
        sources = ["fm_memory","fm_spu", "fm_mdec", "fm_media", "fm_vlc", "fm_xa", "fm_audio", "disc"]
        cmd = cc + ["-std=gnu11", "-O2", "-Wall", "-Werror=implicit-function-declaration",
                    "-DPSX_NO_DEBUG_TOOLS", "-I", str(ROOT / "tests/host/include"),
                    "-I", str(ROOT / "3ds/include")]
        cmd += [str(ROOT / f"3ds/source/{s}.c") for s in sources]
        cmd += [str(ROOT / "tests/host/test_media.c"), "-o", str(cls.binary)]
        result = subprocess.run(cmd, capture_output=True, text=True)
        if result.returncode:
            cls.temp.cleanup()
            raise AssertionError(result.stdout + result.stderr)

    @classmethod
    def tearDownClass(cls):
        cls.temp.cleanup()

    def run_case(self, case, *args):
        result = subprocess.run([str(self.binary), case, *map(str, args)], capture_output=True, text=True)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)

    def test_xa_pcm_history_and_formats(self):
        self.run_case("xa")

    def test_audio_buffer_ownership_and_dsp_failure(self):
        self.run_case("audio")

    def test_str_complete_frames_and_ring_backpressure(self):
        self.run_case("video")

    def test_mdec_input_output_dma_and_rgb_depths(self):
        self.run_case("mdec")

    def test_snapshot_replay_and_transactional_decoder_failure(self):
        self.run_case("snapshot")

    def make_disc(self):
        image = Path(self.temp.name) / "synthetic-disc.bin"
        def raw_sector():
            raw = bytearray(2352)
            raw[1:11] = bytes([255] * 10)
            raw[15] = 2
            raw[16:20] = raw[20:24] = bytes([1, 2, 0x64, 1])
            return raw
        with image.open("wb") as f:
            f.truncate(548427600)  # Sparse synthetic fixture, no game content.
            pvd = raw_sector()
            pvd[24:31] = b"\x01CD001\x01"
            f.seek(16 * 2352)
            f.write(pvd)
            raw = raw_sector()
            for g in range(18):
                raw[24 + g * 128:40 + g * 128] = bytes([12] * 16)
                raw[40 + g * 128:152 + g * 128] = bytes([0xF1] * 112)
            raw[2323], raw[2351] = 0xA5, 0x7E
            f.seek(100 * 2352)
            f.write(raw)
            raw[17] = raw[21] = 3
            f.write(raw)
        return image

    def test_full_raw_sector_and_2048_compatibility(self):
        self.run_case("disc", self.make_disc())

    def test_xa_disc_filter_and_cd_volume_to_audio(self):
        self.run_case("pipeline", self.make_disc())

    @unittest.skipUnless(shutil.which("ffmpeg"), "Independent FFmpeg oracle unavailable")
    def test_xa_against_ffmpeg_pcm(self):
        # Synthetic nonzero 4-bit stereo, all four predictor filters, 16 sectors.
        raw = bytearray(2352)
        raw[1:11] = bytes([255] * 10)
        raw[15] = 2
        raw[16:20] = raw[20:24] = bytes([1, 0, 0x64, 1])
        sectors = []
        for n in range(32):
            for g in range(18):
                for u in range(8):
                    raw[24 + g * 128 + 4 + u] = ((n + g + u) % 4 << 4) | (8 + (g % 5))
                # Duplicate the XA header bytes as required by the format.
                raw[24 + g * 128:28 + g * 128] = raw[28 + g * 128:32 + g * 128]
                raw[36 + g * 128:40 + g * 128] = raw[32 + g * 128:36 + g * 128]
                for i in range(112):
                    raw[40 + g * 128 + i] = (i * 37 + n * 19 + g * 7) & 255
            sectors.append(bytes(raw))
        source = Path(self.temp.name) / "oracle.str"
        expected = Path(self.temp.name) / "oracle.pcm"
        actual = Path(self.temp.name) / "production.pcm"
        source.write_bytes(b"".join(sectors))
        result = subprocess.run(["ffmpeg", "-hide_banner", "-loglevel", "error", "-f", "psxstr",
                                 "-i", str(source), "-map", "0:a:0", "-frames:a", "16",
                                 "-f", "s16le", "-y", str(expected)], capture_output=True, text=True)
        self.assertEqual(result.returncode, 0, result.stderr)
        self.run_case("xa_dump", source, actual)
        self.assertEqual(len(expected.read_bytes()), 16 * 2016 * 4)
        self.assertEqual(actual.read_bytes(), expected.read_bytes())
