document.addEventListener('DOMContentLoaded', (event) => 
{
    var dragSourceEl = null;

    function handleDragStart(e) 
    {
        this.style.opacity = '0.4';
        dragSourceEl = this;
        e.dataTransfer.effectAllowed = 'move';
        e.dataTransfer.setData('text/html', this.innerHTML);
    }

    function handleDragOver(e) 
    {
        if (e.preventDefault) 
        {
            e.preventDefault();
        }
        e.dataTransfer.dropEffect = 'move';
        return false;
    }

    function handleDragEnter(e) 
    {
        this.classList.add('over');
    }

    function handleDragLeave(e) 
    {
        this.classList.remove('over');
    }

    function handleDrop(e) 
    {
        if (e.stopPropagation) 
        {
            e.stopPropagation(); // stops the browser from redirecting.
        }
        if (dragSourceEl != this) 
        {
            dragSourceEl.innerHTML = this.innerHTML;
            this.innerHTML = e.dataTransfer.getData('text/html');
        }
        return false;
    }

    function handleDragEnd(e) 
    {
        this.style.opacity = '1'; 
        items.forEach(function (item) 
        {
            item.classList.remove('over');
        });
    }

    let items = document.querySelectorAll('.container .box');
    items.forEach(function(item)
    {
        item.addEventListener('dragstart', handleDragStart, false);
        item.addEventListener('dragenter', handleDragEnter, false);
        item.addEventListener('dragover', handleDragOver, false);
        item.addEventListener('dragleave', handleDragLeave, false);
        item.addEventListener('drop', handleDrop, false);
        item.addEventListener('dragend', handleDragEnd, false);
    });
});


//------------------Connection with the bridge-------------------
    var ros = new ROSLIB.Ros({ url : 'ws://localhost:9090'});

    ros.on('connection', function() { document.getElementById("status").innerHTML = "Connected"; });

    ros.on('error', function(error) { document.getElementById("status").innerHTML = "Error"; });

    ros.on('close', function() { document.getElementById("status").innerHTML = "Closed"; });
//------------------Connection with the bridge-------------------

let green = "#699b2c";

//-------------------linear velocity----------------
    // listen to the topic /vehicle_cmd
    let velocity_listener = new ROSLIB.Topic({
        ros : ros,
        name : '/vehicle_cmd',
        messageType : 'autoware_msgs/VehicleCmd'
     });

    //subscribing to the topic /vehicle_cmd
    velocity_listener.subscribe(function(message)
    {
        let value = message.ctrl_cmd.linear_velocity;
        let max_gauge_speed = 10;
        const gauge_element = document.querySelector(".gauge_velocity");
        
        //shifting value by one decimal
        value = value / max_gauge_speed;

        // passing the value received from the topic /vehicle_cmd to the function to display the velocity of the car
        setGaugeValue(gauge_element,value);

        //function to set values of the gauge
        function setGaugeValue(gauge_velocity,value) 
        {
            //safety check to ensure that the values are within the range
            if (value < 0 || value > 1) 
            {
              return;
            }

            //making the turn over the gauge body
            gauge_velocity.querySelector(".gauge_velocity_fill").style.transform = `rotate(${value/3}turn)`;

            // to convert the value to km/hr from m/s
            value = (value * 180) / 5; 

            //printing the velocity value
            gauge_velocity.querySelector(".gauge_velocity_cover").textContent = `${Math.round(value)} km/h`;
        }
    });
//-------------------linear velocity----------------



//-------------------linear acceleration----------------
    //listen to the topic /vehicle_cmd
    let acceleration_listener = new ROSLIB.Topic({
        ros : ros,
        name : '/vehicle_cmd',
        messageType : 'autoware_msgs/VehicleCmd'
    });

    //subscribing to the topic /vehicle_cmd
    acceleration_listener.subscribe(function(message)
    {
        let value = message.ctrl_cmd.linear_acceleration;
        const gauge_element = document.querySelector(".gauge_acceleration");

        // passing the value received from the topic /vehicle_cmd to the function to display the acceleration of the car
        setGaugeValue(gauge_element, value);

        //function to set values of the gauge
        function setGaugeValue(gauge_acceleration, value) 
        {
            //safety check to ensure that values are within the range
            if (value < 0 || value > 1) 
            {
              return;
            }

            //making the turn over the gauge body
            gauge_acceleration.querySelector(".gauge_acceleration_fill").style.transform = `rotate( ${ value / 4 }turn )`;

            //printing the acceleration value
            gauge_acceleration.querySelector(".gauge_acceleration_cover").textContent = `${ Math.round( value * 10 ) } m/s²`;
        }
    });
//-------------------linear acceleration----------------



//-------------------Nominal Vs Safety Channel----------------
    //listen to the topic /switchCommand
    let data_listener = new ROSLIB.Topic({
        ros : ros,
        name : '/switchCommand',
        messageType : 'std_msgs/Int32'
    });

    //subscribing to the topic /switchCommand
    data_listener.subscribe(function(message) 
    {
        let channel_id = message.data;

        // array for postion:color pairs
        let positionColorPairs = Array({'position' : 00, 'color' : green},{'position' : 01, 'color' : green});
        let position = assignPosition(channel_id);
        assignColor(position);

        //function to change the color of buttons and reseting it to gray when not in use
        function assignColor(position)
        {
            let buttonList = document.getElementsByClassName('channel');
            let numOfButtons = buttonList.length;
            let buttonId = buttonList[position].id;
            for (let i = 0; i < numOfButtons; i++)
            {
                for (let j = 0; j < positionColorPairs.length; j++)
                {
                    if (positionColorPairs[j].position == buttonId)
                    {
                        buttonList[buttonId].style.backgroundColor = positionColorPairs[j].color;
                    }
                    else 
                    {
                        buttonList[i].style.backgroundColor  = 'gray';
                    }
                }
            }
        }

        //function to assign the position in the array based on the data value received
        function assignPosition(channel_id)
        {
            let position;
            if((channel_id == 0))
            {
                position = 0;
            }
            else if((channel_id == 1))
            {
                position = 1;
            }
            return position;
            
        }
    });
    
    // function to switch the channel on button click from nominal to safety and vice-versa 
    function toggleState_OnClick(channel)
    {
        if(channel.value == "off")
        {
            let dataToggleOn = new ROSLIB.Topic({
                ros : ros,
                name : '/switchCommand',
                messageType : 'std_msgs/Int32'
            });

            let dataOn = new ROSLIB.Message({
                data : 1
            });
            
            dataToggleOn.publish(dataOn);
        }
        else
        {
            let dataToggleOff = new ROSLIB.Topic({
                ros : ros,
                name : '/switchCommand',
                messageType : 'std_msgs/Int32'
            });

            let dataOff = new ROSLIB.Message({
                data : 0
            });

            dataToggleOff.publish(dataOff);
        }
    }
