target=oefreprodangle1 oefreprodangle2 oefreprodangle3 oefreprodangle4 oefreprodangle5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_oefreprodangle1
\statement{
  \name_enonce:
<div>\embed{r1}</div>
}
\answer{}{1;\list}{type=radio}
#endif
#if defined TARGET_oefreprodangle2
\text{nom=shuffle(A,B,C,E,F,G,H,J,K,L,M,N,R,S,T)}
\integer{ang1=randint(30..80)}
\integer{ch=randint(0,5)}
\integer{ang2=\ang1+\ch}
\if{\ch=0}{\integer{rep=1}}{\integer{rep=2}}

\text{dess1=draw(300,300
xrange -5,25
yrange -5,25
arc 0,0,40,40,357,3,black
arc 0,0,40,40,357+\ang1,3+\ang1,black
arc 0,0,10,10,0,\ang1,black
seg 0,0,25,0,black
rotate \ang1
seg 0,0,25,0,black
fill 3,-0.5,6,red
)}

\text{dess2=draw(300,300
xrange -5,25
yrange -5,25
arc 0,0,40,40,357,3,black
arc 0,0,40,40,357+\ang2,3+\ang2,black
arc 0,0,10,10,0,\ang2,black
seg 0,0,25,0,black
rotate \ang2
seg 0,0,25,0,black
fill 3,-0.5,6,yellow
)}

\text{fig1=<img src="\dess1" alt="">}
\text{fig2=<img src="\dess2" alt="">}

\statement{
<div class="wims_center">\fig1 \fig2</div>
\name_enonce? \embed{r1}
<p>\name_hint</p>
}

\answer{}{\rep;\reps}{type=radio}
#endif
#if defined TARGET_oefreprodangle3
\text{fig=<img src="\imagedir/reproangl1r.jpg" alt="">,<img src="\imagedir/reproangl2r.jpg" alt="">,<img src="\imagedir/reproangl3r.jpg" alt="">,
<img src="\imagedir/reproangl4r.jpg" alt="">,<img src="\imagedir/reproangl5r.jpg" alt="">,<img src="\imagedir/reproangl6r.jpg" alt="">}
\statement{
<h2>\name_head</h2>
<p>\name_enonce</p>
<table class="wimscenter wimsborder">
<tr><th>\name_step 1</th><th>\name_step 2</th><th>\name_step 3</th></tr>
<tr>
\for{i=1 to 3}{<td>\embed{r\i,250x250}</td>}
</tr>
<tr><th>\name_step 4</th><th>\name_step 5</th><th>\name_step 6</th></tr>
<tr>
\for{i=4 to 6}{<td>\embed{r\i,250x250}</td>}
</tr>
</table>}

\answer{}{\fig[1]}{type=dragfill}{option=shuffle}
\answer{}{\fig[2]}{type=dragfill}
\answer{}{\fig[3]}{type=dragfill}
\answer{}{\fig[4]}{type=dragfill}
\answer{}{\fig[5]}{type=dragfill}
\answer{}{\fig[6]}{type=dragfill}
#endif
#if defined TARGET_oefreprodangle4
\text{fig=<img src="\imagedir/reproangl1r.jpg" alt="">,<img src="\imagedir/reproangl2r.jpg" alt="">,<img src="\imagedir/reproangl3r.jpg" alt="">,
<img src="\imagedir/reproangl4r.jpg" alt="">,<img src="\imagedir/reproangl5r.jpg" alt="">,<img src="\imagedir/reproangl6r.jpg" alt="">}
\statement{
<h2>\name_head</h2>
<p>\name_enonce</p>
<table class="wimscenter wimsborder">
<tr><th>\name_step 1</th><th>\name_step 2</th><th>\name_step 3</th></tr>
<tr>
\for{i=1 to 3}{<td>\fig[\i]</td>}
</tr><tr>
\for{i=1 to 3}{<td>\embed{r\i,250x80}</td>}
</tr><tr>
<th>\name_step 4</th><th>\name_step 5</th><th>\name_step 6</th>
</tr><tr>
\for{i=4 to 6}{<td>\fig[\i]</td>}
</tr><tr>
\for{i=4 to 6}{<td>\embed{r\i,250x80}</td>}
</tr>
</table>}

\answer{}{\rep[1]}{type=dragfill}{option=shuffle}
\answer{}{\rep[2]}{type=dragfill}
\answer{}{\rep[3]}{type=dragfill}
\answer{}{\rep[4]}{type=dragfill}
\answer{}{\rep[5]}{type=dragfill}
\answer{}{\rep[6]}{type=dragfill}
#endif
#if defined TARGET_oefreprodangle5
\statement{
<h2>\name_head</h2>
<p>\name_enonce</p>
<ul>
\for{i=1 to 6}{<li>\name_step \i : \embed{r\i,400x70}</li>}
</ul>}

\answer{}{\rep[1]}{type=dragfill}{option=shuffle}
\answer{}{\rep[2]}{type=dragfill}
\answer{}{\rep[3]}{type=dragfill}
\answer{}{\rep[4]}{type=dragfill}
\answer{}{\rep[5]}{type=dragfill}
\answer{}{\rep[6]}{type=dragfill}
#endif
