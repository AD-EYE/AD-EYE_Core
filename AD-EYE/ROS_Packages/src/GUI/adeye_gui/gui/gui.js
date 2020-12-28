

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
        const gauge_element = document.querySelector(".gauge_velocity");
        //shifting value by one decimal
        value = value / 10; 
                            
        //function to set values of the gauge
        function setGaugeValue(gauge_velocity, value) 
        {
        //safety check to ensure that the values are within the range
            if (value < 0 || value > 1) 
            {
              return;
            }
            //making the turn over the gauge body
            gauge_velocity.querySelector(".gauge_velocity_fill").style.transform = `rotate( ${ value / 3 }turn )`;
            // to convert the value to km/hr from m/s
            value = (value * 180) / 5; 
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
        //shifting the value by one decimal
        value = value / 10; 

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
        let data = message.data;
        let number = data;

        // array for postion:color pairs
        let positionColorPairs = Array({'position' : 00, 'color' : green},{'position' : 01, 'color' : green});
        let position = assignPosition(number);
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
        function assignPosition(number)
        {
            let position;
            if((number == 0))
            {
                position = 0;
            }
            else if((number == 1))
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
            //channel.value="On";
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
            //channel.value="Off";
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
        if(initial.value == "off") 
        {
            initial.value = "on";
            let initialToggleOn = new ROSLIB.Topic({
                ros : ros,
                name : '/initial_checks',
                messageType :'std_msgs/Bool'
            });

            let initialOn = new ROSLIB.Message({
                data : true
            });
            document.getElementById("initial").innerHTML = initialOn.data;
            initialToggleOn.publish(initialOn);
        }
         
        else
        {
            initial.value = "off";
            let initialToggleOff = new ROSLIB.Topic({
                ros : ros,
                name : '/initial_checks',
                messageType :'std_msgs/Bool'
            });

            let initialOff = new ROSLIB.Message({
                data : false
            });
            document.getElementById("initial").innerHTML = initialOff.data;
            initialToggleOff.publish(initialOff);
        }
    }
    
    // function to toggle the state on and off by clicking on the buttons.
    function toggleStateactivation_OnClick(activation)
    {
        if(activation.value == "off") 
        {
            activation.value = "on";
            let activationToggleOn = new ROSLIB.Topic({
                ros : ros,
                name : '/activation_request',
                messageType : 'std_msgs/Bool'
            });

            let activationOn = new ROSLIB.Message({
                data : true
            });
            document.getElementById("activation").innerHTML = activationOn.data;
            activationToggleOn.publish(activationOn);
        } 
        else
        {
            activation.value = "off";
            let activationToggleOff = new ROSLIB.Topic({
                ros : ros,
                name : '/activation_request',
                messageType :'std_msgs/Bool'
            });

            let activationOff = new ROSLIB.Message({
                data : false
            });
            document.getElementById("activation").innerHTML = activationOff.data;
            activationToggleOff.publish(activationOff);
        }
    }

    // function to toggle the state on and off by clicking on the buttons.
    function toggleStatefault_OnClick(fault)
    {
        if(fault.value == "off") 
        {
            fault.value = "on";
            let faultToggleOn = new ROSLIB.Topic({
                ros : ros,
                name : '/fault',
                messageType : 'std_msgs/Bool'
            });

            let faultOn = new ROSLIB.Message({
                data : true
            });
            document.getElementById("fault").innerHTML = faultOn.data;
            faultToggleOn.publish(faultOn);
        } 
        else
        {
            fault.value = "off";
            let faultToggleOff = new ROSLIB.Topic({
                ros : ros,
                name : '/fault',
                messageType :'std_msgs/Bool'
            });

            let faultOff = new ROSLIB.Message({
                data : false
            });
            document.getElementById("fault").innerHTML = faultOff.data;
            faultToggleOff.publish(faultOff);
        }
        
    }
//--------------------Manager State--------------



//-------------------- State Change---------------
    
   

//choose consistent function names, including casing
//each function should have at least a line describing purpose
//each file in the project should have a few lines describing purpose
//variable names should be as descrptive as possible, check casing
//add wiki page about general coding guideline rules and add examples about javascript

//-------------------- state Change---------------



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
            s = object.join("")
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
    var behavior_listener = new ROSLIB.Topic({
        ros : ros,
        name : '/behavior_state',
        messageType : 'visualization_msgs/MarkerArray'
    });

    //subscribing to the topic /behavior_state
    behavior_listener.subscribe(function(message) 
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
            t = marker.join("")
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

    let green="#699b2c";
    let data_array;

    //subscribing to the topic manager/features
    feature_listener.subscribe(function(message) 
    {
        data_array = message.data;
        let number =data_array;
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
        position = checkPosition(number);
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
        function checkPosition(number)
        {
            let dataon = [];
            for (let i = 0; i < number.length; i++)
            {
                if (number[i] === 1)
                {
                dataon.push(i);
                }
            }
            return dataon;
        }
});
//-----------------feature state-----------------



//-------------------- feature Change---------------
    // function to switch on the feature recording on button click and publishing the message on to topic /Features_state
    function toggleStateRecording_OnClick(recording)
    {
        if(recording.value == "off")
        {
            recording.value = "on";
            let recordingToggleOff = new ROSLIB.Topic({
                ros : ros,
                name : '/Features_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            let recordingOff = new ROSLIB.Message({
                data: [1,1,1,0,1,0,1,0,1,1,1,0]
            });
            recordingToggleOff.publish(recordingOff);
        } 
    } 
    // function to switch on the feature map on button click and publishing the message on to topic /Features_state
    function toggleStateMap_OnClick(map)
    {
        if(map.value == "off")
        {
            map.value = "on";
            let mapToggleOff = new ROSLIB.Topic({
                ros : ros,
                name : '/Features_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            let mapOff = new ROSLIB.Message({
                data : data_array,
                data : data[1]
    
                 //data: [0,1,1,0,1,0,1,0,1,1,1,0] //hard coding is incorrect, should subscribe from topic and change exactly one value for each
            });
                    
            mapToggleOff.publish(mapOff);
        } 
    } 
    // function to switch on the feature sensing on button click and publishing the message on to topic /Features_state
    function toggleStateSensing_OnClick(sensing)
    {
        if(sensing.value == "off")
        {
            sensing.value = "on";
            let sensingToggleOff = new ROSLIB.Topic({
                ros : ros,
                name : '/Features_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            let sensingOff = new ROSLIB.Message({
                /* data:arr,
                data[2]1 */
                data: [0,1,1,0,1,0,1,0,1,1,1,0] 
                /* data:arr */
            });
            sensingToggleOff.publish(sensingOff);
        } 
    } 
    // function to switch on the feature localization on button click and publishing the message on to topic /Features_state
    function toggleStateLocalization_OnClick(localization)
    {
        if(localization.value == "off")
        {
            localization.value = "on";
            let localizationToggleOff = new ROSLIB.Topic({
                ros : ros,
                name : '/Features_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            let localizationOff = new ROSLIB.Message({
                data: [0,1,1,1,1,0,1,0,1,1,1,0]
            });
            localizationToggleOff.publish(localizationOff);
        } 
    } 
    // function to switch on the feature fakelocalization on button click and publishing the message on to topic /Features_state
    function toggleStateFakeLocalization_OnClick(fakelocalization)
    {
        if(fakelocalization.value == "off")
        {
            fakelocalization.value = "on";
            let fakelocalizationToggleOff = new ROSLIB.Topic({
                ros : ros,
                name : '/Features_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            let fakelocalizationOff = new ROSLIB.Message({
                data: [0,1,1,1,1,0,1,0,1,1,1,0]
            });
            fakelocalizationToggleOff.publish(fakelocalizationOff);
        } 
    } 
    // function to switch on the feature detection on button click and publishing the message on to topic /Features_state
    function toggleStateDetection_OnClick(detection)
    {
        if(detection.value == "off")
        {
            detection.value = "on";
            let detectionToggleOff = new ROSLIB.Topic({
                ros : ros,
                name : '/Features_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            let detectionOff = new ROSLIB.Message({
                data: [0,1,1,1,1,1,1,0,1,1,1,0]
            });
            detectionToggleOff.publish(detectionOff);
        } 
    } 
    // function to switch on the feature missionplanning on button click and publishing the message on to topic /Features_state
    function toggleStateMissionPlanning_OnClick(missionplanning)
    {
        if(missionplanning.value == "off")
        {
            missionplanning.value = "on";
            let missionplanningToggleOff = new ROSLIB.Topic({
                ros : ros,
                name : '/Features_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            let missionplanningOff = new ROSLIB.Message({
                data: [0,1,1,1,1,1,1,1,1,1,1,0]
            });
            missionplanningToggleOff.publish(missionplanningOff);
        } 
    } 
    // function to switch on the feature motion planning on button click and publishing the message on to topic /Features_state
    function toggleStateMotion_OnClick(motionplanning)
    {
        if(motionplanning.value == "off")
        {
            motionplanning.value = "on";
            let motionplanningToggleOff = new ROSLIB.Topic({
                ros : ros,
                name : '/Features_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            let motionplanningOff = new ROSLIB.Message({
                data: [0,1,1,1,1,1,1,1,1,1,1,0]
            });
            motionplanningToggleOff.publish(motionplanningOff);
        } 
    } 
    // function to switch on the feature switch on button click and publishing the message on to topic /Features_state
    function toggleStateSwitch_OnClick(Switch)
    {
        if(Switch.value == "off")
        {
            Switch.value = "on";
            let SwitchToggleOff = new ROSLIB.Topic({
                ros : ros,
                name : '/Features_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            let SwitchOff = new ROSLIB.Message({
                data: [0,1,1,1,1,1,1,1,1,1,1,0]
            });
            SwitchToggleOff.publish(SwitchOff);
        } 
    } 
    // function to switch on the feature ssmp on button click and publishing the message on to topic /Features_state
    function toggleStateSSMP_OnClick(ssmp)
    {
        if(ssmp.value == "off")
        {
            ssmp.value = "on";
            let ssmpToggleOff = new ROSLIB.Topic({
                ros : ros,
                name : '/Features_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            let ssmpOff = new ROSLIB.Message({
                data: [0,1,1,1,1,1,1,1,1,1,1,0]
            });
            ssmpToggleOff.publish(ssmpOff);
        } 
    } 
    // function to switch on the feature rviz on button click and publishing the message on to topic /Features_state
    function toggleStateRviz_OnClick(rviz)
    {
        if(rviz.value == "off")
        {
            rviz.value = "on";
            let rvizToggleOff = new ROSLIB.Topic({
                ros : ros,
                name : '/Features_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            let rvizOff = new ROSLIB.Message({
                data: [0,1,1,1,1,1,1,1,1,1,1,0]
            });
            rvizToggleOff.publish(rvizOff);
        } 
    } 
    // function to switch on the feature experiment recording on button click and publishing the message on to topic /Features_state
    function toggleStateExpRecording_OnClick(exprecording)
    {
        if(exprecording.value == "off")
        {
            exprecording.value = "on";
            let exprecordingToggleOff = new ROSLIB.Topic({
                ros : ros,
                name : '/Features_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            let exprecordingOff = new ROSLIB.Message({
                data: [0,1,1,1,1,1,1,1,1,1,1,1]
            });
            exprecordingToggleOff.publish(exprecordingOff);
        } 
    } 
//-------------------- feature Change---------------



//-------------fault injection---------------
    // function to switch on gnss on button click and publishing the message on to topic fault_injection/GNSS
    function faultInjectionGNSS_OnClick(gnss)
    {
        if(gnss.className == "on") 
        {
            gnss.className = "off";
            let togglegnssOn = new ROSLIB.Topic({
            ros : ros,
            name : '/fault_injection/GNSS',
            messageType : 'std_msgs/Int32'
            });

            let gnssOn = new ROSLIB.Message({
            data : 1
            });
            togglegnssOn.publish(gnssOn);
        } 
        else 
        {
            gnss.className = "on";
            let togglegnssOff = new ROSLIB.Topic({
            ros : ros,
            name : '/fault_injection/GNSS',
            messageType : 'std_msgs/Int32'
            });

            let gnssOff = new ROSLIB.Message({
            data : 0
            });
            togglegnssOff.publish(gnssOff);
        }
    }
    // function to switch on lidar1 on button click and publishing the message on to topic fault_injection/lidar1
    function faultinjectionlidar1_OnClick(lidar1)
    {
        if(lidar1.className == "on") 
        {
            lidar1.className = "off";
            let togglelidar1On = new ROSLIB.Topic({
            ros : ros,
            name : '/fault_injection/lidar1',
            messageType : 'std_msgs/Int32'
            });

            let lidar1On = new ROSLIB.Message({
            data : 1
            });
            togglelidar1On.publish(lidar1On);
        } 
        else 
        {
            lidar1.className = "on";
            let togglelidar1Off = new ROSLIB.Topic({
            ros : ros,
            name : '/fault_injection/lidar1',
            messageType : 'std_msgs/Int32'
            });

            let lidar1Off = new ROSLIB.Message({
            data : 0
            });
            togglelidar1Off.publish(lidar1Off);
        }
    }
    // function to switch on lidar2 on button click and publishing the message on to topic fault_injection/lidar2
    function faultinjectionlidar2(lidar2)
    {
        if(lidar2.className == "on") 
        {
            lidar2.className="off";
            let togglelidar2On = new ROSLIB.Topic({
            ros : ros,
            name : '/fault_injection/lidar2',
            messageType : 'std_msgs/Int32'
            });

            let lidar2On = new ROSLIB.Message({
            data : 1
            });
            togglelidar2On.publish(lidar2On);
        } 
        else 
        {
            lidar2.className="on";
            let togglelidar2Off = new ROSLIB.Topic({
            ros : ros,
            name : '/fault_injection/lidar2',
            messageType : 'std_msgs/Int32'
            });

            let lidar2Off = new ROSLIB.Message({
            data : 0
            });
            togglelidar2Off.publish(lidar2Off);
        }
    }
    // function to switch on lidar3 on button click and publishing the message on to topic fault_injection/lidar3
    function faultinjectionlidar3(lidar3)
    {
        if(lidar3.className == "on") 
        {
            lidar3.className = "off";
            let togglelidar3On = new ROSLIB.Topic({
            ros : ros,
            name : '/fault_injection/lidar3',
            messageType : 'std_msgs/Int32'
            });

            let lidar3On = new ROSLIB.Message({
            data : 1
            });
            togglelidar3On.publish(lidar3On);
        } 
        else 
        {
            lidar3.className="on";
            let togglelidar3Off = new ROSLIB.Topic({
            ros : ros,
            name : '/fault_injection/lidar3',
            messageType : 'std_msgs/Int32'
            });

            let lidar3Off = new ROSLIB.Message({
            data : 0
            });
            togglelidar3Off.publish(lidar3Off);
        }
    }
    // function to switch on lidar4 on button click and publishing the message on to topic fault_injection/lidar4
    function faultinjectionlidar4(lidar4)
    {
        if(lidar4.className == "on") 
        {
            lidar4.className = "off";
            let togglelidar4On = new ROSLIB.Topic({
            ros : ros,
            name : '/fault_injection/lidar4',
            messageType : 'std_msgs/Int32'
            });

            let lidar4On = new ROSLIB.Message({
            data : 1
            });
            togglelidar4On.publish(lidar4On);
        } 
        else 
        {
            lidar4.className = "on";
            let togglelidar4Off = new ROSLIB.Topic({
            ros : ros,
            name : '/fault_injection/lidar4',
            messageType : 'std_msgs/Int32'
            });

            let lidar4Off = new ROSLIB.Message({
            data : 0
            });
            togglelidar4Off.publish(lidar4Off);
        }
    }
    // function to switch on radar on button click and publishing the message on to topic fault_injection/radar
    function faultinjectionradar(radar)
    {
        if(radar.className == "on") 
        {
            radar.className = "off";
            let toggleradarOn = new ROSLIB.Topic({
            ros : ros,
            name : '/fault_injection/radar',
            messageType : 'std_msgs/Int32'
            });

            let radarOn = new ROSLIB.Message({
            data : 1
            });
            toggleradarOn.publish(radarOn);
        } 
        else 
        {
            radar.className = "on";
            let toggleradarOff = new ROSLIB.Topic({
            ros : ros,
            name : '/fault_injection/radar',
            messageType : 'std_msgs/Int32'
            });

            let radarOff = new ROSLIB.Message({
            data : 0
            });
            toggleradarOff.publish(radarOff);
        }
    }

//-------------fault injection----------------



//-------------------camera display ----------------

    //listen to the topic camera_1/image_raw
    var image_topic = new ROSLIB.Topic({
        ros : ros,
        name : '/camera_1/image_raw',
        messageType : 'sensor_msgs/Image'
    });

    //subscribing to the topic camera_1/image_raw
    image_topic.subscribe(function(message)
    {  
        let msg = atob(message.data);
        let array = new Uint8Array(new ArrayBuffer(msg.length));
        for (let i = 0; i < msg.length; i++) 
        {
            array[i] = msg.charCodeAt(i);
        }

        var canvas = document.getElementById( "canvas" );
        const ctx = canvas.getContext( "2d" ); 

        var imgData = ctx.createImageData(canvas.width,canvas.height);
        for(var j = 0; j < array.length; j++)
        {
            imgData.data[ 4 * j + 0 ] = array[ 3 * j + 0 ];
            imgData.data[ 4 * j + 1 ] = array[ 3 * j + 1 ];
            imgData.data[ 4 * j + 2 ] = array[ 3 * j + 2 ];
            imgData.data[ 4 * j + 3 ] = 255;
        }
        ctx.putImageData(imgData,0,0,0,0,canvas.width,canvas.height);
    }); 
//-------------------camera display ----------------




