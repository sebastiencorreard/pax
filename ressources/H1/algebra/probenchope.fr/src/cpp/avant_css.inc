%%% css commune autre que css euler et css particuliere %%%
\css{
<style>
#include "css.inc"

.indication{
  font-weight:bold;color:#009999;
  margin-bottom: 0.8em;
  margin-top: 0.8em;
}
.quest{
  color:blue;
  font-weight:bold;
  margin:0;
}

.flex_box{
  align-items:center;
  justify-content:center;
}
.sigle{
  margin:0.4em;
}
.tick:before{
  content : "\002713";
  color:green;
  font-weight:bold;
  font-size:1.3em;
  border-radius:4px;
  border-style:solid;
  padding:0.1em;
}
.croix:before{
  content : "\002717";
  color:red;
  font-weight:bold;
  font-size:1.3em;
  border-radius:4px;
  border-style:solid;
  padding:0.1em;
}
.approx:before{
  content : "\002248";
  color:orange;
  font-weight:bold;
  font-size:1.3em;
  border-radius:4px;
  border-style: solid;
  padding:0.1em;
}
}
