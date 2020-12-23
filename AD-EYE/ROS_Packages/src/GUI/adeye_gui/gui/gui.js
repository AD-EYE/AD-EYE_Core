
var green="#699b2c";
document.addEventListener('DOMContentLoaded', (event) => 
{
    var dragSrcEl = null;

    function handleDragStart(e) 
    {
      this.style.opacity = '0.4';
      dragSrcEl = this;
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
      if (dragSrcEl != this) 
      {
       dragSrcEl.innerHTML = this.innerHTML;
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
    // Listen to the topic /vehicle_cmd
    let vel_listener = new ROSLIB.Topic({
        ros : ros,
        name : '/vehicle_cmd',
        messageType : 'autoware_msgs/VehicleCmd'
     });

    //subscribing to the topic
    vel_listener.subscribe(function(message)
    {
        let value = message.ctrl_cmd.linear_velocity;
        const gaugeElement = document.querySelector(".gauge");
        value = value / 10; //shifting one decimal
                            
        //function to set values of the gauge
        function setGaugeValue(gauge, value) 
        {
        //safety check for the values within the range
            if (value < 0 || value > 1) 
            {
              return;
            }
            //making the turn over the gauge body
            gauge.querySelector(".gauge_fill").style.transform = `rotate(${value / 3}turn)`;
            value = (value * 180) / 5; // to convert the value to km/hr from m/s
            //printing the velocity value
            gauge.querySelector(".gauge_cover").textContent = `${Math.round(value )} km/h`;
        }

        // passing the value received from the topic /vehicle_cmd to the function to display the velocity
        setGaugeValue(gaugeElement, value);
    });
//-------------------linear velocity----------------



//-------------------linear acceleration----------------
    //listen to the topic
    let acc_listener = new ROSLIB.Topic({
        ros : ros,
        name : '/vehicle_cmd',
        messageType : 'autoware_msgs/VehicleCmd'
    });

    //subscribing to the topic
    acc_listener.subscribe(function(message)
    {
        let value_a = message.ctrl_cmd.linear_acceleration;
        const gaugeElement_a = document.querySelector(".gauge_a");
        value_a = value_a / 10; //shifting one decimal

        //function to set values of the gauge
        function setGaugeValue_a(gauge_a, value_a) 
        {
        //safety check for the values within the range
            if (value_a < 0 || value_a > 1) 
            {
              return;
            }
            //making the turn over the gauge body
            gauge_a.querySelector(".gauge_a_fill").style.transform = `rotate(${value_a / 4}turn)`;
            //printing the acceleration value
            gauge_a.querySelector(".gauge_a_cover").textContent = `${Math.round(value_a*10 )} m/s²`;
        }

        // passing the value received from the topic /vehicle_cmd to the function to display the acceleration
        setGaugeValue_a(gaugeElement_a, value_a);
    });
//-------------------linear acceleration----------------



//-------------------Nominal Vs Safety Channel----------------
    //listen to the topic
    let data_listener = new ROSLIB.Topic({
        ros : ros,
        name : '/switchCommand',
        messageType : 'std_msgs/Int32'
    });

    //subscribing to the topic
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
    
    // function to switch the channel on buttuon click from nominal to safety and vice-versa 
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
    //listen to the topic
    let manager_listener = new ROSLIB.Topic({
        ros : ros,
        name : '/manager/state',
        messageType : 'std_msgs/Int8'
    });

    //subscribing to the topic
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

    // function to change the state from one to another by clicking on the buttons.
    function toggleStateinitial(initial)
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

            initialToggleOff.publish(initialOff);
        }
    }
    
    // function to change the state from one to another by clicking on the buttons.
    function toggleStateactivation(activation)
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

            activationToggleOff.publish(activationOff);
        }
    }

    // function to change the state from one to another by clicking on the buttons.
    function toggleStatefault(fault)
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
    //listen to the topic
    var track_listener = new ROSLIB.Topic({
        ros : ros,
        name : '/tracked_objects',
        messageType : 'autoware_msgs/DetectedObjectArray'
    });

    //subscribing to the topic
    track_listener.subscribe(function(message) 
    {

        let object=[];
        var k=0;
        for (var i = 0; i < message.objects.length; i++) 
        {
            for (var j = 0; j < message.objects[i].label.length; j++) 
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



//---------------------behaviour state--------------
    //listen to the topic
    var beh_listener = new ROSLIB.Topic({
        ros : ros,
        name : '/behavior_state',
        messageType : 'visualization_msgs/MarkerArray'
    });

    //subscribing to the topic
    beh_listener.subscribe(function(message) 
    {
        let marker = [];
        var k = 0;
        for (var i = 0; i < message.markers.length; i++) 
        {
            for (var j = 0; j < message.markers[i].text.length; j++) 
            {
                marker[k] = message.markers[i].text[j];
                k++;
            }
            t = marker.join("")
            document.getElementById("beh").innerHTML = t;
            marker.splice(0, marker.length);
        }
    });
//--------------------behaviour state---------------



//-----------------feature state-----------------
//listen to the topic
var feature_listener = new ROSLIB.Topic({
    ros : ros,
    name : 'manager/features',
    messageType : 'std_msgs/Int32MultiArray'
});


var arr;
feature_listener.subscribe(function(message) 
{
    arr = message.data;
    var num =arr;
    // array for twelve leds
    var strColorPairs = Array(
    {'position' : 0, 'color' : '#699b2c'},//remove magic numbers
    {'position' : 1, 'color' : '#699b2c'},
    {'position' : 2, 'color' : '#699b2c'},
    {'position' : 3, 'color' : '#699b2c'},
    {'position' : 4, 'color' : '#699b2c'},
    {'position' : 5, 'color' : '#699b2c'},
    {'position' : 6, 'color' : '#699b2c'},
    {'position' : 7, 'color' : '#699b2c'},
    {'position' : 8, 'color' : '#699b2c'},
    {'position' : 9, 'color' : '#699b2c'},
    {'position' : 10, 'color' : '#699b2c'},
    {'position' : 11, 'color' : '#699b2c'});

    var position = new Array();
    position = checkPosition(num);
    colorBox(position);

    //function to change the color of leds and reseting it to gray when not in use
    function colorBox(position)
    {
        var divList = document.getElementsByClassName('btn2');
        var i, n = divList.length;
             
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
                     //continue;
                    }
                    else 
                    {
                        divList[i].style.backgroundColor  = 'gray';
                    }
                }
            }

        }
    }

    //function to check the positions of the features to be enabled



    function checkPosition(num)
    {
        let on = [];
        for (let i = 0; i < num.length; i++)
        {
            if (num[i] === 1)
            {
              on.push(i);
            }
        }
        return on;
    }
});
//-----------------feature state-----------------



