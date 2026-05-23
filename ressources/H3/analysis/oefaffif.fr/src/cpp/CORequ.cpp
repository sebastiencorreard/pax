target= CORequa3 CORfonct3 CORequa4 CORfonct4 CORequa5 CORfonct5

#if defined TARGET_CORfonct3
# define NUMBER 3
# define TYPE 1
#endif
#if defined TARGET_CORfonct4
# define NUMBER 4
# define TYPE 1
#endif
#if defined TARGET_CORfonct5
# define NUMBER 5
# define TYPE 1
#endif
#if defined TARGET_CORequa3
# define NUMBER 3
# define TYPE 2
#endif
#if defined TARGET_CORequa4
# define NUMBER 4
# define TYPE 2
#endif
#if defined TARGET_CORequa5
# define NUMBER 5
# define TYPE 2
#endif

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\integer{type=TYPE}
\integer{number=NUMBER}
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{10000}
\if{\type=1}{
\text{question=\name_question1}
\text{ord=f(x)}
\text{size=40x150x75}
}{
\text{question=\name_question2}
\text{ord=y}
\text{size=40x140x75}
}

\text{a=1,2,3,4}
\integer{b=item(1,\a)}
\integer{a=item(2,\a)}

\text{choix=\a;#;\b,\a;#;-\b,-\a;#;\b,-\a;#;-\b,\b;#;\a,-\b;#;\a,\b;#;-\a,-\b;#;-\a}
\text{choix=shuffle(\choix)}
\text{co=shuffle(\co)}
\text{co=wims(item 1 to \number of \co)}
\matrix{tmp=wims(items2lines \co)}
\matrix{tmp=wims(replace internal ;#; by , in \tmp)}
\text{co=column(1,\tmp)}
\text{nom=column(2,\tmp)}

\text{dessin=wims(record 2 of src/graph.don)}
\text{coord=}
\for{i=1 to \number}{
\text{don=item(\i,\choix)}
\text{tmp=\don}
\text{don=wims(replace internal ;#; by , in \don)}
\integer{A=item(1,\don)}
\integer{B=item(2,\don)}

\integer{xpt1=150+(-5*30)}
\integer{xpt2=150+(5*30)}
\function{dg=-(\A*(x)+(\B))*30+150}
\integer{ypt1=evalue(\dg,x=-5)}
\integer{ypt2=evalue(\dg,x=5)}
\text{dessin=\dessin
segment \xpt1,\ypt1,\xpt2,\ypt2,\co[\i]}
\text{val=texmath(\A*x+(\B))}
\text{tmp=\type=1?\(x \mapsto \val):\(y=\val)}
\text{coord=wims(append item \tmp to \coord)}
}

\text{dessin=\dessin
text black,290,150,medium,x
text black,155,2,medium,\ord}

\statement{
<div class="wims_columns">
  <div class="medium_size img_col">\draw{301,301}{\dessin}</div>
  <div class="medium_size text_col">\question
    <div class="wimscenter">\embed{r1,\size}</div>
  </div>
</div>
}
\answer{\name_answer}{\coord;\nom}{type=correspond}
