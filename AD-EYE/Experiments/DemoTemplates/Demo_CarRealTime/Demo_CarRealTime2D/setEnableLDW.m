% setEnableLDW connects to raspberry pi and sets 0/1 on the LDWmdl state
%
% Usage - setEnableLDW(0/1)
%                      0 - To disable
%                      1 - To enable
%
% Always requires an argument
%
% NOTE: An error is thrown if the raspberry pi does not respond in 5000ms
%

function setEnableLDW(enable)

    if (nargin < 1)
        error('setEnableLDW:InsufficientArguments','Not enough arguments');
    end

    import java.net.DatagramSocket
	import java.net.DatagramPacket
    import java.io.*
    
    host = '10.87.2.178';
    ctrl_port = 8855;
    data_port = 8854;
	cmd = 'START';
	if(enable == 0)
		cmd = 'STOP';
	end
	
	start_packet = DatagramPacket(java.lang.String(cmd).getBytes(), length(cmd), java.net.InetAddress.getByName(host), ctrl_port);	
	control_sock = DatagramSocket();
	
	control_sock.send(start_packet);
    
    if(strcmp(cmd,'START'))
        data_size = 3;
        target_buffer = java.util.Arrays.copyOf(int8(zeros(data_size,1)),data_size);

        dataPacket = DatagramPacket(target_buffer, data_size);    
        input_sock = DatagramSocket(data_port);

        timeout_val = 5000;    
        input_sock.setSoTimeout(timeout_val);

        try_again = false;

        try
            input_sock.receive(dataPacket);
            disp('LDW enabled');
        catch
            % request got timeout we try again
            try_again = true;
        end

        if(try_again)

            % send the request again
            control_sock.send(start_packet);

            try
                input_sock.receive(dataPacket);
                disp('LDW enabled');
            catch
                input_sock.close;
                control_sock.close;
                error('toggleLDW:noData', 'No data was received from Rpi, try restarting it')
            end

        end    
        input_sock.close;
    else
        disp('LDW disabled');
    end   
    
	control_sock.close;

end