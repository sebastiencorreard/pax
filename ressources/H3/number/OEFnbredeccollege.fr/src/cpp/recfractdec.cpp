target=oefrecfractdec1 oefrecfractdec2 oefrecfractdec3 oefrecfractdec4 oefrecfractdec5 oefrecfractdec6 oefrecfractdec7
#include "author.inc"
\langage{fr}
\format{html}
\precision{1000000}
#include "lang_titles.inc"
#include "lang.inc"
\integer{p=15}
\integer{xa=25}
\integer{ya=25}
\text{typ1=square}
\text{typ2=fsquare}
\text{col1=black}
\text{col2=red}

\text{quad=}
\for{j=0 to 9}{
   \for{i=0 to 9}{
      \integer{x=\xa+\i*\p}
      \integer{y=\ya+\j*\p}
     \text{c=\typ1 \x,\y,\p,\col1}
       \text{quad=\quad
     \c}}}

#if defined TARGET_oefrecfractdec1 || defined TARGET_oefrecfractdec3
\integer{nb1=randint(1..9)}
\integer{nb0=randint(1..9)}
\text{nb=0,\nb1\nb0}
#endif
#if defined TARGET_oefrecfractdec2
\integer{nb1=randint(1..9)}
\integer{nb0=0}
\text{nb=0,\nb1}
#endif
#if defined TARGET_oefrecfractdec4
\integer{nb0=randint(1..9)}
\integer{nb1=0}
\text{nb=0,\nb1\nb0}
#endif
#if defined TARGET_oefrecfractdec5 || defined TARGET_oefrecfractdec6
\integer{nb0=randint(1..9)}
\integer{nb1=randint(0..9)}
\text{nb=1,\nb1\nb0}
#endif
#if defined TARGET_oefrecfractdec7
\integer{nb0=0}
\integer{nb1=randint(1..9)}
\text{nb=1,\nb1}
#endif
\text{remp=}
\for{j=1 to \nb1}{
  \for{i=0 to 9}{
      \integer{x=\xa+\i*\p}
      \integer{y=\ya+(\j-1)*\p}
     \text{c=\typ2 \x,\y,\p,\col2}
       \text{remp=\remp
     \c}}}

\integer{j=\nb1}
  \for{i=1 to \nb0}{
      \integer{x=\xa+(\i-1)*\p}
      \integer{y=\ya+\j*\p}
     \text{c=\typ2 \x,\y,\p,\col2}
       \text{remp=\remp
     \c}}

\text{carre=draw(200,200
linewidth 2
\remp
\quad
)}

#if defined TARGET_oefrecfractdec5 || defined TARGET_oefrecfractdec6 || defined TARGET_oefrecfractdec7
\text{carre1=draw(200,200
linewidth 2
fsquare 25,25,150,red
\quad)}
#endif

\statement{
<div class="wims_columns">
 <div class="medium_size img_col">
#if defined TARGET_oefrecfractdec5 || defined TARGET_oefrecfractdec6 || defined TARGET_oefrecfractdec7
<img src="\carre1" alt="">
#endif
<img src="\carre" alt=""><br>
\name_comment
</div><div class="medium_size txt_col">
\name_statement[1] :
<ul><li>
\name_stat
#if defined TARGET_oefrecfractdec1 || TARGET_oefrecfractdec2 || TARGET_oefrecfractdec4
\special{mathmlinput [\frac{reply1}{reply2}],3
reply1
reply2
}
#endif
#if defined TARGET_oefrecfractdec3
\special{mathmlinput [\frac{reply1}{10} + \frac{reply2}{100}],3
reply1
reply2}
#endif
#if defined TARGET_oefrecfractdec5
\special{mathmlinput [\frac{reply1}{100}],3
reply1
}
#endif
#if defined TARGET_oefrecfractdec6
\special{mathmlinput [reply1 + \frac{reply2}{10} + \frac{reply3}{100}],3
reply1
reply2
reply3}
#endif
#if defined TARGET_oefrecfractdec7
\special{mathmlinput [\frac{reply1}{10}], 3
reply1}
#endif
#if defined TARGET_oefrecfractdec1 || defined TARGET_oefrecfractdec2 || defined TARGET_oefrecfractdec4
<div class="wims_instruction">\name_statement[2]</div>
#endif
</li><li>
#if defined TARGET_oefrecfractdec1 || TARGET_oefrecfractdec2 || TARGET_oefrecfractdec3 || TARGET_oefrecfractdec4
\name_statement[3]: \embed{r3,5}
#endif
#if defined TARGET_oefrecfractdec5 || defined TARGET_oefrecfractdec7
\name_statement[3]: \embed{r2,5}
#endif
#if defined TARGET_oefrecfractdec6
\name_statement[3]: \embed{r4,5}
#endif
<div class="wims_instruction">
\name_inst
</div>
</li></ul>
</div></div>
}
#if defined TARGET_oefrecfractdec1
\answer{}{\nb1\nb0}{type=text}
\answer{}{100}{type=text}
\answer{}{\nb}{type=text}
#endif
#if defined TARGET_oefrecfractdec2
\answer{}{\nb1}{type=text}
\answer{}{10}{type=text}
\answer{}{\nb}{type=text}
#endif
#if defined TARGET_oefrecfractdec3
\answer{}{\nb1}{type=text}
\answer{}{\nb0}{type=text}
\answer{}{\nb}{type=text}
#endif
#if defined TARGET_oefrecfractdec4
\answer{}{\nb0}{type=text}
\answer{}{100}{type=text}
\answer{}{\nb}{type=text}
#endif
#if defined TARGET_oefrecfractdec5
\answer{}{1\nb1\nb0}{type=text}
\answer{}{\nb}{type=text}
#endif
#if defined TARGET_oefrecfractdec6
\answer{}{1}{type=text}
\answer{}{\nb1}{type=text}
\answer{}{\nb0}{type=text}
\answer{}{\nb}{type=text}
#endif
#if defined TARGET_oefrecfractdec7
\answer{}{1\nb1}{type=text}
\answer{}{\nb}{type=text}
#endif

