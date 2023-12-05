

setInterval(()=>{
    fetch("/api/changed")
   .then(response => response.json())
   .then(data =>{
       if(data.changed){
           window.location.reload();
       }
   })
},100)

