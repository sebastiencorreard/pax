!! fichier qui teste si un tableau est sous forme reduite.
lib_rep=yes
tmp=$wims_read_parm
val20=$tmp
tmp1=!rownum $tmp
!for i=1 to $tmp1
   tmp3=0
   tmp4=!rownum $tmp
   !for j=1 to $tmp4
      tmp5=!row $j of $tmp
      tmp6=!positionof item 0 in $tmp5
      tmp6=!itemcnt $tmp6
      !ifval $tmp6=$tmp4-1
         tmp3=$j
         !break
      !endif
   !next j
   !if $tmp3=0
      lib_rep=no
      !break
   !endif
   tmp7=!values v for v=1 to $tmp4
   tmp7=!listcomplement $tmp3 in $tmp7
   tmp=!row $tmp7 of $tmp
!next i
