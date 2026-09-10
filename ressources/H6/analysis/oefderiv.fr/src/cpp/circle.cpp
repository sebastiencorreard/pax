target=circle circle2 circle3 circle4
\language{fr}
\range{-5..5}
#include "xiao.inc"
#if defined TARGET_circle
# define NUM I
#endif
#if defined TARGET_circle2
# define NUM II
#endif
#if defined TARGET_circle3
# define NUM III
#endif
#if defined TARGET_circle4
# define NUM IV
#endif

\computeanswer{yes}
\format{html}
\precision{10000}
#include "lang_titles.inc"
#include "lang.inc"

#if defined TARGET_circle
\real{a=randint(20..100)/10}
\integer{r=random(10..30)}
\real{sol=2*pi*\r*\a}
#endif
#if defined TARGET_circle2
\real{a=randint(20..100)/10}
\integer{area=randint(10..40)}
\real{r=sqrt(\area/pi)}
\real{sol=2*pi*\r*\a}
#endif
#if defined TARGET_circle3 || defined TARGET_circle4
\real{a=randint(20..100)}
\real{r=randint(10..30)}
\real{area=pi*\r^2}
\real{sol=\a/sqrt(4*pi*\area)}
#endif
#if defined TARGET_circle
\text{var=\r,cm,\(cm^2\)/s}
#endif
#if defined TARGET_circle2
\text{var=\area, \(cm^2\),\(cm^2\)/s}
#endif
#if defined TARGET_circle3
\text{var=\area, \(cm^2\),cm/s}
#endif
#if defined TARGET_circle4
\text{var=\r,cm,cm/s}
#endif
\text{name_in=en}
\statement{\name_enonce[1] \a \name_enonce[2] \name_question[1]
  \var[1] \name_question[2], \name_question[3] (\name_in \var[3])?
}

\answer{\name_answer}{\sol}
