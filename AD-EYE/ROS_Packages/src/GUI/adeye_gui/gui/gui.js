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
    //listen to the topic
    var vel_listener = new ROSLIB.Topic({
        ros : ros,
        name : '/vehicle_cmd',
        messageType : 'autoware_msgs/VehicleCmd'
     });

    //subscribing to the topic
    vel_listener.subscribe(function(message)
    {
        var val = message.ctrl_cmd.linear_velocity;
        const gaugeElement = document.querySelector(".gauge");
        val = val / 10; //shifting one decimal
                            
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
            value = (value * 180) / 5;// to convert the value to km/hr from m/s
            //printing the velocity value
            gauge.querySelector(".gauge_cover").textContent = `${Math.round(value )} km/h`;
        }

        // passing the value to the function
        setGaugeValue(gaugeElement, val);
    });
//-------------------linear velocity----------------



//-------------------linear acceleration----------------
    //listen to the topic
    var acc_listener = new ROSLIB.Topic({
        ros : ros,
        name : '/vehicle_cmd',
        messageType : 'autoware_msgs/VehicleCmd'
    });

    //subscribing to the topic
    acc_listener.subscribe(function(message)
    {
        var val_a = message.ctrl_cmd.linear_acceleration;
        const gaugeElement_a = document.querySelector(".gauge_a");
        val_a = val_a / 10; //shifting one decimal

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

        // passing the value to the function
        setGaugeValue_a(gaugeElement_a, val_a);
    });
//-------------------linear acceleration----------------



//-------------------Nominal Vs Safety Channel----------------
    //listen to the topic
    var data_listener = new ROSLIB.Topic({
        ros : ros,
        name : '/switchCommand',
        messageType : 'std_msgs/Int32'
    });

    //subscribing to the topic
    data_listener.subscribe(function(message) 
    {
        var val_data = message.data;
        var num =val_data;
        // array for two leds
        var strColorPairs = Array({'position' : 0, 'color' : '#699b2c'},{'position' : 1, 'color' : '#699b2c'});
        var position = checkPosition(num);

        colorBox(position);

        //function to change the color of leds and reseting it to gray when not in use
        function colorBox(position)
        {
            var divList = document.getElementsByClassName('btn');
            var i, n = divList.length;
            curContent = divList[position].id;
            for (i=0; i<n; i++)
            {
              for (j=0; j<strColorPairs.length; j++)
                {
                    if (strColorPairs[j].position == curContent)
                    {
                     divList[curContent].style.backgroundColor  = strColorPairs[j].color;
                    }
                    else {divList[i].style.backgroundColor  = 'gray'}
                }
            }
        }

        //function to assign the position in the array base on the data value recived
        function checkPosition(num)
        {
            var position;
            if((num==0))
            {
                position=0;
            }
            else if((num==1))
            {
                position=1;
            }
            return position;
        }
    });
//-------------------Nominal Vs Safety Channel ----------------



//--------------------Toggle state---------------
    function toggleState(item)
    {
        //var test1=(item.id);
        //var currentvalue = document.getElementById(test1).value;
        if(item.value == "Off")
        {
            item.value="On";//document.getElementById(test1).value="On";
            var dataToggleOn = new ROSLIB.Topic({
                ros : ros,
                name : '/switchCommand',
                messageType : 'std_msgs/Int32'
            });

            var dataOn = new ROSLIB.Message({
                data : 1
            });
            
            dataToggleOn.publish(dataOn);
        }
        else
        {
            item.value="Off";
            var dataToggleOff = new ROSLIB.Topic({
                ros : ros,
                name : '/switchCommand',
                messageType : 'std_msgs/Int32'
            });

            var dataOff = new ROSLIB.Message({
                data : 0
            });

            dataToggleOff.publish(dataOff);
        }
    }
//--------------------Toggle state---------------



//-------------------Manager State----------------
    //listen to the topic
    var manager_listener = new ROSLIB.Topic({
        ros : ros,
        name : '/manager/state',
        messageType : 'std_msgs/Int8'
    });

    //subscribing to the topic
    manager_listener.subscribe(function(message) 
    {
        var num = message.data;
        if(num==0)
        {
            var initial = "Initiaizing";
            document.getElementById("state").innerHTML=initial;
        }
        else if(num==1)
        {
            var enabled = "Enabled";
            document.getElementById("state").innerHTML=enabled;
        }
        else if(num==2)
        {
            var engaged = "Engaged";
            document.getElementById("state").innerHTML=engaged;
        }
        else if(num==3)
        {
            var fault = "Fault";
            document.getElementById("state").innerHTML=fault;
        }
        else
        {
            document.getElementById("state").innerHTML="Unknown State"
        }

    });
