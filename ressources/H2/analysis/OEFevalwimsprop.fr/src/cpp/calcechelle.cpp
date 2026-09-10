target=calcechelle2 calcechelle3 calcechelle4 calcechelle5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_calcechelle2
 \integer{rapport=randint(100,1000,200,400,500,2000,5000)}
 \integer{l1=randint(1..9)*100}
 \real{l2=\l1/\rapport}
 \text{unit1=randitem(cm,mm,dm)}
 \text{unit2=\unit1}
 \text{rep=simplify(\l2/\l1)}
#endif
#if defined TARGET_calcechelle3
 \integer{rapport=randint(100,1000,200,400,500,2000,5000)}
 \integer{l1=randint(1..9)*100}
 \real{l2=\l1*\rapport}
 \text{unit1=randitem(cm,mm,dm)}
 \text{unit2=\unit1}
 \text{rep=simplify(\l2/\l1)}
#endif
#if defined TARGET_calcechelle4
 \integer{rapport=randint(10,20,40,50,200,500)}
 \integer{l1=randint(1..9)*100}
 \real{l2=\l1/\rapport}
 \text{unit=randrow(Km,m,1000
m,cm,100
m,mm,1000)}
 \text{unit1=\unit[1]}
 \text{unit2=\unit[2]}
 \text{rep=simplify(\l2/(\l1*\unit[3]))}
#endif
#if defined TARGET_calcechelle5
 \integer{rapport=randint(10,20,40,50,200,500)}
 \integer{l1=randint(1..9)}
 \real{l2=\l1*\rapport}
 \text{unit1=randitem(cm,mm,dm)}
 \text{unit2=\unit1}
 \text{rep=simplify(\l2/(\l1))}
#endif
\statement{
\l1 \unit1 \name_enonce[1] \l2 \unit2 \name_enonce[2]<p>
\name_question?
</p>}

\answer{\name_answer}{\rep}{type=numexp}{option=noreduction}
