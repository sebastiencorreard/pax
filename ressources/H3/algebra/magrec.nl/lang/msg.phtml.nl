!! This file contains error messages. It will be processed
!! whenever the variable `error' is not empty.

<b>Fout.</b>

!if bad_sum=$error
Verkeerde berekening: de rijen of kolommen waarvan de 
 !if $kind=sum
  som
 !else
  product
 !endif
 niet oevereenkiomen zijn rood gekleurd
 Verbeter je fout, en probeer het nog een keertje.
 !exit
!endif

!if $error=double_number
 Het getal $e komt meerdere keren voor: verbeteren dus.

 !exit
!endif

!msg $error

