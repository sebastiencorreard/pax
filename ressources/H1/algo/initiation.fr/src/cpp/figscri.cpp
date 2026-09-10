target= figcriptchoix figscriptcompleter figscriptassocier

#if defined TARGET_figcriptchoix
\text{confparm1= items(\confparm1)=0 ? randitem(1,2):randitem(\confparm1)}
:\title{Figures usuelles : Lequel convient ?}
#endif

#if defined TARGET_figscriptcompleter
:\title{Figures usuelles : Compléter le script}
#endif

#if defined TARGET_figscriptassocier
\title{Figures usuelles : Associer chaque script à la figure qui lui correspond}
#endif


:\author{Bruno, Mifsud}
:\email{bruno.mifsud@laposte.net}

\text{name_instruction=Aucun logiciel n'est autorisé pour répondre à cet exercice,
 sans quoi il ne sert pas à grand chose pour progresser.}
:%%%%%%%%%% pour les solutions générales  %%%%%%%%%%%%%%%


:%%%%%%%%%%%%%%%%%%%%% fin sol %%%%%%


#if defined TARGET_figcriptchoix
\if{\confparm1=1}{\text{data=1_pgm_0.png, 1_fig_0.png
2_pgm_0.png,2_fig_0.png
3_pgm_0.png,3_fig_0.png
5_pgm_0.png,5_fig_0.png
6_pgm_0.png,6_fig_0.png}}
\if{\confparm1=2}{\text{data=1_fig_0.png, 1_pgm_0.png
2_fig_0.png,2_pgm_0.png
3_fig_0.png,3_pgm_0.png
5_fig_0.png,5_pgm_0.png
6_fig_0.png,6_pgm_0.png}}


:Nombre d'images présentées.

\integer{cnt=3}

:La taille verticale des images en pixels
\if{\confparm1=1}{\text{sizev=200}}{\text{sizev=100}}

:%%%%%%%%%%%%%%
ne pas mettre de ; dans sizev
\if{\sizev notsametext }{
  \text{sizev= style="height:wims(nospace \sizev px)"}
}
\text{data=wims(embraced randitem \data)}
\text{tot=rows(\data)}
\text{imagenonce=}
\while{\imagenonce issametext }{
 \text{mot = randrow(\data)}
 \text{imagenonce=\mot[2]}
}
\text{image=\mot[1]}
\text{ext=item(2,wims(replace internal . by , in wims(lowercase \image)))}


:Consigne
Ici <span class="wims_emph">\imagenonce</span> représente le nom de l'image qui sera à cliquer
(à placer en 2e item dans les données).

%%%%%%%%%%%%%
\if{\confparm1=1}{
\text{instruction=<p>Clique sur le seul script qui trace la figure suivante :
</p>}}{\text{instruction=<p>Clique sur la seule figure que trace le script suivant :
</p>}}

:%%%%%%%%%%%%%%
\css{<style>
.ans_multipleclick {margin-left:auto;margin-right:auto}
</style>
}
\text{liste=column(1,\data)}
\text{listeimagenonce=column(2,\data)}
\text{rep=position(\imagenonce,\listeimagenonce)}
\text{perturb=wims(makelist x for x=1 to \tot)}
\text{perturb=shuffle(\perturb)}
\text{perturb=\perturb[1..\cnt]}
\text{inter=wims(listintersection \rep and \perturb)}
\if{\inter=}{
  \integer{repcnt=items(\rep)}
  \text{rep= \repcnt >1 ? randitem(\rep)}
  \text{perturb=\rep,\perturb[1..\cnt-1]}
  \text{perturb=shuffle(\perturb)}
}
\matrix{data=\data}
\text{liste=\data[\perturb;1]}
\text{listeimagenonce=\data[\perturb;2]}
\text{cnt=items(\liste)}
\text{Image=}
\for{j=1 to \cnt}{
  \text{Image=/ isin \liste[\j] ? wims(append item \liste[\j] to \Image):
  wims(append item \imagedir/\liste[\j] to \Image)}
}
\text{liste=wims(makelist imgrename(x \sizev) for x in \Image)}
\text{rep=position(\imagenonce,\listeimagenonce)}

