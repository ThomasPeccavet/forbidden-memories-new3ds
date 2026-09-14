/* Analysis pseudo-C, not buildable source. */

char * FUN_8008fa08(char *param_1,char *param_2,int param_3)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  char *pcVar4;
  
  pcVar2 = (char *)0x0;
  if (((param_1 != (char *)0x0) && (iVar3 = 0, param_2 != (char *)0x0)) &&
     (pcVar2 = param_1, pcVar4 = param_1, 0 < param_3)) {
    do {
      cVar1 = *param_2;
      param_2 = param_2 + 1;
      *pcVar4 = cVar1;
      pcVar4 = pcVar4 + 1;
      if (cVar1 == '\0') {
        while (iVar3 = iVar3 + 1, iVar3 < param_3) {
          *pcVar4 = '\0';
          pcVar4 = pcVar4 + 1;
        }
        return param_1;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < param_3);
  }
  return pcVar2;
}

