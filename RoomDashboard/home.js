window.onload = function(){
    
}

const luce = document.querySelectorAll("button")[0];
const tapparella = document.querySelectorAll("button")[1];
luce.addEventListener("click", function(){
    luce.getAttribute("value") == "on" ? luce.setAttribute("value", "off") : luce.setAttribute("value", "on");
    if(luce.getAttribute("value") == "on"){
        luce.setAttribute("value", "off");
        luce.style.backgroundColor = "red";
        
    }else{
        luce.setAttribute("value", "on");
        luce.style.backgroundColor = "green";

    }
});
tapparella.addEventListener("click", function(){
    const t=document.querySelector("input");

});