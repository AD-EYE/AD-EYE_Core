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
    lidar2_form[0].id = "lidar2_state";
    
    let lidar3_form = document.getElementById("lidar3_form")
    lidar3_form.innerHTML = lidar1_form.innerHTML;
    lidar3_form[0].id = "lidar3_state";

    let lidar4_form = document.getElementById("lidar4_form");
    lidar4_form.innerHTML = lidar1_form.innerHTML;
    lidar4_form[0].id = "lidar4_state";

    // forms for camera
    let camera1_form = document.getElementById("camera1_form");

    let camera2_form = document.getElementById("camera2_form");
    camera2_form.innerHTML = camera1_form.innerHTML;
    camera2_form[0].id = "camera2_state";

    let tl_camera_form = document.getElementById("tl_camera_form");
    tl_camera_form.innerHTML = camera1_form.innerHTML;
    tl_camera_form[0].id = "tl_camera_state";
}
    
function faultInjection_OnClick(button)
{
    formsCollection = document.getElementsByTagName("form");
    let parent_div = button.parentNode;
    for(let i = 0; i < formsCollection.length; i++)
    {
        if(button.name == formsCollection[i].name)
        {
            if(button.value == "off")
            {
                button.value = "on";
                button.style.backgroundColor = green;
                formsCollection[i].append(parent_div);
                //formsCollection[i].append(parent_second_element);
                formsCollection[i].style.display = "block";

            }
            else
            {
                button.value = "off";
                button.style.backgroundColor = "gray";
                document.getElementById(button.parentNode.parentNode.parentNode.id).append(formsCollection[i].lastElementChild);
                formsCollection[i].style.display = "none";

            }
            
        }
    }      
}

    let gnss_array = new Array();
    let lidar1_array = new Array();
    let lidar2_array = new Array(); 
    let lidar3_array = new Array(); 
    let lidar4_array = new Array(); 
    let radar_array = new Array();
    let camera1_array = new Array();
    let camera2_array = new Array();
    let tl_camera_array = new Array();
    

    // function to collect the values of lidar parameters from the form and put them in an array
    function fault_injection_parameter_values(button)
    {
        var form = button.parentNode.id;
        switch(form)
        {
            case "gnss_form":
                    // values are collected from form and kept in an array
                    for (let i=0;i<gnss_form.length-3;i++)
                    {
                        gnss_array[i] = gnss_form[i].value;
                    }

                    // coverting the string array to float array as we need float data to publish
                    for (let i=0;i<gnss_array.length;i++)
                    {
                        gnss_array[i] = parseFloat(gnss_array[i]);
                    }

                    // To display the selected value of dropdown in the textbox beside the button
                    selected_value = gnss_state.options[gnss_state.selectedIndex].text;
                    gnss_input.value = selected_value;
                    
                    // publishing the data from the form to gnss fault injection topic 
                    publish_fault_injection(0,gnss_array);
                    break;

                case "lidar1_form":
                    // values are collected from form and kept in an array
                    for (let i = 0; i < lidar1_form.length-3; i++)
                    {
                        lidar1_array[i] = lidar1_form[i].value;
                    }

                    // coverting the string array to float array as we need float data to publish
                    for (let i = 0; i < lidar1_array.length; i++)
                    {
                        lidar1_array[i] = parseFloat(lidar1_array[i]);
                    }

                    // To display the selected value of dropdown in the textbox beside the button
                    selected_value = lidar1_state.options[lidar1_state.selectedIndex].text;
                    lidar1_input.value = selected_value;

                    // publishing the data from the form to gnss fault injection topic 
                    publish_fault_injection(1,lidar1_array);
                    break;

                case "lidar2_form":
                    // values are collected from form and kept in an array
                    for (let i = 0; i < lidar2_form.length-3; i++)
                    {
                        lidar2_array[i] = lidar2_form[i].value;
                    }

                    // coverting the string array to float array as we need float data to publish
                    for (let i = 0; i < lidar2_array.length; i++)
                    {
                        lidar2_array[i] = parseFloat(lidar2_array[i]);
                    }

                    // To display the selected value of dropdown in the textbox beside the button
                    selected_value = lidar2_state.options[lidar2_state.selectedIndex].text;
                    lidar2_input.value = selected_value;

                    // publishing the data from the form to gnss fault injection topic 
                    publish_fault_injection(2,lidar2_array);
                    break;

                case "lidar3_form":
                    // values are collected from form and kept in an array
                    for (let i = 0; i < lidar3_form.length-3; i++)
                    {
                        lidar3_array[i] = lidar3_form[i].value;
                    }

                    // coverting the string array to float array as we need float data to publish
                    for (let i = 0; i < lidar3_array.length; i++)
                    {
                        lidar3_array[i] = parseFloat(lidar3_array[i]);
                    }

                    // To display the selected value of dropdown in the textbox beside the button
                    selected_value = lidar3_state.options[lidar3_state.selectedIndex].text;
                    lidar3_input.value = selected_value;

                    // publishing the data from the form to gnss fault injection topic 
                    publish_fault_injection(3,lidar3_array);
                    break;

                case "lidar4_form":
                    // values are collected from form and kept in an array
                    for (let i = 0; i < lidar4_form.length-3; i++)
                    {
                        lidar4_array[i] = lidar4_form[i].value;
                    }
    
                    // coverting the string array to float array as we need float data to publish
                    for (let i = 0; i < lidar4_array.length; i++)
                    {
                        lidar4_array[i] = parseFloat(lidar4_array[i]);
                    }
    
                    // To display the selected value of dropdown in the textbox beside the button
                    selected_value = lidar4_state.options[lidar4_state.selectedIndex].text;
                    lidar4_input.value = selected_value;
    
                    // publishing the data from the form to gnss fault injection topic 
                    publish_fault_injection(4,lidar4_array);
                    break;

                case "radar_form":
                    // values are collected from form and kept in an array
                    for (let i = 0; i < radar_form.length-3; i++)
                    {
                        radar_array[i] = radar_form[i].value;
                    }
    
                    // coverting the string array to float array as we need float data to publish
                    for (let i = 0; i < radar_array.length; i++)
                    {
                        radar_array[i] = parseFloat(radar_array[i]);
                    }
    
                    // To display the selected value of dropdown in the textbox beside the button
                    selected_value = radar_state.options[radar_state.selectedIndex].text;
                    radar_input.value = selected_value;
    
                    // publishing the data from the form to gnss fault injection topic 
                    publish_fault_injection(5,radar_array);
                    break;

                case "camera1_form":
                    
                    // values are collected from form and kept in an array
                    for (let i = 0; i < camera1_form.length-3; i++)
                    {
                        camera1_array[i] = camera1_form[i].value;
                    }
                    
                    // coverting the string array to float array as we need float data to publish
                    for (let i = 0; i < camera1_array.length; i++)
                    {
                        camera1_array[i] = parseFloat(camera1_array[i]);
                    }
                    // To display the selected value of dropdown in the textbox beside the button
                    selected_value = camera1_state.options[camera1_state.selectedIndex].text;
                    camera1_input.value = selected_value;
                    
                    // publishing the data from the form to gnss fault injection topic 
                    publish_fault_injection(6,camera1_array);
                    break;

                case "camera2_form":
                    // values are collected from form and kept in an array
                    for (let i = 0; i < camera2_form.length-3; i++)
                    {
                        camera2_array[i] = camera2_form[i].value;
                    }
    
                    // coverting the string array to float array as we need float data to publish
                    for (let i = 0; i < camera2_array.length; i++)
                    {
                        camera2_array[i] = parseFloat(camera2_array[i]);
                    }
    
                    // To display the selected value of dropdown in the textbox beside the button
                    selected_value = camera2_state.options[camera2_state.selectedIndex].text;
                    camera2_input.value = selected_value;
    
                    // publishing the data from the form to gnss fault injection topic 
                    publish_fault_injection(7,camera2_array);
                    break;

                case "tl_camera_form":
                    // values are collected from form and kept in an array
                    for (let i = 0; i < tl_camera_form.length-3; i++)
                    {
                        tl_camera_array[i] = tl_camera_form[i].value;
                    }
    
                    // coverting the string array to float array as we need float data to publish
                    for (let i = 0; i < tl_camera_array.length; i++)
                    {
                        tl_camera_array[i] = parseFloat(tl_camera_array[i]);
                    }
    
                    // To display the selected value of dropdown in the textbox beside the button
                    selected_value = tl_camera_state.options[tl_camera_state.selectedIndex].text;
                    tl_camera_input.value = selected_value;
    
                    // publishing the data from the form to gnss fault injection topic 
                    publish_fault_injection(8,tl_camera_array);
                    break;
                }  

    }
     
    // Function to publish the fault injection parameter values from user to specific rostopic
    function publish_fault_injection(i,array)
    {
        let lidar_topics_array = new Array("/fault_injection/gnss","/fault_injection/lidar1","/fault_injection/lidar2","/fault_injection/lidar3","/fault_injection/lidar4","/fault_injection/radar","/fault_injection/camera1","/fault_injection/camera2","/fault_injection/tl_camera");
        
        let fault_injection_topic = new ROSLIB.Topic({
            ros : ros,
            name : lidar_topics_array[i],
            messageType : 'std_msgs/Float64MultiArray'
            });
                    
        let fault_injection_msg = new ROSLIB.Message({
            data : array
            });
    
        fault_injection_topic.publish(fault_injection_msg);
    }
    
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

        let imgData = context.createImageData(canvas1.width,canvas1.height);
        for(let j = 0; j < array.length; j++)
        {
            imgData.data[ 4 * j + 0 ] = array[ 3 * j + 0 ];
            imgData.data[ 4 * j + 1 ] = array[ 3 * j + 1 ];
            imgData.data[ 4 * j + 2 ] = array[ 3 * j + 2 ];
            imgData.data[ 4 * j + 3 ] = 255;
        }
        
       //var image = document.getElementById("camera1_canvas");
       canvas1.style.width = "100%";
       canvas1.style.height = "auto";
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

        //let image = document.getElementById("camera2_canvas");
        canvas2.style.width = "100%";
        canvas2.style.height = "auto";
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

        //let image = document.getElementById("tl_camera_canvas");
        canvas3.style.width = "100%";
        canvas3.style.height = "auto";
        context.putImageData(imgData,0,0,0,0,canvas3.width,canvas3.height);
}); 
//------------------- TL camera  display --------------



