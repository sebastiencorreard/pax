%%% css commune autre que css euler et css particuliere %%%
\css{
<style>
.euler_quest_nobg {
    border-left:0.3em solid blue;
    border-radius:3px;
    padding:0.3em 0.3em 0.3em 0.5em;
    margin:0.3em 0;
}
.euler_rep_good_nobg {
    border-left:0.3em solid green;
    border-radius:3px;
    padding:0.3em 0.3em 0.3em 0.5em;
    margin:0.3em 0;
    margin-left:0.3em;
  
}  
.euler_answer_nobg {
    border-left:0.3em solid grey;
    border-radius:3px;
    padding:0.3em 0.3em 0.3em 0.5em;
    margin:0.3em 0;
    margin-left:0.3em;
}  
.euler_rep_bad_nobg {
    border-left:0.3em solid red;
    border-radius:3px;
    padding:0.3em 0.3em 0.3em 0.5em;
    margin-top: 0.3em;
    margin-bottom: 0.3em;
    margin-left:0.3em;
}
.tick:before{
  content : "\002713";
  color:#008000;
  font-weight:bold;
  font-size:1.3em;
}
.cross:before{
  content : "\002717";
  color:#b50000;
  font-weight:bold;
  font-size:1.3em;
}
div.tick::before, div.cross::before{
  font-size:2em;
  position: absolute;
  left: 0.2em;
  top: 0;
  height: 100%;
  display: grid;
  place-items: center;
  box-sizing:border-box;
}
div.tick,div.cross{
  position: relative;
  background-size: 100% 1px;
  background-repeat: no-repeat;
  background-position: 0 0;
  overflow: hidden;
  padding-left:2.5em;
}
.container {
  display: flex;
  flex-wrap:wrap;
  gap:1rem;
  align-items:center;
  justify-content: flex-start;
  }
.image-wrapper {
  flex: 0 1 auto;
  text-align: center;
  box-sizing: border-box;           
}
.table-wrapper {
  flex: 1 1 300px;      
  min-width: 300px;
  box-sizing: border-box;  
} 
.image-block {
  display: flex;
  flex-direction: column;
  align-items: center;
  gap: 0.5rem;    
}

.ui-accordion .ui-accordion-content{
  padding-left:1em;
  padding-right:1em;
 }
.highlight {
  background-color: #FFF9C4; 
  color: #333;   
  padding: 0.2em 0.4em; 
  border-radius: 0.2em; 
}
.legend-item span {
      line-height: 20px;
    }
.spacer {
  margin: 1em 0;
}
@media (max-width: 768px) {
    .container {
      flex-direction: column; 
    }
  }
</style>
#if defined TARGET_gant || defined TARGET_gim || defined TARGET_coef
<script>
#include "animation.inc"
</script>
#endif
}
