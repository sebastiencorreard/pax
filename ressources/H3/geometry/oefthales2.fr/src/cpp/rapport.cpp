target=raplong2,raplong1,rapara,raplong3,raplong4

#define RAPPORT rapport

\language{fr}
\range{-5..5}
#include "lang_titles.inc"
#include "author.inc"
\computeanswer{no}
\format{html}
\precision{1000}
\text{size=35x25x1}
\integer{size2=50}

#if defined TARGET_raplong1
 \integer{nbrap=3}
 \integer{ch=randint(1..2)}
 \if{\ch=1}{
  \integer{recnt=wims(recordcnt data/raptriangle.don)}
  \integer{recnt=random(1..\recnt)}
  \matrix{don=wims(record \recnt of data/raptriangle.don)}
 }{
  \integer{recnt=wims(recordcnt data/rappapillon.don)}
  \integer{recnt=random(1..\recnt)}
  \matrix{don=wims(record \recnt of data/rappapillon.don)}
 }
#endif

#if defined TARGET_raplong2
 \integer{recnt=wims(recordcnt data/raptriangle.don)}
 \integer{recnt=random(1..\recnt)}
 \matrix{don=wims(record \recnt of data/raptriangle.don)}
 \integer{nbrap=3}
#endif

#if defined TARGET_raplong3
 \matrix{don=wims(record 1 of data/raptriangle.don)}
 \integer{nbrap=3}
#endif

#if defined TARGET_raplong4
 \integer{nbrap=3}
 \matrix{don=wims(record 1 of data/rappapillon.don)}
#endif

#if defined TARGET_rapara
\integer{ch=1}
\integer{type=2}
\integer{nbrap=2}
#endif


\text{S=A,B,C,D,E,F,G,H,I,J,K,L,M,N}
\text{S=shuffle(\S)}

#if defined TARGET_rapara
 \integer{recnt=wims(recordcnt data/parallele.don)}
 \integer{recnt=random(1..\recnt)}
 \matrix{don=wims(record \recnt of data/parallele.don)}
#else

#endif

#include "lang.inc"

moved here from data/rapptriangle.don and data/rappapillon.don as
those files must be language independent (one line per record)
\matrix{hypos=\name_hypos[1] \(\lbeg X2X3\lend\) \name_and \(\lbeg X4X5\lend\) \name_hypos[2].,1
\name_hypos[3] \(X3X5X4X6\) \name_hypos[4] \name_and \(X2\) \name_hypos[5] \(\sbeg X6X3\lend\).,2
\name_hypos[3] \(X2X3X6X4\) \name_hypos[4] \name_and \(X1\) \name_hypos[5] \(\sbeg X2X4\lend\).,3
\name_hypos[1] \(\lbeg X2X4\lend\) \name_and \(\lbeg X5X7\lend\) \name_hypos[2]. \(X6\) \name_hypos[6] \(\sbeg X5X7\send\) \name_and \(X3\) \name_hypos[7] \(\lbeg X6X1\lend\) \name_and \(\lbeg X2X4\lend\).,4
\name_hypos[1] \(\lbeg X2X4\lend\) \name_and \(\lbeg X5X7\lend\) \name_hypos[2]. \(X6\) \name_hypos[6] \(\sbeg X5X7\send\) \name_and \(X3\) \name_hypos[7] \(\lbeg X6X1\lend\) \name_and \(\lbeg X2X4\lend\).,5
\name_hypos[1] \(\lbeg X2X4\lend\) \name_and \(\lbeg X5X7\lend\) \name_hypos[2]. \(X6\) \name_hypos[6] \(\sbeg X5X7\send\) \name_and \(X3\) \name_hypos[7] \(\lbeg X6X1\lend\) \name_and \(\lbeg X2X4\lend\).,6
\name_hypos[1] \(\lbeg X2X3\lend\) \name_and \(\lbeg X4X5\lend\) \name_hypos[2] \name_and \name_hypos[9] \(\lbeg X2X4\lend\) \name_and \(\lbeg X3X5\lend\) \name_hypos[8] X1.,7
\name_hypos[3] \(X3X5X4X6\) \name_hypos[4] \name_and \(X2\) \name_hypos[5] \(\sbeg X6X3\lend\).,8
\name_hypos[3] \(X2X3X6X4\) \name_hypos[4] \name_and \(X1\) \name_hypos[5] \(\sbeg X2X4\lend\).,9
\name_hypos[1] \(\lbeg X2X1\lend\) \name_and \(\lbeg X4X5\lend\) \name_hypos[2] \name_and \name_hypos[9] \(\lbeg X1X5\lend\) \name_and \(\lbeg X2X4\lend\) \name_hypos[8] \(X3\).,10
}