//----------------goal setting--------------------------

//--- displaying the image from ros topic---
    
    //listen to the topic camera_1/image_raw
    let camera_topic = new ROSLIB.Topic({
        ros : ros,
        name : '/camera_1/image_raw',
        messageType : 'sensor_msgs/Image'
    });

    // original image coordinates
    let original_width; 
    let original_height;

    //subscribing to the topic camera_1/image_raw
    camera_topic.subscribe(function(message)
    { 
        // original image coordinates
        original_width = message.width;
        original_height = message.height;

        let msg = atob(message.data);
        let array = new Uint8Array(new ArrayBuffer(msg.length));

        for (let i = 0; i < msg.length; i++) 
        {
            array[i] = msg.charCodeAt(i);
        }

        let canvas4 = document.getElementById( "image_canvas" );
        const context = canvas4.getContext( "2d" ); 

        let imgData = context.createImageData(canvas4.width,canvas4.height);

        for(let j = 0; j < (array.length)/2; j++)
        {
            imgData.data[ 4 * j + 0 ] = array[ 3 * j + 0 ];
            imgData.data[ 4 * j + 1 ] = array[ 3 * j + 1 ];
            imgData.data[ 4 * j + 2 ] = array[ 3 * j + 2 ];
            imgData.data[ 4 * j + 3 ] = 255;

        }
        canvas4.style.width = "100%";
        canvas4.style.height = "auto";
        context.putImageData(imgData,0,0,0,0,canvas4.width,canvas4.height);
    }); 
    