//-------------------- Feature Change---------------

    function toggleStateRecording(recording)
    {
        if(recording.value=="off")
        {
            recording.value="on";
            var recordingToggleOff = new ROSLIB.Topic({
                ros : ros,
                name : '/Features_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            var recordingOff = new ROSLIB.Message({
                data: [1,1,1,0,1,0,1,0,1,1,1,0]
            });
                    
            recordingToggleOff.publish(recordingOff);
        } 
    } 

    function toggleStateMap(map)
    {
        if(map.value=="off")
        {
            map.value="on";
            var mapToggleOff = new ROSLIB.Topic({
                ros : ros,
                name : '/Features_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            var mapOff = new ROSLIB.Message({
                 data: [0,1,1,0,1,0,1,0,1,1,1,0] //hard coding is incorrect, should subscribe from topic and change exactly one value for each
            });
                    
            mapToggleOff.publish(mapOff);
        } 
    } 

    function toggleStateSensing(sensing)
    {
        if(sensing.value=="off")
        {
            sensing.value="on";
            var sensingToggleOff = new ROSLIB.Topic({
                ros : ros,
                name : '/Features_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            var sensingOff = new ROSLIB.Message({
                /* data:arr,
                data[2]1 */
                data: [0,1,1,0,1,0,1,0,1,1,1,0] 
                /* data:arr */
            });
                    
            sensingToggleOff.publish(sensingOff);
        } 
    } 

    function toggleStateLocalization(localization)
    {
        if(localization.value=="off")
        {
            localization.value="on";
            var localizationToggleOff = new ROSLIB.Topic({
                ros : ros,
                name : '/Features_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            var localizationOff = new ROSLIB.Message({
                data: [0,1,1,1,1,0,1,0,1,1,1,0]
            });
                    
            localizationToggleOff.publish(localizationOff);
        } 
    } 

    function toggleStateFakeLocalization(fakelocalization)
    {
        if(fakelocalization.value=="off")
        {
            fakelocalization.value="on";
            var fakelocalizationToggleOff = new ROSLIB.Topic({
                ros : ros,
                name : '/Features_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            var fakelocalizationOff = new ROSLIB.Message({
                data: [0,1,1,1,1,0,1,0,1,1,1,0]
            });
                    
            fakelocalizationToggleOff.publish(fakelocalizationOff);
        } 
    } 

    function toggleStateDetection(detection)
    {
        if(detection.value=="off")
        {
            detection.value="on";
            var detectionToggleOff = new ROSLIB.Topic({
                ros : ros,
                name : '/Features_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            var detectionOff = new ROSLIB.Message({
                data: [0,1,1,1,1,1,1,0,1,1,1,0]
            });
                    
            detectionToggleOff.publish(detectionOff);
        } 
    } 

    function toggleStateMissionPlanning(missionplanning)
    {
        if(missionplanning.value=="off")
        {
            missionplanning.value="on";
            var missionplanningToggleOff = new ROSLIB.Topic({
                ros : ros,
                name : '/Features_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            var missionplanningOff = new ROSLIB.Message({
                data: [0,1,1,1,1,1,1,1,1,1,1,0]
            });
                    
            missionplanningToggleOff.publish(missionplanningOff);
        } 
    } 

    function toggleStateMotion(motionplanning)
    {
        if(motionplanning.value=="off")
        {
            motionplanning.value="on";
            var motionplanningToggleOff = new ROSLIB.Topic({
                ros : ros,
                name : '/Features_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            var motionplanningOff = new ROSLIB.Message({
                data: [0,1,1,1,1,1,1,1,1,1,1,0]
            });
                    
            motionplanningToggleOff.publish(motionplanningOff);
        } 
    } 

    function toggleStateSwitch(Switch)
    {
        if(Switch.value=="off")
        {
            Switch.value="on";
            var SwitchToggleOff = new ROSLIB.Topic({
                ros : ros,
                name : '/Features_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            var SwitchOff = new ROSLIB.Message({
                data: [0,1,1,1,1,1,1,1,1,1,1,0]
            });
                    
            SwitchToggleOff.publish(SwitchOff);
        } 
    } 

    function toggleStateSSMP(ssmp)
    {
        if(ssmp.value=="off")
        {
            ssmp.value="on";
            var ssmpToggleOff = new ROSLIB.Topic({
                ros : ros,
                name : '/Features_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            var ssmpOff = new ROSLIB.Message({
                data: [0,1,1,1,1,1,1,1,1,1,1,0]
            });
                    
            ssmpToggleOff.publish(ssmpOff);
        } 
    } 

    function toggleStateRviz(rviz)
    {
        if(rviz.value=="off")
        {
            rviz.value="on";
            var rvizToggleOff = new ROSLIB.Topic({
                ros : ros,
                name : '/Features_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            var rvizOff = new ROSLIB.Message({
                data: [0,1,1,1,1,1,1,1,1,1,1,0]
            });
                    
            rvizToggleOff.publish(rvizOff);
        } 
    } 

    function toggleStateExpRecording(exprecording)
    {
        if(exprecording.value=="off")
        {
            exprecording.value="on";
            var exprecordingToggleOff = new ROSLIB.Topic({
                ros : ros,
                name : '/Features_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            var exprecordingOff = new ROSLIB.Message({
                data: [0,1,1,1,1,1,1,1,1,1,1,1]
            });
                    
            exprecordingToggleOff.publish(exprecordingOff);
        } 
    } 


    
