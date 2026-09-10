target=oefmachop1 oefmachop2 oefmachop3 oefmachop4 oefmachop5
#include "author.inc"
\precision(1000000)

#if defined TARGET_oefmachop1
#define NUM 1
\integer{nb1=randint(110..990)}
\integer{nb2=randint(1111000..9999000)}
\integer{nb3=randint(11..9900000)}
\text{nb=shuffle(\nb1,\nb2,\nb3)}
\integer{res=\nb[1] + \nb[2] + \nb[3]}
\text{nb1=slib(numeration/ecriturenombre \nb[1])}
\text{nb2=slib(numeration/ecriturenombre \nb[2])}
\text{nb3=slib(numeration/ecriturenombre \nb[3])}
\text{enonc=\nb1 + \nb2 + \nb3 =}
\integer{l=10}
#endif

#if defined TARGET_oefmachop2
#define NUM 2
\integer{nb1=randint(11000..990000)}
\integer{nb2=randint(1111000..9999000)}
\integer{nb3=randint(11..99000)}
\text{nb=shuffle(+ \nb2,- \nb3)}
\integer{res=\nb1 + \nb2 - \nb3}
\text{nb1=slib(numeration/ecriturenombre \nb1)}
\text{nb2=slib(numeration/ecriturenombre \nb[1])}
\text{nb3=slib(numeration/ecriturenombre \nb[2])}
\integer{l=10}
\text{enonc=\nb1 \nb2 \nb3 =}
#endif

#if defined TARGET_oefmachop3
#define NUM 3
\integer{nb1=randint(110..9900)}
\integer{nb2=randint(110..9999)}
\integer{res=\nb1 * \nb2}
\text{nb1=slib(numeration/ecriturenombre \nb1)}
\text{nb2=slib(numeration/ecriturenombre \nb2)}

\text{enonc=\nb1 \(\times) \nb2 =}
\integer{l=10}
#endif

#if defined TARGET_oefmachop4
#define NUM 4

\integer{e1=randint(0..5)}
\integer{e2=randint(1..5)}
\integer{nb1=randint(11..990)}
\integer{nb2=randint(11..999)}
\real{nb1=\nb1/10^\e1}
\real{nb2=\nb2/10^\e2}
\real{res=\nb1 * \nb2}
\text{nb1=slib(numeration/ecriturenombre \nb1)}
\text{nb2=slib(numeration/ecriturenombre \nb2)}
\text{nb1=wims(translate . to , in \nb1)}
\text{nb2=wims(translate . to , in \nb2)}
\text{enonc=\nb1 \(\times) \nb2 =}
\integer{l=10}
#endif

#if defined TARGET_oefmachop5
#define NUM 5

\integer{e1=randint(0..2)}
\integer{e2=randint(0..2)}
\integer{e3=randint(0..3)}
\integer{e4=randint(0..4)}
\integer{nb1=randint(11..99)}
\integer{nb2=randint(11..99)}
\integer{nb3=randint(11..99)}
\integer{nb4=randint(11..99)}
\text{nb=shuffle(\nb1,\nb2,\nb3,\nb4)}
\real{nb1=\nb[1]/10^\e1}
\real{nb2=\nb[2]/10^\e2}
\real{nb3=\nb[3]/10^\e1}
\real{nb4=\nb[4]/10^\e2}
\real{res=\nb1 * \nb2 * \nb3 * \nb4}
\text{nb1=slib(numeration/ecriturenombre \nb1)}
\text{nb2=slib(numeration/ecriturenombre \nb2)}
\text{nb3=slib(numeration/ecriturenombre \nb3)}
\text{nb4=slib(numeration/ecriturenombre \nb4)}
\text{nb1=wims(translate . to , in \nb1)}
\text{nb2=wims(translate . to , in \nb2)}
\text{nb3=wims(translate . to , in \nb3)}
\text{nb4=wims(translate . to , in \nb4)}

\text{enonc=\nb1 \(\times) \nb2 \(\times) \nb3 \(\times) \nb4 =}
\integer{l=12}
#endif
#include "lang_titles.inc"
#include "lang.inc"
\text{res=slib(numeration/ecriturenombre \res)}
\text{res=wims(translate . to , in \res)}

\statement{
\name_enonce:
<div class="wimscenter">
 \enonc \embed{r1,\l}
</div>
<div class="wims_instruction">\name_warning</div>
}
\answer{}{\res}{type=raw}
