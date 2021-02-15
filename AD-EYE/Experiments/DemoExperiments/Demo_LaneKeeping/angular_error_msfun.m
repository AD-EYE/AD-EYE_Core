function angular_error_msfun( block )
    setup( block );
end

function setup( block )

    % port setup
    block.NumInputPorts = 9;
    block.NumOutputPorts = 1;
    
    for j=1:9,
        block.InputPort(j).Complexity = 'Real';
        block.InputPort(j).DataTypeId = 0;
        block.InputPort(j).SamplingMode = 'Sample';
    end
    
    block.OutputPort(1).Complexity = 'Real';
    block.OutputPort(1).DataTypeId = 0;
    block.OutputPort(1).SamplingMode = 'Sample';
    
    % method registration
    block.RegBlockMethod('Outputs', @Outputs);
end


function Outputs( block )
    cx1 = block.InputPort(1).Data;
    cy1 = block.InputPort(2).Data;
    cx2 = block.InputPort(3).Data;
    cy2 = block.InputPort(4).Data;
    lsx1 = block.InputPort(5).Data;
    lsy1 = block.InputPort(6).Data;
    lsx2 = block.InputPort(7).Data;
    lsy2 = block.InputPort(8).Data;
    scaler = block.InputPort(9).Data;
    
    cv = [ cx2 cy2 0 ] - [ cx1 cy1 0 ];
    lsv = [ lsx2 lsy2 0 ] - [ lsx1 lsy1 0 ];

    cp = cross(cv,lsv);
    angle = atan2(norm(cp),dot(cv,lsv));
    angle = angle * sign(cp(3));

    block.OutputPort(1).Data = angle * scaler;
end