//--------------------Manager State--------------



//-------------------- State Change---------------
    function toggleStateinitial(item1)
    {
        if(item1.value == "Off") 
        {
            item1.value="On";
            var initialToggleOn = new ROSLIB.Topic({
                ros : ros,
                name : '/initial_checks',
                messageType :'std_msgs/Bool'
            });

            var initialOn = new ROSLIB.Message({
                data : true
            });

            initialToggleOn.publish(initialOn);
        }
        document.getElementById("state").innerHTML="Initial Checks";
    }
        /* else 
        {
            item1.value="On";
            var initialToggleOff = new ROSLIB.Topic({
                ros : ros,
                name : '/initial_checks',
                messageType : 'std_msgs/Bool'
            });

            var initialOff = new ROSLIB.Message({
                data : false
            });

            initialToggleOff.publish(initialOff);
            document.getElementById("state").innerHTML="Initial Checks";
        } */
    

    function toggleStateactivation(act)
    {
        if(act.value == "Off") 
        {
            act.value="On";
            var activationToggleOn = new ROSLIB.Topic({
                ros : ros,
                name : '/activation_request',
                messageType : 'std_msgs/Bool'
            });

            var activationOn = new ROSLIB.Message({
                data : true
            });

            activationToggleOn.publish(activationOn);
            
        } 
        document.getElementById("state").innerHTML="Activation Request";
    }

    
    function toggleStatefault(flt)
    {
        if(flt.value == "Off") 
        {
            flt.value="On";
            var faultToggleOn = new ROSLIB.Topic({
                ros : ros,
                name : '/fault',
                messageType : 'std_msgs/Bool'
            });

            var faultOn = new ROSLIB.Message({
                data : true
            });

            faultToggleOn.publish(faultOn);
        } 
        document.getElementById("state").innerHTML="Fault";
        
    }
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
        let marker=[];
        var k=0;
        for (var i = 0; i < message.markers.length; i++) 
        {
            for (var j = 0; j < message.markers[i].text.length; j++) 
            {
                marker[k]=message.markers[i].text[j];
                k++;
            }
            t = marker.join("")
            document.getElementById("beh").innerHTML = t;
            marker.splice(0, marker.length);
        }
    });
//--------------------behaviour state---------------



