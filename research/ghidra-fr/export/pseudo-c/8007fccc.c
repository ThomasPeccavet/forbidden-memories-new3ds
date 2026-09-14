/* Analysis pseudo-C, not buildable source. */

void FUN_8007fccc(undefined4 param_1,short *param_2)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  
  if (DAT_80095a9a == '\x01') {
    iVar3 = (int)param_2[2];
    if ((iVar3 <= DAT_80095a9c) && (iVar3 + *param_2 <= (int)DAT_80095a9c)) {
      iVar1 = (int)param_2[1];
      if (((iVar1 <= DAT_80095a9e) &&
          (((iVar1 + param_2[3] <= (int)DAT_80095a9e && (0 < iVar3)) && (-1 < *param_2)))) &&
         ((-1 < iVar1 && (0 < param_2[3])))) {
        return;
      }
    }
    pcVar2 = s__s_bad_RECT_8001214c;
  }
  else {
    if (DAT_80095a9a != '\x02') {
      return;
    }
    pcVar2 = &DAT_8001216c;
  }
  (*(code *)PTR_FUN_80095a94)(pcVar2,param_1);
  (*(code *)PTR_FUN_80095a94)
            (s___d__d____d__d__80012158,(int)*param_2,(int)param_2[1],(int)param_2[2],
             (int)param_2[3]);
  return;
}

