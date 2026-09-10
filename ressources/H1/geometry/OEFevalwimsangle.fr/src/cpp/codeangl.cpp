target=oefcodeangl1 oefcodeangl2 oefcodeangl3 oefcodeangl4 oefcodeangl5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_oefcodeangl1
\text{nat=\(\widehat{DBC}),\(\widehat{DAC}),
\(\widehat{ACD}),\(\widehat{DCB}),
\(\widehat{ACB})}

\text{ch=shuffle(5)}
\integer{a1=position(3,\ch)}
\integer{a2=position(4,\ch)}
\text{nat=\nat[\ch[1]],\nat[\ch[2]],\nat[\ch[3]],\nat[\ch[4]],\nat[\ch[5]]}
\text{angle=angle1}
#endif
#if defined TARGET_oefcodeangl2
\text{nat1=\(\widehat{ABC}), \(\widehat{BED}),
\(\widehat{EDB}), \(\widehat{BAC}),
\(\widehat{ACB}), \(\widehat{DFE})}

\text{nat2=\(\widehat{ABC}),\(\widehat{ACB}),
\(\widehat{DFE}),\(\widehat{FEC}),
\(\widehat{DEF}),\(\widehat{EFC})}

\text{ch1=shuffle(6)}
\integer{a1=position(1,\ch1)}
\integer{a2=position(2,\ch1)}
\integer{a3=position(3,\ch1)}
\text{nat1=\nat1[\ch1[1]],\nat1[\ch1[2]],\nat1[\ch1[3]],\nat1[\ch1[4]],\nat1[\ch1[5]],\nat1[\ch1[6]]}

\text{ch2=shuffle(6)}
\integer{a4=position(3,\ch2)}
\integer{a5=position(4,\ch2)}
\text{nat2=\nat2[\ch2[1]],\nat2[\ch2[2]],\nat2[\ch2[3]],\nat2[\ch2[4]],\nat2[\ch2[5]],\nat2[\ch2[6]]}
\text{angle=angle3}
#endif
#if defined TARGET_oefcodeangl3
\text{nat1=\(\widehat{BAC}), \(\widehat{AGE}), \(\widehat{BED}), \(\widehat{EBC})}

\text{nat2=\(\widehat{EDB}), \(\widehat{CGD}),
 \(\widehat{ACD}), \(\widehat{ABD})}
\text{angle=angle7}
#endif
#if defined TARGET_oefcodeangl4
\text{rep=2,1}
\text{a=shuffle(2)}
\text{angle=angle4}
#endif
#if defined TARGET_oefcodeangl5
\integer{ang1=randint(10..50)}
\integer{ang2=randint(\ang1+1..85)}
\integer{ang3=90-\ang1}
\integer{ang4=90+\ang1}

\text{nat=\(\widehat{CDG}), \(\widehat{ABC}),
 \(\widehat{GCD}), \(\widehat{GJK}),
 \(\widehat{DGM})}

\text{ch=randint(1..5)}
\text{reps=\ang1,\ang2,\ang3,\ang4,90}
\integer{rep=\reps[\ch]}
\text{angle=angle5b}
#endif
\text{fig=<img src="\imagedir/\angle.jpg" alt="">}

#if defined TARGET_oefcodeangl1 || defined TARGET_oefcodeangl2 || defined TARGET_oefcodeangl3 || defined TARGET_oefcodeangl4 || defined TARGET_oefcodeangl5
\statement{
<div class="wims_columns">
 <div class="medium_size img_col">\fig</div>
<div class="medium_size text_col">
# if defined TARGET_oefcodeangl1
\name_enonce :
\embed{r1}
</div></div>}

\answer{}{\a1,\a2;\nat}{type=mark}
# endif
# if defined TARGET_oefcodeangl2
<ul><li>
\name_enonce[1]:
\embed{r1}
</li><li>
\name_enonce[2]:
\embed{r2}
</li></ul>
</div></div>}
\answer{}{\a1,\a2,\a3;\nat1}{type=mark}
\answer{}{\a4,\a5;\nat2}{type=mark}
# endif
# if defined TARGET_oefcodeangl3
\name_enonce:
<div class="wimscenter">\embed{r1,40x140}</div>
</div></div>
}
\answer{}{\nat2;\nat1}{type=correspond}
# endif
# if defined TARGET_oefcodeangl4
<ul><li>\enonc[\a[1]] : \embed{r1}</li><li>
\enonc[\a[2]] : \embed{r2}</li></ul>
</div></div>
}

\answer{}{\rep[\a[1]];\reps}{type=menu}
\answer{}{\rep[\a[2]];\reps}{type=menu}
# endif
# if defined TARGET_oefcodeangl5
\name_enonce[1]
<ul><li>
\(\widehat{GHJ}) = \ang1 °
</li><li>\(\widehat{FBL}) = \ang2 °
</li><li>\(\widehat{GJH}) = \ang3 °
</li><li>\(\widehat{BCG}) = \ang4 °
</li></ul>
\name_enonce[2] \nat[\ch] :
<div class="wimscenter"><label for="reply1"> \nat[\ch] =</label> \embed{r1,3} °</div>
</div></div>
}
\answer{}{\rep}{type=raw}
# endif
#endif