//-------------------- Feature Change---------------
    function toggleStaterec(rec)
    {
        if(rec.className == "on") 
        {
            rec.className="off";
            var recToggleOn = new ROSLIB.Topic({
                ros : ros,
                name : '/feature_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            var recOn = new ROSLIB.Message({
                INITIALIZING_STATE : 
                {
                    RECORDING : 1
                },
                ENABLED_STATE : 
                {
                    RECORDING : 1
                },
                ENGAGED_STATE : 
                {
                    RECORDING : 1
                },
                FAULT_STATE : 
                {
                    RECORDING : 1
                }
            });

            recToggleOn.publish(recOn);
        } 
        else 
        {
            rec.className="on";
            var recToggleOff = new ROSLIB.Topic({
                ros : ros,
                name : '/feature_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            var recOff = new ROSLIB.Message({
            INITIALIZING_STATE : 
            {
                RECORDING : 0
            },
            ENABLED_STATE : 
            {
                RECORDING : 0
            },
                ENGAGED_STATE : 
            {
                RECORDING : 0
            },
                FAULT_STATE : 
            {
                RECORDING : 0
            }
            });
                    
            recToggleOff.publish(recOff);
        }
    }
                
    function toggleStatemap(map)
    {
        if(map.className == "on") 
        {
            map.className="off";
            var mapToggleOn = new ROSLIB.Topic({
                ros : ros,
                name : '/feature_state',
                messageType : 'std_msgs/Int32MultiArray'
            });
                      
            var mapOn = new ROSLIB.Message({
            INITIALIZING_STATE : 
            {
                MAP : 1
            },
            ENABLED_STATE : 
            {
                MAP : 1
            },
            ENGAGED_STATE : 
            {
                MAP : 1
            },
            FAULT_STATE : 
            {
                MAP : 1
            }
            });

            mapToggleOn.publish(mapOn);
        } 
        else 
        {
            map.className="on";
            var mapToggleOff = new ROSLIB.Topic({
                ros : ros,
                name : '/feature_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            var mapOff = new ROSLIB.Message({
            INITIALIZING_STATE : 
            {
                MAP : 0
            },
            ENABLED_STATE : 
            {
                MAP : 0
            },
            ENGAGED_STATE : 
            {
                MAP : 0
            },
            FAULT_STATE : 
            {
                MAP : 0
            }
            });

            mapToggleOff.publish(mapOff);
        }
    }

    function toggleStatesen(sen)
    {
        if(sen.className == "on") 
        {
            sen.className="off";
            var senToggleOn = new ROSLIB.Topic({
                ros : ros,
                name : '/feature_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            var senOn = new ROSLIB.Message({
            INITIALIZING_STATE : 
            {
                SENSING : 1
            },
            ENABLED_STATE : 
            {
                SENSING : 1
            },
            ENGAGED_STATE : 
            {
                SENSING : 1
            },
            FAULT_STATE : 
            {
                SENSING : 1
            }
            });

            senToggleOn.publish(senOn);
        } 
        else 
        {
            sen.className="on";
            var senToggleOff = new ROSLIB.Topic({
                ros : ros,
                name : '/feature_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            var senOff = new ROSLIB.Message({
            INITIALIZING_STATE : 
            {
                SENSING : 0
            },
            ENABLED_STATE : 
            {
                SENSING : 0
            },
            ENGAGED_STATE : 
            {
                SENSING : 0
            },
            FAULT_STATE : 
            {
                SENSING : 0
            }
            });

            senToggleOff.publish(senOff);
        }
    }

    function toggleStateloc(loc)
    {
        if(loc.className == "on") 
        {
            loc.className="off";
            var locToggleOn = new ROSLIB.Topic({
                ros : ros,
                name : '/feature_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            var locOn = new ROSLIB.Message({
            INITIALIZING_STATE : 
                {
                    LOCALIZATION : 1
                },
            ENABLED_STATE : 
                {
                    LOCALIZATION: 1
                },
            ENGAGED_STATE : 
                {
                    LOCALIZATION : 1
                },
            FAULT_STATE : 
                {
                    LOCALIZATION : 1
                }
            });

            locToggleOn.publish(locOn);
        } 
        else
        {
            loc.className="on";
            var locToggleOff = new ROSLIB.Topic({
                ros : ros,
                name : '/feature_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            var locOff = new ROSLIB.Message({
            INITIALIZING_STATE : 
                {
                    LOCALIZATION : 0
                },
            ENABLED_STATE : 
                {
                    LOCALIZATION : 0
                },
            ENGAGED_STATE : 
                {
                    LOCALIZATION : 0
                },
            FAULT_STATE : 
                {
                    LOCALIZATION : 0
                }
            });
                
            locToggleOff.publish(locOff);
        }
    }

    function toggleStatefloc(floc)
    {
        if(floc.className == "on") 
        {
            floc.className="off";
            var flocToggleOn = new ROSLIB.Topic({
                ros : ros,
                name : '/feature_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            var flocOn = new ROSLIB.Message({
            INITIALIZING_STATE : 
            {
                FAKE_LOCALIZATION : 1
            },
                ENABLED_STATE : 
            {
                FAKE_LOCALIZATION: 1
            },
            ENGAGED_STATE : 
            {
                FAKE_LOCALIZATION : 1
            },
                FAULT_STATE : 
            {
                FAKE_LOCALIZATION : 1
            }
            });

            flocToggleOn.publish(flocOn);
        } 
        else
        {
            floc.className="on";
            var flocToggleOff = new ROSLIB.Topic({
                ros : ros,
                name : '/feature_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            var flocOff = new ROSLIB.Message({
            INITIALIZING_STATE :
            {
                FAKE_LOCALIZATION: 0
            },
            ENABLED_STATE : 
            {
                FAKE_LOCALIZATION : 0
            },
            ENGAGED_STATE : 
            {
                FAKE_LOCALIZATION : 0
            },
            FAULT_STATE : 
            {
                FAKE_LOCALIZATION: 0
            }
            });

            flocToggleOff.publish(flocOff);
        }
    }

    function toggleStatedet(det)
    {
        if(det.className == "on") 
        {
            det.className="off";
            var detToggleOn = new ROSLIB.Topic({
                ros : ros,
                name : '/feature_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            var detOn = new ROSLIB.Message({
            INITIALIZING_STATE : 
            {
                DETECTION : 1
            },
            ENABLED_STATE : 
            {
                DETECTION : 1
            },
            ENGAGED_STATE : 
            {
                DETECTION : 1
            },
            FAULT_STATE : 
            {
                DETECTION : 1
            }
            });

            detToggleOn.publish(detOn);
        }
        else 
        {
            det.className="on";
            var detToggleOff = new ROSLIB.Topic({
                ros : ros,
                name : '/feature_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            var detOff = new ROSLIB.Message({
            INITIALIZING_STATE : 
            {
                DETECTION : 0
            },
            ENABLED_STATE : 
            {
                DETECTION : 0
            },
            ENGAGED_STATE : 
            {
                DETECTION : 0
            },
            FAULT_STATE : 
            {
                DETECTION : 0
            }
            });

            detToggleOff.publish(detOff);
        }
    }

    function toggleStatemip(mission)
    {
        if(mission.className == "on") 
        {
            mission.className="off";
            var mipToggleOn = new ROSLIB.Topic({
                ros : ros,
                name : '/feature_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            var mipOn = new ROSLIB.Message({
            INITIALIZING_STATE : 
            {
                MISSION_PLANNING : 1
            },
            ENABLED_STATE : 
            {
                MISSION_PLANNING : 1
            },
            ENGAGED_STATE : 
            {
                MISSION_PLANNING : 1
            },
            FAULT_STATE : 
            {
                MISSION_PLANNING : 1
            }
            });

            mipToggleOn.publish(mipOn);
        }
        else 
        {
            mission.className="on";
            var mipToggleOff = new ROSLIB.Topic({
                ros : ros,
                name : '/feature_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            var mipOff = new ROSLIB.Message({
            INITIALIZING_STATE : 
            {
                MISSION_PLANNING : 0
            },
            ENABLED_STATE : 
            {
                MISSION_PLANNING : 0
            },
            ENGAGED_STATE : 
            {
                MISSION_PLANNING : 0
            },
            FAULT_STATE : 
            {
                MISSION_PLANNING : 0
            }
            });

            mipToggleOff.publish(mipOff);
        }
    }

    function toggleStatemop(motion)
    {
        if(motion.className == "on") 
        {
            motion.className="off";
            var mopToggleOn = new ROSLIB.Topic({
                ros : ros,
                name : '/feature_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            var mopOn = new ROSLIB.Message({
            INITIALIZING_STATE :
            {
                MOTION_PLANNING : 1
            },
            ENABLED_STATE : 
            {
                MOTION_PLANNING : 1
            },
            ENGAGED_STATE : 
            {
                MOTION_PLANNING : 1
            },
            FAULT_STATE : 
            {
                MOTION_PLANNING : 1
            }
            });

            mopToggleOn.publish(mopOn);
        } 
        else
        {
            motion.className="on";
            var mopToggleOff = new ROSLIB.Topic({
                ros : ros,
                name : '/feature_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            var mopOff = new ROSLIB.Message({
            INITIALIZING_STATE :
            {
                MOTION_PLANNING : 0
            },
            ENABLED_STATE : 
            {
                MOTION_PLANNING: 0
            },
            ENGAGED_STATE : 
            {
                MOTION_PLANNING : 0
            },
            FAULT_STATE : 
            {
                MOTION_PLANNING : 0
            }
            });

            mopToggleOff.publish(mopOff);
        }
    }

    function toggleStateswit(swit)
    {
        if(swit.className == "on") 
        {
            swit.className="off";
            var switToggleOn = new ROSLIB.Topic({
                ros : ros,
                name : '/feature_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            var switOn = new ROSLIB.Message({
            INITIALIZING_STATE : 
            {
                SWITCH : 1
            },
            ENABLED_STATE : 
            {
                SWITCH : 1
            },
            ENGAGED_STATE : 
            {
                SWITCH : 1
            },
            FAULT_STATE : 
            {
                SWITCH : 1
            }
            });

            switToggleOn.publish(switOn);
        } 
        else
        {
            swit.className="on";
            var switToggleOff = new ROSLIB.Topic({
                ros : ros,
                name : '/feature_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            var switOff = new ROSLIB.Message({
            INITIALIZING_STATE : 
            {
                SWITCH : 0
            },
            ENABLED_STATE : 
            {
                SWITCH : 0
            },
            ENGAGED_STATE : 
            {
                SWITCH : 0
            },
            FAULT_STATE : 
            {
                SWITCH : 0
            }
            });

            switToggleOff.publish(switOff);
        }
    }

    function toggleStatessmp(ssmp)
    {
        if(ssmp.className == "on") 
        {
            ssmp.className="off";
            var ssmpToggleOn = new ROSLIB.Topic({
                ros : ros,
                name : '/feature_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            var ssmpOn = new ROSLIB.Message({
            INITIALIZING_STATE : 
            {
                SSMP : 1
            },
            ENABLED_STATE : 
            {
                SSMP : 1
            },
            ENGAGED_STATE : 
            {
                SSMP : 1
            },
            FAULT_STATE : 
            {
                SSMP : 1
            }
            });
        
            ssmpToggleOn.publish(ssmpOn);
        } 
        else 
        {
            ssmp.className="on";
            var ssmpToggleOff = new ROSLIB.Topic({
                ros : ros,
                name : '/feature_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            var ssmpOff = new ROSLIB.Message({
            INITIALIZING_STATE : 
            {
                SSMP : 0
            },
            ENABLED_STATE : 
            {
                SSMP: 0
            },
            ENGAGED_STATE : 
            {
                SSMP : 0
            },
            FAULT_STATE : 
            {
                SSMP : 0
            }
            });

            ssmpToggleOff.publish(ssmpOff);
        }
    }

    function toggleStaterviz(rviz)
    {
        if(rviz.className == "on") 
        {
            rviz.className="off";
            var rvizToggleOn = new ROSLIB.Topic({
                ros : ros,
                name : '/feature_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            var rvizOn = new ROSLIB.Message({
            INITIALIZING_STATE : 
            {
                RVIZ : 1
            },
            ENABLED_STATE : 
            {
                RVIZ : 1
            },
            ENGAGED_STATE : 
            {
                RVIZ : 1
            },
            FAULT_STATE : 
            {
                RECORDING : 1
            }
            });

            rvizToggleOn.publish(rvizOn);
        } 
        else 
        {
            rviz.className="on";
            var rvizToggleOff = new ROSLIB.Topic({
                ros : ros,
                name : '/feature_state',
                messageType : 'std_msgs/Int32MultiArray'
            });

            var rvizOff = new ROSLIB.Message({
            INITIALIZING_STATE : 
            {
                RVIZ : 0
            },
            ENABLED_STATE : 
            {
                RVIZ : 0
            },
            ENGAGED_STATE : 
            {
                RVIZ : 0
            },
            FAULT_STATE : 
            {
                RVIZ : 0
            }
            });

            rvizToggleOff.publish(rvizOff);
        }
    }
