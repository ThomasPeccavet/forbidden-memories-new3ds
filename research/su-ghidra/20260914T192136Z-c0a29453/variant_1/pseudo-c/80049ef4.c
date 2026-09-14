/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80049ef4(int *param_1,undefined2 param_2)

{
  int iVar1;
  int iVar2;
  
  *(undefined1 *)(DAT_8009c7d8 + 0x500) = 1;
  iVar1 = DAT_8009c7d8;
  iVar2 = *param_1;
  if ((((iVar2 != 0x53455170) && (iVar2 != 0x6468544d)) && (iVar2 != 0x2054444b)) &&
     (iVar2 != 0x3154444b)) {
    return 0xffffffff;
  }
  if (*(short *)(DAT_8009c7d8 + 0x7e0) != -1) {
    *(undefined1 *)(DAT_8009c7d8 + 0x500) = 0;
    return 0xffffffff;
  }
  *(int **)(DAT_8009c7d8 + 0x7e8) = param_1;
  *(undefined2 *)(iVar1 + 0x7e0) = param_2;
  *(undefined2 *)(iVar1 + 0x7e2) = 2;
  *(undefined1 *)(iVar1 + 0x500) = 0;
  return 0;
}

