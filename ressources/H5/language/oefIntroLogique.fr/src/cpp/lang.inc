#include "lang_fr.inc"
\if{\lang=it}{
#include "lang_it.inc"
}

\if{\confparm1=2}{
\text{ou=\vee}
\text{et=\wedge}
\text{not=\neg}
}{
\text{ou=\;\;\mathrm{\name_ou}\;\;}
\text{et=\;\;\mathrm{\name_et}\;\;}
\text{not=\overline}
}
