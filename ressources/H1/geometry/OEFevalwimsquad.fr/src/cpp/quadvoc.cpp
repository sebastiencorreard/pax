target=oefquadvoc1 oefquadvoc2 oefquadvoc3 oefquadvoc4 oefquadvoc5
\format{html}
\precision{100000}
\langage{fr}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_oefquadvoc1 || defined TARGET_oefquadvoc2
\text{fig=<img src="\imagedir/quad01b.jpg" alt="">,<img src="\imagedir/quad02b.jpg" alt="">,<img src="\imagedir/quad03b.jpg" alt="">,<img src="\imagedir/quad04b.jpg" alt="">,
<img src="\imagedir/quad05b.jpg" alt="">,<img src="\imagedir/quad06b.jpg" alt="">,<img src="\imagedir/quad07b.jpg" alt="">,<img src="\imagedir/quad08b.jpg" alt="">,
<img src="\imagedir/quad09b.jpg" alt="">,<img src="\imagedir/quad11b.jpg" alt="">,<img src="\imagedir/quad12b.jpg" alt="">,
<img src="\imagedir/quad14b.jpg" alt="">,<img src="\imagedir/quad16b.jpg" alt="">,
<img src="\imagedir/quad17b.jpg" alt="">,<img src="\imagedir/quad18b.jpg" alt="">,<img src="\imagedir/quad19b.jpg" alt="">,<img src="\imagedir/quad20b.jpg" alt="">}
#endif
#if defined TARGET_oefquadvoc3
\text{fig=<img src="\imagedir/quad01b.jpg" alt="">,<img src="\imagedir/quad02b.jpg" alt="">,<img src="\imagedir/quad08b.jpg" alt="">,<img src="\imagedir/quad04b.jpg" alt="">,
<img src="\imagedir/quad05b.jpg" alt="">,<img src="\imagedir/quad06b.jpg" alt="">,<img src="\imagedir/quad07b.jpg" alt="">,<img src="\imagedir/quad08b.jpg" alt="">,
<img src="\imagedir/quad09b.jpg" alt="">,<img src="\imagedir/quad12b.jpg" alt="">,
<img src="\imagedir/quad14b.jpg" alt="">,<img src="\imagedir/quad16b.jpg" alt="">,
<img src="\imagedir/quad17b.jpg" alt="">,<img src="\imagedir/quad19b.jpg" alt="">,<img src="\imagedir/quad20b.jpg" alt="">}
#endif
#if defined TARGET_oefquadvoc1
\integer{ch=randint(1..17)}
#endif
#if defined TARGET_oefquadvoc2
\text{ch=shuffle(17)}
#endif
#if defined TARGET_oefquadvoc3
\text{ch=randint(1..15)}
#endif
#if defined TARGET_oefquadvoc1 || defined TARGET_oefquadvoc2
\text{reps=2,3,2,4,5,3,2,2,4,1,2,5,5,5,1,6,6}
#endif
#if defined TARGET_oefquadvoc3
\text{reps=2,3,2,4,5,3,2,2,4,2,5,5,5,6,6}
#endif
#if defined TARGET_oefquadvoc4
\text{fig=<img src="\imagedir/triangcomplex2b.jpg" alt="">}
\text{nm=BDGC,BDEC,BDCE,DFHG,HGDF,FDGH,IKHF,KIFH,FKIH,DEG,ABCED,KHJ}
\text{reps=1,3,1,2,2,2,4,4,1,1,1,1}
\integer{ch=randint(1..12)}
\integer{rep=\reps[\ch]}
#endif
#if defined TARGET_oefquadvoc5
\text{fig=<img src="\imagedir/triangcomplex2b.jpg" alt="">}
\text{nm=DFHG|FHGD|HGDF|GDFH|GHFD|DGHF|FDGH|HFDG,
BDEC|DECB|ECBD|CBDE|BCED|CEDB|EDBC|DBCE,
IKHF|KHFI|HFIK|FIKH|IFHK|FHKI|HKIF|KIFH}
\integer{ch=randint(1..3)}
\text{rep=\nm[\ch]}
#endif
\statement{
#if defined TARGET_oefquadvoc1 || defined TARGET_oefquadvoc3 || defined TARGET_oefquadvoc4 || defined TARGET_oefquadvoc5
<div class="wims_columns">
 <div class="medium_size img_col">
#if defined TARGET_oefquadvoc1 || defined TARGET_oefquadvoc3
\fig[\ch]
#endif
#if defined TARGET_oefquadvoc4 || defined TARGET_oefquadvoc5
\fig
#endif
#endif
</div>
 <div class="medium_size text_col">
#if defined TARGET_oefquadvoc1
\name_question[1] \name_question[2]:
#endif
#if defined TARGET_oefquadvoc4
\name_question[1] \nm[\ch] \name_question[2]:
#endif
#if defined TARGET_oefquadvoc3
<label for="reply1">\name_question</label>
#endif
#if defined TARGET_oefquadvoc5
<label for="reply1">\name_question\nat[\ch] :</label>
#endif
#if defined TARGET_oefquadvoc1 || defined TARGET_oefquadvoc3 || defined TARGET_oefquadvoc4 || defined TARGET_oefquadvoc5
\embed{r1}.
</div></div>
#endif
#if defined TARGET_oefquadvoc2
  <table class="wimsborder wimscenter"><tr>
<td>\fig[\ch[1]]</td>
<td>\fig[\ch[2]]</td>
<td>\fig[\ch[3]]</td></tr>
<tr><td>\embed{r1,150x40}</td>
<td>\embed{r2}</td>
<td>\embed{r3}</td></tr>
</table>
#endif
}
#if defined TARGET_oefquadvoc1
\answer{}{\reps[\ch];\nat}{type=radio}
#endif
#if defined TARGET_oefquadvoc2
\answer{}{\nat[\reps[\ch[1]]];\nat}{type=clickfill}
\answer{}{\nat[\reps[\ch[2]]];\nat}{type=clickfill}
\answer{}{\nat[\reps[\ch[3]]];\nat}{type=clickfill}
#endif
#if defined TARGET_oefquadvoc3
\answer{}{\nat[\reps[\ch]]}{type=atext}
#endif
#if defined TARGET_oefquadvoc4
\answer{}{\rep;\nat}{type=radio}
#endif
#if defined TARGET_oefquadvoc5
\answer{}{\rep}{type=case}
#endif
