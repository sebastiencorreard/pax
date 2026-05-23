target=rangfrac1 rangfrac2 rangfrac3 rangfrac4 rangfrac5

\language{fr}
\range{-5..5}
\author{Fabrice, Guerimand}
\email{fguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{100}
\text{size=40x50x1}

#if defined TARGET_rangfrac1
 \title{Ranger des nombres B1}
 \integer{a=randint(2..9)}
 \integer{b=randint(21..29)}
 \integer{c=randint(31..49)}
 \integer{d=randint(51..69)}
 \integer{e=randint(71..99)}
 \text{ltrep=\(\frac{\a}{\e}),\(\frac{\a}{\d}),\(\frac{\a}{\c}),\(\frac{\a}{\b})}
#endif

#if defined TARGET_rangfrac2
 \title{Ranger des nombres B2}
 \integer{a=randint(2..9)}
 \integer{b=randint(21..29)}
 \integer{c=randint(31..49)}
 \integer{d=randint(51..69)}
 \integer{e=randint(71..99)}
 \text{ltrep=\(\frac{\b}{\a}),\(\frac{\c}{\a}),\(\frac{\d}{\a}),\(\frac{\e}{\a})}
#endif

#if defined TARGET_rangfrac3
 \title{Ranger des nombres B3}
 \integer{b=randint(21..29)}
 \integer{c=randint(31..49)}
 \integer{d=randint(51..69)}
 \integer{e=randint(71..99)}
 \text{ltrep=\(-\frac{1}{\b}),\(-\frac{1}{\c}),\(-\frac{1}{\d}),\(-\frac{1}{\e})}
#endif

#if defined TARGET_rangfrac4
 \title{Ranger des nombres B4}
 \integer{a=randint(2..9)}
 \integer{b=randint(21..29)}
 \integer{c=randint(31..49)}
 \integer{d=randint(51..69)}
 \integer{e=randint(71..99)}
 \text{ltrep=\(-\frac{\a}{\b}),\(-\frac{\a}{\c}),\(\frac{\a}{\e}),\(\frac{\a}{\d})}
#endif

#if defined TARGET_rangfrac5
 \title{Ranger des nombres B5}
 \integer{a=randint(11..49)}
 \integer{b=randint(51..99)}
 \integer{c=randint(11..49)}
 \integer{d=randint(51..99)}
 \integer{e=randint(11..49)}
 \integer{f=randint(51..99)}
 \integer{g=randint(11..49)}
 \integer{h=randint(51..99)}
 \text{ltrep=\(-\frac{\b}{\a}),\(-\frac{\c}{\d}),\(\frac{\e}{\f}),\(\frac{\h}{\g})}
#endif

\integer{ch=randint(1..2)}
\text{sign=item(\ch,<,>)}
\text{sens=item(\ch,croissant,décroissant)}
\text{ltrep=\ch=2?\ltrep[4],\ltrep[3],\ltrep[2],\ltrep[1]}

\statement{
Ranger les nombres suivants dans l'ordre \sens.
<table class="wimscenter"><tr>
 <td>\embed{r1,\size}</td>
 <td>\sign</td>
 <td>\embed{r2,\size}</td>
 <td>\sign</td>
 <td>\embed{r3,\size}</td>
 <td>\sign</td>
 <td>\embed{r4,\size}</td>
 </tr></table>}

\answer{Premier champ}{\rep1;\ltrep}{type=dragfill}
\answer{Deuxième champ}{\rep2}{type=dragfill}
\answer{Troisième champ}{\rep3}{type=dragfill}
\answer{Quatrième champ}{\rep4}{type=dragfill}

\condition{Ordre correct}{(\rep1 isin \ltrep[1] and \rep2 isin \ltrep[2]) and (\rep3 isin \ltrep[3] and \rep4 isin \ltrep[4])}