//-------------------Nominal Vs Safety Channel ----------------



//-------------------Manager State----------------
    //listen to the topic /manager/state
    let manager_listener = new ROSLIB.Topic({
        ros : ros,
        name : '/manager/state',
        messageType : 'std_msgs/Int8'
    });

    //subscribing to the topic /manager/state
    manager_listener.subscribe(function(message) 
    {
        let data = message.data;
        if(data === 0)
        {
            document.getElementById("state").innerHTML = "Initializing";
        }
        else if(data === 1)
        {
            document.getElementById("state").innerHTML = "Enabled";
        }
        else if(data === 2)
        {
            document.getElementById("state").innerHTML = "Engaged";
        }
        else if(data === 3)
        {
            document.getElementById("state").innerHTML = "Fault";
        }
        else
        {
            document.getElementById("state").innerHTML = "Unknown";
        }

    });

    // function to toggle the state on and off by clicking on the buttons.
    function toggleStateinitial_OnClick(initial)
    {
        let initialChecksTopic = new ROSLIB.Topic({
            ros : ros,
            name : '/initial_checks',
            messageType :'std_msgs/Bool'
        });
        
        if(initial.value == "off") 
        {
            initial.value = "on";
            let initialOn = new ROSLIB.Message({
                data : true
            });

            let stringData = (initialOn.data).toString();
            let data = stringData.toUpperCase();
            document.getElementById("initial").innerHTML = data;
            initialChecksTopic.publish(initialOn);
        }
        else
        {
            initial.value = "off";
            let initialOff = new ROSLIB.Message({
                data : false
            });

            let stringData = (initialOff.data).toString();
            let data = stringData.toUpperCase();
            document.getElementById("initial").innerHTML = data;
            initialChecksTopic.publish(initialOff);
        }
    }
    
    // function to toggle the state on and off by clicking on the buttons.
    function toggleStateactivation_OnClick(activation)
    {
        let activationRequestTopic = new ROSLIB.Topic({
            ros : ros,
            name : '/activation_request',
            messageType : 'std_msgs/Bool'
        });

        if(activation.value == "off") 
        {
            activation.value = "on";
            let activationOn = new ROSLIB.Message({
                data : true
            });

            let stringData = (activationOn.data).toString();
            let data = stringData.toUpperCase();
            document.getElementById("activation").innerHTML = data;
            activationRequestTopic.publish(activationOn);
        } 
        else
        {
            activation.value = "off";
            let activationOff = new ROSLIB.Message({
                data : false
            });

            let stringData = (activationOff.data).toString();
            let data = stringData.toUpperCase();
            document.getElementById("activation").innerHTML = data;
            activationRequestTopic.publish(activationOff);
        }
    }

    // function to toggle the state on and off by clicking on the buttons.
    function toggleStatefault_OnClick(fault)
    {
        let faultTopic = new ROSLIB.Topic({
            ros : ros,
            name : '/fault',
            messageType : 'std_msgs/Bool'
        });

        if(fault.value == "off") 
        {
            fault.value = "on";
            let faultOn = new ROSLIB.Message({
                data : true
            });

            let stringData = (faultOn.data).toString();
            let data = stringData.toUpperCase();
            document.getElementById("fault").innerHTML = data;
            faultTopic.publish(faultOn);
        } 
        else
        {
            fault.value = "off";
            let faultOff = new ROSLIB.Message({
                data : false
            });

            let stringData = (faultOff.data).toString();
            let data = stringData.toUpperCase();
            document.getElementById("fault").innerHTML = data;
            faultTopic.publish(faultOff);
        }
        
    }
//--------------------Manager State--------------



//-------------------tracked object ----------------
    //listen to the topic /tracked_objects 
    let track_listener = new ROSLIB.Topic({
        ros : ros,
        name : '/tracked_objects',
        messageType : 'autoware_msgs/DetectedObjectArray'
    });

    //subscribing to the topic /tracked_objects
    track_listener.subscribe(function(message) 
    {
        let object=[];
        let k=0;
        for (let i = 0; i < message.objects.length; i++) 
        {
            for (let j = 0; j < message.objects[i].label.length; j++) 
            {
                object[k]=message.objects[i].label[j];
                k++;
            }
            s = object.join("");
            document.getElementById("track").innerHTML = s;
            x = message.objects[0].pose.position.x;
            document.getElementById("x").innerHTML = x;
            y = message.objects[0].pose.position.y;
            document.getElementById("y").innerHTML = y;
            z = message.objects[0].pose.position.z
            document.getElementById("z").innerHTML = z;
            object.splice(0, object.length);
        }
    });
//-------------------tracked object ----------------



//---------------------behavior state--------------
    //listen to the topic /behavior_state
    var behavior_state_listener = new ROSLIB.Topic({
        ros : ros,
        name : '/behavior_state',
        messageType : 'visualization_msgs/MarkerArray'
    });

    //subscribing to the topic /behavior_state
    behavior_state_listener.subscribe(function(message) 
    {
        let marker = [];
        var k = 0;
        for (let i = 0; i < message.markers.length; i++) 
        {
            for (let j = 0; j < message.markers[i].text.length; j++) 
            {
                marker[k] = message.markers[i].text[j];
                k++;
            }
            t = marker.join("");
            document.getElementById("behavior").innerHTML = t;
            marker.splice(0, marker.length);
        }
    });
