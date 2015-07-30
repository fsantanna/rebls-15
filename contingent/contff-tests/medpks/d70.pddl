(define (domain medicalPKS70)
 (:predicates 
 (dead)
    (stain ?i - STAIN) 
               (ill ?i - ILLNESS)
 
  )
 
(:action inspect-stain
   :parameters (?i - STAIN)
   :precondition (not (dead))
   :observe (stain ?i))
(:action medicate
  :parameters (?i - ILLNESS)
  :precondition (and (not (dead)) (not (ill i0)))
  :effect (and (when (ill ?i) (ill i0))
               (when (not (ill ?i)) (dead))))
(:action stain
                   :parameters ()
                   :precondition (not (dead))
                   :effect (and (when (ill i1) (stain s1))
 (when (ill i2) (stain s2))
 (when (ill i3) (stain s3))
 (when (ill i4) (stain s4))
 (when (ill i5) (stain s5))
 (when (ill i6) (stain s6))
 (when (ill i7) (stain s7))
 (when (ill i8) (stain s8))
 (when (ill i9) (stain s9))
 (when (ill i10) (stain s10))
 (when (ill i11) (stain s11))
 (when (ill i12) (stain s12))
 (when (ill i13) (stain s13))
 (when (ill i14) (stain s14))
 (when (ill i15) (stain s15))
 (when (ill i16) (stain s16))
 (when (ill i17) (stain s17))
 (when (ill i18) (stain s18))
 (when (ill i19) (stain s19))
 (when (ill i20) (stain s20))
 (when (ill i21) (stain s21))
 (when (ill i22) (stain s22))
 (when (ill i23) (stain s23))
 (when (ill i24) (stain s24))
 (when (ill i25) (stain s25))
 (when (ill i26) (stain s26))
 (when (ill i27) (stain s27))
 (when (ill i28) (stain s28))
 (when (ill i29) (stain s29))
 (when (ill i30) (stain s30))
 (when (ill i31) (stain s31))
 (when (ill i32) (stain s32))
 (when (ill i33) (stain s33))
 (when (ill i34) (stain s34))
 (when (ill i35) (stain s35))
 (when (ill i36) (stain s36))
 (when (ill i37) (stain s37))
 (when (ill i38) (stain s38))
 (when (ill i39) (stain s39))
 (when (ill i40) (stain s40))
 (when (ill i41) (stain s41))
 (when (ill i42) (stain s42))
 (when (ill i43) (stain s43))
 (when (ill i44) (stain s44))
 (when (ill i45) (stain s45))
 (when (ill i46) (stain s46))
 (when (ill i47) (stain s47))
 (when (ill i48) (stain s48))
 (when (ill i49) (stain s49))
 (when (ill i50) (stain s50))
 (when (ill i51) (stain s51))
 (when (ill i52) (stain s52))
 (when (ill i53) (stain s53))
 (when (ill i54) (stain s54))
 (when (ill i55) (stain s55))
 (when (ill i56) (stain s56))
 (when (ill i57) (stain s57))
 (when (ill i58) (stain s58))
 (when (ill i59) (stain s59))
 (when (ill i60) (stain s60))
 (when (ill i61) (stain s61))
 (when (ill i62) (stain s62))
 (when (ill i63) (stain s63))
 (when (ill i64) (stain s64))
 (when (ill i65) (stain s65))
 (when (ill i66) (stain s66))
 (when (ill i67) (stain s67))
 (when (ill i68) (stain s68))
 (when (ill i69) (stain s69))
 (when (ill i70) (stain s70))
))
)
