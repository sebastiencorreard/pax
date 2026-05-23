!! This file contains error messages. It will be processed
!! whenever the variable `error' is not empty.

<b>$wims_name_Error</b>

!if bound_integer=$error
  The given numbers are not integers between 1 and $[$cols*$rows].
  Please correct the error and try again.
  !exit
!endif
!if bad_sum=$error
  Verkeerde berekening: de rijen of kolommen waarvan de
  $(n_$kind)
  niet oevereenkiomen zijn rood gekleurd
  Verbeter je fout, en probeer het nog een keertje.
  !exit
!endif
!if $error=double_number
  Het getal $e komt meerdere keren voor: verbeteren dus.
  !exit
!endif

!msg $error
