/* Analysis pseudo-C, not buildable source. */

void FUN_80017dcc(int param_1)

{
  uint uVar1;
  ushort uVar2;
  
  uVar1 = (uint)*(byte *)(param_1 + 0x6a);
  if (((&DAT_801a7aee)[uVar1 * 0xe] & 0x2000) == 0) {
    *(undefined1 *)(param_1 + 0x67) = 0;
  }
  uVar2 = *(ushort *)(param_1 + 8) & 0xfffb;
  *(ushort *)(param_1 + 8) = uVar2;
  if (((&DAT_801a7aee)[uVar1 * 0xe] & 0x1800) != 0) {
    *(ushort *)(param_1 + 8) = uVar2 | 4;
    *(undefined1 *)(param_1 + 0x21) = 0;
    if (((&DAT_801a7aee)[uVar1 * 0xe] & 0x1000) != 0) {
      *(undefined1 *)(param_1 + 0x21) = 0x80;
    }
    *(undefined1 *)(param_1 + 0x22) = 0;
    if (((&DAT_801a7aee)[uVar1 * 0xe] & 0x800) != 0) {
      *(undefined1 *)(param_1 + 0x22) = 0xc0;
    }
  }
  *(undefined4 *)(param_1 + 0xc) = 0x808080;
  if (((&DAT_801a7aee)[uVar1 * 0xe] & 0x4000) != 0) {
    *(undefined4 *)(param_1 + 0xc) = 0x404040;
  }
  return;
}