\statement{
  <div class="instruction">\instruction</div>
  <div class="wimscenter"> \img{\imagedir/\imagenonce}</div>
  <div class="wimscenter">\embed{r1}</div>
  <div class="wims_instruction">
  \name_instruction
  </div>
}

\answer{}{\rep;\liste}{type=click}{option=shuffle}
#endif

%%%% Fin scriptfigure

%%%%%%%%%%%%% Figures Usuelles associer
#if defined TARGET_figscriptassocier

\text{file=donnee_scriptfig}
\text{notepad=slib(utilities/notepad Notepad,small)}

\text{instruction=asis(Associez à chaque script la figure qu'il trace.)}
\text{instruction2=asis()}
\text{choice=}
\text{common=}
\text{audio_file=no}
\text{reading_file=no}
\text{image_file=no}
\text{video_file=no}
\text{alea=yes}
\text{size=200x200x200}
\text{partialscore=split}
\text{percent=1}
\text{aucune=aucune de ces possibilités}
\text{format=clickfill}
\text{format0=mark}
\text{specialhelp1=}
\text{specialhelp2=}
\text{specialhelp3=}
\text{specialhelp4=}
\text{helpprompt=}
\text{reaccent=}
\text{paste=yes}
\text{pos_rep=inside}
\text{second_step=yes}
\text{first_step=1}
\text{answer_given=}
\text{try=}
\text{packs=}
\text{player=}
\text{player_option=}
#####################
\text{givegood=slib(oef/env givegood)}
\text{givegood=\givegood issametext ? 1}
\text{answer_given=\givegood>0? yes}
\text{file0=randitem(\file)}
\integer{cnt_question= wims(recordcnt \file0)}

################
\text{MAX=1}
\text{N=1}
\text{M=3}
################
\text{option=\format0 iswordof flashcard?show}
\text{ff=\format0 iswordof flashcard ?s;&nbsp;}
\text{autocompletion=\format iswordof case nocase ? autocomplete="off"}
\text{player=wims(replace internal - by in \player)}
\text{specialhelp=\specialhelp1,\specialhelp2,\specialhelp3,\specialhelp4}
\text{helpprompt=\helpprompt = ?++>}
\integer{first_step=\first_step notwordof 0 ? 1}
\text{option_reaccent=\reaccent!=yes ? noreaccent:}
\text{nopaste=\paste issametext no ? slib(utilities/nopaste )}

\text{instruction=\instruction issametext ? wims(getdef instruction in \file0)}
\text{instruction=wims(\instruction)}
\text{instruction2=\instruction2 issametext ? wims(getdef instruction2 in \file0)}
\text{instruction2=wims(\instruction2)}
\text{size=\size issametext ? wims(getdef size in \file0)}
\text{reading_file=\reading_file issametext ? wims(getdef reading_file in \file0)}
\text{reading = wims(record 0 of \reading_file)}
\text{reading=wims(\reading)}
\text{audio_file = \audio_file issametext ? wims(getdef audio_file in \file0)}
\text{audio=\audio_file notsametext and \audio_file notsametext no?
<div class="wimscenter">slib(media/audio \imagedir/\audio_file,\player_option,player=\player)</div>}

\text{image_file=\image_file issametext ? wims(getdef image_file in \file0)}
\text{image=\image_file notsametext and \image_file notsametext no?
wims(makelist <img src="\imagedir/x " alt="" /> for x in \image_file)}

\text{video_file=\video_file issametext ? wims(getdef video_file in \file0)}
\if{\video_file notsametext and \video_file notsametext no}{
  \text{video_file=http notin \video_file ? \imagedir/\video_file}
\text{video=\video_file notsametext ? <div><a target="wims_external" href="\video_file">[video]</a></div>}
}
\text{choix=\choice issametext ? wims(getdef choice in \file0):\choice}

\text{try =\try notwordof 1 2 3 4 5 6 7 8 9 10 ? 1}
\text{size=\format iswordof dragfill clickfill ? \size x 1}
\integer{N = min(\cnt_question,\N)}
\integer{MAX=min(\N*\MAX,\cnt_question)}
\text{battage=\alea issametext yes ? shuffle(\cnt_question) :
wims(makelist x for x = 1 to \cnt_question)}
      \text{QUEST=wims(randrecord \file)}
\text{QUEST=wims(embraced randitem \QUEST)}
\text{preliminaire_test=\QUEST}
\text{preliminaire_test=row(1,\preliminaire_test)}
\if{\preliminaire_test notsametext }{
 \text{inst_audio=wims(getopt audio in \preliminaire_test)}
 \text{inst_image=wims(getopt image in \preliminaire_test)}
 \text{inst_title=wims(getopt title in \preliminaire_test)}
 \text{inst_intro=wims(getopt intro in \preliminaire_test)}
 \integer{test_inst=\inst_audio\inst_image\inst_title\inst_intro notsametext ? 1 : 0}
 \text{rab_inst=}
 \text{rab_inst=\inst_title notsametext ?\rab_inst<div class="wimscenter">\inst_title</div>}
 \text{rab_inst=\inst_intro notsametext ?\rab_inst \inst_intro}
 \text{rab_inst=\inst_image notsametext ? \rab_inst <div class="wimscenter"><img src="\imagedir/\inst_image" alt="" /></div>}
 \if{\inst_audio notsametext }{
     \text{rab_inst1= . isin \inst_audio or \packs= ?
       slib(media/audio \imagedir/\inst_audio,\player_option,player=\player):slib(lang/swac \inst_audio,\packs,player=\player,\player_option)}
     \text{rab_inst=\rab_inst <div class="wimscenter">\rab_inst1[1;1]</div>}
 }
 \text{preliminaire=\test_inst=1 ? \rab_inst:&nbsp;}
}{\integer{test_inst=2}}

 \matrix{QUEST=\test_inst=1 or \test_inst=2 ? wims(line 2 to -1 of \QUEST):\QUEST}
\integer{cnt_QUEST = rows(\QUEST)}
\integer{M=\M issametext all ? \cnt_QUEST:min(\cnt_QUEST,\M)}
\text{choix=shuffle(\cnt_QUEST)}
\matrix{QUEST=\QUEST[\choix[1..\M];]}
matrix{QUEST = wims(replace internal _imagedir by \imagedir in \QUEST)}
\text{gauche=}
\text{droite=}
\for{ im = 1 to \M}{
    \if{.mp3 isin \QUEST[\im;2] or .jpg isin \QUEST[\im;2] or .gif isin \QUEST[\im;2] or .png isin \QUEST[\im;2]}{
     \if{.mp3 isin \QUEST[\im;2]}{
      \text{Image=wims(nospace \QUEST[\im;2])}
      \text{Image=slib(media/audio \imagedir/\QUEST[\im;2],\player_option,player=\player)}
      }
      \if{.jpg isin \QUEST[\im;2] or .gif isin \QUEST[\im;2] or .png isin \QUEST[\im;2]}{
        \text{Image=wims(nospace \QUEST[\im;2])}
        \text{Image=wims(replace internal image= by in \Image)}
        \text{Image=wims(replace internal imag= by in \Image)}
        \text{Image=imgrename(\imagedir/\Image )}
      }
   }
   {##recherche dans swac -- rajouter ensuite les images
   \text{ audiocorr=wims(getopt audio in \QUEST[\im;2])}
    \if{\audiocorr notsametext }{
      \text{Image=slib(lang/swac \audiocorr,\packs,player=\player,\player_option)}
      \text{Image=\Image[1;1]}
    }{\text{Image= \QUEST[\im;2]}}
   }
   \text{droite = wims(append item \Image to \droite)}
}
\for{ im = 1 to \M}{
  \if{.mp3 isin \QUEST[\im;1] or .jpg isin \QUEST[\im;1] or .gif isin \QUEST[\im;1] or .png isin \QUEST[\im;1]}{
    \if{.mp3 isin \QUEST[\im;1]}{
      \text{Image=wims(nospace \QUEST[\im;1])}
      \text{Image=slib(media/audio \imagedir/\QUEST[\im;1],\player_option,player=\player)}
    }
    \if{.jpg isin \QUEST[\im;1] or .gif isin \QUEST[\im;1] or .png isin \QUEST[\im;1]}{
      \text{Image=wims(nospace \QUEST[\im;1])}
      \text{Image=wims(replace internal image= by in \Image)}
      \text{Image=wims(replace internal imag= by in \Image)}
      \text{Image=imgrename(\imagedir/\Image )}
    }
  }
  {##recherche dans swac -- rajouter ensuite les images
   \text{ audiocorr=wims(getopt audio in \QUEST[\im;1])}
    \if{\audiocorr notsametext }{
      \text{Image=slib(lang/swac \audiocorr,\packs,player=\player,\player_option)}
      \text{Image=\Image[1;1]}
    }{\text{Image= \QUEST[\im;1]}}
  }
    \text{gauche = wims(append item \Image to \gauche)}
}
#include "size.inc"
\statement{\nopaste <div class="instruction">\instruction</div> \preliminaire
  \if{\reading notsametext }{\special{help reading,[à lire]}}
  \if{\image notsametext }{\special{help image,[à regarder]}}
  \audio\video
  <div class="wimscenter question">\embed{reply1,\size}</div>
  <div class="wims_instruction">
  \name_instruction
  </div>
}

\answer{}{\gauche; \droite}{type=correspond}{option=\partialscore}
#endif
:%%%%%%%%%%%%% Fin Angles associer


:%%%%%%%%%%%%%%%% Compléter le script incomplet

#if defined TARGET_figscriptcompleter
\integer{fig=random(1,2,3,5,6)}
\if{\fig=1}{\real{ans=random(4,90)}}
\if{\fig=2}{\real{ans=random(3,120)}}
\if{\fig=3}{\real{ans=random(2,90)}}
\if{\fig=5}{\real{ans=90}}
\if{\fig=6}{\real{ans=random(60,100)}}


\text{imgfig=fig\fig.png}
\text{imgpgm=pgm\fig\ans.png}

%%%%%% pour solution :
\text{pgmcorr=pgm\fig.png}

:Le texte qui explique ce qu'il faut faire.
$embraced_randitem
\text{explain=
Quelle valeur faut-il saisir dans ce script pour obtenir la figure ci dessous ?
}
:Mise en aléatoire par des accolades emboitables
$embraced_randitem
\text{accolade=item(1,1 oui,
2 non)}

:%% Calculs à ne pas modifier
\text{accolade=wims(word 1 of \accolade)}
\text{explain=\accolade=1 ?wims(embraced randitem \explain)}

:%%%%%%%%%%%%% Maintenant l'énoncé en code html. %%%%%%%%%%%%%%%%%%%%

::Vous n'avez pas besoin de modifier ceci en général.

\statement{
<div class="wimscenter">\img{\imagedir/\imgpgm}</div>
\explain
<br /><div class="wimscenter">\img{\imagedir/\imgfig}</div>}

:%%%%%%%%%%%%% Rien à modifier ci-après. %%%%%%%%%%%%%%%%%5

\answer{Réponse}{\ans}{type=number}

\latex{
\begin{statement}
  \explain
\end{statement}
}

#endif

\solution{
#if defined TARGET_figcriptchoix
\if{\confparm1=1}{
Script \img{\imagedir/\image}
permettant de tracer la figure
\img{\imagedir/\imagenonce}.
}{
Figure \img{\imagedir/\image} obtenue par le script \img{\imagedir/\imagenonce}.
}
#endif

#if defined TARGET_figscriptcompleter
Script : \img{\imagedir/\pgmcorr}.

Figure obtenue : \img{\imagedir/\imgfig}.

#endif
#if defined TARGET_figscriptassocier
<b>Bonnes réponses :</b>
<table class="wimscenter wimsnoborder">
\for{ k = 1 to 3}{
<tr>
<td>\img{\imagedir/\QUEST[\k;1]}</td>
<td>\(\leftrightarrow\)</td>
<td>\img{\imagedir/\QUEST[\k;2]}</td>
</tr>}
</table>
#endif
}
