target=listdiv1 listdiv2 listdiv3 listdiv4 listdiv5
\range{-5..5}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\precision{10000}

#if defined TARGET_listdiv1
 \text{lt=shuffle(0,0,0,0,0,1)}
#endif

#if defined TARGET_listdiv2
 \text{lt=shuffle(0,0,0,0,1,1)}
#endif

#if defined TARGET_listdiv3
 \text{lt=shuffle(0,0,0,0,2,0)}
#endif

#if defined TARGET_listdiv4
 \text{lt=shuffle(0,0,0,1,1,1)}
#endif

#if defined TARGET_listdiv5
 \text{lt=shuffle(0,0,0,2,2,0)}
#endif

\integer{a1=item(1,\lt)}
\integer{a2=item(2,\lt)}
\integer{a3=item(3,\lt)}
\integer{a4=item(4,\lt)}
\integer{a5=item(5,\lt)}
\integer{a6=item(6,\lt)}
\integer{nombre=2^\a1*3^\a2*5^\a3*7^\a4*11^\a5*13^\a6}
\text{liste=}
\for{i1=0 to \a1}{
 \for{i2=0 to \a2}{
  \for{i3=0 to \a3}{
   \for{i4=0 to \a4}{
    \for{i5=0 to \a5}{
     \for{i6=0 to \a6}{
       \integer{nb=2^\i1*3^\i2*5^\i3*7^\i4*11^\i5*13^\i6}
        \text{liste=wims(append item \nb to \liste)}
     }
    }
   }
  }
 }
}
\statement{
  \name_question \nombre.
<br class="spacer">

<b>\name_answer:</b>
  <label for="reply1">\name_question1[1] \nombre \name_question1[2]</label> \embed{r1}.
<div class="wims_instruction">
 \name_instruction
 </div>
}

\answer{liste}{\liste}{type=set}
