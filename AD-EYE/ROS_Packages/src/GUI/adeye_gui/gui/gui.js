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
        document.getElementById("test").innerHTML= value;

        //function to set values of the gauge
        function setGaugeValue(gauge_velocity, value ) 
        {
            //safety check to ensure that the values are within the range
            if (value < 0 || value > 1) 
            {
              return;
            }

            //making the turn over the gauge body
            gauge_velocity.querySelector(".gauge_velocity_fill").style.transform = `rotate( ${ value / 3 }turn )`;

            // to convert the value to km/hr from m/s
            value = (value * 18) / 5; 

            //printing the velocity value
            gauge_velocity.querySelector(".gauge_velocity_cover").textContent = `${ Math.round( value ) } km/h`;
        }

        // passing the value received from the topic /vehicle_cmd to the function to display the velocity of the car
        setGaugeValue(gauge_element, value);
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

        // passing the value received from the topic /vehicle_cmd to the function to display the acceleration of the car
        setGaugeValue(gauge_element, value);
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
   
    // function to reset the dropdown list to off value and to change the color of button based on the values on/off
    function faultInjection_OnClick(button_element)
    {

        let selected_element = document.getElementsByClassName("selected");
        for( let i = 0; i < selected_element.length; i++)
        {
            if(button_element.name == selected_element[i].name)
            {
                document.getElementById("a").innerHTML = " ";
                if(button_element.value == "off")
                {
                    button_element.value = "on";
                    button_element.style.backgroundColor = green;
                    selected_element[i].selectedIndex = 0;
                    lidarForm();
                    x.style.display = "block";
                }
                else
                {
                    button_element.value = "off";
                    button_element.style.backgroundColor = "gray";
                    selected_element[i].selectedIndex = 0;
                    x.style.display = "none";
                }
            }
        }
    }

    function lidarForm()
    {
    // Create a form dynamically 
    let form = document.createElement("form"); 

    var values = ["Off", "Random","Rain"];
    var drop_down = document.createElement("select");
 
    for (const val of values) 
    {
        var option = document.createElement("option");
        //option.value = val;
        option.text = val;
        drop_down.append(option);
    }

    // Create an input element for state
    let statelabel = document.createElement("label");
    statelabel.htmlFor = "state";
   // statelabel.setAttribute("value","State");

    let state = document.createElement("input"); 
    state.setAttribute("type", "text"); 
    state.setAttribute("name", "state"); 
    state.setAttribute("placeholder", "State"); 

    // Create an input element for random/range_variance
    let random_range_variance = document.createElement("input"); 
    random_range_variance.setAttribute("type", "text"); 
    random_range_variance.setAttribute("name", "random/range_variance"); 
    random_range_variance.setAttribute("placeholder", "random/range_variance"); 

    // Create an input element for random/theta_variance
    let random_theta_variance = document.createElement("input"); 
    random_theta_variance.setAttribute("type", "text"); 
    random_theta_variance.setAttribute("name", "random/theta_variance"); 
    random_theta_variance.setAttribute("placeholder", "random/theta_variance"); 

    // Create an input element for rain/rain_intensity
    let rain_rain_intensity = document.createElement("input"); 
    rain_rain_intensity.setAttribute("type", "text"); 
    rain_rain_intensity.setAttribute("name", "rain/rain_intensity"); 
    rain_rain_intensity.setAttribute("placeholder", "rain/rain_intensity"); 

    // Create an input element for rain/a
    let rain_a = document.createElement("input"); 
    rain_a.setAttribute("type", "text"); 
    rain_a.setAttribute("name", "rain/a"); 
    rain_a.setAttribute("placeholder", "rain/a"); 

    // Create an input element for rain/b
    let rain_b = document.createElement("input"); 
    rain_b.setAttribute("type", "text"); 
    rain_b.setAttribute("name", "rain/b"); 
    rain_b.setAttribute("placeholder", "rain/b");
    
    // Create an input element for rain/reflectivity
    let rain_reflectivity = document.createElement("input"); 
    rain_reflectivity.setAttribute("type", "text"); 
    rain_reflectivity.setAttribute("name", "rain/reflectivity"); 
    rain_reflectivity.setAttribute("min","0");
    rain_reflectivity.setAttribute("max","1");
    rain_reflectivity.setAttribute("placeholder", "rain/reflectivity"); 

    // Create an input element for rain/max_range
    let rain_max_range = document.createElement("input"); 
    rain_max_range.setAttribute("type", "text"); 
    rain_max_range.setAttribute("name", "rain/max_range"); 
    rain_max_range.setAttribute("placeholder", "rain/max_range"); 

    // Create a submit button 
    let s = document.createElement("input"); 
    s.setAttribute("type", "submit"); 
    s.setAttribute("value", "Submit"); 

    form.append(statelabel);

    form.append(drop_down);

    // Append the state input to the form 
    form.append(state);  
    
    // Append the random_range_variance to the form 
    form.append(random_range_variance); 
    
    // Append the random_theta_variance to the form 
    form.append(random_theta_variance);  
    
    // Append the rain_rain_intensity to the form 
    form.append(rain_rain_intensity);

    // Append the rain_a to the form 
    form.append(rain_a);

    // Append the rain_b to the form 
    form.append(rain_b);

    // Append the rain_reflectivity to the form 
    form.append(rain_reflectivity);

    // Append the rain_max_range to the form
    form.append(rain_max_range);

    // Append the button to the form 
    form.append(s);  

    document.getElementById("a").appendChild(form); 

    

    }
    

    // function to change the color of the button based on the value selected from the dropdown list for fault injection
    /* function changeColor(data_value) 
    { 
        if(data_value == 0)
        {
            document.getElementsByClassName("fault_injection").style.backgroundColor = "gray";
        }
        else if(data_value == 1)
        {
            document.getElementsByClassName("fault_injection").style.backgroundColor = green;
        }
        else if(data_value == 2)
        {
            document.getElementsByClassName("fault_injection").style.backgroundColor = green;
        }
    }   */

    let data_value;

    function publish_fault_injection(fault_injection,topic)
    {
        let fault_injection_button = document.getElementsByClassName("selected");
        for( let i = 0; i < fault_injection_button.length; i++)
        {   
            if(fault_injection.name === fault_injection_button[i].name)
            {
                let option = fault_injection_button[i].options[fault_injection_button[i].selectedIndex];
                data_value = fault_injection_button[i].value;
                if((option.value) != 0)
                {
                    let fault_injection_topic = new ROSLIB.Topic({
                        ros : ros,
                        name : topic,
                        messageType : 'std_msgs/Int32'
                    });
                
                    let fault_injection_msg = new ROSLIB.Message({
                        data : parseInt(data_value)
                    });

                    fault_injection_topic.publish(fault_injection_msg);
                }
            }
        }
    }
    
    // function to switch on fault_injection on value change of dropdown and publishing the message on to topic fault_injection/gnss
    function faultInjectionGnss_OnChange(gnss)
    {
        let topic = "/fault_injection/gnss";
        publish_fault_injection(gnss,topic);
    }

    // function to switch on fault_injection on value change of dropdown and publishing the message on to topic fault_injection/lidar1
    function faultInjectionLidar1_OnChange(lidar1)
    {
        let topic = "/fault_injection/lidar1";
        publish_fault_injection(lidar1,topic);
    }

    // function to switch on fault_injection on value change of dropdown and publishing the message on to topic fault_injection/lidar2
    function faultInjectionLidar2_OnChange(lidar2)
    {
        let topic = "/fault_injection/lidar2";
        publish_fault_injection(lidar2,topic);
    }

    // function to switch on fault_injection on value change of dropdown and publishing the message on to topic fault_injection/lidar3
    function faultInjectionLidar3_OnChange(lidar3)
    {
        let topic = "/fault_injection/lidar3";
        publish_fault_injection(lidar3,topic);
    }

    // function to switch on fault_injection on value change of dropdown and publishing the message on to topic fault_injection/lidar4
    function faultInjectionLidar4_OnChange(lidar4)
    {
        let topic = "/fault_injection/lidar4";
        publish_fault_injection(lidar4,topic);
    }

    // function to switch on fault_injection on value change of dropdown and publishing the message on to topic fault_injection/radar
    function faultInjectionRadar_OnChange(radar)
    {
        let topic = "/fault_injection/radar";
        publish_fault_injection(radar,topic);
    }

    // function to switch on fault_injection on value change of dropdown and publishing the message on to topic fault_injection/camera1
    function faultInjectionCamera1_OnChange(camera1)
    {
        let topic = "/fault_injection/camera1";
        publish_fault_injection(camera1,topic);
    }

    // function to switch on fault_injection on value change of dropdown and publishing the message on to topic fault_injection/camera2
    function faultInjectionCamera2_OnChange(camera2)
    {
        let topic = "/fault_injection/camera2";
        publish_fault_injection(camera2,topic);
    }

    // function to switch on fault_injection on value change of dropdown and publishing the message on to topic fault_injection/tl_camera
    function faultInjectionTlCamera_OnChange(tl_camera)
    {
        let topic = "/fault_injection/tl_camera";
        publish_fault_injection(tl_camera,topic);
    }
        
    /* // function to switch on lidar1 on button click and publishing the message on to topic fault_injection/lidar1
    function faultInjectionLidar1_OnChange(lidar1)
    {
        let lidar1_btn = document.getElementById("lidar1");
        let option = lidar1_btn.options[lidar1_btn.selectedIndex];
        let data_value = lidar1_btn.value;
        if((option.value) != 0) 
        {
            let togglelidar1On = new ROSLIB.Topic({
                ros : ros,
                name : '/fault_injection/lidar1',
                messageType : 'std_msgs/Int32'
            });

            let lidar1On = new ROSLIB.Message({
                data : parseInt(data_value)
            });
            togglelidar1On.publish(lidar1On);
        } 
        changeColor(data_value);
    }

    // function to switch on lidar2 on button click and publishing the message on to topic fault_injection/lidar2
    function faultInjectionLidar2_OnChange(lidar2)
    {
        let lidar2_btn = document.getElementById("lidar2");
        let option = lidar2_btn.options[lidar2_btn.selectedIndex];
        let data_value = lidar2_btn.value;
        if((option.value) != 0) 
        {
            let togglelidar2On = new ROSLIB.Topic({
                ros : ros,
                name : '/fault_injection/lidar2',
                messageType : 'std_msgs/Int32'
            });

            let lidar2On = new ROSLIB.Message({
                data : parseInt(data_value)
            });
            togglelidar2On.publish(lidar2On);
        } 
        changeColor(data_value);
    }
        
    // function to switch on lidar3 on button click and publishing the message on to topic fault_injection/lidar3
    function faultInjectionLidar3_OnChange(lidar3)
    {
        let lidar3_btn = document.getElementById("lidar3");
        let option = lidar3_btn.options[lidar3_btn.selectedIndex];
        let data_value = lidar3_btn.value;
        if((option.value) != 0) 
        {
            let togglelidar3On = new ROSLIB.Topic({
                ros : ros,
                name : '/fault_injection/lidar3',
                messageType : 'std_msgs/Int32'
            });
            let lidar3On = new ROSLIB.Message({
                data : parseInt(data_value)
            });
            togglelidar3On.publish(lidar3On);
        } 
        changeColor(data_value);
    } 

    // function to switch on lidar4 on button click and publishing the message on to topic fault_injection/lidar4
    function faultInjectionLidar4_OnClick(lidar4)
    {
        let lidar4_btn = document.getElementById("lidar4");
        let option = lidar4_btn.options[lidar4_btn.selectedIndex];
        let data_value = lidar4_btn.value;
        if((option.value) != 0) 
        {
            let togglelidar4On = new ROSLIB.Topic({
                ros : ros,
                name : '/fault_injection/lidar4',
                messageType : 'std_msgs/Int32'
            });
            let lidar4On = new ROSLIB.Message({
                data : parseInt(data_value)
            });
            togglelidar4On.publish(lidar4On);
        } 
        changeColor(data_value);
    }

    // function to switch on radar on button click and publishing the message on to topic fault_injection/radar
    function faultInjectionRadar_OnClick(radar)
    {
        let radar_btn = document.getElementById("radar");
        let option = radar_btn.options[radar_btn.selectedIndex];
        let data_value = radar_btn.value;
        if((option.value) != 0) 
        {
            let toggleradarOn = new ROSLIB.Topic({
                ros : ros,
                name : '/fault_injection/radar',
                messageType : 'std_msgs/Int32'
            });
            let radarOn = new ROSLIB.Message({
                data : parseInt(data_value)
            });
            toggleradarOn.publish(radarOn);
        } 
        changeColor(data_value);
    }

    // function to switch on camera1 on button click and publishing the message on to topic fault_injection/camera1
    function faultInjectionCamera1_OnClick(camera1)
    {
        let camera1_btn = document.getElementById("camera_1");
        let option = camera1_btn.options[camera1_btn.selectedIndex];
        let data_value = camera1_btn.value;
        if((option.value) != 0) 
        {
            let togglecamera1On = new ROSLIB.Topic({
                ros : ros,
                name : '/fault_injection/camera1',
                messageType : 'std_msgs/Int32'
            });
            let camera1On = new ROSLIB.Message({
                data : parseInt(data_value)
            });
            togglecamera1On.publish(camera1On);
        } 
        changeColor(data_value);
    }

    // function to switch on camera2 on button click and publishing the message on to topic fault_injection/camera2
    function faultInjectionCamera2_OnClick(camera2)
    {
        let camera2_btn = document.getElementById("camera_2");
        let option = camera2_btn.options[camera2_btn.selectedIndex];
        let data_value = camera2_btn.value;
        if((option.value) != 0) 
        {
            let togglecamera2On = new ROSLIB.Topic({
                ros : ros,
                name : '/fault_injection/camera2',
                messageType : 'std_msgs/Int32'
            });
            let camera2On = new ROSLIB.Message({
                data : parseInt(data_value)
            });
            togglecamera2On.publish(camera2On);
        } 
        changeColor(data_value);
    }

    // function to switch on tl_camera on button click and publishing the message on to topic fault_injection/tl_camera
    function faultInjectionTlCamera_OnClick(tlcamera)
    {
        let tlcamera_btn = document.getElementById("tl_camera");
        let option = tlcamera_btn.options[tlcamera_btn.selectedIndex];
        let data_value = tlcamera_btn.value;
        if((option.value) != 0) 
        {
            let toggletlcameraOn = new ROSLIB.Topic({
                ros : ros,
                name : '/fault_injection/tl_camera',
                messageType : 'std_msgs/Int32'
            });
            let tlcameraOn = new ROSLIB.Message({
                 data : parseInt(data_value)
            });
            toggletlcameraOn.publish(tlcameraOn);
        }
        changeColor(data_value);
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
        





       

         
