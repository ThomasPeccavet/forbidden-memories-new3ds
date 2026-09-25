from pathlib import Path
import unittest


ROOT = Path(__file__).resolve().parents[1]
MAKEFILE = (ROOT / "3ds/Makefile").read_text(encoding="utf-8")
MAIN = (ROOT / "3ds/source/main.c").read_text(encoding="utf-8")
GPU = (ROOT / "3ds/source/fm_gpu.c").read_text(encoding="utf-8")
MEMORY = (ROOT / "3ds/source/fm_memory.c").read_text(encoding="utf-8")
SHIM = (ROOT / "3ds/source/fm_runtime_shim.c").read_text(encoding="utf-8")


class B13574ProfileCleanTests(unittest.TestCase):
    def test_makefile_has_isolated_clean_and_profile_modes(self) -> None:
        self.assertIn("PROFILE ?= 0", MAKEFILE)
        self.assertIn("build-clean", MAKEFILE)
        self.assertIn("build-profile", MAKEFILE)
        self.assertIn("-DFM_PERF_PROFILE=0", MAKEFILE)
        self.assertIn("-DFM_PERF_PROFILE=1", MAKEFILE)

    def test_clean_build_has_visible_identity(self) -> None:
        self.assertIn("BUILD B135.78-CONSERVATIVE-CLEAN (SAFE B135.71)", MAIN)
        self.assertIn("BUILD B135.78-CONSERVATIVE-PROFILE (SAFE B135.71)", MAIN)

    def test_hot_gpu_diagnostics_are_profile_only(self) -> None:
        self.assertIn("#if FM_PERF_PROFILE", GPU)
        self.assertIn("B135.30/34/35: sampled opcode/raster timing is PROFILE-only", GPU)
        self.assertIn("++g_b13543_rect_nonzero_texels;", GPU)
        self.assertIn("++g_b13543_rect_writes;", GPU)

    def test_dma_packet_probe_is_profile_only(self) -> None:
        self.assertIn("#if FM_PERF_PROFILE", MEMORY)
        self.assertIn("b13554_is_hand_packet", MEMORY)
        self.assertIn("fm_gpu_b13532_profile_reset();", MEMORY)

    def test_b13571_safety_net_remains_present(self) -> None:
        self.assertIn("g_b13571_forced", SHIM)
        self.assertIn("cpu->write_byte(", SHIM)
        self.assertIn("0x8009C4B8u", SHIM)

    def test_heavy_console_block_is_profile_only(self) -> None:
        marker = "FMGpuOpcodePerf hot0 = {0};"
        pos = MAIN.index(marker)
        guard = MAIN.rfind("#if FM_PERF_PROFILE", 0, pos)
        self.assertGreaterEqual(guard, 0)


if __name__ == "__main__":
    unittest.main()
