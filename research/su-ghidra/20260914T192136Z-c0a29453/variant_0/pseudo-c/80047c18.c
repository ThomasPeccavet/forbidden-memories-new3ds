/* Analysis pseudo-C, not buildable source. */

/* WARNING: Removing unreachable block (ram,0x80047c44) */

void FUN_80047c18(uint param_1)

{
  ushort *puVar1;
  int iVar2;
  undefined1 local_38 [4];
  undefined4 local_34;
  undefined1 *local_2c;
  
  iVar2 = (param_1 & 0xffff) * 8;
  puVar1 = (ushort *)(iVar2 + *(int *)(DAT_8009c7e0 + 0x448));
  FUN_80047660(*(undefined4 *)(DAT_8009c7e0 + 0x438),&DAT_801e6800,
               ((int)((uint)*(ushort *)(DAT_8009c7e0 + 2) * 8 + 0x7ff) >> 0xb) + 1 + (uint)*puVar1,
               *(undefined4 *)(puVar1 + 2),0x800,0x10);
  local_38[0] = 0x51;
  local_34 = *(undefined4 *)(DAT_8009c7e0 + 0x438);
  local_2c = &DAT_801e6800;
  FUN_800460a4(local_38);
  *(int *)(DAT_8009c7e0 + 0x438) =
       *(int *)(DAT_8009c7e0 + 0x438) + *(int *)(iVar2 + *(int *)(DAT_8009c7e0 + 0x448) + 4);
  return;
}