//---displaying the image from ros topic---

    // function to find the position of canvas element
    function findPosition(canvas_element)
    {
        if(typeof( canvas_element.offsetParent ) != "undefined")
        {
            for(var posX = 0, posY = 0;canvas_element ;canvas_element = canvas_element.offsetParent)
            {
                posX += canvas_element.offsetLeft;
                posY += canvas_element.offsetTop;
            }
            return [ posX, posY ];
        }
        else
        {
            return [ canvas_element.x, canvas_element.y ];
        }
    }

    // function to find the coordinates of the point on mouse click
    function getCoordinates(e)
    {
        let posX = 0;
        let posY = 0;
        let imgPos;
        imgPos = findPosition(image_canvas);
        if (!e) 
        var e = window.event;
        
        if (e.pageX || e.pageY)
        {
            posX = e.pageX;
            posY = e.pageY;
        }
        else if (e.clientX || e.clientY)
        {
            posX = e.clientX + document.body.scrollLeft + document.documentElement.scrollLeft;
            posY = e.clientY + document.body.scrollTop + document.documentElement.scrollTop;
        }
        posX = posX - imgPos[0];
        posY = posY - imgPos[1];
        document.getElementById("x-co-ordinate").innerHTML = posX;
        document.getElementById("y-co-ordinate").innerHTML = posY;
    
        let canvas = document.getElementById("image_canvas");
        let rect = canvas.getBoundingClientRect();

        // coordinates of image displayed on canvas 
        let canvas_width = rect.width;
        let canvas_height = rect.height;

        // scaling factor
        let width_scaling = original_width / canvas_width;
        let height_scaling = original_height / canvas_height;

            let coordinate_array = new Array();
            coordinate_array[0] = posX * Math.floor(width_scaling);
            coordinate_array[1] = posY * Math.floor(height_scaling);
            
            // publishing the coordinate values to rostopic /gui/goal_pixels
            let goal_pixel_topic = new ROSLIB.Topic({
                ros : ros,
                name : '/gui/goal_pixels',
                messageType : 'std_msgs/Int16MultiArray'
            });
                        
            let goal_pixel_msg = new ROSLIB.Message({
                data : coordinate_array
            });

            goal_pixel_topic.publish(goal_pixel_msg);
    }
 //----------------goal setting------------------
 
 