//--------------------behavior state---------------



//-----------------feature state-----------------
    //listen to the topic manager/features
    let feature_listener = new ROSLIB.Topic({
        ros : ros,
        name : 'manager/features',
        messageType : 'std_msgs/Int32MultiArray'
    });

    let data_array;

    //subscribing to the topic manager/features
    feature_listener.subscribe(function(message) 
    {
        data_array = message.data;

        // array for position:color pairs
        let strColorPairs = Array(
        {'position' : 0, 'color' : green},
        {'position' : 1, 'color' : green},
        {'position' : 2, 'color' : green},
        {'position' : 3, 'color' : green},
        {'position' : 4, 'color' : green},
        {'position' : 5, 'color' : green},
        {'position' : 6, 'color' : green},
        {'position' : 7, 'color' : green},
        {'position' : 8, 'color' : green},
        {'position' : 9, 'color' : green},
        {'position' : 10, 'color' : green},
        {'position' : 11, 'color' : green});
        
        // array to get postions with the data value 1
        let position = new Array();
        position = checkPosition(data_array);
        colorBox(position);
        

        //function to change the color of button and reseting it to gray when not in use
        function colorBox(position)
        {
            let divList = document.getElementsByClassName('features');
            let i, n = divList.length;
                
            for (p=0; p<position.length; p++)
            {
                curContent = divList[position[p]].id;
                for (i=0; i<n; i++)
                {
                    for (j=0; j<strColorPairs.length; j++)
                    {
                        if (strColorPairs[j].position !== curContent)
                        {
                            divList[curContent].style.backgroundColor  = strColorPairs[j].color;
                        }
                        else 
                        {
                            divList[i].style.backgroundColor  = 'gray';
                        }
                    }
                }
            }
        }

        //function to check the positions of the features to be enabled based on the data array value received from the topic manager/features
        function checkPosition(data_array)
        {
            let dataon = [];
            for (let i = 0; i < data_array.length; i++)
            {
                if (data_array[i] === 1)
                {
                    dataon.push(i);
                }
            }
            return dataon;
        }
    });
//-----------------feature state-----------------



//-------------------- feature Change---------------
    // function to toggle fetaures on and off on button click.
    function toggleFeatureState_OnClick(feature)
    {
        let features = document.getElementsByClassName("features");
        let featureToggleOff = new ROSLIB.Topic({
            ros : ros,
            name : '/Features_state',
            messageType : 'std_msgs/Int32MultiArray'
        });
        let featureOff = new ROSLIB.Message({
            data : data_array 
        });
        for(let i = 0; i < features.length; i++)
        {
            if(feature.id == i)
            {
                if(featureOff.data[i] == 1)
                {
                    featureOff.data[i] = 0; 
                }
                else
                {
                    featureOff.data[i] = 1; 
                }
            }
        }
        featureToggleOff.publish(featureOff);
    }  
//-------------------- feature Change---------------


//-------------fault injection----------------------

function create_forms()
{
    // forms for lidar
    let lidar1_form = document.getElementById("lidar1_form");
    let lidar2_form = document.getElementById("lidar2_form");
    lidar2_form.innerHTML = lidar1_form.innerHTML;
    
    //lidar2_form_send.onclick("lidar2_parameter_values()");
    let lidar3_form = document.getElementById("lidar3_form")
    lidar3_form.innerHTML = lidar1_form.innerHTML;
    let lidar4_form = document.getElementById("lidar4_form");
    lidar4_form.innerHTML = lidar1_form.innerHTML;

    // forms for camera
    let camera1_form = document.getElementById("camera1_form");
    let camera2_form = document.getElementById("camera2_form");
    camera2_form.innerHTML = camera1_form.innerHTML;
    let tl_camera_form = document.getElementById("tl_camera_form");
    tl_camera_form.innerHTML = camera1_form.innerHTML;
}
    
function faultInjection_OnClick(button)
{
    formsCollection = document.getElementsByTagName("form");
    for(let i = 0; i < formsCollection.length; i++)
    {
        if(button.name == formsCollection[i].name)
        {
            if(button.value == "off")
            {
                button.value = "on";
                button.style.backgroundColor = green;
                formsCollection[i].style.display = "block";
                document.getElementById("form_display").append(formsCollection[i]);
            }
            else
            {
                button.value = "off";
                button.style.backgroundColor = "gray";
                formsCollection[i].style.display = "none";
            }
            
        }
    }      
}