//-------------------- Feature Change---------------



//-------------fault injection---------------

              function faultinjectiongnss(gnss){
                 if(gnss.className == "on") {
                     gnss.className="off";
                    var togglegnssOn = new ROSLIB.Topic({
                       ros : ros,
                       name : '/fault_injection/GNSS',
                       messageType : 'std_msgs/Int32'
                     });

                    var gnssOn = new ROSLIB.Message({
                       data : 1
                     });
                  togglegnssOn.publish(gnssOn);
                 } else {
                    gnss.className="on";
                    var togglegnssOff = new ROSLIB.Topic({
                       ros : ros,
                       name : '/fault_injection/GNSS',
                       messageType : 'std_msgs/Int32'
                     });

                    var gnssOff = new ROSLIB.Message({
                       data : 0
                     });
                  togglegnssOff.publish(gnssOff);
                 }
              }

              function faultinjectionlidar1(lidar1){
                 if(lidar1.className == "on") {
                     lidar1.className="off";
                    var togglelidar1On = new ROSLIB.Topic({
                       ros : ros,
                       name : '/fault_injection/lidar1',
                       messageType : 'std_msgs/Int32'
                     });

                    var lidar1On = new ROSLIB.Message({
                       data : 1
                     });
                  togglelidar1On.publish(lidar1On);
                 } else {
                    lidar1.className="on";
                    var togglelidar1Off = new ROSLIB.Topic({
                       ros : ros,
                       name : '/fault_injection/lidar1',
                       messageType : 'std_msgs/Int32'
                     });

                    var lidar1Off = new ROSLIB.Message({
                       data : 0
                     });
                  togglelidar1Off.publish(lidar1Off);
                 }
              }

              function faultinjectionlidar2(lidar2){
                 if(lidar2.className == "on") {
                     lidar2.className="off";
                    var togglelidar2On = new ROSLIB.Topic({
                       ros : ros,
                       name : '/fault_injection/lidar2',
                       messageType : 'std_msgs/Int32'
                     });

                    var lidar2On = new ROSLIB.Message({
                       data : 1
                     });
                  togglelidar2On.publish(lidar2On);
                 } else {
                    lidar2.className="on";
                    var togglelidar2Off = new ROSLIB.Topic({
                       ros : ros,
                       name : '/fault_injection/lidar2',
                       messageType : 'std_msgs/Int32'
                     });

                    var lidar2Off = new ROSLIB.Message({
                       data : 0
                     });
                  togglelidar2Off.publish(lidar2Off);
                 }
              }

              function faultinjectionlidar3(lidar3){
                 if(lidar3.className == "on") {
                     lidar3.className="off";
                    var togglelidar3On = new ROSLIB.Topic({
                       ros : ros,
                       name : '/fault_injection/lidar3',
                       messageType : 'std_msgs/Int32'
                     });

                    var lidar3On = new ROSLIB.Message({
                       data : 1
                     });
                  togglelidar3On.publish(lidar3On);
                 } else {
                    lidar3.className="on";
                    var togglelidar3Off = new ROSLIB.Topic({
                       ros : ros,
                       name : '/fault_injection/lidar3',
                       messageType : 'std_msgs/Int32'
                     });

                    var lidar3Off = new ROSLIB.Message({
                       data : 0
                     });
                  togglelidar3Off.publish(lidar3Off);
                 }
              }

              function faultinjectionlidar4(lidar4){
                 if(lidar4.className == "on") {
                     lidar4.className="off";
                    var togglelidar4On = new ROSLIB.Topic({
                       ros : ros,
                       name : '/fault_injection/lidar4',
                       messageType : 'std_msgs/Int32'
                     });

                    var lidar4On = new ROSLIB.Message({
                       data : 1
                     });
                  togglelidar4On.publish(lidar4On);
                 } else {
                    lidar4.className="on";
                    var togglelidar4Off = new ROSLIB.Topic({
                       ros : ros,
                       name : '/fault_injection/lidar4',
                       messageType : 'std_msgs/Int32'
                     });

                    var lidar4Off = new ROSLIB.Message({
                       data : 0
                     });
                  togglelidar4Off.publish(lidar4Off);
                 }
              }

              function faultinjectionradar(radar){
                 if(radar.className == "on") {
                     radar.className="off";
                    var toggleradarOn = new ROSLIB.Topic({
                       ros : ros,
                       name : '/fault_injection/radar',
                       messageType : 'std_msgs/Int32'
                     });

                    var radarOn = new ROSLIB.Message({
                       data : 1
                     });
                  toggleradarOn.publish(radarOn);
                 } else {
                    radar.className="on";
                    var toggleradarOff = new ROSLIB.Topic({
                       ros : ros,
                       name : '/fault_injection/radar',
                       messageType : 'std_msgs/Int32'
                     });

                    var radarOff = new ROSLIB.Message({
                       data : 0
                     });
                  toggleradarOff.publish(radarOff);
                 }
              }

//-------------fault injection----------------



//-------------------camera display ----------------

//listen to the topic
var image_topic = new ROSLIB.Topic({
    ros : ros,
    name : '/camera_1/image_raw',
    messageType : 'sensor_msgs/Image'
 });

//subscribing to the topic
image_topic.subscribe(function(message)
{  
   var msg=atob(message.data);
   var array = new Uint8Array(new ArrayBuffer(msg.length));
    for (let i = 0; i < msg.length; i++) 
    {
        array[i] = msg.charCodeAt(i);
    }

    var canvas=document.getElementById("canvas");
    const ctx = canvas.getContext("2d"); 

    var imgData=ctx.createImageData(canvas.width,canvas.height);
    for(var j=0;j<array.length;j++)
    {
        imgData.data[4*j+0]=array[3*j+0];
        imgData.data[4*j+1]=array[3*j+1];
        imgData.data[4*j+2]=array[3*j+2];
        imgData.data[4*j+3]=255;
    }

    ctx.putImageData(imgData,0,0,0,0,canvas.width,canvas.height);
    
}); 
//-------------------camera display ----------------




