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

    ros.on('connection', function() { document.getElementById("status").innerHTML = "Connected to ROS"; });

    ros.on('error', function(error) { document.getElementById("status").innerHTML = "Error"; });

    ros.on('close', function() { document.getElementById("status").innerHTML = "Closed"; });
//------------------Connection with the bridge-------------------

    let green = "#699b2c";
    let time = "";

    function clock() 
    {
        let today = new Date();
        let hours = today.getHours();
        let minutes = today.getMinutes();
        let seconds = today.getSeconds();
        hours = checkTime(hours);
        minutes = checkTime(minutes);
        seconds = checkTime(seconds);
        time = hours + ":" + minutes + ":" + seconds;
        document.getElementById("real_time").innerHTML = " " + time;
        setInterval(clock, 1000);
    }

    function checkTime(time) 
    {
        if (time < 10) 
        {
            time = "0" + time;
        }
        return time;
    }

    function responsive()
    {
        let col = document.querySelectorAll(".column");

        for (let i = 0; i < col.length; i++)
        {
            col[i].className = "col-md-3 col-sm-12"; 
        }
    }

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
        let max_gauge_acceleration = 1;

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
            let position = 0;
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
        document.getElementById("control_channel").value = time + " "+channel.name;

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
        let initialOn = new ROSLIB.Message({
            data : true
        });
        initialChecksTopic.publish(initialOn);
        document.getElementById("latest_state").value = time + " " + initialChecksTopic.name + ": " + initialOn.data;
    }
    
    // function to toggle the state on and off by clicking on the buttons.
    function toggleStateactivation_OnClick(activation)
    {
        let activationRequestTopic = new ROSLIB.Topic({
            ros : ros,
            name : '/activation_request',
            messageType : 'std_msgs/Bool'
        });
        let activationOn = new ROSLIB.Message({
            data : true
        });
        activationRequestTopic.publish(activationOn);
        document.getElementById("latest_state").value = time + " " + activationRequestTopic.name + ": " + activationOn.data;
    }

    // function to toggle the state on and off by clicking on the buttons.
    function toggleStatedeactivation_OnClick(deactivation)
    {
        let activationRequestTopic = new ROSLIB.Topic({
            ros : ros,
            name : '/activation_request',
            messageType : 'std_msgs/Bool'
        });

        let activationOff = new ROSLIB.Message({
            data : false
        });
        activationRequestTopic.publish(activationOff);
        document.getElementById("latest_state").value = time + " " + activationRequestTopic.name + ": " + activationOff.data;;
    }

    // function to toggle the state on and off by clicking on the buttons.
    function toggleStatefault_OnClick(fault)
    {
        let faultTopic = new ROSLIB.Topic({
            ros : ros,
            name : '/fault',
            messageType : 'std_msgs/Bool'
        });
        let faultOn = new ROSLIB.Message({
            data : true
        });
        faultTopic.publish(faultOn);
        document.getElementById("latest_state").value = time + " " + faultTopic.name + ": " + faultOn.data;; 
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
        let object = [];
        let k = 0;
        for (let i = 0; i < message.objects.length; i++) 
        {
            for (let j = 0; j < message.objects[i].label.length; j++) 
            {
                object[k] = message.objects[i].label[j];
                k++;
            } 
            document.getElementById("test").innerHTML = message.objects[i].user_defined_info;
            if(message.objects[i].user_defined_info[1] == "camera_2")
            {
                s = object.join("");
                document.getElementById("track").innerHTML = s;
                x = message.objects[i].pose.position.x;
                document.getElementById("x").innerHTML = x;
                y = message.objects[i].pose.position.y;
                document.getElementById("y").innerHTML = y;
                z = message.objects[i].pose.position.z
                document.getElementById("z").innerHTML = z;
                object.splice(0, object.length);
            }
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

    let data_array = 0;
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
        document.getElementById("features_array").value = time + "\n " + featureToggleOff.name + ": " + featureOff.data;
    }  
//-------------------- feature Change---------------


//-------------fault injection----------------------
    // function to create the forms for respective fault injection topic
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

    // Arrays for storing the values entered by the user for fault injection. 
    let gnss_array = new Array();
    let lidar1_array = new Array();
    let lidar2_array = new Array(); 
    let lidar3_array = new Array(); 
    let lidar4_array = new Array(); 
    let radar_array = new Array();
    let camera1_array = new Array();
    let camera2_array = new Array();
    let tl_camera_array = new Array();
    
    //  function to display the form for fault injection control from gui 
    function faultInjection_OnClick(button)
    {
        formsCollection = document.getElementsByTagName("form");
        button_div = document.getElementsByClassName("button_div");
        for(let i = 0; i < formsCollection.length; i++)
        {
            if(button.name == formsCollection[i].name)
            {
                if(button.value == "off")
                {
                    button.value = "on";
                    button.style.backgroundColor = "white";
                    button.style.color = "black";
                    formsCollection[i].firstElementChild.innerHTML = button_div[i].innerHTML;
                    button.value = "off";
                    button.style.backgroundColor = "gray";
                    button.style.color = "white";
                    button_div[i].style.display = "none";
                    formsCollection[i].style.display = "block";
                }
                else
                {
                    button.value = "off";                   
                    button_div[i].style.display = "inline-flex";
                    formsCollection[i].style.display = "none";
                }   
            }
        }      
    }
    
   /*  function to collect the parameter values from the form and put them in an array and 
    to display the value selected in the dropdown in textbox beside the button for fault injection */
    function form_values(form,array,state,input)
    {
        // values are collected from form and kept in an array
        for (let i = 2; i < form.length-1; i++)
        {
            array[i-2] = form[i].value;
        }

        // coverting the string array to float array as we need float data to publish
        for (let i=0; i < array.length; i++)
        {
            array[i] = parseFloat(array[i]);
        }

        selected_value = state.options[state.selectedIndex].text;
        // displaying the value selected in the dropdown in the text box beside the faultinjection button. 
        input.value = selected_value;
        return selected_value;
    }

    // function to collect the values of lidar parameters from the form and put them in an array
    function fault_injection_parameter_values(button)
    {
        let form = button.parentNode.parentNode.id;
        let value = 0;
        switch(form)
        {
            case "gnss_form":
                let gnss_input = document.getElementById("gnss_input");
                value = form_values(gnss_form,gnss_array,gnss_state,gnss_input);
                // displaying the value selected in the dropdown in the text box beside the faultinjection button inside the form. 
                gnss_form[1].value = value;
                // publishing the data from the form to gnss fault injection topic 
                publish_fault_injection(0,gnss_array);
                break;

            case "lidar1_form":
                let lidar1_input = document.getElementById("lidar1_input");
                value = form_values(lidar1_form,lidar1_array,lidar1_state,lidar1_input);
                // displaying the value selected in the dropdown in the text box beside the faultinjection button inside the form. 
                lidar1_form[1].value = value;
                // publishing the data from the form to gnss fault injection topic 
                publish_fault_injection(1,lidar1_array);
                break;

            case "lidar2_form":
                let lidar2_input = document.getElementById("lidar2_input");
                value = form_values(lidar2_form,lidar2_array,lidar2_state,lidar2_input);
                // displaying the value selected in the dropdown in the text box beside the faultinjection button inside the form. 
                lidar2_form[1].value = value;
                // publishing the data from the form to gnss fault injection topic 
                publish_fault_injection(2,lidar2_array);
                break;

            case "lidar3_form":
                let lidar3_input = document.getElementById("lidar3_input");
                value = form_values(lidar3_form,lidar3_array,lidar3_state,lidar3_input);
                // displaying the value selected in the dropdown in the text box beside the faultinjection button inside the form. 
                lidar3_form[1].value = value;
                // publishing the data from the form to gnss fault injection topic 
                publish_fault_injection(3,lidar3_array);
                break;

            case "lidar4_form":
                let lidar4_input = document.getElementById("lidar4_input");
                value = form_values(lidar4_form,lidar4_array,lidar4_state,lidar4_input);
                // displaying the value selected in the dropdown in the text box beside the faultinjection button inside the form. 
                lidar4_form[1].value = value;
                // publishing the data from the form to gnss fault injection topic 
                publish_fault_injection(4,lidar4_array);
                break;

            case "radar_form":
                let radar_input = document.getElementById("radar_input");
                value = form_values(radar_form,radar_array,radar_state,radar_input);
                // displaying the value selected in the dropdown in the text box beside the faultinjection button inside the form. 
                radar_form[1].value = value;
                // publishing the data from the form to gnss fault injection topic 
                publish_fault_injection(5,radar_array);
                break;

            case "camera1_form":
                let camera1_input = document.getElementById("camera1_input");
                value = form_values(camera1_form,camera1_array,camera1_state,camera1_input);
                // displaying the value selected in the dropdown in the text box beside the faultinjection button inside the form. 
                camera1_form[1].value = value;
                // publishing the data from the form to gnss fault injection topic 
                publish_fault_injection(6,camera1_array);
                break;

            case "camera2_form":
                let camera2_input = document.getElementById("camera2_input");
                value = form_values(camera2_form,camera2_array,camera2_state,camera2_input);
                // displaying the value selected in the dropdown in the text box beside the faultinjection button inside the form. 
                camera2_form[1].value = value;
                // publishing the data from the form to gnss fault injection topic 
                publish_fault_injection(7,camera2_array);
                break;

            case "tl_camera_form":
                let tl_camera_input = document.getElementById("tl_camera_input");
                value = form_values(tl_camera_form,tl_camera_array,tl_camera_state,tl_camera_input);
                // displaying the value selected in the dropdown in the text box beside the faultinjection button inside the form. 
                tl_camera_form[1].value = value;
                // publishing the data from the form to gnss fault injection topic 
                publish_fault_injection(8,tl_camera_array);
                break;
        } 
    }

    // function to publish the fault injection parameter values specified by the user to corresponding rostopic
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
        document.getElementById("fault_injection_values").value = time + "\n " + fault_injection_topic.name + ": " + fault_injection_msg.data;
    }