let gnss_array = new Array();
// function to collect the values of gnss parameters from the form and put them in an array
function gnss_parameter_values()
    {
        let gnss_form = document.getElementById("gnss_form");
        let gnss_state = document.getElementById("gnss_state");
        let gnss_input = document.getElementById("gnss_input");
        
        // values are collected from form and kept in an array
        for (let i=0;i<gnss_form.length-1;i++)
        {
            gnss_array[i] = gnss_form[i].value;
        }

        // coverting the string array to float array as we need float data to publish
        for (let i=0;i<gnss_array.length;i++)
        {
            gnss_array[i] = parseFloat(gnss_array[i]);
        }

        // To display the selected value of dropdown in the textbox beside the button
        let selected_value = gnss_state.options[gnss_state.selectedIndex].text;
        gnss_input.value = selected_value;
        
        // publishing the data from the form to gnss fault injection topic 
        publish_fault_injection(0);
        /* fault_injection_topic = new ROSLIB.Topic({
            ros : ros,
            name :'/fault_injection/gnss',
            messageType : 'std_msgs/Float64MultiArray'
        });

        fault_injection_msg = new ROSLIB.Message({
            data : gnss_array
        });

        fault_injection_topic.publish(fault_injection_msg);  */
    }

    let lidar1_array = new Array();
    let lidar2_array = new Array(); 
    let lidar3_array = new Array(); 
    let lidar4_array = new Array(); 

    // function to collect the values of lidar parameters from the form and put them in an array
     function lidar_parameter_values()
    {
        let lidar1_form = document.getElementById("lidar1_form");
        let lidar2_form = document.getElementById("lidar2_form");
        let lidar3_form = document.getElementById("lidar3_form");
        let lidar4_form = document.getElementById("lidar4_form");
        let form_array = new Array("lidar1_form","lidar2_form","lidar3_form","lidar4_form");
        //form_array.push(lidar1_form);
        //("lidar1_form","lidar2_form","lidar3_form","lidar4_form");

        let lidar_state = document.getElementById("lidar_state");
        let lidar1_input = document.getElementById("lidar1_input");
        let lidar2_input = document.getElementById("lidar2_input");
        let lidar3_input = document.getElementById("lidar3_input");
        let lidar4_input = document.getElementById("lidar4_input");
//        let input = document.getElementsByTagName("input");
       
        for (let i = 0; i < form_array.length; i++)
        {
            switch(form_array[i])
            {
                case "lidar1_form":
                    document.getElementById("x1").innerHTML = "test2";
                    // values are collected from form and kept in an array
                    for (let i = 0; i < lidar1_form.length-1; i++)
                    {
                        lidar1_array[i] = lidar1_form[i].value;
                    }

                    // coverting the string array to float array as we need float data to publish
                    for (let i = 0; i < lidar1_array.length; i++)
                    {
                        lidar1_array[i] = parseFloat(lidar1_array[i]);
                    }

                    // To display the selected value of dropdown in the textbox beside the button
                    selected_value = lidar_state.options[lidar_state.selectedIndex].text;
                    lidar1_input.value = selected_value;

                    // publishing the data from the form to gnss fault injection topic 
                    publish_fault_injection(1);
                    break;

                case "lidar2_form":
                    document.getElementById("x1").innerHTML = "test";

                    // values are collected from form and kept in an array
                    for (let i = 0; i < lidar2_form.length-1; i++)
                    {
                        lidar2_array[i] = lidar2_form[i].value;
                    }

                    // coverting the string array to float array as we need float data to publish
                    for (let i = 0; i < lidar2_array.length; i++)
                    {
                        lidar2_array[i] = parseFloat(lidar2_array[i]);
                    }

                    // To display the selected value of dropdown in the textbox beside the button
                    selected_value = lidar_state.options[lidar_state.selectedIndex].text;
                    lidar2_input.value = selected_value;

                    // publishing the data from the form to gnss fault injection topic 
                    publish_fault_injection(2);
                    break;

                case "lidar3_form":

                    // values are collected from form and kept in an array
                    for (let i = 0; i < lidar3_form.length-1; i++)
                    {
                        lidar3_array[i] = lidar3_form[i].value;
                    }

                    // coverting the string array to float array as we need float data to publish
                    for (let i = 0; i < lidar3_array.length; i++)
                    {
                        lidar3_array[i] = parseFloat(lidar3_array[i]);
                    }

                    // To display the selected value of dropdown in the textbox beside the button
                    selected_value = lidar_state.options[lidar_state.selectedIndex].text;
                    lidar3_input.value = selected_value;

                    // publishing the data from the form to gnss fault injection topic 
                    publish_fault_injection(3);
                    break;

            }
        }  
       
        // coverting the string array to float array
        /* for (let i = 0; i < lidar1_array.length; i++)
        {
            lidar1_array[i] = parseFloat(lidar1_array[i]);
        } */
       
        // To display the selected value of dropdown in the textbox
        /* for(var i = 0; i < input.length; i++)
        {
            if(input[i].type.toLowerCase() == "text")
            {
                selected_value = lidar_state.options[lidar_state.selectedIndex].text;
                lidar1_input.value = selected_value;
            }
        } */
       /*  let lidar_topics_array = new Array("/fault_injection/lidar1","/fault_injection/lidar2","/fault_injection/lidar3","/fault_injection/lidar4");
        let lidar_parameters_array = new Array();
        lidar_parameters_array[0] = lidar1_array;
        lidar_parameters_array[1] = lidar2_array;

        document.getElementById("x1").innerHTML = lidar_parameters_array[0][1];
        //lidar_parameters_array.push(lidar2_array);

 for (let i = 0; i < lidar_topics_array.length; i++)
       {
            fault_injection_topic = new ROSLIB.Topic({
                ros : ros,
                name : lidar_topics_array[i],
                messageType : 'std_msgs/Float64MultiArray'
            });
        }
            
            for (let i = 0; i < lidar_topics_array.length; i++)
            {
                fault_injection_msg = new ROSLIB.Message({
                    data : lidar_parameters_array[i]
                });
            }
            
    
            fault_injection_topic.publish(fault_injection_msg);  */
 
        
        
        

     }
     

    function publish_fault_injection(i)
    {
        let lidar_topics_array = new Array("/fault_injection/gnss","/fault_injection/lidar1","/fault_injection/lidar2","/fault_injection/lidar3","/fault_injection/lidar4");
        let lidar_parameters_array = new Array();
        lidar_parameters_array[0] = gnss_array;
        lidar_parameters_array[1] = lidar1_array;
        lidar_parameters_array[2] = lidar2_array;

        let fault_injection_topic = new ROSLIB.Topic({
            ros : ros,
            name : lidar_topics_array[i],
            messageType : 'std_msgs/Float64MultiArray'
            });
                    
        let fault_injection_msg = new ROSLIB.Message({
            data : lidar_parameters_array[i]
            });
    
        fault_injection_topic.publish(fault_injection_msg);

    }
     

    /* let lidar2_array = new Array();
    function lidar2_parameter_values()
    {
        let lidar2_form = document.getElementById("lidar2_form");
        let lidar_state = document.getElementById("lidar_state");
        let lidar2_input = document.getElementById("lidar2_input");
        let input = document.getElementsByTagName("input");
       
        for (let i = 0; i < lidar2_form.length-1; i++)
        {
            lidar2_array[i] = lidar2_form[i].value;
        }
       
        // coverting the string array to float array
        for (let i = 0; i < lidar2_array.length; i++)
        {
            lidar2_array[i] = parseFloat(lidar2_array[i]);
        }
       
        // To display the selected value of dropdown in the textbox
        for(var i = 0; i < input.length; i++)
        {
            if(input[i].type.toLowerCase() == "text")
            {
                selected_value = lidar_state.options[lidar_state.selectedIndex].text;
                lidar2_input.value = selected_value;
            }
        }
        
        fault_injection_topic = new ROSLIB.Topic({
            ros : ros,
            name :'/fault_injection/lidar2',
            messageType : 'std_msgs/Float64MultiArray'
        });

        fault_injection_msg = new ROSLIB.Message({
            data : lidar2_array
        });

        fault_injection_topic.publish(fault_injection_msg); 
    } */
