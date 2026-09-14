/* Analysis pseudo-C, not buildable source. */

void FUN_80018010(int param_1)

{
  uint uVar1;
  
  uVar1 = (uint)*(byte *)(param_1 + 0x6a);
  *(undefined1 *)(param_1 + 0x22) = 0;
  *(ushort *)(param_1 + 8) = *(ushort *)(param_1 + 8) & 0xfffb;
  if (((&DAT_801a7aee)[uVar1 * 0xe] & 0x1000) != 0) {
    *(undefined1 *)(param_1 + 0x22) = 0x80;
  }
  *(undefined1 *)(param_1 + 0x21) = 0;
  if (((&DAT_801a7aee)[uVar1 * 0xe] & 0x800) != 0) {
    *(undefined1 *)(param_1 + 0x21) = 0xc0;
  }
  *(undefined4 *)(param_1 + 0xc) = 0x808080;
  if (((&DAT_801a7aee)[uVar1 * 0xe] & 0x4000) != 0) {
    *(undefined4 *)(param_1 + 0xc) = 0x404040;
  }
  FUN_80017d44(param_1);
  if (((&DAT_801a7aee)[uVar1 * 0xe] & 0x2000) == 0) {
    *(undefined1 *)(param_1 + 0x67) = 0;
  }
  return;
}

