/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8008219c(void)

{
  bool bVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = FUN_800746b8(0xffffffff);
  if ((DAT_80095bd4 < iVar2) ||
     (iVar2 = DAT_80095bd8 + 1, bVar1 = 0xf0000 < DAT_80095bd8, DAT_80095bd8 = iVar2, bVar1)) {
    FUN_8008fa78(s_GPU_timeout_que__d_stat__08x_chc_8001223c,DAT_80095bc0 - DAT_80095bc4 & 0x3f,
                 *DAT_80095ba0,*DAT_80095bac,*DAT_80095ba4);
    DAT_80095bd0 = FUN_80074a54(0);
    DAT_80095bc4 = 0;
    DAT_80095bc0 = 0;
    *DAT_80095bac = 0x401;
    *DAT_80095bbc = *DAT_80095bbc | 0x800;
    *DAT_80095ba0 = 0x2000000;
    *DAT_80095ba0 = 0x1000000;
    FUN_80074a54(DAT_80095bd0);
    uVar3 = 0xffffffff;
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}