\integer{nbsom=row(1,\don)}
\for{i=1 to \nbsom}{
 \matrix{don=wims(replace X\i by \S[\i] in \don)}
 \matrix{hypos=wims(replace X\i by \S[\i] in \hypos)}
}

\integer{iii=row(2,\don)}
\text{hypo=wims(select \hypos where column 2=\iii)}
\text{tri=row(3,\don)}
\text{rapports=row(4,\don)}

#if defined TARGET_rapara
 \text{droites=item(3,\rapports)}
 \text{droites=wims(replace internal / by , in \droites)}
#else
 \text{rapports=shuffle(\rapports)}
#endif

\text{ltmp=wims(replace internal / by , in \rapports)}
\text{num=item(1,\ltmp)}
\text{liste=row(5,\don)}
\text{liste=\liste,\ltmp}
\text{tmp=row(6,\don)}
\text{xrange=item(1,\tmp)}
\text{yrange=item(2,\tmp)}
\matrix{dessin=row(7 to -1,\don)}
\text{dessin=wims(rows2lines \dessin)}

\text{rapports1=\rapports}
\text{rapports2=\ltmp[2]/\ltmp[1],\ltmp[4]/\ltmp[3],\ltmp[6]/\ltmp[5]}
\text{affrapports1=wims(replace internal , by = in \rapports1)}
\text{affrapports1=texmath(\affrapports1)}
\text{affrapports2=wims(replace internal , by = in \rapports2)}
\text{affrapports2=texmath(\affrapports2)}


#if defined TARGET_rapara
\integer{choixtheo=random(1..2)}
\statement{
<div class="wims_columns">
 <div class="medium_size img_col">\draw{\xrange,\yrange}{\dessin}</div>
 <div class="medium_size text_col">
  \name_statement[1] \(\lbeg \droites[1]\lend) \name_and
\(\lbeg \droites[2]\lend)
\if{choixtheo=1}{\name_statement[2].}
  {\name_statement[3].}
  <br>
<b>\name_yourreply:</b>
<table class="wimscenter">
<tr>
<td>\embed{reply 1,\size}</td>
<td rowspan="3"> \name_and </td>
<td> \embed{reply 3,\size}</td>
</tr><tr>
<td><hr></td>
<td><hr></td>
</tr><tr>
<td> \embed{reply 2,\size}</td>
<td> \embed{reply 4,\size}</td>
</tr></table>
<div class="wims_instruction">
\name_instruction.</div>
 </div>
</div>

}
\reply{numérateur1}{\num1;\liste}{type=clickfill}
\reply{dénominateur1}{\den1;\liste}{type=clickfill}
\reply{numérateur2}{\num2;\liste}{type=clickfill}
\reply{dénominateur1}{\den2;\liste}{type=clickfill}

\text{tmplin=\num1/\den1,\num2/\den2}

#else
\statement{
<div class="wims_columns">
 <div class="medium_size img_col">\draw{\xrange,\yrange}{\dessin}</div>
 <div class="medium_size text_col">
  \hypo[1]

  \name_statement[1]
  <b>\name_statement[2] \(\tri[1]) \name_and \(\tri[2])</b>?

<br><b>\name_yourreply:</b>
<table class="wimscenter wimsnoborder">
<tr>
<td>\embed{reply 1,\size}</td>
<td rowspan="3"> =</td>
<td> \embed{reply 3,\size}</td>
<td rowspan="3"> = </td>
<td> \embed{reply 5,\size}</td>
</tr><tr>
<td><hr></td>
<td><hr></td>
<td><hr></td>
</tr><tr>
<td> \embed{reply 2,\size}</td>
<td> \embed{reply 4,\size}</td>
<td> \embed{reply 6,\size}</td>
</tr></table>
<div class="wims_instruction">\name_instruction.</div>
 </div>
</div>

}
\reply{numérateur1}{\num1;\liste}{type=clickfill}
\reply{dénominateur1}{\den1;\liste}{type=clickfill}
\reply{numérateur2}{\num2;\liste}{type=clickfill}
\reply{dénominateur1}{\den2;\liste}{type=clickfill}
\reply{numérateur3}{\num3;\liste}{type=clickfill}
\reply{dénominateur3}{\den3;\liste}{type=clickfill}

\text{tmplin=\num1/\den1,\num2/\den2,\num3/\den3}
#endif

\text{tmplin=wims(listuniq \tmplin)}
\text{set1=wims(listintersect \rapports1 and \tmplin)}
\text{set2=wims(listintersect \rapports2 and \tmplin)}
\integer{lin1=items(\tmplin)}
\integer{lin2=items(\set1)}
\integer{lin3=items(\set2)}
\condition{}{\lin1=\nbrap and (\lin2=\nbrap or \lin3=\nbrap)}

\solution{\name_solution: \(\affrapports1) \name_or \(\affrapports2)}