//-------------fault injection----------------




//-------------------camera 1 display ----------------

    //listen to the topic camera_1/image_raw
    let camera1_topic = new ROSLIB.Topic({
        ros : ros,
        name : '/camera_1/image_raw',
        messageType : 'sensor_msgs/Image'
    });

    //subscribing to the topic camera_1/image_raw
    camera1_topic.subscribe(function(message)
    {  
        let msg = atob(message.data);
        let array = new Uint8Array(new ArrayBuffer(msg.length));
        for (let i = 0; i < msg.length; i++) 
        {
            array[i] = msg.charCodeAt(i);
        }
        
        let canvas1 = document.getElementById( "camera1_canvas" );
        const context = canvas1.getContext( "2d" ); 

        let imgData = context.createImageData(960,720);
        for(let j = 0; j < array.length; j++)
        {
            imgData.data[ 4 * j + 0 ] = array[ 3 * j + 0 ];
            imgData.data[ 4 * j + 1 ] = array[ 3 * j + 1 ];
            imgData.data[ 4 * j + 2 ] = array[ 3 * j + 2 ];
            imgData.data[ 4 * j + 3 ] = 255;
        }
        
       var image = document.getElementById("camera1_canvas");
       image.style.width = "100%";
       image.style.height = "auto";
       context.putImageData(imgData,0,0,0,0,canvas1.width,canvas1.height);
    
    }); 
//-------------------camera 1 display ----------------



//-------------------camera 2 display ----------------

    //listen to the topic camera_2/image_raw
    let camera2_topic = new ROSLIB.Topic({
        ros : ros,
        name : '/camera_2/image_raw',
        messageType : 'sensor_msgs/Image'
    });

    //subscribing to the topic camera_1/image_raw
    camera2_topic.subscribe(function(message)
    {  
        let msg = atob(message.data);
        let array = new Uint8Array(new ArrayBuffer(msg.length));
        for (let i = 0; i < msg.length; i++) 
        {
            array[i] = msg.charCodeAt(i);
        }

        let canvas2 = document.getElementById( "camera2_canvas" );
        const context = canvas2.getContext( "2d" ); 

        let imgData = context.createImageData(canvas2.width,canvas2.height);
        for(let j = 0; j < array.length; j++)
        {
            imgData.data[ 4 * j + 0 ] = array[ 3 * j + 0 ];
            imgData.data[ 4 * j + 1 ] = array[ 3 * j + 1 ];
            imgData.data[ 4 * j + 2 ] = array[ 3 * j + 2 ];
            imgData.data[ 4 * j + 3 ] = 255;
        }

        let image = document.getElementById("camera2_canvas");
        image.style.width = "100%";
        image.style.height = "auto";
        context.putImageData(imgData,0,0,0,0,canvas2.width,canvas2.height);
}); 
//-------------------camera 2 display --------------


//-------------------TL camera  display ----------------

    //listen to the topic /tl/image_raw
    let tl_camera_topic = new ROSLIB.Topic({
        ros : ros,
        name : '/tl/image_raw',
        messageType : 'sensor_msgs/Image'
    });

    //subscribing to the topic /tl/image_raw
    tl_camera_topic.subscribe(function(message)
    {  
        let msg = atob(message.data);
        let array = new Uint8Array(new ArrayBuffer(msg.length));
        for (let i = 0; i < msg.length; i++) 
        {
            array[i] = msg.charCodeAt(i);
        }

        let canvas3 = document.getElementById( "tl_camera_canvas" );
        const context = canvas3.getContext( "2d" ); 

        let imgData = context.createImageData(canvas3.width,canvas3.height);
        for(let j = 0; j < array.length; j++)
        {
            imgData.data[ 4 * j + 0 ] = array[ 3 * j + 0 ];
            imgData.data[ 4 * j + 1 ] = array[ 3 * j + 1 ];
            imgData.data[ 4 * j + 2 ] = array[ 3 * j + 2 ];
            imgData.data[ 4 * j + 3 ] = 255;
        }

        let image = document.getElementById("tl_camera_canvas");
        image.style.width = "100%";
        image.style.height = "auto";
        context.putImageData(imgData,0,0,0,0,canvas3.width,canvas3.height);
}); 
//------------------- TL camera  display --------------


//---------------------List of Topics-----------------------
function getTopics() 
{
    var topicsClient = new ROSLIB.Service({
    ros : ros,
    name : '/rosapi/topics',
    serviceType : 'rosapi/Topics'
    });

    let request = new ROSLIB.ServiceRequest();
    topicsClient.callService(request, function(result) 
    {
        let topics_list = result.topics;
        let select = document.getElementById("select_topic");
        let topics_array = Object.values(topics_list); 
        for(var i = 0; i < topics_array.length; i++)
        {
            let value = topics_array[i];
            let option = document.createElement("option");
            option.textContent = value;
            select.appendChild(option);
        }
        let topic_data = document.getElementById("topic_data_textbox");
        for(let i = 0; i < topics_array.length; i++)
        { 
            // Subscribing to a Topic
            var listener = new ROSLIB.Topic({
            ros : ros,
            name : topics_array[i],
            messageType : 'std_msgs'
            });

            listener.subscribe(function(message) {
            listener.unsubscribe();
            });
        }  
        
    });
}
/* ROSLIB.Ros.prototype.callOnConnection = function(message) {
    var that = this;
    var messageJson = JSON.stringify(message);
  
    if (!this.socket || this.socket.readyState !== WebSocket.OPEN) {
      that.once('connection', function() {
        that.socket.send(messageJson);
      });
    } else {
      that.socket.send(messageJson);
    }
  }; */

 