//-------------fault injection----------------


//---------------camera displays----------------------
    // function that takes the raw int8 data from ros topic and paints raw data as image on canvas 
    function subscribe_to_topic(message,canvas)
    {
        let msg = atob(message.data);
        let array = new Uint8Array(new ArrayBuffer(msg.length));
        for (let i = 0; i < msg.length; i++) 
        {
            array[i] = msg.charCodeAt(i);
        }

        canvas.width = message.width;
        canvas.height = message.height;
        const context = canvas.getContext( "2d" ); 

        let imgData = context.createImageData(canvas.width,canvas.height);
        for(let j = 0; j < array.length; j++)
        {
            imgData.data[ 4 * j + 0 ] = array[ 3 * j + 0 ];
            imgData.data[ 4 * j + 1 ] = array[ 3 * j + 1 ];
            imgData.data[ 4 * j + 2 ] = array[ 3 * j + 2 ];
            imgData.data[ 4 * j + 3 ] = 255;
        }
        canvas.style.width = "100%";
        canvas.style.height = "auto";
        context.putImageData(imgData,0,0,0,0,canvas.width,canvas.height);
    }

    //-------------------camera 1 display ----------------
        //listen to the topic camera_1/image_raw
        let camera1_topic = new ROSLIB.Topic({
            ros : ros,
            name : '/camera_1/image_raw',
            messageType : 'sensor_msgs/Image'
        });

        camera1_topic.subscribe(function(message)
        {
            let camera1_canvas = document.getElementById( "camera1_canvas" );
            subscribe_to_topic(message,camera1_canvas);
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
            let camera2_canvas = document.getElementById( "camera2_canvas" );
            subscribe_to_topic(message,camera2_canvas);
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
            let tl_camera_canvas = document.getElementById( "tl_camera_canvas" );
            subscribe_to_topic(message,tl_camera_canvas); 
    }); 
    //------------------- TL camera  display --------------
