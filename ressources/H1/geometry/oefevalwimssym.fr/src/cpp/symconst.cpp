target=oefsymconst1 oefsymconst2 oefsymconst3 oefsymconst4 oefsymconst5
#include "author.inc"
#include "lang.inc"
\precision{1000}
\keywords{symmetry}
\text{geom=draw(300,300
segment 0,300,300,0,red
segment 75,215,85,225,black
segment 75,225,85,215,black
segment 70,105,80,95,black
segment 70,95,80,105,black
segment 255,45,245,55,black
segment 255,55,245,45,black
text black,60,100,medium,C
text black,85,225,medium,B
text black,255,55,medium,A
)}
#if defined TARGET_oefsymconst1
# define NUM 1
\text{mot1=shuffle(\name_mot)}
\text{rep1=position(\name_mot[1],\mot1)}
\text{mot2=(AB),(AC),(BC)}
\text{mot2=shuffle(\mot2)}
\text{rep2=position((AB),\mot2)}
\text{mot3=C,A,B}
\text{mot3=shuffle(\mot3)}
\text{rep3=position(C,\mot3)}
\text{mot4=[MC],[MA],[MB]}
\text{mot4=shuffle(\mot4)}
\text{rep4=position([MC],\mot4)}
\text{mot5=[CC'],[BC'],[AC']}
\text{mot5=shuffle(\mot5)}
\text{rep5=position([CC'],\mot5)}
#endif
#if defined TARGET_oefsymconst2
# define NUM 2
\text{mot1=shuffle(\name_mot1)}
\text{rep1=position(\name_mot1[1],\mot1)}
\text{mot2=shuffle(\name_mot2)}
\text{rep2=position(\name_mot2[1],\mot2)}
\text{mot3=shuffle(\name_mot3)}
\text{rep3=position(\name_mot3[3],\mot3)}
\text{mot4=shuffle(\name_mot4)}
\text{rep4=position(\name_mot4[1],\mot4)}
\text{mot5=shuffle(\name_mot5)}
\text{rep5=position(\name_mot5[1],\mot5)}
#endif
#if defined TARGET_oefsymconst3
# define NUM 3
\text{mot1=shuffle(\name_mot)}
\text{rep1=position(\name_mot[1],\mot1)}
\text{mot2=(AB),(AC),(BC)}
\text{mot2=shuffle(\mot2)}
\text{rep2=position((AB),\mot2)}
\text{mot3=C,A,B}
\text{mot3=shuffle(\mot3)}
\text{rep3=position(C,\mot3)}
\text{mot4=A,B,C,M}
\text{mot4=shuffle(\mot4)}
\text{rep4=position(M,\mot4)}
\text{mot5=A,B,C,M}
\text{mot5=shuffle(\mot5)}
\text{rep5=position(C,\mot5)}
#endif
#if defined TARGET_oefsymconst4
# define NUM 4
\text{mot1=shuffle(\name_mot1)}
\text{rep1=position(\name_mot1[1],\mot1)}
\text{mot2=shuffle(\name_mot2)}
\text{rep2=position(\name_mot2[1],\mot2)}
\text{mot3=shuffle(\name_mot1)}
\text{rep3=position(\name_mot1[2],\mot3)}
\text{mot4=shuffle(\name_mot4)}
\text{rep4=position(\name_mot4[1],\mot4)}
\text{mot5=shuffle(\name_mot5)}
\text{rep5=position(\name_mot5[1],\mot5)}
#endif
#if defined TARGET_oefsymconst5
# define NUM 5
\text{mot1=shuffle(\name_mot)}
\text{rep1=position(\name_mot[1],\mot1)}
\text{mot2=A,B,C}
\text{mot2=shuffle(\mot2)}
\text{rep2=position(C,\mot2)}
\text{mot3=C,A,B}
\text{mot3=shuffle(\mot3)}
\text{rep3=position(B,\mot3)}
\text{mot4=A,B,C}
\text{mot4=shuffle(\mot4)}
\text{rep4=position(C,\mot4)}
\text{mot5=A,B,C,C'}
\text{mot5=shuffle(\mot5)}
\text{rep5=position(C',\mot5)}
#endif
#include "lang_titles.inc"
\statement{
<div class="wims_columns">
  <div class="medium_size">
    <img src="\geom" alt="">
  </div>
  <div class="medium_size">
  \enonce
  <p>\enonc0:</p>
  <label for="reply1">\enonc1</label> \embed{r1}
  <label for="reply2">\enonc2</label> \embed{r2}
  <label for="reply3">\enonc3</label> \embed{r3}
  <label for="reply4">\enonc4</label> \embed{r4}
  <label for="reply5">\enonc5</label> \embed{r5}
  \enonc6.
  </div>
</div>
}

\answer{}{\rep1;\mot1[1],\mot1[2],\mot1[3],\mot1[4]}{type=menu}
\answer{}{\rep2;\mot2[1],\mot2[2],\mot2[3],\mot2[4]}{type=menu}
\answer{}{\rep3;\mot3[1],\mot3[2],\mot3[3],\mot3[4]}{type=menu}
\answer{}{\rep4;\mot4[1],\mot4[2],\mot4[3],\mot4[4]}{type=menu}
\answer{}{\rep5;\mot5[1],\mot5[2],\mot5[3],\mot5[4]}{type=menu}

\feedback{1=0}{\name_youranswer : \enonc1 \reply1 \enonc2 \reply2
\enonc3 \reply3 \enonc4 \reply4 \enonc5 \reply5 \enonc6}