/* ROSLIB.Ros.prototype.getTopics = function(callback) {
    var topicsClient = new ROSLIB.Service({
      ros : this,
      name : '/rosapi/topics',
      serviceType : 'rosapi/Topics'
    });
  
    var request = new ROSLIB.ServiceRequest();
  
    topicsClient.callService(request, function(result) {
      callback(result.topics);
    });
  }; 
  document.getElementById("topics").innerHTML = "hello";
 */
//---------------------List of Topics-----------------------
        



//-----------------code------------------
// let formElements = new Array();
// let result = new Array();


//     // function to reset the dropdown list to off value and to change the color of button based on the values on/off
//     function faultInjection_OnClick(button_element)
//     {
//         let selected_element = document.getElementsByClassName("selected");
        
//         for( let i = 0; i < selected_element.length; i++)
//         {
//             if(button_element.name == selected_element[i].name)
//             {
//                 document.getElementById("a").innerHTML = " ";
//                 if(button_element.value == "off")
//                 {
//                     button_element.value = "on";
//                     button_element.style.backgroundColor = green;
//                     selected_element[i].selectedIndex = 0;
//                     /* let gnss_form = document.getElementById("gnss_form");
//                     gnss_form.style.display = "block"; */
                    

//             //form.append(lidar_div.firstElementChild);
//                     switch(button_element.name)
//                     {
//                         case "gnss":
//                             //gnssForm(button_element);
//                             let gnss_form = document.getElementById("gnss_div_form");
//                             gnss_form.style.display = "block";
//                             break;
//                         case "lidar1":
//                             let lidar_div = document.getElementById(button_element.parentElement.id);
//                             lidar_div.lastElementChild.style.display = "none";
//                             form1 = lidarForm(button_element,lidar_div.firstElementChild);
//                             break;
//                         case "lidar2":
//                             lidarForm(button_element,lidar_div.firstElementChild);
//                             break;
//                         case "lidar3":
//                             lidarForm(button_element,lidar_div.firstElementChild);
//                             break;
//                         case "lidar4":
//                             lidarForm(button_element,lidar_div.firstElementChild);
//                             break;
//                         case "radar":
//                             radarForm();
//                             break;
//                         case "camera_1":
//                             cameraForm();
//                             break;
//                         case "camera_2":
//                             cameraForm();
//                             break;
//                         case "tl_camera":
//                             cameraForm();
//                             break;        
//                     }
                 
                    
                   
