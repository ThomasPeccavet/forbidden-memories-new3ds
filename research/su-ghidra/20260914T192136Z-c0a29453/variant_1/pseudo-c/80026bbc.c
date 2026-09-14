/* Analysis pseudo-C, not buildable source. */

ushort FUN_80026bbc(void)

{
  int iVar1;
  
  if ((DAT_8009c550 & 0x8000) != 0) {
    iVar1 = (uint)(byte)(&DAT_80091eec)[DAT_8009c5a4] * 2;
    if ((DAT_8009c550 & 0x4000) != 0) {
      iVar1 = iVar1 + 1;
    }
    (*(code *)(&PTR_LAB_80091e74)[iVar1])();
  }
  return DAT_8009c550;
}

