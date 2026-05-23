target= CORequa3,CORfonct3,CORequa4,CORfonct4,CORequa5,CORfonct5

#if #TARGET(CORfonct3)
#define TIT fonction-représentation
#define NUMBER 3
#define TYPE 1
#endif
#if #TARGET(CORfonct4)
#define TIT fonction-représentation
#define NUMBER 4
#define TYPE 1
#endif
#if #TARGET(CORfonct5)
#define TIT fonction-représentation
#define NUMBER 5
#define TYPE 1
#endif
#if #TARGET(CORequa3)
#define TIT équation-droite
#define NUMBER 3
#define TYPE 2
#endif
#if #TARGET(CORequa4)
#define TIT équation-droite
#define NUMBER 4
#define TYPE 2
#endif
#if #TARGET(CORequa5)
#define TIT équation-droite
#define NUMBER 5
#define TYPE 2
#endif

\title{Correspondance TIT NUMBER}

\integer{type=TYPE}
\integer{number=NUMBER}
\language{fr}
\range{-5..5}
\author{Fabrice, Guerimand}
\email{fwguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{10000}

\if{\type=1}{
\text{question=Mettez en correspondance chaque fonction avec la couleur de sa
représentation graphique dans le repère ci-contre.}
\text{ord=f(x)}
\text{size=60x150x75}
}{
\text{question=Mettez en relation chaque équation avec la couleur de
la droite correspondante dans le repère ci-contre.}
\text{ord=y}
\text{size=60x100x75}
}


\text{a=2,3,4,5}
\integer{b=0}
\integer{a=randitem(\a)}

\text{choix=\a,-\a,-1/\a,1/\a,1,-1}
\text{choix=shuffle(\choix)}
\text{co=red;#;rouge,green;#;vert,yellow;#;jaune,purple;#;violet,blue;#;bleu,black;#;noir}
\text{co=shuffle(\co)}
\text{co=wims(item 1 to \number of \co)}
\matrix{tmp=wims(items2lines \co)}
\matrix{tmp=wims(replace internal ;#; by , in \tmp)}
\text{co=column(1,\tmp)}
\text{nom=column(2,\tmp)}

\text{dessin=wims(record 2 of src/graph.don)}
\text{coord=}
\for{i=1 to \number}{
\text{A=item(\i,\choix)}
\integer{B=0}

\integer{xpt1=150+(-5*30)}
\integer{xpt2=150+(5*30)}
\function{dg=-(\A*(x)+(\B))*30+150}
\integer{ypt1=evalue(\dg,x=-5)}
\integer{ypt2=evalue(\dg,x=5)}
\text{dessin=\dessin
segment \xpt1,\ypt1,\xpt2,\ypt2,\co[\i]}
\text{val=texmath(\A*x)}
\text{tmp=\type=1?\(x \mapsto \val):\(y=\val)}
\text{coord=wims(append item \tmp to \coord)}
}

\text{dessin=\dessin
text black,290,150,medium,x
text black,155,2,medium,\ord}


\statement{
<div class="float_right">\draw{301,301}{\dessin}</div>
\question
<div class="wimscenter">
\embed{r1,\size}
</div>
}

\answer{Réponse}{\coord;\nom}{type=correspond}
