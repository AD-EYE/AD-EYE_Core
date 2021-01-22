var txtNewInputBox = document.createElement('div');

    // Then add the content (a new input box) of the element.
	txtNewInputBox.innerHTML = "<input type='text' id='newInputBox'>";

    // Finally put it where it is supposed to appear.
    document.getElementById("formelement").appendChild(txtNewInputBox);
    
    -------------------------------------------------------------------

    var down = document.getElementById("a"); 
            
                
                // Create a form synamically 
                var form = document.createElement("form"); 
                form.setAttribute("method", "post"); 
                form.setAttribute("action", "submit.php"); 
  
                // Create an input element for emailID 
                var ID = document.createElement("input"); 
                ID.setAttribute("type", "text"); 
                ID.setAttribute("name", "emailID"); 
                ID.setAttribute("placeholder", "E-Mail ID"); 
  
                // Create an input element for password 
                var PWD = document.createElement("input"); 
                PWD.setAttribute("type", "password"); 
                PWD.setAttribute("name", "password"); 
                PWD.setAttribute("placeholder", "Password"); 
  
                // Create a submit button 
                var s = document.createElement("input"); 
                s.setAttribute("type", "submit"); 
                s.setAttribute("value", "Submit"); 
  
                // Append the email_ID input to the form 
                form.append(ID);  
                
                // Append the password to the form 
                form.append(PWD);  
                
                // Append the button to the form 
                form.append(s);  
  
                document.getElementsByTagName("body").appendChild(form); 

                -----------------------------------



                var select = document.createElement("select");
    
    //select.class="searchw8";

    var option1 = document.createElement("option");
    option1.value="0";
    option1.selected="";
    option1.innerHTML= "off";

    var option2 = document.createElement("option");
    option2.value="1";
    option2.innerHTML= "rain";

    var option3 = document.createElement("option");
    option3.value="2";
    option3.innerHTML= "random";

    select.addChild(option1);
    select.addChild(option2);
    select.addChild(option3);
    //document.addChild(select);
    form.append(select);
    -------------------------------------

    
  var values = ["dog", "cat", "parrot", "rabbit"];
 
  var select = document.createElement("select");
  select.name = "pets";
  select.id = "pets"
 
  for (const val of values) {
    var option = document.createElement("option");
    option.value = val;
    option.text = val.charAt(0).toUpperCase() + val.slice(1);
    select.appendChild(option);
  }


















  -----------------------------------------------------

   //----------
            /* var titles  = [];
var names   = [];
var tickets = [];
 */

var titleInput  = document.getElementById("title");
var nameInput   = document.getElementById("name");
var ticketInput = document.getElementById("tickets");

var myArray = [ title, name, tickets ];


var messageBox  = document.getElementById("display");

function insert ( ) {
 titles.push( titleInput.value );
 names.push( nameInput.value );
 tickets.push( ticketInput.value );
  
 clearAndShow();
}

function clearAndShow () {
  // Clear our fields
  titleInput.value = "";
  nameInput.value = "";
  ticketInput.value = "";
  
  // Show our output
  messageBox.innerHTML = "";
  
  messageBox.innerHTML += "Titles: " + titles.join(", ") + "<br/>";
  messageBox.innerHTML += "Names: " + names.join(", ") + "<br/>";
  messageBox.innerHTML += "Tickets: " + tickets.join(", ");
}
//----------------

            for (var i=0; i<formElements.length; i++)
        if (formElements[i].type === "text")
        {
            storeData[formElements[i].name]=formElements[i].value;
        

            //storeData.state = formElements[0].options[formElements[0].selectedIndex].value;
            document.getElementById("x1").innerHTML = storeData[range_variance].value;
        }
    
    }

    

    /* function send_button_onClick()
    {
        var state =  
        var lastname =  $('#last1').val();
        var address =  $('#add1').val(); 
    var hour =  $('#hour1').val();

    storeData.firstname = firstname;
    storeData.lastname = lastname;
    storeData.address = address;
    storeData.hour = hour;    

    } */