//-------------------- Feature Change---------------



//-----------------feature state-----------------
//listen to the topic
                var feature_listener = new ROSLIB.Topic({
                  ros : ros,
                  name : 'manager/features',
                  messageType : 'std_msgs/Int32MultiArray'
                });

                feature_listener.subscribe(function(message) {

                    var position;
                    document.getElementById("a").innerHTML=message.data[1];

                    i_r=message.INITIALIZING_STATE.RECORDING;
                    i_m=message.INITIALIZING_STATE.MAP;
                    i_s=message.INITIALIZING_STATE.SENSING;
                    i_l=message.INITIALIZING_STATE.LOCALIZATION;
                    i_f=message.INITIALIZING_STATE.FAKE_LOCALIZATION;
                    i_d=message.INITIALIZING_STATE.DETECTION;
                    i_mip=message.INITIALIZING_STATE.MISSION_PLANNING;
                    i_mop=message.INITIALIZING_STATE.MOTION_PLANNING;
                    i_sw=message.INITIALIZING_STATE.SWITCH;
                    i_ss=message.INITIALIZING_STATE.SSMP;
                    i_rv=message.INITIALIZING_STATE.RVIZ;

                    enab_r=message.ENABLED_STATE.RECORDING;
                    enab_m=message.ENABLED_STATE.MAP;
                    enab_s=message.ENABLED_STATE.SENSING;
                    enab_l=message.ENABLED_STATE.LOCALIZATION;
                    enab_f=message.ENABLED_STATE.FAKE_LOCALIZATION;
                    enab_d=message.ENABLED_STATE.DETECTION;
                    enab_mip=message.ENABLED_STATE.MISSION_PLANNING;
                    enab_mop=message.ENABLED_STATE.MOTION_PLANNING;
                    enab_sw=message.ENABLED_STATE.SWITCH;
                    enab_ss=message.ENABLED_STATE.SSMP;
                    enab_rv=message.ENABLED_STATE.RVIZ;

                    eng_r=message.ENGAGED_STATE.RECORDING;
                    eng_m=message.ENGAGED_STATE.MAP;
                    eng_s=message.ENGAGED_STATE.SENSING;
                    eng_l=message.ENGAGED_STATE.LOCALIZATION;
                    eng_f=message.ENGAGED_STATE.FAKE_LOCALIZATION;
                    eng_d=message.ENGAGED_STATE.DETECTION;
                    eng_mip=message.ENGAGED_STATE.MISSION_PLANNING;
                    eng_mop=message.ENGAGED_STATE.MOTION_PLANNING;
                    eng_sw=message.ENGAGED_STATE.SWITCH;
                    eng_ss=message.ENGAGED_STATE.SSMP;
                    eng_rv=message.ENGAGED_STATE.RVIZ;


                    f_r=message.FAULT_STATE.RECORDING;
                    f_m=message.FAULT_STATE.MAP;
                    f_s=message.FAULT_STATE.SENSING;
                    f_l=message.FAULT_STATE.LOCALIZATION;
                    f_f=message.FAULT_STATE.FAKE_LOCALIZATION;
                    f_d=message.FAULT_STATE.DETECTION;
                    f_mip=message.FAULT_STATE.MISSION_PLANNING;
                    f_mop=message.FAULT_STATE.MOTION_PLANNING;
                    f_sw=message.FAULT_STATE.SWITCH;
                    f_ss=message.FAULT_STATE.SSMP;
                    f_rv=message.FAULT_STATE.RVIZ;

                    if((i_r==1)||(enab_r==1)||(eng_r)||(f_r==1))
                    {
                        position=0;
                    }
                    if((i_m==1)||(enab_m==1)||(eng_m==1)(f_m==1))
                    {
                        position=1;
                    }
                    if((i_s==1)||(enab_s==1)||(eng_s==1)(f_s==1))
                    {
                        position=2;
                    }
                    if((i_l==1)||(enab_l==1)||(eng_l==1)(f_l==1))
                    {
                        position=3;
                    }
                    if((i_f==1)||(enab_f==1)||(eng_f==1)(f_f==1))
                    {
                        position=4;
                    }
                    if((i_d==1)||(enab_d==1)||(eng_d==1)(f_d==1))
                    {
                        position=5;
                    }
                    if((i_mip==1)||(enab_mip==1)||(eng_mip==1)(f_mip==1))
                    {
                        position=6;
                    }
                    if((i_mop==1)||(enab_mop==1)||(eng_mop==1)(f_mop==1))
                    {
                        position=7;
                    }
                    if((i_sw==1)||(enab_sw==1)||(eng_sw==1)(f_sw==1))
                    {
                        position=8;
                    }
                    if((i_ss==1)||(enab_ss==1)||(eng_ss==1)(f_ss==1))
                    {
                        position=9;
                    }
                    if((i_rv==1)||(enab_rv==1)||(eng_rv==1)(f_rv==1))
                    {
                        position=10;
                    }


                  // array for 11 ledsx
                    var strColorPairs = Array(
                                                {'position' : 0, 'color' : 'green'},
                                                {'position' : 1, 'color' : 'green'},
                                                {'position' : 2, 'color' : 'green'},
                                                {'position' : 3, 'color' : 'green'},
                                                {'position' : 4, 'color' : 'green'},
                                                {'position' : 5, 'color' : 'green'},
                                                {'position' : 6, 'color' : 'green'},
                                                {'position' : 7, 'color' : 'green'},
                                                {'position' : 8, 'color' : 'green'},
                                                {'position' : 9, 'color' : 'green'},
                                                {'position' :10, 'color' : 'green'}
                                            );


                    colorBox(position);
                    //function to change the color of leds and reseting it to gray when not in use
                     function colorBox(position)
                        {
                            var divList = document.getElementsByClassName('ratingBox');
                            var i, n = divList.length;
                            curContent = divList[position].id;
                            for (i=0; i<n; i++)
                            {

                                for (j=0; j<strColorPairs.length; j++)
                                {
                                    if (strColorPairs[j].position == curContent){
                                        divList[curContent].style.backgroundColor  = strColorPairs[j].color;
                                        }
                                    else {divList[i].style.backgroundColor  = 'gray'}
                                }
                            }
                        }


                });


//-----------------feature state-----------------

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




