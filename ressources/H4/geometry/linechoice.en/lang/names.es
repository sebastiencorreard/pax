!set lang_exists=yes

!set t_1=paramétricas

!distribute lines Dada una recta en el plano cartesiano\
  que se muestra a continuación.\
  Gráfico de la recta\
  Gráfico de la rectaa que escogiste\
  expresada por las siguientes ecuaciones paramétricas.\
  expresada por la siguiente equación.\
  ¿Cuál de las siguientes gráficas corresponde a esta recta?\
  Clica sobre ella.\
  Clica aquí\
  si piensas que ninguna de las opciones corresponde a la recta correcta.\
into name_present1,name_present2,name_attribut1,name_attribut2,name_equations,name_equation,\
 name_question1,name_clickon,name_clickhere,name_nochoice

!set name_question2=!nosubst ¿Cuál de las siguientes ecuaciones $(t_$asktype) \
 corresponde a esta recta?
!distribute lines Abandonar la sesión\
  Una nueva sesión\
  Cambiar el ejercicio\
  Un nuevo ejercicio\
  Reconfigurar el ejercicio\
into name_abandon,name_news,name_newexo,name_otherexo,name_reconfig

!set name_intro1=Se utilizan 4 formas de expresar una recta (no pasa por\
el origen, no es vertical ni horizontal) en el plano cartesiano:\
una ecuación implícita, una ecuación que da \(y\) como una función de x, una que da\
\(x\) como una función de y, o un sistema de ecuaciones paramétricas.

!set name_intro2=Este ejercicio te brinda una oportunidad de entrenamiento para familiarizarte con\
  estas diferentes expresiones de la recta, así como sus gráficos.

!distribute lines Se puede\
  Puedes elegir el tipo de ecuación\
  \
  Y una sesión estará compuesta por\
  preguntas \
  con la nota asignada al final de cada sesión \
  ecuaciones o gráficas se presentarán como opciones, que \
  la respuesta correcta\
into name_intro3,name_type,name_chinese,name_session,name_questions,name_Score,\
 name_numberequation,name_good

!set name_prompt1=dar el gráfico y pide reconocer la ecuación,\
dar la ecuación y pide reconocer el gráfico,\
dar una forma de ecuación y pide que se reconozca otra

!set name_prompt2=sistema de ecuaciones paramétricas, ecuación implícita,\
   y como función de x, x como función de y

!set name_prompt3=siempre contienen, podrían no contener

!set name_questionnumber=!nosubst Número de pregunta $[$replycnt+1] dentro de una sesión de $repeat.
!set name_related=rectas, opciones gráficas, ecuaciones, ecuaciones paramétricas

!set name_answer1=Tu elección se muestra en <span class="bold">negrita</span>,\
 y la respuesta correcta en <span style="color:blue">azul</span>.

!distribute lines Sí, tu elección corresponde correctamente a la recta.\
   No, has elegido otra recta.\
   No, la recta que has elegido se ve como\
   No, la respuesta correcta está entre las opciones!\
   De hecho, la respuesta correcta no está entre las opciones\
   Respuesta correcta\
   Respuesta incorrecta\
   Nota\
   Continuar con la siguiente pregunta.\
into name_answer2,name_answer3,name_answer4,name_answer5,name_answer6,\
 name_goodanswer,name_badanswer,name_score,name_continue

!set name_questionon=!nosubst Pregunta número $replycnt de $repeat
!set name_theend=!nosubst Has terminado una sesión de $repeat preguntas, con una nota de

!set name_mustfinish=!nosubst Tienes que terminar las $repeat preguntas para obtener una nota.

!! only latin character without accent
!set name_gnuplot_good=Respuesta correcta
!set name_gnuplot_choice=Tu elección