//---------------camera displays----------------------


//----------------goal setting--------------------------
    //--- displaying the image from ros topic---
    
        //listen to the topic camera_1/image_raw
        let goal_topic = new ROSLIB.Topic({
            ros : ros,
            name : 'lane_layer_image',
            messageType : 'sensor_msgs/Image'
        });

        // original image coordinates
        let original_width; 
        let original_height;

        //subscribing to the topic camera_1/image_raw
        goal_topic.subscribe(function(message)
        { 
            // original image coordinates
            original_width = message.width;
            original_height = message.height;

            let image_canvas = document.getElementById( "image_canvas" );
            subscribe_to_topic(message,image_canvas);
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

    // function to find the coordinates of the point on canvas on mouse click
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
    
        let canvas = document.getElementById("image_canvas");
        let rect = canvas.getBoundingClientRect();

        // coordinates of image displayed on canvas 
        let canvas_width = rect.width;

        // scaling factor
        var scale_factor = original_width / canvas_width;

        // finding the pixels coordinates that correspond to original image 
        posX = scale_factor * posX;
        posY = scale_factor * posY; 

        // Fixing out of bounds pixel coordinates.
        if(posX < 0)
        {
            posX = 0;
        }

        if(posY < 0)
        {
            posY = 0;
        }

        if(posX > original_width) 
        {
            posX = original_width;
        }
        
        if(posY > original_height)
        {
            posY = original_height;
        }
 
        let coordinate_array = new Array();
        coordinate_array[0] = parseInt(posX) ;
        coordinate_array[1] = parseInt(posY) ;
        document.getElementById("goal_pixel_coordinates").value = " " + time + " X:" + coordinate_array[0] + " Y:" + coordinate_array[1] ;
        document.getElementById("x-co-ordinate").innerHTML = coordinate_array[0];
        document.getElementById("y-co-ordinate").innerHTML = coordinate_array[1];

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


 //--------------simulation and real time displays--------------
    // listen to the topic /clock
    let clock_topic = new ROSLIB.Topic({
        ros : ros,
        name : '/clock',
        messageType : 'rosgraph_msgs/Clock'
    });

    //subscribing to the topic /vehicle_cmd
    clock_topic.subscribe(function(message)
    {
        let str = message.clock.nsecs.toString(); //convert number to string
        let result = str.substring(0,2)  // cut first two characters
        result = parseInt(result); // convert it to a number
        document.getElementById("simulation_time").innerHTML =" " +message.clock.secs+"."+result+ " s";
    });
 //--------------simulation and real time displays----------------
 

//---------------- creating a generic card----------------
    let button_clicked = false;
    function createGenericCard()
    {
        // div holds newly created generic card
        let generic_div = document.createElement("div");

        // appending created div to main row_div
        let row_div = document.getElementById("row_div");
        row_div.appendChild(generic_div);
        
        if(button_clicked === false)
        {
            let generic_child_div = document.createElement("div");
            generic_child_div.className = "box";
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
            let topic_label = document.createElement("label");
            topic_label.id = "topic_label";
            let topic_label_text = document.createTextNode("Topic");
            topic_label.appendChild(topic_label_text);

            // creation of dropdown to hold list of rostopics 
            let dropdown = document.createElement("select");
            dropdown.id = "select_topic";
            dropdown.onclick = getTopics;
            dropdown.onchange = display_topic_data;

            // appending label and dropdown to p element
            p.appendChild(topic_label);
            p.appendChild(dropdown);

            // creation of another p element
            let p1 = document.createElement("p");
            p1.id = "p1";

            // creation of label element
            let topic_data = document.createElement("label");
            topic_data.id = "topic_data";
            let topic_data_text = document.createTextNode("Topic_Data");
            topic_data.appendChild(topic_data_text);

            // creation of textarea to hold the data of selected rostopic
            let textarea = document.createElement("textarea");
            textarea.id = "topic_data_textbox";
            textarea.rows = "4";
            textarea.columns = "auto";
            textarea.name = "topic_data";
            textarea.disabled = "true";

            // appending label and textarea to p element
            p1.appendChild(topic_data);
            p1.appendChild(textarea);

            // appending both p elements to div tag and appending that div to div1 created to hold generic card
            generic_child_div.appendChild(p);
            generic_child_div.appendChild(p1);
            generic_div.appendChild(generic_child_div);
            document.getElementById("generic-div").style.display ="block";
            document.getElementById("generic-div").append(generic_div);
        }
        button_clicked = true;
    }
//---------------- creating a generic card----------------


//-----displaying the list of topics in the dropdown  & data of selected rostopic in textarea of generic card-------------
    let isClicked = false;
    let topicsClient = new ROSLIB.Service({
        ros : ros,
        name : '/rosapi/topics',
        serviceType : 'rosapi/Topics'
        });

    let request = new ROSLIB.ServiceRequest();
    let listener;

    // function to get the list of rostopics 
    function getTopics() 
    {
        let select = document.getElementById("select_topic");
        if(isClicked === false)
        {
            topicsClient.callService(request, function(result) 
            {
                topics_list = result.topics;
                topic_types = result.types;

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
        let selected = document.getElementById("select_topic");
        selected_topic = selected.options[selected.selectedIndex].text;
        selected_topic_value = selected.options[selected.selectedIndex].value;

        topicsClient.callService(request, function(result) 
        {
            topic_types = result.types;
            for(var i = 0; i < topic_types.length; i++)
            {
                if(i == selected_topic_value)
                { 
                    // Subscribing to a Topic
                    listener = new ROSLIB.Topic({
                        ros : ros,
                        name : selected_topic,
                        messageType : topic_types[i]
                    });

                    listener.subscribe(function(message) {
                        topic_val = JSON.stringify(message);
                        document.getElementById("topic_data_textbox").value = topic_val ;
                    });
                } 
            }
        });
        listener.unsubscribe();
    }
//-----displaying the list of topics in the dropdown  & data of selected rostopic in textarea of generic card-------------


        