//                 }
//                 else
//                 {
//                     button_element.value = "off";
//                     button_element.style.backgroundColor = "gray";
//                     selectlet gnss_array = new Array();
    // function gnss_parameter_values()
    // {
    //     let gnss_form = document.getElementById("gnss_form");
    //     for (let i=0;i<gnss_form.length;i++)
    //         {
    //           gnss_array[i] = gnss_form[i].value;
    //         }
    //         document.getElementById("x1").innerHTML = gnss_array;
    //         //gnss_array[0] = gnss_form[1].options[gnss_form[1].selectedIndex].index;
            

    // }

    
    // //function to assign labels to lidar fault injection parameters
    // function lidar_fault_injection_label(i)
    // {
    //     let lidar_fault_injection_labels_array = new Array("State","random/range_variance","random/theta_variance","rain/rain_intensity","rain/a","rain/b","rain/reflectivity","rain/max_range");
    //     let lidar_label = document.createElement("label");
    //     lidar_label.innerHTML = lidar_fault_injection_labels_array[i];
    //     return lidar_label;
    // }
    
    // //function to create a feild in the form for lidar fault injection parameter
    // function lidar_fault_injection_parameters(i)
    // {
    //     let lidar_fault_injection_parameters_array = new Array("random/range_variance","random/theta_variance","rain/rain_intensity","rain/a","rain/b","rain/reflectivity","rain/max_range");
    //     let parameter_default_values_array = new Array("0.0001","0.0001","7.5","0.01","0.6","0.9","100");
    //     let lidar_parameter = document.createElement("input"); 
    //     lidar_parameter.setAttribute("id",lidar_fault_injection_parameters_array[i]);
    //     lidar_parameter.setAttribute("type", "text"); 
    //     lidar_parameter.setAttribute("name", lidar_fault_injection_parameters_array[i]); 
    //     lidar_parameter.setAttribute("placeholder", lidar_fault_injection_parameters_array[i]); 
    //     lidar_parameter.setAttribute("value",parameter_default_values_array[i]);
    //     return lidar_parameter;
    // }

    

    // // function for creating a form for lidar fault injection parameters.
    // function lidarForm(button_element,lidar_div)
    // {
    //    // let storeData = new Array();
        
    //     // create a form dynamically 
    //     let form = document.createElement("form"); 
    //     form.setAttribute("id", "lidar_parameters");

    //     //--------- state parameter of lidar fault injection ----------

    //         // label for state parameter of fault injection
    //         let state_label = lidar_fault_injection_label(0);

    //         // drop down element to select the value for state parameter of fault injection.
    //         let values = ["Off", "Random","Rain"];
    //         let state_drop_down = document.createElement("select");
    //         state_drop_down.setAttribute("id","State");

    //         for (const val of values) 
    //         {
    //             var option = document.createElement("option");
    //             option.text = val;
    //             state_drop_down.append(option);
    //         }
            
    //         // create span element for accepting the input for state parameter of fault injection
    //         let state_span = document.createElement("span");
            
    //         // adding the label and drop down of state parameter to state_span element
    //         state_span.append(state_label);
    //         state_span.append(" ");
    //         state_span.append(state_drop_down); 
            
 
    //     //--------- state parameter of lidar fault injection ----------

    //     //---------  random/range_variance parameter of lidar fault injection ----------

    //         // label for random/range_variance parameter of fault injection
    //         let range_variance_label = lidar_fault_injection_label(1);

    //         // Create an input element for random/range_variance
    //         let range_variance_parameter = lidar_fault_injection_parameters(0);

    //         // create span element for accepting the input for random/range_variance parameter of fault injection
    //         let range_variance_span = document.createElement("span");

    //         // adding the label and text feild of random/range_variance parameter to range_variance_span element
    //         range_variance_span.append(range_variance_label);
    //         range_variance_span.append("  ");
    //         range_variance_span.append(range_variance_parameter);
 
    //     //---------  random/range_variance parameter of lidar fault injection ----------

    //     //---------  random/theta_variance parameter of lidar fault injection ----------

    //         // label for random/theta_variance parameter of fault injection
    //         let theta_variance_label = lidar_fault_injection_label(2);
            
    //         // Create an input element for random/theta_variance
    //         let theta_variance_parameter = lidar_fault_injection_parameters(1);

    //         // create span element for accepting the input for random/theta_variance parameter of fault injection
    //         let theta_variance_span = document.createElement("span");

    //         // adding the label and text feild of random/theta_variance parameter to theta_variance_span element
    //         theta_variance_span.append(theta_variance_label);
    //         theta_variance_span.append(" ");
    //         theta_variance_span.append(theta_variance_parameter);

    //     //---------  random/theta_variance parameter of lidar fault injection ----------

    //     //---------  rain/rain_intensity parameter of lidar fault injection ----------

    //         // label for rain/rain_intensity parameter of fault injection
    //         let rain_intensity_label = lidar_fault_injection_label(3); 

    //         // Create an input element for rain/rain_intensity
    //         let rain_intensity_parameter = lidar_fault_injection_parameters(2);

    //         // create span element for accepting the input for rain/rain_intensity parameter of fault injection
    //         let rain_intensity_span = document.createElement("span");

    //         // adding the label and text feild of rain/rain_intensity parameter to rain_intensity_span element
    //         rain_intensity_span.append(rain_intensity_label);
    //         rain_intensity_span.append(" ");
    //         rain_intensity_span.append(rain_intensity_parameter);
        
    //     //---------  rain/rain_intensity parameter of lidar fault injection ----------

    //     //---------  rain/a parameter of lidar fault injection ----------

    //         // label for rain/a parameter of fault injection
    //         let rain_a_label = lidar_fault_injection_label(4); 

    //         // Create an input element for rain/a
    //         let rain_a_parameter = lidar_fault_injection_parameters(3);

    //         // create span element for accepting the input for rain/a parameter of fault injection
    //         let rain_a_span = document.createElement("span");

    //         // adding the label and text feild of rain/a parameter to rain_intensity_span element
    //         rain_a_span.append(rain_a_label);
    //         rain_a_span.append(" ");
    //         rain_a_span.append(rain_a_parameter);

    //     //---------  rain/a parameter of lidar fault injection ----------

    //     //---------  rain/b parameter of lidar fault injection ----------

    //         // label for rain/b parameter of fault injection
    //         let rain_b_label = lidar_fault_injection_label(5);

    //         // Create an input element for rain/b
    //         let rain_b_parameter = lidar_fault_injection_parameters(4);

    //         // create span element for accepting the input for rain/b parameter of fault injection
    //         let rain_b_span = document.createElement("span");

    //         // adding the label and text feild of rain/b parameter to rain_intensity_span element
    //         rain_b_span.append(rain_b_label);
    //         rain_b_span.append(" ");
    //         rain_b_span.append(rain_b_parameter);

    //     //---------  rain/b parameter of lidar fault injection ----------

    //     //---------  rain/reflectivity parameter of lidar fault injection ----------
        
    //         // label for rain/reflectivity parameter of fault injection
    //         let reflectivity_label = lidar_fault_injection_label(6); 

    //         // Create an input element for rain/reflectivity
    //         let reflectivity_parameter = lidar_fault_injection_parameters(5);

    //         // create span element for accepting the input for rain/reflectivity parameter of fault injection
    //         let reflectivity_span = document.createElement("span");

    //         // adding the label and text feild of rain/reflectivity parameter to reflectivity_span element
    //         reflectivity_span.append(reflectivity_label);
    //         reflectivity_span.append(" ");
    //         reflectivity_span.append(reflectivity_parameter);
            
    //     //---------  rain/reflectivity parameter of lidar fault injection ----------

    //     //---------  rain/max_range parameter of lidar fault injection ----------

    //         // label for rain/max_range parameter of fault injection
    //         let max_range_label = lidar_fault_injection_label(7); 

    //         // Create an input element for rain/max_range
    //         let max_range_parameter = lidar_fault_injection_parameters(6);

    //         // create span element for accepting the input for rain/max_range parameter of fault injection
    //         let max_range_span = document.createElement("span");

    //         // adding the label and text feild of rain/max_range parameter to reflectivity_span element
    //         max_range_span.append(max_range_label);
    //         max_range_span.append(" ");
    //         max_range_span.append(max_range_parameter);

    //     //---------  rain/max_range parameter of lidar fault injection ----------    

    //         // Create a send button 
    //         let send = document.createElement("input");
    //         send.setAttribute("id","send_button"); 
    //         send.setAttribute("type", "submit"); 
    //         send.setAttribute("value", "Send");
    //        // send_button.addEventListener("click", insert);
    //         //send.setAttribute("onclick",insert(form));

            
    //         //myFunction(button_element,form);
    //         //let lidar_div = document.getElementById(button_element.parentElement.id);
    //         //lidar_div.lastElementChild.style.display = "none";
    //         form.append(lidar_div); 

    //     // Append the state to the form 
    //     form.append(state_span);  

    //     // Append the random_range_variance to the form 
    //     form.append(range_variance_span); 

    //     // Append the random_theta_variance to the form 
    //     form.append(theta_variance_span); 
        
    //     // Append the rain_rain_intensity to the form 
    //     form.append(rain_intensity_span);

    //     // Append the rain_a to the form 
    //     form.append(rain_a_span);

    //     // Append the rain_b to the form 
    //     form.append(rain_b_span);

    //     // Append the rain_reflectivity to the form 
    //     form.append(reflectivity_span);

    //     // Append the rain_max_range to the form
    //     form.append(max_range_span);

    //     // Append the button to the form 
    //     form.append(send);  

    //     document.getElementById("a").appendChild(form);

    //     }

    //     function insert(form1)
    //     {
    //         let form_element = document.getElementById("lidar_parameters");
    //          for (let i=0;i<form_element.length;i++)
    //         {
              
    //           formElements[i] = form_element[i].value;
    //           formElements[1] = form_element[1].options[form_element[1].selectedIndex].index;
    //         }
    //         //document.getElementById("x1").innerHTML = formElements;
    //         return formElements; 
    //     }  

    //     let data_value = new Array();
    //     //data_value = result;
       
    // function publish_fault_injection(fault_injection,topic,result)
    // {
    //     let fault_injection_button = document.getElementsByClassName("selected");
    //     for( let i = 0; i < fault_injection_button.length; i++)
    //     {   
    //         if(fault_injection.name === fault_injection_button[i].name)
    //         {
    //             let option = fault_injection_button[i].options[fault_injection_button[i].selectedIndex];
    //             //data_value = fault_injection_button[i].value;
    //             data_value.push(...result);
    //             //data_value = formElements;
    //             if((option.value) != 0)
    //             {
    //                 let fault_injection_topic = new ROSLIB.Topic({
    //                     ros : ros,
    //                     name : topic,
    //                     messageType : 'std_msgs/Float64MultiArray'
    //                 });
                
    //                 let fault_injection_msg = new ROSLIB.Message({
    //                     data : parseFloat(data_value)
    //                 });

    //                 fault_injection_topic.publish(fault_injection_msg);
    //                 //document.getElementById("x1").innerHTML = "hello";
    //             }
    //         }
    //     }
    // }
    
    // // function to switch on fault_injection on value change of dropdown and publishing the message on to topic fault_injection/gnss
    // function faultInjectionGnss_OnChange(gnss)
    // {
    //     let topic = "/fault_injection/gnss";
    //     publish_fault_injection(gnss,topic);
    //     //document.getElementById("x1").innerHTML = "hello";
    // }

    // // function to switch on fault_injection on value change of dropdown and publishing the message on to topic fault_injection/lidar1
    // function faultInjectionLidar1_OnChange(lidar1)
    // {
    //     let form = document.getElementById("lidar_parameters");
    //     let result = insert(form);
    //    // document.getElementById("x1").innerHTML = result;
    //     let topic = "/fault_injection/lidar1";
    //     publish_fault_injection(lidar1,topic,result);
    // }

    // // function to switch on fault_injection on value change of dropdown and publishing the message on to topic fault_injection/lidar2
    // function faultInjectionLidar2_OnChange(lidar2)
    // {
    //     let topic = "/fault_injection/lidar2";
    //     publish_fault_injection(lidar2,topic);
    // }

    // // function to switch on fault_injection on value change of dropdown and publishing the message on to topic fault_injection/lidar3
    // function faultInjectionLidar3_OnChange(lidar3)
    // {
    //     let topic = "/fault_injection/lidar3";
    //     publish_fault_injection(lidar3,topic);
    // }

    // // function to switch on fault_injection on value change of dropdown and publishing the message on to topic fault_injection/lidar4
    // function faultInjectionLidar4_OnChange(lidar4)
    // {
    //     let topic = "/fault_injection/lidar4";
    //     publish_fault_injection(lidar4,topic);
    // }

    // // function to switch on fault_injection on value change of dropdown and publishing the message on to topic fault_injection/radar
    // function faultInjectionRadar_OnChange(radar)
    // {
    //     let topic = "/fault_injection/radar";
    //     publish_fault_injection(radar,topic);
    // }

    // // function to switch on fault_injection on value change of dropdown and publishing the message on to topic fault_injection/camera1
    // function faultInjectionCamera1_OnChange(camera1)
    // {
    //     let topic = "/fault_injection/camera1";
    //     publish_fault_injection(camera1,topic);
    // }

    // // function to switch on fault_injection on value change of dropdown and publishing the message on to topic fault_injection/camera2
    // function faultInjectionCamera2_OnChange(camera2)
    // {
    //     let topic = "/fault_injection/camera2";
    //     publish_fault_injection(camera2,topic);
    // }

    // // function to switch on fault_injection on value change of dropdown and publishing the message on to topic fault_injection/tl_camera
    // function faultInjectionTlCamera_OnChange(tl_camera)
    // {
    //     let topic = "/fault_injection/tl_camera";
    //     publish_fault_injection(tl_camera,topic);
    // } 
    
   /*  function fault_injection_parameters()
{
    let form_array = new Array("gnss_form","lidar1_form","lidar2_form","lidar3_form","lidar4_form","radar_form","camera_form");
    let state_array = new Array("gnss_state","lidar_state","radar_state","camera_state");
    let input_array = new Array("gnss_input","lidar1_input","lidar2_input","lidar3_input","lidar4_input","radar_input","camera1_input","camera2_input","tl_camera_input")
    
    for (let i = 0;i < form_array.length-1;i++)
    {
        gnss_array[i] = form_array[i].value;
    }

    // coverting the string array to float array
    for (let i = 0;i < form_array.length;i++)
    {
        gnss_array[i] = parseFloat(gnss_array[i]);
    }

    // To display the selected value of dropdown in the textbox
    for(var i = 0; i < input_array.length; i++)
    {
        selected_value = state_array[i].options[state_array[i].selectedIndex].text;
        input_array[i].value = selected_value;
    }

    fault_injection_topic = new ROSLIB.Topic({
        ros : ros,
        name :'/fault_injection/gnss',
        messageType : 'std_msgs/Float64MultiArray'
    });

    fault_injection_msg = new ROSLIB.Message({
        data : gnss_array
    });

    fault_injection_topic.publish(fault_injection_msg); 
    document.getElementById("x1").innerHTML = fault_injection_msg.data;
}*/ 
    //-----------------code------------------
        


       

         
