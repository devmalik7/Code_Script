let gameSeq=[];
let userSeq=[];
let started=false;
let level=0;
let btns=["yellow",'red','purple','green'];
let h2=document.querySelector('h2');
document.addEventListener("keypress",function(){
    if(started==false){
    console.log("game started");
    started=true;

    levelUp();
    }

})
function btnflash(btn){
    btn.classList.add("flash");
    setTimeout(function(){
        btn.classList.remove("flash");
    },700)
}

function levelUp(){
    userSeq=[];
    level++;
h2.innerText=`level${level}`;
let randcolor=btns[Math.floor(Math.random()*4)];
let btn=document.querySelector(`.${randcolor}`);
gameSeq.push(randcolor);
console.log(gameSeq);
btnflash(btn);
}


function btnpress(){
    btnflash(this);
    userSeq.push(this.getAttribute("id"));
    console.log(userSeq);
    checkAns(userSeq.length-1);
}
function checkAns(idx){
    
    if(userSeq[idx]===gameSeq[idx]){
        if(gameSeq.length==userSeq.length){
            setTimeout(()=>{levelUp()},1000);
        }
       
    }
    else{
        h2.innerHTML=`Game over! Score was <b>${level}</b><br>Press any key to restart`;
        document.querySelector("body").style.backgroundColor="red";
        setTimeout(()=>{
            document.querySelector("body").style.backgroundColor="white";},200);
        reset();
    }
}

let allBtns=document.querySelectorAll(".btn");
for(butns of allBtns){
    butns.addEventListener("click",btnpress);
}

function reset(){
    gameSeq=[];
    userSeq=[];
    started=false;
    level=0;
}