//---------------- creating a generic card----------------
    let button_clicked = false;

    function createGenericCard()
    {
        // two divs should be created one holds the generic card and the other holds the + button

        // div1 holds newly created generic card
        let div1 = document.createElement("div");
        div1.id = "div1";
        div1.className = "col-md-4 col-sm-12";

        // div2 will hold the + button
        let div2 = document.createElement("div");
        div2.id = "div2";

        // appending both the created divs to main row_div

        let row_div = document.getElementById("row_div");
        row_div.appendChild(div1);
        row_div.appendChild(div2);
        
        if(button_clicked === false)
        {

        let generic_child_div = document.createElement("div");
        generic_child_div.classList.add("box");
        generic_child_div.draggable = "true";

        // h2 element creation and asigning text to it
        let h2 = document.createElement("h2");
        h2.style.textAlign = "center";
        let text = document.createTextNode("ROS Topics List");
        h2.appendChild(text);
        generic_child_div.appendChild(h2);

        // creation of p element
        let p = document.createElement("p");

        // creation of label element
        let label1 = document.createElement("label");
        let label1_text = document.createTextNode("Topic");
        label1.appendChild(label1_text);

        // creation of dropdown to hold list of rostopics 
        let dropdown = document.createElement("select");
        dropdown.id = "select_topic";
        dropdown.onclick = getTopics;
        dropdown.onchange = display_topic_data;

        // appending label and dropdown to p element
        p.appendChild(label1);
        p.appendChild(dropdown);

        // creation of another p element
        let p1 = document.createElement("p");

        // creation of label element
        let label2 = document.createElement("label");
        let label2_text = document.createTextNode("Topic_Data");
        label2.appendChild(label2_text);

        // creation of textarea to hold the data of selected rostopic
        let textarea = document.createElement("textarea");
        textarea.id = "topic_data_textbox";
        textarea.rows = "9";
        textarea.columns = "250";
        textarea.name = "topic_data";

        // appending label and textarea to p element
        p1.appendChild(label2);
        p1.appendChild(textarea);

        // appending both p elements to div tag and appending that div to div1 created to hold generic card
        generic_child_div.appendChild(p);
        generic_child_div.appendChild(p1);
        div1.appendChild(generic_child_div);

        //appending the button element to div2
        let generic_button = document.getElementById("generic_button");
        div2.appendChild(generic_button);
        }
        
        button_clicked = true;
    }
//----------------generic card----------------



//-----displaying the list of topics in the dropdown  & data of selected rostopic in textarea of generic card-------------

    let isClicked = false;
    let topicsClient = new ROSLIB.Service({
        ros : ros,
        name : '/rosapi/topics',
        serviceType : 'rosapi/Topics'
        });

    let request = new ROSLIB.ServiceRequest();

    // function to get the list of rostopics 
    function getTopics() 
    {
        let select = document.getElementById("select_topic");
        if(isClicked === false)
        {
            topicsClient.callService(request, function(result) 
            {
                topics_list = result.topics;
                for(var i = 0; i < topics_list.length; i++)
                {
                    let topic_name = topics_list[i];
                    let option = document.createElement("option");
                    option.value = i;
                    option.text = topic_name;
                    select.append(option);

                }
            });
        }
        isClicked = true;
    }

    // function to display the data of selected rostopic in the teaxarea of generic card
    function display_topic_data()
    {
        let select = document.getElementById("select_topic");
        let selected_topic = select.options[select.selectedIndex].text;
        let selected_topic_value = select.options[select.selectedIndex].value;

        topicsClient.callService(request, function(result) 
        {
            topic_types = result.types;
            for(var i = 0; i < topic_types.length; i++)
            {
                if(i == selected_topic_value)
                { 
                    // Subscribing to a Topic
                    let listener = new ROSLIB.Topic({
                        ros : ros,
                        name : selected_topic,
                        messageType : topic_types[i]
                    });

                    listener.subscribe(function(message) {
                        topic_val = JSON.stringify(message);

                    });
                    document.getElementById("topic_data_textbox").value = selected_topic ;


                }  
            }
        });
    }
//-----displaying the list of topics in the dropdown  & data of selected rostopic in textarea of generic card-------------