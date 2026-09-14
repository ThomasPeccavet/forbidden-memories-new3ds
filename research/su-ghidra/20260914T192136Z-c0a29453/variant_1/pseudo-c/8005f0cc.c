/* Analysis pseudo-C, not buildable source. */

code * FUN_8005f0cc(uint param_1)

{
  uint uVar1;
  
  uVar1 = param_1 & 0xffff0000;
  if (uVar1 == 0x100000) {
    param_1 = param_1 & 0xffff;
    if (param_1 == 0x15) {
      return (code *)&LAB_80061044;
    }
    if (param_1 < 0x16) {
      if (param_1 == 0xd) {
        return (code *)&LAB_80060b04;
      }
      if (param_1 < 0xe) {
        if (param_1 == 9) {
          return (code *)&LAB_800608bc;
        }
      }
      else if (param_1 == 0x11) {
        return (code *)&LAB_80060db4;
      }
    }
    else {
      if (param_1 == 0x20d) {
        return (code *)&LAB_800615f0;
      }
      if (param_1 < 0x20e) {
        if (param_1 == 0x209) {
          return (code *)&LAB_80061388;
        }
      }
      else {
        if (param_1 == 0x211) {
          return (code *)&LAB_800618c0;
        }
        if (param_1 == 0x215) {
          return (code *)&LAB_80061b70;
        }
      }
    }
  }
  else if (uVar1 < 0x100001) {
    if (uVar1 == 0) {
      param_1 = param_1 & 0xffff;
      if (param_1 == 0x15) {
        return FUN_8004d260;
      }
      if (param_1 < 0x16) {
        if (param_1 == 9) {
          return (code *)&LAB_8005f820;
        }
        if (param_1 < 10) {
          if (param_1 == 0) goto LAB_8005f51c;
        }
        else {
          if (param_1 == 0xd) {
            return FUN_8004cf9c;
          }
          if (param_1 == 0x11) {
            return (code *)&LAB_8005fa7c;
          }
        }
      }
      else {
        if (param_1 == 0x20d) {
          return (code *)&LAB_8005ff9c;
        }
        if (param_1 < 0x20e) {
          if (param_1 == 0x209) {
            return (code *)&LAB_8005fd20;
          }
        }
        else {
          if (param_1 == 0x211) {
            return (code *)&LAB_80060280;
          }
          if (param_1 == 0x215) {
            return (code *)&LAB_80060544;
          }
        }
      }
    }
    else if (uVar1 == 0x20000) {
      if ((param_1 & 0xffff) == 0xd) {
        return (code *)&LAB_800342b0;
      }
      if ((param_1 & 0xffff) == 0x15) {
        return FUN_80034d30;
      }
    }
  }
  else if (uVar1 == 0x200000) {
    param_1 = param_1 & 0xffff;
    if (param_1 == 0x15) {
      return (code *)&LAB_800627ac;
    }
    if (param_1 < 0x16) {
      if (param_1 == 0xd) {
        return (code *)&LAB_8006218c;
      }
      if (param_1 < 0xe) {
        if (param_1 == 9) {
          return (code *)&LAB_80061ed4;
        }
      }
      else if (param_1 == 0x11) {
        return (code *)&LAB_800624ac;
      }
    }
    else {
      if (param_1 == 0x20d) {
        return (code *)&LAB_80062e38;
      }
      if (param_1 < 0x20e) {
        if (param_1 == 0x209) {
          return (code *)&LAB_80062b60;
        }
      }
      else {
        if (param_1 == 0x211) {
          return (code *)&LAB_80063178;
        }
        if (param_1 == 0x215) {
          return (code *)&LAB_80063498;
        }
      }
    }
  }
  else if (uVar1 == 0x300000) {
    param_1 = param_1 & 0xffff;
    if (param_1 == 0x15) {
      return (code *)&LAB_80064108;
    }
    if (param_1 < 0x16) {
      if (param_1 == 0xd) {
        return (code *)&LAB_80063b10;
      }
      if (param_1 < 0xe) {
        if (param_1 == 9) {
          return (code *)&LAB_8006386c;
        }
      }
      else if (param_1 == 0x11) {
        return (code *)&LAB_80063e1c;
      }
    }
    else {
      if (param_1 == 0x20d) {
        return (code *)&LAB_8006476c;
      }
      if (param_1 < 0x20e) {
        if (param_1 == 0x209) {
          return (code *)&LAB_800644a8;
        }
      }
      else {
        if (param_1 == 0x211) {
          return (code *)&LAB_80064a98;
        }
        if (param_1 == 0x215) {
          return (code *)&LAB_80064da4;
        }
      }
    }
  }
  FUN_8008fa78(s_unsupported_POLYGON_primitive_0x_800117ac);
LAB_8005f51c:
  return (code *)&LAB_80089da8;
}

