target=ecrire1 ecrire2 ecrire3 ecrire4

#include "swac.inc"
#include "bpr.inc"
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_ecrire1 || defined TARGET_ecrire2
\text{mot=\confparm1}
\text{mot=randitem(\mot)}
\text{mot=wims(lookup \mot in swac_baseform_keys)}
\text{mot=randitem(\mot)}

\text{mot= \mot issametext or confparm1 isin \mot ? wims(randrecord verbes.keys)}
\text{audio=slib(lang/swac \mot,eng-balm-verbs)}
\text{Mot=\audio[2..-1]}
\text{audio=\audio[1;1]}
\text{text=wims(getopt swac_text in \Mot)}
\text{title=wims(getopt swac_title in \Mot)}
\text{baseform=wims(getopt swac_baseform in \Mot)}
\text{formname=wims(getopt swac_form_name in \Mot)}
\text{formname=wims(replace internal Simple Past by Preterite in \formname)}
\text{choix=Infinitive,Present Perfect,Preterite}
#endif
#if defined TARGET_ecrire1
\statement{
  \name_enonce[1] \audio .
<p>\name_enonce2[1]</p>
<div class="wimscenter">\embed{r1,20}</div>
<div>\name_enonce2[2]? \embed{r2,100 x 40}</div>
}

\answer{}{\text}{type=case}
\answer{}{\formname;\choix}{type=clickfill}
#endif
#if defined TARGET_ecrire2
infinitif : baseform
on cherche les trois formes (audio) dans swac_baseform_keys

\text{forms=wims(lookup \baseform in swac_baseform_keys)}
text{forms=shuffle(\forms)}
\for{i=1 to 3}{
 \text{audio=\forms[\i]}
 \text{audio=slib(lang/swac \audio,eng-balm-verbs)}
 \text{Mot=\audio[2..-1]}
 \text{audio=\audio[1;1]}
 \text{form=wims(getopt swac_form_name in \Mot)}
 \text{text=wims(getopt swac_text in \Mot)}
 \text{inf=\form issametext Infinitive?\text}
 \text{audioinf=\form issametext Infinitive?\audio}
 \text{audiopret=\form issametext Preterite?\audio}
 \text{audiopres=\form issametext Simple Past?\audio}
 \text{pret=\form issametext Simple Past?\text}
 \text{pres=\form issametext Present Perfect?\text}
}
\text{audio=\audioinf}
\text{f=randint(1..2)}
\text{temps=Preterite,Present Perfect}
\text{text=\pret,\pres}
\statement{<p>\name_enonce[1] \audio.</p>
<p>\name_enonce2[1] "\temps[\f]" (\name_enonce2[2]): </p>
<div class="wimscenter"> \embed{r1,20} </div>
}
\answer{}{\text[\f]}{type=case}
#endif

#if defined TARGET_ecrire3 || defined TARGET_ecrire4
infinitif : baseform
on cherche les trois formes (audio) dans

\text{mot=wims(randrecord listverbs)}
\text{forms=wims(lookup \mot in swac_baseform_keys)}
\text{f=shuffle(3)}
\text{audio=\forms[\f[1]]}
\text{audio=slib(lang/swac \audio,eng-balm-verbs)}
\text{Mot=\audio[2..-1]}
\text{audio=\audio[1;1]}
\text{choix=Preterite,Present Perfect,Infinitive}

\text{form2=\choix[\f[2]]}
\text{form3=\choix[\f[3]]}
\text{text2=\forms[\f[2]]}
\text{text3=\forms[\f[3]]}
#endif
#if defined TARGET_ecrire3
\statement{\name_enonce[1] \audio.
<p>\name_enonce2[1] "\form2" \if{\form2 issametext Infinitive}{(to + infinitif)}
{(\name_enonce2[2])}</p>
<div class="wimscenter"> \embed{r1,20} </div>
}

\answer{}{\text2}{type=case}
#endif
#if defined TARGET_ecrire4
\statement{<p>\name_enonce[1] \audio.</p>
<p>\name_enonce2:</p>
<table class="wimsborder wimscenter">
<tr><th>\form2</th><td>\embed{r1,20} </td></tr>
<tr><th>\form3</th><td>\embed{r2,20} </td></tr>
</table>
}

\answer{}{\text2}{type=case}
\answer{}{\text3}{type=case}

#endif
